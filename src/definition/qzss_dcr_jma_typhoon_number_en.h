#pragma once
// AUTO-GENERATED from azarashi 0.17.1 — do not edit
// azarashi.definitions.qzss.dcr.typhoon_number → qzss_dcr_jma_typhoon_number_en: 99 entries, strategy array
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

inline constexpr uint8_t QZSS_DCR_JMA_TYPHOON_NUMBER_EN_BASE = 1;
inline constexpr uint8_t QZSS_DCR_JMA_TYPHOON_NUMBER_EN_SIZE = 99;
#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCR_JMA_TYPHOON_NUMBER_EN_POOL[] = "1\0002\0003\0004\0005\0006\0007\0008\0009\0000\0001\0002\0003\0004\0005\0006\0007\0008\0009\0000\0001\0002\0003\0004\0005\0006\0007\0008\0009\0000\0001\0002\0003\0004\0005\0006\0007\0008\0009\0000\0001\0002\0003\0004\0005\0006\0007\0008\0009\0000\0001\0002\0003\0004\0005\0006\0007\0008\0009\0000\0001\0002\0003\0004\0005\0006\0007\0008\0009\0000\0001\0002\0003\0004\0005\0006\0007\0008\0009\0000\0001\0002\0003\0004\0005\0006\0007\0008\0009\0000\0001\0002\0003\0004\0005\0006\0007\0008\0009\000";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_TYPHOON_NUMBER_EN_PARENT_POOL[] = "No. \000No. 1\000No. 2\000No. 3\000No. 4\000No. 5\000No. 6\000No. 7\000No. 8\000No. 9\000";
struct QZSS_DCR_JMA_TYPHOON_NUMBER_EN_PARENT_Entry { uint16_t offset; };
static const QZSS_DCR_JMA_TYPHOON_NUMBER_EN_PARENT_Entry QZSS_DCR_JMA_TYPHOON_NUMBER_EN_PARENT_TABLE[] AZARAC_PROGMEM = {
    {0u},
    {5u},
    {11u},
    {17u},
    {23u},
    {29u},
    {35u},
    {41u},
    {47u},
    {53u},
};
struct QZSS_DCR_JMA_TYPHOON_NUMBER_EN_Entry { uint16_t offset; uint8_t parent; };
static const QZSS_DCR_JMA_TYPHOON_NUMBER_EN_Entry QZSS_DCR_JMA_TYPHOON_NUMBER_EN_TABLE[] AZARAC_PROGMEM = {
    {0u, 0u},
    {2u, 0u},
    {4u, 0u},
    {6u, 0u},
    {8u, 0u},
    {10u, 0u},
    {12u, 0u},
    {14u, 0u},
    {16u, 0u},
    {18u, 1u},
    {20u, 1u},
    {22u, 1u},
    {24u, 1u},
    {26u, 1u},
    {28u, 1u},
    {30u, 1u},
    {32u, 1u},
    {34u, 1u},
    {36u, 1u},
    {38u, 2u},
    {40u, 2u},
    {42u, 2u},
    {44u, 2u},
    {46u, 2u},
    {48u, 2u},
    {50u, 2u},
    {52u, 2u},
    {54u, 2u},
    {56u, 2u},
    {58u, 3u},
    {60u, 3u},
    {62u, 3u},
    {64u, 3u},
    {66u, 3u},
    {68u, 3u},
    {70u, 3u},
    {72u, 3u},
    {74u, 3u},
    {76u, 3u},
    {78u, 4u},
    {80u, 4u},
    {82u, 4u},
    {84u, 4u},
    {86u, 4u},
    {88u, 4u},
    {90u, 4u},
    {92u, 4u},
    {94u, 4u},
    {96u, 4u},
    {98u, 5u},
    {100u, 5u},
    {102u, 5u},
    {104u, 5u},
    {106u, 5u},
    {108u, 5u},
    {110u, 5u},
    {112u, 5u},
    {114u, 5u},
    {116u, 5u},
    {118u, 6u},
    {120u, 6u},
    {122u, 6u},
    {124u, 6u},
    {126u, 6u},
    {128u, 6u},
    {130u, 6u},
    {132u, 6u},
    {134u, 6u},
    {136u, 6u},
    {138u, 7u},
    {140u, 7u},
    {142u, 7u},
    {144u, 7u},
    {146u, 7u},
    {148u, 7u},
    {150u, 7u},
    {152u, 7u},
    {154u, 7u},
    {156u, 7u},
    {158u, 8u},
    {160u, 8u},
    {162u, 8u},
    {164u, 8u},
    {166u, 8u},
    {168u, 8u},
    {170u, 8u},
    {172u, 8u},
    {174u, 8u},
    {176u, 8u},
    {178u, 9u},
    {180u, 9u},
    {182u, 9u},
    {184u, 9u},
    {186u, 9u},
    {188u, 9u},
    {190u, 9u},
    {192u, 9u},
    {194u, 9u},
    {196u, 9u}
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_typhoon_number_en_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCR_JMA_TYPHOON_NUMBER_EN_BASE || id >= QZSS_DCR_JMA_TYPHOON_NUMBER_EN_BASE + QZSS_DCR_JMA_TYPHOON_NUMBER_EN_SIZE) return std::nullopt;
    azarac_pgm_ptr p = AZARAC_PGM_PTR(QZSS_DCR_JMA_TYPHOON_NUMBER_EN_TABLE) + static_cast<size_t>(id - 1u) * sizeof(QZSS_DCR_JMA_TYPHOON_NUMBER_EN_Entry);
    uint16_t off = azarac_read_word(p, offsetof(QZSS_DCR_JMA_TYPHOON_NUMBER_EN_Entry, offset));
    uint8_t pi = azarac_read_byte(p, offsetof(QZSS_DCR_JMA_TYPHOON_NUMBER_EN_Entry, parent));
    if (pi == 255u) return azarac_pgm_view_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_TYPHOON_NUMBER_EN_POOL) + off);
    azarac_pgm_ptr pp = AZARAC_PGM_PTR(QZSS_DCR_JMA_TYPHOON_NUMBER_EN_PARENT_TABLE) + static_cast<size_t>(pi) * sizeof(QZSS_DCR_JMA_TYPHOON_NUMBER_EN_PARENT_Entry);
    uint16_t poff = azarac_read_word(pp, offsetof(QZSS_DCR_JMA_TYPHOON_NUMBER_EN_PARENT_Entry, offset));
    return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_TYPHOON_NUMBER_EN_PARENT_POOL) + poff, AZARAC_PGM_PTR(QZSS_DCR_JMA_TYPHOON_NUMBER_EN_POOL) + off);
}
#else
inline constexpr const char* QZSS_DCR_JMA_TYPHOON_NUMBER_EN_TABLE[] = {
    "No. 1",
    "No. 2",
    "No. 3",
    "No. 4",
    "No. 5",
    "No. 6",
    "No. 7",
    "No. 8",
    "No. 9",
    "No. 10",
    "No. 11",
    "No. 12",
    "No. 13",
    "No. 14",
    "No. 15",
    "No. 16",
    "No. 17",
    "No. 18",
    "No. 19",
    "No. 20",
    "No. 21",
    "No. 22",
    "No. 23",
    "No. 24",
    "No. 25",
    "No. 26",
    "No. 27",
    "No. 28",
    "No. 29",
    "No. 30",
    "No. 31",
    "No. 32",
    "No. 33",
    "No. 34",
    "No. 35",
    "No. 36",
    "No. 37",
    "No. 38",
    "No. 39",
    "No. 40",
    "No. 41",
    "No. 42",
    "No. 43",
    "No. 44",
    "No. 45",
    "No. 46",
    "No. 47",
    "No. 48",
    "No. 49",
    "No. 50",
    "No. 51",
    "No. 52",
    "No. 53",
    "No. 54",
    "No. 55",
    "No. 56",
    "No. 57",
    "No. 58",
    "No. 59",
    "No. 60",
    "No. 61",
    "No. 62",
    "No. 63",
    "No. 64",
    "No. 65",
    "No. 66",
    "No. 67",
    "No. 68",
    "No. 69",
    "No. 70",
    "No. 71",
    "No. 72",
    "No. 73",
    "No. 74",
    "No. 75",
    "No. 76",
    "No. 77",
    "No. 78",
    "No. 79",
    "No. 80",
    "No. 81",
    "No. 82",
    "No. 83",
    "No. 84",
    "No. 85",
    "No. 86",
    "No. 87",
    "No. 88",
    "No. 89",
    "No. 90",
    "No. 91",
    "No. 92",
    "No. 93",
    "No. 94",
    "No. 95",
    "No. 96",
    "No. 97",
    "No. 98",
    "No. 99"
};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_typhoon_number_en_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCR_JMA_TYPHOON_NUMBER_EN_BASE || id >= QZSS_DCR_JMA_TYPHOON_NUMBER_EN_BASE + QZSS_DCR_JMA_TYPHOON_NUMBER_EN_SIZE) return std::nullopt;
    const char* s = QZSS_DCR_JMA_TYPHOON_NUMBER_EN_TABLE[id - QZSS_DCR_JMA_TYPHOON_NUMBER_EN_BASE];
    return s ? std::optional<std::string_view>(std::string_view{s}) : std::nullopt;
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_typhoon_number_en_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_typhoon_number_en_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
