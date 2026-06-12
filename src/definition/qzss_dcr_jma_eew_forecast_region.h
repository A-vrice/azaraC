#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcr_jma_eew_forecast_region
// Variable      : qzss_dcr_jma_eew_forecast_region
// Entries       : 71
// Strategy      : array

#include <cstdint>
#include <optional>
#include <string_view>
#include "../azaraC.h"

namespace azaraC {
namespace def {

#if (AZARAC_ENABLE_EEW)

inline constexpr std::optional<std::string_view> QZSS_DCR_JMA_EEW_FORECAST_REGION_TABLE[] = {
    std::string_view{"北海道道央", 15},
    std::string_view{"北海道道南", 15},
    std::string_view{"北海道道北", 15},
    std::string_view{"北海道道東", 15},
    std::string_view{"青森", 6},
    std::string_view{"岩手", 6},
    std::string_view{"宮城", 6},
    std::string_view{"秋田", 6},
    std::string_view{"山形", 6},
    std::string_view{"福島", 6},
    std::string_view{"茨城", 6},
    std::string_view{"栃木", 6},
    std::string_view{"群馬", 6},
    std::string_view{"埼玉", 6},
    std::string_view{"千葉", 6},
    std::string_view{"東京", 6},
    std::string_view{"伊豆諸島", 12},
    std::string_view{"小笠原", 9},
    std::string_view{"神奈川", 9},
    std::string_view{"新潟", 6},
    std::string_view{"富山", 6},
    std::string_view{"石川", 6},
    std::string_view{"福井", 6},
    std::string_view{"山梨", 6},
    std::string_view{"長野", 6},
    std::string_view{"岐阜", 6},
    std::string_view{"静岡", 6},
    std::string_view{"愛知", 6},
    std::string_view{"三重", 6},
    std::string_view{"滋賀", 6},
    std::string_view{"京都", 6},
    std::string_view{"大阪", 6},
    std::string_view{"兵庫", 6},
    std::string_view{"奈良", 6},
    std::string_view{"和歌山", 9},
    std::string_view{"鳥取", 6},
    std::string_view{"島根", 6},
    std::string_view{"岡山", 6},
    std::string_view{"広島", 6},
    std::string_view{"山口", 6},
    std::string_view{"徳島", 6},
    std::string_view{"香川", 6},
    std::string_view{"愛媛", 6},
    std::string_view{"高知", 6},
    std::string_view{"福岡", 6},
    std::string_view{"佐賀", 6},
    std::string_view{"長崎", 6},
    std::string_view{"熊本", 6},
    std::string_view{"大分", 6},
    std::string_view{"宮崎", 6},
    std::string_view{"鹿児島", 9},
    std::string_view{"奄美(群島)", 14},
    std::string_view{"沖縄本島", 12},
    std::string_view{"大東島", 9},
    std::string_view{"宮古島", 9},
    std::string_view{"八重山", 9},
    std::string_view{"北海道", 9},
    std::string_view{"東北", 6},
    std::string_view{"関東", 6},
    std::string_view{"伊豆諸島", 12},
    std::string_view{"小笠原", 9},
    std::string_view{"北陸", 6},
    std::string_view{"甲信", 6},
    std::string_view{"東海", 6},
    std::string_view{"近畿", 6},
    std::string_view{"中国", 6},
    std::string_view{"四国", 6},
    std::string_view{"九州", 6},
    std::string_view{"奄美(群島)", 14},
    std::string_view{"沖縄", 6},
    std::nullopt,
    std::nullopt,
    std::nullopt,
    std::nullopt,
    std::nullopt,
    std::nullopt,
    std::nullopt,
    std::nullopt,
    std::nullopt,
    std::string_view{"その他の府県予報区および地方予報区", 51}
};
inline constexpr uint8_t QZSS_DCR_JMA_EEW_FORECAST_REGION_BASE = 1;
inline constexpr uint8_t QZSS_DCR_JMA_EEW_FORECAST_REGION_SIZE = 80;
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_eew_forecast_region_lookup(uint8_t id) {
    if (id < QZSS_DCR_JMA_EEW_FORECAST_REGION_BASE || id >= QZSS_DCR_JMA_EEW_FORECAST_REGION_BASE + QZSS_DCR_JMA_EEW_FORECAST_REGION_SIZE) return std::nullopt;
    return QZSS_DCR_JMA_EEW_FORECAST_REGION_TABLE[id - QZSS_DCR_JMA_EEW_FORECAST_REGION_BASE];
}

#else

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_eew_forecast_region_lookup(uint8_t id) {
    (void)id;
    return std::nullopt;
}

#endif

} // namespace def
} // namespace azaraC
