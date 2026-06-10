#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcr_jma_long_period_ground_motion_upper_limit
// Variable      : qzss_dcr_jma_long_period_ground_motion_upper_limit
// Entries       : 8
// Strategy      : switch

#include <cstdint>
#include <optional>
#include <string_view>

namespace azaraC {
namespace def {

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_long_period_ground_motion_upper_limit_lookup(uint8_t id) {
    switch (id) {
        case 0: return std::string_view{"None", 4};
        case 1: return std::string_view{"長周期地震動階級1未満", 31};
        case 2: return std::string_view{"長周期地震動階級1", 25};
        case 3: return std::string_view{"長周期地震動階級2", 25};
        case 4: return std::string_view{"長周期地震動階級3", 25};
        case 5: return std::string_view{"長周期地震動階級4", 25};
        case 6: return std::string_view{"〜程度以上", 15};
        case 7: return std::string_view{"不明", 6};
        default: return std::nullopt;
    }
}

} // namespace def
} // namespace azaraC
