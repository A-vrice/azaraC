#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcx_camf_b4_lower_level_fields_tables
// Variable      : qzss_dcx_camf_d6_temperature_range
// Entries       : 16
// Strategy      : array

#include <cstdint>
#include <optional>
#include <string_view>

namespace azaraC {
namespace def {

inline constexpr std::optional<std::string_view> QZSS_DCX_CAMF_D6_TEMPERATURE_RANGE_TABLE[] = {
    std::string_view{"T ≤ -30°C", 12},
    std::string_view{"-30°C < T ≤ -25°C", 21},
    std::string_view{"-25°C < T ≤ -20°C", 21},
    std::string_view{"-20°C < T ≤ -15°C", 21},
    std::string_view{"-15°C < T ≤ -10°C", 21},
    std::string_view{"-10°C < T ≤ -5°C", 20},
    std::string_view{"-5°C < T ≤ 0°C", 18},
    std::string_view{"0°C < T ≤ 5°C", 17},
    std::string_view{"5°C < T ≤ 10°C", 18},
    std::string_view{"10°C < T ≤ 15°C", 19},
    std::string_view{"15°C < T ≤ 20°C", 19},
    std::string_view{"20°C < T ≤ 25°C", 19},
    std::string_view{"25°C < T ≤ 30°C", 19},
    std::string_view{"30°C < T ≤ 35°C", 19},
    std::string_view{"35°C < T ≤ 45°C", 19},
    std::string_view{"T > 45°C", 9}
};
inline constexpr uint8_t QZSS_DCX_CAMF_D6_TEMPERATURE_RANGE_BASE = 0;
inline constexpr uint8_t QZSS_DCX_CAMF_D6_TEMPERATURE_RANGE_SIZE = 16;
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d6_temperature_range_lookup(uint8_t id) {
    if (id < QZSS_DCX_CAMF_D6_TEMPERATURE_RANGE_BASE || id >= QZSS_DCX_CAMF_D6_TEMPERATURE_RANGE_BASE + QZSS_DCX_CAMF_D6_TEMPERATURE_RANGE_SIZE) return std::nullopt;
    return QZSS_DCX_CAMF_D6_TEMPERATURE_RANGE_TABLE[id - QZSS_DCX_CAMF_D6_TEMPERATURE_RANGE_BASE];
}

} // namespace def
} // namespace azaraC
