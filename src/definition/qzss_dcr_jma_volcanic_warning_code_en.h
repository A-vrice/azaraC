#pragma once
// AUTO-GENERATED from azarashi 0.17.1 — do not edit
// Specs: IS-QZSS-DCR-017 / IS-QZSS-DCX-004 Rev.004 / EWSS CAMF Issue 1.2
// azarashi.definitions.qzss.dcr.volcanic_warning_code → qzss_dcr_jma_volcanic_warning_code_en: 15 entries, strategy binary_search
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

#if (AZARAC_ENABLE_VOLCANO) && (AZARAC_LANG_EN)

static const char AZARAC_PROGMEM QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_EN_POOL[] = "1 (Potential for increased activity)\0002 (Restriction on proximity to the crater)\0003 (Restriction on proximity to the volcano)\0004 (Evacuation of the elderly, etc.)\0005 (Evacuation)\000Potential for increased activity\000Caution advised around the crater\000Caution in non-residential areas near the crater\000Extreme caution advised at the foot of mountains concerned\000Extreme caution advised in residential areas and non-residential areas nearer the crater\000Potential for increased activity (Submarine volcano)\000Caution advised for the sea area in the vicinity of the volcano\000Volcanic eruptions\000Possible eruption\000Other Volcanic Warning\000";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_EN_PARENT_POOL[] = "Level \000";
struct QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_EN_PARENT_Entry { uint16_t offset; };
static const QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_EN_PARENT_Entry QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_EN_PARENT_TABLE[] AZARAC_PROGMEM = {
    {0u},
};
struct QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_EN_Entry { uint8_t id; uint8_t parent; uint16_t offset; };
static const QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_EN_Entry QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_EN_TABLE[] AZARAC_PROGMEM = {
    {11u, 0u, 0u},
    {12u, 0u, 37u},
    {13u, 0u, 80u},
    {14u, 0u, 124u},
    {15u, 0u, 160u},
    {21u, 255u, 175u},
    {22u, 255u, 208u},
    {23u, 255u, 242u},
    {24u, 255u, 291u},
    {25u, 255u, 350u},
    {35u, 255u, 439u},
    {36u, 255u, 492u},
    {52u, 255u, 556u},
    {62u, 255u, 575u},
    {127u, 255u, 593u},
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_volcanic_warning_code_en_lookup(uint8_t id) noexcept {
    uint8_t lo = 0, hi = 15;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        azarac_pgm_ptr ep = AZARAC_PGM_PTR(QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_EN_TABLE) + static_cast<size_t>(mid) * sizeof(QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_EN_Entry);
        uint8_t eid = static_cast<uint8_t>(azarac_read_byte(ep, offsetof(QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_EN_Entry, id)));
        if (eid == id) {
            uint16_t off = azarac_read_word(ep, offsetof(QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_EN_Entry, offset));
            uint8_t pi = azarac_read_byte(ep, offsetof(QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_EN_Entry, parent));
            if (pi == 255u) return azarac_pgm_view_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_EN_POOL) + off);
            azarac_pgm_ptr pp = AZARAC_PGM_PTR(QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_EN_PARENT_TABLE) + static_cast<size_t>(pi) * sizeof(QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_EN_PARENT_Entry);
            uint16_t poff = azarac_read_word(pp, offsetof(QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_EN_PARENT_Entry, offset));
            return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_EN_PARENT_POOL) + poff, AZARAC_PGM_PTR(QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_EN_POOL) + off);
        }
        if (eid < id) lo = static_cast<uint8_t>(mid + 1); else hi = mid;
    }
    return std::nullopt;
}

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_volcanic_warning_code_en_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_volcanic_warning_code_en_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
