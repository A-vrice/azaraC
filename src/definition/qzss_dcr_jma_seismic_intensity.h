#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcr_jma_seismic_intensity
// Variable      : qzss_dcr_jma_seismic_intensity
// Entries       : 7
// Strategy      : switch

#include <cstdint>
#include <optional>
#include <string_view>

namespace azaraC {
namespace def {

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_seismic_intensity_lookup(uint8_t id) {
    switch (id) {
        case 1: return std::string_view{"4未満", 7};
        case 2: return std::string_view{"4", 1};
        case 3: return std::string_view{"5弱", 4};
        case 4: return std::string_view{"5強", 4};
        case 5: return std::string_view{"6弱", 4};
        case 6: return std::string_view{"6強", 4};
        case 7: return std::string_view{"7", 1};
        default: return std::nullopt;
    }
}

} // namespace def
} // namespace azaraC
