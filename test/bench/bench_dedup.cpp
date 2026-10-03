// test/bench/bench_dedup.cpp
// Deterministic duplicate-suppression benchmark + spec conformance check.
//
// Inputs are tracked real captures only (no network, no clock input, fixed
// 32-bit LCG seed):
//   test/data/dcr_vectors.json    — 2022 QZQSM capture (MT43)
//   test/data/dcx_vectors.json    — 2024 QZQSM capture (MT44, 3 satellites)
//   test/data/nankai_vectors.json — Nankai multi-page event
//
// Spec model (qzss-specs/アプリケーションノートv2.md, 原PDF p.23–27)
//   ① 複数衛星からの受信 — 照合の対象は MT～VN（フレーム bit 8..219 = 212 bit、
//     付属フローチャートも「MT～Vnの212bitについて比較する」と明記）。250 ビット
//     全体でもなく、プリアンブル（bit 0..7）も Reserved（bit 220..225）も含めない
//     — どちらも放送で巡回するため、含めると 1 情報が分裂する。
//     The 250-bit frame carries no satellite identifier (svid comes from the
//     NMEA/UBX header), so the key carries no svid — a per-satellite key would
//     re-announce one information once per relay satellite.
//   ② 連続受信 — 保存した履歴と照合し、一致すれば通知しない。履歴は
//     手順④ 配信終了条件 / 手順④' 無受信タイムアウトで削除する。
//     One information is therefore remembered for its validity window and
//     forgotten after it. Roughest faithful reading used here: an information
//     is live while it was received within the phase's declared window.
//
// Phases P1–P4 are scored against that model; P5 measures throughput only.
// The aggregated Nankai check is behavioural, not a phase: the same event fed in
// two page orders must be reported once (see nankaiKeyStable).
//
// What is optimised
// Primary     NANOS_PER_OP   — ns per decision over the scored stream.
// Guardrails  NEW_RECALL     — fraction of genuinely-new informations reported
//                              (a filter that suppresses everything scores 0
//                              here; autoresearch.sh fails the run below the
//                              baseline).
//             DUP_SUPPRESS   — fraction of in-window repeats suppressed.
// A metric built only from ACCURACY would be gamed by the trivial
// "everything is a duplicate" filter, which would suppress every alert.
//
// Harness contract: "METRIC <name>=<value>" lines, exit 0 on success.
// CRASH_GROUP is a sentinel: a run that aborts mid-way leaves it at -1.

#include "azaraC.h"
#include "internal/Dedup.h"
#include "../test_helpers.h"   // setBits / crc24qRef / makeNmeaQzqsm (shared host helpers)

#include <algorithm>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <set>
#include <string>
#include <vector>

#if defined(__x86_64__) || defined(_M_X64) || defined(__i386__)
#  include <x86intrin.h>
#  define BENCH_HAS_RDTSC 1
#endif

using azaraC::Parser;
using azaraC::internal::DedupFilter;
using azaraC::internal::DedupKey;

// measurement

static inline uint64_t readCycles() {
#ifdef BENCH_HAS_RDTSC
    return __rdtsc();
#else
    return (uint64_t)std::chrono::duration_cast<std::chrono::nanoseconds>(
               std::chrono::steady_clock::now().time_since_epoch()).count();
#endif
}

static double nowNanos() {
    return (double)std::chrono::duration_cast<std::chrono::nanoseconds>(
               std::chrono::steady_clock::now().time_since_epoch()).count();
}

// corpus scanning

struct CorpusEntry {
    DedupKey    key;     // content identity (msg_type + MT～VN digest)
    std::string nmea;    // re-composed, checksummed sentence
};

struct Corpus {
    std::vector<CorpusEntry> entries;   // one per observed (satellite, content)
    std::vector<CorpusEntry> distinct;  // first occurrence of each content
    size_t tokens = 0;            // raw $QZQSM tokens in the file
};

