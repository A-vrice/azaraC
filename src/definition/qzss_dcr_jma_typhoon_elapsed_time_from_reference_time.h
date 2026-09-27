#pragma once
// AUTO-GENERATED from azarashi 0.17.0 with CI-CD
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
static const char AZARAC_PROGMEM QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_POOL[] = "0時間後\0001時間後\0002時間後\0003時間後\0004時間後\0005時間後\0006時間後\0007時間後\0008時間後\0009時間後\00010時間後\00011時間後\00012時間後\00013時間後\00014時間後\00015時間後\00016時間後\00017時間後\00018時間後\00019時間後\00020時間後\00021時間後\00022時間後\00023時間後\00024時間後\00025時間後\00026時間後\00027時間後\00028時間後\00029時間後\00030時間後\00031時間後\00032時間後\00033時間後\00034時間後\00035時間後\00036時間後\00037時間後\00038時間後\00039時間後\00040時間後\00041時間後\00042時間後\00043時間後\00044時間後\00045時間後\00046時間後\00047時間後\00048時間後\00049時間後\00050時間後\00051時間後\00052時間後\00053時間後\00054時間後\00055時間後\00056時間後\00057時間後\00058時間後\00059時間後\00060時間後\00061時間後\00062時間後\00063時間後\00064時間後\00065時間後\00066時間後\00067時間後\00068時間後\00069時間後\00070時間後\00071時間後\00072時間後\00073時間後\00074時間後\00075時間後\00076時間後\00077時間後\00078時間後\00079時間後\00080時間後\00081時間後\00082時間後\00083時間後\00084時間後\00085時間後\00086時間後\00087時間後\00088時間後\00089時間後\00090時間後\00091時間後\00092時間後\00093時間後\00094時間後\00095時間後\00096時間後\00097時間後\00098時間後\00099時間後\000100時間後\000101時間後\000102時間後\000103時間後\000104時間後\000105時間後\000106時間後\000107時間後\000108時間後\000109時間後\000110時間後\000111時間後\000112時間後\000113時間後\000114時間後\000115時間後\000116時間後\000117時間後\000118時間後\000119時間後\000120時間後\000121時間後\000122時間後\000123時間後\000124時間後\000125時間後\000126時間後\000127時間後\000";
struct QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_Entry { uint16_t offset; uint16_t len; };
static const QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_Entry QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_TABLE[] AZARAC_PROGMEM = {
    {0u, 10u},
    {11u, 10u},
    {22u, 10u},
    {33u, 10u},
    {44u, 10u},
    {55u, 10u},
    {66u, 10u},
    {77u, 10u},
    {88u, 10u},
    {99u, 10u},
    {110u, 11u},
    {122u, 11u},
    {134u, 11u},
    {146u, 11u},
    {158u, 11u},
    {170u, 11u},
    {182u, 11u},
    {194u, 11u},
    {206u, 11u},
    {218u, 11u},
    {230u, 11u},
    {242u, 11u},
    {254u, 11u},
    {266u, 11u},
    {278u, 11u},
    {290u, 11u},
    {302u, 11u},
    {314u, 11u},
    {326u, 11u},
    {338u, 11u},
    {350u, 11u},
    {362u, 11u},
    {374u, 11u},
    {386u, 11u},
    {398u, 11u},
    {410u, 11u},
    {422u, 11u},
    {434u, 11u},
    {446u, 11u},
    {458u, 11u},
    {470u, 11u},
    {482u, 11u},
    {494u, 11u},
    {506u, 11u},
    {518u, 11u},
    {530u, 11u},
    {542u, 11u},
    {554u, 11u},
    {566u, 11u},
    {578u, 11u},
    {590u, 11u},
    {602u, 11u},
    {614u, 11u},
    {626u, 11u},
    {638u, 11u},
    {650u, 11u},
    {662u, 11u},
    {674u, 11u},
    {686u, 11u},
    {698u, 11u},
    {710u, 11u},
    {722u, 11u},
    {734u, 11u},
    {746u, 11u},
    {758u, 11u},
    {770u, 11u},
    {782u, 11u},
    {794u, 11u},
    {806u, 11u},
    {818u, 11u},
    {830u, 11u},
    {842u, 11u},
    {854u, 11u},
    {866u, 11u},
    {878u, 11u},
    {890u, 11u},
    {902u, 11u},
    {914u, 11u},
    {926u, 11u},
    {938u, 11u},
    {950u, 11u},
    {962u, 11u},
    {974u, 11u},
    {986u, 11u},
    {998u, 11u},
    {1010u, 11u},
    {1022u, 11u},
    {1034u, 11u},
    {1046u, 11u},
    {1058u, 11u},
    {1070u, 11u},
    {1082u, 11u},
    {1094u, 11u},
    {1106u, 11u},
    {1118u, 11u},
    {1130u, 11u},
    {1142u, 11u},
    {1154u, 11u},
    {1166u, 11u},
    {1178u, 11u},
    {1190u, 12u},
    {1203u, 12u},
    {1216u, 12u},
    {1229u, 12u},
    {1242u, 12u},
    {1255u, 12u},
    {1268u, 12u},
    {1281u, 12u},
    {1294u, 12u},
    {1307u, 12u},
    {1320u, 12u},
    {1333u, 12u},
    {1346u, 12u},
    {1359u, 12u},
    {1372u, 12u},
    {1385u, 12u},
    {1398u, 12u},
    {1411u, 12u},
    {1424u, 12u},
    {1437u, 12u},
    {1450u, 12u},
    {1463u, 12u},
    {1476u, 12u},
    {1489u, 12u},
    {1502u, 12u},
    {1515u, 12u},
    {1528u, 12u},
    {1541u, 12u}
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_typhoon_elapsed_time_from_reference_time_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_BASE || id >= QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_BASE + QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_SIZE) return std::nullopt;
    const char* AZARAC_PROGMEM p = reinterpret_cast<const char*>(&QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_TABLE[id - 0u]);
    uint16_t off = pgm_read_word(p + offsetof(QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_Entry, offset));
    uint16_t n = pgm_read_word(p + offsetof(QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_Entry, len));
    return azarac_pgm_view(QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_POOL + off, n);
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
