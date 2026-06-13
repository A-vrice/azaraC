#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcx_camf_b4_lower_level_fields_tables
// Variable      : qzss_dcx_camf_d5_wave_height
// Entries       : 8
// Strategy      : switch

#include <cstdint>
#include <optional>
#include <string_view>
#include "../azaraC.h"

namespace azaraC {
namespace def {

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d5_wave_height_lookup(uint8_t id) {
    switch (id) {
        case 0: return std::string_view{"H ≤ 0.5m", 10};
        case 1: return std::string_view{"0.5m < H ≤ 1.0m", 17};
        case 2: return std::string_view{"1.0m < H ≤ 1.5m", 17};
        case 3: return std::string_view{"1.5m < H ≤ 2.0m", 17};
        case 4: return std::string_view{"2.0m < H ≤ 3.0m", 17};
        case 5: return std::string_view{"3.0m < H ≤ 5.0m", 17};
        case 6: return std::string_view{"5.0m < H ≤ 10.0m", 18};
        case 7: return std::string_view{"H > 10.0m", 9};
        default: return std::nullopt;
    }
}

} // namespace def
} // namespace azaraC
