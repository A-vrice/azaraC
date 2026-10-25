#pragma once
// AUTO-GENERATED from azarashi 0.17.1 — do not edit
// azarashi.definitions.camf.d_fields → qzss_dcx_camf_d15_flood_severity: 4 entries, strategy switch
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

static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D15_FLOOD_SEVERITY_C0[] = "Minor Flooding - Minimal or no property damage, but possibly some public threat.";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D15_FLOOD_SEVERITY_C1[] = "Moderate Flooding - Some inundation of structures and roads near stream. Some evacuations of people and/or transfer of property to higher elevations.";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D15_FLOOD_SEVERITY_C2[] = "Major Flooding - Extensive inundation of structures and roads. Significant evacuations of people and/or transfer of property to higher elevations.";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D15_FLOOD_SEVERITY_C3[] = "Record Flooding";
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d15_flood_severity_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D15_FLOOD_SEVERITY_C0), 80);
        case 1: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D15_FLOOD_SEVERITY_C1), 149);
        case 2: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D15_FLOOD_SEVERITY_C2), 146);
        case 3: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D15_FLOOD_SEVERITY_C3), 15);
        default: return std::nullopt;
    }
}

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d15_flood_severity_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d15_flood_severity_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
