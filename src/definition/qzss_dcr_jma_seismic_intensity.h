#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcr_jma_seismic_intensity
// Variable      : qzss_dcr_jma_seismic_intensity
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

#if (AZARAC_ENABLE_SEISMIC)

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_seismic_intensity_lookup(uint8_t id) noexcept {
    switch (id) {
        case 1: return std::string_view{"4未満", 3};
        case 2: return std::string_view{"4", 1};
        case 3: return std::string_view{"5弱", 2};
        case 4: return std::string_view{"5強", 2};
        case 5: return std::string_view{"6弱", 2};
        case 6: return std::string_view{"6強", 2};
        case 7: return std::string_view{"7", 1};
        default: return std::nullopt;
    }
}

#else

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_seismic_intensity_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}

#endif

} // namespace def
} // namespace azaraC
