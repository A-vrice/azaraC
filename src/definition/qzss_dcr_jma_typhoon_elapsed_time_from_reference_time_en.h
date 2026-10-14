#pragma once
// AUTO-GENERATED from azarashi 0.17.1 with CI-CD
// Source module : azarashi.definitions.qzss.dcr.typhoon_elapsed_time_from_reference_time
// Variable      : qzss_dcr_jma_typhoon_elapsed_time_from_reference_time_en
// Entries       : 128
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

inline constexpr uint8_t QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_EN_BASE = 0;
inline constexpr uint8_t QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_EN_SIZE = 128;
#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_EN_POOL[] = "0\0001 hour\0002\0003\0004\0005\0006\0007\0008\0009\00010\00011\00012\00013\00014\00015\00016\00017\00018\00019\00020\00021\00022\00023\00024\00025\00026\00027\00028\00029\00030\00031\00032\00033\00034\00035\00036\00037\00038\00039\00040\00041\00042\00043\00044\00045\00046\00047\00048\00049\00050\00051\00052\00053\00054\00055\00056\00057\00058\00059\00060\00061\00062\00063\00064\00065\00066\00067\00068\00069\00070\00071\00072\00073\00074\00075\00076\00077\00078\00079\00080\00081\00082\00083\00084\00085\00086\00087\00088\00089\00090\00091\00092\00093\00094\00095\00096\00097\00098\00099\000100\000101\000102\000103\000104\000105\000106\000107\000108\000109\000110\000111\000112\000113\000114\000115\000116\000117\000118\000119\000120\000121\000122\000123\000124\000125\000126\000127\000";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_EN_PARENT_POOL[] = " ahead\000 hours ahead\000";
struct QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_EN_PARENT_Entry { uint16_t offset; };
static const QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_EN_PARENT_Entry QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_EN_PARENT_TABLE[] AZARAC_PROGMEM = {
    {0u},
    {7u},
};
struct QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_EN_Entry { uint16_t offset; uint8_t parent; };
static const QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_EN_Entry QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_EN_TABLE[] AZARAC_PROGMEM = {
    {0u, 1u},
    {2u, 0u},
    {9u, 1u},
    {11u, 1u},
    {13u, 1u},
    {15u, 1u},
    {17u, 1u},
    {19u, 1u},
    {21u, 1u},
    {23u, 1u},
    {25u, 1u},
    {28u, 1u},
    {31u, 1u},
    {34u, 1u},
    {37u, 1u},
    {40u, 1u},
    {43u, 1u},
    {46u, 1u},
    {49u, 1u},
    {52u, 1u},
    {55u, 1u},
    {58u, 1u},
    {61u, 1u},
    {64u, 1u},
    {67u, 1u},
    {70u, 1u},
    {73u, 1u},
    {76u, 1u},
    {79u, 1u},
    {82u, 1u},
    {85u, 1u},
    {88u, 1u},
    {91u, 1u},
    {94u, 1u},
    {97u, 1u},
    {100u, 1u},
    {103u, 1u},
    {106u, 1u},
    {109u, 1u},
    {112u, 1u},
    {115u, 1u},
    {118u, 1u},
    {121u, 1u},
    {124u, 1u},
    {127u, 1u},
    {130u, 1u},
    {133u, 1u},
    {136u, 1u},
    {139u, 1u},
    {142u, 1u},
    {145u, 1u},
    {148u, 1u},
    {151u, 1u},
    {154u, 1u},
    {157u, 1u},
    {160u, 1u},
    {163u, 1u},
    {166u, 1u},
    {169u, 1u},
    {172u, 1u},
    {175u, 1u},
    {178u, 1u},
    {181u, 1u},
    {184u, 1u},
    {187u, 1u},
    {190u, 1u},
    {193u, 1u},
    {196u, 1u},
    {199u, 1u},
    {202u, 1u},
    {205u, 1u},
    {208u, 1u},
    {211u, 1u},
    {214u, 1u},
    {217u, 1u},
    {220u, 1u},
    {223u, 1u},
    {226u, 1u},
    {229u, 1u},
    {232u, 1u},
    {235u, 1u},
    {238u, 1u},
    {241u, 1u},
    {244u, 1u},
    {247u, 1u},
    {250u, 1u},
    {253u, 1u},
    {256u, 1u},
    {259u, 1u},
    {262u, 1u},
    {265u, 1u},
    {268u, 1u},
    {271u, 1u},
    {274u, 1u},
    {277u, 1u},
    {280u, 1u},
    {283u, 1u},
    {286u, 1u},
    {289u, 1u},
    {292u, 1u},
    {295u, 1u},
    {299u, 1u},
    {303u, 1u},
    {307u, 1u},
    {311u, 1u},
    {315u, 1u},
    {319u, 1u},
    {323u, 1u},
    {327u, 1u},
    {331u, 1u},
    {335u, 1u},
    {339u, 1u},
    {343u, 1u},
    {347u, 1u},
    {351u, 1u},
    {355u, 1u},
    {359u, 1u},
    {363u, 1u},
    {367u, 1u},
    {371u, 1u},
    {375u, 1u},
    {379u, 1u},
    {383u, 1u},
    {387u, 1u},
    {391u, 1u},
    {395u, 1u},
    {399u, 1u},
    {403u, 1u}
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_typhoon_elapsed_time_from_reference_time_en_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_EN_BASE || id >= QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_EN_BASE + QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_EN_SIZE) return std::nullopt;
    const char* AZARAC_PROGMEM p = reinterpret_cast<const char*>(&QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_EN_TABLE[id - 0u]);
    uint16_t off = pgm_read_word(p + offsetof(QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_EN_Entry, offset));
    uint8_t pi = pgm_read_byte(p + offsetof(QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_EN_Entry, parent));
    if (pi == 255u) return azarac_pgm_view_z(QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_EN_POOL + off);
    const char* AZARAC_PROGMEM pp = reinterpret_cast<const char*>(&QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_EN_PARENT_TABLE[pi]);
    uint16_t poff = pgm_read_word(pp + offsetof(QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_EN_PARENT_Entry, offset));
    return azarac_pgm_join_z(QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_EN_POOL + off, QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_EN_PARENT_POOL + poff);
}
#else
inline constexpr const char* QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_EN_TABLE[] = {
    "0 hours ahead",
    "1 hour ahead",
    "2 hours ahead",
    "3 hours ahead",
    "4 hours ahead",
    "5 hours ahead",
    "6 hours ahead",
    "7 hours ahead",
    "8 hours ahead",
    "9 hours ahead",
    "10 hours ahead",
    "11 hours ahead",
    "12 hours ahead",
    "13 hours ahead",
    "14 hours ahead",
    "15 hours ahead",
    "16 hours ahead",
    "17 hours ahead",
    "18 hours ahead",
    "19 hours ahead",
    "20 hours ahead",
    "21 hours ahead",
    "22 hours ahead",
    "23 hours ahead",
    "24 hours ahead",
    "25 hours ahead",
    "26 hours ahead",
    "27 hours ahead",
    "28 hours ahead",
    "29 hours ahead",
    "30 hours ahead",
    "31 hours ahead",
    "32 hours ahead",
    "33 hours ahead",
    "34 hours ahead",
    "35 hours ahead",
    "36 hours ahead",
    "37 hours ahead",
    "38 hours ahead",
    "39 hours ahead",
    "40 hours ahead",
    "41 hours ahead",
    "42 hours ahead",
    "43 hours ahead",
    "44 hours ahead",
    "45 hours ahead",
    "46 hours ahead",
    "47 hours ahead",
    "48 hours ahead",
    "49 hours ahead",
    "50 hours ahead",
    "51 hours ahead",
    "52 hours ahead",
    "53 hours ahead",
    "54 hours ahead",
    "55 hours ahead",
    "56 hours ahead",
    "57 hours ahead",
    "58 hours ahead",
    "59 hours ahead",
    "60 hours ahead",
    "61 hours ahead",
    "62 hours ahead",
    "63 hours ahead",
    "64 hours ahead",
    "65 hours ahead",
    "66 hours ahead",
    "67 hours ahead",
    "68 hours ahead",
    "69 hours ahead",
    "70 hours ahead",
    "71 hours ahead",
    "72 hours ahead",
    "73 hours ahead",
    "74 hours ahead",
    "75 hours ahead",
    "76 hours ahead",
    "77 hours ahead",
    "78 hours ahead",
    "79 hours ahead",
    "80 hours ahead",
    "81 hours ahead",
    "82 hours ahead",
    "83 hours ahead",
    "84 hours ahead",
    "85 hours ahead",
    "86 hours ahead",
    "87 hours ahead",
    "88 hours ahead",
    "89 hours ahead",
    "90 hours ahead",
    "91 hours ahead",
    "92 hours ahead",
    "93 hours ahead",
    "94 hours ahead",
    "95 hours ahead",
    "96 hours ahead",
    "97 hours ahead",
    "98 hours ahead",
    "99 hours ahead",
    "100 hours ahead",
    "101 hours ahead",
    "102 hours ahead",
    "103 hours ahead",
    "104 hours ahead",
    "105 hours ahead",
    "106 hours ahead",
    "107 hours ahead",
    "108 hours ahead",
    "109 hours ahead",
    "110 hours ahead",
    "111 hours ahead",
    "112 hours ahead",
    "113 hours ahead",
    "114 hours ahead",
    "115 hours ahead",
    "116 hours ahead",
    "117 hours ahead",
    "118 hours ahead",
    "119 hours ahead",
    "120 hours ahead",
    "121 hours ahead",
    "122 hours ahead",
    "123 hours ahead",
    "124 hours ahead",
    "125 hours ahead",
    "126 hours ahead",
    "127 hours ahead"
};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_typhoon_elapsed_time_from_reference_time_en_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_EN_BASE || id >= QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_EN_BASE + QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_EN_SIZE) return std::nullopt;
    const char* s = QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_EN_TABLE[id - QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_EN_BASE];
    return s ? std::optional<std::string_view>(std::string_view{s}) : std::nullopt;
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_typhoon_elapsed_time_from_reference_time_en_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_typhoon_elapsed_time_from_reference_time_en_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
