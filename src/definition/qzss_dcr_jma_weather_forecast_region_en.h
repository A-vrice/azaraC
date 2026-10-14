#pragma once
// AUTO-GENERATED from azarashi 0.17.1 with CI-CD
// Source module : azarashi.definitions.qzss.dcr.weather_forecast_region
// Variable      : qzss_dcr_jma_weather_forecast_region_en
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

#if (AZARAC_ENABLE_WEATHER) && (AZARAC_LANG_EN)

#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCR_JMA_WEATHER_FORECAST_REGION_EN_POOL[] = "Soya\000Kamikawa and Rumoi\000Kamikawa\000Rumoi\000Abashiri · Kitami · Mombetsu\000Nemuro\000Kushiro\000Tokachi\000Kushiro and Nemuro\000Iburi and Hidaka\000Iburi\000Hidaka\000Region of Ishikari/Sorachi/Shiribeshi\000Ishikari\000Sorachi\000Shiribeshi\000Region of Ishikari and Sorachi\000Region of Oshima and Hiyama\000Oshima\000Hiyama\000Aomori\000Iwate\000Miyagi\000Akit\000Yamagat\000Fukushim\000Ibaraki\000Tochigi\000Gunm\000Saitam\000Chib\000Tokyo\000Tokyo\000Northern Izu Islands\000Southern Izu Islands\000Kanagaw\000Niigat\000Toyam\000Ishikaw\000Fukui\000Yamanashi\000Nagano\000Gifu\000Shizuok\000Aichi\000Mie \000Shig\000Kyoto\000Osak\000Hyogo\000Nara\000Wakayam\000Tottori\000Shimane\000Okayam\000Hiroshim\000Yamaguchi\000Tokushim\000Kagaw\000Ehime\000Kochi\000Fukuok\000Saga\000Nagasaki\000Kumamoto\000Oita\000Miyazaki\000Kagoshim\000Amami\000Kagoshima Prefecture (excluding Amami Region)\000Okinawa Main Island\000Daitojima\000Miyakojima\000Yaeyama\000Other Prefectural Forecast\000";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_WEATHER_FORECAST_REGION_EN_PARENT_POOL[] = " Prefecture\000 Region\000Prefecture\000a Prefecture\000";
struct QZSS_DCR_JMA_WEATHER_FORECAST_REGION_EN_PARENT_Entry { uint16_t offset; uint8_t len; };
static const QZSS_DCR_JMA_WEATHER_FORECAST_REGION_EN_PARENT_Entry QZSS_DCR_JMA_WEATHER_FORECAST_REGION_EN_PARENT_TABLE[] AZARAC_PROGMEM = {
    {0u, 11u},
    {12u, 7u},
    {20u, 10u},
    {31u, 12u},
};
struct QZSS_DCR_JMA_WEATHER_FORECAST_REGION_EN_Entry { uint32_t id; uint8_t parent; uint16_t offset; uint8_t len; };
static const QZSS_DCR_JMA_WEATHER_FORECAST_REGION_EN_Entry QZSS_DCR_JMA_WEATHER_FORECAST_REGION_EN_TABLE[] AZARAC_PROGMEM = {
    {11000u, 1u, 0u, 4u},
    {12000u, 1u, 5u, 18u},
    {12010u, 1u, 24u, 8u},
    {12020u, 1u, 33u, 5u},
    {13000u, 1u, 39u, 30u},
    {14010u, 1u, 70u, 6u},
    {14020u, 1u, 77u, 7u},
    {14030u, 1u, 85u, 7u},
    {14100u, 1u, 93u, 18u},
    {15000u, 1u, 112u, 16u},
    {15010u, 1u, 129u, 5u},
    {15020u, 1u, 135u, 6u},
    {16000u, 255u, 142u, 37u},
    {16010u, 1u, 180u, 8u},
    {16020u, 1u, 189u, 7u},
    {16030u, 1u, 197u, 10u},
    {16100u, 255u, 208u, 30u},
    {17000u, 255u, 239u, 27u},
    {17010u, 1u, 267u, 6u},
    {17020u, 1u, 274u, 6u},
    {20000u, 0u, 281u, 6u},
    {30000u, 0u, 288u, 5u},
    {40000u, 0u, 294u, 6u},
    {50000u, 3u, 301u, 4u},
    {60000u, 3u, 306u, 7u},
    {70000u, 3u, 314u, 8u},
    {80000u, 0u, 323u, 7u},
    {90000u, 0u, 331u, 7u},
    {100000u, 3u, 339u, 4u},
    {110000u, 3u, 344u, 6u},
    {120000u, 3u, 351u, 4u},
    {130000u, 255u, 356u, 5u},
    {130010u, 1u, 362u, 5u},
    {130020u, 255u, 368u, 20u},
    {130030u, 255u, 389u, 20u},
    {140000u, 3u, 410u, 7u},
    {150000u, 3u, 418u, 6u},
    {160000u, 3u, 425u, 5u},
    {170000u, 3u, 431u, 7u},
    {180000u, 0u, 439u, 5u},
    {190000u, 0u, 445u, 9u},
    {200000u, 0u, 455u, 6u},
    {210000u, 0u, 462u, 4u},
    {220000u, 3u, 467u, 7u},
    {230000u, 0u, 475u, 5u},
    {240000u, 2u, 481u, 4u},
    {250000u, 3u, 486u, 4u},
    {260000u, 0u, 491u, 5u},
    {270000u, 3u, 497u, 4u},
    {280000u, 0u, 502u, 5u},
    {290000u, 0u, 508u, 4u},
    {300000u, 3u, 513u, 7u},
    {310000u, 0u, 521u, 7u},
    {320000u, 0u, 529u, 7u},
    {330000u, 3u, 537u, 6u},
    {340000u, 3u, 544u, 8u},
    {350000u, 0u, 553u, 9u},
    {360000u, 3u, 563u, 8u},
    {370000u, 3u, 572u, 5u},
    {380000u, 0u, 578u, 5u},
    {390000u, 0u, 584u, 5u},
    {400000u, 3u, 590u, 6u},
    {410000u, 0u, 597u, 4u},
    {420000u, 0u, 602u, 8u},
    {430000u, 0u, 611u, 8u},
    {440000u, 0u, 620u, 4u},
    {450000u, 0u, 625u, 8u},
    {460000u, 3u, 634u, 8u},
    {460040u, 1u, 643u, 5u},
    {460100u, 255u, 649u, 45u},
    {471000u, 1u, 695u, 19u},
    {472000u, 1u, 715u, 9u},
    {473000u, 1u, 725u, 10u},
    {474000u, 1u, 736u, 7u},
    {500000u, 1u, 744u, 26u},
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_weather_forecast_region_en_lookup(uint32_t id) noexcept {
    uint8_t lo = 0, hi = 75;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        const char* AZARAC_PROGMEM ep = reinterpret_cast<const char*>(&QZSS_DCR_JMA_WEATHER_FORECAST_REGION_EN_TABLE[mid]);
        uint32_t eid = pgm_read_dword(ep + offsetof(QZSS_DCR_JMA_WEATHER_FORECAST_REGION_EN_Entry, id));
        if (eid == id) {
            uint16_t off = pgm_read_word(ep + offsetof(QZSS_DCR_JMA_WEATHER_FORECAST_REGION_EN_Entry, offset));
            uint8_t n = pgm_read_byte(ep + offsetof(QZSS_DCR_JMA_WEATHER_FORECAST_REGION_EN_Entry, len));
            uint8_t pi = pgm_read_byte(ep + offsetof(QZSS_DCR_JMA_WEATHER_FORECAST_REGION_EN_Entry, parent));
            if (pi == 255u) return azarac_pgm_view(QZSS_DCR_JMA_WEATHER_FORECAST_REGION_EN_POOL + off, n);
            const char* AZARAC_PROGMEM pp = reinterpret_cast<const char*>(&QZSS_DCR_JMA_WEATHER_FORECAST_REGION_EN_PARENT_TABLE[pi]);
            uint16_t poff = pgm_read_word(pp + offsetof(QZSS_DCR_JMA_WEATHER_FORECAST_REGION_EN_PARENT_Entry, offset));
            uint8_t pn = pgm_read_byte(pp + offsetof(QZSS_DCR_JMA_WEATHER_FORECAST_REGION_EN_PARENT_Entry, len));
            return azarac_pgm_join(QZSS_DCR_JMA_WEATHER_FORECAST_REGION_EN_POOL + off, n, QZSS_DCR_JMA_WEATHER_FORECAST_REGION_EN_PARENT_POOL + poff, pn);
        }
        if (eid < id) lo = static_cast<uint8_t>(mid + 1); else hi = mid;
    }
    return std::nullopt;
}
#else
struct QZSS_DCR_JMA_WEATHER_FORECAST_REGION_EN_Entry { uint32_t id; const char* label; };
inline constexpr QZSS_DCR_JMA_WEATHER_FORECAST_REGION_EN_Entry QZSS_DCR_JMA_WEATHER_FORECAST_REGION_EN_TABLE[] = {
    {11000u, "Soya Region"},
    {12000u, "Kamikawa and Rumoi Region"},
    {12010u, "Kamikawa Region"},
    {12020u, "Rumoi Region"},
    {13000u, "Abashiri · Kitami · Mombetsu Region"},
    {14010u, "Nemuro Region"},
    {14020u, "Kushiro Region"},
    {14030u, "Tokachi Region"},
    {14100u, "Kushiro and Nemuro Region"},
    {15000u, "Iburi and Hidaka Region"},
    {15010u, "Iburi Region"},
    {15020u, "Hidaka Region"},
    {16000u, "Region of Ishikari/Sorachi/Shiribeshi"},
    {16010u, "Ishikari Region"},
    {16020u, "Sorachi Region"},
    {16030u, "Shiribeshi Region"},
    {16100u, "Region of Ishikari and Sorachi"},
    {17000u, "Region of Oshima and Hiyama"},
    {17010u, "Oshima Region"},
    {17020u, "Hiyama Region"},
    {20000u, "Aomori Prefecture"},
    {30000u, "Iwate Prefecture"},
    {40000u, "Miyagi Prefecture"},
    {50000u, "Akita Prefecture"},
    {60000u, "Yamagata Prefecture"},
    {70000u, "Fukushima Prefecture"},
    {80000u, "Ibaraki Prefecture"},
    {90000u, "Tochigi Prefecture"},
    {100000u, "Gunma Prefecture"},
    {110000u, "Saitama Prefecture"},
    {120000u, "Chiba Prefecture"},
    {130000u, "Tokyo"},
    {130010u, "Tokyo Region"},
    {130020u, "Northern Izu Islands"},
    {130030u, "Southern Izu Islands"},
    {140000u, "Kanagawa Prefecture"},
    {150000u, "Niigata Prefecture"},
    {160000u, "Toyama Prefecture"},
    {170000u, "Ishikawa Prefecture"},
    {180000u, "Fukui Prefecture"},
    {190000u, "Yamanashi Prefecture"},
    {200000u, "Nagano Prefecture"},
    {210000u, "Gifu Prefecture"},
    {220000u, "Shizuoka Prefecture"},
    {230000u, "Aichi Prefecture"},
    {240000u, "Mie Prefecture"},
    {250000u, "Shiga Prefecture"},
    {260000u, "Kyoto Prefecture"},
    {270000u, "Osaka Prefecture"},
    {280000u, "Hyogo Prefecture"},
    {290000u, "Nara Prefecture"},
    {300000u, "Wakayama Prefecture"},
    {310000u, "Tottori Prefecture"},
    {320000u, "Shimane Prefecture"},
    {330000u, "Okayama Prefecture"},
    {340000u, "Hiroshima Prefecture"},
    {350000u, "Yamaguchi Prefecture"},
    {360000u, "Tokushima Prefecture"},
    {370000u, "Kagawa Prefecture"},
    {380000u, "Ehime Prefecture"},
    {390000u, "Kochi Prefecture"},
    {400000u, "Fukuoka Prefecture"},
    {410000u, "Saga Prefecture"},
    {420000u, "Nagasaki Prefecture"},
    {430000u, "Kumamoto Prefecture"},
    {440000u, "Oita Prefecture"},
    {450000u, "Miyazaki Prefecture"},
    {460000u, "Kagoshima Prefecture"},
    {460040u, "Amami Region"},
    {460100u, "Kagoshima Prefecture (excluding Amami Region)"},
    {471000u, "Okinawa Main Island Region"},
    {472000u, "Daitojima Region"},
    {473000u, "Miyakojima Region"},
    {474000u, "Yaeyama Region"},
    {500000u, "Other Prefectural Forecast Region"},};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_weather_forecast_region_en_lookup(uint32_t id) noexcept {
    uint8_t lo = 0, hi = 75;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        if (QZSS_DCR_JMA_WEATHER_FORECAST_REGION_EN_TABLE[mid].id == id) {
            const char* s = QZSS_DCR_JMA_WEATHER_FORECAST_REGION_EN_TABLE[mid].label;
            return s ? std::optional<std::string_view>(std::string_view{s}) : std::nullopt;
        }
        if (QZSS_DCR_JMA_WEATHER_FORECAST_REGION_EN_TABLE[mid].id < id) lo = mid + 1;
        else hi = mid;
    }
    return std::nullopt;
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_weather_forecast_region_en_lookup(uint32_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_weather_forecast_region_en_lookup(uint32_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
