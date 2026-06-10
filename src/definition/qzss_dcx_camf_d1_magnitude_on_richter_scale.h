#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcx_camf_b4_lower_level_fields_tables
// Variable      : qzss_dcx_camf_d1_magnitude_on_richter_scale
// Entries       : 9
// Strategy      : switch

#include <cstdint>
#include <optional>
#include <string_view>

namespace azaraC {
namespace def {

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d1_magnitude_on_richter_scale_lookup(uint8_t id) {
    switch (id) {
        case 0: return std::string_view{"1.0-1.9 - Micro", 15};
        case 1: return std::string_view{"2.0-2.9 - Minor", 15};
        case 2: return std::string_view{"3.0-3.9 - Minor", 15};
        case 3: return std::string_view{"4.0-4.9 - Light", 15};
        case 4: return std::string_view{"5.0-5.9 - Moderate", 18};
        case 5: return std::string_view{"6.0-6.9 - Strong", 16};
        case 6: return std::string_view{"7.0-7.9 - Major", 15};
        case 7: return std::string_view{"8.0-8.9 - Great", 15};
        case 8: return std::string_view{"9.0 and greater - Great", 23};
        default: return std::nullopt;
    }
}

} // namespace def
} // namespace azaraC
