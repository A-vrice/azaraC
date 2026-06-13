#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcx_camf_a3_provider_identifier
// Variable      : qzss_dcx_camf_a3_provider_identifier_australia
// Entries       : 12
// Strategy      : array

#include <cstdint>
#include <optional>
#include <string_view>
#include "../azaraC.h"

namespace azaraC {
namespace def {

inline constexpr std::optional<std::string_view> QZSS_DCX_CAMF_A3_PROVIDER_IDENTIFIER_AUSTRALIA_TABLE[] = {
    std::string_view{"National Emergency Management Agency", 36},
    std::string_view{"Bureau of Meteorology", 21},
    std::string_view{"Australian Climate Service", 26},
    std::string_view{"Geoscience Australia", 20},
    std::string_view{"Commonwealth Scientific and Industrial Research Organisation", 60},
    std::string_view{"Australian Bureau of Statistics", 31},
    std::string_view{"Resilience New South Wales", 26},
    std::string_view{"State Emergency Service New South Wales", 39},
    std::string_view{"New South Wales Rural Fire Service", 34},
    std::string_view{"Joint Australian Tsunami Warning Centre", 39},
    std::string_view{"Flood Knowledge Centre", 22},
    std::string_view{"Australian Broadcasting Corporation", 35}
};
inline constexpr uint8_t QZSS_DCX_CAMF_A3_PROVIDER_IDENTIFIER_AUSTRALIA_BASE = 1;
inline constexpr uint8_t QZSS_DCX_CAMF_A3_PROVIDER_IDENTIFIER_AUSTRALIA_SIZE = 12;
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_a3_provider_identifier_australia_lookup(uint8_t id) {
    if (id < QZSS_DCX_CAMF_A3_PROVIDER_IDENTIFIER_AUSTRALIA_BASE || id >= QZSS_DCX_CAMF_A3_PROVIDER_IDENTIFIER_AUSTRALIA_BASE + QZSS_DCX_CAMF_A3_PROVIDER_IDENTIFIER_AUSTRALIA_SIZE) return std::nullopt;
    return QZSS_DCX_CAMF_A3_PROVIDER_IDENTIFIER_AUSTRALIA_TABLE[id - QZSS_DCX_CAMF_A3_PROVIDER_IDENTIFIER_AUSTRALIA_BASE];
}

} // namespace def
} // namespace azaraC
