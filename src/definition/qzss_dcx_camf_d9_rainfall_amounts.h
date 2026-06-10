#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcx_camf_b4_lower_level_fields_tables
// Variable      : qzss_dcx_camf_d9_rainfall_amounts
// Entries       : 8
// Strategy      : switch

#include <cstdint>
#include <optional>
#include <string_view>

namespace azaraC {
namespace def {

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d9_rainfall_amounts_lookup(uint8_t id) {
    switch (id) {
        case 0: return std::string_view{"p ≤ 2.5mm/h", 13};
        case 1: return std::string_view{"2.5mm/h < p ≤ 7.5mm/h", 23};
        case 2: return std::string_view{"7.5mm/h < p ≤ 10mm/h", 22};
        case 3: return std::string_view{"10mm/h < p ≤ 20mm/h", 21};
        case 4: return std::string_view{"20mm/h < p ≤ 30mm/h", 21};
        case 5: return std::string_view{"30mm/h < p ≤ 50mm/h", 21};
        case 6: return std::string_view{"50mm/h < p ≤ 80mm/h", 21};
        case 7: return std::string_view{"80mm/h < p", 10};
        default: return std::nullopt;
    }
}

} // namespace def
} // namespace azaraC
