#pragma once
// AUTO-GENERATED from azarashi 0.16.4 with CI-CD
// Source module : qzss_dcr_jma_volcanic_warning_code
// Variable      : qzss_dcr_jma_volcanic_warning_code
// Entries       : 15
// Strategy      : binary_search

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

#if (AZARAC_ENABLE_VOLCANO)

#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_POOL[] = "レベル1(活火山であることに留意)\0レベル2(火口周辺規制)\0レベル3(入山規制)\0レベル4(高齢者等避難)\0レベル5(避難)\0活火山であることに留意\0火口周辺危険\0入山危険\0山麓厳重警戒\0居住地域厳重警戒\0活火山であることに留意(海底火山)\0周辺海域警戒\0噴火\0噴火したもよう\0その他の防災気象情報要素\0";
struct QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_Entry { uint8_t id; uint16_t offset; uint16_t len; };
static const QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_Entry QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_TABLE[] AZARAC_PROGMEM = {
    {11u, 0u, 45u},
    {12u, 46u, 30u},
    {13u, 77u, 24u},
    {14u, 102u, 30u},
    {15u, 133u, 18u},
    {21u, 152u, 33u},
    {22u, 186u, 18u},
    {23u, 205u, 12u},
    {24u, 218u, 18u},
    {25u, 237u, 24u},
    {35u, 262u, 47u},
    {36u, 310u, 18u},
    {52u, 329u, 6u},
    {62u, 336u, 21u},
    {127u, 358u, 36u},
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_volcanic_warning_code_lookup(uint8_t id) noexcept {
    uint8_t lo = 0, hi = 15;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        const char* AZARAC_PROGMEM ep = reinterpret_cast<const char*>(&QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_TABLE[mid]);
        uint8_t eid = static_cast<uint8_t>(pgm_read_byte(ep + offsetof(QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_Entry, id)));
        if (eid == id) {
            uint16_t off = pgm_read_word(ep + offsetof(QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_Entry, offset));
            uint16_t n = pgm_read_word(ep + offsetof(QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_Entry, len));
            if (n == 0) return std::nullopt;
            return azarac_pgm_view(QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_POOL + off, n);
        }
        if (eid < id) lo = static_cast<uint8_t>(mid + 1); else hi = mid;
    }
    return std::nullopt;
}
#else
struct QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_Entry { uint8_t id; std::optional<std::string_view> label; };
inline constexpr QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_Entry QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_TABLE[] = {
    {11u, std::string_view{"レベル1(活火山であることに留意)", 45}},
    {12u, std::string_view{"レベル2(火口周辺規制)", 30}},
    {13u, std::string_view{"レベル3(入山規制)", 24}},
    {14u, std::string_view{"レベル4(高齢者等避難)", 30}},
    {15u, std::string_view{"レベル5(避難)", 18}},
    {21u, std::string_view{"活火山であることに留意", 33}},
    {22u, std::string_view{"火口周辺危険", 18}},
    {23u, std::string_view{"入山危険", 12}},
    {24u, std::string_view{"山麓厳重警戒", 18}},
    {25u, std::string_view{"居住地域厳重警戒", 24}},
    {35u, std::string_view{"活火山であることに留意(海底火山)", 47}},
    {36u, std::string_view{"周辺海域警戒", 18}},
    {52u, std::string_view{"噴火", 6}},
    {62u, std::string_view{"噴火したもよう", 21}},
    {127u, std::string_view{"その他の防災気象情報要素", 36}},};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_volcanic_warning_code_lookup(uint8_t id) noexcept {
    uint8_t lo = 0, hi = 15;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        if (QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_TABLE[mid].id == id) return QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_TABLE[mid].label;
        if (QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_TABLE[mid].id < id) lo = mid + 1;
        else hi = mid;
    }
    return std::nullopt;
}
#endif

#else

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_volcanic_warning_code_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}

#endif

} // namespace def
} // namespace azaraC
