#pragma once
// AUTO-GENERATED from azarashi 0.16.4 with CI-CD
// Source module : qzss_dcr_jma_weather_forecast_region
// Variable      : qzss_dcr_jma_weather_forecast_region
// Entries       : 75
// Strategy      : binary_search

// NOTE: This function may return nullptr for unknown IDs.
// Callers MUST perform a null-check before using the result.

#if defined(__AVR__)
#include "../internal/avr_std/cstdint"
#include "../internal/avr_std/optional"
#include "../internal/avr_std/string_view"
#else
#include <cstdint>
#include <optional>
#include <string_view>
#endif
#include "../azaraC.h"
#include "../internal/FlashString.h"

namespace azaraC {
namespace def {

#if (AZARAC_ENABLE_WEATHER)

#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCR_JMA_WEATHER_FORECAST_REGION_POOL[] = "宗谷地方\000上川・留萌地方\000上川地方\000留萌地方\000網走・北見・紋別地方\000根室地方\000釧路地方\000十勝地方\000釧路・根室地方\000胆振・日高地方\000胆振地方\000日高地方\000石狩・空知・後志地方\000石狩地方\000空知地方\000後志地方\000石狩・空知地方\000渡島・檜山地方\000渡島地方\000檜山地方\000青森県\000岩手県\000宮城県\000秋田県\000山形県\000福島県\000茨城県\000栃木県\000群馬県\000埼玉県\000千葉県\000東京都\000東京地方\000伊豆諸島北部\000伊豆諸島南部\000神奈川県\000新潟県\000富山県\000石川県\000福井県\000山梨県\000長野県\000岐阜県\000静岡県\000愛知県\000三重県\000滋賀県\000京都府\000大阪府\000兵庫県\000奈良県\000和歌山県\000鳥取県\000島根県\000岡山県\000広島県\000山口県\000徳島県\000香川県\000愛媛県\000高知県\000福岡県\000佐賀県\000長崎県\000熊本県\000大分県\000宮崎県\000鹿児島県\000奄美地方\000鹿児島県(奄美地方除く)\000沖縄本島地方\000大東島地方\000宮古島地方\000八重山地方\000その他の府県予報区\000";
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
            return azarac_pgm_view(QZSS_DCR_JMA_WEATHER_FORECAST_REGION_POOL + off, n);
        }
        if (eid < id) lo = static_cast<uint8_t>(mid + 1); else hi = mid;
    }
    return std::nullopt;
}
#else
struct QZSS_DCR_JMA_WEATHER_FORECAST_REGION_Entry { uint32_t id; const char* label; };
inline constexpr QZSS_DCR_JMA_WEATHER_FORECAST_REGION_Entry QZSS_DCR_JMA_WEATHER_FORECAST_REGION_TABLE[] = {
    {11000u, "宗谷地方"},
    {12000u, "上川・留萌地方"},
    {12010u, "上川地方"},
    {12020u, "留萌地方"},
    {13000u, "網走・北見・紋別地方"},
    {14010u, "根室地方"},
    {14020u, "釧路地方"},
    {14030u, "十勝地方"},
    {14100u, "釧路・根室地方"},
    {15000u, "胆振・日高地方"},
    {15010u, "胆振地方"},
    {15020u, "日高地方"},
    {16000u, "石狩・空知・後志地方"},
    {16010u, "石狩地方"},
    {16020u, "空知地方"},
    {16030u, "後志地方"},
    {16100u, "石狩・空知地方"},
    {17000u, "渡島・檜山地方"},
    {17010u, "渡島地方"},
    {17020u, "檜山地方"},
    {20000u, "青森県"},
    {30000u, "岩手県"},
    {40000u, "宮城県"},
    {50000u, "秋田県"},
    {60000u, "山形県"},
    {70000u, "福島県"},
    {80000u, "茨城県"},
    {90000u, "栃木県"},
    {100000u, "群馬県"},
    {110000u, "埼玉県"},
    {120000u, "千葉県"},
    {130000u, "東京都"},
    {130010u, "東京地方"},
    {130020u, "伊豆諸島北部"},
    {130030u, "伊豆諸島南部"},
    {140000u, "神奈川県"},
    {150000u, "新潟県"},
    {160000u, "富山県"},
    {170000u, "石川県"},
    {180000u, "福井県"},
    {190000u, "山梨県"},
    {200000u, "長野県"},
    {210000u, "岐阜県"},
    {220000u, "静岡県"},
    {230000u, "愛知県"},
    {240000u, "三重県"},
    {250000u, "滋賀県"},
    {260000u, "京都府"},
    {270000u, "大阪府"},
    {280000u, "兵庫県"},
    {290000u, "奈良県"},
    {300000u, "和歌山県"},
    {310000u, "鳥取県"},
    {320000u, "島根県"},
    {330000u, "岡山県"},
    {340000u, "広島県"},
    {350000u, "山口県"},
    {360000u, "徳島県"},
    {370000u, "香川県"},
    {380000u, "愛媛県"},
    {390000u, "高知県"},
    {400000u, "福岡県"},
    {410000u, "佐賀県"},
    {420000u, "長崎県"},
    {430000u, "熊本県"},
    {440000u, "大分県"},
    {450000u, "宮崎県"},
    {460000u, "鹿児島県"},
    {460040u, "奄美地方"},
    {460100u, "鹿児島県(奄美地方除く)"},
    {471000u, "沖縄本島地方"},
    {472000u, "大東島地方"},
    {473000u, "宮古島地方"},
    {474000u, "八重山地方"},
    {500000u, "その他の府県予報区"},};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_weather_forecast_region_lookup(uint32_t id) noexcept {
    uint8_t lo = 0, hi = 75;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        if (QZSS_DCR_JMA_WEATHER_FORECAST_REGION_TABLE[mid].id == id) {
            const char* s = QZSS_DCR_JMA_WEATHER_FORECAST_REGION_TABLE[mid].label;
            return s ? std::optional<std::string_view>(std::string_view{s}) : std::nullopt;
        }
        if (QZSS_DCR_JMA_WEATHER_FORECAST_REGION_TABLE[mid].id < id) lo = mid + 1;
        else hi = mid;
    }
    return std::nullopt;
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_weather_forecast_region_lookup(uint32_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_weather_forecast_region_lookup(uint32_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
