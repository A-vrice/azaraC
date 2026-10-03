#pragma once
// AUTO-GENERATED from azarashi 0.17.0 with CI-CD
// Source module : azarashi.definitions.qzss.dcr.tsunami_forecast_region
// Variable      : qzss_dcr_jma_tsunami_forecast_region_en
// Entries       : 99
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

#if (AZARAC_ENABLE_TSUNAMI) && (AZARAC_LANG_EN)

#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_EN_POOL[] = "Eastern part of Pacific Coast of Hokkaido\000Central part of Pacific Coast of Hokkaido\000Western part of Pacific Coast of Hokkaido\000Northern part of Japan Sea Coast of Hokkaido\000Southern part of Japan Sea Coast of Hokkaido\000Okhotsk Sea Coast of Hokkaido\000Pacific Coast of Hokkaido\000Japan Sea Coast of Hokkaido\000Japan Sea Coast of Aomori Prefecture\000Pacific Coast of Aomori Prefecture\000Mutsu Bay\000Iwate Prefecture\000Miyagi Prefecture\000Akita Prefecture\000Yamagata Prefecture\000Fukushima Prefecture\000Aomori Prefecture\000Pacific Coast of Tohoku\000Japan Sea Coast of Tohoku\000Ibaraki Prefecture\000Kujukuri and Sotobo Area, Chiba Prefecture\000Uchibo Area, Chiba Prefecture\000Tokyo Bay\000Izu Islands\000Ogasawara Islands\000Sagami Bay and Miura Peninsula\000Niigata Prefecture, Except Sadogashima Island\000Sadogashima Island\000Toyama Prefecture\000Noto Area, Ishikawa Prefecture\000Kaga Area, Ishikawa Prefecture\000Fukui Prefecture\000Shizuoka Prefecture\000Pacific Coast of Aichi Prefecture\000Ise Bay and Mikawa Bay\000Southern Part of Mie Prefecture\000Chiba Prefecture\000Kanagawa Prefecture\000Niigata Prefecture\000Ishikawa Prefecture\000Aichi Prefecture\000Mie Prefecture\000Kanto\000Izu and Ogasawara\000Hokuriku\000Tokai\000Kyoto Prefecture\000Osaka Prefecture\000Northern Part of Hyogo Prefecture\000Setonaikai Coast of Hyogo Prefecture\000Southern Part of Awaji Island\000Wakayama Prefecture\000Tottori Prefecture\000Shimane Prefecture, Except Oki Islands\000Oki Islands\000Okayama Prefecture\000Hiroshima Prefecture\000Tokushima Prefecture\000Kagawa Prefecture\000Bungo Strait Coast of Ehime Prefecture\000Setonaikai Coast of Ehime Prefecture\000Kochi Prefecture\000Hyogo Prefecture\000Shimane Prefecture\000Ehime Prefecture\000Pacific Coast of Kinki/Shikoku\000Japan Sea Coast of Kinki/Chugoku\000Setonaikai Coast\000Japan Sea Coast of Yamaguchi Prefecture\000Setonaikai Coast of Yamaguchi Prefecture\000Setonaikai Coast of Fukuoka Prefecture\000Japan Sea Coast of Fukuoka Prefecture\000Ariake Sea and Yatsushiro Sea\000Northern Part of Saga Prefecture\000Western Part of Nagasaki Prefecture\000Iki Island and Tsushima Islands\000Amakusa Nada Coast of Kumamoto Prefecture\000Setonaikai Coast of Oita Prefecture\000Bungo Strait Coast of Oita Prefecture\000Miyazaki Prefecture\000Eastern Part of Kagoshima Prefecture\000Tanegashima and Yakushima Area\000Amami Islands and Tokara Islands\000Western Part of Kagoshima Prefecture\000Yamaguchi Prefecture\000Fukuoka Prefecture\000Saga Prefecture\000Nagasaki Prefecture\000Kumamoto Prefecture\000Ooita Prefecture\000Kagoshima Prefecture\000Eastern Part of Kyushu\000Western Part of Kyushu\000Satsunan Islands\000Okinawa Main Island Region\000Daitojima Area\000Miyakojima and Yaeyama Area\000Okinawa Prefecture\000Other Tsunami Forecast Region\000";
struct QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_EN_Entry { uint16_t id; uint16_t offset; uint16_t len; };
static const QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_EN_Entry QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_EN_TABLE[] AZARAC_PROGMEM = {
    {100u, 0u, 41u},
    {101u, 42u, 41u},
    {102u, 84u, 41u},
    {110u, 126u, 44u},
    {111u, 171u, 44u},
    {120u, 216u, 29u},
    {191u, 246u, 25u},
    {192u, 272u, 27u},
    {200u, 300u, 36u},
    {201u, 337u, 34u},
    {202u, 372u, 9u},
    {210u, 382u, 16u},
    {220u, 399u, 17u},
    {230u, 417u, 16u},
    {240u, 434u, 19u},
    {250u, 454u, 20u},
    {281u, 475u, 17u},
    {291u, 493u, 23u},
    {292u, 517u, 25u},
    {300u, 543u, 18u},
    {310u, 562u, 42u},
    {311u, 605u, 29u},
    {312u, 635u, 9u},
    {320u, 645u, 11u},
    {321u, 657u, 17u},
    {330u, 675u, 30u},
    {340u, 706u, 45u},
    {341u, 752u, 18u},
    {350u, 771u, 17u},
    {360u, 789u, 30u},
    {361u, 820u, 30u},
    {370u, 851u, 16u},
    {380u, 868u, 19u},
    {390u, 888u, 33u},
    {391u, 922u, 22u},
    {400u, 945u, 31u},
    {481u, 977u, 16u},
    {482u, 994u, 19u},
    {483u, 1014u, 18u},
    {484u, 1033u, 19u},
    {485u, 1053u, 16u},
    {486u, 1070u, 14u},
    {491u, 1085u, 5u},
    {492u, 1091u, 17u},
    {493u, 1109u, 8u},
    {494u, 1118u, 5u},
    {500u, 1124u, 16u},
    {510u, 1141u, 16u},
    {520u, 1158u, 33u},
    {521u, 1192u, 36u},
    {522u, 1229u, 29u},
    {530u, 1259u, 19u},
    {540u, 1279u, 18u},
    {550u, 1298u, 38u},
    {551u, 1337u, 11u},
    {560u, 1349u, 18u},
    {570u, 1368u, 20u},
    {580u, 1389u, 20u},
    {590u, 1410u, 17u},
    {600u, 1428u, 38u},
    {601u, 1467u, 36u},
    {610u, 1504u, 16u},
    {681u, 1521u, 16u},
    {682u, 1538u, 18u},
    {683u, 1557u, 16u},
    {691u, 1574u, 30u},
    {692u, 1605u, 32u},
    {693u, 1638u, 16u},
    {700u, 1655u, 39u},
    {701u, 1695u, 40u},
    {710u, 1736u, 38u},
    {711u, 1775u, 37u},
    {712u, 1813u, 29u},
    {720u, 1843u, 32u},
    {730u, 1876u, 35u},
    {731u, 1912u, 31u},
    {740u, 1944u, 41u},
    {750u, 1986u, 35u},
    {751u, 2022u, 37u},
    {760u, 2060u, 19u},
    {770u, 2080u, 36u},
    {771u, 2117u, 30u},
    {772u, 2148u, 32u},
    {773u, 2181u, 36u},
    {781u, 2218u, 20u},
    {782u, 2239u, 18u},
    {783u, 2258u, 15u},
    {784u, 2274u, 19u},
    {785u, 2294u, 19u},
    {786u, 2314u, 16u},
    {787u, 2331u, 20u},
    {791u, 2352u, 22u},
    {792u, 2375u, 22u},
    {793u, 2398u, 16u},
    {800u, 2415u, 26u},
    {801u, 2442u, 14u},
    {802u, 2457u, 27u},
    {891u, 2485u, 18u},
    {1000u, 2504u, 29u},
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_tsunami_forecast_region_en_lookup(uint16_t id) noexcept {
    uint8_t lo = 0, hi = 99;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        const char* AZARAC_PROGMEM ep = reinterpret_cast<const char*>(&QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_EN_TABLE[mid]);
        uint16_t eid = pgm_read_word(ep + offsetof(QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_EN_Entry, id));
        if (eid == id) {
            uint16_t off = pgm_read_word(ep + offsetof(QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_EN_Entry, offset));
            uint16_t n = pgm_read_word(ep + offsetof(QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_EN_Entry, len));
            return azarac_pgm_view(QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_EN_POOL + off, n);
        }
        if (eid < id) lo = static_cast<uint8_t>(mid + 1); else hi = mid;
    }
    return std::nullopt;
}
#else
struct QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_EN_Entry { uint16_t id; const char* label; };
inline constexpr QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_EN_Entry QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_EN_TABLE[] = {
    {100u, "Eastern part of Pacific Coast of Hokkaido"},
    {101u, "Central part of Pacific Coast of Hokkaido"},
    {102u, "Western part of Pacific Coast of Hokkaido"},
    {110u, "Northern part of Japan Sea Coast of Hokkaido"},
    {111u, "Southern part of Japan Sea Coast of Hokkaido"},
    {120u, "Okhotsk Sea Coast of Hokkaido"},
    {191u, "Pacific Coast of Hokkaido"},
    {192u, "Japan Sea Coast of Hokkaido"},
    {200u, "Japan Sea Coast of Aomori Prefecture"},
    {201u, "Pacific Coast of Aomori Prefecture"},
    {202u, "Mutsu Bay"},
    {210u, "Iwate Prefecture"},
    {220u, "Miyagi Prefecture"},
    {230u, "Akita Prefecture"},
    {240u, "Yamagata Prefecture"},
    {250u, "Fukushima Prefecture"},
    {281u, "Aomori Prefecture"},
    {291u, "Pacific Coast of Tohoku"},
    {292u, "Japan Sea Coast of Tohoku"},
    {300u, "Ibaraki Prefecture"},
    {310u, "Kujukuri and Sotobo Area, Chiba Prefecture"},
    {311u, "Uchibo Area, Chiba Prefecture"},
    {312u, "Tokyo Bay"},
    {320u, "Izu Islands"},
    {321u, "Ogasawara Islands"},
    {330u, "Sagami Bay and Miura Peninsula"},
    {340u, "Niigata Prefecture, Except Sadogashima Island"},
    {341u, "Sadogashima Island"},
    {350u, "Toyama Prefecture"},
    {360u, "Noto Area, Ishikawa Prefecture"},
    {361u, "Kaga Area, Ishikawa Prefecture"},
    {370u, "Fukui Prefecture"},
    {380u, "Shizuoka Prefecture"},
    {390u, "Pacific Coast of Aichi Prefecture"},
    {391u, "Ise Bay and Mikawa Bay"},
    {400u, "Southern Part of Mie Prefecture"},
    {481u, "Chiba Prefecture"},
    {482u, "Kanagawa Prefecture"},
    {483u, "Niigata Prefecture"},
    {484u, "Ishikawa Prefecture"},
    {485u, "Aichi Prefecture"},
    {486u, "Mie Prefecture"},
    {491u, "Kanto"},
    {492u, "Izu and Ogasawara"},
    {493u, "Hokuriku"},
    {494u, "Tokai"},
    {500u, "Kyoto Prefecture"},
    {510u, "Osaka Prefecture"},
    {520u, "Northern Part of Hyogo Prefecture"},
    {521u, "Setonaikai Coast of Hyogo Prefecture"},
    {522u, "Southern Part of Awaji Island"},
    {530u, "Wakayama Prefecture"},
    {540u, "Tottori Prefecture"},
    {550u, "Shimane Prefecture, Except Oki Islands"},
    {551u, "Oki Islands"},
    {560u, "Okayama Prefecture"},
    {570u, "Hiroshima Prefecture"},
    {580u, "Tokushima Prefecture"},
    {590u, "Kagawa Prefecture"},
    {600u, "Bungo Strait Coast of Ehime Prefecture"},
    {601u, "Setonaikai Coast of Ehime Prefecture"},
    {610u, "Kochi Prefecture"},
    {681u, "Hyogo Prefecture"},
    {682u, "Shimane Prefecture"},
    {683u, "Ehime Prefecture"},
    {691u, "Pacific Coast of Kinki/Shikoku"},
    {692u, "Japan Sea Coast of Kinki/Chugoku"},
    {693u, "Setonaikai Coast"},
    {700u, "Japan Sea Coast of Yamaguchi Prefecture"},
    {701u, "Setonaikai Coast of Yamaguchi Prefecture"},
    {710u, "Setonaikai Coast of Fukuoka Prefecture"},
    {711u, "Japan Sea Coast of Fukuoka Prefecture"},
    {712u, "Ariake Sea and Yatsushiro Sea"},
    {720u, "Northern Part of Saga Prefecture"},
    {730u, "Western Part of Nagasaki Prefecture"},
    {731u, "Iki Island and Tsushima Islands"},
    {740u, "Amakusa Nada Coast of Kumamoto Prefecture"},
    {750u, "Setonaikai Coast of Oita Prefecture"},
    {751u, "Bungo Strait Coast of Oita Prefecture"},
    {760u, "Miyazaki Prefecture"},
    {770u, "Eastern Part of Kagoshima Prefecture"},
    {771u, "Tanegashima and Yakushima Area"},
    {772u, "Amami Islands and Tokara Islands"},
    {773u, "Western Part of Kagoshima Prefecture"},
    {781u, "Yamaguchi Prefecture"},
    {782u, "Fukuoka Prefecture"},
    {783u, "Saga Prefecture"},
    {784u, "Nagasaki Prefecture"},
    {785u, "Kumamoto Prefecture"},
    {786u, "Ooita Prefecture"},
    {787u, "Kagoshima Prefecture"},
    {791u, "Eastern Part of Kyushu"},
    {792u, "Western Part of Kyushu"},
    {793u, "Satsunan Islands"},
    {800u, "Okinawa Main Island Region"},
    {801u, "Daitojima Area"},
    {802u, "Miyakojima and Yaeyama Area"},
    {891u, "Okinawa Prefecture"},
    {1000u, "Other Tsunami Forecast Region"},};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_tsunami_forecast_region_en_lookup(uint16_t id) noexcept {
    uint8_t lo = 0, hi = 99;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        if (QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_EN_TABLE[mid].id == id) {
            const char* s = QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_EN_TABLE[mid].label;
            return s ? std::optional<std::string_view>(std::string_view{s}) : std::nullopt;
        }
        if (QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_EN_TABLE[mid].id < id) lo = mid + 1;
        else hi = mid;
    }
    return std::nullopt;
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_tsunami_forecast_region_en_lookup(uint16_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_tsunami_forecast_region_en_lookup(uint16_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
