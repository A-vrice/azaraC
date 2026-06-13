#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcx_camf_b4_lower_level_fields_tables
// Variable      : qzss_dcx_camf_d24_water_quality
// Entries       : 6
// Strategy      : switch

#include <cstdint>
#include <optional>
#include <string_view>
#include "../azaraC.h"

namespace azaraC {
namespace def {

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d24_water_quality_lookup(uint8_t id) {
    switch (id) {
        case 0: return std::string_view{"Excellent water quality", 23};
        case 1: return std::string_view{"Good water quality", 18};
        case 2: return std::string_view{"Poor water quality", 18};
        case 3: return std::string_view{"Very poor water quality", 23};
        case 4: return std::string_view{"Suitable for drinking purposes", 30};
        case 5: return std::string_view{"Unsuitable for drinking purposes", 32};
        default: return std::nullopt;
    }
}

} // namespace def
} // namespace azaraC