static inline bool isHex(char c) {
    return (c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f');
}

static inline uint8_t hexVal(char c) {
    return (uint8_t)(c <= '9' ? c - '0' : (c | 0x20) - 'a' + 10);
}

// Extracts $QZQSM sentences from any text file (JSON, CSV, syslog dump).
// msg_type = bits 8..13; identity = CRC-24Q over bits 8..219 (MT～VN, 手順③).
static void scanFile(const char* path, Corpus& out) {
    FILE* fp = fopen(path, "rb");
    if (!fp) { fprintf(stderr, "bench: cannot open %s\n", path); exit(2); }
    std::string buf;
    char chunk[65536];
    size_t n;
    while ((n = fread(chunk, 1, sizeof(chunk), fp)) > 0) buf.append(chunk, n);
    fclose(fp);

    std::set<std::string> seen_content;
    size_t i = 0;
    while ((i = buf.find("$QZQSM,", i)) != std::string::npos) {
        size_t p = i + 7;
        unsigned svid = 0;
        bool digits = false;
        while (p < buf.size() && buf[p] >= '0' && buf[p] <= '9') {
            svid = svid * 10 + (unsigned)(buf[p] - '0');
            ++p;
            digits = true;
        }
        if (!digits || svid > 255 || p >= buf.size() || buf[p] != ',') { i += 7; continue; }
        ++p;
        const size_t h0 = p;
        while (p < buf.size() && isHex(buf[p])) ++p;
        if (p - h0 < 63) { i += 7; continue; }

        CorpusEntry e{};
        e.key.msg_type = (uint8_t)((hexVal(buf[h0 + 2]) << 2) | (hexVal(buf[h0 + 3]) >> 2));
        // 手順③ の照合対象 MT～VN = フレーム bit 8..219 = hex 2..55 文字目（26.5 バイト）。
        // Parser::handleFrame と同じ digest を作る（プリアンブルも Reserved も含まない）。
        uint8_t fbuf[32] = {};
        for (int i = 0; i < 31; ++i) {
            fbuf[i] = (uint8_t)((hexVal(buf[h0 + i * 2]) << 4) | hexVal(buf[h0 + i * 2 + 1]));
        }
        fbuf[31] = (uint8_t)(hexVal(buf[h0 + 62]) << 4);
        e.key.identity = crc24qRef(fbuf + 1, 212);
        ++out.tokens;

        char frame[96];
        const int len = snprintf(frame, sizeof(frame), "$QZQSM,%u,%.*s", svid, 63, buf.data() + h0);
        uint8_t xsum = 0;
        for (int k = 1; k < len; ++k) xsum ^= (uint8_t)frame[k];
        char tail[8];
        snprintf(tail, sizeof(tail), "*%02X\r\n", xsum);
        e.nmea.assign(frame, (size_t)len);
        e.nmea += tail;

        out.entries.push_back(e);
        if (seen_content.insert(std::string(buf, h0, 63)).second) out.distinct.push_back(e);
        i = p;
    }
}

// stream model

struct Op {
    DedupKey key;
    uint64_t now_ms;   // receiver clock at reception (手順④' timer basis)
};

// One scripted stretch of traffic with the spec's validity window applied to
// the informations that appear in it.
struct Phase {
    const char* name = "";
    uint64_t    window_ms = 300000;  // 5 min — 緊急地震速報 (原PDF p.25-27)
    std::vector<Op> ops;
    size_t      scored = 0;
    size_t      correct = 0;
    uint64_t    cycles = 0;
    bool        timing_only = false;
};

static inline uint64_t contentOf(const DedupKey& k) {
    return ((uint64_t)k.msg_type << 24) | k.identity;
}

static uint32_t lcg(uint32_t& s) {
    s = s * 1664525u + 1013904223u;
    return s;
}

// Single call site facing the filter
static bool filterIsDuplicate(DedupFilter& f, const Phase& p, const Op& op) {
    return f.isDuplicate(op.key, op.now_ms, p.window_ms);
}

struct PhaseResult {
    size_t scored = 0, correct = 0;
    size_t dup_expected = 0, dup_correct = 0;   // class: same content already live
    size_t new_expected = 0, new_correct = 0;   // class: genuinely new information
};

static bool verbose = false;

static double medianOf(std::vector<double> v) {
    if (v.empty()) return 0.0;
    std::sort(v.begin(), v.end());
    return v[v.size() / 2];
}

// Scores the phase against the spec model: a decision is correct when it
// matches "same content already received within window_ms".
static PhaseResult verifyPhase(const Phase& p) {
    PhaseResult r;
    DedupFilter f;
    std::vector<uint64_t> seen_content, seen_at;
    for (const Op& op : p.ops) {
        const uint64_t c = contentOf(op.key);
        bool expected = false;
        for (size_t i = 0; i < seen_content.size(); ++i) {
            if (seen_content[i] != c) continue;
            if ((uint64_t)op.now_ms - seen_at[i] <= p.window_ms) { expected = true; break; }
        }
        ++r.scored;
        const bool actual = filterIsDuplicate(f, p, op);
        if (actual == expected) ++r.correct;
        if (expected) {
            ++r.dup_expected;
            if (actual) ++r.dup_correct;
        } else {
            ++r.new_expected;
            if (!actual) ++r.new_correct;
        }
        if (actual != expected && verbose) {
            fprintf(stderr, "# %s mismatch @%zu expected=%d actual=%d mt=%u crc=%06X now=%llu\n",
                    p.name, r.scored - 1, (int)expected, (int)actual,
                    op.key.msg_type, op.key.identity, (unsigned long long)op.now_ms);
        }
        seen_content.push_back(c);
        seen_at.push_back(op.now_ms);
    }
    return r;
}

// phase builders

static const uint32_t MS_SEC = 1000;
static const uint32_t W_5MIN = 5 * 60 * MS_SEC;         // EEW 発表時刻から5分
static const uint32_t W_24H  = 24 * 60 * 60 * MS_SEC;   // 津波 最大24時間

// P1 — one information relayed by three satellites, 4 s rebroadcast (原PDF p.23/24)
static Phase phaseMultiSat(const Corpus& c) {
    Phase p;
    p.name = "P1_multi_sv";
    p.window_ms = W_5MIN;
    p.scored = 1;
    const uint64_t start = 50'000'000;
    for (int rep = 0; rep < 75; ++rep) {
        for (size_t i = 0; i < 6 && i < c.distinct.size(); ++i) {
            for (uint8_t sv = 0; sv < 3; ++sv) {
                Op op;
                op.key = c.distinct[i].key;
                (void)sv;  // relay satellite: same content, different PRN
                op.now_ms = start + (uint64_t)rep * 4 * MS_SEC;
                p.ops.push_back(op);
            }
        }
    }
    return p;
}

// P2 — single satellite, 8 concurrent informations, 4 s rebroadcast
static Phase phaseRebroadcast(const Corpus& c) {
    Phase p;
    p.name = "P2_rebroadcast";
    p.window_ms = W_5MIN;
    p.scored = 1;
    const uint64_t start = 50'000'000;
    for (int rep = 0; rep < 75; ++rep) {
        for (size_t i = 0; i < 8 && i < c.distinct.size(); ++i) {
            Op op;
            op.key = c.distinct[i].key;
            op.now_ms = start + (uint64_t)rep * 4 * MS_SEC;
            p.ops.push_back(op);
        }
    }
    return p;
}

// P3 — in-window repeats are duplicates, post-window repeats are new
// (手順④' 一定時間受信しなかった情報は履歴から削除する).
// Window is EEW's 5 min (原PDF p.26); the clock starts at a realistic uptime.
static Phase phaseWindowExpiry(const Corpus& c) {
    Phase p;
    p.name = "P3_expiry";
    p.window_ms = W_5MIN;
    p.scored = 1;
    const uint64_t start = 50'000'000;                    // 13.9 h uptime
    for (int cycle = 0; cycle < 60; ++cycle) {            // 0..236 s: in window
        for (size_t i = 0; i < 4 && i < c.distinct.size(); ++i) {
            Op op;
            op.key = c.distinct[i].key;
            op.now_ms = start + (uint64_t)cycle * 4 * MS_SEC;
            p.ops.push_back(op);
        }
    }
    const uint64_t after = start + (60 * 4 + 600) * MS_SEC;  // +10 min silence
    for (int cycle = 0; cycle < 3; ++cycle) {              // fresh, then dup
        for (size_t i = 0; i < 4 && i < c.distinct.size(); ++i) {
            Op op;
            op.key = c.distinct[i].key;
            op.now_ms = after + (uint64_t)cycle * 4 * MS_SEC;
            p.ops.push_back(op);
        }
    }
    // Boundary: exactly one window after the first post-gap reception is still
    // inside it ("経過" means elapsed, so the boundary itself is not expired).
    for (size_t i = 0; i < 4 && i < c.distinct.size(); ++i) {
        Op op;
        op.key = c.distinct[i].key;
        op.now_ms = after + W_5MIN;
        p.ops.push_back(op);
    }
    return p;
}

// P4 — 16 informations, each relayed by a second satellite (capacity pressure)
static Phase phaseCapacity(const Corpus& c) {
    Phase p;
    p.name = "P4_two_sv";
    p.window_ms = W_24H;
    p.scored = 1;
    const uint64_t start = 50'000'000;
    for (size_t i = 0; i < 16 && i < c.distinct.size(); ++i) {
        Op op;
        op.key = c.distinct[i].key;
        op.now_ms = start + (uint64_t)i * MS_SEC;
        p.ops.push_back(op);
    }
    for (size_t i = 0; i < 16 && i < c.distinct.size(); ++i) {
        Op op;
        op.key = c.distinct[i].key;
        // relayed by another PRN: identical content
        op.now_ms = start + 60 * MS_SEC + (uint64_t)i * MS_SEC;
        p.ops.push_back(op);
    }
    return p;
}

// P6 — capacity reclaimed: an information that stopped being received must not
// pin a slot forever. A window is enough silence to retire the old set
// (手順④'), so the new set must be tracked with no false duplicate.
static Phase phaseReclaim(const Corpus& c) {
    Phase p;
    p.name = "P6_reclaim";
    p.window_ms = W_24H;
    p.scored = 1;
    const uint64_t base = 50'000'000;
    const size_t n = std::min<size_t>(c.distinct.size(), 40);
    for (int cycle = 0; cycle < 3; ++cycle) {
        for (size_t i = 0; i < n; ++i) {
            Op op;
            op.key = c.distinct[i].key;
            op.now_ms = base + (uint64_t)cycle * 4 * MS_SEC;
            p.ops.push_back(op);
        }
    }
    // Silence longer than the validity window, then a completely different set.
    const uint64_t after = base + (uint64_t)n * 4 * MS_SEC + W_24H + MS_SEC;
    for (int cycle = 0; cycle < 3; ++cycle) {
        for (size_t i = n; i < n + 40 && i < c.distinct.size(); ++i) {
            Op op;
            op.key = c.distinct[i].key;
            op.now_ms = after + (uint64_t)cycle * 4 * MS_SEC;
            p.ops.push_back(op);
        }
    }
    return p;
}

// P5 — payload-distinct churn, no repeats: throughput only
static Phase phaseChurn(const Corpus& c) {
    Phase p;
    p.name = "P5_churn";
    p.timing_only = true;
    uint32_t seed = 0x5EED1234u;
    std::vector<Op> order;
    for (const CorpusEntry& e : c.distinct) {
        Op op;
        op.key = e.key;
        op.now_ms = 50'000'000;
        order.push_back(op);
    }
    for (size_t i = order.size(); i > 1; --i) std::swap(order[i - 1], order[lcg(seed) % i]);
    for (int rep = 0; rep < 20; ++rep) p.ops.insert(p.ops.end(), order.begin(), order.end());
    return p;
}

// spec identity for aggregated Nankai events

// The completed aggregation is one information, so its identity must not depend
// on which page completed the set: the page that finishes last is an artefact of
// arrival order. Measured behaviourally, through the Parser:
//   1) event A (27 pages, file order)      → reported once
//   2) event B (same pages, other event)   → reported (and evicts A's buffer,
//      since AZARAC_NANKAI_BUFFERS is 1)
//   3) event A again, reversed page order  → NOT reported
// Step 3 is the discriminator: identified by the completing frame's CRC, A
// completes on a different page and is reported a second time.
// 1 = stable, 0 = unstable, -1 = fixture unusable.
static int nankaiKeyStable(const std::vector<std::string>& pages, uint32_t& key_used) {
    key_used = 0;
    if (pages.size() < 2) return -1;

    // Rebuild each sentence: patch the report-minute field so the same page set
    // describes a different event, then re-checksum the frame.
    auto rewriteAsOtherEvent = [](const std::string& in, std::string& out) {
        const size_t p = in.find(',', 7);
        if (p == std::string::npos) return false;
        const unsigned svid = (unsigned)strtoul(in.c_str() + 7, nullptr, 10);
        const char* hex = in.c_str() + p + 1;
        uint8_t bits[32] = {};
        for (int i = 0; i < 31; ++i) {
            bits[i] = (uint8_t)((hexVal(hex[i * 2]) << 4) | hexVal(hex[i * 2 + 1]));
        }
        bits[31] = (uint8_t)(hexVal(hex[62]) << 4);
        setBits(bits, 35, 6, (TestDecoder::extractBits(bits, 35, 6) + 1) & 0x3F);  // report minute
        setBits(bits, 226, 24, crc24qRef(bits, 226));
        out = makeNmeaQzqsm((uint8_t)svid, bits);
        return true;
    };

    std::vector<std::string> other;
    other.reserve(pages.size());
    for (const std::string& s : pages) {
        std::string t;
        if (!rewriteAsOtherEvent(s, t)) return -1;
        other.push_back(t);
    }

    Parser p;
    azaraC::Message msg;
    auto feed = [&](const std::string& s) {
        bool emitted = false;
        for (size_t j = 0; j < s.size(); ++j) {
            if (p.feed((uint8_t)s[j], msg, 0)) emitted = true;
        }
        return emitted;
    };
    auto feedAll = [&](const std::vector<std::string>& set, bool reversed) {
        bool emitted = false;
        for (size_t i = 0; i < set.size(); ++i) {
            if (feed(set[reversed ? (set.size() - 1 - i) : i])) emitted = true;
        }
        return emitted;
    };

    const bool a_first = feedAll(pages, false);
    const bool b_own  = feedAll(other, false);
    const bool a_again = feedAll(pages, true);

    // Bitmask 1|2|4 of what was reported, so a failure names which step broke.
    key_used = (uint32_t)((a_first ? 1u : 0u) | (b_own ? 2u : 0u) | (a_again ? 4u : 0u));
    return (a_first && b_own && !a_again) ? 1 : 0;
}

// spec identity: MT～VN, not the whole 250-bit frame

// 手順③ の照合対象は MT～VN（フレーム bit 8..219 = 212 bit）で、プリアンブル（bit 0..7）も
// Reserved（bit 220..225）も含まない。どちらも放送で巡回する（プリアンブルは A→B→C、
// Reserved は 16 値）ので、250 ビット全体でも 218 bit でも 1 情報が分裂する。fixture の
// 1 文について両方を回し、通知がちょうど 1 回であることを見る。
// 1 = stable, 0 = unstable, -1 = fixture unusable（1 回も通知されない = デコード不能）。
static int preambleKeyStable(const std::string& sentence) {
    const size_t p = sentence.find(',', 7);
    if (p == std::string::npos) return -1;
    const unsigned svid = (unsigned)strtoul(sentence.c_str() + 7, nullptr, 10);
    const char* hex = sentence.c_str() + p + 1;
    if (strlen(hex) < 63) return -1;

    uint8_t bits[32] = {};
    for (int i = 0; i < 31; ++i) {
        bits[i] = (uint8_t)((hexVal(hex[i * 2]) << 4) | hexVal(hex[i * 2 + 1]));
    }
    bits[31] = (uint8_t)(hexVal(hex[62]) << 4);

    static const uint8_t kPreambles[3]  = {0x53, 0x9A, 0xC6};   // A/B/C 巡回
    static const uint8_t kReserved[3]   = {0, 5, 15};           // Reserved は 16 値巡回
    Parser p2;
    azaraC::Message msg;
    int notified = 0;
    for (uint8_t preamble : kPreambles) {
        for (uint8_t res : kReserved) {
            setBits(bits, 0, 8, preamble);
            setBits(bits, 220, 6, res);
            setBits(bits, 226, 24, crc24qRef(bits, 226));
            const std::string s = makeNmeaQzqsm((uint8_t)svid, bits);
            for (size_t j = 0; j < s.size(); ++j) {
                if (p2.feed((uint8_t)s[j], msg, 0)) ++notified;
            }
        }
    }
    if (notified == 0) return -1;                 // 1 通もデコードできない = fixture 不能
    return (notified == 1) ? 1 : 0;               // 2 回以上 = 鍵が分裂
}

// main

// One pass over the given phases, in nanoseconds (used to size the timing loop).
static double nanosPerPass(Phase** phases, size_t count, size_t ops) {
    const double t = nowNanos();
    for (size_t i = 0; i < count; ++i) {
        DedupFilter f;
        for (const Op& op : phases[i]->ops) filterIsDuplicate(f, *phases[i], op);
    }
    const double dt = nowNanos() - t;
    return ops ? dt / (double)ops : 1.0;
}

int main() {
    printf("METRIC CRASH_GROUP=-1\n");   // re-emitted as 0 once the run completes
    verbose = getenv("AZARAC_BENCH_VERBOSE") != nullptr;

    Corpus dcr, dcx, nankai;
    scanFile("test/data/dcr_vectors.json", dcr);
    scanFile("test/data/dcx_vectors.json", dcx);
    scanFile("test/data/nankai_vectors.json", nankai);
    if (dcr.distinct.empty() || dcx.distinct.empty()) {
        fprintf(stderr, "bench: corpus is empty\n");
        return 2;
    }

    Corpus corpus;
    corpus.entries = dcr.entries;
    corpus.entries.insert(corpus.entries.end(), dcx.entries.begin(), dcx.entries.end());
    {
        std::set<uint64_t> uniq;
        for (const CorpusEntry& e : corpus.entries) {
            if (uniq.insert(contentOf(e.key)).second) corpus.distinct.push_back(e);
        }
    }
    if (corpus.distinct.size() < 16) {
        fprintf(stderr, "bench: corpus too small (%zu distinct)\n", corpus.distinct.size());
        return 2;
    }

    Phase p1 = phaseMultiSat(corpus);
    Phase p2 = phaseRebroadcast(corpus);
    Phase p3 = phaseWindowExpiry(corpus);
    Phase p4 = phaseCapacity(corpus);
    Phase p6 = phaseReclaim(corpus);
    Phase p5 = phaseChurn(corpus);
    Phase* all[6] = {&p1, &p2, &p3, &p4, &p6, &p5};
    Phase* scored[5] = {&p1, &p2, &p3, &p4, &p6};

    size_t total_scored = 0, total_correct = 0;
    size_t dup_expected = 0, dup_correct = 0, new_expected = 0, new_correct = 0;
    double phase_acc[5];
    for (int i = 0; i < 5; ++i) {
        const PhaseResult r = verifyPhase(*scored[i]);
        total_scored    += r.scored;
        total_correct   += r.correct;
        dup_expected    += r.dup_expected;
        dup_correct     += r.dup_correct;
        new_expected    += r.new_expected;
        new_correct     += r.new_correct;
        phase_acc[i] = r.scored ? (double)r.correct / (double)r.scored : 0.0;
    }
    const double new_recall = new_expected ? (double)new_correct / (double)new_expected : 0.0;
    const double dup_suppress = dup_expected ? (double)dup_correct / (double)dup_expected : 0.0;

    // ── Timing: averaged streaming (steady_clock). The TSC of a hardware
    // counter is ~50 % noisy here on short runs; a 200-pass average of the
    // same workload repeats to ~3 %.
    constexpr double TARGET_SECONDS = 0.25;
    size_t all_ops = 0;
    for (Phase* p : all) all_ops += p->ops.size();
    int passes = (int)(TARGET_SECONDS * 1e9 / (nanosPerPass(all, 6, all_ops) * (double)all_ops));
    if (passes < 5) passes = 5;
    if (passes > 20000) passes = 20000;

    std::vector<double> samples;
    samples.reserve(9);
    double scored_nanos = 0, churn_nanos = 0;
    for (int s = 0; s < 9; ++s) {
        double t = nowNanos();
        for (int rep = 0; rep < passes; ++rep) {
            for (Phase* p : scored) { DedupFilter f; for (const Op& op : p->ops) filterIsDuplicate(f, *p, op); }
        }
        double dt = nowNanos() - t;
        samples.push_back(dt / (double)(total_scored * passes));
        t = nowNanos();
        for (int rep = 0; rep < passes; ++rep) {
            DedupFilter f;
            for (const Op& op : p5.ops) filterIsDuplicate(f, p5, op);
        }
        churn_nanos += (nowNanos() - t) / (double)(p5.ops.size() * passes);
    }
    const double nanos_per_op = medianOf(samples);
    churn_nanos /= 9.0;   // averaged: churn stream is long enough to be stable

    // Largest live set answered with zero mistakes (capacity headroom).
    int capacity = 0;
    {
        const size_t maxK = std::min<size_t>(corpus.distinct.size(), 128);
        for (size_t K = 1; K <= maxK; ++K) {
            Phase probe;
            probe.name = "capacity";
            probe.window_ms = W_24H;
            for (int round = 0; round < 4; ++round) {
                for (size_t i = 0; i < K; ++i) {
                    Op op;
                    op.key = corpus.distinct[i].key;
                    op.now_ms = 50'000'000 + (uint64_t)i * MS_SEC;
                    probe.ops.push_back(op);
                }
            }
            const PhaseResult r = verifyPhase(probe);
            if (r.correct != r.scored) break;
            capacity = (int)K;
        }
    }

    std::vector<std::string> nk_pages;
    nk_pages.reserve(nankai.distinct.size());
    for (const CorpusEntry& e : nankai.distinct) nk_pages.push_back(e.nmea);
    // nankai_vectors.json holds exactly one event: the real 27-page 南海トラフ message.
    // A different fixture size would silently measure something else.
    const bool nk_ok = (nk_pages.size() == 27);
    uint32_t nk_steps = 0;
    const int nankai_stable = nk_ok ? nankaiKeyStable(nk_pages, nk_steps) : -1;

    // Same shape, MT=43 only: one EEW sentence rebroadcast with each of the three
    // cycling preambles must be announced exactly once.
    int preamble_stable = -1;
    for (const CorpusEntry& e : dcr.distinct) {
        if (e.key.msg_type != 43) continue;
        preamble_stable = preambleKeyStable(e.nmea);
        break;
    }

    // End-to-end sanity: duplicates are still suppressed through Parser.
    double parser_nanos = 0;
    size_t parser_out = 0, parser_sent = 0;
    {
        Parser p;
        azaraC::Message msg;
        const double s0 = nowNanos();
        for (int rep = 0; rep < 20; ++rep) {
            for (const CorpusEntry& e : corpus.entries) {
                ++parser_sent;
                for (size_t j = 0; j < e.nmea.size(); ++j) {
                    if (p.feed((uint8_t)e.nmea[j], msg, 0)) ++parser_out;
                }
            }
        }
        parser_nanos = (nowNanos() - s0) / (double)parser_sent;
    }

    printf("METRIC CRASH_GROUP=0\n");
    printf("METRIC NANOS_PER_OP=%.6f\n", nanos_per_op);
    printf("METRIC ACCURACY=%.4f\n", total_scored ? (double)total_correct / (double)total_scored : 0.0);
    printf("METRIC NEW_RECALL=%.4f\n", new_recall);
    printf("METRIC DUP_SUPPRESS=%.4f\n", dup_suppress);
    printf("METRIC NEW_EXPECTED=%zu\n", new_expected);
    printf("METRIC NEW_CORRECT=%zu\n", new_correct);
    printf("METRIC DUP_EXPECTED=%zu\n", dup_expected);
    printf("METRIC DUP_CORRECT=%zu\n", dup_correct);
    printf("METRIC ACCURACY_P1_MULTI_SV=%.4f\n", phase_acc[0]);
    printf("METRIC ACCURACY_P2_REBROADCAST=%.4f\n", phase_acc[1]);
    printf("METRIC ACCURACY_P3_EXPIRY=%.4f\n", phase_acc[2]);
    printf("METRIC ACCURACY_P4_TWO_SV=%.4f\n", phase_acc[3]);
    printf("METRIC ACCURACY_P6_RECLAIM=%.4f\n", phase_acc[4]);
    printf("METRIC DECISIONS_SCORED=%zu\n", total_scored);
    printf("METRIC DECISIONS_CORRECT=%zu\n", total_correct);
    printf("METRIC CHURN_NANOS_PER_OP=%.6f\n", churn_nanos);
    printf("METRIC TIMING_PASSES=%d\n", passes);
    printf("METRIC CAPACITY_DISTINCT=%d\n", capacity);
    printf("METRIC SRAM_DEDUP_BYTES=%zu\n", sizeof(DedupFilter));
    printf("METRIC SRAM_PARSER_BYTES=%zu\n", sizeof(Parser));
    printf("METRIC NANKAI_KEY_STABLE=%d\n", nankai_stable);
    printf("METRIC PREAMBLE_KEY_STABLE=%d\n", preamble_stable);
    printf("METRIC NANKAI_STEPS=%u\n", nk_steps);
    printf("METRIC PARSER_NANOS_PER_MSG=%.1f\n", parser_nanos);
    printf("METRIC PARSER_SENT=%zu\n", parser_sent);
    printf("METRIC PARSER_OUTPUTS=%zu\n", parser_out);
    printf("METRIC CORPUS_DISTINCT=%zu\n", corpus.distinct.size());
    printf("METRIC CORPUS_ENTRIES=%zu\n", corpus.entries.size());
    return 0;
}
