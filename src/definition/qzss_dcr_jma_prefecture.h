#pragma once
// AUTO-GENERATED from azarashi 0.17.1 — do not edit
// azarashi.definitions.qzss.dcr.prefecture → qzss_dcr_jma_prefecture: 47 entries, strategy array
// Unknown id returns nullptr — callers MUST null-check.

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
static const char AZARAC_PROGMEM QZSS_DCR_JMA_PREFECTURE_POOL[] = "北海道\000青森県\000岩手県\000宮城県\000秋田県\000山形県\000福島県\000茨城県\000栃木県\000群馬県\000埼玉県\000千葉県\000東京都\000神奈川県\000新潟県\000富山県\000石川県\000福井県\000山梨県\000長野県\000岐阜県\000静岡県\000愛知県\000三重県\000滋賀県\000京都府\000大阪府\000兵庫県\000奈良県\000和歌山県\000鳥取県\000島根県\000岡山県\000広島県\000山口県\000徳島県\000香川県\000愛媛県\000高知県\000福岡県\000佐賀県\000長崎県\000熊本県\000大分県\000宮崎県\000鹿児島県\000沖縄県\000";
struct QZSS_DCR_JMA_PREFECTURE_Entry { uint16_t offset; };
static const QZSS_DCR_JMA_PREFECTURE_Entry QZSS_DCR_JMA_PREFECTURE_TABLE[] AZARAC_PROGMEM = {
    {0u},
    {10u},
    {20u},
    {30u},
    {40u},
    {50u},
    {60u},
    {70u},
    {80u},
    {90u},
    {100u},
    {110u},
    {120u},
    {130u},
    {143u},
    {153u},
    {163u},
    {173u},
    {183u},
    {193u},
    {203u},
    {213u},
    {223u},
    {233u},
    {243u},
    {253u},
    {263u},
    {273u},
    {283u},
    {293u},
    {306u},
    {316u},
    {326u},
    {336u},
    {346u},
    {356u},
    {366u},
    {376u},
    {386u},
    {396u},
    {406u},
    {416u},
    {426u},
    {436u},
    {446u},
    {456u},
    {469u}
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_prefecture_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCR_JMA_PREFECTURE_BASE || id >= QZSS_DCR_JMA_PREFECTURE_BASE + QZSS_DCR_JMA_PREFECTURE_SIZE) return std::nullopt;
    azarac_pgm_ptr p = AZARAC_PGM_PTR(QZSS_DCR_JMA_PREFECTURE_TABLE) + static_cast<size_t>(id - 1u) * sizeof(QZSS_DCR_JMA_PREFECTURE_Entry);
    uint16_t off = azarac_read_word(p, offsetof(QZSS_DCR_JMA_PREFECTURE_Entry, offset));
    return azarac_pgm_view_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_PREFECTURE_POOL) + off);
}

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
