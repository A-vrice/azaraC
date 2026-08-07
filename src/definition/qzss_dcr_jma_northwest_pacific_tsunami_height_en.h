#pragma once
// AUTO-GENERATED from azarashi 0.16.4 with CI-CD
// Source module : qzss_dcr_jma_northwest_pacific_tsunami_height
// Variable      : qzss_dcr_jma_northwest_pacific_tsunami_height_en
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

#if (AZARAC_ENABLE_NW_PAC_TSUNAMI) && (AZARAC_LANG_EN)

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_northwest_pacific_tsunami_height_en_lookup(uint16_t id) noexcept {
    switch (id) {
        case 1: { static const char AZARAC_PROGMEM s[] = "0.3m~1m"; return azarac_pgm_view(s, 7); }
        case 2: { static const char AZARAC_PROGMEM s[] = "1m~3m"; return azarac_pgm_view(s, 5); }
        case 3: { static const char AZARAC_PROGMEM s[] = "3m~5m"; return azarac_pgm_view(s, 5); }
        case 4: { static const char AZARAC_PROGMEM s[] = "5m~10m"; return azarac_pgm_view(s, 6); }
        case 508: { static const char AZARAC_PROGMEM s[] = "More than 10m"; return azarac_pgm_view(s, 13); }
        case 509: { static const char AZARAC_PROGMEM s[] = "Huge"; return azarac_pgm_view(s, 4); }
        case 510: { static const char AZARAC_PROGMEM s[] = "High"; return azarac_pgm_view(s, 4); }
        case 511: { static const char AZARAC_PROGMEM s[] = "Unknown"; return azarac_pgm_view(s, 7); }
        default: return std::nullopt;
    }
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_northwest_pacific_tsunami_height_en_lookup(uint16_t id) noexcept {
    switch (id) {
        case 1: return std::string_view{"0.3m~1m", 7};
        case 2: return std::string_view{"1m~3m", 5};
        case 3: return std::string_view{"3m~5m", 5};
        case 4: return std::string_view{"5m~10m", 6};
        case 508: return std::string_view{"More than 10m", 13};
        case 509: return std::string_view{"Huge", 4};
        case 510: return std::string_view{"High", 4};
        case 511: return std::string_view{"Unknown", 7};
        default: return std::nullopt;
    }
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_northwest_pacific_tsunami_height_en_lookup(uint16_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_northwest_pacific_tsunami_height_en_lookup(uint16_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
