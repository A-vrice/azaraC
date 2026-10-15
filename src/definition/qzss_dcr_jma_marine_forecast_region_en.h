#pragma once
// AUTO-GENERATED from azarashi 0.17.1 with CI-CD
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
static const char AZARAC_PROGMEM QZSS_DCR_JMA_MARINE_FORECAST_REGION_EN_POOL[] = "ern Part of Japan Sea and Southern Part of Okhotsk Sea\000Sakhalin\000Sakhalin\000Abashiri\000Soya Kaikyo\000Hokkaido\000 and East of Hokkaido\000Hokkaido\000Kushiro\000Hidaka\000Tsugaru Kaikyo\000Hiyama and Tsugaru\000anriku\000Eastern Sea off Sanriku\000Western Sea off Sanriku\000Kanto\000ern Sea off Kanto\000Sea off Kanto\000Central Part of Japan Sea\000outhern Coast of Maritime Province\000Akita\000ado\000Noto\000Sea off Tokai\000Eastern Sea off Tokai\000Western Sea off Tokai\000Southern Sea off Tokai\000hikoku and Setonaikai\000Setonaikai\000ern Sea off Shikoku\000Sea off Shikoku\000Western Part of Japan Sea\000western Part of Japan Sea\000Oki Syoto and around Wakasa Wan\000Oki Syoto\000Tsushima Kaikyo\000Kyushu\000Cheju Island\000Nagasaki\000west of Meshima\000 of Kyushu and Hyuga Nada\000Hyuga Nada\000Kagoshima\000around Amami\000around Okinawa\000Part of East China Sea\000Okinawa\000 of Okinawa\000Other Marine Forecast Region\000";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_MARINE_FORECAST_REGION_EN_PARENT_POOL[] = "North\000Sea \000Sea East of \000Sea South\000Sea West of \000Sea off \000Sea off S\000Southern \000";
struct QZSS_DCR_JMA_MARINE_FORECAST_REGION_EN_PARENT_Entry { uint16_t offset; };
static const QZSS_DCR_JMA_MARINE_FORECAST_REGION_EN_PARENT_Entry QZSS_DCR_JMA_MARINE_FORECAST_REGION_EN_PARENT_TABLE[] AZARAC_PROGMEM = {
    {0u},
    {6u},
    {11u},
    {24u},
    {34u},
    {47u},
    {56u},
    {66u},
};
struct QZSS_DCR_JMA_MARINE_FORECAST_REGION_EN_Entry { uint16_t id; uint8_t parent; uint16_t offset; };
static const QZSS_DCR_JMA_MARINE_FORECAST_REGION_EN_Entry QZSS_DCR_JMA_MARINE_FORECAST_REGION_EN_TABLE[] AZARAC_PROGMEM = {
    {1000u, 0u, 0u},
    {1010u, 2u, 55u},
    {1020u, 4u, 64u},
    {1030u, 5u, 73u},
    {1040u, 255u, 82u},
    {1050u, 4u, 94u},
    {1100u, 3u, 103u},
    {1110u, 2u, 125u},
    {1120u, 5u, 134u},
    {1130u, 5u, 142u},
    {1140u, 255u, 149u},
    {1150u, 5u, 164u},
    {2000u, 6u, 183u},
    {2010u, 255u, 190u},
    {2020u, 255u, 214u},
    {3000u, 5u, 238u},
    {3010u, 0u, 244u},
    {3020u, 7u, 262u},
    {3100u, 255u, 276u},
    {3110u, 6u, 302u},
    {3120u, 5u, 337u},
    {3130u, 6u, 343u},
    {3140u, 5u, 347u},
    {3200u, 255u, 352u},
    {3210u, 255u, 366u},
    {3220u, 255u, 388u},
    {3230u, 255u, 410u},
    {4000u, 6u, 433u},
    {4010u, 255u, 455u},
    {4020u, 0u, 466u},
    {4030u, 7u, 486u},
    {4100u, 255u, 502u},
    {4110u, 0u, 528u},
    {4120u, 2u, 554u},
    {4130u, 4u, 586u},
    {5000u, 255u, 596u},
    {5100u, 4u, 612u},
    {5110u, 4u, 619u},
    {5120u, 4u, 632u},
    {5130u, 3u, 641u},
    {5200u, 3u, 657u},
    {5210u, 255u, 683u},
    {5220u, 5u, 694u},
    {5230u, 1u, 704u},
    {6000u, 1u, 717u},
    {6010u, 7u, 732u},
    {6020u, 2u, 755u},
    {6030u, 3u, 763u},
    {10000u, 255u, 775u},
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_marine_forecast_region_en_lookup(uint16_t id) noexcept {
    uint8_t lo = 0, hi = 49;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        azarac_pgm_ptr ep = AZARAC_PGM_PTR(QZSS_DCR_JMA_MARINE_FORECAST_REGION_EN_TABLE) + static_cast<size_t>(mid) * sizeof(QZSS_DCR_JMA_MARINE_FORECAST_REGION_EN_Entry);
        uint16_t eid = azarac_read_word(ep, offsetof(QZSS_DCR_JMA_MARINE_FORECAST_REGION_EN_Entry, id));
        if (eid == id) {
            uint16_t off = azarac_read_word(ep, offsetof(QZSS_DCR_JMA_MARINE_FORECAST_REGION_EN_Entry, offset));
            uint8_t pi = azarac_read_byte(ep, offsetof(QZSS_DCR_JMA_MARINE_FORECAST_REGION_EN_Entry, parent));
            if (pi == 255u) return azarac_pgm_view_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_MARINE_FORECAST_REGION_EN_POOL) + off);
            azarac_pgm_ptr pp = AZARAC_PGM_PTR(QZSS_DCR_JMA_MARINE_FORECAST_REGION_EN_PARENT_TABLE) + static_cast<size_t>(pi) * sizeof(QZSS_DCR_JMA_MARINE_FORECAST_REGION_EN_PARENT_Entry);
            uint16_t poff = azarac_read_word(pp, offsetof(QZSS_DCR_JMA_MARINE_FORECAST_REGION_EN_PARENT_Entry, offset));
            return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_MARINE_FORECAST_REGION_EN_PARENT_POOL) + poff, AZARAC_PGM_PTR(QZSS_DCR_JMA_MARINE_FORECAST_REGION_EN_POOL) + off);
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
