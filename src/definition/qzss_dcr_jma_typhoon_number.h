#pragma once
// AUTO-GENERATED from azarashi 0.17.1 with CI-CD
// Source module : azarashi.definitions.qzss.dcr.typhoon_number
// Variable      : qzss_dcr_jma_typhoon_number
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

#if (AZARAC_ENABLE_TYPHOON) && (AZARAC_LANG_JA)

inline constexpr uint8_t QZSS_DCR_JMA_TYPHOON_NUMBER_BASE = 1;
inline constexpr uint8_t QZSS_DCR_JMA_TYPHOON_NUMBER_SIZE = 99;
#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCR_JMA_TYPHOON_NUMBER_POOL[] = "1号\0002号\0003号\0004号\0005号\0006号\0007号\0008号\0009号\0001\0001\0001\0001\0001\0001\0001\0001\0001\0001\0002\0002\0002\0002\0002\0002\0002\0002\0002\0002\0003\0003\0003\0003\0003\0003\0003\0003\0003\0003\0004\0004\0004\0004\0004\0004\0004\0004\0004\0004\0005\0005\0005\0005\0005\0005\0005\0005\0005\0005\0006\0006\0006\0006\0006\0006\0006\0006\0006\0006\0007\0007\0007\0007\0007\0007\0007\0007\0007\0007\0008\0008\0008\0008\0008\0008\0008\0008\0008\0008\0009\0009\0009\0009\0009\0009\0009\0009\0009\0009\000";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_TYPHOON_NUMBER_PARENT_POOL[] = "0号\0001号\0002号\0003号\0004号\0005号\0006号\0007号\0008号\0009号\000";
struct QZSS_DCR_JMA_TYPHOON_NUMBER_PARENT_Entry { uint16_t offset; };
static const QZSS_DCR_JMA_TYPHOON_NUMBER_PARENT_Entry QZSS_DCR_JMA_TYPHOON_NUMBER_PARENT_TABLE[] AZARAC_PROGMEM = {
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
struct QZSS_DCR_JMA_TYPHOON_NUMBER_Entry { uint16_t offset; uint8_t parent; };
static const QZSS_DCR_JMA_TYPHOON_NUMBER_Entry QZSS_DCR_JMA_TYPHOON_NUMBER_TABLE[] AZARAC_PROGMEM = {
    {0u, 255u},
    {5u, 255u},
    {10u, 255u},
    {15u, 255u},
    {20u, 255u},
    {25u, 255u},
    {30u, 255u},
    {35u, 255u},
    {40u, 255u},
    {45u, 0u},
    {47u, 1u},
    {49u, 2u},
    {51u, 3u},
    {53u, 4u},
    {55u, 5u},
    {57u, 6u},
    {59u, 7u},
    {61u, 8u},
    {63u, 9u},
    {65u, 0u},
    {67u, 1u},
    {69u, 2u},
    {71u, 3u},
    {73u, 4u},
    {75u, 5u},
    {77u, 6u},
    {79u, 7u},
    {81u, 8u},
    {83u, 9u},
    {85u, 0u},
    {87u, 1u},
    {89u, 2u},
    {91u, 3u},
    {93u, 4u},
    {95u, 5u},
    {97u, 6u},
    {99u, 7u},
    {101u, 8u},
    {103u, 9u},
    {105u, 0u},
    {107u, 1u},
    {109u, 2u},
    {111u, 3u},
    {113u, 4u},
    {115u, 5u},
    {117u, 6u},
    {119u, 7u},
    {121u, 8u},
    {123u, 9u},
    {125u, 0u},
    {127u, 1u},
    {129u, 2u},
    {131u, 3u},
    {133u, 4u},
    {135u, 5u},
    {137u, 6u},
    {139u, 7u},
    {141u, 8u},
    {143u, 9u},
    {145u, 0u},
    {147u, 1u},
    {149u, 2u},
    {151u, 3u},
    {153u, 4u},
    {155u, 5u},
    {157u, 6u},
    {159u, 7u},
    {161u, 8u},
    {163u, 9u},
    {165u, 0u},
    {167u, 1u},
    {169u, 2u},
    {171u, 3u},
    {173u, 4u},
    {175u, 5u},
    {177u, 6u},
    {179u, 7u},
    {181u, 8u},
    {183u, 9u},
    {185u, 0u},
    {187u, 1u},
    {189u, 2u},
    {191u, 3u},
    {193u, 4u},
    {195u, 5u},
    {197u, 6u},
    {199u, 7u},
    {201u, 8u},
    {203u, 9u},
    {205u, 0u},
    {207u, 1u},
    {209u, 2u},
    {211u, 3u},
    {213u, 4u},
    {215u, 5u},
    {217u, 6u},
    {219u, 7u},
    {221u, 8u},
    {223u, 9u}
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_typhoon_number_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCR_JMA_TYPHOON_NUMBER_BASE || id >= QZSS_DCR_JMA_TYPHOON_NUMBER_BASE + QZSS_DCR_JMA_TYPHOON_NUMBER_SIZE) return std::nullopt;
    const char* AZARAC_PROGMEM p = reinterpret_cast<const char*>(&QZSS_DCR_JMA_TYPHOON_NUMBER_TABLE[id - 1u]);
    uint16_t off = pgm_read_word(p + offsetof(QZSS_DCR_JMA_TYPHOON_NUMBER_Entry, offset));
    uint8_t pi = pgm_read_byte(p + offsetof(QZSS_DCR_JMA_TYPHOON_NUMBER_Entry, parent));
    if (pi == 255u) return azarac_pgm_view_z(QZSS_DCR_JMA_TYPHOON_NUMBER_POOL + off);
    const char* AZARAC_PROGMEM pp = reinterpret_cast<const char*>(&QZSS_DCR_JMA_TYPHOON_NUMBER_PARENT_TABLE[pi]);
    uint16_t poff = pgm_read_word(pp + offsetof(QZSS_DCR_JMA_TYPHOON_NUMBER_PARENT_Entry, offset));
    return azarac_pgm_join_z(QZSS_DCR_JMA_TYPHOON_NUMBER_POOL + off, QZSS_DCR_JMA_TYPHOON_NUMBER_PARENT_POOL + poff);
}
#else
inline constexpr const char* QZSS_DCR_JMA_TYPHOON_NUMBER_TABLE[] = {
    "1号",
    "2号",
    "3号",
    "4号",
    "5号",
    "6号",
    "7号",
    "8号",
    "9号",
    "10号",
    "11号",
    "12号",
    "13号",
    "14号",
    "15号",
    "16号",
    "17号",
    "18号",
    "19号",
    "20号",
    "21号",
    "22号",
    "23号",
    "24号",
    "25号",
    "26号",
    "27号",
    "28号",
    "29号",
    "30号",
    "31号",
    "32号",
    "33号",
    "34号",
    "35号",
    "36号",
    "37号",
    "38号",
    "39号",
    "40号",
    "41号",
    "42号",
    "43号",
    "44号",
    "45号",
    "46号",
    "47号",
    "48号",
    "49号",
    "50号",
    "51号",
    "52号",
    "53号",
    "54号",
    "55号",
    "56号",
    "57号",
    "58号",
    "59号",
    "60号",
    "61号",
    "62号",
    "63号",
    "64号",
    "65号",
    "66号",
    "67号",
    "68号",
    "69号",
    "70号",
    "71号",
    "72号",
    "73号",
    "74号",
    "75号",
    "76号",
    "77号",
    "78号",
    "79号",
    "80号",
    "81号",
    "82号",
    "83号",
    "84号",
    "85号",
    "86号",
    "87号",
    "88号",
    "89号",
    "90号",
    "91号",
    "92号",
    "93号",
    "94号",
    "95号",
    "96号",
    "97号",
    "98号",
    "99号"
};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_typhoon_number_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCR_JMA_TYPHOON_NUMBER_BASE || id >= QZSS_DCR_JMA_TYPHOON_NUMBER_BASE + QZSS_DCR_JMA_TYPHOON_NUMBER_SIZE) return std::nullopt;
    const char* s = QZSS_DCR_JMA_TYPHOON_NUMBER_TABLE[id - QZSS_DCR_JMA_TYPHOON_NUMBER_BASE];
    return s ? std::optional<std::string_view>(std::string_view{s}) : std::nullopt;
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_typhoon_number_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_typhoon_number_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
