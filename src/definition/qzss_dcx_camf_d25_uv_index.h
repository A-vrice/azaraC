#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcx_camf_b4_lower_level_fields_tables
// Variable      : qzss_dcx_camf_d25_uv_index
// Entries       : 10
// Strategy      : switch

#include <cstdint>
#include <optional>
#include <string_view>

namespace azaraC {
namespace def {

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d25_uv_index_lookup(uint8_t id) {
    switch (id) {
        case 0: return std::string_view{"Index 0 - 2 Low. No protection needed. You can safely stay outside using minimal sun protection.", 96};
        case 1: return std::string_view{"Index 3/11 Moderate. Protection needed. Seek shade during late morning through mid-afternoon. When outside, generously apply broad-spectrum SPF-15 or higher sunscreen on exposed skin, and wear protective clothing, a wide-brimmed hat, and sunglasses.", 249};
        case 2: return std::string_view{"Index 4/11 Moderate. Protection needed. Seek shade during late morning through mid-afternoon. When outside, generously apply broad-spectrum SPF-15 or higher sunscreen on exposed skin, and wear protective clothing, a wide-brimmed hat, and sunglasses.", 249};
        case 3: return std::string_view{"Index 5/11 High. Protection needed. Seek shade during late morning through mid-afternoon. When outside, generously apply broad-spectrum SPF-15 or higher sunscreen on exposed skin, and wear protective clothing, a wide-brimmed hat, and sunglasses.", 245};
        case 4: return std::string_view{"Index 6/11 High. Protection needed. Seek shade during late morning through mid-afternoon. When outside, generously apply broad-spectrum SPF-15 or higher sunscreen on exposed skin, and wear protective clothing, a wide-brimmed hat, and sunglasses.", 245};
        case 5: return std::string_view{"Index 7/11 High. Protection needed. Seek shade during late morning through mid-afternoon. When outside, generously apply broad-spectrum SPF-15 or higher sunscreen on exposed skin, and wear protective clothing, a wide-brimmed hat, and sunglasses.", 245};
        case 6: return std::string_view{"Index 8/11 Very high. Extra protection needed. Be careful outside, especially during late morning through mid-afternoon. If your shadow is shorter than you, seek shade and wear protective clothing, a wide-brimmed hat, and sunglasses, and generously apply a minimum of SPF-15, broad-spectrum sunscreen on exposed skin.", 317};
        case 7: return std::string_view{"Index 9/11 Very high. Extra protection needed. Be careful outside, especially during late morning through mid-afternoon. If your shadow is shorter than you, seek shade and wear protective clothing, a wide-brimmed hat, and sunglasses, and generously apply a minimum of SPF-15, broad-spectrum sunscreen on exposed skin.", 317};
        case 8: return std::string_view{"Index 10/11 Extreme. Extra protection needed. Be careful outside, especially during late morning through mid-afternoon. If your shadow is shorter than you, seek shade and wear protective clothing, a wide-brimmed hat, and sunglasses, and generously apply a minimum of SPF-15, broad-spectrum sunscreen on exposed skin.", 316};
        case 9: return std::string_view{"Index 11/11 Extreme. Extra protection needed. Be careful outside, especially during late morning through mid-afternoon. If your shadow is shorter than you, seek shade and wear protective clothing, a wide-brimmed hat, and sunglasses, and generously apply a minimum of SPF-15, broad-spectrum sunscreen on exposed skin.", 316};
        default: return std::nullopt;
    }
}

} // namespace def
} // namespace azaraC
