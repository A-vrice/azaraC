#pragma once
// AUTO-GENERATED from azarashi 0.16.4 with CI-CD
// Source module : qzss_dcr_jma_disaster_category
// Variable      : qzss_dcr_jma_disaster_category
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

#if (AZARAC_LANG_JA)

inline constexpr const char* QZSS_DCR_JMA_DISASTER_CATEGORY_TABLE[] = {
    "緊急地震速報",
    "震源",
    "震度",
    "南海トラフ地震",
    "津波",
    "北西太平洋津波",
    nullptr,
    "火山",
    "降灰",
    "気象",
    "洪水",
    "台風",
    nullptr,
    "海上"
};
inline constexpr uint8_t QZSS_DCR_JMA_DISASTER_CATEGORY_BASE = 1;
inline constexpr uint8_t QZSS_DCR_JMA_DISASTER_CATEGORY_SIZE = 14;
[[nodiscard]] inline constexpr const char* qzss_dcr_jma_disaster_category_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCR_JMA_DISASTER_CATEGORY_BASE || id >= QZSS_DCR_JMA_DISASTER_CATEGORY_BASE + QZSS_DCR_JMA_DISASTER_CATEGORY_SIZE) return nullptr;
    return QZSS_DCR_JMA_DISASTER_CATEGORY_TABLE[id - QZSS_DCR_JMA_DISASTER_CATEGORY_BASE];
}

#else

[[nodiscard]] inline constexpr const char* qzss_dcr_jma_disaster_category_lookup(uint8_t id) noexcept {
    (void)id;
    return nullptr;
}

#endif

} // namespace def
} // namespace azaraC
