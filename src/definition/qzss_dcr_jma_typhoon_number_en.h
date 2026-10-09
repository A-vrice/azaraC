#pragma once
// AUTO-GENERATED from azarashi 0.17.1 with CI-CD
// Source module : azarashi.definitions.qzss.dcr.typhoon_number
// Variable      : qzss_dcr_jma_typhoon_number_en
// Entries       : 99
// Strategy      : array

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

inline constexpr uint8_t QZSS_DCR_JMA_TYPHOON_NUMBER_EN_BASE = 1;
inline constexpr uint8_t QZSS_DCR_JMA_TYPHOON_NUMBER_EN_SIZE = 99;
#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCR_JMA_TYPHOON_NUMBER_EN_POOL[] = "No. 1\000No. 2\000No. 3\000No. 4\000No. 5\000No. 6\000No. 7\000No. 8\000No. 9\000No. 10\000No. 11\000No. 12\000No. 13\000No. 14\000No. 15\000No. 16\000No. 17\000No. 18\000No. 19\000No. 20\000No. 21\000No. 22\000No. 23\000No. 24\000No. 25\000No. 26\000No. 27\000No. 28\000No. 29\000No. 30\000No. 31\000No. 32\000No. 33\000No. 34\000No. 35\000No. 36\000No. 37\000No. 38\000No. 39\000No. 40\000No. 41\000No. 42\000No. 43\000No. 44\000No. 45\000No. 46\000No. 47\000No. 48\000No. 49\000No. 50\000No. 51\000No. 52\000No. 53\000No. 54\000No. 55\000No. 56\000No. 57\000No. 58\000No. 59\000No. 60\000No. 61\000No. 62\000No. 63\000No. 64\000No. 65\000No. 66\000No. 67\000No. 68\000No. 69\000No. 70\000No. 71\000No. 72\000No. 73\000No. 74\000No. 75\000No. 76\000No. 77\000No. 78\000No. 79\000No. 80\000No. 81\000No. 82\000No. 83\000No. 84\000No. 85\000No. 86\000No. 87\000No. 88\000No. 89\000No. 90\000No. 91\000No. 92\000No. 93\000No. 94\000No. 95\000No. 96\000No. 97\000No. 98\000No. 99\000";
struct QZSS_DCR_JMA_TYPHOON_NUMBER_EN_Entry { uint16_t offset; uint16_t len; };
static const QZSS_DCR_JMA_TYPHOON_NUMBER_EN_Entry QZSS_DCR_JMA_TYPHOON_NUMBER_EN_TABLE[] AZARAC_PROGMEM = {
    {0u, 5u},
    {6u, 5u},
    {12u, 5u},
    {18u, 5u},
    {24u, 5u},
    {30u, 5u},
    {36u, 5u},
    {42u, 5u},
    {48u, 5u},
    {54u, 6u},
    {61u, 6u},
    {68u, 6u},
    {75u, 6u},
    {82u, 6u},
    {89u, 6u},
    {96u, 6u},
    {103u, 6u},
    {110u, 6u},
    {117u, 6u},
    {124u, 6u},
    {131u, 6u},
    {138u, 6u},
    {145u, 6u},
    {152u, 6u},
    {159u, 6u},
    {166u, 6u},
    {173u, 6u},
    {180u, 6u},
    {187u, 6u},
    {194u, 6u},
    {201u, 6u},
    {208u, 6u},
    {215u, 6u},
    {222u, 6u},
    {229u, 6u},
    {236u, 6u},
    {243u, 6u},
    {250u, 6u},
    {257u, 6u},
    {264u, 6u},
    {271u, 6u},
    {278u, 6u},
    {285u, 6u},
    {292u, 6u},
    {299u, 6u},
    {306u, 6u},
    {313u, 6u},
    {320u, 6u},
    {327u, 6u},
    {334u, 6u},
    {341u, 6u},
    {348u, 6u},
    {355u, 6u},
    {362u, 6u},
    {369u, 6u},
    {376u, 6u},
    {383u, 6u},
    {390u, 6u},
    {397u, 6u},
    {404u, 6u},
    {411u, 6u},
    {418u, 6u},
    {425u, 6u},
    {432u, 6u},
    {439u, 6u},
    {446u, 6u},
    {453u, 6u},
    {460u, 6u},
    {467u, 6u},
    {474u, 6u},
    {481u, 6u},
    {488u, 6u},
    {495u, 6u},
    {502u, 6u},
    {509u, 6u},
    {516u, 6u},
    {523u, 6u},
    {530u, 6u},
    {537u, 6u},
    {544u, 6u},
    {551u, 6u},
    {558u, 6u},
    {565u, 6u},
    {572u, 6u},
    {579u, 6u},
    {586u, 6u},
    {593u, 6u},
    {600u, 6u},
    {607u, 6u},
    {614u, 6u},
    {621u, 6u},
    {628u, 6u},
    {635u, 6u},
    {642u, 6u},
    {649u, 6u},
    {656u, 6u},
    {663u, 6u},
    {670u, 6u},
    {677u, 6u}
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_typhoon_number_en_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCR_JMA_TYPHOON_NUMBER_EN_BASE || id >= QZSS_DCR_JMA_TYPHOON_NUMBER_EN_BASE + QZSS_DCR_JMA_TYPHOON_NUMBER_EN_SIZE) return std::nullopt;
    const char* AZARAC_PROGMEM p = reinterpret_cast<const char*>(&QZSS_DCR_JMA_TYPHOON_NUMBER_EN_TABLE[id - 1u]);
    uint16_t off = pgm_read_word(p + offsetof(QZSS_DCR_JMA_TYPHOON_NUMBER_EN_Entry, offset));
    uint16_t n = pgm_read_word(p + offsetof(QZSS_DCR_JMA_TYPHOON_NUMBER_EN_Entry, len));
    return azarac_pgm_view(QZSS_DCR_JMA_TYPHOON_NUMBER_EN_POOL + off, n);
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
