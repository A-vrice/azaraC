#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcx_camf_b4_lower_level_fields_tables
// Variable      : qzss_dcx_camf_d13_visibility
// Entries       : 10
// Strategy      : switch

#include <cstdint>
#include <optional>
#include <string_view>

namespace azaraC {
namespace def {

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d13_visibility_lookup(uint8_t id) {
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

} // namespace def
} // namespace azaraC
