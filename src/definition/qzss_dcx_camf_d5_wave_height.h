#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcx_camf_b4_lower_level_fields_tables
// Variable      : qzss_dcx_camf_d5_wave_height
// Entries       : 8
// Strategy      : switch

// NOTE: This function may return nullptr for unknown IDs.
// Callers MUST perform a null-check before using the result.

#include <cstdint>
#include <optional>
#include <string_view>
#include "../azaraC.h"

namespace azaraC {
namespace def {

#if (AZARAC_ENABLE_DCX_CAMF)

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d5_wave_height_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return std::string_view{"H ≤ 0.5m", 8};
        case 1: return std::string_view{"0.5m < H ≤ 1.0m", 15};
        case 2: return std::string_view{"1.0m < H ≤ 1.5m", 15};
        case 3: return std::string_view{"1.5m < H ≤ 2.0m", 15};
        case 4: return std::string_view{"2.0m < H ≤ 3.0m", 15};
        case 5: return std::string_view{"3.0m < H ≤ 5.0m", 15};
        case 6: return std::string_view{"5.0m < H ≤ 10.0m", 16};
        case 7: return std::string_view{"H > 10.0m", 9};
        default: return std::nullopt;
    }
}

#else

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d5_wave_height_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}

#endif

} // namespace def
} // namespace azaraC
