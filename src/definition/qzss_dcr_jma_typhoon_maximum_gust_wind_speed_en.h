#pragma once
// AUTO-GENERATED from azarashi 0.17.1 — do not edit
// azarashi.definitions.qzss.dcr.typhoon_maximum_gust_wind_speed → qzss_dcr_jma_typhoon_maximum_gust_wind_speed_en: 92 entries, strategy binary_search
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

#if (AZARAC_ENABLE_TYPHOON) && (AZARAC_LANG_EN)

#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_EN_POOL[] = "Unknown\0001\0001\0001\0001\0001\0002\0002\0002\0002\0002\0002\0002\0002\0002\0002\0003\0003\0003\0003\0003\0003\0003\0003\0003\0003\0004\0004\0004\0004\0004\0004\0004\0004\0004\0004\0005\0005\0005\0005\0005\0005\0005\0005\0005\0005\0006\0006\0006\0006\0006\0006\0006\0006\0006\0006\0007\0007\0007\0007\0007\0007\0007\0007\0007\0007\0008\0008\0008\0008\0008\0008\0008\0008\0008\0008\0009\0009\0009\0009\0009\0009\0009\0009\0009\0009\00010\00010\00010\00010\00010\00010\000";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_EN_PARENT_POOL[] = "0 m/s\0001 m/s\0002 m/s\0003 m/s\0004 m/s\0005 m/s\0006 m/s\0007 m/s\0008 m/s\0009 m/s\000";
struct QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_EN_PARENT_Entry { uint16_t offset; };
static const QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_EN_PARENT_Entry QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_EN_PARENT_TABLE[] AZARAC_PROGMEM = {
    {0u},
    {6u},
    {12u},
    {18u},
    {24u},
    {30u},
    {36u},
    {42u},
    {48u},
    {54u},
};
struct QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_EN_Entry { uint8_t id; uint8_t parent; uint16_t offset; };
static const QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_EN_Entry QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_EN_TABLE[] AZARAC_PROGMEM = {
    {0u, 255u, 0u},
    {15u, 5u, 8u},
    {16u, 6u, 10u},
    {17u, 7u, 12u},
    {18u, 8u, 14u},
    {19u, 9u, 16u},
    {20u, 0u, 18u},
    {21u, 1u, 20u},
    {22u, 2u, 22u},
    {23u, 3u, 24u},
    {24u, 4u, 26u},
    {25u, 5u, 28u},
    {26u, 6u, 30u},
    {27u, 7u, 32u},
    {28u, 8u, 34u},
    {29u, 9u, 36u},
    {30u, 0u, 38u},
    {31u, 1u, 40u},
    {32u, 2u, 42u},
    {33u, 3u, 44u},
    {34u, 4u, 46u},
    {35u, 5u, 48u},
    {36u, 6u, 50u},
    {37u, 7u, 52u},
    {38u, 8u, 54u},
    {39u, 9u, 56u},
    {40u, 0u, 58u},
    {41u, 1u, 60u},
    {42u, 2u, 62u},
    {43u, 3u, 64u},
    {44u, 4u, 66u},
    {45u, 5u, 68u},
    {46u, 6u, 70u},
    {47u, 7u, 72u},
    {48u, 8u, 74u},
    {49u, 9u, 76u},
    {50u, 0u, 78u},
    {51u, 1u, 80u},
    {52u, 2u, 82u},
    {53u, 3u, 84u},
    {54u, 4u, 86u},
    {55u, 5u, 88u},
    {56u, 6u, 90u},
    {57u, 7u, 92u},
    {58u, 8u, 94u},
    {59u, 9u, 96u},
    {60u, 0u, 98u},
    {61u, 1u, 100u},
    {62u, 2u, 102u},
    {63u, 3u, 104u},
    {64u, 4u, 106u},
    {65u, 5u, 108u},
    {66u, 6u, 110u},
    {67u, 7u, 112u},
    {68u, 8u, 114u},
    {69u, 9u, 116u},
    {70u, 0u, 118u},
    {71u, 1u, 120u},
    {72u, 2u, 122u},
    {73u, 3u, 124u},
    {74u, 4u, 126u},
    {75u, 5u, 128u},
    {76u, 6u, 130u},
    {77u, 7u, 132u},
    {78u, 8u, 134u},
    {79u, 9u, 136u},
    {80u, 0u, 138u},
    {81u, 1u, 140u},
    {82u, 2u, 142u},
    {83u, 3u, 144u},
    {84u, 4u, 146u},
    {85u, 5u, 148u},
    {86u, 6u, 150u},
    {87u, 7u, 152u},
    {88u, 8u, 154u},
    {89u, 9u, 156u},
    {90u, 0u, 158u},
    {91u, 1u, 160u},
    {92u, 2u, 162u},
    {93u, 3u, 164u},
    {94u, 4u, 166u},
    {95u, 5u, 168u},
    {96u, 6u, 170u},
    {97u, 7u, 172u},
    {98u, 8u, 174u},
    {99u, 9u, 176u},
    {100u, 0u, 178u},
    {101u, 1u, 181u},
    {102u, 2u, 184u},
    {103u, 3u, 187u},
    {104u, 4u, 190u},
    {105u, 5u, 193u},
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_typhoon_maximum_gust_wind_speed_en_lookup(uint8_t id) noexcept {
    uint8_t lo = 0, hi = 92;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        azarac_pgm_ptr ep = AZARAC_PGM_PTR(QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_EN_TABLE) + static_cast<size_t>(mid) * sizeof(QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_EN_Entry);
        uint8_t eid = static_cast<uint8_t>(azarac_read_byte(ep, offsetof(QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_EN_Entry, id)));
        if (eid == id) {
            uint16_t off = azarac_read_word(ep, offsetof(QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_EN_Entry, offset));
            uint8_t pi = azarac_read_byte(ep, offsetof(QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_EN_Entry, parent));
            if (pi == 255u) return azarac_pgm_view_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_EN_POOL) + off);
            azarac_pgm_ptr pp = AZARAC_PGM_PTR(QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_EN_PARENT_TABLE) + static_cast<size_t>(pi) * sizeof(QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_EN_PARENT_Entry);
            uint16_t poff = azarac_read_word(pp, offsetof(QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_EN_PARENT_Entry, offset));
            return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_EN_POOL) + off, AZARAC_PGM_PTR(QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_EN_PARENT_POOL) + poff);
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
