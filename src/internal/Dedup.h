#pragma once
// azaraC - src/internal/Dedup.h
// Ring-buffer duplicate suppression.
// A message is considered duplicate when {svid, msg_type, crc24} matches
// any slot in the ring.

// DedupFilter — ring-buffer duplicate suppression.
// A message is considered duplicate when {svid, msg_type, crc24} matches
// any slot in the ring.  To guard against false matches on zero-initialized
// (unused) slots, the ring is filled with a sentinel svid=0xFF before first
// use (valid SVIDs for QZSS L1S are 184-202).

#include <cstdint>
#include <cstring>

#ifndef AZARAC_DEDUP_SLOTS
#define AZARAC_DEDUP_SLOTS 8
#endif

namespace azaraC {
namespace internal {

struct DedupKey {
    uint8_t  svid;
    uint8_t  msg_type;
    uint32_t crc24;
};

class DedupFilter {
public:
    DedupFilter() {
        // Fill ring with sentinel svid=0xFF so unused slots never match valid keys.
        // Valid QZSS L1S SVIDs are 184-202, so 0xFF is safe.
        memset(_ring, 0xFF, sizeof(_ring));
    }

    // Returns true if key is a duplicate (already seen).
    // If not duplicate, stores key and returns false.
    bool isDuplicate(const DedupKey& key);
    void reset();

private:
    DedupKey _ring[AZARAC_DEDUP_SLOTS];
    uint16_t _head = 0;
    bool     _full = false;
};

} // namespace internal
} // namespace azaraC
