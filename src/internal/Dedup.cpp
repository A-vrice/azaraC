#include "Dedup.h"

namespace azaraC {
namespace internal {

// 詰めた内容からセット番号を決める: DEDUP_SETS は 2 の冪なので、CRC を自分自身へ fold した後の下位 log2(DEDUP_SETS) bit が index。
// シフト量は 8 と 4 で、いずれも 24 未満に収まる（24 以上のシフトは未定義）。
// `& 0xFFFFFF` は SETS ≤ 2^12（SLOTS ≤ 32768）では no-op: fold は各ビットを最大 12 しか下げないので、下位 log2(SETS) bit は元の bit 24 以上（msg_type bits 24-29、synthetic 鍵の It bits 24-25）へ届かない。
// SETS ≥ 2^13（SLOTS ≥ 65536）で届き始め、マスクが効くかどうかが決まる。
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

    // 未追跡: 空き way があれば使い、無ければ最終受信が最も古いものを追い出す。
    // 一様リングだと最新の情報を落として、生きている警報を再通知し古い情報を残す。
    Entry& e = free_slot ? *free_slot : *oldest;
    e.content = content;
    e.last_seen_ms = now_ms;
    return false;
}

void DedupFilter::reset() {
    for (uint16_t s = 0; s < DEDUP_SETS; ++s) {
        for (uint8_t w = 0; w < DEDUP_WAYS; ++w) {
            _ring[s][w].content = 0;      // VALID ビット無し = 未使用
            _ring[s][w].last_seen_ms = 0;
        }
    }
}

} // namespace internal
} // namespace azaraC
