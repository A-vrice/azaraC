#pragma once
// AUTO-GENERATED from azarashi 0.17.1 with CI-CD
// Source module : azarashi.definitions.qzss.dcr.long_period_ground_motion_lower_limit
// Variable      : qzss_dcr_jma_long_period_ground_motion_lower_limit_en
// Entries       : 7
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

#if (AZARAC_ENABLE_EEW) && (AZARAC_LANG_EN)

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_long_period_ground_motion_lower_limit_en_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: { static const char AZARAC_PROGMEM s[] = "No data"; return azarac_pgm_view(s, 7); }
        case 1: { static const char AZARAC_PROGMEM s[] = "Less than Long-Period Ground Motion class of 1"; return azarac_pgm_view(s, 46); }
        case 2: { static const char AZARAC_PROGMEM s[] = "Long-Period Ground Motion class of 1"; return azarac_pgm_view(s, 36); }
        case 3: { static const char AZARAC_PROGMEM s[] = "Long-Period Ground Motion class of 2"; return azarac_pgm_view(s, 36); }
        case 4: { static const char AZARAC_PROGMEM s[] = "Long-Period Ground Motion class of 3"; return azarac_pgm_view(s, 36); }
        case 5: { static const char AZARAC_PROGMEM s[] = "Long-Period Ground Motion class of 4"; return azarac_pgm_view(s, 36); }
        case 7: { static const char AZARAC_PROGMEM s[] = "Unknown"; return azarac_pgm_view(s, 7); }
        default: return std::nullopt;
    }
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_long_period_ground_motion_lower_limit_en_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return std::string_view{"No data", 7};
        case 1: return std::string_view{"Less than Long-Period Ground Motion class of 1", 46};
        case 2: return std::string_view{"Long-Period Ground Motion class of 1", 36};
        case 3: return std::string_view{"Long-Period Ground Motion class of 2", 36};
        case 4: return std::string_view{"Long-Period Ground Motion class of 3", 36};
        case 5: return std::string_view{"Long-Period Ground Motion class of 4", 36};
        case 7: return std::string_view{"Unknown", 7};
        default: return std::nullopt;
    }
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_long_period_ground_motion_lower_limit_en_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_long_period_ground_motion_lower_limit_en_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
