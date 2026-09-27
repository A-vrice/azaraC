#pragma once
// AUTO-GENERATED from azarashi 0.17.0 with CI-CD
// Source module : azarashi.definitions.qzss.dcr.flood_warning_level
// Variable      : qzss_dcr_jma_flood_warning_level_en
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

#if (AZARAC_ENABLE_FLOOD) && (AZARAC_LANG_EN)

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_flood_warning_level_en_lookup(uint8_t id) noexcept {
    switch (id) {
        case 1: { static const char AZARAC_PROGMEM s[] = "Warning Lifted"; return azarac_pgm_view(s, 14); }
        case 2: { static const char AZARAC_PROGMEM s[] = "Information to provide a warning on flooding"; return azarac_pgm_view(s, 44); }
        case 3: { static const char AZARAC_PROGMEM s[] = "Information on potential flood hazards"; return azarac_pgm_view(s, 38); }
        case 4: { static const char AZARAC_PROGMEM s[] = "Information on flooding"; return azarac_pgm_view(s, 23); }
        case 15: { static const char AZARAC_PROGMEM s[] = "Other Warning Level"; return azarac_pgm_view(s, 19); }
        default: return std::nullopt;
    }
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_flood_warning_level_en_lookup(uint8_t id) noexcept {
    switch (id) {
        case 1: return std::string_view{"Warning Lifted", 14};
        case 2: return std::string_view{"Information to provide a warning on flooding", 44};
        case 3: return std::string_view{"Information on potential flood hazards", 38};
        case 4: return std::string_view{"Information on flooding", 23};
        case 15: return std::string_view{"Other Warning Level", 19};
        default: return std::nullopt;
    }
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_flood_warning_level_en_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_flood_warning_level_en_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
