// test/tools/dedup_realday.cpp
// 実日の .l1s アーカイブに対する重複判定の再現計測。
//
//   make -C test dedup-realday
//   make -C test dedup-realday CXXFLAGS_EXTRA="-DAZARAC_DEDUP_SLOTS=128" -B （CXXFLAGS_EXTRA は依存関係に載らないので、容量を変えて測った後は必ず
//     `make -C test clean` する。残った .o が次の既定ビルドに混ざる。）
//
// 計測するもの（すべて METRIC 行）:
//   REALDAY_FRAMES       — 採用したフレーム数（Decoder が受理したもの）
//   REALDAY_DISTINCT     — 同一性（MT～VN の digest）の相異なる個数
//   REALDAY_PEAK_LIVE_*  — 生存ピーク（各情報を自身の窓で失効させる）
//   REALDAY_EXPECTED_DUP — 一意な履歴（容量無制限）で重複と判定される回数
//   REALDAY_FALSE_RE     — 窓内で生存している情報を新規と誤判定した回数
//   REALDAY_MISSED       — 生きていない情報を重複と誤判定した回数
//   REALDAY_UNALIGNED    — 1 秒境界（bit 40 + n*288）に載らなかった CRC 有効フレーム数（0 でなければ入力の枠組みが想定と違う = 数字を信用しない）
//
// 窓・ハッシュ・カテゴリ判定はすべてライブラリ本体と同じものを使う:
// Decoder::decode で電文を復号し、internal::dedupWindowMs(Message) で窓を取り、
// internal::DedupFilter で判定する。表やカテゴリ判定をここで写すと、計測対象が本体から静かにずれる（payload を渡さない窓は津波・気象・洪水・海上を 3〜10 時間と誤って短く見積もる、など）。

#define ARDUINO 0
#include "azaraC.h"
#include "decoder/Decoder.h"
#include "internal/Dedup.h"
#include "internal/DedupWindow.h"

#include <cstdio>
#include <cstring>
#include <vector>

using azaraC::internal::Decoder;
using azaraC::internal::DedupFilter;
using azaraC::internal::DedupKey;
using azaraC::internal::Frame;

