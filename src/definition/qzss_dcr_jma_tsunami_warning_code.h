#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcr_jma_tsunami_warning_code
// Variable      : qzss_dcr_jma_tsunami_warning_code
// Entries       : 6
// Strategy      : switch

#include <cstdint>
#include <optional>
#include <string_view>

namespace azaraC {
namespace def {

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_tsunami_warning_code_lookup(uint8_t id) {
    switch (id) {
        case 1: return std::string_view{"津波なし", 12};
        case 2: return std::string_view{"警報解除", 12};
        case 3: return std::string_view{"津波警報", 12};
        case 4: return std::string_view{"大津波警報", 15};
        case 5: return std::string_view{"大津波警報：発表", 24};
        case 15: return std::string_view{"その他の警報", 18};
        default: return std::nullopt;
    }
}

} // namespace def
} // namespace azaraC
