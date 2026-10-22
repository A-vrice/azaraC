#pragma once
// AUTO-GENERATED from azarashi 0.17.1 — do not edit
// azarashi.definitions.camf.a17_type_of_specific_settings → qzss_dcx_camf_a17_type_of_specific_settings: 4 entries, strategy switch
// Unknown id returns nullptr — callers MUST null-check.

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
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_A17_TYPE_OF_SPECIFIC_SETTINGS_C0[] = "B1 - Improved Resolution of Main Ellipse";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_A17_TYPE_OF_SPECIFIC_SETTINGS_C1[] = "B2 - Position of the Centre of the Hazard";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_A17_TYPE_OF_SPECIFIC_SETTINGS_C2[] = "B3 - Secondary Ellipse Definition";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_A17_TYPE_OF_SPECIFIC_SETTINGS_C3[] = "B4 - Quantitative and detailed information about the Hazard";
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_a17_type_of_specific_settings_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCX_CAMF_A17_TYPE_OF_SPECIFIC_SETTINGS_C0), 40);
        case 1: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCX_CAMF_A17_TYPE_OF_SPECIFIC_SETTINGS_C1), 41);
        case 2: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCX_CAMF_A17_TYPE_OF_SPECIFIC_SETTINGS_C2), 33);
        case 3: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCX_CAMF_A17_TYPE_OF_SPECIFIC_SETTINGS_C3), 59);
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

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_a17_type_of_specific_settings_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_a17_type_of_specific_settings_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
