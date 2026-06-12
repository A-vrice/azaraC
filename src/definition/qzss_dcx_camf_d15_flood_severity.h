#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcx_camf_b4_lower_level_fields_tables
// Variable      : qzss_dcx_camf_d15_flood_severity
// Entries       : 4
// Strategy      : switch

#include <cstdint>
#include <optional>
#include <string_view>
#include "../azaraC.h"

namespace azaraC {
namespace def {

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d15_flood_severity_lookup(uint8_t id) {
    switch (id) {
        case 0: return std::string_view{"Minor Flooding - Minimal or no property damage, but possibly some public threat.", 80};
        case 1: return std::string_view{"Moderate Flooding - Some inundation of structures and roads near stream. Some evacuations of people and/or transfer of property to higher elevations.", 149};
        case 2: return std::string_view{"Major Flooding - Extensive inundation of structures and roads. Significant evacuations of people and/or transfer of property to higher elevations.", 146};
        case 3: return std::string_view{"Record Flooding", 15};
        default: return std::nullopt;
    }
}

} // namespace def
} // namespace azaraC
