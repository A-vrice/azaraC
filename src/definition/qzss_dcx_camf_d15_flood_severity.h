#pragma once
// AUTO-GENERATED from azarashi 0.16.4 with CI-CD
// Source module : qzss_dcx_camf_b4_lower_level_fields_tables
// Variable      : qzss_dcx_camf_d15_flood_severity
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
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d15_flood_severity_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: { static const char AZARAC_PROGMEM s[] = "Minor Flooding - Minimal or no property damage, but possibly some public threat."; return azarac_pgm_view(s, 80); }
        case 1: { static const char AZARAC_PROGMEM s[] = "Moderate Flooding - Some inundation of structures and roads near stream. Some evacuations of people and/or transfer of property to higher elevations."; return azarac_pgm_view(s, 149); }
        case 2: { static const char AZARAC_PROGMEM s[] = "Major Flooding - Extensive inundation of structures and roads. Significant evacuations of people and/or transfer of property to higher elevations."; return azarac_pgm_view(s, 146); }
        case 3: { static const char AZARAC_PROGMEM s[] = "Record Flooding"; return azarac_pgm_view(s, 15); }
        default: return std::nullopt;
    }
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d15_flood_severity_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return std::string_view{"Minor Flooding - Minimal or no property damage, but possibly some public threat.", 80};
        case 1: return std::string_view{"Moderate Flooding - Some inundation of structures and roads near stream. Some evacuations of people and/or transfer of property to higher elevations.", 149};
        case 2: return std::string_view{"Major Flooding - Extensive inundation of structures and roads. Significant evacuations of people and/or transfer of property to higher elevations.", 146};
        case 3: return std::string_view{"Record Flooding", 15};
        default: return std::nullopt;
    }
}
#endif

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
