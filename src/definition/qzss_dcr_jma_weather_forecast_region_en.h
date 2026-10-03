#pragma once
// AUTO-GENERATED from azarashi 0.17.0 with CI-CD
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
static const char AZARAC_PROGMEM QZSS_DCR_JMA_WEATHER_FORECAST_REGION_EN_POOL[] = "Soya Region\000Kamikawa and Rumoi Region\000Kamikawa Region\000Rumoi Region\000Abashiri · Kitami · Mombetsu Region\000Nemuro Region\000Kushiro Region\000Tokachi Region\000Kushiro and Nemuro Region\000Iburi and Hidaka Region\000Iburi Region\000Hidaka Region\000Region of Ishikari/Sorachi/Shiribeshi\000Ishikari Region\000Sorachi Region\000Shiribeshi Region\000Region of Ishikari and Sorachi\000Region of Oshima and Hiyama\000Oshima Region\000Hiyama Region\000Aomori Prefecture\000Iwate Prefecture\000Miyagi Prefecture\000Akita Prefecture\000Yamagata Prefecture\000Fukushima Prefecture\000Ibaraki Prefecture\000Tochigi Prefecture\000Gunma Prefecture\000Saitama Prefecture\000Chiba Prefecture\000Tokyo\000Tokyo Region\000Northern Izu Islands\000Southern Izu Islands\000Kanagawa Prefecture\000Niigata Prefecture\000Toyama Prefecture\000Ishikawa Prefecture\000Fukui Prefecture\000Yamanashi Prefecture\000Nagano Prefecture\000Gifu Prefecture\000Shizuoka Prefecture\000Aichi Prefecture\000Mie Prefecture\000Shiga Prefecture\000Kyoto Prefecture\000Osaka Prefecture\000Hyogo Prefecture\000Nara Prefecture\000Wakayama Prefecture\000Tottori Prefecture\000Shimane Prefecture\000Okayama Prefecture\000Hiroshima Prefecture\000Yamaguchi Prefecture\000Tokushima Prefecture\000Kagawa Prefecture\000Ehime Prefecture\000Kochi Prefecture\000Fukuoka Prefecture\000Saga Prefecture\000Nagasaki Prefecture\000Kumamoto Prefecture\000Oita Prefecture\000Miyazaki Prefecture\000Kagoshima Prefecture\000Amami Region\000Kagoshima Prefecture (excluding Amami Region)\000Okinawa Main Island Region\000Daitojima Region\000Miyakojima Region\000Yaeyama Region\000Other Prefectural Forecast Region\000";
struct QZSS_DCR_JMA_WEATHER_FORECAST_REGION_EN_Entry { uint32_t id; uint16_t offset; uint16_t len; };
static const QZSS_DCR_JMA_WEATHER_FORECAST_REGION_EN_Entry QZSS_DCR_JMA_WEATHER_FORECAST_REGION_EN_TABLE[] AZARAC_PROGMEM = {
    {11000u, 0u, 11u},
    {12000u, 12u, 25u},
    {12010u, 38u, 15u},
    {12020u, 54u, 12u},
    {13000u, 67u, 37u},
    {14010u, 105u, 13u},
    {14020u, 119u, 14u},
    {14030u, 134u, 14u},
    {14100u, 149u, 25u},
    {15000u, 175u, 23u},
    {15010u, 199u, 12u},
    {15020u, 212u, 13u},
    {16000u, 226u, 37u},
    {16010u, 264u, 15u},
    {16020u, 280u, 14u},
    {16030u, 295u, 17u},
    {16100u, 313u, 30u},
    {17000u, 344u, 27u},
    {17010u, 372u, 13u},
    {17020u, 386u, 13u},
    {20000u, 400u, 17u},
    {30000u, 418u, 16u},
    {40000u, 435u, 17u},
    {50000u, 453u, 16u},
    {60000u, 470u, 19u},
    {70000u, 490u, 20u},
    {80000u, 511u, 18u},
    {90000u, 530u, 18u},
    {100000u, 549u, 16u},
    {110000u, 566u, 18u},
    {120000u, 585u, 16u},
    {130000u, 602u, 5u},
    {130010u, 608u, 12u},
    {130020u, 621u, 20u},
    {130030u, 642u, 20u},
    {140000u, 663u, 19u},
    {150000u, 683u, 18u},
    {160000u, 702u, 17u},
    {170000u, 720u, 19u},
    {180000u, 740u, 16u},
    {190000u, 757u, 20u},
    {200000u, 778u, 17u},
    {210000u, 796u, 15u},
    {220000u, 812u, 19u},
    {230000u, 832u, 16u},
    {240000u, 849u, 14u},
    {250000u, 864u, 16u},
    {260000u, 881u, 16u},
    {270000u, 898u, 16u},
    {280000u, 915u, 16u},
    {290000u, 932u, 15u},
    {300000u, 948u, 19u},
    {310000u, 968u, 18u},
    {320000u, 987u, 18u},
    {330000u, 1006u, 18u},
    {340000u, 1025u, 20u},
    {350000u, 1046u, 20u},
    {360000u, 1067u, 20u},
    {370000u, 1088u, 17u},
    {380000u, 1106u, 16u},
    {390000u, 1123u, 16u},
    {400000u, 1140u, 18u},
    {410000u, 1159u, 15u},
    {420000u, 1175u, 19u},
    {430000u, 1195u, 19u},
    {440000u, 1215u, 15u},
    {450000u, 1231u, 19u},
    {460000u, 1251u, 20u},
    {460040u, 1272u, 12u},
    {460100u, 1285u, 45u},
    {471000u, 1331u, 26u},
    {472000u, 1358u, 16u},
    {473000u, 1375u, 17u},
    {474000u, 1393u, 14u},
    {500000u, 1408u, 33u},
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_weather_forecast_region_en_lookup(uint32_t id) noexcept {
    uint8_t lo = 0, hi = 75;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        const char* AZARAC_PROGMEM ep = reinterpret_cast<const char*>(&QZSS_DCR_JMA_WEATHER_FORECAST_REGION_EN_TABLE[mid]);
        uint32_t eid = pgm_read_dword(ep + offsetof(QZSS_DCR_JMA_WEATHER_FORECAST_REGION_EN_Entry, id));
        if (eid == id) {
            uint16_t off = pgm_read_word(ep + offsetof(QZSS_DCR_JMA_WEATHER_FORECAST_REGION_EN_Entry, offset));
            uint16_t n = pgm_read_word(ep + offsetof(QZSS_DCR_JMA_WEATHER_FORECAST_REGION_EN_Entry, len));
            return azarac_pgm_view(QZSS_DCR_JMA_WEATHER_FORECAST_REGION_EN_POOL + off, n);
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
