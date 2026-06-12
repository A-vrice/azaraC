#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcr_jma_typhoon_intensity_category
// Variable      : qzss_dcr_jma_typhoon_intensity_category
// Entries       : 5
// Strategy      : switch

#include <cstdint>
#include <optional>
#include <string_view>
#include "../azaraC.h"

namespace azaraC {
namespace def {

#if (AZARAC_ENABLE_TYPHOON)

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_typhoon_intensity_category_lookup(uint8_t id) {
    switch (id) {
        case 0: return std::string_view{"なし", 6};
        case 1: return std::string_view{"強い", 6};
        case 2: return std::string_view{"非常に強い", 15};
        case 3: return std::string_view{"猛烈な", 9};
        case 15: return std::string_view{"その他の強さ階級分類", 30};
        default: return std::nullopt;
    }
}

#else

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_typhoon_intensity_category_lookup(uint8_t id) {
    (void)id;
    return std::nullopt;
}

#endif

} // namespace def
} // namespace azaraC
