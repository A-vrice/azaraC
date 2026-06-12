#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcx_camf_b4_lower_level_fields_tables
// Variable      : qzss_dcx_camf_d36_typhoon_category
// Entries       : 5
// Strategy      : switch

#include <cstdint>
#include <optional>
#include <string_view>
#include "../azaraC.h"

namespace azaraC {
namespace def {

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d36_typhoon_category_lookup(uint8_t id) {
    switch (id) {
        case 0: return std::string_view{"Scale 1 and Intensity 1", 23};
        case 1: return std::string_view{"Scale 1 and Intensity 2", 23};
        case 2: return std::string_view{"Scale 1 and Intensity 3", 23};
        case 3: return std::string_view{"Scale 2 and Intensity 1", 23};
        case 4: return std::string_view{"Scale 2 and Intensity 2", 23};
        default: return std::nullopt;
    }
}

} // namespace def
} // namespace azaraC
