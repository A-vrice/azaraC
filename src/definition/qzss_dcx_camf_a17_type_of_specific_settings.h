#pragma once
// AUTO-GENERATED from azarashi 0.16.4 with CI-CD
// Source module : qzss_dcx_camf_a17_type_of_specific_settings
// Variable      : qzss_dcx_camf_a17_type_of_specific_settings
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

#if (AZARAC_ENABLE_DCX_CAMF)

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_a17_type_of_specific_settings_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: { static const char AZARAC_PROGMEM s[] = "B1 - Improved Resolution of Main Ellipse"; return azarac_pgm_view(s, 40); }
        case 1: { static const char AZARAC_PROGMEM s[] = "B2 - Position of the Centre of the Hazard"; return azarac_pgm_view(s, 41); }
        case 2: { static const char AZARAC_PROGMEM s[] = "B3 - Secondary Ellipse Definition"; return azarac_pgm_view(s, 33); }
        case 3: { static const char AZARAC_PROGMEM s[] = "B4 - Quantitative and detailed information about the Hazard"; return azarac_pgm_view(s, 59); }
        default: return std::nullopt;
    }
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_a17_type_of_specific_settings_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return std::string_view{"B1 - Improved Resolution of Main Ellipse", 40};
        case 1: return std::string_view{"B2 - Position of the Centre of the Hazard", 41};
        case 2: return std::string_view{"B3 - Secondary Ellipse Definition", 33};
        case 3: return std::string_view{"B4 - Quantitative and detailed information about the Hazard", 59};
        default: return std::nullopt;
    }
}
#endif

#else

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_a17_type_of_specific_settings_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}

#endif

} // namespace def
} // namespace azaraC
