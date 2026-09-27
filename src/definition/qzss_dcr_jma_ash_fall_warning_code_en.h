#pragma once
// AUTO-GENERATED from azarashi 0.17.0 with CI-CD
// Source module : azarashi.definitions.qzss.dcr.ash_fall_warning_code
// Variable      : qzss_dcr_jma_ash_fall_warning_code_en
// Entries       : 5
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

#if (AZARAC_ENABLE_ASH_FALL) && (AZARAC_LANG_EN)

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_ash_fall_warning_code_en_lookup(uint8_t id) noexcept {
    switch (id) {
        case 1: { static const char AZARAC_PROGMEM s[] = "Low ash fall"; return azarac_pgm_view(s, 12); }
        case 2: { static const char AZARAC_PROGMEM s[] = "Moderate ash fall"; return azarac_pgm_view(s, 17); }
        case 3: { static const char AZARAC_PROGMEM s[] = "Heavy ash fall"; return azarac_pgm_view(s, 14); }
        case 4: { static const char AZARAC_PROGMEM s[] = "Falling debris"; return azarac_pgm_view(s, 14); }
        case 7: { static const char AZARAC_PROGMEM s[] = "Other Ash Fall Warning"; return azarac_pgm_view(s, 22); }
        default: return std::nullopt;
    }
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_ash_fall_warning_code_en_lookup(uint8_t id) noexcept {
    switch (id) {
        case 1: return std::string_view{"Low ash fall", 12};
        case 2: return std::string_view{"Moderate ash fall", 17};
        case 3: return std::string_view{"Heavy ash fall", 14};
        case 4: return std::string_view{"Falling debris", 14};
        case 7: return std::string_view{"Other Ash Fall Warning", 22};
        default: return std::nullopt;
    }
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_ash_fall_warning_code_en_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_ash_fall_warning_code_en_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
