#pragma once
// azaraC - src/framer/Frame.h

#if defined(__AVR__)
#include "../internal/avr_std/cstdint"
#else
#include <cstdint>
#endif

namespace azaraC {
namespace internal {

enum class FrameSource : uint8_t { UBX = 0, NMEA = 1 };

struct Frame {
    uint8_t     svid;       // QZSS svId (UBX) or PRN-offset
    uint8_t     bits[32];   // 250 bits MSB-first; bits[31] lower 6 = padding zeros
    FrameSource source;
};

} // namespace internal
} // namespace azaraC
