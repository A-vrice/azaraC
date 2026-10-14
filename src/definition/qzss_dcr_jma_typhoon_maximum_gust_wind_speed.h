#pragma once
// AUTO-GENERATED from azarashi 0.17.1 with CI-CD
// Source module : azarashi.definitions.qzss.dcr.typhoon_maximum_gust_wind_speed
// Variable      : qzss_dcr_jma_typhoon_maximum_gust_wind_speed
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

#if (AZARAC_ENABLE_TYPHOON) && (AZARAC_LANG_JA)

#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_POOL[] = "不明\00015m/\00016m/\00017m/\00018m/\00019m/\00020m/\00021m/\00022m/\00023m/\00024m/\00025m/\00026m/\00027m/\00028m/\00029m/\00030m/\00031m/\00032m/\00033m/\00034m/\00035m/\00036m/\00037m/\00038m/\00039m/\00040m/\00041m/\00042m/\00043m/\00044m/\00045m/\00046m/\00047m/\00048m/\00049m/\00050m/\00051m/\00052m/\00053m/\00054m/\00055m/\00056m/\00057m/\00058m/\00059m/\00060m/\00061m/\00062m/\00063m/\00064m/\00065m/\00066m/\00067m/\00068m/\00069m/\00070m/\00071m/\00072m/\00073m/\00074m/\00075m/\00076m/\00077m/\00078m/\00079m/\00080m/\00081m/\00082m/\00083m/\00084m/\00085m/\00086m/\00087m/\00088m/\00089m/\00090m/\00091m/\00092m/\00093m/\00094m/\00095m/\00096m/\00097m/\00098m/\00099m/\000100m\000101m\000102m\000103m\000104m\000105m\000";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_PARENT_POOL[] = "/s\000s\000";
struct QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_PARENT_Entry { uint16_t offset; uint8_t len; };
static const QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_PARENT_Entry QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_PARENT_TABLE[] AZARAC_PROGMEM = {
    {0u, 2u},
    {3u, 1u},
};
struct QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_Entry { uint8_t id; uint8_t parent; uint16_t offset; uint8_t len; };
static const QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_Entry QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_TABLE[] AZARAC_PROGMEM = {
    {0u, 255u, 0u, 6u},
    {15u, 1u, 7u, 4u},
    {16u, 1u, 12u, 4u},
    {17u, 1u, 17u, 4u},
    {18u, 1u, 22u, 4u},
    {19u, 1u, 27u, 4u},
    {20u, 1u, 32u, 4u},
    {21u, 1u, 37u, 4u},
    {22u, 1u, 42u, 4u},
    {23u, 1u, 47u, 4u},
    {24u, 1u, 52u, 4u},
    {25u, 1u, 57u, 4u},
    {26u, 1u, 62u, 4u},
    {27u, 1u, 67u, 4u},
    {28u, 1u, 72u, 4u},
    {29u, 1u, 77u, 4u},
    {30u, 1u, 82u, 4u},
    {31u, 1u, 87u, 4u},
    {32u, 1u, 92u, 4u},
    {33u, 1u, 97u, 4u},
    {34u, 1u, 102u, 4u},
    {35u, 1u, 107u, 4u},
    {36u, 1u, 112u, 4u},
    {37u, 1u, 117u, 4u},
    {38u, 1u, 122u, 4u},
    {39u, 1u, 127u, 4u},
    {40u, 1u, 132u, 4u},
    {41u, 1u, 137u, 4u},
    {42u, 1u, 142u, 4u},
    {43u, 1u, 147u, 4u},
    {44u, 1u, 152u, 4u},
    {45u, 1u, 157u, 4u},
    {46u, 1u, 162u, 4u},
    {47u, 1u, 167u, 4u},
    {48u, 1u, 172u, 4u},
    {49u, 1u, 177u, 4u},
    {50u, 1u, 182u, 4u},
    {51u, 1u, 187u, 4u},
    {52u, 1u, 192u, 4u},
    {53u, 1u, 197u, 4u},
    {54u, 1u, 202u, 4u},
    {55u, 1u, 207u, 4u},
    {56u, 1u, 212u, 4u},
    {57u, 1u, 217u, 4u},
    {58u, 1u, 222u, 4u},
    {59u, 1u, 227u, 4u},
    {60u, 1u, 232u, 4u},
    {61u, 1u, 237u, 4u},
    {62u, 1u, 242u, 4u},
    {63u, 1u, 247u, 4u},
    {64u, 1u, 252u, 4u},
    {65u, 1u, 257u, 4u},
    {66u, 1u, 262u, 4u},
    {67u, 1u, 267u, 4u},
    {68u, 1u, 272u, 4u},
    {69u, 1u, 277u, 4u},
    {70u, 1u, 282u, 4u},
    {71u, 1u, 287u, 4u},
    {72u, 1u, 292u, 4u},
    {73u, 1u, 297u, 4u},
    {74u, 1u, 302u, 4u},
    {75u, 1u, 307u, 4u},
    {76u, 1u, 312u, 4u},
    {77u, 1u, 317u, 4u},
    {78u, 1u, 322u, 4u},
    {79u, 1u, 327u, 4u},
    {80u, 1u, 332u, 4u},
    {81u, 1u, 337u, 4u},
    {82u, 1u, 342u, 4u},
    {83u, 1u, 347u, 4u},
    {84u, 1u, 352u, 4u},
    {85u, 1u, 357u, 4u},
    {86u, 1u, 362u, 4u},
    {87u, 1u, 367u, 4u},
    {88u, 1u, 372u, 4u},
    {89u, 1u, 377u, 4u},
    {90u, 1u, 382u, 4u},
    {91u, 1u, 387u, 4u},
    {92u, 1u, 392u, 4u},
    {93u, 1u, 397u, 4u},
    {94u, 1u, 402u, 4u},
    {95u, 1u, 407u, 4u},
    {96u, 1u, 412u, 4u},
    {97u, 1u, 417u, 4u},
    {98u, 1u, 422u, 4u},
    {99u, 1u, 427u, 4u},
    {100u, 0u, 432u, 4u},
    {101u, 0u, 437u, 4u},
    {102u, 0u, 442u, 4u},
    {103u, 0u, 447u, 4u},
    {104u, 0u, 452u, 4u},
    {105u, 0u, 457u, 4u},
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_typhoon_maximum_gust_wind_speed_lookup(uint8_t id) noexcept {
    uint8_t lo = 0, hi = 92;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        const char* AZARAC_PROGMEM ep = reinterpret_cast<const char*>(&QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_TABLE[mid]);
        uint8_t eid = static_cast<uint8_t>(pgm_read_byte(ep + offsetof(QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_Entry, id)));
        if (eid == id) {
            uint16_t off = pgm_read_word(ep + offsetof(QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_Entry, offset));
            uint8_t n = pgm_read_byte(ep + offsetof(QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_Entry, len));
            uint8_t pi = pgm_read_byte(ep + offsetof(QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_Entry, parent));
            if (pi == 255u) return azarac_pgm_view(QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_POOL + off, n);
            const char* AZARAC_PROGMEM pp = reinterpret_cast<const char*>(&QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_PARENT_TABLE[pi]);
            uint16_t poff = pgm_read_word(pp + offsetof(QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_PARENT_Entry, offset));
            uint8_t pn = pgm_read_byte(pp + offsetof(QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_PARENT_Entry, len));
            return azarac_pgm_join(QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_POOL + off, n, QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_PARENT_POOL + poff, pn);
        }
        if (eid < id) lo = static_cast<uint8_t>(mid + 1); else hi = mid;
    }
    return std::nullopt;
}
#else
struct QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_Entry { uint8_t id; const char* label; };
inline constexpr QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_Entry QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_TABLE[] = {
    {0u, "不明"},
    {15u, "15m/s"},
    {16u, "16m/s"},
    {17u, "17m/s"},
    {18u, "18m/s"},
    {19u, "19m/s"},
    {20u, "20m/s"},
    {21u, "21m/s"},
    {22u, "22m/s"},
    {23u, "23m/s"},
    {24u, "24m/s"},
    {25u, "25m/s"},
    {26u, "26m/s"},
    {27u, "27m/s"},
    {28u, "28m/s"},
    {29u, "29m/s"},
    {30u, "30m/s"},
    {31u, "31m/s"},
    {32u, "32m/s"},
    {33u, "33m/s"},
    {34u, "34m/s"},
    {35u, "35m/s"},
    {36u, "36m/s"},
    {37u, "37m/s"},
    {38u, "38m/s"},
    {39u, "39m/s"},
    {40u, "40m/s"},
    {41u, "41m/s"},
    {42u, "42m/s"},
    {43u, "43m/s"},
    {44u, "44m/s"},
    {45u, "45m/s"},
    {46u, "46m/s"},
    {47u, "47m/s"},
    {48u, "48m/s"},
    {49u, "49m/s"},
    {50u, "50m/s"},
    {51u, "51m/s"},
    {52u, "52m/s"},
    {53u, "53m/s"},
    {54u, "54m/s"},
    {55u, "55m/s"},
    {56u, "56m/s"},
    {57u, "57m/s"},
    {58u, "58m/s"},
    {59u, "59m/s"},
    {60u, "60m/s"},
    {61u, "61m/s"},
    {62u, "62m/s"},
    {63u, "63m/s"},
    {64u, "64m/s"},
    {65u, "65m/s"},
    {66u, "66m/s"},
    {67u, "67m/s"},
    {68u, "68m/s"},
    {69u, "69m/s"},
    {70u, "70m/s"},
    {71u, "71m/s"},
    {72u, "72m/s"},
    {73u, "73m/s"},
    {74u, "74m/s"},
    {75u, "75m/s"},
    {76u, "76m/s"},
    {77u, "77m/s"},
    {78u, "78m/s"},
    {79u, "79m/s"},
    {80u, "80m/s"},
    {81u, "81m/s"},
    {82u, "82m/s"},
    {83u, "83m/s"},
    {84u, "84m/s"},
    {85u, "85m/s"},
    {86u, "86m/s"},
    {87u, "87m/s"},
    {88u, "88m/s"},
    {89u, "89m/s"},
    {90u, "90m/s"},
    {91u, "91m/s"},
    {92u, "92m/s"},
    {93u, "93m/s"},
    {94u, "94m/s"},
    {95u, "95m/s"},
    {96u, "96m/s"},
    {97u, "97m/s"},
    {98u, "98m/s"},
    {99u, "99m/s"},
    {100u, "100m/s"},
    {101u, "101m/s"},
    {102u, "102m/s"},
    {103u, "103m/s"},
    {104u, "104m/s"},
    {105u, "105m/s"},};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_typhoon_maximum_gust_wind_speed_lookup(uint8_t id) noexcept {
    uint8_t lo = 0, hi = 92;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        if (QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_TABLE[mid].id == id) {
            const char* s = QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_TABLE[mid].label;
            return s ? std::optional<std::string_view>(std::string_view{s}) : std::nullopt;
        }
        if (QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_TABLE[mid].id < id) lo = mid + 1;
        else hi = mid;
    }
    return std::nullopt;
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_typhoon_maximum_gust_wind_speed_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_typhoon_maximum_gust_wind_speed_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
