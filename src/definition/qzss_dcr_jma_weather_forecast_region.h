#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcr_jma_weather_forecast_region
// Variable      : qzss_dcr_jma_weather_forecast_region
// Entries       : 75
// Strategy      : binary_search

// NOTE: This function may return nullptr for unknown IDs.
// Callers MUST perform a null-check before using the result.

#include <cstdint>
#include <optional>
#include <string_view>
#include "../azaraC.h"

namespace azaraC {
namespace def {

#if (AZARAC_ENABLE_WEATHER)

struct QZSS_DCR_JMA_WEATHER_FORECAST_REGION_Entry { uint32_t id; std::optional<std::string_view> label; };
inline constexpr QZSS_DCR_JMA_WEATHER_FORECAST_REGION_Entry QZSS_DCR_JMA_WEATHER_FORECAST_REGION_TABLE[] = {
    {11000u, std::string_view{"宗谷地方", 4}},
    {12000u, std::string_view{"上川・留萌地方", 7}},
    {12010u, std::string_view{"上川地方", 4}},
    {12020u, std::string_view{"留萌地方", 4}},
    {13000u, std::string_view{"網走・北見・紋別地方", 10}},
    {14010u, std::string_view{"根室地方", 4}},
    {14020u, std::string_view{"釧路地方", 4}},
    {14030u, std::string_view{"十勝地方", 4}},
    {14100u, std::string_view{"釧路・根室地方", 7}},
    {15000u, std::string_view{"胆振・日高地方", 7}},
    {15010u, std::string_view{"胆振地方", 4}},
    {15020u, std::string_view{"日高地方", 4}},
    {16000u, std::string_view{"石狩・空知・後志地方", 10}},
    {16010u, std::string_view{"石狩地方", 4}},
    {16020u, std::string_view{"空知地方", 4}},
    {16030u, std::string_view{"後志地方", 4}},
    {16100u, std::string_view{"石狩・空知地方", 7}},
    {17000u, std::string_view{"渡島・檜山地方", 7}},
    {17010u, std::string_view{"渡島地方", 4}},
    {17020u, std::string_view{"檜山地方", 4}},
    {20000u, std::string_view{"青森県", 3}},
    {30000u, std::string_view{"岩手県", 3}},
    {40000u, std::string_view{"宮城県", 3}},
    {50000u, std::string_view{"秋田県", 3}},
    {60000u, std::string_view{"山形県", 3}},
    {70000u, std::string_view{"福島県", 3}},
    {80000u, std::string_view{"茨城県", 3}},
    {90000u, std::string_view{"栃木県", 3}},
    {100000u, std::string_view{"群馬県", 3}},
    {110000u, std::string_view{"埼玉県", 3}},
    {120000u, std::string_view{"千葉県", 3}},
    {130000u, std::string_view{"東京都", 3}},
    {130010u, std::string_view{"東京地方", 4}},
    {130020u, std::string_view{"伊豆諸島北部", 6}},
    {130030u, std::string_view{"伊豆諸島南部", 6}},
    {140000u, std::string_view{"神奈川県", 4}},
    {150000u, std::string_view{"新潟県", 3}},
    {160000u, std::string_view{"富山県", 3}},
    {170000u, std::string_view{"石川県", 3}},
    {180000u, std::string_view{"福井県", 3}},
    {190000u, std::string_view{"山梨県", 3}},
    {200000u, std::string_view{"長野県", 3}},
    {210000u, std::string_view{"岐阜県", 3}},
    {220000u, std::string_view{"静岡県", 3}},
    {230000u, std::string_view{"愛知県", 3}},
    {240000u, std::string_view{"三重県", 3}},
    {250000u, std::string_view{"滋賀県", 3}},
    {260000u, std::string_view{"京都府", 3}},
    {270000u, std::string_view{"大阪府", 3}},
    {280000u, std::string_view{"兵庫県", 3}},
    {290000u, std::string_view{"奈良県", 3}},
    {300000u, std::string_view{"和歌山県", 4}},
    {310000u, std::string_view{"鳥取県", 3}},
    {320000u, std::string_view{"島根県", 3}},
    {330000u, std::string_view{"岡山県", 3}},
    {340000u, std::string_view{"広島県", 3}},
    {350000u, std::string_view{"山口県", 3}},
    {360000u, std::string_view{"徳島県", 3}},
    {370000u, std::string_view{"香川県", 3}},
    {380000u, std::string_view{"愛媛県", 3}},
    {390000u, std::string_view{"高知県", 3}},
    {400000u, std::string_view{"福岡県", 3}},
    {410000u, std::string_view{"佐賀県", 3}},
    {420000u, std::string_view{"長崎県", 3}},
    {430000u, std::string_view{"熊本県", 3}},
    {440000u, std::string_view{"大分県", 3}},
    {450000u, std::string_view{"宮崎県", 3}},
    {460000u, std::string_view{"鹿児島県", 4}},
    {460040u, std::string_view{"奄美地方", 4}},
    {460100u, std::string_view{"鹿児島県(奄美地方除く)", 12}},
    {471000u, std::string_view{"沖縄本島地方", 6}},
    {472000u, std::string_view{"大東島地方", 5}},
    {473000u, std::string_view{"宮古島地方", 5}},
    {474000u, std::string_view{"八重山地方", 5}},
    {500000u, std::string_view{"その他の府県予報区", 9}},};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_weather_forecast_region_lookup(uint32_t id) noexcept {
    uint8_t lo = 0, hi = 75;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        if (QZSS_DCR_JMA_WEATHER_FORECAST_REGION_TABLE[mid].id == id) return QZSS_DCR_JMA_WEATHER_FORECAST_REGION_TABLE[mid].label;
        if (QZSS_DCR_JMA_WEATHER_FORECAST_REGION_TABLE[mid].id < id) lo = mid + 1;
        else hi = mid;
    }
    return std::nullopt;
}

#else

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_weather_forecast_region_lookup(uint32_t id) noexcept {
    (void)id;
    return std::nullopt;
}

#endif

} // namespace def
} // namespace azaraC
