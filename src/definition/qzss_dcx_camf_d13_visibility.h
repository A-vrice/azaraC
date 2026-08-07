#pragma once
// AUTO-GENERATED from azarashi 0.16.4 with CI-CD
// Source module : qzss_dcx_camf_b4_lower_level_fields_tables
// Variable      : qzss_dcx_camf_d13_visibility
// Entries       : 10
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
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d13_visibility_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: { static const char AZARAC_PROGMEM s[] = "Dense fog: visibility < 20m"; return azarac_pgm_view(s, 27); }
        case 1: { static const char AZARAC_PROGMEM s[] = "Thick fog: 20m < visibility < 200m"; return azarac_pgm_view(s, 34); }
        case 2: { static const char AZARAC_PROGMEM s[] = "Moderate fog: 200m < visibility < 500m"; return azarac_pgm_view(s, 38); }
        case 3: { static const char AZARAC_PROGMEM s[] = "Light fog: 500m < visibility < 1000m"; return azarac_pgm_view(s, 36); }
        case 4: { static const char AZARAC_PROGMEM s[] = "Thin fog: 1km < visibility < 2km"; return azarac_pgm_view(s, 32); }
        case 5: { static const char AZARAC_PROGMEM s[] = "Haze: 2km < visibility < 4km"; return azarac_pgm_view(s, 28); }
        case 6: { static const char AZARAC_PROGMEM s[] = "Light haze: 4km < visibility < 10km"; return azarac_pgm_view(s, 35); }
        case 7: { static const char AZARAC_PROGMEM s[] = "Clear: 10km < visibility < 20km"; return azarac_pgm_view(s, 31); }
        case 8: { static const char AZARAC_PROGMEM s[] = "Very clear: 20km < visibility < 50km"; return azarac_pgm_view(s, 36); }
        case 9: { static const char AZARAC_PROGMEM s[] = "Exceptionally clear: visibility > 50km"; return azarac_pgm_view(s, 38); }
        default: return std::nullopt;
    }
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d13_visibility_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return std::string_view{"Dense fog: visibility < 20m", 27};
        case 1: return std::string_view{"Thick fog: 20m < visibility < 200m", 34};
        case 2: return std::string_view{"Moderate fog: 200m < visibility < 500m", 38};
        case 3: return std::string_view{"Light fog: 500m < visibility < 1000m", 36};
        case 4: return std::string_view{"Thin fog: 1km < visibility < 2km", 32};
        case 5: return std::string_view{"Haze: 2km < visibility < 4km", 28};
        case 6: return std::string_view{"Light haze: 4km < visibility < 10km", 35};
        case 7: return std::string_view{"Clear: 10km < visibility < 20km", 31};
        case 8: return std::string_view{"Very clear: 20km < visibility < 50km", 36};
        case 9: return std::string_view{"Exceptionally clear: visibility > 50km", 38};
        default: return std::nullopt;
    }
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d13_visibility_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d13_visibility_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
