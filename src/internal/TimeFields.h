#pragma once
// Platform-independent time utility
//
// Overflow-safe implementation without external library dependencies:
// - Arduino: Uses millis() with volatile uint64_t to handle ~49.7-day overflow.
//            No <atomic> dependency — avoids libatomic link issues on 32-bit MCUs.
// - Host: Uses std::chrono::steady_clock with uint64_t
// volatile + read-compute-write is unsynchronized: multi-core callers
//           may see non-monotonic values. Single-core / single-task use is safe.
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
    // On multi-core / FreeRTOS platforms the unsynchronized read-compute-write
    // can return non-monotonic values or lose an epoch near wraparound;
    // acceptable only for coarse time-keeping from a single task.
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

} // namespace internal
} // namespace azaraC
