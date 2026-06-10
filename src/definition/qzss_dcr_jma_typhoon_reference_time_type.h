#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcr_jma_typhoon_reference_time_type
// Variable      : qzss_dcr_jma_typhoon_reference_time_type
// Entries       : 3
// Strategy      : switch

#include <cstdint>
#include <optional>
#include <string_view>

namespace azaraC {
namespace def {

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_typhoon_reference_time_type_lookup(uint8_t id) {
    switch (id) {
        case 1: return std::string_view{"実況", 6};
        case 2: return std::string_view{"推定", 6};
        case 3: return std::string_view{"予報", 6};
        default: return std::nullopt;
    }
}

} // namespace def
} // namespace azaraC
