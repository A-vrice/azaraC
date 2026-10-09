#pragma once
// AUTO-GENERATED from azarashi 0.17.1 with CI-CD
// Source module : azarashi.definitions.qzss.dcr.hypocenter_magnitude
// Variable      : qzss_dcr_jma_hypocenter_magnitude_en
// Entries       : 103
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

#if (AZARAC_ENABLE_HYPOCENTER || AZARAC_ENABLE_NW_PAC_TSUNAMI) && (AZARAC_LANG_EN)

#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCR_JMA_HYPOCENTER_MAGNITUDE_EN_POOL[] = "0.1\0000.2\0000.3\0000.4\0000.5\0000.6\0000.7\0000.8\0000.9\0001.0\0001.1\0001.2\0001.3\0001.4\0001.5\0001.6\0001.7\0001.8\0001.9\0002.0\0002.1\0002.2\0002.3\0002.4\0002.5\0002.6\0002.7\0002.8\0002.9\0003.0\0003.1\0003.2\0003.3\0003.4\0003.5\0003.6\0003.7\0003.8\0003.9\0004.0\0004.1\0004.2\0004.3\0004.4\0004.5\0004.6\0004.7\0004.8\0004.9\0005.0\0005.1\0005.2\0005.3\0005.4\0005.5\0005.6\0005.7\0005.8\0005.9\0006.0\0006.1\0006.2\0006.3\0006.4\0006.5\0006.6\0006.7\0006.8\0006.9\0007.0\0007.1\0007.2\0007.3\0007.4\0007.5\0007.6\0007.7\0007.8\0007.9\0008.0\0008.1\0008.2\0008.3\0008.4\0008.5\0008.6\0008.7\0008.8\0008.9\0009.0\0009.1\0009.2\0009.3\0009.4\0009.5\0009.6\0009.7\0009.8\0009.9\00010.0\000Over 10.0\000Unknown (Over 8.0)\000Unknown\000";
struct QZSS_DCR_JMA_HYPOCENTER_MAGNITUDE_EN_Entry { uint8_t id; uint16_t offset; uint16_t len; };
static const QZSS_DCR_JMA_HYPOCENTER_MAGNITUDE_EN_Entry QZSS_DCR_JMA_HYPOCENTER_MAGNITUDE_EN_TABLE[] AZARAC_PROGMEM = {
    {1u, 0u, 3u},
    {2u, 4u, 3u},
    {3u, 8u, 3u},
    {4u, 12u, 3u},
    {5u, 16u, 3u},
    {6u, 20u, 3u},
    {7u, 24u, 3u},
    {8u, 28u, 3u},
    {9u, 32u, 3u},
    {10u, 36u, 3u},
    {11u, 40u, 3u},
    {12u, 44u, 3u},
    {13u, 48u, 3u},
    {14u, 52u, 3u},
    {15u, 56u, 3u},
    {16u, 60u, 3u},
    {17u, 64u, 3u},
    {18u, 68u, 3u},
    {19u, 72u, 3u},
    {20u, 76u, 3u},
    {21u, 80u, 3u},
    {22u, 84u, 3u},
    {23u, 88u, 3u},
    {24u, 92u, 3u},
    {25u, 96u, 3u},
    {26u, 100u, 3u},
    {27u, 104u, 3u},
    {28u, 108u, 3u},
    {29u, 112u, 3u},
    {30u, 116u, 3u},
    {31u, 120u, 3u},
    {32u, 124u, 3u},
    {33u, 128u, 3u},
    {34u, 132u, 3u},
    {35u, 136u, 3u},
    {36u, 140u, 3u},
    {37u, 144u, 3u},
    {38u, 148u, 3u},
    {39u, 152u, 3u},
    {40u, 156u, 3u},
    {41u, 160u, 3u},
    {42u, 164u, 3u},
    {43u, 168u, 3u},
    {44u, 172u, 3u},
    {45u, 176u, 3u},
    {46u, 180u, 3u},
    {47u, 184u, 3u},
    {48u, 188u, 3u},
    {49u, 192u, 3u},
    {50u, 196u, 3u},
    {51u, 200u, 3u},
    {52u, 204u, 3u},
    {53u, 208u, 3u},
    {54u, 212u, 3u},
    {55u, 216u, 3u},
    {56u, 220u, 3u},
    {57u, 224u, 3u},
    {58u, 228u, 3u},
    {59u, 232u, 3u},
    {60u, 236u, 3u},
    {61u, 240u, 3u},
    {62u, 244u, 3u},
    {63u, 248u, 3u},
    {64u, 252u, 3u},
    {65u, 256u, 3u},
    {66u, 260u, 3u},
    {67u, 264u, 3u},
    {68u, 268u, 3u},
    {69u, 272u, 3u},
    {70u, 276u, 3u},
    {71u, 280u, 3u},
    {72u, 284u, 3u},
    {73u, 288u, 3u},
    {74u, 292u, 3u},
    {75u, 296u, 3u},
    {76u, 300u, 3u},
    {77u, 304u, 3u},
    {78u, 308u, 3u},
    {79u, 312u, 3u},
    {80u, 316u, 3u},
    {81u, 320u, 3u},
    {82u, 324u, 3u},
    {83u, 328u, 3u},
    {84u, 332u, 3u},
    {85u, 336u, 3u},
    {86u, 340u, 3u},
    {87u, 344u, 3u},
    {88u, 348u, 3u},
    {89u, 352u, 3u},
    {90u, 356u, 3u},
    {91u, 360u, 3u},
    {92u, 364u, 3u},
    {93u, 368u, 3u},
    {94u, 372u, 3u},
    {95u, 376u, 3u},
    {96u, 380u, 3u},
    {97u, 384u, 3u},
    {98u, 388u, 3u},
    {99u, 392u, 3u},
    {100u, 396u, 4u},
    {101u, 401u, 9u},
    {126u, 411u, 18u},
    {127u, 430u, 7u},
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_hypocenter_magnitude_en_lookup(uint8_t id) noexcept {
    uint8_t lo = 0, hi = 103;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        const char* AZARAC_PROGMEM ep = reinterpret_cast<const char*>(&QZSS_DCR_JMA_HYPOCENTER_MAGNITUDE_EN_TABLE[mid]);
        uint8_t eid = static_cast<uint8_t>(pgm_read_byte(ep + offsetof(QZSS_DCR_JMA_HYPOCENTER_MAGNITUDE_EN_Entry, id)));
        if (eid == id) {
            uint16_t off = pgm_read_word(ep + offsetof(QZSS_DCR_JMA_HYPOCENTER_MAGNITUDE_EN_Entry, offset));
            uint16_t n = pgm_read_word(ep + offsetof(QZSS_DCR_JMA_HYPOCENTER_MAGNITUDE_EN_Entry, len));
            return azarac_pgm_view(QZSS_DCR_JMA_HYPOCENTER_MAGNITUDE_EN_POOL + off, n);
        }
        if (eid < id) lo = static_cast<uint8_t>(mid + 1); else hi = mid;
    }
    return std::nullopt;
}
#else
struct QZSS_DCR_JMA_HYPOCENTER_MAGNITUDE_EN_Entry { uint8_t id; const char* label; };
inline constexpr QZSS_DCR_JMA_HYPOCENTER_MAGNITUDE_EN_Entry QZSS_DCR_JMA_HYPOCENTER_MAGNITUDE_EN_TABLE[] = {
    {1u, "0.1"},
    {2u, "0.2"},
    {3u, "0.3"},
    {4u, "0.4"},
    {5u, "0.5"},
    {6u, "0.6"},
    {7u, "0.7"},
    {8u, "0.8"},
    {9u, "0.9"},
    {10u, "1.0"},
    {11u, "1.1"},
    {12u, "1.2"},
    {13u, "1.3"},
    {14u, "1.4"},
    {15u, "1.5"},
    {16u, "1.6"},
    {17u, "1.7"},
    {18u, "1.8"},
    {19u, "1.9"},
    {20u, "2.0"},
    {21u, "2.1"},
    {22u, "2.2"},
    {23u, "2.3"},
    {24u, "2.4"},
    {25u, "2.5"},
    {26u, "2.6"},
    {27u, "2.7"},
    {28u, "2.8"},
    {29u, "2.9"},
    {30u, "3.0"},
    {31u, "3.1"},
    {32u, "3.2"},
    {33u, "3.3"},
    {34u, "3.4"},
    {35u, "3.5"},
    {36u, "3.6"},
    {37u, "3.7"},
    {38u, "3.8"},
    {39u, "3.9"},
    {40u, "4.0"},
    {41u, "4.1"},
    {42u, "4.2"},
    {43u, "4.3"},
    {44u, "4.4"},
    {45u, "4.5"},
    {46u, "4.6"},
    {47u, "4.7"},
    {48u, "4.8"},
    {49u, "4.9"},
    {50u, "5.0"},
    {51u, "5.1"},
    {52u, "5.2"},
    {53u, "5.3"},
    {54u, "5.4"},
    {55u, "5.5"},
    {56u, "5.6"},
    {57u, "5.7"},
    {58u, "5.8"},
    {59u, "5.9"},
    {60u, "6.0"},
    {61u, "6.1"},
    {62u, "6.2"},
    {63u, "6.3"},
    {64u, "6.4"},
    {65u, "6.5"},
    {66u, "6.6"},
    {67u, "6.7"},
    {68u, "6.8"},
    {69u, "6.9"},
    {70u, "7.0"},
    {71u, "7.1"},
    {72u, "7.2"},
    {73u, "7.3"},
    {74u, "7.4"},
    {75u, "7.5"},
    {76u, "7.6"},
    {77u, "7.7"},
    {78u, "7.8"},
    {79u, "7.9"},
    {80u, "8.0"},
    {81u, "8.1"},
    {82u, "8.2"},
    {83u, "8.3"},
    {84u, "8.4"},
    {85u, "8.5"},
    {86u, "8.6"},
    {87u, "8.7"},
    {88u, "8.8"},
    {89u, "8.9"},
    {90u, "9.0"},
    {91u, "9.1"},
    {92u, "9.2"},
    {93u, "9.3"},
    {94u, "9.4"},
    {95u, "9.5"},
    {96u, "9.6"},
    {97u, "9.7"},
    {98u, "9.8"},
    {99u, "9.9"},
    {100u, "10.0"},
    {101u, "Over 10.0"},
    {126u, "Unknown (Over 8.0)"},
    {127u, "Unknown"},};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_hypocenter_magnitude_en_lookup(uint8_t id) noexcept {
    uint8_t lo = 0, hi = 103;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        if (QZSS_DCR_JMA_HYPOCENTER_MAGNITUDE_EN_TABLE[mid].id == id) {
            const char* s = QZSS_DCR_JMA_HYPOCENTER_MAGNITUDE_EN_TABLE[mid].label;
            return s ? std::optional<std::string_view>(std::string_view{s}) : std::nullopt;
        }
        if (QZSS_DCR_JMA_HYPOCENTER_MAGNITUDE_EN_TABLE[mid].id < id) lo = mid + 1;
        else hi = mid;
    }
    return std::nullopt;
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_hypocenter_magnitude_en_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_hypocenter_magnitude_en_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
