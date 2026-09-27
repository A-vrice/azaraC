#pragma once
// AUTO-GENERATED from azarashi 0.17.0 with CI-CD
// Source module : azarashi.definitions.qzss.dcr.typhoon_scale_category
// Variable      : qzss_dcr_jma_typhoon_scale_category_en
// Entries       : 4
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

#if (AZARAC_ENABLE_TYPHOON) && (AZARAC_LANG_EN)

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_typhoon_scale_category_en_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: { static const char AZARAC_PROGMEM s[] = "None"; return azarac_pgm_view(s, 4); }
        case 1: { static const char AZARAC_PROGMEM s[] = "Large"; return azarac_pgm_view(s, 5); }
        case 2: { static const char AZARAC_PROGMEM s[] = "Very large"; return azarac_pgm_view(s, 10); }
        case 15: { static const char AZARAC_PROGMEM s[] = "Other Scale Category"; return azarac_pgm_view(s, 20); }
        default: return std::nullopt;
    }
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_typhoon_scale_category_en_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return std::string_view{"None", 4};
        case 1: return std::string_view{"Large", 5};
        case 2: return std::string_view{"Very large", 10};
        case 15: return std::string_view{"Other Scale Category", 20};
        default: return std::nullopt;
    }
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_typhoon_scale_category_en_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_typhoon_scale_category_en_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
