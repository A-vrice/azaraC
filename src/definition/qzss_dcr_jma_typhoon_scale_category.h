#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcr_jma_typhoon_scale_category
// Variable      : qzss_dcr_jma_typhoon_scale_category
// Entries       : 4
// Strategy      : switch

#include <cstdint>
#include <optional>
#include <string_view>

namespace azaraC {
namespace def {

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_typhoon_scale_category_lookup(uint8_t id) {
    switch (id) {
        case 0: return std::string_view{"なし", 6};
        case 1: return std::string_view{"大型", 6};
        case 2: return std::string_view{"超大型", 9};
        case 15: return std::string_view{"その他の大きさ階級分類", 33};
        default: return std::nullopt;
    }
}

} // namespace def
} // namespace azaraC
