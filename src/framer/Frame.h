#pragma once

#if defined(__AVR__)
#include "../internal/avr_std/cstdint"
#else
#include <cstdint>
#endif

namespace azaraC {
namespace internal {

struct Frame {
    uint8_t     svid;       // QZSS L1S PRN (183–191 from both framers)
    uint8_t     bits[32];   // 250 bits MSB-first; bits[31] lower 6 = padding zeros
};

} // namespace internal
} // namespace azaraC
