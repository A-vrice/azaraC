#pragma once
// AUTO-GENERATED from azarashi 0.16.4 with CI-CD
// Source module : qzss_dcx_camf_b4_lower_level_fields_tables
// Variable      : qzss_dcx_camf_d2_seismic_coefficient
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

#if (AZARAC_ENABLE_DCX_CAMF)

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d2_seismic_coefficient_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: { static const char AZARAC_PROGMEM s[] = "2"; return azarac_pgm_view(s, 1); }
        case 1: { static const char AZARAC_PROGMEM s[] = "3"; return azarac_pgm_view(s, 1); }
        case 2: { static const char AZARAC_PROGMEM s[] = "4"; return azarac_pgm_view(s, 1); }
        case 3: { static const char AZARAC_PROGMEM s[] = "5 weak"; return azarac_pgm_view(s, 6); }
        case 4: { static const char AZARAC_PROGMEM s[] = "5 strong"; return azarac_pgm_view(s, 8); }
        case 5: { static const char AZARAC_PROGMEM s[] = "6 weak"; return azarac_pgm_view(s, 6); }
        case 6: { static const char AZARAC_PROGMEM s[] = "6 strong"; return azarac_pgm_view(s, 8); }
        case 7: { static const char AZARAC_PROGMEM s[] = "7"; return azarac_pgm_view(s, 1); }
        default: return std::nullopt;
    }
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d2_seismic_coefficient_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return std::string_view{"2", 1};
        case 1: return std::string_view{"3", 1};
        case 2: return std::string_view{"4", 1};
        case 3: return std::string_view{"5 weak", 6};
        case 4: return std::string_view{"5 strong", 8};
        case 5: return std::string_view{"6 weak", 6};
        case 6: return std::string_view{"6 strong", 8};
        case 7: return std::string_view{"7", 1};
        default: return std::nullopt;
    }
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d2_seismic_coefficient_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d2_seismic_coefficient_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
