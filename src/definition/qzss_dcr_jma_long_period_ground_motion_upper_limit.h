#pragma once
// AUTO-GENERATED from azarashi 0.16.4 with CI-CD
// Source module : qzss_dcr_jma_long_period_ground_motion_upper_limit
// Variable      : qzss_dcr_jma_long_period_ground_motion_upper_limit
// Entries       : 8
// Strategy      : switch

// NOTE: This function may return nullptr for unknown IDs.
// Callers MUST perform a null-check before using the result.

#if defined(__AVR__)
#include "../internal/avr_std/cstdint"
#include "../internal/avr_std/optional"
#include "../internal/avr_std/string_view"
#else
#include <cstdint>
#include <optional>
#include <string_view>
#endif
#include "../azaraC.h"
#include "../internal/FlashString.h"

namespace azaraC {
namespace def {

#if (AZARAC_ENABLE_EEW)

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_long_period_ground_motion_upper_limit_lookup(uint8_t id) noexcept {
    switch (id) {
        case 1: { static const char AZARAC_PROGMEM s[] = "長周期地震動階級1未満"; return azarac_pgm_view(s, 31); }
        case 2: { static const char AZARAC_PROGMEM s[] = "長周期地震動階級1"; return azarac_pgm_view(s, 25); }
        case 3: { static const char AZARAC_PROGMEM s[] = "長周期地震動階級2"; return azarac_pgm_view(s, 25); }
        case 4: { static const char AZARAC_PROGMEM s[] = "長周期地震動階級3"; return azarac_pgm_view(s, 25); }
        case 5: { static const char AZARAC_PROGMEM s[] = "長周期地震動階級4"; return azarac_pgm_view(s, 25); }
        case 6: { static const char AZARAC_PROGMEM s[] = "〜程度以上"; return azarac_pgm_view(s, 15); }
        case 7: { static const char AZARAC_PROGMEM s[] = "不明"; return azarac_pgm_view(s, 6); }
        default: return std::nullopt;
    }
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_long_period_ground_motion_upper_limit_lookup(uint8_t id) noexcept {
    switch (id) {
        case 1: return std::string_view{"長周期地震動階級1未満", 31};
        case 2: return std::string_view{"長周期地震動階級1", 25};
        case 3: return std::string_view{"長周期地震動階級2", 25};
        case 4: return std::string_view{"長周期地震動階級3", 25};
        case 5: return std::string_view{"長周期地震動階級4", 25};
        case 6: return std::string_view{"〜程度以上", 15};
        case 7: return std::string_view{"不明", 6};
        default: return std::nullopt;
    }
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_long_period_ground_motion_upper_limit_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_long_period_ground_motion_upper_limit_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
