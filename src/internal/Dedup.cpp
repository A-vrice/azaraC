#include "Dedup.h"

namespace azaraC {
namespace internal {

// Set index from the packed content: DEDUP_SETS is a power of two, so the index is the low log2(DEDUP_SETS) bits after folding the CRC onto itself.
// Both shifts stay below 24 (shifting by DEDUP_SETS/2 was undefined once DEDUP_SETS >= 64).
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
        // Age = now - last_seen as unsigned: correct across the 49.7-day millis() rollover.
        // Comparing last_seen values wraps once two entries are >24.8 days apart and then evicts the live one.
        if ((uint32_t)(now_ms - e.last_seen_ms) > (uint32_t)(now_ms - oldest->last_seen_ms)) oldest = &e;
        if (e.content != content) continue;
        if ((uint32_t)(now_ms - e.last_seen_ms) <= window_ms) {
            e.last_seen_ms = now_ms;   // 手順④': 再受信で有効時間を延長
            return true;
        }
        e.last_seen_ms = now_ms;
        return false;
    }

    // Not tracked: take a free way, else evict the least recently seen one (a uniform ring would drop the newest information instead, re-announcing a live alert and keeping a stale one).
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
