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
static const char AZARAC_PROGMEM QZSS_DCR_JMA_PREFECTURE_POOL[] = "北海道\000青森\000岩手\000宮城\000秋田\000山形\000福島\000茨城\000栃木\000群馬\000埼玉\000千葉\000東京都\000神奈川\000新潟\000富山\000石川\000福井\000山梨\000長野\000岐阜\000静岡\000愛知\000三重\000滋賀\000京都府\000大阪府\000兵庫\000奈良\000和歌山\000鳥取\000島根\000岡山\000広島\000山口\000徳島\000香川\000愛媛\000高知\000福岡\000佐賀\000長崎\000熊本\000大分\000宮崎\000鹿児島\000沖縄\000";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_PREFECTURE_PARENT_POOL[] = "県\000";
struct QZSS_DCR_JMA_PREFECTURE_PARENT_Entry { uint16_t offset; uint8_t len; };
static const QZSS_DCR_JMA_PREFECTURE_PARENT_Entry QZSS_DCR_JMA_PREFECTURE_PARENT_TABLE[] AZARAC_PROGMEM = {
    {0u, 3u},
};
struct QZSS_DCR_JMA_PREFECTURE_Entry { uint16_t offset; uint8_t len; uint8_t parent; };
static const QZSS_DCR_JMA_PREFECTURE_Entry QZSS_DCR_JMA_PREFECTURE_TABLE[] AZARAC_PROGMEM = {
    {0u, 9u, 255u},
    {10u, 6u, 0u},
    {17u, 6u, 0u},
    {24u, 6u, 0u},
    {31u, 6u, 0u},
    {38u, 6u, 0u},
    {45u, 6u, 0u},
    {52u, 6u, 0u},
    {59u, 6u, 0u},
    {66u, 6u, 0u},
    {73u, 6u, 0u},
    {80u, 6u, 0u},
    {87u, 9u, 255u},
    {97u, 9u, 0u},
    {107u, 6u, 0u},
    {114u, 6u, 0u},
    {121u, 6u, 0u},
    {128u, 6u, 0u},
    {135u, 6u, 0u},
    {142u, 6u, 0u},
    {149u, 6u, 0u},
    {156u, 6u, 0u},
    {163u, 6u, 0u},
    {170u, 6u, 0u},
    {177u, 6u, 0u},
    {184u, 9u, 255u},
    {194u, 9u, 255u},
    {204u, 6u, 0u},
    {211u, 6u, 0u},
    {218u, 9u, 0u},
    {228u, 6u, 0u},
    {235u, 6u, 0u},
    {242u, 6u, 0u},
    {249u, 6u, 0u},
    {256u, 6u, 0u},
    {263u, 6u, 0u},
    {270u, 6u, 0u},
    {277u, 6u, 0u},
    {284u, 6u, 0u},
    {291u, 6u, 0u},
    {298u, 6u, 0u},
    {305u, 6u, 0u},
    {312u, 6u, 0u},
    {319u, 6u, 0u},
    {326u, 6u, 0u},
    {333u, 9u, 0u},
    {343u, 6u, 0u}
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_prefecture_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCR_JMA_PREFECTURE_BASE || id >= QZSS_DCR_JMA_PREFECTURE_BASE + QZSS_DCR_JMA_PREFECTURE_SIZE) return std::nullopt;
    const char* AZARAC_PROGMEM p = reinterpret_cast<const char*>(&QZSS_DCR_JMA_PREFECTURE_TABLE[id - 1u]);
    uint16_t off = pgm_read_word(p + offsetof(QZSS_DCR_JMA_PREFECTURE_Entry, offset));
    uint8_t n = pgm_read_byte(p + offsetof(QZSS_DCR_JMA_PREFECTURE_Entry, len));
    uint8_t pi = pgm_read_byte(p + offsetof(QZSS_DCR_JMA_PREFECTURE_Entry, parent));
    if (pi == 255u) return azarac_pgm_view(QZSS_DCR_JMA_PREFECTURE_POOL + off, n);
    const char* AZARAC_PROGMEM pp = reinterpret_cast<const char*>(&QZSS_DCR_JMA_PREFECTURE_PARENT_TABLE[pi]);
    uint16_t poff = pgm_read_word(pp + offsetof(QZSS_DCR_JMA_PREFECTURE_PARENT_Entry, offset));
    uint8_t pn = pgm_read_byte(pp + offsetof(QZSS_DCR_JMA_PREFECTURE_PARENT_Entry, len));
    return azarac_pgm_join(QZSS_DCR_JMA_PREFECTURE_POOL + off, n, QZSS_DCR_JMA_PREFECTURE_PARENT_POOL + poff, pn);
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
