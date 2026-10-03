#pragma once
// AUTO-GENERATED from azarashi 0.17.0 with CI-CD
// Source module : azarashi.definitions.qzss.dcr.marine_forecast_region
// Variable      : qzss_dcr_jma_marine_forecast_region_en
// Entries       : 49
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

#if (AZARAC_ENABLE_MARINE) && (AZARAC_LANG_EN)

#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCR_JMA_MARINE_FORECAST_REGION_EN_POOL[] = "Northern Part of Japan Sea and Southern Part of Okhotsk Sea\000Sea East of Sakhalin\000Sea West of Sakhalin\000Sea off Abashiri\000Soya Kaikyo\000Sea West of Hokkaido\000Sea South and East of Hokkaido\000Sea East of Hokkaido\000Sea off Kushiro\000Sea off Hidaka\000Tsugaru Kaikyo\000Sea off Hiyama and Tsugaru\000Sea off Sanriku\000Eastern Sea off Sanriku\000Western Sea off Sanriku\000Sea off Kanto\000Northern Sea off Kanto\000Southern Sea off Kanto\000Central Part of Japan Sea\000Sea off Southern Coast of Maritime Province\000Sea off Akita\000Sea off Sado\000Sea off Noto\000Sea off Tokai\000Eastern Sea off Tokai\000Western Sea off Tokai\000Southern Sea off Tokai\000Sea off Shikoku and Setonaikai\000Setonaikai\000Northern Sea off Shikoku\000Southern Sea off Shikoku\000Western Part of Japan Sea\000Northwestern Part of Japan Sea\000Sea East of Oki Syoto and around Wakasa Wan\000Sea West of Oki Syoto\000Tsushima Kaikyo\000Sea West of Kyushu\000Sea West of Cheju Island\000Sea West of Nagasaki\000Sea Southwest of Meshima\000Sea South of Kyushu and Hyuga Nada\000Hyuga Nada\000Sea off Kagoshima\000Sea around Amami\000Sea around Okinawa\000Southern Part of East China Sea\000Sea East of Okinawa\000Sea South of Okinawa\000Other Marine Forecast Region\000";
struct QZSS_DCR_JMA_MARINE_FORECAST_REGION_EN_Entry { uint16_t id; uint16_t offset; uint16_t len; };
static const QZSS_DCR_JMA_MARINE_FORECAST_REGION_EN_Entry QZSS_DCR_JMA_MARINE_FORECAST_REGION_EN_TABLE[] AZARAC_PROGMEM = {
    {1000u, 0u, 59u},
    {1010u, 60u, 20u},
    {1020u, 81u, 20u},
    {1030u, 102u, 16u},
    {1040u, 119u, 11u},
    {1050u, 131u, 20u},
    {1100u, 152u, 30u},
    {1110u, 183u, 20u},
    {1120u, 204u, 15u},
    {1130u, 220u, 14u},
    {1140u, 235u, 14u},
    {1150u, 250u, 26u},
    {2000u, 277u, 15u},
    {2010u, 293u, 23u},
    {2020u, 317u, 23u},
    {3000u, 341u, 13u},
    {3010u, 355u, 22u},
    {3020u, 378u, 22u},
    {3100u, 401u, 25u},
    {3110u, 427u, 43u},
    {3120u, 471u, 13u},
    {3130u, 485u, 12u},
    {3140u, 498u, 12u},
    {3200u, 511u, 13u},
    {3210u, 525u, 21u},
    {3220u, 547u, 21u},
    {3230u, 569u, 22u},
    {4000u, 592u, 30u},
    {4010u, 623u, 10u},
    {4020u, 634u, 24u},
    {4030u, 659u, 24u},
    {4100u, 684u, 25u},
    {4110u, 710u, 30u},
    {4120u, 741u, 43u},
    {4130u, 785u, 21u},
    {5000u, 807u, 15u},
    {5100u, 823u, 18u},
    {5110u, 842u, 24u},
    {5120u, 867u, 20u},
    {5130u, 888u, 24u},
    {5200u, 913u, 34u},
    {5210u, 948u, 10u},
    {5220u, 959u, 17u},
    {5230u, 977u, 16u},
    {6000u, 994u, 18u},
    {6010u, 1013u, 31u},
    {6020u, 1045u, 19u},
    {6030u, 1065u, 20u},
    {10000u, 1086u, 28u},
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_marine_forecast_region_en_lookup(uint16_t id) noexcept {
    uint8_t lo = 0, hi = 49;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        const char* AZARAC_PROGMEM ep = reinterpret_cast<const char*>(&QZSS_DCR_JMA_MARINE_FORECAST_REGION_EN_TABLE[mid]);
        uint16_t eid = pgm_read_word(ep + offsetof(QZSS_DCR_JMA_MARINE_FORECAST_REGION_EN_Entry, id));
        if (eid == id) {
            uint16_t off = pgm_read_word(ep + offsetof(QZSS_DCR_JMA_MARINE_FORECAST_REGION_EN_Entry, offset));
            uint16_t n = pgm_read_word(ep + offsetof(QZSS_DCR_JMA_MARINE_FORECAST_REGION_EN_Entry, len));
            return azarac_pgm_view(QZSS_DCR_JMA_MARINE_FORECAST_REGION_EN_POOL + off, n);
        }
        if (eid < id) lo = static_cast<uint8_t>(mid + 1); else hi = mid;
    }
    return std::nullopt;
}
#else
struct QZSS_DCR_JMA_MARINE_FORECAST_REGION_EN_Entry { uint16_t id; const char* label; };
inline constexpr QZSS_DCR_JMA_MARINE_FORECAST_REGION_EN_Entry QZSS_DCR_JMA_MARINE_FORECAST_REGION_EN_TABLE[] = {
    {1000u, "Northern Part of Japan Sea and Southern Part of Okhotsk Sea"},
    {1010u, "Sea East of Sakhalin"},
    {1020u, "Sea West of Sakhalin"},
    {1030u, "Sea off Abashiri"},
    {1040u, "Soya Kaikyo"},
    {1050u, "Sea West of Hokkaido"},
    {1100u, "Sea South and East of Hokkaido"},
    {1110u, "Sea East of Hokkaido"},
    {1120u, "Sea off Kushiro"},
    {1130u, "Sea off Hidaka"},
    {1140u, "Tsugaru Kaikyo"},
    {1150u, "Sea off Hiyama and Tsugaru"},
    {2000u, "Sea off Sanriku"},
    {2010u, "Eastern Sea off Sanriku"},
    {2020u, "Western Sea off Sanriku"},
    {3000u, "Sea off Kanto"},
    {3010u, "Northern Sea off Kanto"},
    {3020u, "Southern Sea off Kanto"},
    {3100u, "Central Part of Japan Sea"},
    {3110u, "Sea off Southern Coast of Maritime Province"},
    {3120u, "Sea off Akita"},
    {3130u, "Sea off Sado"},
    {3140u, "Sea off Noto"},
    {3200u, "Sea off Tokai"},
    {3210u, "Eastern Sea off Tokai"},
    {3220u, "Western Sea off Tokai"},
    {3230u, "Southern Sea off Tokai"},
    {4000u, "Sea off Shikoku and Setonaikai"},
    {4010u, "Setonaikai"},
    {4020u, "Northern Sea off Shikoku"},
    {4030u, "Southern Sea off Shikoku"},
    {4100u, "Western Part of Japan Sea"},
    {4110u, "Northwestern Part of Japan Sea"},
    {4120u, "Sea East of Oki Syoto and around Wakasa Wan"},
    {4130u, "Sea West of Oki Syoto"},
    {5000u, "Tsushima Kaikyo"},
    {5100u, "Sea West of Kyushu"},
    {5110u, "Sea West of Cheju Island"},
    {5120u, "Sea West of Nagasaki"},
    {5130u, "Sea Southwest of Meshima"},
    {5200u, "Sea South of Kyushu and Hyuga Nada"},
    {5210u, "Hyuga Nada"},
    {5220u, "Sea off Kagoshima"},
    {5230u, "Sea around Amami"},
    {6000u, "Sea around Okinawa"},
    {6010u, "Southern Part of East China Sea"},
    {6020u, "Sea East of Okinawa"},
    {6030u, "Sea South of Okinawa"},
    {10000u, "Other Marine Forecast Region"},};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_marine_forecast_region_en_lookup(uint16_t id) noexcept {
    uint8_t lo = 0, hi = 49;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        if (QZSS_DCR_JMA_MARINE_FORECAST_REGION_EN_TABLE[mid].id == id) {
            const char* s = QZSS_DCR_JMA_MARINE_FORECAST_REGION_EN_TABLE[mid].label;
            return s ? std::optional<std::string_view>(std::string_view{s}) : std::nullopt;
        }
        if (QZSS_DCR_JMA_MARINE_FORECAST_REGION_EN_TABLE[mid].id < id) lo = mid + 1;
        else hi = mid;
    }
    return std::nullopt;
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_marine_forecast_region_en_lookup(uint16_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_marine_forecast_region_en_lookup(uint16_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
