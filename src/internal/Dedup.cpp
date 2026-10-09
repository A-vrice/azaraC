#include "Dedup.h"

namespace azaraC {
namespace internal {

// Set index from the packed content. DEDUP_SETS is a power of two, so the index is the low log2(DEDUP_SETS) bits after folding the CRC down onto itself. Both shifts stay below 24, so the fold is well defined for every legal AZARAC_DEDUP_SETS (shifting by DEDUP_SETS/2, the previous form, is undefined once DEDUP_SETS >= 64).
//
// ponytail: `& 0xFFFFFF` は現構成では no-op。fold は各ビットを最大 12 しか下げないため、出力 bit i は元の bit i, i+4, i+8, i+12 のみに依存する（出力 k bit なら元の bit (k-1)+12 まで）。低 log2(SETS) bit しか採らないので、SETS ≤ 2^12（= SLOTS ≤ 32768）では元の bit 24 以上は index に到達できない。つまり It（合成鍵 bits 24-25）も msg_type（実鍵 bits 24-29）もセット選択に効かない。SETS ≥ 2^13（SLOTS ≥ 65536、512KB）にすると到達し始め、このマスクが両者を index に効かせる/効かせないを決める。実測: 20 万件の乱数で SETS = 2^4..2^12 はマスク有無で index 完全一致、2^14 で差異が出る。
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
        // Age from now, unsigned: correct across the 49.7-day rollover of millis() and for gaps beyond 2^31 ms. Comparing last_seen_ms values against each other wraps once the two entries are >24.8 days apart, and then picks the live entry as the victim.
        if ((uint32_t)(now_ms - e.last_seen_ms) > (uint32_t)(now_ms - oldest->last_seen_ms)) oldest = &e;
        if (e.content != content) continue;
        if ((uint32_t)(now_ms - e.last_seen_ms) <= window_ms) {
            e.last_seen_ms = now_ms;   // seen again: extend validity (手順④')
            return true;
        }
        // Older than the validity window → no longer a duplicate.
        e.last_seen_ms = now_ms;
        return false;
    }

    // Not tracked: take a free way, or replace the least recently seen one (a uniform ring would drop the newest information instead, which re-announces a live alert and keeps a stale one).
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
