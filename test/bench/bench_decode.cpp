// Parser::feed の 1 文あたりサイクルベンチ（フレーミング込み）。
//
// 入力は test/data/{dcr,dcx,nankai}_vectors.json の $QZQSM 文のみ（ネットワーク・時計入力なし）。
// report_unix は固定値（≥2000-01-01 なので日付解決経路も通す）。
//
// 測定: 同じ Parser に同じ文を 15 回流し rdtsc 差分の最小値を取り、同一グループ内の文ごとの中央値を METRIC DECODE_CYCLES_<GROUP> として出力する。
// 重複抑止は 2 回目以降に通知を抑えるがデコード自体は毎回走るので、測っているのはフレーミング＋デコード＋シリアライズ前処理。
//
// MT43_NANKAI だけは Parser を作り直すとページ集約が完了しないため、ページ列を 1 つの Parser に通し、集約が完了する文を測る（先行ページは毎回同じ Parser に投入し、時間外）。
//
// Harness contract: "METRIC <name>=<value>" を出力し成功時 exit 0（bench_dedup.cpp と同じ）。

#include "azaraC.h"

#include <algorithm>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <set>
#include <string>
#include <vector>

#if defined(__x86_64__) || defined(_M_X64) || defined(__i386__)
#  include <x86intrin.h>
#  define BENCH_HAS_RDTSC 1
#endif

using azaraC::Parser;

static inline uint64_t readCycles() {
#ifdef BENCH_HAS_RDTSC
    return __rdtsc();
#else
    return (uint64_t)std::chrono::duration_cast<std::chrono::nanoseconds>(
               std::chrono::steady_clock::now().time_since_epoch()).count();
#endif
}

// vectors JSON の "type" 名 → グループ名（METRIC の接尾辞）。
// 未知の型は MT のみ（ フレーム bit 8..13 から判定）に落とす。
static const char* groupOfType(const std::string& type, uint8_t mt) {
    if (mt == 44) return "MT44";
    static const struct { const char* needle, *name; } kMap[] = {
        {"EarthquakeEarlyWarning", "MT43_EEW"},
        {"SeismicIntensity",       "MT43_SEISMIC"},
        {"Hypocenter",             "MT43_HYPOCENTER"},
        {"Tsunami",                "MT43_TSUNAMI"},
        {"NankaiTroughEarthquake", "MT43_NANKAI"},
        {"Volcano",                "MT43_VOLCANO"},
        {"AshFall",                "MT43_ASHFALL"},
        {"Weather",                "MT43_WEATHER"},
        {"Flood",                  "MT43_FLOOD"},
    };
    for (const auto& m : kMap)
        if (type.find(m.needle) != std::string::npos) return m.name;
    return "MT43_OTHER";
}

struct Sentence {
    std::string nmea;
    const char* group;
};

// JSON テキストから $QZQSM 文を取り出す。
// "nmea" と "params.sentence" の両方に同じ文が入っているので、文全体で重複除去する。
// 型は各 "nmea" の直後の "type": "..." から取る（生成された JSON では nmea が必ず type の前に来る）。
static void scanFile(const char* path, std::vector<Sentence>& out) {
    FILE* fp = fopen(path, "rb");
    if (!fp) { fprintf(stderr, "bench: cannot open %s\n", path); exit(2); }
    std::string buf;
    char chunk[65536];
    size_t n;
    while ((n = fread(chunk, 1, sizeof(chunk), fp)) > 0) buf.append(chunk, n);
    fclose(fp);

    std::set<std::string> seen;
    size_t i = 0;
    while ((i = buf.find("$QZQSM,", i)) != std::string::npos) {
        size_t e = i;
        while (e < buf.size() && buf[e] != '"' && buf[e] != '\n' && buf[e] != '\r') ++e;
        if (e - i < 20 || buf[e - 3] != '*') { i += 7; continue; }
        std::string sentence = buf.substr(i, e - i);

        size_t tpos = buf.find("\"type\": \"", e);
        std::string type;
        if (tpos != std::string::npos) {
            const size_t t0 = tpos + 9;
            const size_t t1 = buf.find('"', t0);
            if (t1 != std::string::npos) type = buf.substr(t0, t1 - t0);
        }
        // MT はフレーム本体（hex 3..4 文字目 = byte1）から。nmea と sentence の重複は seen で落とす。
        const size_t h0 = sentence.find(',', 7);
        if (h0 == std::string::npos || h0 + 5 > sentence.size()) { i = e; continue; }
        auto hexVal = [](char c) -> int {
            if (c >= '0' && c <= '9') return c - '0';
            if (c >= 'A' && c <= 'F') return c - 'A' + 10;
            if (c >= 'a' && c <= 'f') return c - 'a' + 10;
            return -1;
        };
        const int b1 = (hexVal(sentence[h0 + 3]) << 4) | hexVal(sentence[h0 + 4]);
        if (b1 < 0) { i = e; continue; }
        const uint8_t mt = (uint8_t)((b1 >> 2) & 0x3Fu);

        if (seen.insert(sentence).second) out.push_back({sentence, groupOfType(type, mt)});
        i = e;
    }
}

