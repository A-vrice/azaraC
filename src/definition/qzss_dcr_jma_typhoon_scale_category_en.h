#pragma once
// AUTO-GENERATED from azarashi 0.17.1 — do not edit
// Specs: IS-QZSS-DCR-017 / IS-QZSS-DCX-004 Rev.004 / EWSS CAMF Issue 1.2
// azarashi.definitions.qzss.dcr.typhoon_scale_category → qzss_dcr_jma_typhoon_scale_category_en: 4 entries, strategy switch
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

#if (AZARAC_ENABLE_TYPHOON) && (AZARAC_LANG_EN)

static const char AZARAC_PROGMEM QZSS_DCR_JMA_TYPHOON_SCALE_CATEGORY_EN_C0[] = "None";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_TYPHOON_SCALE_CATEGORY_EN_C1[] = "Large";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_TYPHOON_SCALE_CATEGORY_EN_C2[] = "Very large";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_TYPHOON_SCALE_CATEGORY_EN_C15[] = "Other Scale Category";
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_typhoon_scale_category_en_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCR_JMA_TYPHOON_SCALE_CATEGORY_EN_C0), 4);
        case 1: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCR_JMA_TYPHOON_SCALE_CATEGORY_EN_C1), 5);
        case 2: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCR_JMA_TYPHOON_SCALE_CATEGORY_EN_C2), 10);
        case 15: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCR_JMA_TYPHOON_SCALE_CATEGORY_EN_C15), 20);
        default: return std::nullopt;
    }
}

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_typhoon_scale_category_en_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_typhoon_scale_category_en_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
