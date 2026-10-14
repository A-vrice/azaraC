#pragma once
// AUTO-GENERATED from azarashi 0.17.1 with CI-CD
// Source module : azarashi.definitions.qzss.dcr.typhoon_maximum_gust_wind_speed
// Variable      : qzss_dcr_jma_typhoon_maximum_gust_wind_speed_en
// Entries       : 92
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

#if (AZARAC_ENABLE_TYPHOON) && (AZARAC_LANG_EN)

#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_EN_POOL[] = "Unknown\00015 m\00016 m\00017 m\00018 m\00019 m\00020 m\00021 m\00022 m\00023 m\00024 m\00025 m\00026 m\00027 m\00028 m\00029 m\00030 m\00031 m\00032 m\00033 m\00034 m\00035 m\00036 m\00037 m\00038 m\00039 m\00040 m\00041 m\00042 m\00043 m\00044 m\00045 m\00046 m\00047 m\00048 m\00049 m\00050 m\00051 m\00052 m\00053 m\00054 m\00055 m\00056 m\00057 m\00058 m\00059 m\00060 m\00061 m\00062 m\00063 m\00064 m\00065 m\00066 m\00067 m\00068 m\00069 m\00070 m\00071 m\00072 m\00073 m\00074 m\00075 m\00076 m\00077 m\00078 m\00079 m\00080 m\00081 m\00082 m\00083 m\00084 m\00085 m\00086 m\00087 m\00088 m\00089 m\00090 m\00091 m\00092 m\00093 m\00094 m\00095 m\00096 m\00097 m\00098 m\00099 m\000100 \000101 \000102 \000103 \000104 \000105 \000";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_EN_PARENT_POOL[] = "/s\000m/s\000";
struct QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_EN_PARENT_Entry { uint16_t offset; uint8_t len; };
static const QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_EN_PARENT_Entry QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_EN_PARENT_TABLE[] AZARAC_PROGMEM = {
    {0u, 2u},
    {3u, 3u},
};
struct QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_EN_Entry { uint8_t id; uint8_t parent; uint16_t offset; uint8_t len; };
static const QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_EN_Entry QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_EN_TABLE[] AZARAC_PROGMEM = {
    {0u, 255u, 0u, 7u},
    {15u, 0u, 8u, 4u},
    {16u, 0u, 13u, 4u},
    {17u, 0u, 18u, 4u},
    {18u, 0u, 23u, 4u},
    {19u, 0u, 28u, 4u},
    {20u, 0u, 33u, 4u},
    {21u, 0u, 38u, 4u},
    {22u, 0u, 43u, 4u},
    {23u, 0u, 48u, 4u},
    {24u, 0u, 53u, 4u},
    {25u, 0u, 58u, 4u},
    {26u, 0u, 63u, 4u},
    {27u, 0u, 68u, 4u},
    {28u, 0u, 73u, 4u},
    {29u, 0u, 78u, 4u},
    {30u, 0u, 83u, 4u},
    {31u, 0u, 88u, 4u},
    {32u, 0u, 93u, 4u},
    {33u, 0u, 98u, 4u},
    {34u, 0u, 103u, 4u},
    {35u, 0u, 108u, 4u},
    {36u, 0u, 113u, 4u},
    {37u, 0u, 118u, 4u},
    {38u, 0u, 123u, 4u},
    {39u, 0u, 128u, 4u},
    {40u, 0u, 133u, 4u},
    {41u, 0u, 138u, 4u},
    {42u, 0u, 143u, 4u},
    {43u, 0u, 148u, 4u},
    {44u, 0u, 153u, 4u},
    {45u, 0u, 158u, 4u},
    {46u, 0u, 163u, 4u},
    {47u, 0u, 168u, 4u},
    {48u, 0u, 173u, 4u},
    {49u, 0u, 178u, 4u},
    {50u, 0u, 183u, 4u},
    {51u, 0u, 188u, 4u},
    {52u, 0u, 193u, 4u},
    {53u, 0u, 198u, 4u},
    {54u, 0u, 203u, 4u},
    {55u, 0u, 208u, 4u},
    {56u, 0u, 213u, 4u},
    {57u, 0u, 218u, 4u},
    {58u, 0u, 223u, 4u},
    {59u, 0u, 228u, 4u},
    {60u, 0u, 233u, 4u},
    {61u, 0u, 238u, 4u},
    {62u, 0u, 243u, 4u},
    {63u, 0u, 248u, 4u},
    {64u, 0u, 253u, 4u},
    {65u, 0u, 258u, 4u},
    {66u, 0u, 263u, 4u},
    {67u, 0u, 268u, 4u},
    {68u, 0u, 273u, 4u},
    {69u, 0u, 278u, 4u},
    {70u, 0u, 283u, 4u},
    {71u, 0u, 288u, 4u},
    {72u, 0u, 293u, 4u},
    {73u, 0u, 298u, 4u},
    {74u, 0u, 303u, 4u},
    {75u, 0u, 308u, 4u},
    {76u, 0u, 313u, 4u},
    {77u, 0u, 318u, 4u},
    {78u, 0u, 323u, 4u},
    {79u, 0u, 328u, 4u},
    {80u, 0u, 333u, 4u},
    {81u, 0u, 338u, 4u},
    {82u, 0u, 343u, 4u},
    {83u, 0u, 348u, 4u},
    {84u, 0u, 353u, 4u},
    {85u, 0u, 358u, 4u},
    {86u, 0u, 363u, 4u},
    {87u, 0u, 368u, 4u},
    {88u, 0u, 373u, 4u},
    {89u, 0u, 378u, 4u},
    {90u, 0u, 383u, 4u},
    {91u, 0u, 388u, 4u},
    {92u, 0u, 393u, 4u},
    {93u, 0u, 398u, 4u},
    {94u, 0u, 403u, 4u},
    {95u, 0u, 408u, 4u},
    {96u, 0u, 413u, 4u},
    {97u, 0u, 418u, 4u},
    {98u, 0u, 423u, 4u},
    {99u, 0u, 428u, 4u},
    {100u, 1u, 433u, 4u},
    {101u, 1u, 438u, 4u},
    {102u, 1u, 443u, 4u},
    {103u, 1u, 448u, 4u},
    {104u, 1u, 453u, 4u},
    {105u, 1u, 458u, 4u},
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_typhoon_maximum_gust_wind_speed_en_lookup(uint8_t id) noexcept {
    uint8_t lo = 0, hi = 92;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        const char* AZARAC_PROGMEM ep = reinterpret_cast<const char*>(&QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_EN_TABLE[mid]);
        uint8_t eid = static_cast<uint8_t>(pgm_read_byte(ep + offsetof(QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_EN_Entry, id)));
        if (eid == id) {
            uint16_t off = pgm_read_word(ep + offsetof(QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_EN_Entry, offset));
            uint8_t n = pgm_read_byte(ep + offsetof(QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_EN_Entry, len));
            uint8_t pi = pgm_read_byte(ep + offsetof(QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_EN_Entry, parent));
            if (pi == 255u) return azarac_pgm_view(QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_EN_POOL + off, n);
            const char* AZARAC_PROGMEM pp = reinterpret_cast<const char*>(&QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_EN_PARENT_TABLE[pi]);
            uint16_t poff = pgm_read_word(pp + offsetof(QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_EN_PARENT_Entry, offset));
            uint8_t pn = pgm_read_byte(pp + offsetof(QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_EN_PARENT_Entry, len));
            return azarac_pgm_join(QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_EN_POOL + off, n, QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_EN_PARENT_POOL + poff, pn);
        }
        if (eid < id) lo = static_cast<uint8_t>(mid + 1); else hi = mid;
    }
    return std::nullopt;
}
#else
struct QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_EN_Entry { uint8_t id; const char* label; };
inline constexpr QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_EN_Entry QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_EN_TABLE[] = {
    {0u, "Unknown"},
    {15u, "15 m/s"},
    {16u, "16 m/s"},
    {17u, "17 m/s"},
    {18u, "18 m/s"},
    {19u, "19 m/s"},
    {20u, "20 m/s"},
    {21u, "21 m/s"},
    {22u, "22 m/s"},
    {23u, "23 m/s"},
    {24u, "24 m/s"},
    {25u, "25 m/s"},
    {26u, "26 m/s"},
    {27u, "27 m/s"},
    {28u, "28 m/s"},
    {29u, "29 m/s"},
    {30u, "30 m/s"},
    {31u, "31 m/s"},
    {32u, "32 m/s"},
    {33u, "33 m/s"},
    {34u, "34 m/s"},
    {35u, "35 m/s"},
    {36u, "36 m/s"},
    {37u, "37 m/s"},
    {38u, "38 m/s"},
    {39u, "39 m/s"},
    {40u, "40 m/s"},
    {41u, "41 m/s"},
    {42u, "42 m/s"},
    {43u, "43 m/s"},
    {44u, "44 m/s"},
    {45u, "45 m/s"},
    {46u, "46 m/s"},
    {47u, "47 m/s"},
    {48u, "48 m/s"},
    {49u, "49 m/s"},
    {50u, "50 m/s"},
    {51u, "51 m/s"},
    {52u, "52 m/s"},
    {53u, "53 m/s"},
    {54u, "54 m/s"},
    {55u, "55 m/s"},
    {56u, "56 m/s"},
    {57u, "57 m/s"},
    {58u, "58 m/s"},
    {59u, "59 m/s"},
    {60u, "60 m/s"},
    {61u, "61 m/s"},
    {62u, "62 m/s"},
    {63u, "63 m/s"},
    {64u, "64 m/s"},
    {65u, "65 m/s"},
    {66u, "66 m/s"},
    {67u, "67 m/s"},
    {68u, "68 m/s"},
    {69u, "69 m/s"},
    {70u, "70 m/s"},
    {71u, "71 m/s"},
    {72u, "72 m/s"},
    {73u, "73 m/s"},
    {74u, "74 m/s"},
    {75u, "75 m/s"},
    {76u, "76 m/s"},
    {77u, "77 m/s"},
    {78u, "78 m/s"},
    {79u, "79 m/s"},
    {80u, "80 m/s"},
    {81u, "81 m/s"},
    {82u, "82 m/s"},
    {83u, "83 m/s"},
    {84u, "84 m/s"},
    {85u, "85 m/s"},
    {86u, "86 m/s"},
    {87u, "87 m/s"},
    {88u, "88 m/s"},
    {89u, "89 m/s"},
    {90u, "90 m/s"},
    {91u, "91 m/s"},
    {92u, "92 m/s"},
    {93u, "93 m/s"},
    {94u, "94 m/s"},
    {95u, "95 m/s"},
    {96u, "96 m/s"},
    {97u, "97 m/s"},
    {98u, "98 m/s"},
    {99u, "99 m/s"},
    {100u, "100 m/s"},
    {101u, "101 m/s"},
    {102u, "102 m/s"},
    {103u, "103 m/s"},
    {104u, "104 m/s"},
    {105u, "105 m/s"},};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_typhoon_maximum_gust_wind_speed_en_lookup(uint8_t id) noexcept {
    uint8_t lo = 0, hi = 92;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        if (QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_EN_TABLE[mid].id == id) {
            const char* s = QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_EN_TABLE[mid].label;
            return s ? std::optional<std::string_view>(std::string_view{s}) : std::nullopt;
        }
        if (QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_EN_TABLE[mid].id < id) lo = mid + 1;
        else hi = mid;
    }
    return std::nullopt;
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_typhoon_maximum_gust_wind_speed_en_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_typhoon_maximum_gust_wind_speed_en_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
