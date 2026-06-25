#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcr_jma_long_period_ground_motion_lower_limit
// Variable      : qzss_dcr_jma_long_period_ground_motion_lower_limit
// Entries       : 7
// Strategy      : switch

// NOTE: This function may return nullptr for unknown IDs.
// Callers MUST perform a null-check before using the result.

#include <cstdint>
#include <optional>
#include <string_view>
#include "../azaraC.h"

namespace azaraC {
namespace def {

#if (AZARAC_ENABLE_EEW)

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_long_period_ground_motion_lower_limit_lookup(uint8_t id) noexcept {
    switch (id) {
        case 1: return std::string_view{"長周期地震動階級1未満", 31};
        case 2: return std::string_view{"長周期地震動階級1", 25};
        case 3: return std::string_view{"長周期地震動階級2", 25};
        case 4: return std::string_view{"長周期地震動階級3", 25};
        case 5: return std::string_view{"長周期地震動階級4", 25};
        case 7: return std::string_view{"不明", 6};
        default: return std::nullopt;
    }
}

#else

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_long_period_ground_motion_lower_limit_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}

#endif

} // namespace def
} // namespace azaraC
