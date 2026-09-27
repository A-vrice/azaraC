#pragma once
// AUTO-GENERATED from azarashi 0.17.0 with CI-CD
// Source module : azarashi.definitions.qzss.dcr.typhoon_maximum_wind_speed
// Variable      : qzss_dcr_jma_typhoon_maximum_wind_speed_en
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
static const char AZARAC_PROGMEM QZSS_DCR_JMA_TYPHOON_MAXIMUM_WIND_SPEED_EN_POOL[] = "Unknown\00015 m/s\00016 m/s\00017 m/s\00018 m/s\00019 m/s\00020 m/s\00021 m/s\00022 m/s\00023 m/s\00024 m/s\00025 m/s\00026 m/s\00027 m/s\00028 m/s\00029 m/s\00030 m/s\00031 m/s\00032 m/s\00033 m/s\00034 m/s\00035 m/s\00036 m/s\00037 m/s\00038 m/s\00039 m/s\00040 m/s\00041 m/s\00042 m/s\00043 m/s\00044 m/s\00045 m/s\00046 m/s\00047 m/s\00048 m/s\00049 m/s\00050 m/s\00051 m/s\00052 m/s\00053 m/s\00054 m/s\00055 m/s\00056 m/s\00057 m/s\00058 m/s\00059 m/s\00060 m/s\00061 m/s\00062 m/s\00063 m/s\00064 m/s\00065 m/s\00066 m/s\00067 m/s\00068 m/s\00069 m/s\00070 m/s\00071 m/s\00072 m/s\00073 m/s\00074 m/s\00075 m/s\00076 m/s\00077 m/s\00078 m/s\00079 m/s\00080 m/s\00081 m/s\00082 m/s\00083 m/s\00084 m/s\00085 m/s\00086 m/s\00087 m/s\00088 m/s\00089 m/s\00090 m/s\00091 m/s\00092 m/s\00093 m/s\00094 m/s\00095 m/s\00096 m/s\00097 m/s\00098 m/s\00099 m/s\000100 m/s\000101 m/s\000102 m/s\000103 m/s\000104 m/s\000105 m/s\000";
struct QZSS_DCR_JMA_TYPHOON_MAXIMUM_WIND_SPEED_EN_Entry { uint8_t id; uint16_t offset; uint16_t len; };
static const QZSS_DCR_JMA_TYPHOON_MAXIMUM_WIND_SPEED_EN_Entry QZSS_DCR_JMA_TYPHOON_MAXIMUM_WIND_SPEED_EN_TABLE[] AZARAC_PROGMEM = {
    {0u, 0u, 7u},
    {15u, 8u, 6u},
    {16u, 15u, 6u},
    {17u, 22u, 6u},
    {18u, 29u, 6u},
    {19u, 36u, 6u},
    {20u, 43u, 6u},
    {21u, 50u, 6u},
    {22u, 57u, 6u},
    {23u, 64u, 6u},
    {24u, 71u, 6u},
    {25u, 78u, 6u},
    {26u, 85u, 6u},
    {27u, 92u, 6u},
    {28u, 99u, 6u},
    {29u, 106u, 6u},
    {30u, 113u, 6u},
    {31u, 120u, 6u},
    {32u, 127u, 6u},
    {33u, 134u, 6u},
    {34u, 141u, 6u},
    {35u, 148u, 6u},
    {36u, 155u, 6u},
    {37u, 162u, 6u},
    {38u, 169u, 6u},
    {39u, 176u, 6u},
    {40u, 183u, 6u},
    {41u, 190u, 6u},
    {42u, 197u, 6u},
    {43u, 204u, 6u},
    {44u, 211u, 6u},
    {45u, 218u, 6u},
    {46u, 225u, 6u},
    {47u, 232u, 6u},
    {48u, 239u, 6u},
    {49u, 246u, 6u},
    {50u, 253u, 6u},
    {51u, 260u, 6u},
    {52u, 267u, 6u},
    {53u, 274u, 6u},
    {54u, 281u, 6u},
    {55u, 288u, 6u},
    {56u, 295u, 6u},
    {57u, 302u, 6u},
    {58u, 309u, 6u},
    {59u, 316u, 6u},
    {60u, 323u, 6u},
    {61u, 330u, 6u},
    {62u, 337u, 6u},
    {63u, 344u, 6u},
    {64u, 351u, 6u},
    {65u, 358u, 6u},
    {66u, 365u, 6u},
    {67u, 372u, 6u},
    {68u, 379u, 6u},
    {69u, 386u, 6u},
    {70u, 393u, 6u},
    {71u, 400u, 6u},
    {72u, 407u, 6u},
    {73u, 414u, 6u},
    {74u, 421u, 6u},
    {75u, 428u, 6u},
    {76u, 435u, 6u},
    {77u, 442u, 6u},
    {78u, 449u, 6u},
    {79u, 456u, 6u},
    {80u, 463u, 6u},
    {81u, 470u, 6u},
    {82u, 477u, 6u},
    {83u, 484u, 6u},
    {84u, 491u, 6u},
    {85u, 498u, 6u},
    {86u, 505u, 6u},
    {87u, 512u, 6u},
    {88u, 519u, 6u},
    {89u, 526u, 6u},
    {90u, 533u, 6u},
    {91u, 540u, 6u},
    {92u, 547u, 6u},
    {93u, 554u, 6u},
    {94u, 561u, 6u},
    {95u, 568u, 6u},
    {96u, 575u, 6u},
    {97u, 582u, 6u},
    {98u, 589u, 6u},
    {99u, 596u, 6u},
    {100u, 603u, 7u},
    {101u, 611u, 7u},
    {102u, 619u, 7u},
    {103u, 627u, 7u},
    {104u, 635u, 7u},
    {105u, 643u, 7u},
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_typhoon_maximum_wind_speed_en_lookup(uint8_t id) noexcept {
    uint8_t lo = 0, hi = 92;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        const char* AZARAC_PROGMEM ep = reinterpret_cast<const char*>(&QZSS_DCR_JMA_TYPHOON_MAXIMUM_WIND_SPEED_EN_TABLE[mid]);
        uint8_t eid = static_cast<uint8_t>(pgm_read_byte(ep + offsetof(QZSS_DCR_JMA_TYPHOON_MAXIMUM_WIND_SPEED_EN_Entry, id)));
        if (eid == id) {
            uint16_t off = pgm_read_word(ep + offsetof(QZSS_DCR_JMA_TYPHOON_MAXIMUM_WIND_SPEED_EN_Entry, offset));
            uint16_t n = pgm_read_word(ep + offsetof(QZSS_DCR_JMA_TYPHOON_MAXIMUM_WIND_SPEED_EN_Entry, len));
            return azarac_pgm_view(QZSS_DCR_JMA_TYPHOON_MAXIMUM_WIND_SPEED_EN_POOL + off, n);
        }
        if (eid < id) lo = static_cast<uint8_t>(mid + 1); else hi = mid;
    }
    return std::nullopt;
}
#else
struct QZSS_DCR_JMA_TYPHOON_MAXIMUM_WIND_SPEED_EN_Entry { uint8_t id; const char* label; };
inline constexpr QZSS_DCR_JMA_TYPHOON_MAXIMUM_WIND_SPEED_EN_Entry QZSS_DCR_JMA_TYPHOON_MAXIMUM_WIND_SPEED_EN_TABLE[] = {
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
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_typhoon_maximum_wind_speed_en_lookup(uint8_t id) noexcept {
    uint8_t lo = 0, hi = 92;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        if (QZSS_DCR_JMA_TYPHOON_MAXIMUM_WIND_SPEED_EN_TABLE[mid].id == id) {
            const char* s = QZSS_DCR_JMA_TYPHOON_MAXIMUM_WIND_SPEED_EN_TABLE[mid].label;
            return s ? std::optional<std::string_view>(std::string_view{s}) : std::nullopt;
        }
        if (QZSS_DCR_JMA_TYPHOON_MAXIMUM_WIND_SPEED_EN_TABLE[mid].id < id) lo = mid + 1;
        else hi = mid;
    }
    return std::nullopt;
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_typhoon_maximum_wind_speed_en_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_typhoon_maximum_wind_speed_en_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
