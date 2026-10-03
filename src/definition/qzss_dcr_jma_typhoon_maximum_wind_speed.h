#pragma once
// AUTO-GENERATED from azarashi 0.17.0 with CI-CD
// Source module : azarashi.definitions.qzss.dcr.typhoon_maximum_wind_speed
// Variable      : qzss_dcr_jma_typhoon_maximum_wind_speed
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
static const char AZARAC_PROGMEM QZSS_DCR_JMA_TYPHOON_MAXIMUM_WIND_SPEED_POOL[] = "不明\00015m/s\00016m/s\00017m/s\00018m/s\00019m/s\00020m/s\00021m/s\00022m/s\00023m/s\00024m/s\00025m/s\00026m/s\00027m/s\00028m/s\00029m/s\00030m/s\00031m/s\00032m/s\00033m/s\00034m/s\00035m/s\00036m/s\00037m/s\00038m/s\00039m/s\00040m/s\00041m/s\00042m/s\00043m/s\00044m/s\00045m/s\00046m/s\00047m/s\00048m/s\00049m/s\00050m/s\00051m/s\00052m/s\00053m/s\00054m/s\00055m/s\00056m/s\00057m/s\00058m/s\00059m/s\00060m/s\00061m/s\00062m/s\00063m/s\00064m/s\00065m/s\00066m/s\00067m/s\00068m/s\00069m/s\00070m/s\00071m/s\00072m/s\00073m/s\00074m/s\00075m/s\00076m/s\00077m/s\00078m/s\00079m/s\00080m/s\00081m/s\00082m/s\00083m/s\00084m/s\00085m/s\00086m/s\00087m/s\00088m/s\00089m/s\00090m/s\00091m/s\00092m/s\00093m/s\00094m/s\00095m/s\00096m/s\00097m/s\00098m/s\00099m/s\000100m/s\000101m/s\000102m/s\000103m/s\000104m/s\000105m/s\000";
struct QZSS_DCR_JMA_TYPHOON_MAXIMUM_WIND_SPEED_Entry { uint8_t id; uint16_t offset; uint16_t len; };
static const QZSS_DCR_JMA_TYPHOON_MAXIMUM_WIND_SPEED_Entry QZSS_DCR_JMA_TYPHOON_MAXIMUM_WIND_SPEED_TABLE[] AZARAC_PROGMEM = {
    {0u, 0u, 6u},
    {15u, 7u, 5u},
    {16u, 13u, 5u},
    {17u, 19u, 5u},
    {18u, 25u, 5u},
    {19u, 31u, 5u},
    {20u, 37u, 5u},
    {21u, 43u, 5u},
    {22u, 49u, 5u},
    {23u, 55u, 5u},
    {24u, 61u, 5u},
    {25u, 67u, 5u},
    {26u, 73u, 5u},
    {27u, 79u, 5u},
    {28u, 85u, 5u},
    {29u, 91u, 5u},
    {30u, 97u, 5u},
    {31u, 103u, 5u},
    {32u, 109u, 5u},
    {33u, 115u, 5u},
    {34u, 121u, 5u},
    {35u, 127u, 5u},
    {36u, 133u, 5u},
    {37u, 139u, 5u},
    {38u, 145u, 5u},
    {39u, 151u, 5u},
    {40u, 157u, 5u},
    {41u, 163u, 5u},
    {42u, 169u, 5u},
    {43u, 175u, 5u},
    {44u, 181u, 5u},
    {45u, 187u, 5u},
    {46u, 193u, 5u},
    {47u, 199u, 5u},
    {48u, 205u, 5u},
    {49u, 211u, 5u},
    {50u, 217u, 5u},
    {51u, 223u, 5u},
    {52u, 229u, 5u},
    {53u, 235u, 5u},
    {54u, 241u, 5u},
    {55u, 247u, 5u},
    {56u, 253u, 5u},
    {57u, 259u, 5u},
    {58u, 265u, 5u},
    {59u, 271u, 5u},
    {60u, 277u, 5u},
    {61u, 283u, 5u},
    {62u, 289u, 5u},
    {63u, 295u, 5u},
    {64u, 301u, 5u},
    {65u, 307u, 5u},
    {66u, 313u, 5u},
    {67u, 319u, 5u},
    {68u, 325u, 5u},
    {69u, 331u, 5u},
    {70u, 337u, 5u},
    {71u, 343u, 5u},
    {72u, 349u, 5u},
    {73u, 355u, 5u},
    {74u, 361u, 5u},
    {75u, 367u, 5u},
    {76u, 373u, 5u},
    {77u, 379u, 5u},
    {78u, 385u, 5u},
    {79u, 391u, 5u},
    {80u, 397u, 5u},
    {81u, 403u, 5u},
    {82u, 409u, 5u},
    {83u, 415u, 5u},
    {84u, 421u, 5u},
    {85u, 427u, 5u},
    {86u, 433u, 5u},
    {87u, 439u, 5u},
    {88u, 445u, 5u},
    {89u, 451u, 5u},
    {90u, 457u, 5u},
    {91u, 463u, 5u},
    {92u, 469u, 5u},
    {93u, 475u, 5u},
    {94u, 481u, 5u},
    {95u, 487u, 5u},
    {96u, 493u, 5u},
    {97u, 499u, 5u},
    {98u, 505u, 5u},
    {99u, 511u, 5u},
    {100u, 517u, 6u},
    {101u, 524u, 6u},
    {102u, 531u, 6u},
    {103u, 538u, 6u},
    {104u, 545u, 6u},
    {105u, 552u, 6u},
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_typhoon_maximum_wind_speed_lookup(uint8_t id) noexcept {
    uint8_t lo = 0, hi = 92;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        const char* AZARAC_PROGMEM ep = reinterpret_cast<const char*>(&QZSS_DCR_JMA_TYPHOON_MAXIMUM_WIND_SPEED_TABLE[mid]);
        uint8_t eid = static_cast<uint8_t>(pgm_read_byte(ep + offsetof(QZSS_DCR_JMA_TYPHOON_MAXIMUM_WIND_SPEED_Entry, id)));
        if (eid == id) {
            uint16_t off = pgm_read_word(ep + offsetof(QZSS_DCR_JMA_TYPHOON_MAXIMUM_WIND_SPEED_Entry, offset));
            uint16_t n = pgm_read_word(ep + offsetof(QZSS_DCR_JMA_TYPHOON_MAXIMUM_WIND_SPEED_Entry, len));
            return azarac_pgm_view(QZSS_DCR_JMA_TYPHOON_MAXIMUM_WIND_SPEED_POOL + off, n);
        }
        if (eid < id) lo = static_cast<uint8_t>(mid + 1); else hi = mid;
    }
    return std::nullopt;
}
#else
struct QZSS_DCR_JMA_TYPHOON_MAXIMUM_WIND_SPEED_Entry { uint8_t id; const char* label; };
inline constexpr QZSS_DCR_JMA_TYPHOON_MAXIMUM_WIND_SPEED_Entry QZSS_DCR_JMA_TYPHOON_MAXIMUM_WIND_SPEED_TABLE[] = {
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
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_typhoon_maximum_wind_speed_lookup(uint8_t id) noexcept {
    uint8_t lo = 0, hi = 92;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        if (QZSS_DCR_JMA_TYPHOON_MAXIMUM_WIND_SPEED_TABLE[mid].id == id) {
            const char* s = QZSS_DCR_JMA_TYPHOON_MAXIMUM_WIND_SPEED_TABLE[mid].label;
            return s ? std::optional<std::string_view>(std::string_view{s}) : std::nullopt;
        }
        if (QZSS_DCR_JMA_TYPHOON_MAXIMUM_WIND_SPEED_TABLE[mid].id < id) lo = mid + 1;
        else hi = mid;
    }
    return std::nullopt;
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_typhoon_maximum_wind_speed_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_typhoon_maximum_wind_speed_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
