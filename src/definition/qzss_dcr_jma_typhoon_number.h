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
static const char AZARAC_PROGMEM QZSS_DCR_JMA_TYPHOON_NUMBER_POOL[] = "1号\0002号\0003号\0004号\0005号\0006号\0007号\0008号\0009号\00010号\00011号\00012号\00013号\00014号\00015号\00016号\00017号\00018号\00019号\00020号\00021号\00022号\00023号\00024号\00025号\00026号\00027号\00028号\00029号\00030号\00031号\00032号\00033号\00034号\00035号\00036号\00037号\00038号\00039号\00040号\00041号\00042号\00043号\00044号\00045号\00046号\00047号\00048号\00049号\00050号\00051号\00052号\00053号\00054号\00055号\00056号\00057号\00058号\00059号\00060号\00061号\00062号\00063号\00064号\00065号\00066号\00067号\00068号\00069号\00070号\00071号\00072号\00073号\00074号\00075号\00076号\00077号\00078号\00079号\00080号\00081号\00082号\00083号\00084号\00085号\00086号\00087号\00088号\00089号\00090号\00091号\00092号\00093号\00094号\00095号\00096号\00097号\00098号\00099号\000";
struct QZSS_DCR_JMA_TYPHOON_NUMBER_Entry { uint16_t offset; uint16_t len; };
static const QZSS_DCR_JMA_TYPHOON_NUMBER_Entry QZSS_DCR_JMA_TYPHOON_NUMBER_TABLE[] AZARAC_PROGMEM = {
    {0u, 4u},
    {5u, 4u},
    {10u, 4u},
    {15u, 4u},
    {20u, 4u},
    {25u, 4u},
    {30u, 4u},
    {35u, 4u},
    {40u, 4u},
    {45u, 5u},
    {51u, 5u},
    {57u, 5u},
    {63u, 5u},
    {69u, 5u},
    {75u, 5u},
    {81u, 5u},
    {87u, 5u},
    {93u, 5u},
    {99u, 5u},
    {105u, 5u},
    {111u, 5u},
    {117u, 5u},
    {123u, 5u},
    {129u, 5u},
    {135u, 5u},
    {141u, 5u},
    {147u, 5u},
    {153u, 5u},
    {159u, 5u},
    {165u, 5u},
    {171u, 5u},
    {177u, 5u},
    {183u, 5u},
    {189u, 5u},
    {195u, 5u},
    {201u, 5u},
    {207u, 5u},
    {213u, 5u},
    {219u, 5u},
    {225u, 5u},
    {231u, 5u},
    {237u, 5u},
    {243u, 5u},
    {249u, 5u},
    {255u, 5u},
    {261u, 5u},
    {267u, 5u},
    {273u, 5u},
    {279u, 5u},
    {285u, 5u},
    {291u, 5u},
    {297u, 5u},
    {303u, 5u},
    {309u, 5u},
    {315u, 5u},
    {321u, 5u},
    {327u, 5u},
    {333u, 5u},
    {339u, 5u},
    {345u, 5u},
    {351u, 5u},
    {357u, 5u},
    {363u, 5u},
    {369u, 5u},
    {375u, 5u},
    {381u, 5u},
    {387u, 5u},
    {393u, 5u},
    {399u, 5u},
    {405u, 5u},
    {411u, 5u},
    {417u, 5u},
    {423u, 5u},
    {429u, 5u},
    {435u, 5u},
    {441u, 5u},
    {447u, 5u},
    {453u, 5u},
    {459u, 5u},
    {465u, 5u},
    {471u, 5u},
    {477u, 5u},
    {483u, 5u},
    {489u, 5u},
    {495u, 5u},
    {501u, 5u},
    {507u, 5u},
    {513u, 5u},
    {519u, 5u},
    {525u, 5u},
    {531u, 5u},
    {537u, 5u},
    {543u, 5u},
    {549u, 5u},
    {555u, 5u},
    {561u, 5u},
    {567u, 5u},
    {573u, 5u},
    {579u, 5u}
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_typhoon_number_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCR_JMA_TYPHOON_NUMBER_BASE || id >= QZSS_DCR_JMA_TYPHOON_NUMBER_BASE + QZSS_DCR_JMA_TYPHOON_NUMBER_SIZE) return std::nullopt;
    const char* AZARAC_PROGMEM p = reinterpret_cast<const char*>(&QZSS_DCR_JMA_TYPHOON_NUMBER_TABLE[id - 1u]);
    uint16_t off = pgm_read_word(p + offsetof(QZSS_DCR_JMA_TYPHOON_NUMBER_Entry, offset));
    uint16_t n = pgm_read_word(p + offsetof(QZSS_DCR_JMA_TYPHOON_NUMBER_Entry, len));
    return azarac_pgm_view(QZSS_DCR_JMA_TYPHOON_NUMBER_POOL + off, n);
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
