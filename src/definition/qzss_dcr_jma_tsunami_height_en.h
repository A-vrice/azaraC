#pragma once
// AUTO-GENERATED from azarashi 0.17.1 with CI-CD
// Source module : azarashi.definitions.qzss.dcr.tsunami_height
// Variable      : qzss_dcr_jma_tsunami_height_en
// Entries       : 9
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

#if (AZARAC_ENABLE_TSUNAMI) && (AZARAC_LANG_EN)

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_tsunami_height_en_lookup(uint8_t id) noexcept {
    switch (id) {
        case 1: { static const char AZARAC_PROGMEM s[] = "Less than 0.2 m"; return azarac_pgm_view(s, 15); }
        case 2: { static const char AZARAC_PROGMEM s[] = "1 m"; return azarac_pgm_view(s, 3); }
        case 3: { static const char AZARAC_PROGMEM s[] = "3 m"; return azarac_pgm_view(s, 3); }
        case 4: { static const char AZARAC_PROGMEM s[] = "5 m"; return azarac_pgm_view(s, 3); }
        case 5: { static const char AZARAC_PROGMEM s[] = "10 m"; return azarac_pgm_view(s, 4); }
        case 6: { static const char AZARAC_PROGMEM s[] = "Over 10 m"; return azarac_pgm_view(s, 9); }
        case 13: { static const char AZARAC_PROGMEM s[] = "No data"; return azarac_pgm_view(s, 7); }
        case 14: { static const char AZARAC_PROGMEM s[] = "Unknown"; return azarac_pgm_view(s, 7); }
        case 15: { static const char AZARAC_PROGMEM s[] = "Other Tsunami Height"; return azarac_pgm_view(s, 20); }
        default: return std::nullopt;
    }
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_tsunami_height_en_lookup(uint8_t id) noexcept {
    switch (id) {
        case 1: return std::string_view{"Less than 0.2 m", 15};
        case 2: return std::string_view{"1 m", 3};
        case 3: return std::string_view{"3 m", 3};
        case 4: return std::string_view{"5 m", 3};
        case 5: return std::string_view{"10 m", 4};
        case 6: return std::string_view{"Over 10 m", 9};
        case 13: return std::string_view{"No data", 7};
        case 14: return std::string_view{"Unknown", 7};
        case 15: return std::string_view{"Other Tsunami Height", 20};
        default: return std::nullopt;
    }
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_tsunami_height_en_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_tsunami_height_en_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
