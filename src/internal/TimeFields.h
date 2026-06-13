#pragma once
// azaraC - src/internal/TimeFields.h
// Platform-independent time utility
#include <cstdint>

#if defined(ARDUINO) && ARDUINO >= 1
#include <Arduino.h>
#endif

// ---------------------------------------------------------------------------
// Workaround for mbed/Arduino macro conflicts with <chrono>
// Arduino/mbed defines abs, min, max, round as macros.
// The C++ <chrono> header contains declarations like:
//   abs(duration<_Rep, _Period> __d)
// The preprocessor misinterprets the comma inside the template arguments
// as a macro argument separator, causing a "passed 2 arguments" error.
// We temporarily undefine these macros while including <chrono>.
// ---------------------------------------------------------------------------
#pragma push_macro("abs")
#pragma push_macro("min")
#pragma push_macro("max")
#pragma push_macro("round")

#undef abs
#undef min
#undef max
#undef round

#include <chrono>

#pragma pop_macro("abs")
#pragma pop_macro("min")
#pragma pop_macro("max")
#pragma pop_macro("round")
// ---------------------------------------------------------------------------

namespace azaraC {
namespace internal {

// Get current time in milliseconds
// Uses millis() on Arduino, std::chrono::steady_clock otherwise
//
// NOTE on wraparound (non-ARDUINO path): the raw millisecond count from
// std::chrono::steady_clock is cast to uint32_t. This causes the returned
// value to wrap around approximately every 49.7 days (2^32 ms), matching
// the behavior of Arduino::millis(). This wraparound is intentional.
// Callers MUST perform timeout checks using unsigned arithmetic, e.g.:
//     (current - start) < timeout
// to handle rollovers safely.
static inline uint32_t getMillis() {
#if defined(ARDUINO) && ARDUINO >= 1
    return millis();
#else
    auto now = std::chrono::steady_clock::now();
    // Fix: Corrected the syntax for duration_cast
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch()
    ).count();
    return static_cast<uint32_t>(ms);
#endif
}

} // namespace internal
} // namespace azaraC