static bool feedSentence(Parser& p, azaraC::Message& msg, const std::string& s) {
    bool emitted = false;
    for (size_t j = 0; j < s.size(); ++j) {
        if (p.feed((uint8_t)s[j], msg, 1750000000u)) emitted = true;
    }
    return emitted;
}

static double medianOf(std::vector<double> v) {
    std::sort(v.begin(), v.end());
    return v.empty() ? 0.0 : v[v.size() / 2];
}

int main() {
    printf("METRIC CRASH_GROUP=-1\n");

    std::vector<Sentence> sentences;
    scanFile("test/data/dcr_vectors.json", sentences);
    scanFile("test/data/dcx_vectors.json", sentences);
    scanFile("test/data/nankai_vectors.json", sentences);
    if (sentences.empty()) { fprintf(stderr, "bench: corpus is empty\n"); return 2; }

    std::map<std::string, std::vector<double>> per_group;
    std::map<std::string, size_t> group_outputs;
    size_t total_outputs = 0;

    std::vector<const Sentence*> per_sentence;
    std::vector<const Sentence*> nankai;
    for (const Sentence& s : sentences) {
        if (std::strcmp(s.group, "MT43_NANKAI") == 0) nankai.push_back(&s);
        else per_sentence.push_back(&s);
    }

    for (const Sentence* sp : per_sentence) {
        const Sentence& s = *sp;
        Parser p;
        azaraC::Message msg;
        if (feedSentence(p, msg, s.nmea)) { ++total_outputs; ++group_outputs[s.group]; }
        uint64_t best = ~0ull;
        for (int rep = 0; rep < 15; ++rep) {
            const uint64_t t0 = readCycles();
            feedSentence(p, msg, s.nmea);
            const uint64_t dt = readCycles() - t0;
            if (dt < best) best = dt;
        }
        per_group[s.group].push_back((double)best);
    }

    if (!nankai.empty()) {
        // 集約は Parser を作り直すと完了しない。ページ列を 1 つの Parser に通し、
        // 最初に完了した文の位置を求める（現 fixture は 1 イベント = 1 出力）。
        size_t complete_at = nankai.size();
        {
            Parser p;
            azaraC::Message msg;
            for (size_t i = 0; i < nankai.size(); ++i) {
                if (feedSentence(p, msg, nankai[i]->nmea)) {
                    ++total_outputs; ++group_outputs["MT43_NANKAI"];
                    if (complete_at == nankai.size()) complete_at = i;
                }
            }
        }
        if (complete_at < nankai.size()) {
            // 完了文を 1 文として測る。先行ページは毎回同じ Parser に投入する（時間外）。
            uint64_t best = ~0ull;
            for (int rep = 0; rep < 15; ++rep) {
                Parser p;
                azaraC::Message msg;
                for (size_t i = 0; i < complete_at; ++i) feedSentence(p, msg, nankai[i]->nmea);
                const uint64_t t0 = readCycles();
                feedSentence(p, msg, nankai[complete_at]->nmea);
                const uint64_t dt = readCycles() - t0;
                if (dt < best) best = dt;
            }
            per_group["MT43_NANKAI"].push_back((double)best);
        }
    }

    printf("METRIC CRASH_GROUP=0\n");
    printf("METRIC DECODE_OUTPUTS=%zu\n", total_outputs);
    printf("METRIC DECODE_GROUPS=%zu\n", per_group.size());
    printf("METRIC DECODE_SENTENCES=%zu\n", sentences.size());
    for (const auto& g : per_group) {
        printf("METRIC DECODE_CYCLES_%s=%.1f\n", g.first.c_str(), medianOf(g.second));
        printf("METRIC DECODE_SAMPLES_%s=%zu\n", g.first.c_str(), g.second.size());
        const size_t outs = group_outputs.count(g.first) ? group_outputs[g.first] : 0;
        printf("METRIC DECODE_EMITTED_%s=%zu\n", g.first.c_str(), outs);
    }
    return 0;
}
