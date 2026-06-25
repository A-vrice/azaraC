#pragma once
// azaraC - src/internal/TimeFields.h
// Platform-independent time utility
//
// Overflow-safe implementation:
// - Arduino: Uses millis() with uint64_t to handle ~49.7-day overflow
// - Host: Uses std::chrono::steady_clock with uint64_t

#include <cstdint>

#if defined(ARDUINO) && ARDUINO >= 1
#include <Arduino.h>
#else
#include <chrono>
#endif

namespace azaraC {
namespace internal {

// Get current time in milliseconds (overflow-safe, returns uint64_t)
// On Arduino: millis() overflows after ~49.7 days, but we use uint64_t
//            to allow safe arithmetic even after overflow
// On Host:    Uses std::chrono::steady_clock with full 64-bit range
static inline uint64_t getMillis() {
#if defined(ARDUINO) && ARDUINO >= 1
    static uint32_t last_raw = 0;
    static uint64_t high = 0;
    uint32_t raw = static_cast<uint32_t>(millis());
    if (raw < last_raw) {
        high += (1ULL << 32);
    }
    last_raw = raw;
    return high | raw;
#else
    auto now = std::chrono::steady_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch()
    ).count();
    return static_cast<uint64_t>(ms);
#endif
}

// Safe millisecond difference calculation (handles overflow)
// Returns (current - previous) correctly even if current < previous (overflow case)
static inline uint32_t millisDiff(uint64_t current, uint64_t previous) {
    return static_cast<uint32_t>(current - previous);
}

} // namespace internal
} // namespace azaraC
