#pragma once
// AUTO-GENERATED from azarashi 0.16.4 with CI-CD
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
#include "../internal/FlashString.h"

namespace azaraC {
namespace def {

#if (AZARAC_ENABLE_WEATHER)

#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCR_JMA_WEATHER_FORECAST_REGION_POOL[] = "宗谷地方\0上川・留萌地方\0上川地方\0留萌地方\0網走・北見・紋別地方\0根室地方\0釧路地方\0十勝地方\0釧路・根室地方\0胆振・日高地方\0胆振地方\0日高地方\0石狩・空知・後志地方\0石狩地方\0空知地方\0後志地方\0石狩・空知地方\0渡島・檜山地方\0渡島地方\0檜山地方\0青森県\0岩手県\0宮城県\0秋田県\0山形県\0福島県\0茨城県\0栃木県\0群馬県\0埼玉県\0千葉県\0東京都\0東京地方\0伊豆諸島北部\0伊豆諸島南部\0神奈川県\0新潟県\0富山県\0石川県\0福井県\0山梨県\0長野県\0岐阜県\0静岡県\0愛知県\0三重県\0滋賀県\0京都府\0大阪府\0兵庫県\0奈良県\0和歌山県\0鳥取県\0島根県\0岡山県\0広島県\0山口県\0徳島県\0香川県\0愛媛県\0高知県\0福岡県\0佐賀県\0長崎県\0熊本県\0大分県\0宮崎県\0鹿児島県\0奄美地方\0鹿児島県(奄美地方除く)\0沖縄本島地方\0大東島地方\0宮古島地方\0八重山地方\0その他の府県予報区\0";
struct QZSS_DCR_JMA_WEATHER_FORECAST_REGION_Entry { uint32_t id; uint16_t offset; uint16_t len; };
static const QZSS_DCR_JMA_WEATHER_FORECAST_REGION_Entry QZSS_DCR_JMA_WEATHER_FORECAST_REGION_TABLE[] AZARAC_PROGMEM = {
    {11000u, 0u, 12u},
    {12000u, 13u, 21u},
    {12010u, 35u, 12u},
    {12020u, 48u, 12u},
    {13000u, 61u, 30u},
    {14010u, 92u, 12u},
    {14020u, 105u, 12u},
    {14030u, 118u, 12u},
    {14100u, 131u, 21u},
    {15000u, 153u, 21u},
    {15010u, 175u, 12u},
    {15020u, 188u, 12u},
    {16000u, 201u, 30u},
    {16010u, 232u, 12u},
    {16020u, 245u, 12u},
    {16030u, 258u, 12u},
    {16100u, 271u, 21u},
    {17000u, 293u, 21u},
    {17010u, 315u, 12u},
    {17020u, 328u, 12u},
    {20000u, 341u, 9u},
    {30000u, 351u, 9u},
    {40000u, 361u, 9u},
    {50000u, 371u, 9u},
    {60000u, 381u, 9u},
    {70000u, 391u, 9u},
    {80000u, 401u, 9u},
    {90000u, 411u, 9u},
    {100000u, 421u, 9u},
    {110000u, 431u, 9u},
    {120000u, 441u, 9u},
    {130000u, 451u, 9u},
    {130010u, 461u, 12u},
    {130020u, 474u, 18u},
    {130030u, 493u, 18u},
    {140000u, 512u, 12u},
    {150000u, 525u, 9u},
    {160000u, 535u, 9u},
    {170000u, 545u, 9u},
    {180000u, 555u, 9u},
    {190000u, 565u, 9u},
    {200000u, 575u, 9u},
    {210000u, 585u, 9u},
    {220000u, 595u, 9u},
    {230000u, 605u, 9u},
    {240000u, 615u, 9u},
    {250000u, 625u, 9u},
    {260000u, 635u, 9u},
    {270000u, 645u, 9u},
    {280000u, 655u, 9u},
    {290000u, 665u, 9u},
    {300000u, 675u, 12u},
    {310000u, 688u, 9u},
    {320000u, 698u, 9u},
    {330000u, 708u, 9u},
    {340000u, 718u, 9u},
    {350000u, 728u, 9u},
    {360000u, 738u, 9u},
    {370000u, 748u, 9u},
    {380000u, 758u, 9u},
    {390000u, 768u, 9u},
    {400000u, 778u, 9u},
    {410000u, 788u, 9u},
    {420000u, 798u, 9u},
    {430000u, 808u, 9u},
    {440000u, 818u, 9u},
    {450000u, 828u, 9u},
    {460000u, 838u, 12u},
    {460040u, 851u, 12u},
    {460100u, 864u, 32u},
    {471000u, 897u, 18u},
    {472000u, 916u, 15u},
    {473000u, 932u, 15u},
    {474000u, 948u, 15u},
    {500000u, 964u, 27u},
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_weather_forecast_region_lookup(uint32_t id) noexcept {
    uint8_t lo = 0, hi = 75;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        const char* AZARAC_PROGMEM ep = reinterpret_cast<const char*>(&QZSS_DCR_JMA_WEATHER_FORECAST_REGION_TABLE[mid]);
        uint32_t eid = pgm_read_dword(ep + offsetof(QZSS_DCR_JMA_WEATHER_FORECAST_REGION_Entry, id));
        if (eid == id) {
            uint16_t off = pgm_read_word(ep + offsetof(QZSS_DCR_JMA_WEATHER_FORECAST_REGION_Entry, offset));
            uint16_t n = pgm_read_word(ep + offsetof(QZSS_DCR_JMA_WEATHER_FORECAST_REGION_Entry, len));
            if (n == 0) return std::nullopt;
            return azarac_pgm_view(QZSS_DCR_JMA_WEATHER_FORECAST_REGION_POOL + off, n);
        }
        if (eid < id) lo = static_cast<uint8_t>(mid + 1); else hi = mid;
    }
    return std::nullopt;
}
#else
struct QZSS_DCR_JMA_WEATHER_FORECAST_REGION_Entry { uint32_t id; std::optional<std::string_view> label; };
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
    {500000u, std::string_view{"その他の府県予報区", 27}},};
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
#endif

#else

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_weather_forecast_region_lookup(uint32_t id) noexcept {
    (void)id;
    return std::nullopt;
}

#endif

} // namespace def
} // namespace azaraC
