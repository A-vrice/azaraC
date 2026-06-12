#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcx_camf_b4_lower_level_fields_tables
// Variable      : qzss_dcx_camf_d3_azimuth_from_centre_of_main_ellipse_to_epicentre
// Entries       : 16
// Strategy      : array

#include <cstdint>
#include <optional>
#include <string_view>
#include "../azaraC.h"

namespace azaraC {
namespace def {

inline constexpr std::optional<std::string_view> QZSS_DCX_CAMF_D3_AZIMUTH_FROM_CENTRE_OF_MAIN_ELLIPSE_TO_EPICENTRE_TABLE[] = {
    std::string_view{"0.0", 3},
    std::string_view{"22.5", 4},
    std::string_view{"45.0", 4},
    std::string_view{"67.5", 4},
    std::string_view{"90.0", 4},
    std::string_view{"112.5", 5},
    std::string_view{"135.0", 5},
    std::string_view{"157.5", 5},
    std::string_view{"180.0", 5},
    std::string_view{"202.5", 5},
    std::string_view{"225.0", 5},
    std::string_view{"247.5", 5},
    std::string_view{"270.0", 5},
    std::string_view{"292.5", 5},
    std::string_view{"315.0", 5},
    std::string_view{"337.5", 5}
};
inline constexpr uint8_t QZSS_DCX_CAMF_D3_AZIMUTH_FROM_CENTRE_OF_MAIN_ELLIPSE_TO_EPICENTRE_BASE = 0;
inline constexpr uint8_t QZSS_DCX_CAMF_D3_AZIMUTH_FROM_CENTRE_OF_MAIN_ELLIPSE_TO_EPICENTRE_SIZE = 16;
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d3_azimuth_from_centre_of_main_ellipse_to_epicentre_lookup(uint8_t id) {
    if (id < QZSS_DCX_CAMF_D3_AZIMUTH_FROM_CENTRE_OF_MAIN_ELLIPSE_TO_EPICENTRE_BASE || id >= QZSS_DCX_CAMF_D3_AZIMUTH_FROM_CENTRE_OF_MAIN_ELLIPSE_TO_EPICENTRE_BASE + QZSS_DCX_CAMF_D3_AZIMUTH_FROM_CENTRE_OF_MAIN_ELLIPSE_TO_EPICENTRE_SIZE) return std::nullopt;
    return QZSS_DCX_CAMF_D3_AZIMUTH_FROM_CENTRE_OF_MAIN_ELLIPSE_TO_EPICENTRE_TABLE[id - QZSS_DCX_CAMF_D3_AZIMUTH_FROM_CENTRE_OF_MAIN_ELLIPSE_TO_EPICENTRE_BASE];
}

} // namespace def
} // namespace azaraC
