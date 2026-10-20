#pragma once
// Platform-independent, overflow-safe millis(), no external dependencies.
// - Arduino: millis() (~49.7-day wrap) extended to uint64_t with a volatile counter, so no <atomic> (avoids libatomic link issues on 32-bit MCUs).
// - Host: std::chrono::steady_clock.
// The volatile + read-compute-write is unsynchronized: multi-core callers may see non-monotonic values, single-task use is safe.
// On AVR and Cortex-M the update saves and restores the caller's interrupt state instead of unconditionally enabling IRQs.
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

// Current time in milliseconds (uint64_t, wrap-safe).
static inline uint64_t getMillis() {
#if defined(ARDUINO) && ARDUINO >= 1
    // Upper 32 bits = wrap count, lower 32 = last raw millis().
    // The unsynchronized read-compute-write can go backwards on multi-core / FreeRTOS; acceptable for coarse timing from a single task.
    static volatile uint64_t s_last = 0;

    uint32_t raw;
#if defined(__AVR__)
    // Save SREG instead of calling interrupts(): getMillis() may be called from the
    // caller's critical section or an ISR, and re-enabling IRQs there would break its atomicity.
    uint8_t irq_state = SREG;
    cli();
#elif defined(__arm__)
    // Cortex-M: restore PRIMASK rather than unconditionally enabling IRQs.
    // Use mrs/msr directly: CMSIS intrinsics are not in scope on every Arduino
    // ARM core (rp2040, Teensy), and every Cortex-M supports these instructions.
    uint32_t irq_state;
    __asm__ volatile("mrs %0, primask" : "=r"(irq_state));
    __asm__ volatile("cpsid i" ::: "memory");
#else
    // No portable save/restore API on this core (e.g. Xtensa). Keep the previous behaviour.
    noInterrupts();
#endif
    // Read millis() inside the critical section so the extension below observes one consistent value.
    raw = millis();
    uint64_t prev = s_last;
    uint32_t prev_low = static_cast<uint32_t>(prev);
    uint64_t high = prev & 0xFFFFFFFF00000000ULL;
    if (raw < prev_low) {
        high += (1ULL << 32);
    }
    uint64_t current = high | raw;
    s_last = current;
#if defined(__AVR__)
    SREG = irq_state;
#elif defined(__arm__)
    __asm__ volatile("msr primask, %0" :: "r"(irq_state) : "memory");
#else
    interrupts();
#endif
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
