#pragma once
// AUTO-GENERATED from azarashi 0.17.1 — do not edit
// azarashi.definitions.qzss.dcr.report_classification → qzss_dcr_jma_report_classification_en: 4 entries, strategy switch
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

#if (AZARAC_LANG_EN)

#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCR_JMA_REPORT_CLASSIFICATION_EN_C1[] = "Maximum Priority";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_REPORT_CLASSIFICATION_EN_C2[] = "Priority";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_REPORT_CLASSIFICATION_EN_C3[] = "Regular";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_REPORT_CLASSIFICATION_EN_C7[] = "Training/Test";
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_report_classification_en_lookup(uint8_t id) noexcept {
    switch (id) {
        case 1: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCR_JMA_REPORT_CLASSIFICATION_EN_C1), 16);
        case 2: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCR_JMA_REPORT_CLASSIFICATION_EN_C2), 8);
        case 3: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCR_JMA_REPORT_CLASSIFICATION_EN_C3), 7);
        case 7: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCR_JMA_REPORT_CLASSIFICATION_EN_C7), 13);
        default: return std::nullopt;
    }
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_report_classification_en_lookup(uint8_t id) noexcept {
    switch (id) {
        case 1: return std::string_view{"Maximum Priority", 16};
        case 2: return std::string_view{"Priority", 8};
        case 3: return std::string_view{"Regular", 7};
        case 7: return std::string_view{"Training/Test", 13};
        default: return std::nullopt;
    }
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_report_classification_en_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_report_classification_en_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
