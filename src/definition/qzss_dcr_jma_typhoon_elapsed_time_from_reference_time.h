#pragma once
// AUTO-GENERATED from azarashi 0.17.1 with CI-CD
// Source module : azarashi.definitions.qzss.dcr.typhoon_elapsed_time_from_reference_time
// Variable      : qzss_dcr_jma_typhoon_elapsed_time_from_reference_time
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

#if (AZARAC_ENABLE_TYPHOON) && (AZARAC_LANG_JA)

inline constexpr uint8_t QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_BASE = 0;
inline constexpr uint8_t QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_SIZE = 128;
#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_POOL[] = "0時\0001時\0002時\0003時\0004時\0005時\0006時\0007時\0008時\0009時\00010時\00011時\00012時\00013時\00014時\00015時\00016時\00017時\00018時\00019時\00020時\00021時\00022時\00023時\00024時\00025時\00026時\00027時\00028時\00029時\00030時\00031時\00032時\00033時\00034時\00035時\00036時\00037時\00038時\00039時\00040時\00041時\00042時\00043時\00044時\00045時\00046時\00047時\00048時\00049時\00050時\00051時\00052時\00053時\00054時\00055時\00056時\00057時\00058時\00059時\00060時\00061時\00062時\00063時\00064時\00065時\00066時\00067時\00068時\00069時\00070時\00071時\00072時\00073時\00074時\00075時\00076時\00077時\00078時\00079時\00080時\00081時\00082時\00083時\00084時\00085時\00086時\00087時\00088時\00089時\00090時\00091時\00092時\00093時\00094時\00095時\00096時\00097時\00098時\00099時\000100時\000101時\000102時\000103時\000104時\000105時\000106時\000107時\000108時\000109時\000110時\000111時\000112時\000113時\000114時\000115時\000116時\000117時\000118時\000119時\000120時\000121時\000122時\000123時\000124時\000125時\000126時\000127時\000";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_PARENT_POOL[] = "間後\000";
struct QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_PARENT_Entry { uint16_t offset; uint8_t len; };
static const QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_PARENT_Entry QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_PARENT_TABLE[] AZARAC_PROGMEM = {
    {0u, 6u},
};
struct QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_Entry { uint16_t offset; uint8_t len; uint8_t parent; };
static const QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_Entry QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_TABLE[] AZARAC_PROGMEM = {
    {0u, 4u, 0u},
    {5u, 4u, 0u},
    {10u, 4u, 0u},
    {15u, 4u, 0u},
    {20u, 4u, 0u},
    {25u, 4u, 0u},
    {30u, 4u, 0u},
    {35u, 4u, 0u},
    {40u, 4u, 0u},
    {45u, 4u, 0u},
    {50u, 5u, 0u},
    {56u, 5u, 0u},
    {62u, 5u, 0u},
    {68u, 5u, 0u},
    {74u, 5u, 0u},
    {80u, 5u, 0u},
    {86u, 5u, 0u},
    {92u, 5u, 0u},
    {98u, 5u, 0u},
    {104u, 5u, 0u},
    {110u, 5u, 0u},
    {116u, 5u, 0u},
    {122u, 5u, 0u},
    {128u, 5u, 0u},
    {134u, 5u, 0u},
    {140u, 5u, 0u},
    {146u, 5u, 0u},
    {152u, 5u, 0u},
    {158u, 5u, 0u},
    {164u, 5u, 0u},
    {170u, 5u, 0u},
    {176u, 5u, 0u},
    {182u, 5u, 0u},
    {188u, 5u, 0u},
    {194u, 5u, 0u},
    {200u, 5u, 0u},
    {206u, 5u, 0u},
    {212u, 5u, 0u},
    {218u, 5u, 0u},
    {224u, 5u, 0u},
    {230u, 5u, 0u},
    {236u, 5u, 0u},
    {242u, 5u, 0u},
    {248u, 5u, 0u},
    {254u, 5u, 0u},
    {260u, 5u, 0u},
    {266u, 5u, 0u},
    {272u, 5u, 0u},
    {278u, 5u, 0u},
    {284u, 5u, 0u},
    {290u, 5u, 0u},
    {296u, 5u, 0u},
    {302u, 5u, 0u},
    {308u, 5u, 0u},
    {314u, 5u, 0u},
    {320u, 5u, 0u},
    {326u, 5u, 0u},
    {332u, 5u, 0u},
    {338u, 5u, 0u},
    {344u, 5u, 0u},
    {350u, 5u, 0u},
    {356u, 5u, 0u},
    {362u, 5u, 0u},
    {368u, 5u, 0u},
    {374u, 5u, 0u},
    {380u, 5u, 0u},
    {386u, 5u, 0u},
    {392u, 5u, 0u},
    {398u, 5u, 0u},
    {404u, 5u, 0u},
    {410u, 5u, 0u},
    {416u, 5u, 0u},
    {422u, 5u, 0u},
    {428u, 5u, 0u},
    {434u, 5u, 0u},
    {440u, 5u, 0u},
    {446u, 5u, 0u},
    {452u, 5u, 0u},
    {458u, 5u, 0u},
    {464u, 5u, 0u},
    {470u, 5u, 0u},
    {476u, 5u, 0u},
    {482u, 5u, 0u},
    {488u, 5u, 0u},
    {494u, 5u, 0u},
    {500u, 5u, 0u},
    {506u, 5u, 0u},
    {512u, 5u, 0u},
    {518u, 5u, 0u},
    {524u, 5u, 0u},
    {530u, 5u, 0u},
    {536u, 5u, 0u},
    {542u, 5u, 0u},
    {548u, 5u, 0u},
    {554u, 5u, 0u},
    {560u, 5u, 0u},
    {566u, 5u, 0u},
    {572u, 5u, 0u},
    {578u, 5u, 0u},
    {584u, 5u, 0u},
    {590u, 6u, 0u},
    {597u, 6u, 0u},
    {604u, 6u, 0u},
    {611u, 6u, 0u},
    {618u, 6u, 0u},
    {625u, 6u, 0u},
    {632u, 6u, 0u},
    {639u, 6u, 0u},
    {646u, 6u, 0u},
    {653u, 6u, 0u},
    {660u, 6u, 0u},
    {667u, 6u, 0u},
    {674u, 6u, 0u},
    {681u, 6u, 0u},
    {688u, 6u, 0u},
    {695u, 6u, 0u},
    {702u, 6u, 0u},
    {709u, 6u, 0u},
    {716u, 6u, 0u},
    {723u, 6u, 0u},
    {730u, 6u, 0u},
    {737u, 6u, 0u},
    {744u, 6u, 0u},
    {751u, 6u, 0u},
    {758u, 6u, 0u},
    {765u, 6u, 0u},
    {772u, 6u, 0u},
    {779u, 6u, 0u}
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_typhoon_elapsed_time_from_reference_time_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_BASE || id >= QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_BASE + QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_SIZE) return std::nullopt;
    const char* AZARAC_PROGMEM p = reinterpret_cast<const char*>(&QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_TABLE[id - 0u]);
    uint16_t off = pgm_read_word(p + offsetof(QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_Entry, offset));
    uint8_t n = pgm_read_byte(p + offsetof(QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_Entry, len));
    uint8_t pi = pgm_read_byte(p + offsetof(QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_Entry, parent));
    if (pi == 255u) return azarac_pgm_view(QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_POOL + off, n);
    const char* AZARAC_PROGMEM pp = reinterpret_cast<const char*>(&QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_PARENT_TABLE[pi]);
    uint16_t poff = pgm_read_word(pp + offsetof(QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_PARENT_Entry, offset));
    uint8_t pn = pgm_read_byte(pp + offsetof(QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_PARENT_Entry, len));
    return azarac_pgm_join(QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_POOL + off, n, QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_PARENT_POOL + poff, pn);
}
#else
inline constexpr const char* QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_TABLE[] = {
    "0時間後",
    "1時間後",
    "2時間後",
    "3時間後",
    "4時間後",
    "5時間後",
    "6時間後",
    "7時間後",
    "8時間後",
    "9時間後",
    "10時間後",
    "11時間後",
    "12時間後",
    "13時間後",
    "14時間後",
    "15時間後",
    "16時間後",
    "17時間後",
    "18時間後",
    "19時間後",
    "20時間後",
    "21時間後",
    "22時間後",
    "23時間後",
    "24時間後",
    "25時間後",
    "26時間後",
    "27時間後",
    "28時間後",
    "29時間後",
    "30時間後",
    "31時間後",
    "32時間後",
    "33時間後",
    "34時間後",
    "35時間後",
    "36時間後",
    "37時間後",
    "38時間後",
    "39時間後",
    "40時間後",
    "41時間後",
    "42時間後",
    "43時間後",
    "44時間後",
    "45時間後",
    "46時間後",
    "47時間後",
    "48時間後",
    "49時間後",
    "50時間後",
    "51時間後",
    "52時間後",
    "53時間後",
    "54時間後",
    "55時間後",
    "56時間後",
    "57時間後",
    "58時間後",
    "59時間後",
    "60時間後",
    "61時間後",
    "62時間後",
    "63時間後",
    "64時間後",
    "65時間後",
    "66時間後",
    "67時間後",
    "68時間後",
    "69時間後",
    "70時間後",
    "71時間後",
    "72時間後",
    "73時間後",
    "74時間後",
    "75時間後",
    "76時間後",
    "77時間後",
    "78時間後",
    "79時間後",
    "80時間後",
    "81時間後",
    "82時間後",
    "83時間後",
    "84時間後",
    "85時間後",
    "86時間後",
    "87時間後",
    "88時間後",
    "89時間後",
    "90時間後",
    "91時間後",
    "92時間後",
    "93時間後",
    "94時間後",
    "95時間後",
    "96時間後",
    "97時間後",
    "98時間後",
    "99時間後",
    "100時間後",
    "101時間後",
    "102時間後",
    "103時間後",
    "104時間後",
    "105時間後",
    "106時間後",
    "107時間後",
    "108時間後",
    "109時間後",
    "110時間後",
    "111時間後",
    "112時間後",
    "113時間後",
    "114時間後",
    "115時間後",
    "116時間後",
    "117時間後",
    "118時間後",
    "119時間後",
    "120時間後",
    "121時間後",
    "122時間後",
    "123時間後",
    "124時間後",
    "125時間後",
    "126時間後",
    "127時間後"
};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_typhoon_elapsed_time_from_reference_time_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_BASE || id >= QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_BASE + QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_SIZE) return std::nullopt;
    const char* s = QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_TABLE[id - QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_BASE];
    return s ? std::optional<std::string_view>(std::string_view{s}) : std::nullopt;
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_typhoon_elapsed_time_from_reference_time_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_typhoon_elapsed_time_from_reference_time_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
