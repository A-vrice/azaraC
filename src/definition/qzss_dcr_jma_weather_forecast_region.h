#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcr_jma_weather_forecast_region
// Variable      : qzss_dcr_jma_weather_forecast_region
// Entries       : 75
// Strategy      : binary_search

#include <cstdint>
#include <optional>
#include <string_view>

namespace azaraC {
namespace def {

struct QZSS_DCR_JMA_WEATHER_FORECAST_REGION_Entry { uint32_t id; std::string_view label; };
inline constexpr QZSS_DCR_JMA_WEATHER_FORECAST_REGION_Entry QZSS_DCR_JMA_WEATHER_FORECAST_REGION_TABLE[] = {
    {11000u, std::string_view{"宗谷地方", 12}},

    {12000u, std::string_view{"上川・留萌地方", 21}},

    {12010u, std::string_view{"上川地方", 12}},

    {12020u, std::string_view{"留萌地方", 12}},

    {13000u, std::string_view{"網走・北見・紋別地方", 30}},

    {14010u, std::string_view{"根室地方", 12}},

    {14020u, std::string_view{"釧路地方", 12}},

    {14030u, std::string_view{"十勝地方", 12}},

    {14100u, std::string_view{"釧路・根室地方", 21}},

    {15000u, std::string_view{"胆振・日高地方", 21}},

    {15010u, std::string_view{"胆振地方", 12}},

    {15020u, std::string_view{"日高地方", 12}},

    {16000u, std::string_view{"石狩・空知・後志地方", 30}},

    {16010u, std::string_view{"石狩地方", 12}},

    {16020u, std::string_view{"空知地方", 12}},

    {16030u, std::string_view{"後志地方", 12}},

    {16100u, std::string_view{"石狩・空知地方", 21}},

    {17000u, std::string_view{"渡島・檜山地方", 21}},

    {17010u, std::string_view{"渡島地方", 12}},

    {17020u, std::string_view{"檜山地方", 12}},

    {20000u, std::string_view{"青森県", 9}},

    {30000u, std::string_view{"岩手県", 9}},

    {40000u, std::string_view{"宮城県", 9}},

    {50000u, std::string_view{"秋田県", 9}},

    {60000u, std::string_view{"山形県", 9}},

    {70000u, std::string_view{"福島県", 9}},

    {80000u, std::string_view{"茨城県", 9}},

    {90000u, std::string_view{"栃木県", 9}},

    {100000u, std::string_view{"群馬県", 9}},

    {110000u, std::string_view{"埼玉県", 9}},

    {120000u, std::string_view{"千葉県", 9}},

    {130000u, std::string_view{"東京都", 9}},

    {130010u, std::string_view{"東京地方", 12}},

    {130020u, std::string_view{"伊豆諸島北部", 18}},

    {130030u, std::string_view{"伊豆諸島南部", 18}},

    {140000u, std::string_view{"神奈川県", 12}},

    {150000u, std::string_view{"新潟県", 9}},

    {160000u, std::string_view{"富山県", 9}},

    {170000u, std::string_view{"石川県", 9}},

    {180000u, std::string_view{"福井県", 9}},

    {190000u, std::string_view{"山梨県", 9}},

    {200000u, std::string_view{"長野県", 9}},

    {210000u, std::string_view{"岐阜県", 9}},

    {220000u, std::string_view{"静岡県", 9}},

    {230000u, std::string_view{"愛知県", 9}},

    {240000u, std::string_view{"三重県", 9}},

    {250000u, std::string_view{"滋賀県", 9}},

    {260000u, std::string_view{"京都府", 9}},

    {270000u, std::string_view{"大阪府", 9}},

    {280000u, std::string_view{"兵庫県", 9}},

    {290000u, std::string_view{"奈良県", 9}},

    {300000u, std::string_view{"和歌山県", 12}},

    {310000u, std::string_view{"鳥取県", 9}},

    {320000u, std::string_view{"島根県", 9}},

    {330000u, std::string_view{"岡山県", 9}},

    {340000u, std::string_view{"広島県", 9}},

    {350000u, std::string_view{"山口県", 9}},

    {360000u, std::string_view{"徳島県", 9}},

    {370000u, std::string_view{"香川県", 9}},

    {380000u, std::string_view{"愛媛県", 9}},

    {390000u, std::string_view{"高知県", 9}},

    {400000u, std::string_view{"福岡県", 9}},

    {410000u, std::string_view{"佐賀県", 9}},

    {420000u, std::string_view{"長崎県", 9}},

    {430000u, std::string_view{"熊本県", 9}},

    {440000u, std::string_view{"大分県", 9}},

    {450000u, std::string_view{"宮崎県", 9}},

    {460000u, std::string_view{"鹿児島県", 12}},

    {460040u, std::string_view{"奄美地方", 12}},

    {460100u, std::string_view{"鹿児島県(奄美地方除く)", 32}},

    {471000u, std::string_view{"沖縄本島地方", 18}},

    {472000u, std::string_view{"大東島地方", 15}},

    {473000u, std::string_view{"宮古島地方", 15}},

    {474000u, std::string_view{"八重山地方", 15}},

    {500000u, std::string_view{"その他の府県予報区", 27}},
};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_weather_forecast_region_lookup(uint32_t id) {
    uint8_t lo = 0, hi = 75;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        if (QZSS_DCR_JMA_WEATHER_FORECAST_REGION_TABLE[mid].id == id) return QZSS_DCR_JMA_WEATHER_FORECAST_REGION_TABLE[mid].label;
        if (QZSS_DCR_JMA_WEATHER_FORECAST_REGION_TABLE[mid].id < id) lo = mid + 1;
        else hi = mid;
    }
    return std::nullopt;
}

} // namespace def
} // namespace azaraC
