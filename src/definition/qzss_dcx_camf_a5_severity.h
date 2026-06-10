#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcx_camf_a5_severity
// Variable      : qzss_dcx_camf_a5_severity
// Entries       : 4
// Strategy      : switch

#include <cstdint>
#include <optional>
#include <string_view>

namespace azaraC {
namespace def {

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_a5_severity_lookup(uint8_t id) {
    switch (id) {
        case 0: return std::string_view{"Unknown", 7};
        case 1: return std::string_view{"Moderate - Possible threat to life or property", 46};
        case 2: return std::string_view{"Severe - Significant threat to life or property", 47};
        case 3: return std::string_view{"Extreme - Extraordinary threat to life or property", 50};
        default: return std::nullopt;
    }
}

} // namespace def
} // namespace azaraC
