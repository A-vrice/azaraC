#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcx_camf_a8_hazard_duration
// Variable      : qzss_dcx_camf_a8_hazard_duration
// Entries       : 4
// Strategy      : switch

#include <cstdint>
#include <optional>
#include <string_view>

namespace azaraC {
namespace def {

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_a8_hazard_duration_lookup(uint8_t id) {
    switch (id) {
        case 0: return std::string_view{"Unknown", 7};
        case 1: return std::string_view{"Duration < 6H", 13};
        case 2: return std::string_view{"6H <= Duration < 12H", 20};
        case 3: return std::string_view{"12H <= Duration < 24H", 21};
        default: return std::nullopt;
    }
}

} // namespace def
} // namespace azaraC
