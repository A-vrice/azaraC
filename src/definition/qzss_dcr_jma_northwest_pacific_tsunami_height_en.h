#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcr_jma_northwest_pacific_tsunami_height
// Variable      : qzss_dcr_jma_northwest_pacific_tsunami_height_en
// Entries       : 8
// Strategy      : switch

#include <cstdint>
#include <optional>
#include <string_view>

namespace azaraC {
namespace def {

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_northwest_pacific_tsunami_height_en_lookup(uint16_t id) {
    switch (id) {
        case 1: return std::string_view{"0.3m~1m", 7};
        case 2: return std::string_view{"1m~3m", 5};
        case 3: return std::string_view{"3m~5m", 5};
        case 4: return std::string_view{"5m~10m", 6};
        case 508: return std::string_view{"More than 10m", 13};
        case 509: return std::string_view{"Huge", 4};
        case 510: return std::string_view{"High", 4};
        case 511: return std::string_view{"Unknown", 7};
        default: return std::nullopt;
    }
}

} // namespace def
} // namespace azaraC
