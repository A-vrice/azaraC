#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcr_jma_flood_warning_level
// Variable      : qzss_dcr_jma_flood_warning_level
// Entries       : 5
// Strategy      : switch

#include <cstdint>
#include <optional>
#include <string_view>

namespace azaraC {
namespace def {

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_flood_warning_level_lookup(uint8_t id) {
    switch (id) {
        case 1: return std::string_view{"警報解除", 12};
        case 2: return std::string_view{"氾濫警戒情報", 18};
        case 3: return std::string_view{"氾濫危険情報", 18};
        case 4: return std::string_view{"氾濫発生情報", 18};
        case 15: return std::string_view{"その他の警戒レベル", 27};
        default: return std::nullopt;
    }
}

} // namespace def
} // namespace azaraC
