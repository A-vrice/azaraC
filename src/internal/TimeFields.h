#pragma once
// azaraC - src/internal/TimeFields.h
// Platform-independent time utility
#include <cstdint>

#if defined(ARDUINO) && ARDUINO >= 1
#include <Arduino.h>
#else
#include <chrono>
#endif

namespace azaraC {
namespace internal {

// Get current time in milliseconds
// Uses millis() on Arduino, std::chrono::steady_clock otherwise
static inline uint32_t getMillis() {
#if defined(ARDUINO) && ARDUINO >= 1
    return millis();
#else
    auto now = std::chrono::steady_clock::now();
    // 修正: duration_castの構文エラー([] -> <>)と重複キャストを修正
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch()
    ).count();
    return static_cast<uint32_t>(ms);
#endif
}

} // namespace internal
} // namespace azaraC

