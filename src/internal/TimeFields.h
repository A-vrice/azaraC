#pragma once
// azaraC - src/internal/TimeFields.h
// Platform-independent time utility
#include <cstdint>

#if defined(ARDUINO) && ARDUINO >= 1
#include <Arduino.h>
#else
// Non-Arduino environment
#endif

// ---------------------------------------------------------------------------
// Workaround for Arduino/mbed macro conflicts with <chrono>
// Arduino.h defines abs, min, max, round as macros.
// These conflict with std::chrono templates like abs(duration<_Rep, _Period>).
// We temporarily undefine them while including <chrono>.
// ---------------------------------------------------------------------------
#if defined(ARDUINO) && ARDUINO >= 1
#pragma push_macro("abs")
#pragma push_macro("min")
#pragma push_macro("max")
#pragma push_macro("round")
#undef abs
#undef min
#undef max
#undef round
#endif

#include <chrono>

#if defined(ARDUINO) && ARDUINO >= 1
#pragma pop_macro("abs")
#pragma pop_macro("min")
#pragma pop_macro("max")
#pragma pop_macro("round")
#endif
// ---------------------------------------------------------------------------

namespace azaraC {
namespace internal {

static inline uint32_t getMillis() {
#if defined(ARDUINO) && ARDUINO >= 1
    return millis();
#else
    auto now = std::chrono::steady_clock::now();
    // Fixed syntax error: [] -> <>, removed duplicate cast
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch()
    ).count();
    return static_cast<uint32_t>(ms);
#endif
}

} // namespace internal
} // namespace azaraC
