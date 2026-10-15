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
static const char AZARAC_PROGMEM QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_POOL[] = "不明\0001\0001\0001\0001\0001\0002\0002\0002\0002\0002\0002\0002\0002\0002\0002\0003\0003\0003\0003\0003\0003\0003\0003\0003\0003\0004\0004\0004\0004\0004\0004\0004\0004\0004\0004\0005\0005\0005\0005\0005\0005\0005\0005\0005\0005\0006\0006\0006\0006\0006\0006\0006\0006\0006\0006\0007\0007\0007\0007\0007\0007\0007\0007\0007\0007\0008\0008\0008\0008\0008\0008\0008\0008\0008\0008\0009\0009\0009\0009\0009\0009\0009\0009\0009\0009\00010\00010\00010\00010\00010\00010\000";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_PARENT_POOL[] = "0m/s\0001m/s\0002m/s\0003m/s\0004m/s\0005m/s\0006m/s\0007m/s\0008m/s\0009m/s\000";
struct QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_PARENT_Entry { uint16_t offset; };
static const QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_PARENT_Entry QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_PARENT_TABLE[] AZARAC_PROGMEM = {
    {0u},
    {5u},
    {10u},
    {15u},
    {20u},
    {25u},
    {30u},
    {35u},
    {40u},
    {45u},
};
struct QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_Entry { uint8_t id; uint8_t parent; uint16_t offset; };
static const QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_Entry QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_TABLE[] AZARAC_PROGMEM = {
    {0u, 255u, 0u},
    {15u, 5u, 7u},
    {16u, 6u, 9u},
    {17u, 7u, 11u},
    {18u, 8u, 13u},
    {19u, 9u, 15u},
    {20u, 0u, 17u},
    {21u, 1u, 19u},
    {22u, 2u, 21u},
    {23u, 3u, 23u},
    {24u, 4u, 25u},
    {25u, 5u, 27u},
    {26u, 6u, 29u},
    {27u, 7u, 31u},
    {28u, 8u, 33u},
    {29u, 9u, 35u},
    {30u, 0u, 37u},
    {31u, 1u, 39u},
    {32u, 2u, 41u},
    {33u, 3u, 43u},
    {34u, 4u, 45u},
    {35u, 5u, 47u},
    {36u, 6u, 49u},
    {37u, 7u, 51u},
    {38u, 8u, 53u},
    {39u, 9u, 55u},
    {40u, 0u, 57u},
    {41u, 1u, 59u},
    {42u, 2u, 61u},
    {43u, 3u, 63u},
    {44u, 4u, 65u},
    {45u, 5u, 67u},
    {46u, 6u, 69u},
    {47u, 7u, 71u},
    {48u, 8u, 73u},
    {49u, 9u, 75u},
    {50u, 0u, 77u},
    {51u, 1u, 79u},
    {52u, 2u, 81u},
    {53u, 3u, 83u},
    {54u, 4u, 85u},
    {55u, 5u, 87u},
    {56u, 6u, 89u},
    {57u, 7u, 91u},
    {58u, 8u, 93u},
    {59u, 9u, 95u},
    {60u, 0u, 97u},
    {61u, 1u, 99u},
    {62u, 2u, 101u},
    {63u, 3u, 103u},
    {64u, 4u, 105u},
    {65u, 5u, 107u},
    {66u, 6u, 109u},
    {67u, 7u, 111u},
    {68u, 8u, 113u},
    {69u, 9u, 115u},
    {70u, 0u, 117u},
    {71u, 1u, 119u},
    {72u, 2u, 121u},
    {73u, 3u, 123u},
    {74u, 4u, 125u},
    {75u, 5u, 127u},
    {76u, 6u, 129u},
    {77u, 7u, 131u},
    {78u, 8u, 133u},
    {79u, 9u, 135u},
    {80u, 0u, 137u},
    {81u, 1u, 139u},
    {82u, 2u, 141u},
    {83u, 3u, 143u},
    {84u, 4u, 145u},
    {85u, 5u, 147u},
    {86u, 6u, 149u},
    {87u, 7u, 151u},
    {88u, 8u, 153u},
    {89u, 9u, 155u},
    {90u, 0u, 157u},
    {91u, 1u, 159u},
    {92u, 2u, 161u},
    {93u, 3u, 163u},
    {94u, 4u, 165u},
    {95u, 5u, 167u},
    {96u, 6u, 169u},
    {97u, 7u, 171u},
    {98u, 8u, 173u},
    {99u, 9u, 175u},
    {100u, 0u, 177u},
    {101u, 1u, 180u},
    {102u, 2u, 183u},
    {103u, 3u, 186u},
    {104u, 4u, 189u},
    {105u, 5u, 192u},
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_typhoon_maximum_gust_wind_speed_lookup(uint8_t id) noexcept {
    uint8_t lo = 0, hi = 92;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        azarac_pgm_ptr ep = AZARAC_PGM_PTR(QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_TABLE) + static_cast<size_t>(mid) * sizeof(QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_Entry);
        uint8_t eid = static_cast<uint8_t>(azarac_read_byte(ep, offsetof(QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_Entry, id)));
        if (eid == id) {
            uint16_t off = azarac_read_word(ep, offsetof(QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_Entry, offset));
            uint8_t pi = azarac_read_byte(ep, offsetof(QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_Entry, parent));
            if (pi == 255u) return azarac_pgm_view_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_POOL) + off);
            azarac_pgm_ptr pp = AZARAC_PGM_PTR(QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_PARENT_TABLE) + static_cast<size_t>(pi) * sizeof(QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_PARENT_Entry);
            uint16_t poff = azarac_read_word(pp, offsetof(QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_PARENT_Entry, offset));
            return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_POOL) + off, AZARAC_PGM_PTR(QZSS_DCR_JMA_TYPHOON_MAXIMUM_GUST_WIND_SPEED_PARENT_POOL) + poff);
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
