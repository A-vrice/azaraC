#pragma once

#if defined(__AVR__)
#include "../internal/avr_std/cstdint"
#else
#include <cstdint>
#endif
#include "Frame.h"

namespace azaraC {
namespace internal {

class IFramer {
public:
    // Return true only after filling *both* members of `out` (svid and all 32 bytes of bits).
    // Parser zero-initialises it on the custom-framer path, but a partial write would still
    // decode as all-zero data.
    virtual bool feed(uint8_t byte, Frame& out) = 0;
    virtual void reset() = 0;
    virtual ~IFramer() = default;
};

} // namespace internal
} // namespace azaraC
