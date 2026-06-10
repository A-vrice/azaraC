#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcr_jma_tsunami_height
// Variable      : qzss_dcr_jma_tsunami_height
// Entries       : 8
// Strategy      : switch

#include <cstdint>
#include <optional>
#include <string_view>

namespace azaraC {
namespace def {

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_tsunami_height_lookup(uint8_t id) {
    switch (id) {
        case 1: return std::string_view{"0.2m未満", 10};
        case 2: return std::string_view{"1m", 2};
        case 3: return std::string_view{"3m", 2};
        case 4: return std::string_view{"5m", 2};
        case 5: return std::string_view{"10m", 3};
        case 6: return std::string_view{"10m超", 6};
        case 14: return std::string_view{"不明", 6};
        case 15: return std::string_view{"その他の津波の高さ", 27};
        default: return std::nullopt;
    }
}

} // namespace def
} // namespace azaraC
