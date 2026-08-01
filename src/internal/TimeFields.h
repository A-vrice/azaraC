#pragma once
// azaraC - src/internal/TimeFields.h
// Platform-independent time utility
//
// Overflow-safe implementation without external library dependencies:
// - Arduino: Uses millis() with volatile uint64_t to handle ~49.7-day overflow.
//            No <atomic> dependency — avoids libatomic link issues on 32-bit MCUs.
// - Host: Uses std::chrono::steady_clock with uint64_t

#if defined(__AVR__)
#include "avr_std/cstdint"
#else
#include <cstdint>
#endif

#if defined(ARDUINO) && ARDUINO >= 1
#include <Arduino.h>
#else
#include <chrono>
#endif

namespace azaraC {
namespace internal {

// Get current time in milliseconds (overflow-safe, returns uint64_t)
// On Arduino: 32-bit millis() is extended to 64-bit with wrap detection.
//            volatile prevents compiler reordering and is available on all
//            platforms without requiring the <atomic> or libatomic libraries.
// On Host:    Uses std::chrono::steady_clock with full 64-bit range.
static inline uint64_t getMillis() {
#if defined(ARDUINO) && ARDUINO >= 1
    // 32-bit millis() extended to 64-bit: upper 32 bits track overflow count,
    // lower 32 bits = last raw millis() value.
    // volatile ensures each call reads/writes actual memory (no register caching).
    // On single-core platforms this is naturally race-free.
    // On multi-core / FreeRTOS platforms tiny windows between read and write
    // are acceptable for time-keeping; worst-case is a duplicate timestamp.
    static volatile uint64_t s_last = 0;

    uint32_t raw = millis();
    uint64_t prev = s_last;  // volatile read
    uint32_t prev_low = static_cast<uint32_t>(prev);
    uint64_t high = prev & 0xFFFFFFFF00000000ULL;
    if (raw < prev_low) {
        high += (1ULL << 32);
    }
    uint64_t current = high | raw;
    s_last = current;  // volatile store
    return current;
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
