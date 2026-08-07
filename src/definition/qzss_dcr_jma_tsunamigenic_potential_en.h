#pragma once
// AUTO-GENERATED from azarashi 0.16.4 with CI-CD
// Source module : qzss_dcr_jma_tsunamigenic_potential
// Variable      : qzss_dcr_jma_tsunamigenic_potential_en
// Entries       : 6
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
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_tsunamigenic_potential_en_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: { static const char AZARAC_PROGMEM s[] = "There is No Possibility of a Tsunami"; return azarac_pgm_view(s, 36); }
        case 1: { static const char AZARAC_PROGMEM s[] = "There is a Possibility of a Destructive Ocean-Wide Tsunami"; return azarac_pgm_view(s, 58); }
        case 2: { static const char AZARAC_PROGMEM s[] = "There is a Possibility of a Destructive Regional Tsunami"; return azarac_pgm_view(s, 56); }
        case 3: { static const char AZARAC_PROGMEM s[] = "There is a Possibility of a Destructive Local Tsunami Near the Epicenter"; return azarac_pgm_view(s, 72); }
        case 4: { static const char AZARAC_PROGMEM s[] = "There is a Very Small Possibility of a Destructive Local Tsunami"; return azarac_pgm_view(s, 64); }
        case 7: { static const char AZARAC_PROGMEM s[] = "There is a Possibility of a Tsunami"; return azarac_pgm_view(s, 35); }
        default: return std::nullopt;
    }
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_tsunamigenic_potential_en_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return std::string_view{"There is No Possibility of a Tsunami", 36};
        case 1: return std::string_view{"There is a Possibility of a Destructive Ocean-Wide Tsunami", 58};
        case 2: return std::string_view{"There is a Possibility of a Destructive Regional Tsunami", 56};
        case 3: return std::string_view{"There is a Possibility of a Destructive Local Tsunami Near the Epicenter", 72};
        case 4: return std::string_view{"There is a Very Small Possibility of a Destructive Local Tsunami", 64};
        case 7: return std::string_view{"There is a Possibility of a Tsunami", 35};
        default: return std::nullopt;
    }
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_tsunamigenic_potential_en_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_tsunamigenic_potential_en_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
