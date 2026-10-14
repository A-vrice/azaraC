#pragma once
// AUTO-GENERATED from azarashi 0.17.1 with CI-CD
// Source module : azarashi.definitions.qzss.dcr.prefecture
// Variable      : qzss_dcr_jma_prefecture
// Entries       : 47
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

#if (AZARAC_ENABLE_SEISMIC || AZARAC_ENABLE_DCX_CAMF) && (AZARAC_LANG_JA)

inline constexpr uint8_t QZSS_DCR_JMA_PREFECTURE_BASE = 1;
inline constexpr uint8_t QZSS_DCR_JMA_PREFECTURE_SIZE = 47;
#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCR_JMA_PREFECTURE_POOL[] = "北海道\000青森県\000岩手県\000宮城県\000秋田県\000山形県\000福\000茨城県\000栃木県\000群馬県\000埼玉県\000千葉県\000東京都\000神奈川県\000新潟県\000富山県\000石川県\000福井県\000山梨県\000長野県\000岐阜県\000静岡県\000愛知県\000三重県\000滋賀県\000京都府\000大阪府\000兵庫県\000奈良県\000和歌山県\000鳥取県\000島根県\000岡山県\000広\000山口県\000徳\000香川県\000愛媛県\000高知県\000福岡県\000佐賀県\000長崎県\000熊本県\000大分県\000宮崎県\000鹿児\000沖縄県\000";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_PREFECTURE_PARENT_POOL[] = "島県\000";
struct QZSS_DCR_JMA_PREFECTURE_PARENT_Entry { uint16_t offset; };
static const QZSS_DCR_JMA_PREFECTURE_PARENT_Entry QZSS_DCR_JMA_PREFECTURE_PARENT_TABLE[] AZARAC_PROGMEM = {
    {0u},
};
struct QZSS_DCR_JMA_PREFECTURE_Entry { uint16_t offset; uint8_t parent; };
static const QZSS_DCR_JMA_PREFECTURE_Entry QZSS_DCR_JMA_PREFECTURE_TABLE[] AZARAC_PROGMEM = {
    {0u, 255u},
    {10u, 255u},
    {20u, 255u},
    {30u, 255u},
    {40u, 255u},
    {50u, 255u},
    {60u, 0u},
    {64u, 255u},
    {74u, 255u},
    {84u, 255u},
    {94u, 255u},
    {104u, 255u},
    {114u, 255u},
    {124u, 255u},
    {137u, 255u},
    {147u, 255u},
    {157u, 255u},
    {167u, 255u},
    {177u, 255u},
    {187u, 255u},
    {197u, 255u},
    {207u, 255u},
    {217u, 255u},
    {227u, 255u},
    {237u, 255u},
    {247u, 255u},
    {257u, 255u},
    {267u, 255u},
    {277u, 255u},
    {287u, 255u},
    {300u, 255u},
    {310u, 255u},
    {320u, 255u},
    {330u, 0u},
    {334u, 255u},
    {344u, 0u},
    {348u, 255u},
    {358u, 255u},
    {368u, 255u},
    {378u, 255u},
    {388u, 255u},
    {398u, 255u},
    {408u, 255u},
    {418u, 255u},
    {428u, 255u},
    {438u, 0u},
    {445u, 255u}
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_prefecture_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCR_JMA_PREFECTURE_BASE || id >= QZSS_DCR_JMA_PREFECTURE_BASE + QZSS_DCR_JMA_PREFECTURE_SIZE) return std::nullopt;
    const char* AZARAC_PROGMEM p = reinterpret_cast<const char*>(&QZSS_DCR_JMA_PREFECTURE_TABLE[id - 1u]);
    uint16_t off = pgm_read_word(p + offsetof(QZSS_DCR_JMA_PREFECTURE_Entry, offset));
    uint8_t pi = pgm_read_byte(p + offsetof(QZSS_DCR_JMA_PREFECTURE_Entry, parent));
    if (pi == 255u) return azarac_pgm_view_z(QZSS_DCR_JMA_PREFECTURE_POOL + off);
    const char* AZARAC_PROGMEM pp = reinterpret_cast<const char*>(&QZSS_DCR_JMA_PREFECTURE_PARENT_TABLE[pi]);
    uint16_t poff = pgm_read_word(pp + offsetof(QZSS_DCR_JMA_PREFECTURE_PARENT_Entry, offset));
    return azarac_pgm_join_z(QZSS_DCR_JMA_PREFECTURE_POOL + off, QZSS_DCR_JMA_PREFECTURE_PARENT_POOL + poff);
}
#else
inline constexpr const char* QZSS_DCR_JMA_PREFECTURE_TABLE[] = {
    "北海道",
    "青森県",
    "岩手県",
    "宮城県",
    "秋田県",
    "山形県",
    "福島県",
    "茨城県",
    "栃木県",
    "群馬県",
    "埼玉県",
    "千葉県",
    "東京都",
    "神奈川県",
    "新潟県",
    "富山県",
    "石川県",
    "福井県",
    "山梨県",
    "長野県",
    "岐阜県",
    "静岡県",
    "愛知県",
    "三重県",
    "滋賀県",
    "京都府",
    "大阪府",
    "兵庫県",
    "奈良県",
    "和歌山県",
    "鳥取県",
    "島根県",
    "岡山県",
    "広島県",
    "山口県",
    "徳島県",
    "香川県",
    "愛媛県",
    "高知県",
    "福岡県",
    "佐賀県",
    "長崎県",
    "熊本県",
    "大分県",
    "宮崎県",
    "鹿児島県",
    "沖縄県"
};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_prefecture_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCR_JMA_PREFECTURE_BASE || id >= QZSS_DCR_JMA_PREFECTURE_BASE + QZSS_DCR_JMA_PREFECTURE_SIZE) return std::nullopt;
    const char* s = QZSS_DCR_JMA_PREFECTURE_TABLE[id - QZSS_DCR_JMA_PREFECTURE_BASE];
    return s ? std::optional<std::string_view>(std::string_view{s}) : std::nullopt;
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_prefecture_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_prefecture_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
