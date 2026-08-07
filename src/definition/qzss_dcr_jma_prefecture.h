#pragma once
// AUTO-GENERATED from azarashi 0.16.4 with CI-CD
// Source module : qzss_dcr_jma_prefecture
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

#if (AZARAC_ENABLE_SEISMIC || AZARAC_ENABLE_DCX_CAMF)

inline constexpr uint8_t QZSS_DCR_JMA_PREFECTURE_BASE = 1;
inline constexpr uint8_t QZSS_DCR_JMA_PREFECTURE_SIZE = 47;
#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCR_JMA_PREFECTURE_POOL[] = "北海道\000青森県\000岩手県\000宮城県\000秋田県\000山形県\000福島県\000茨城県\000栃木県\000群馬県\000埼玉県\000千葉県\000東京都\000神奈川県\000新潟県\000富山県\000石川県\000福井県\000山梨県\000長野県\000岐阜県\000静岡県\000愛知県\000三重県\000滋賀県\000京都府\000大阪府\000兵庫県\000奈良県\000和歌山県\000鳥取県\000島根県\000岡山県\000広島県\000山口県\000徳島県\000香川県\000愛媛県\000高知県\000福岡県\000佐賀県\000長崎県\000熊本県\000大分県\000宮崎県\000鹿児島県\000沖縄県\000";
struct QZSS_DCR_JMA_PREFECTURE_Entry { uint16_t offset; uint16_t len; };
static const QZSS_DCR_JMA_PREFECTURE_Entry QZSS_DCR_JMA_PREFECTURE_TABLE[] AZARAC_PROGMEM = {
    {0u, 9u},
    {10u, 9u},
    {20u, 9u},
    {30u, 9u},
    {40u, 9u},
    {50u, 9u},
    {60u, 9u},
    {70u, 9u},
    {80u, 9u},
    {90u, 9u},
    {100u, 9u},
    {110u, 9u},
    {120u, 9u},
    {130u, 12u},
    {143u, 9u},
    {153u, 9u},
    {163u, 9u},
    {173u, 9u},
    {183u, 9u},
    {193u, 9u},
    {203u, 9u},
    {213u, 9u},
    {223u, 9u},
    {233u, 9u},
    {243u, 9u},
    {253u, 9u},
    {263u, 9u},
    {273u, 9u},
    {283u, 9u},
    {293u, 12u},
    {306u, 9u},
    {316u, 9u},
    {326u, 9u},
    {336u, 9u},
    {346u, 9u},
    {356u, 9u},
    {366u, 9u},
    {376u, 9u},
    {386u, 9u},
    {396u, 9u},
    {406u, 9u},
    {416u, 9u},
    {426u, 9u},
    {436u, 9u},
    {446u, 9u},
    {456u, 12u},
    {469u, 9u}
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_prefecture_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCR_JMA_PREFECTURE_BASE || id >= QZSS_DCR_JMA_PREFECTURE_BASE + QZSS_DCR_JMA_PREFECTURE_SIZE) return std::nullopt;
    const char* AZARAC_PROGMEM p = reinterpret_cast<const char*>(&QZSS_DCR_JMA_PREFECTURE_TABLE[id - 1u]);
    uint16_t off = pgm_read_word(p + offsetof(QZSS_DCR_JMA_PREFECTURE_Entry, offset));
    uint16_t n = pgm_read_word(p + offsetof(QZSS_DCR_JMA_PREFECTURE_Entry, len));
    if (n == 0) return std::nullopt;
    return azarac_pgm_view(QZSS_DCR_JMA_PREFECTURE_POOL + off, n);
}
#else
inline constexpr std::optional<std::string_view> QZSS_DCR_JMA_PREFECTURE_TABLE[] = {
    std::string_view{"北海道", 9},
    std::string_view{"青森県", 9},
    std::string_view{"岩手県", 9},
    std::string_view{"宮城県", 9},
    std::string_view{"秋田県", 9},
    std::string_view{"山形県", 9},
    std::string_view{"福島県", 9},
    std::string_view{"茨城県", 9},
    std::string_view{"栃木県", 9},
    std::string_view{"群馬県", 9},
    std::string_view{"埼玉県", 9},
    std::string_view{"千葉県", 9},
    std::string_view{"東京都", 9},
    std::string_view{"神奈川県", 12},
    std::string_view{"新潟県", 9},
    std::string_view{"富山県", 9},
    std::string_view{"石川県", 9},
    std::string_view{"福井県", 9},
    std::string_view{"山梨県", 9},
    std::string_view{"長野県", 9},
    std::string_view{"岐阜県", 9},
    std::string_view{"静岡県", 9},
    std::string_view{"愛知県", 9},
    std::string_view{"三重県", 9},
    std::string_view{"滋賀県", 9},
    std::string_view{"京都府", 9},
    std::string_view{"大阪府", 9},
    std::string_view{"兵庫県", 9},
    std::string_view{"奈良県", 9},
    std::string_view{"和歌山県", 12},
    std::string_view{"鳥取県", 9},
    std::string_view{"島根県", 9},
    std::string_view{"岡山県", 9},
    std::string_view{"広島県", 9},
    std::string_view{"山口県", 9},
    std::string_view{"徳島県", 9},
    std::string_view{"香川県", 9},
    std::string_view{"愛媛県", 9},
    std::string_view{"高知県", 9},
    std::string_view{"福岡県", 9},
    std::string_view{"佐賀県", 9},
    std::string_view{"長崎県", 9},
    std::string_view{"熊本県", 9},
    std::string_view{"大分県", 9},
    std::string_view{"宮崎県", 9},
    std::string_view{"鹿児島県", 12},
    std::string_view{"沖縄県", 9}
};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_prefecture_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCR_JMA_PREFECTURE_BASE || id >= QZSS_DCR_JMA_PREFECTURE_BASE + QZSS_DCR_JMA_PREFECTURE_SIZE) return std::nullopt;
    return QZSS_DCR_JMA_PREFECTURE_TABLE[id - QZSS_DCR_JMA_PREFECTURE_BASE];
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
