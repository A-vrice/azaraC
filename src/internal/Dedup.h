#pragma once
// Ring-buffer duplicate suppression.
// A message is considered duplicate when {svid, msg_type, crc24} matches
// any slot in the ring.

#include "../azaraC_config.h"  // single source of truth for AZARAC_DEDUP_SLOTS
#include "MtCommonTypes.h"      // shared integer types (cstdint AVR switch lives here)
#if defined(__AVR__)
#include "avr_std/cstring"
#else
#include <cstring>
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
