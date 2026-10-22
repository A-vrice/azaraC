#pragma once

#if defined(__AVR__)
#include "../internal/avr_std/cstdint"
#else
#include <cstdint>
#endif

namespace azaraC {
namespace internal {

struct Frame {
    uint8_t     svid;       // QZSS L1S PRN (spec IDs 53–63 -> 181–191; NMEA 64–99 rejected, 0–52 pass through as 128–180 and are outside the contract; unmapped UBX svId passes through as-is)
    uint8_t     bits[32];   // 250 bits MSB-first; bits[31] lower 6 = padding zeros
};

} // namespace internal
} // namespace azaraC
