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
static const char AZARAC_PROGMEM QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_EN_POOL[] = "0 ho\0001 hour\0002 ho\0003 ho\0004 ho\0005 ho\0006 ho\0007 ho\0008 ho\0009 ho\00010 h\00011 h\00012 h\00013 h\00014 h\00015 h\00016 h\00017 h\00018 h\00019 h\00020 h\00021 h\00022 h\00023 h\00024 h\00025 h\00026 h\00027 h\00028 h\00029 h\00030 h\00031 h\00032 h\00033 h\00034 h\00035 h\00036 h\00037 h\00038 h\00039 h\00040 h\00041 h\00042 h\00043 h\00044 h\00045 h\00046 h\00047 h\00048 h\00049 h\00050 h\00051 h\00052 h\00053 h\00054 h\00055 h\00056 h\00057 h\00058 h\00059 h\00060 h\00061 h\00062 h\00063 h\00064 h\00065 h\00066 h\00067 h\00068 h\00069 h\00070 h\00071 h\00072 h\00073 h\00074 h\00075 h\00076 h\00077 h\00078 h\00079 h\00080 h\00081 h\00082 h\00083 h\00084 h\00085 h\00086 h\00087 h\00088 h\00089 h\00090 h\00091 h\00092 h\00093 h\00094 h\00095 h\00096 h\00097 h\00098 h\00099 h\000100 \000101 \000102 \000103 \000104 \000105 \000106 \000107 \000108 \000109 \000110 \000111 \000112 \000113 \000114 \000115 \000116 \000117 \000118 \000119 \000120 \000121 \000122 \000123 \000124 \000125 \000126 \000127 \000";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_EN_PARENT_POOL[] = " ahead\000hours ahead\000ours ahead\000urs ahead\000";
struct QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_EN_PARENT_Entry { uint16_t offset; uint8_t len; };
static const QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_EN_PARENT_Entry QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_EN_PARENT_TABLE[] AZARAC_PROGMEM = {
    {0u, 6u},
    {7u, 11u},
    {19u, 10u},
    {30u, 9u},
};
struct QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_EN_Entry { uint16_t offset; uint8_t len; uint8_t parent; };
static const QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_EN_Entry QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_EN_TABLE[] AZARAC_PROGMEM = {
    {0u, 4u, 3u},
    {5u, 6u, 0u},
    {12u, 4u, 3u},
    {17u, 4u, 3u},
    {22u, 4u, 3u},
    {27u, 4u, 3u},
    {32u, 4u, 3u},
    {37u, 4u, 3u},
    {42u, 4u, 3u},
    {47u, 4u, 3u},
    {52u, 4u, 2u},
    {57u, 4u, 2u},
    {62u, 4u, 2u},
    {67u, 4u, 2u},
    {72u, 4u, 2u},
    {77u, 4u, 2u},
    {82u, 4u, 2u},
    {87u, 4u, 2u},
    {92u, 4u, 2u},
    {97u, 4u, 2u},
    {102u, 4u, 2u},
    {107u, 4u, 2u},
    {112u, 4u, 2u},
    {117u, 4u, 2u},
    {122u, 4u, 2u},
    {127u, 4u, 2u},
    {132u, 4u, 2u},
    {137u, 4u, 2u},
    {142u, 4u, 2u},
    {147u, 4u, 2u},
    {152u, 4u, 2u},
    {157u, 4u, 2u},
    {162u, 4u, 2u},
    {167u, 4u, 2u},
    {172u, 4u, 2u},
    {177u, 4u, 2u},
    {182u, 4u, 2u},
    {187u, 4u, 2u},
    {192u, 4u, 2u},
    {197u, 4u, 2u},
    {202u, 4u, 2u},
    {207u, 4u, 2u},
    {212u, 4u, 2u},
    {217u, 4u, 2u},
    {222u, 4u, 2u},
    {227u, 4u, 2u},
    {232u, 4u, 2u},
    {237u, 4u, 2u},
    {242u, 4u, 2u},
    {247u, 4u, 2u},
    {252u, 4u, 2u},
    {257u, 4u, 2u},
    {262u, 4u, 2u},
    {267u, 4u, 2u},
    {272u, 4u, 2u},
    {277u, 4u, 2u},
    {282u, 4u, 2u},
    {287u, 4u, 2u},
    {292u, 4u, 2u},
    {297u, 4u, 2u},
    {302u, 4u, 2u},
    {307u, 4u, 2u},
    {312u, 4u, 2u},
    {317u, 4u, 2u},
    {322u, 4u, 2u},
    {327u, 4u, 2u},
    {332u, 4u, 2u},
    {337u, 4u, 2u},
    {342u, 4u, 2u},
    {347u, 4u, 2u},
    {352u, 4u, 2u},
    {357u, 4u, 2u},
    {362u, 4u, 2u},
    {367u, 4u, 2u},
    {372u, 4u, 2u},
    {377u, 4u, 2u},
    {382u, 4u, 2u},
    {387u, 4u, 2u},
    {392u, 4u, 2u},
    {397u, 4u, 2u},
    {402u, 4u, 2u},
    {407u, 4u, 2u},
    {412u, 4u, 2u},
    {417u, 4u, 2u},
    {422u, 4u, 2u},
    {427u, 4u, 2u},
    {432u, 4u, 2u},
    {437u, 4u, 2u},
    {442u, 4u, 2u},
    {447u, 4u, 2u},
    {452u, 4u, 2u},
    {457u, 4u, 2u},
    {462u, 4u, 2u},
    {467u, 4u, 2u},
    {472u, 4u, 2u},
    {477u, 4u, 2u},
    {482u, 4u, 2u},
    {487u, 4u, 2u},
    {492u, 4u, 2u},
    {497u, 4u, 2u},
    {502u, 4u, 1u},
    {507u, 4u, 1u},
    {512u, 4u, 1u},
    {517u, 4u, 1u},
    {522u, 4u, 1u},
    {527u, 4u, 1u},
    {532u, 4u, 1u},
    {537u, 4u, 1u},
    {542u, 4u, 1u},
    {547u, 4u, 1u},
    {552u, 4u, 1u},
    {557u, 4u, 1u},
    {562u, 4u, 1u},
    {567u, 4u, 1u},
    {572u, 4u, 1u},
    {577u, 4u, 1u},
    {582u, 4u, 1u},
    {587u, 4u, 1u},
    {592u, 4u, 1u},
    {597u, 4u, 1u},
    {602u, 4u, 1u},
    {607u, 4u, 1u},
    {612u, 4u, 1u},
    {617u, 4u, 1u},
    {622u, 4u, 1u},
    {627u, 4u, 1u},
    {632u, 4u, 1u},
    {637u, 4u, 1u}
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_typhoon_elapsed_time_from_reference_time_en_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_EN_BASE || id >= QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_EN_BASE + QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_EN_SIZE) return std::nullopt;
    const char* AZARAC_PROGMEM p = reinterpret_cast<const char*>(&QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_EN_TABLE[id - 0u]);
    uint16_t off = pgm_read_word(p + offsetof(QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_EN_Entry, offset));
    uint8_t n = pgm_read_byte(p + offsetof(QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_EN_Entry, len));
    uint8_t pi = pgm_read_byte(p + offsetof(QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_EN_Entry, parent));
    if (pi == 255u) return azarac_pgm_view(QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_EN_POOL + off, n);
    const char* AZARAC_PROGMEM pp = reinterpret_cast<const char*>(&QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_EN_PARENT_TABLE[pi]);
    uint16_t poff = pgm_read_word(pp + offsetof(QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_EN_PARENT_Entry, offset));
    uint8_t pn = pgm_read_byte(pp + offsetof(QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_EN_PARENT_Entry, len));
    return azarac_pgm_join(QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_EN_POOL + off, n, QZSS_DCR_JMA_TYPHOON_ELAPSED_TIME_FROM_REFERENCE_TIME_EN_PARENT_POOL + poff, pn);
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
