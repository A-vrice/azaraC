#include "Dedup.h"

namespace azaraC {
namespace internal {

// 詰めた内容からセット番号を決める: DEDUP_SETS は 2 の冪なので、CRC を自分自身へ fold した後の下位 log2(DEDUP_SETS) bit が index になる。
// どちらのシフトも 24 未満に収まる（DEDUP_SETS/2 だけのシフトは DEDUP_SETS >= 64 で未定義だった）。
//
// ponytail: `& 0xFFFFFF` は SETS ≤ 2^12（SLOTS ≤ 32768）では no-op。
// fold は各ビットを最大 12 しか下げないので、低 log2(SETS) bit しか採らない構成では元の bit 24 以上（It 合成鍵 bits 24-25、msg_type 実鍵 bits 24-29）が index に届かず、セット選択に効かない。
// SETS ≥ 2^13（SLOTS ≥ 65536）で届き始め、このマスクが効く/効かないを決める。
// 実測: 20 万件の乱数で SETS 2^4..2^12 はマスク有無で index 完全一致、2^14 で差異。
static inline uint16_t setIndexOf(uint32_t content) {
    uint32_t h = content & 0xFFFFFFu;
    h ^= h >> 8;
    h ^= h >> 4;
    return (uint16_t)(h & (DEDUP_SETS - 1));
}

bool DedupFilter::isDuplicate(const DedupKey& key, uint32_t now_ms, uint32_t window_ms) {
    const uint32_t content = key.packed() | VALID;
    Entry* set = _ring[setIndexOf(content)];

    Entry* free_slot = nullptr;
    Entry* oldest = &set[0];
    for (uint8_t w = 0; w < DEDUP_WAYS; ++w) {
        Entry& e = set[w];
        if (!(e.content & VALID)) {
            if (!free_slot) free_slot = &e;
            continue;
        }
        // 経過 = now - last_seen を符号なしで取る: millis() の 49.7 日巻き戻りをまたいでも正しい。
        // last_seen 同士の比較は 2 件が 24.8 日以上離れると巻き戻り、生きている方を追い出してしまう。
        if ((uint32_t)(now_ms - e.last_seen_ms) > (uint32_t)(now_ms - oldest->last_seen_ms)) oldest = &e;
        if (e.content != content) continue;
        if ((uint32_t)(now_ms - e.last_seen_ms) <= window_ms) {
            e.last_seen_ms = now_ms;   // 手順④': 再受信で有効時間を延長
            return true;
        }
        e.last_seen_ms = now_ms;
        return false;
    }

    // 未追跡: 空き way があれば使い、無ければ最終受信が最も古いものを追い出す（一様リングだと最新の情報を落として、生きている警報を再通知し古い情報を残すことになる）。
    Entry& e = free_slot ? *free_slot : *oldest;
    e.content = content;
    e.last_seen_ms = now_ms;
    return false;
}

void DedupFilter::reset() {
    for (uint16_t s = 0; s < DEDUP_SETS; ++s) {
        for (uint8_t w = 0; w < DEDUP_WAYS; ++w) {
            _ring[s][w].content = 0;      // no VALID bit → unused
            _ring[s][w].last_seen_ms = 0;
        }
    }
}

} // namespace internal
} // namespace azaraC
