#pragma once
// AUTO-GENERATED from azarashi 0.17.1 — do not edit
// azarashi.definitions.qzss.dcr.weather_forecast_region → qzss_dcr_jma_weather_forecast_region: 75 entries, strategy binary_search
// Unknown id returns nullptr — callers MUST null-check.

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

static const char AZARAC_PROGMEM QZSS_DCR_JMA_WEATHER_FORECAST_REGION_POOL[] = "宗谷\000上川・留萌\000上川\000留萌\000網走・北見・紋別\000根室\000釧路\000十勝\000釧路・根室\000胆振・日高\000胆振\000日高\000石狩・空知・後志\000石狩\000空知\000後志\000石狩・空知\000渡島・檜山\000渡\000檜山\000青森県\000岩手県\000宮城県\000秋田県\000山形県\000福\000茨城県\000栃木県\000群馬県\000埼玉県\000千葉県\000東京都\000東京\000伊豆諸島北部\000伊豆諸島南部\000神奈川県\000新潟県\000富山県\000石川県\000福井県\000山梨県\000長野県\000岐阜県\000静岡県\000愛知県\000三重県\000滋賀県\000京都府\000大阪府\000兵庫県\000奈良県\000和歌山県\000鳥取県\000島根県\000岡山県\000広\000山口県\000徳\000香川県\000愛媛県\000高知県\000福岡県\000佐賀県\000長崎県\000熊本県\000大分県\000宮崎県\000鹿児\000奄美\000鹿児島県(奄美地方除く)\000沖縄本\000大東\000宮古\000八重山\000その他の府県予報区\000";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_WEATHER_FORECAST_REGION_PARENT_POOL[] = "地方\000島地方\000島県\000";
struct QZSS_DCR_JMA_WEATHER_FORECAST_REGION_PARENT_Entry { uint16_t offset; };
static const QZSS_DCR_JMA_WEATHER_FORECAST_REGION_PARENT_Entry QZSS_DCR_JMA_WEATHER_FORECAST_REGION_PARENT_TABLE[] AZARAC_PROGMEM = {
    {0u},
    {7u},
    {17u},
};
struct QZSS_DCR_JMA_WEATHER_FORECAST_REGION_Entry { uint32_t id; uint8_t parent; uint16_t offset; };
static const QZSS_DCR_JMA_WEATHER_FORECAST_REGION_Entry QZSS_DCR_JMA_WEATHER_FORECAST_REGION_TABLE[] AZARAC_PROGMEM = {
    {11000u, 0u, 0u},
    {12000u, 0u, 7u},
    {12010u, 0u, 23u},
    {12020u, 0u, 30u},
    {13000u, 0u, 37u},
    {14010u, 0u, 62u},
    {14020u, 0u, 69u},
    {14030u, 0u, 76u},
    {14100u, 0u, 83u},
    {15000u, 0u, 99u},
    {15010u, 0u, 115u},
    {15020u, 0u, 122u},
    {16000u, 0u, 129u},
    {16010u, 0u, 154u},
    {16020u, 0u, 161u},
    {16030u, 0u, 168u},
    {16100u, 0u, 175u},
    {17000u, 0u, 191u},
    {17010u, 1u, 207u},
    {17020u, 0u, 211u},
    {20000u, 255u, 218u},
    {30000u, 255u, 228u},
    {40000u, 255u, 238u},
    {50000u, 255u, 248u},
    {60000u, 255u, 258u},
    {70000u, 2u, 268u},
    {80000u, 255u, 272u},
    {90000u, 255u, 282u},
    {100000u, 255u, 292u},
    {110000u, 255u, 302u},
    {120000u, 255u, 312u},
    {130000u, 255u, 322u},
    {130010u, 0u, 332u},
    {130020u, 255u, 339u},
    {130030u, 255u, 358u},
    {140000u, 255u, 377u},
    {150000u, 255u, 390u},
    {160000u, 255u, 400u},
    {170000u, 255u, 410u},
    {180000u, 255u, 420u},
    {190000u, 255u, 430u},
    {200000u, 255u, 440u},
    {210000u, 255u, 450u},
    {220000u, 255u, 460u},
    {230000u, 255u, 470u},
    {240000u, 255u, 480u},
    {250000u, 255u, 490u},
    {260000u, 255u, 500u},
    {270000u, 255u, 510u},
    {280000u, 255u, 520u},
    {290000u, 255u, 530u},
    {300000u, 255u, 540u},
    {310000u, 255u, 553u},
    {320000u, 255u, 563u},
    {330000u, 255u, 573u},
    {340000u, 2u, 583u},
    {350000u, 255u, 587u},
    {360000u, 2u, 597u},
    {370000u, 255u, 601u},
    {380000u, 255u, 611u},
    {390000u, 255u, 621u},
    {400000u, 255u, 631u},
    {410000u, 255u, 641u},
    {420000u, 255u, 651u},
    {430000u, 255u, 661u},
    {440000u, 255u, 671u},
    {450000u, 255u, 681u},
    {460000u, 2u, 691u},
    {460040u, 0u, 698u},
    {460100u, 255u, 705u},
    {471000u, 1u, 738u},
    {472000u, 1u, 748u},
    {473000u, 1u, 755u},
    {474000u, 0u, 762u},
    {500000u, 255u, 772u},
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_weather_forecast_region_lookup(uint32_t id) noexcept {
    uint8_t lo = 0, hi = 75;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        azarac_pgm_ptr ep = AZARAC_PGM_PTR(QZSS_DCR_JMA_WEATHER_FORECAST_REGION_TABLE) + static_cast<size_t>(mid) * sizeof(QZSS_DCR_JMA_WEATHER_FORECAST_REGION_Entry);
        uint32_t eid = azarac_read_dword(ep, offsetof(QZSS_DCR_JMA_WEATHER_FORECAST_REGION_Entry, id));
        if (eid == id) {
            uint16_t off = azarac_read_word(ep, offsetof(QZSS_DCR_JMA_WEATHER_FORECAST_REGION_Entry, offset));
            uint8_t pi = azarac_read_byte(ep, offsetof(QZSS_DCR_JMA_WEATHER_FORECAST_REGION_Entry, parent));
            if (pi == 255u) return azarac_pgm_view_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_WEATHER_FORECAST_REGION_POOL) + off);
            azarac_pgm_ptr pp = AZARAC_PGM_PTR(QZSS_DCR_JMA_WEATHER_FORECAST_REGION_PARENT_TABLE) + static_cast<size_t>(pi) * sizeof(QZSS_DCR_JMA_WEATHER_FORECAST_REGION_PARENT_Entry);
            uint16_t poff = azarac_read_word(pp, offsetof(QZSS_DCR_JMA_WEATHER_FORECAST_REGION_PARENT_Entry, offset));
            return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_WEATHER_FORECAST_REGION_POOL) + off, AZARAC_PGM_PTR(QZSS_DCR_JMA_WEATHER_FORECAST_REGION_PARENT_POOL) + poff);
        }
        if (eid < id) lo = static_cast<uint8_t>(mid + 1); else hi = mid;
    }
    return std::nullopt;
}

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
