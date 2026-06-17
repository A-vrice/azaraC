#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcr_jma_disaster_category
// Variable      : qzss_dcr_jma_disaster_category
// Entries       : 12
// Strategy      : array

#include <cstdint>
#include <optional>
#include <string_view>
#include "../azaraC.h"

namespace azaraC {
namespace def {

#if (AZARAC_LANG_JA)

inline constexpr std::optional<std::string_view> QZSS_DCR_JMA_DISASTER_CATEGORY_TABLE[] = {
    std::string_view{"緊急地震速報", 18},
    std::string_view{"震源", 6},
    std::string_view{"震度", 6},
    std::string_view{"南海トラフ地震", 21},
    std::string_view{"津波", 6},
    std::string_view{"北西太平洋津波", 21},
    std::nullopt,
    std::string_view{"火山", 6},
    std::string_view{"降灰", 6},
    std::string_view{"気象", 6},
    std::string_view{"洪水", 6},
    std::string_view{"台風", 6},
    std::nullopt,
    std::string_view{"海上", 6}
};
inline constexpr uint8_t QZSS_DCR_JMA_DISASTER_CATEGORY_BASE = 1;
inline constexpr uint8_t QZSS_DCR_JMA_DISASTER_CATEGORY_SIZE = 14;
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_disaster_category_lookup(uint8_t id) {
    if (id < QZSS_DCR_JMA_DISASTER_CATEGORY_BASE || id >= QZSS_DCR_JMA_DISASTER_CATEGORY_BASE + QZSS_DCR_JMA_DISASTER_CATEGORY_SIZE) return std::nullopt;
    return QZSS_DCR_JMA_DISASTER_CATEGORY_TABLE[id - QZSS_DCR_JMA_DISASTER_CATEGORY_BASE];
}

#else

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_disaster_category_lookup(uint8_t id) {
    (void)id;
    return std::nullopt;
}

#endif

} // namespace def
} // namespace azaraC
