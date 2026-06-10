#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcx_camf_a3_provider_identifier
// Variable      : qzss_dcx_camf_a3_provider_identifier_thailand
// Entries       : 13
// Strategy      : array

#include <cstdint>
#include <optional>
#include <string_view>

namespace azaraC {
namespace def {

inline constexpr std::optional<std::string_view> QZSS_DCX_CAMF_A3_PROVIDER_IDENTIFIER_THAILAND_TABLE[] = {
    std::string_view{"Department of Disaster Prevention and Mitigation", 48},
    std::string_view{"Thai Meteorological Department", 30},
    std::string_view{"National Disaster Warning Center", 32},
    std::string_view{"Department of Mineral Resources", 31},
    std::string_view{"Navy Hydrographic Department, Royal Thai Navy", 45},
    std::string_view{"Department of Water Resources", 29},
    std::string_view{"Royal Irrigation Department", 27},
    std::string_view{"Department of Pollution Control", 31},
    std::string_view{"Geo-Informatics and Space Technology Development Agency", 55},
    std::string_view{"Electricity Generating Authority of Thailand", 44},
    std::string_view{"Royal Forest Department", 23},
    std::string_view{"Department of Parks, Wildlife and Plant Conservation", 52},
    std::string_view{"Water Crisis Prevention Center", 30}
};
inline constexpr uint8_t QZSS_DCX_CAMF_A3_PROVIDER_IDENTIFIER_THAILAND_BASE = 1;
inline constexpr uint8_t QZSS_DCX_CAMF_A3_PROVIDER_IDENTIFIER_THAILAND_SIZE = 13;
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_a3_provider_identifier_thailand_lookup(uint8_t id) {
    if (id < QZSS_DCX_CAMF_A3_PROVIDER_IDENTIFIER_THAILAND_BASE || id >= QZSS_DCX_CAMF_A3_PROVIDER_IDENTIFIER_THAILAND_BASE + QZSS_DCX_CAMF_A3_PROVIDER_IDENTIFIER_THAILAND_SIZE) return std::nullopt;
    return QZSS_DCX_CAMF_A3_PROVIDER_IDENTIFIER_THAILAND_TABLE[id - QZSS_DCX_CAMF_A3_PROVIDER_IDENTIFIER_THAILAND_BASE];
}

} // namespace def
} // namespace azaraC
