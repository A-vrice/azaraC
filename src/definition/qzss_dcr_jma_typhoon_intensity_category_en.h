#pragma once
// AUTO-GENERATED from azarashi 0.17.1 — do not edit
// azarashi.definitions.qzss.dcr.typhoon_intensity_category → qzss_dcr_jma_typhoon_intensity_category_en: 5 entries, strategy switch
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

#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCR_JMA_TYPHOON_INTENSITY_CATEGORY_EN_C0[] = "None";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_TYPHOON_INTENSITY_CATEGORY_EN_C1[] = "Strong";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_TYPHOON_INTENSITY_CATEGORY_EN_C2[] = "Very Strong";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_TYPHOON_INTENSITY_CATEGORY_EN_C3[] = "Violent";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_TYPHOON_INTENSITY_CATEGORY_EN_C15[] = "Other Intensity Category";
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_typhoon_intensity_category_en_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCR_JMA_TYPHOON_INTENSITY_CATEGORY_EN_C0), 4);
        case 1: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCR_JMA_TYPHOON_INTENSITY_CATEGORY_EN_C1), 6);
        case 2: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCR_JMA_TYPHOON_INTENSITY_CATEGORY_EN_C2), 11);
        case 3: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCR_JMA_TYPHOON_INTENSITY_CATEGORY_EN_C3), 7);
        case 15: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCR_JMA_TYPHOON_INTENSITY_CATEGORY_EN_C15), 24);
        default: return std::nullopt;
    }
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_typhoon_intensity_category_en_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return std::string_view{"None", 4};
        case 1: return std::string_view{"Strong", 6};
        case 2: return std::string_view{"Very Strong", 11};
        case 3: return std::string_view{"Violent", 7};
        case 15: return std::string_view{"Other Intensity Category", 24};
        default: return std::nullopt;
    }
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_typhoon_intensity_category_en_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_typhoon_intensity_category_en_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
