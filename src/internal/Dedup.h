#pragma once
// Ring-buffer duplicate suppression: a message is a duplicate when
// {svid, msg_type, crc24} matches any slot in the ring.

#include "../azaraC_config.h"  // single source of truth for AZARAC_DEDUP_SLOTS
#include "MtCommonTypes.h"      // shared integer types (cstdint AVR switch lives here)
static_assert(AZARAC_DEDUP_SLOTS > 0, "AZARAC_DEDUP_SLOTS must be > 0");
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
        // Sentinel svid=0xFF so unused slots never match; valid SVIDs are 184-202.
        memset(_ring, 0xFF, sizeof(_ring));
    }

    bool isDuplicate(const DedupKey& key);
    void reset();

private:
    DedupKey _ring[AZARAC_DEDUP_SLOTS];
    uint16_t _head = 0;
    bool     _full = false;
};

} // namespace internal
} // namespace azaraC
