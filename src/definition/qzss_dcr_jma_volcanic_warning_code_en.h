#pragma once
// AUTO-GENERATED from azarashi 0.17.1 with CI-CD
// Source module : azarashi.definitions.qzss.dcr.volcanic_warning_code
// Variable      : qzss_dcr_jma_volcanic_warning_code_en
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

#if (AZARAC_ENABLE_VOLCANO) && (AZARAC_LANG_EN)

#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_EN_POOL[] = "Level 1 (Potential for increased activity)\000Level 2 (Restriction on proximity to the crater)\000Level 3 (Restriction on proximity to the volcano)\000Level 4 (Evacuation of the elderly, etc.)\000Level 5 (Evacuation)\000Potential for increased activity\000Caution advised around the crater\000Caution in non-residential areas near the crater\000Extreme caution advised at the foot of mountains concerned\000Extreme caution advised in residential areas and non-residential areas nearer the crater\000Potential for increased activity (Submarine volcano)\000Caution advised for the sea area in the vicinity of the volcano\000Volcanic eruptions\000Possible eruption\000Other Volcanic Warning\000";
struct QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_EN_Entry { uint8_t id; uint16_t offset; uint16_t len; };
static const QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_EN_Entry QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_EN_TABLE[] AZARAC_PROGMEM = {
    {11u, 0u, 42u},
    {12u, 43u, 48u},
    {13u, 92u, 49u},
    {14u, 142u, 41u},
    {15u, 184u, 20u},
    {21u, 205u, 32u},
    {22u, 238u, 33u},
    {23u, 272u, 48u},
    {24u, 321u, 58u},
    {25u, 380u, 88u},
    {35u, 469u, 52u},
    {36u, 522u, 63u},
    {52u, 586u, 18u},
    {62u, 605u, 17u},
    {127u, 623u, 22u},
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_volcanic_warning_code_en_lookup(uint8_t id) noexcept {
    uint8_t lo = 0, hi = 15;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        const char* AZARAC_PROGMEM ep = reinterpret_cast<const char*>(&QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_EN_TABLE[mid]);
        uint8_t eid = static_cast<uint8_t>(pgm_read_byte(ep + offsetof(QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_EN_Entry, id)));
        if (eid == id) {
            uint16_t off = pgm_read_word(ep + offsetof(QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_EN_Entry, offset));
            uint16_t n = pgm_read_word(ep + offsetof(QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_EN_Entry, len));
            return azarac_pgm_view(QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_EN_POOL + off, n);
        }
        if (eid < id) lo = static_cast<uint8_t>(mid + 1); else hi = mid;
    }
    return std::nullopt;
}
#else
struct QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_EN_Entry { uint8_t id; const char* label; };
inline constexpr QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_EN_Entry QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_EN_TABLE[] = {
    {11u, "Level 1 (Potential for increased activity)"},
    {12u, "Level 2 (Restriction on proximity to the crater)"},
    {13u, "Level 3 (Restriction on proximity to the volcano)"},
    {14u, "Level 4 (Evacuation of the elderly, etc.)"},
    {15u, "Level 5 (Evacuation)"},
    {21u, "Potential for increased activity"},
    {22u, "Caution advised around the crater"},
    {23u, "Caution in non-residential areas near the crater"},
    {24u, "Extreme caution advised at the foot of mountains concerned"},
    {25u, "Extreme caution advised in residential areas and non-residential areas nearer the crater"},
    {35u, "Potential for increased activity (Submarine volcano)"},
    {36u, "Caution advised for the sea area in the vicinity of the volcano"},
    {52u, "Volcanic eruptions"},
    {62u, "Possible eruption"},
    {127u, "Other Volcanic Warning"},};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_volcanic_warning_code_en_lookup(uint8_t id) noexcept {
    uint8_t lo = 0, hi = 15;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        if (QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_EN_TABLE[mid].id == id) {
            const char* s = QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_EN_TABLE[mid].label;
            return s ? std::optional<std::string_view>(std::string_view{s}) : std::nullopt;
        }
        if (QZSS_DCR_JMA_VOLCANIC_WARNING_CODE_EN_TABLE[mid].id < id) lo = mid + 1;
        else hi = mid;
    }
    return std::nullopt;
}
#endif

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
