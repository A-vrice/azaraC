#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcr_jma_eew_forecast_region
// Variable      : qzss_dcr_jma_eew_forecast_region
// Entries       : 71
// Strategy      : array

// NOTE: This function may return nullptr for unknown IDs.
// Callers MUST perform a null-check before using the result.

#include <cstdint>
#include <optional>
#include <string_view>
#include "../azaraC.h"

namespace azaraC {
namespace def {

#if (AZARAC_ENABLE_EEW)

inline constexpr std::optional<std::string_view> QZSS_DCR_JMA_EEW_FORECAST_REGION_TABLE[] = {
    std::string_view{"北海道道央", 5},
    std::string_view{"北海道道南", 5},
    std::string_view{"北海道道北", 5},
    std::string_view{"北海道道東", 5},
    std::string_view{"青森", 2},
    std::string_view{"岩手", 2},
    std::string_view{"宮城", 2},
    std::string_view{"秋田", 2},
    std::string_view{"山形", 2},
    std::string_view{"福島", 2},
    std::string_view{"茨城", 2},
    std::string_view{"栃木", 2},
    std::string_view{"群馬", 2},
    std::string_view{"埼玉", 2},
    std::string_view{"千葉", 2},
    std::string_view{"東京", 2},
    std::string_view{"伊豆諸島", 4},
    std::string_view{"小笠原", 3},
    std::string_view{"神奈川", 3},
    std::string_view{"新潟", 2},
    std::string_view{"富山", 2},
    std::string_view{"石川", 2},
    std::string_view{"福井", 2},
    std::string_view{"山梨", 2},
    std::string_view{"長野", 2},
    std::string_view{"岐阜", 2},
    std::string_view{"静岡", 2},
    std::string_view{"愛知", 2},
    std::string_view{"三重", 2},
    std::string_view{"滋賀", 2},
    std::string_view{"京都", 2},
    std::string_view{"大阪", 2},
    std::string_view{"兵庫", 2},
    std::string_view{"奈良", 2},
    std::string_view{"和歌山", 3},
    std::string_view{"鳥取", 2},
    std::string_view{"島根", 2},
    std::string_view{"岡山", 2},
    std::string_view{"広島", 2},
    std::string_view{"山口", 2},
    std::string_view{"徳島", 2},
    std::string_view{"香川", 2},
    std::string_view{"愛媛", 2},
    std::string_view{"高知", 2},
    std::string_view{"福岡", 2},
    std::string_view{"佐賀", 2},
    std::string_view{"長崎", 2},
    std::string_view{"熊本", 2},
    std::string_view{"大分", 2},
    std::string_view{"宮崎", 2},
    std::string_view{"鹿児島", 3},
    std::string_view{"奄美(群島)", 6},
    std::string_view{"沖縄本島", 4},
    std::string_view{"大東島", 3},
    std::string_view{"宮古島", 3},
    std::string_view{"八重山", 3},
    std::string_view{"北海道", 3},
    std::string_view{"東北", 2},
    std::string_view{"関東", 2},
    std::string_view{"伊豆諸島", 4},
    std::string_view{"小笠原", 3},
    std::string_view{"北陸", 2},
    std::string_view{"甲信", 2},
    std::string_view{"東海", 2},
    std::string_view{"近畿", 2},
    std::string_view{"中国", 2},
    std::string_view{"四国", 2},
    std::string_view{"九州", 2},
    std::string_view{"奄美(群島)", 6},
    std::string_view{"沖縄", 2},
    std::nullopt,
    std::nullopt,
    std::nullopt,
    std::nullopt,
    std::nullopt,
    std::nullopt,
    std::nullopt,
    std::nullopt,
    std::nullopt,
    std::string_view{"その他の府県予報区および地方予報区", 17}
};
inline constexpr uint8_t QZSS_DCR_JMA_EEW_FORECAST_REGION_BASE = 1;
inline constexpr uint8_t QZSS_DCR_JMA_EEW_FORECAST_REGION_SIZE = 80;
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_eew_forecast_region_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCR_JMA_EEW_FORECAST_REGION_BASE || id >= QZSS_DCR_JMA_EEW_FORECAST_REGION_BASE + QZSS_DCR_JMA_EEW_FORECAST_REGION_SIZE) return std::nullopt;
    return QZSS_DCR_JMA_EEW_FORECAST_REGION_TABLE[id - QZSS_DCR_JMA_EEW_FORECAST_REGION_BASE];
}

#else

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_eew_forecast_region_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}

#endif

} // namespace def
} // namespace azaraC
