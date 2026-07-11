#pragma once
// AUTO-GENERATED from azarashi 0.16.4 with CI-CD
// Source module : qzss_dcr_jma_seismic_intensity_lower_limit
// Variable      : qzss_dcr_jma_seismic_intensity_lower_limit
// Entries       : 12
// Strategy      : array

// NOTE: This function may return nullptr for unknown IDs.
// Callers MUST perform a null-check before using the result.

#include <cstdint>
#include <optional>
#include <string_view>
#include "../azaraC_config.h"

namespace azaraC {
namespace def {

#if (AZARAC_ENABLE_EEW)

inline constexpr std::optional<std::string_view> QZSS_DCR_JMA_SEISMIC_INTENSITY_LOWER_LIMIT_TABLE[] = {
    std::string_view{"震度0", 7},
    std::string_view{"震度1", 7},
    std::string_view{"震度2", 7},
    std::string_view{"震度3", 7},
    std::string_view{"震度4", 7},
    std::string_view{"震度5弱", 10},
    std::string_view{"震度5強", 10},
    std::string_view{"震度6弱", 10},
    std::string_view{"震度6強", 10},
    std::string_view{"震度7", 7},
    std::nullopt,
    std::nullopt,
    std::nullopt,
    std::string_view{"なし", 6},
    std::string_view{"不明", 6}
};
inline constexpr uint8_t QZSS_DCR_JMA_SEISMIC_INTENSITY_LOWER_LIMIT_BASE = 1;
inline constexpr uint8_t QZSS_DCR_JMA_SEISMIC_INTENSITY_LOWER_LIMIT_SIZE = 15;
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_seismic_intensity_lower_limit_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCR_JMA_SEISMIC_INTENSITY_LOWER_LIMIT_BASE || id >= QZSS_DCR_JMA_SEISMIC_INTENSITY_LOWER_LIMIT_BASE + QZSS_DCR_JMA_SEISMIC_INTENSITY_LOWER_LIMIT_SIZE) return std::nullopt;
    return QZSS_DCR_JMA_SEISMIC_INTENSITY_LOWER_LIMIT_TABLE[id - QZSS_DCR_JMA_SEISMIC_INTENSITY_LOWER_LIMIT_BASE];
}

#else

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_seismic_intensity_lower_limit_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}

#endif

} // namespace def
} // namespace azaraC
