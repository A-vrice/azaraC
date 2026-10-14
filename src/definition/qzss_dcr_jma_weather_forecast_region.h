#pragma once
// AUTO-GENERATED from azarashi 0.17.1 with CI-CD
// Source module : azarashi.definitions.qzss.dcr.weather_forecast_region
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

#if (AZARAC_ENABLE_WEATHER) && (AZARAC_LANG_JA)

#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCR_JMA_WEATHER_FORECAST_REGION_POOL[] = "宗谷\000上川・留萌\000上川\000留萌\000網走・北見・紋別\000根室\000釧路\000十勝\000釧路・根室\000胆振・日高\000胆振\000日高\000石狩・空知・後志\000石狩\000空知\000後志\000石狩・空知\000渡島・檜山\000渡島\000檜山\000青森\000岩手\000宮城\000秋田\000山形\000福島\000茨城\000栃木\000群馬\000埼玉\000千葉\000東京都\000東京\000伊豆諸島北部\000伊豆諸島南部\000神奈川\000新潟\000富山\000石川\000福井\000山梨\000長野\000岐阜\000静岡\000愛知\000三重\000滋賀\000京都府\000大阪府\000兵庫\000奈良\000和歌山\000鳥取\000島根\000岡山\000広島\000山口\000徳島\000香川\000愛媛\000高知\000福岡\000佐賀\000長崎\000熊本\000大分\000宮崎\000鹿児島\000奄美\000鹿児島県(奄美地方除く)\000沖縄本島\000大東島\000宮古島\000八重山\000その他の府県予報区\000";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_WEATHER_FORECAST_REGION_PARENT_POOL[] = "地方\000県\000";
struct QZSS_DCR_JMA_WEATHER_FORECAST_REGION_PARENT_Entry { uint16_t offset; uint8_t len; };
static const QZSS_DCR_JMA_WEATHER_FORECAST_REGION_PARENT_Entry QZSS_DCR_JMA_WEATHER_FORECAST_REGION_PARENT_TABLE[] AZARAC_PROGMEM = {
    {0u, 6u},
    {7u, 3u},
};
struct QZSS_DCR_JMA_WEATHER_FORECAST_REGION_Entry { uint32_t id; uint8_t parent; uint16_t offset; uint8_t len; };
static const QZSS_DCR_JMA_WEATHER_FORECAST_REGION_Entry QZSS_DCR_JMA_WEATHER_FORECAST_REGION_TABLE[] AZARAC_PROGMEM = {
    {11000u, 0u, 0u, 6u},
    {12000u, 0u, 7u, 15u},
    {12010u, 0u, 23u, 6u},
    {12020u, 0u, 30u, 6u},
    {13000u, 0u, 37u, 24u},
    {14010u, 0u, 62u, 6u},
    {14020u, 0u, 69u, 6u},
    {14030u, 0u, 76u, 6u},
    {14100u, 0u, 83u, 15u},
    {15000u, 0u, 99u, 15u},
    {15010u, 0u, 115u, 6u},
    {15020u, 0u, 122u, 6u},
    {16000u, 0u, 129u, 24u},
    {16010u, 0u, 154u, 6u},
    {16020u, 0u, 161u, 6u},
    {16030u, 0u, 168u, 6u},
    {16100u, 0u, 175u, 15u},
    {17000u, 0u, 191u, 15u},
    {17010u, 0u, 207u, 6u},
    {17020u, 0u, 214u, 6u},
    {20000u, 1u, 221u, 6u},
    {30000u, 1u, 228u, 6u},
    {40000u, 1u, 235u, 6u},
    {50000u, 1u, 242u, 6u},
    {60000u, 1u, 249u, 6u},
    {70000u, 1u, 256u, 6u},
    {80000u, 1u, 263u, 6u},
    {90000u, 1u, 270u, 6u},
    {100000u, 1u, 277u, 6u},
    {110000u, 1u, 284u, 6u},
    {120000u, 1u, 291u, 6u},
    {130000u, 255u, 298u, 9u},
    {130010u, 0u, 308u, 6u},
    {130020u, 255u, 315u, 18u},
    {130030u, 255u, 334u, 18u},
    {140000u, 1u, 353u, 9u},
    {150000u, 1u, 363u, 6u},
    {160000u, 1u, 370u, 6u},
    {170000u, 1u, 377u, 6u},
    {180000u, 1u, 384u, 6u},
    {190000u, 1u, 391u, 6u},
    {200000u, 1u, 398u, 6u},
    {210000u, 1u, 405u, 6u},
    {220000u, 1u, 412u, 6u},
    {230000u, 1u, 419u, 6u},
    {240000u, 1u, 426u, 6u},
    {250000u, 1u, 433u, 6u},
    {260000u, 255u, 440u, 9u},
    {270000u, 255u, 450u, 9u},
    {280000u, 1u, 460u, 6u},
    {290000u, 1u, 467u, 6u},
    {300000u, 1u, 474u, 9u},
    {310000u, 1u, 484u, 6u},
    {320000u, 1u, 491u, 6u},
    {330000u, 1u, 498u, 6u},
    {340000u, 1u, 505u, 6u},
    {350000u, 1u, 512u, 6u},
    {360000u, 1u, 519u, 6u},
    {370000u, 1u, 526u, 6u},
    {380000u, 1u, 533u, 6u},
    {390000u, 1u, 540u, 6u},
    {400000u, 1u, 547u, 6u},
    {410000u, 1u, 554u, 6u},
    {420000u, 1u, 561u, 6u},
    {430000u, 1u, 568u, 6u},
    {440000u, 1u, 575u, 6u},
    {450000u, 1u, 582u, 6u},
    {460000u, 1u, 589u, 9u},
    {460040u, 0u, 599u, 6u},
    {460100u, 255u, 606u, 32u},
    {471000u, 0u, 639u, 12u},
    {472000u, 0u, 652u, 9u},
    {473000u, 0u, 662u, 9u},
    {474000u, 0u, 672u, 9u},
    {500000u, 255u, 682u, 27u},
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_weather_forecast_region_lookup(uint32_t id) noexcept {
    uint8_t lo = 0, hi = 75;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        const char* AZARAC_PROGMEM ep = reinterpret_cast<const char*>(&QZSS_DCR_JMA_WEATHER_FORECAST_REGION_TABLE[mid]);
        uint32_t eid = pgm_read_dword(ep + offsetof(QZSS_DCR_JMA_WEATHER_FORECAST_REGION_Entry, id));
        if (eid == id) {
            uint16_t off = pgm_read_word(ep + offsetof(QZSS_DCR_JMA_WEATHER_FORECAST_REGION_Entry, offset));
            uint8_t n = pgm_read_byte(ep + offsetof(QZSS_DCR_JMA_WEATHER_FORECAST_REGION_Entry, len));
            uint8_t pi = pgm_read_byte(ep + offsetof(QZSS_DCR_JMA_WEATHER_FORECAST_REGION_Entry, parent));
            if (pi == 255u) return azarac_pgm_view(QZSS_DCR_JMA_WEATHER_FORECAST_REGION_POOL + off, n);
            const char* AZARAC_PROGMEM pp = reinterpret_cast<const char*>(&QZSS_DCR_JMA_WEATHER_FORECAST_REGION_PARENT_TABLE[pi]);
            uint16_t poff = pgm_read_word(pp + offsetof(QZSS_DCR_JMA_WEATHER_FORECAST_REGION_PARENT_Entry, offset));
            uint8_t pn = pgm_read_byte(pp + offsetof(QZSS_DCR_JMA_WEATHER_FORECAST_REGION_PARENT_Entry, len));
            return azarac_pgm_join(QZSS_DCR_JMA_WEATHER_FORECAST_REGION_POOL + off, n, QZSS_DCR_JMA_WEATHER_FORECAST_REGION_PARENT_POOL + poff, pn);
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