namespace {

// 同一性は {msg_type, MT～VN digest}（internal::DedupKey と同じ）。MT=44 を混ぜても衝突しないよう、計測側でも両方を鍵にする。
struct Identity {
    uint8_t  mt;
    uint32_t digest;
};

struct FrameRef {
    unsigned slot;       // 各秒のフレーム先頭 = bit 40、1 秒 = 288 bit
    Identity id;
    uint32_t window_ms;
    uint8_t  category;   // disaster_category (MT=44 はカテゴリ番号なし → 0)
};

// .l1s は 36 B/秒（288 bit）、フレーム（250 bit）は各秒の bit 40 から始まる。
// ファイル全体を走査し、Decoder が受理するフレームだけを採る（固定レコード長にもカテゴリのマクロ構成にも依存しない — 無効カテゴリは decode() が false を返す）。
//
// 南海トラフ（dc=4）は除く: Parser はページを集約し事象トークンで判定するので、電文単位の鍵とは軸が違う。集約の同一性は test/bench の NANKAI_KEY_STABLE が見る。
// unaligned には「1 秒境界（bit 40 + n*288）に載っていない CRC 有効フレーム」の数を返す。
// slot は受信秒なので、境界に無いフレームに秒を割り当てると隣の秒へ化ける。このアーカイブでは 0 だが、別の形式の .l1s を渡されたときに黙って壊れた数字を出さないよう数えて除外する（0 でなければ REALDAY_UNALIGNED が 0 以外になる）。
std::vector<FrameRef> extractFrames(const std::vector<uint8_t>& data, Decoder& decoder,
                                    size_t& unaligned) {
    std::vector<FrameRef> out;
    unaligned = 0;
    const size_t total_bits = data.size() * 8;
    auto bitAt = [&](size_t p) -> uint32_t {
        return (uint32_t)((data[p >> 3] >> (7 - (p & 7))) & 1u);
    };
    auto get = [&](size_t off, uint8_t len) -> uint32_t {
        uint32_t v = 0;
        for (uint8_t i = 0; i < len; ++i) v = (v << 1) | bitAt(off + i);
        return v;
    };

    // 走査上限は 256 bit（Frame::bits 全体）。k<32 のコピーが off+0..255 を読むため、 250 で切ると末尾 5 bit がバッファ外に出る（このアーカイブは 36 B/秒 + 端数 1 B で実際に到達する）。
    for (size_t off = 40; off + 256 <= total_bits; ++off) {
        const uint8_t preamble = (uint8_t)get(off, 8);
        if (preamble != 0x53 && preamble != 0x9A && preamble != 0xC6) continue;
        Frame frame;
        frame.svid = 0;
        for (uint8_t k = 0; k < 32; ++k) frame.bits[k] = (uint8_t)get(off + k * 8u, 8);

        azaraC::Message msg;
        if (!decoder.decode(frame, msg, 0)) continue;
        const azaraC::Mt43Data* d = msg.getMt43();
        if (d && d->disaster_category == 4) continue;   // 南海トラフは集約経路

        FrameRef f;
        f.slot = (unsigned)((off - 40) / 288);
        f.id.mt = msg.msg_type;
        f.id.digest = Decoder::crc24q(frame.bits + 1, 212);   // MT～VN = bit 8..219
        f.window_ms = azaraC::internal::dedupWindowMs(msg);
        f.category = d ? d->disaster_category : 0;
        if ((off - 40) % 288 != 0) { ++unaligned; continue; }  // 受信秒が定まらない
        out.push_back(f);
    }
    return out;
}

inline bool sameId(const Identity& a, const Identity& b) {
    return a.mt == b.mt && a.digest == b.digest;
}

// 生存ピーク: 各情報を自身の窓で失効させ、再受信で最終受信時刻を更新する。
// 計算量は O(n·live)。1 日分のオフライン計測専用で、長期の実測に使うなら時刻順の優先度付きキューで失効させる。
size_t peakLive(const std::vector<FrameRef>& frames, bool perCategoryWindow) {
    struct Live { Identity id; uint32_t last_ms; uint32_t window_ms; };
    std::vector<Live> live;
    size_t peak = 0;
    for (const FrameRef& f : frames) {
        const uint32_t now = f.slot * 1000u;
        const uint32_t win = perCategoryWindow ? f.window_ms : AZARAC_DEDUP_WINDOW_MS;
        bool found = false;
        for (Live& l : live) {
            if (!sameId(l.id, f.id)) continue;
            l.last_ms = now;
            l.window_ms = win;
            found = true;
            break;
        }
        if (!found) live.push_back(Live{f.id, now, win});
        size_t alive = 0;
        for (const Live& l : live) {
            if ((uint32_t)(now - l.last_ms) <= l.window_ms) ++alive;
        }
        if (alive > peak) peak = alive;
    }
    return peak;
}

// カテゴリごとの生存ピーク（その時点で窓内に生きている同一性の数）。容量が足りるかを判断する材料。計算量は O(n·live) のオフライン計測専用。
size_t peakLivePerCategory(const std::vector<FrameRef>& frames, uint8_t want_category) {
    struct Live { Identity id; uint32_t last_ms; uint32_t window_ms; };
    std::vector<Live> live;
    size_t peak = 0;
    for (const FrameRef& f : frames) {
        if (f.category != want_category) continue;
        const uint32_t now = f.slot * 1000u;
        bool found = false;
        for (Live& l : live) {
            if (!sameId(l.id, f.id)) continue;
            l.last_ms = now; l.window_ms = f.window_ms; found = true; break;
        }
        if (!found) live.push_back(Live{f.id, now, f.window_ms});
        size_t alive = 0;
        for (const Live& l : live) if ((uint32_t)(now - l.last_ms) <= l.window_ms) ++alive;
        if (alive > peak) peak = alive;
    }
    return peak;
}


size_t countDistinct(const std::vector<FrameRef>& frames) {
    std::vector<Identity> seen;
    for (const FrameRef& f : frames) {
        bool dup = false;
        for (const Identity& s : seen) if (sameId(s, f.id)) { dup = true; break; }
        if (!dup) seen.push_back(f.id);
    }
    return seen.size();
}

} // namespace

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "usage: dedup_realday <file.l1s>\n");
        return 2;
    }
    FILE* fp = fopen(argv[1], "rb");
    if (!fp) {
        fprintf(stderr, "dedup_realday: cannot open %s\n", argv[1]);
        return 2;
    }
    std::vector<uint8_t> data;
    uint8_t chunk[65536];
    size_t n;
    while ((n = fread(chunk, 1, sizeof(chunk), fp)) > 0) data.insert(data.end(), chunk, chunk + n);
    fclose(fp);

    Decoder decoder;
    size_t unaligned = 0;
    const std::vector<FrameRef> frames = extractFrames(data, decoder, unaligned);

    // 一意な履歴（容量無制限）を正解として、実装の判定と比べる。
    struct Seen { Identity id; uint32_t last_ms; };
    std::vector<Seen> truth;
    DedupFilter filter;
    size_t expected_dup = 0, false_re = 0, missed = 0, suppressed = 0;

    // カテゴリ別の内訳。expected = 窓内の再受信なので抑制が正解。MISSED は「窓外＝新規のはずなのに抑制した」＝通知が落ちる側（危険側）なので、どの災害でどれだけ落ちるかをカテゴリごとに数える。判定はメインループと同一。
    struct CatStat {
        size_t frames = 0, distinct = 0, false_re = 0, missed = 0;
        std::vector<Identity> seen_ids;
    };
    CatStat cat[16];   // index = disaster_category (MT=43: 1..14 / MT=44: 0)

    for (const FrameRef& f : frames) {
        const uint32_t now = f.slot * 1000u;

        bool expected = false;
        bool known = false;
        for (Seen& s : truth) {
            if (!sameId(s.id, f.id)) continue;
            known = true;
            expected = ((uint32_t)(now - s.last_ms) <= f.window_ms);
            s.last_ms = now;
            break;
        }
        if (!known) truth.push_back(Seen{f.id, now});
        if (expected) ++expected_dup;

        const DedupKey key{f.id.mt, f.id.digest};
        const bool actual = filter.isDuplicate(key, now, f.window_ms);
        if (actual) ++suppressed;

        CatStat& c = cat[f.category < 16 ? f.category : 0];
        ++c.frames;
        if (expected && !actual) { ++false_re; ++c.false_re; }   // 誤再通知（落ちない側）
        if (!expected && actual) { ++missed;   ++c.missed; }     // 取りこぼし（落ちる側）

        bool is_new_id = true;
        for (const Identity& s : c.seen_ids) if (sameId(s, f.id)) { is_new_id = false; break; }
        if (is_new_id) { c.seen_ids.push_back(f.id); ++c.distinct; }
    }

    printf("METRIC REALDAY_FRAMES=%zu\n", frames.size());
    printf("METRIC REALDAY_DISTINCT=%zu\n", countDistinct(frames));
    printf("METRIC REALDAY_PEAK_LIVE_24H=%zu\n", peakLive(frames, false));
    printf("METRIC REALDAY_PEAK_LIVE_SPEC=%zu\n", peakLive(frames, true));
    printf("METRIC REALDAY_EXPECTED_DUP=%zu\n", expected_dup);
    printf("METRIC REALDAY_SUPPRESSED=%zu\n", suppressed);
    printf("METRIC REALDAY_FALSE_RE=%zu\n", false_re);
    printf("METRIC REALDAY_MISSED=%zu\n", missed);
    printf("METRIC REALDAY_UNALIGNED=%zu\n", unaligned);
    // カテゴリ別。MISSED/FRAMES が「その災害で通知が落ちた割合（1 通あたり）」。
    // 0 件のカテゴリはこの実データに出現しない（データ無しであって「安全」ではない）。
    for (int c = 0; c < 16; ++c) {
        if (cat[c].frames == 0) continue;
        printf("METRIC REALDAY_CAT%d_FRAMES=%zu\n",  c, cat[c].frames);
        printf("METRIC REALDAY_CAT%d_DISTINCT=%zu\n", c, cat[c].distinct);
        printf("METRIC REALDAY_CAT%d_PEAK_LIVE=%zu\n", c, peakLivePerCategory(frames, (uint8_t)c));
        printf("METRIC REALDAY_CAT%d_MISSED=%zu\n",   c, cat[c].missed);
        printf("METRIC REALDAY_CAT%d_FALSE_RE=%zu\n", c, cat[c].false_re);
    }
    printf("METRIC REALDAY_DEDUP_SLOTS=%d\n", AZARAC_DEDUP_SLOTS);
    printf("METRIC REALDAY_DEDUP_WAYS=%d\n", AZARAC_DEDUP_WAYS);
    return 0;
}
