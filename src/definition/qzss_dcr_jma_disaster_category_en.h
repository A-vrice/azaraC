#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcr_jma_disaster_category
// Variable      : qzss_dcr_jma_disaster_category_en
// Entries       : 12
// Strategy      : array

#include <cstdint>
#include <optional>
#include <string_view>

namespace azaraC {
namespace def {

inline constexpr std::optional<std::string_view> QZSS_DCR_JMA_DISASTER_CATEGORY_EN_TABLE[] = {
    std::string_view{"Earthquake Early Warning", 24},
    std::string_view{"Hypocenter", 10},
    std::string_view{"Seismic Intensity", 17},
    std::string_view{"Nankai Trough Earthquake", 24},
    std::string_view{"Tsunami", 7},
    std::string_view{"Northwest Pacific Tsunami", 25},
    std::nullopt,
    std::string_view{"Volcano", 7},
    std::string_view{"Ash Fall", 8},
    std::string_view{"Weather", 7},
    std::string_view{"Flood", 5},
    std::string_view{"Typhoon", 7},
    std::nullopt,
    std::string_view{"Marine", 6}
};
inline constexpr uint8_t QZSS_DCR_JMA_DISASTER_CATEGORY_EN_BASE = 1;
inline constexpr uint8_t QZSS_DCR_JMA_DISASTER_CATEGORY_EN_SIZE = 14;
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_disaster_category_en_lookup(uint8_t id) {
    if (id < QZSS_DCR_JMA_DISASTER_CATEGORY_EN_BASE || id >= QZSS_DCR_JMA_DISASTER_CATEGORY_EN_BASE + QZSS_DCR_JMA_DISASTER_CATEGORY_EN_SIZE) return std::nullopt;
    return QZSS_DCR_JMA_DISASTER_CATEGORY_EN_TABLE[id - QZSS_DCR_JMA_DISASTER_CATEGORY_EN_BASE];
}

} // namespace def
} // namespace azaraC
