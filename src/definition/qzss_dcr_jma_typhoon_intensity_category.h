#pragma once
// AUTO-GENERATED from azarashi 0.17.1 — do not edit
// azarashi.definitions.qzss.dcr.typhoon_intensity_category → qzss_dcr_jma_typhoon_intensity_category: 5 entries, strategy switch
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

#if (AZARAC_ENABLE_TYPHOON) && (AZARAC_LANG_JA)

#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCR_JMA_TYPHOON_INTENSITY_CATEGORY_C0[] = "なし";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_TYPHOON_INTENSITY_CATEGORY_C1[] = "強い";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_TYPHOON_INTENSITY_CATEGORY_C2[] = "非常に強い";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_TYPHOON_INTENSITY_CATEGORY_C3[] = "猛烈な";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_TYPHOON_INTENSITY_CATEGORY_C15[] = "その他の強さ階級分類";
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_typhoon_intensity_category_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCR_JMA_TYPHOON_INTENSITY_CATEGORY_C0), 6);
        case 1: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCR_JMA_TYPHOON_INTENSITY_CATEGORY_C1), 6);
        case 2: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCR_JMA_TYPHOON_INTENSITY_CATEGORY_C2), 15);
        case 3: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCR_JMA_TYPHOON_INTENSITY_CATEGORY_C3), 9);
        case 15: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCR_JMA_TYPHOON_INTENSITY_CATEGORY_C15), 30);
        default: return std::nullopt;
    }
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_typhoon_intensity_category_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return std::string_view{"なし", 6};
        case 1: return std::string_view{"強い", 6};
        case 2: return std::string_view{"非常に強い", 15};
        case 3: return std::string_view{"猛烈な", 9};
        case 15: return std::string_view{"その他の強さ階級分類", 30};
        default: return std::nullopt;
    }
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_typhoon_intensity_category_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_typhoon_intensity_category_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
