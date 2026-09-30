#include "Dedup.h"

namespace azaraC {
namespace internal {

// Set index from the packed content: fold the high bits of the CRC down so the
// truncated lanes still steer the set (taking only the low bits leaves whole
// content lanes unused for small tables).
static inline uint16_t setIndexOf(uint32_t content) {
    const uint32_t set_bits = DEDUP_SETS >> 1;   // 2^set_bits == DEDUP_SETS
    uint32_t h = content & 0xFFFFFFu;
    h = (h & ((1u << set_bits) - 1)) ^ (h >> set_bits);
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
        // Unsigned difference, signed comparison: correct across the 49.7-day
        // rollover of millis() and selects the true minimum.
        if ((int32_t)(e.last_seen_ms - oldest->last_seen_ms) < 0) oldest = &e;
        if (e.content != content) continue;
        if ((uint32_t)(now_ms - e.last_seen_ms) <= window_ms) {
            e.last_seen_ms = now_ms;   // seen again: extend validity (手順④')
            return true;
        }
        // Older than the validity window → no longer a duplicate.
        e.last_seen_ms = now_ms;
        return false;
    }

    // Not tracked: take a free way, or replace the least recently seen one
    // (a uniform ring would drop the newest information instead, which
    // re-announces a live alert and keeps a stale one).
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
