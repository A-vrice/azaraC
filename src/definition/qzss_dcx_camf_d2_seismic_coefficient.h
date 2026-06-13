#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcx_camf_b4_lower_level_fields_tables
// Variable      : qzss_dcx_camf_d2_seismic_coefficient
// Entries       : 8
// Strategy      : switch

#include <cstdint>
#include <optional>
#include <string_view>
#include "../azaraC.h"

namespace azaraC {
namespace def {

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d2_seismic_coefficient_lookup(uint8_t id) {
    switch (id) {
        case 0: return std::string_view{"2", 1};
        case 1: return std::string_view{"3", 1};
        case 2: return std::string_view{"4", 1};
        case 3: return std::string_view{"5 weak", 6};
        case 4: return std::string_view{"5 strong", 8};
        case 5: return std::string_view{"6 weak", 6};
        case 6: return std::string_view{"6 strong", 8};
        case 7: return std::string_view{"7", 1};
        default: return std::nullopt;
    }
}

} // namespace def
} // namespace azaraC
