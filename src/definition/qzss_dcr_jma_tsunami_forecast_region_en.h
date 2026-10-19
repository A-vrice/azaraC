#pragma once
// AUTO-GENERATED from azarashi 0.17.1 — do not edit
// azarashi.definitions.qzss.dcr.tsunami_forecast_region → qzss_dcr_jma_tsunami_forecast_region_en: 99 entries, strategy binary_search
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

#if (AZARAC_ENABLE_TSUNAMI) && (AZARAC_LANG_EN)

#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_EN_POOL[] = "Eastern part of Pacific\000Central part of Pacific\000Western part of Pacific\000Northern part of Japan Sea\000Southern part of Japan Sea\000Okhotsk Sea\000Pacific\000Japan Sea\000Japan Sea Coast of Aomor\000Pacific Coast of Aomor\000Mutsu Bay\000Iwate\000Miyag\000Akit\000Yamagat\000Fukushi\000Aomor\000Pacific Coast of Tohoku\000Japan Sea Coast of Tohoku\000Ibarak\000Kujukuri and Sotobo Area, Chib\000Uchibo Area, Chib\000Tokyo Bay\000Izu Islands\000Ogasawara Islands\000Sagami Bay and Miura Peninsula\000Niigata Prefecture, Except Sadogashima Island\000Sadogashima Island\000Toya\000Noto Area, Ishikaw\000Kaga Area, Ishikaw\000Fuku\000Shizuok\000Pacific Coast of Aich\000Ise Bay and Mikawa Bay\000Southern Part of Mie\000Chib\000Kanagaw\000Niigat\000Ishikaw\000Aich\000Mie\000Kanto\000Izu and Ogasawara\000Hokuriku\000Tokai\000Kyoto\000Osak\000Northern Part of Hyogo\000Setonaikai Coast of Hyogo\000Southern Part of Awaji Island\000Wakaya\000Tottor\000Shimane Prefecture, Except Oki Islands\000Oki Islands\000Okaya\000Hiroshi\000Tokushi\000Kagaw\000Bungo Strait Coast of Ehime\000Setonaikai Coast of Ehime\000Koch\000Hyogo\000Shimane\000Ehime\000Pacific Coast of Kinki/Shikoku\000Japan Sea Coast of Kinki/Chugoku\000Setonaikai Coast\000Japan Sea Coast of Yamaguch\000Setonaikai Coast of Yamaguch\000Setonaikai Coast of Fukuok\000Japan Sea Coast of Fukuok\000Ariake Sea and Yatsushiro Sea\000Northern Part of Sag\000Western Part of Nagasak\000Iki Island and Tsushima Islands\000Amakusa Nada Coast of Kumamoto\000Setonaikai Coast of Oit\000Bungo Strait Coast of Oit\000Miyazak\000Eastern Part of Kagoshi\000Tanegashima and Yakushima Area\000Amami Islands and Tokara Islands\000Western Part of Kagoshi\000Yamaguch\000Fukuok\000Sag\000Nagasak\000Kumamoto\000Ooit\000Kagoshi\000Eastern Part of Kyushu\000Western Part of Kyushu\000Satsunan Islands\000Okinawa Main Island Region\000Daitojima Area\000Miyakojima and Yaeyama Area\000Okinaw\000Other Tsunami Forecast Region\000";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_EN_PARENT_POOL[] = " Coast of Hokkaido\000 Prefecture\000a Prefecture\000i Prefecture\000ma Prefecture\000";
struct QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_EN_PARENT_Entry { uint16_t offset; };
static const QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_EN_PARENT_Entry QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_EN_PARENT_TABLE[] AZARAC_PROGMEM = {
    {0u},
    {19u},
    {31u},
    {44u},
    {57u},
};
struct QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_EN_Entry { uint16_t id; uint8_t parent; uint16_t offset; };
static const QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_EN_Entry QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_EN_TABLE[] AZARAC_PROGMEM = {
    {100u, 0u, 0u},
    {101u, 0u, 24u},
    {102u, 0u, 48u},
    {110u, 0u, 72u},
    {111u, 0u, 99u},
    {120u, 0u, 126u},
    {191u, 0u, 138u},
    {192u, 0u, 146u},
    {200u, 3u, 156u},
    {201u, 3u, 181u},
    {202u, 255u, 204u},
    {210u, 1u, 214u},
    {220u, 3u, 220u},
    {230u, 2u, 226u},
    {240u, 2u, 231u},
    {250u, 4u, 239u},
    {281u, 3u, 247u},
    {291u, 255u, 253u},
    {292u, 255u, 277u},
    {300u, 3u, 303u},
    {310u, 2u, 310u},
    {311u, 2u, 341u},
    {312u, 255u, 359u},
    {320u, 255u, 369u},
    {321u, 255u, 381u},
    {330u, 255u, 399u},
    {340u, 255u, 430u},
    {341u, 255u, 476u},
    {350u, 4u, 495u},
    {360u, 2u, 500u},
    {361u, 2u, 519u},
    {370u, 3u, 538u},
    {380u, 2u, 543u},
    {390u, 3u, 551u},
    {391u, 255u, 573u},
    {400u, 1u, 596u},
    {481u, 2u, 617u},
    {482u, 2u, 622u},
    {483u, 2u, 630u},
    {484u, 2u, 637u},
    {485u, 3u, 645u},
    {486u, 1u, 650u},
    {491u, 255u, 654u},
    {492u, 255u, 660u},
    {493u, 255u, 678u},
    {494u, 255u, 687u},
    {500u, 1u, 693u},
    {510u, 2u, 699u},
    {520u, 1u, 704u},
    {521u, 1u, 727u},
    {522u, 255u, 753u},
    {530u, 4u, 783u},
    {540u, 3u, 790u},
    {550u, 255u, 797u},
    {551u, 255u, 836u},
    {560u, 4u, 848u},
    {570u, 4u, 854u},
    {580u, 4u, 862u},
    {590u, 2u, 870u},
    {600u, 1u, 876u},
    {601u, 1u, 904u},
    {610u, 3u, 930u},
    {681u, 1u, 935u},
    {682u, 1u, 941u},
    {683u, 1u, 949u},
    {691u, 255u, 955u},
    {692u, 255u, 986u},
    {693u, 255u, 1019u},
    {700u, 3u, 1036u},
    {701u, 3u, 1064u},
    {710u, 2u, 1093u},
    {711u, 2u, 1120u},
    {712u, 255u, 1146u},
    {720u, 2u, 1176u},
    {730u, 3u, 1197u},
    {731u, 255u, 1221u},
    {740u, 1u, 1253u},
    {750u, 2u, 1284u},
    {751u, 2u, 1308u},
    {760u, 3u, 1334u},
    {770u, 4u, 1342u},
    {771u, 255u, 1366u},
    {772u, 255u, 1397u},
    {773u, 4u, 1430u},
    {781u, 3u, 1454u},
    {782u, 2u, 1463u},
    {783u, 2u, 1470u},
    {784u, 3u, 1474u},
    {785u, 1u, 1482u},
    {786u, 2u, 1491u},
    {787u, 4u, 1496u},
    {791u, 255u, 1504u},
    {792u, 255u, 1527u},
    {793u, 255u, 1550u},
    {800u, 255u, 1567u},
    {801u, 255u, 1594u},
    {802u, 255u, 1609u},
    {891u, 2u, 1637u},
    {1000u, 255u, 1644u},
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_tsunami_forecast_region_en_lookup(uint16_t id) noexcept {
    uint8_t lo = 0, hi = 99;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        azarac_pgm_ptr ep = AZARAC_PGM_PTR(QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_EN_TABLE) + static_cast<size_t>(mid) * sizeof(QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_EN_Entry);
        uint16_t eid = azarac_read_word(ep, offsetof(QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_EN_Entry, id));
        if (eid == id) {
            uint16_t off = azarac_read_word(ep, offsetof(QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_EN_Entry, offset));
            uint8_t pi = azarac_read_byte(ep, offsetof(QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_EN_Entry, parent));
            if (pi == 255u) return azarac_pgm_view_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_EN_POOL) + off);
            azarac_pgm_ptr pp = AZARAC_PGM_PTR(QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_EN_PARENT_TABLE) + static_cast<size_t>(pi) * sizeof(QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_EN_PARENT_Entry);
            uint16_t poff = azarac_read_word(pp, offsetof(QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_EN_PARENT_Entry, offset));
            return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_EN_POOL) + off, AZARAC_PGM_PTR(QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_EN_PARENT_POOL) + poff);
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
