#pragma once
// AUTO-GENERATED from azarashi 0.16.4 with CI-CD
// Source module : qzss_dcr_jma_disaster_category
// Variable      : qzss_dcr_jma_disaster_category_en
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

#if (AZARAC_LANG_EN)

inline constexpr const char* QZSS_DCR_JMA_DISASTER_CATEGORY_EN_TABLE[] = {
    "Earthquake Early Warning",
    "Hypocenter",
    "Seismic Intensity",
    "Nankai Trough Earthquake",
    "Tsunami",
    "Northwest Pacific Tsunami",
    nullptr,
    "Volcano",
    "Ash Fall",
    "Weather",
    "Flood",
    "Typhoon",
    nullptr,
    "Marine"
};
inline constexpr uint8_t QZSS_DCR_JMA_DISASTER_CATEGORY_EN_BASE = 1;
inline constexpr uint8_t QZSS_DCR_JMA_DISASTER_CATEGORY_EN_SIZE = 14;
[[nodiscard]] inline constexpr const char* qzss_dcr_jma_disaster_category_en_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCR_JMA_DISASTER_CATEGORY_EN_BASE || id >= QZSS_DCR_JMA_DISASTER_CATEGORY_EN_BASE + QZSS_DCR_JMA_DISASTER_CATEGORY_EN_SIZE) return nullptr;
    return QZSS_DCR_JMA_DISASTER_CATEGORY_EN_TABLE[id - QZSS_DCR_JMA_DISASTER_CATEGORY_EN_BASE];
}

#else

[[nodiscard]] inline constexpr const char* qzss_dcr_jma_disaster_category_en_lookup(uint8_t id) noexcept {
    (void)id;
    return nullptr;
}

#endif

} // namespace def
} // namespace azaraC
