#pragma once
// AUTO-GENERATED from azarashi 0.17.0 with CI-CD
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
static const char AZARAC_PROGMEM QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_EN_POOL[] = "0 hours ahead\0001 hour ahead\0002 hours ahead\0003 hours ahead\0004 hours ahead\0005 hours ahead\0006 hours ahead\0007 hours ahead\0008 hours ahead\0009 hours ahead\00010 hours ahead\00011 hours ahead\00012 hours ahead\00013 hours ahead\00014 hours ahead\00015 hours ahead\00016 hours ahead\00017 hours ahead\00018 hours ahead\00019 hours ahead\00020 hours ahead\00021 hours ahead\00022 hours ahead\00023 hours ahead\00024 hours ahead\00025 hours ahead\00026 hours ahead\00027 hours ahead\00028 hours ahead\00029 hours ahead\00030 hours ahead\00031 hours ahead\00032 hours ahead\00033 hours ahead\00034 hours ahead\00035 hours ahead\00036 hours ahead\00037 hours ahead\00038 hours ahead\00039 hours ahead\00040 hours ahead\00041 hours ahead\00042 hours ahead\00043 hours ahead\00044 hours ahead\00045 hours ahead\00046 hours ahead\00047 hours ahead\00048 hours ahead\00049 hours ahead\00050 hours ahead\00051 hours ahead\00052 hours ahead\00053 hours ahead\00054 hours ahead\00055 hours ahead\00056 hours ahead\00057 hours ahead\00058 hours ahead\00059 hours ahead\00060 hours ahead\00061 hours ahead\00062 hours ahead\00063 hours ahead\00064 hours ahead\00065 hours ahead\00066 hours ahead\00067 hours ahead\00068 hours ahead\00069 hours ahead\00070 hours ahead\00071 hours ahead\00072 hours ahead\00073 hours ahead\00074 hours ahead\00075 hours ahead\00076 hours ahead\00077 hours ahead\00078 hours ahead\00079 hours ahead\00080 hours ahead\00081 hours ahead\00082 hours ahead\00083 hours ahead\00084 hours ahead\00085 hours ahead\00086 hours ahead\00087 hours ahead\00088 hours ahead\00089 hours ahead\00090 hours ahead\00091 hours ahead\00092 hours ahead\00093 hours ahead\00094 hours ahead\00095 hours ahead\00096 hours ahead\00097 hours ahead\00098 hours ahead\00099 hours ahead\000100 hours ahead\000101 hours ahead\000102 hours ahead\000103 hours ahead\000104 hours ahead\000105 hours ahead\000106 hours ahead\000107 hours ahead\000108 hours ahead\000109 hours ahead\000110 hours ahead\000111 hours ahead\000112 hours ahead\000113 hours ahead\000114 hours ahead\000115 hours ahead\000116 hours ahead\000117 hours ahead\000118 hours ahead\000119 hours ahead\000120 hours ahead\000121 hours ahead\000122 hours ahead\000123 hours ahead\000124 hours ahead\000125 hours ahead\000126 hours ahead\000127 hours ahead\000";
struct QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_EN_Entry { uint16_t offset; uint16_t len; };
static const QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_EN_Entry QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_EN_TABLE[] AZARAC_PROGMEM = {
    {0u, 13u},
    {14u, 12u},
    {27u, 13u},
    {41u, 13u},
    {55u, 13u},
    {69u, 13u},
    {83u, 13u},
    {97u, 13u},
    {111u, 13u},
    {125u, 13u},
    {139u, 14u},
    {154u, 14u},
    {169u, 14u},
    {184u, 14u},
    {199u, 14u},
    {214u, 14u},
    {229u, 14u},
    {244u, 14u},
    {259u, 14u},
    {274u, 14u},
    {289u, 14u},
    {304u, 14u},
    {319u, 14u},
    {334u, 14u},
    {349u, 14u},
    {364u, 14u},
    {379u, 14u},
    {394u, 14u},
    {409u, 14u},
    {424u, 14u},
    {439u, 14u},
    {454u, 14u},
    {469u, 14u},
    {484u, 14u},
    {499u, 14u},
    {514u, 14u},
    {529u, 14u},
    {544u, 14u},
    {559u, 14u},
    {574u, 14u},
    {589u, 14u},
    {604u, 14u},
    {619u, 14u},
    {634u, 14u},
    {649u, 14u},
    {664u, 14u},
    {679u, 14u},
    {694u, 14u},
    {709u, 14u},
    {724u, 14u},
    {739u, 14u},
    {754u, 14u},
    {769u, 14u},
    {784u, 14u},
    {799u, 14u},
    {814u, 14u},
    {829u, 14u},
    {844u, 14u},
    {859u, 14u},
    {874u, 14u},
    {889u, 14u},
    {904u, 14u},
    {919u, 14u},
    {934u, 14u},
    {949u, 14u},
    {964u, 14u},
    {979u, 14u},
    {994u, 14u},
    {1009u, 14u},
    {1024u, 14u},
    {1039u, 14u},
    {1054u, 14u},
    {1069u, 14u},
    {1084u, 14u},
    {1099u, 14u},
    {1114u, 14u},
    {1129u, 14u},
    {1144u, 14u},
    {1159u, 14u},
    {1174u, 14u},
    {1189u, 14u},
    {1204u, 14u},
    {1219u, 14u},
    {1234u, 14u},
    {1249u, 14u},
    {1264u, 14u},
    {1279u, 14u},
    {1294u, 14u},
    {1309u, 14u},
    {1324u, 14u},
    {1339u, 14u},
    {1354u, 14u},
    {1369u, 14u},
    {1384u, 14u},
    {1399u, 14u},
    {1414u, 14u},
    {1429u, 14u},
    {1444u, 14u},
    {1459u, 14u},
    {1474u, 14u},
    {1489u, 15u},
    {1505u, 15u},
    {1521u, 15u},
    {1537u, 15u},
    {1553u, 15u},
    {1569u, 15u},
    {1585u, 15u},
    {1601u, 15u},
    {1617u, 15u},
    {1633u, 15u},
    {1649u, 15u},
    {1665u, 15u},
    {1681u, 15u},
    {1697u, 15u},
    {1713u, 15u},
    {1729u, 15u},
    {1745u, 15u},
    {1761u, 15u},
    {1777u, 15u},
    {1793u, 15u},
    {1809u, 15u},
    {1825u, 15u},
    {1841u, 15u},
    {1857u, 15u},
    {1873u, 15u},
    {1889u, 15u},
    {1905u, 15u},
    {1921u, 15u}
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_typhoon_elapsed_time_from_reference_time_en_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_EN_BASE || id >= QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_EN_BASE + QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_EN_SIZE) return std::nullopt;
    const char* AZARAC_PROGMEM p = reinterpret_cast<const char*>(&QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_EN_TABLE[id - 0u]);
    uint16_t off = pgm_read_word(p + offsetof(QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_EN_Entry, offset));
    uint16_t n = pgm_read_word(p + offsetof(QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_EN_Entry, len));
    return azarac_pgm_view(QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_EN_POOL + off, n);
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
