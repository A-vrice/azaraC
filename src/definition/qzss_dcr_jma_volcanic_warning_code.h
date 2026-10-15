#pragma once
// AUTO-GENERATED from azarashi 0.17.1 with CI-CD
// Source module : azarashi.definitions.qzss.dcr.volcanic_warning_code
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

#if (AZARAC_ENABLE_VOLCANO) && (AZARAC_LANG_JA)

#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_POOL[] = "1(活火山であることに留意)\0002(火口周辺規制)\0003(入山規制)\0004(高齢者等避難)\0005(避難)\000活火山であることに留意\000火口周辺危険\000入山危険\000山麓厳重警戒\000居住地域厳重警戒\000活火山であることに留意(海底火山)\000周辺海域警戒\000噴火\000噴火したもよう\000その他の防災気象情報要素\000";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_PARENT_POOL[] = "レベル\000";
struct QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_PARENT_Entry { uint16_t offset; };
static const QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_PARENT_Entry QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_PARENT_TABLE[] AZARAC_PROGMEM = {
    {0u},
};
struct QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_Entry { uint8_t id; uint8_t parent; uint16_t offset; };
static const QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_Entry QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_TABLE[] AZARAC_PROGMEM = {
    {11u, 0u, 0u},
    {12u, 0u, 37u},
    {13u, 0u, 59u},
    {14u, 0u, 75u},
    {15u, 0u, 97u},
    {21u, 255u, 107u},
    {22u, 255u, 141u},
    {23u, 255u, 160u},
    {24u, 255u, 173u},
    {25u, 255u, 192u},
    {35u, 255u, 217u},
    {36u, 255u, 265u},
    {52u, 255u, 284u},
    {62u, 255u, 291u},
    {127u, 255u, 313u},
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_volcanic_warning_code_lookup(uint8_t id) noexcept {
    uint8_t lo = 0, hi = 15;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        azarac_pgm_ptr ep = AZARAC_PGM_PTR(QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_TABLE) + static_cast<size_t>(mid) * sizeof(QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_Entry);
        uint8_t eid = static_cast<uint8_t>(azarac_read_byte(ep, offsetof(QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_Entry, id)));
        if (eid == id) {
            uint16_t off = azarac_read_word(ep, offsetof(QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_Entry, offset));
            uint8_t pi = azarac_read_byte(ep, offsetof(QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_Entry, parent));
            if (pi == 255u) return azarac_pgm_view_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_POOL) + off);
            azarac_pgm_ptr pp = AZARAC_PGM_PTR(QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_PARENT_TABLE) + static_cast<size_t>(pi) * sizeof(QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_PARENT_Entry);
            uint16_t poff = azarac_read_word(pp, offsetof(QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_PARENT_Entry, offset));
            return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_PARENT_POOL) + poff, AZARAC_PGM_PTR(QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_POOL) + off);
        }
        if (eid < id) lo = static_cast<uint8_t>(mid + 1); else hi = mid;
    }
    return std::nullopt;
}
#else
struct QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_Entry { uint8_t id; const char* label; };
inline constexpr QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_Entry QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_TABLE[] = {
    {11u, "レベル1(活火山であることに留意)"},
    {12u, "レベル2(火口周辺規制)"},
    {13u, "レベル3(入山規制)"},
    {14u, "レベル4(高齢者等避難)"},
    {15u, "レベル5(避難)"},
    {21u, "活火山であることに留意"},
    {22u, "火口周辺危険"},
    {23u, "入山危険"},
    {24u, "山麓厳重警戒"},
    {25u, "居住地域厳重警戒"},
    {35u, "活火山であることに留意(海底火山)"},
    {36u, "周辺海域警戒"},
    {52u, "噴火"},
    {62u, "噴火したもよう"},
    {127u, "その他の防災気象情報要素"},};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_volcanic_warning_code_lookup(uint8_t id) noexcept {
    uint8_t lo = 0, hi = 15;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        if (QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_TABLE[mid].id == id) {
            const char* s = QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_TABLE[mid].label;
            return s ? std::optional<std::string_view>(std::string_view{s}) : std::nullopt;
        }
        if (QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_TABLE[mid].id < id) lo = mid + 1;
        else hi = mid;
    }
    return std::nullopt;
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_volcanic_warning_code_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_volcanic_warning_code_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
