#pragma once
// AUTO-GENERATED from azarashi 0.17.1 — do not edit
// azarashi.definitions.qzss.dcr.flood_warning_level → qzss_dcr_jma_flood_warning_level_en: 5 entries, strategy switch
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

#if (AZARAC_ENABLE_FLOOD) && (AZARAC_LANG_EN)

#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCR_JMA_FLOOD_WARNING_LEVEL_EN_C1[] = "Warning Lifted";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_FLOOD_WARNING_LEVEL_EN_C2[] = "Information to provide a warning on flooding";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_FLOOD_WARNING_LEVEL_EN_C3[] = "Information on potential flood hazards";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_FLOOD_WARNING_LEVEL_EN_C4[] = "Information on flooding";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_FLOOD_WARNING_LEVEL_EN_C15[] = "Other Warning Level";
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_flood_warning_level_en_lookup(uint8_t id) noexcept {
    switch (id) {
        case 1: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCR_JMA_FLOOD_WARNING_LEVEL_EN_C1), 14);
        case 2: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCR_JMA_FLOOD_WARNING_LEVEL_EN_C2), 44);
        case 3: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCR_JMA_FLOOD_WARNING_LEVEL_EN_C3), 38);
        case 4: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCR_JMA_FLOOD_WARNING_LEVEL_EN_C4), 23);
        case 15: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCR_JMA_FLOOD_WARNING_LEVEL_EN_C15), 19);
        default: return std::nullopt;
    }
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_flood_warning_level_en_lookup(uint8_t id) noexcept {
    switch (id) {
        case 1: return std::string_view{"Warning Lifted", 14};
        case 2: return std::string_view{"Information to provide a warning on flooding", 44};
        case 3: return std::string_view{"Information on potential flood hazards", 38};
        case 4: return std::string_view{"Information on flooding", 23};
        case 15: return std::string_view{"Other Warning Level", 19};
        default: return std::nullopt;
    }
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_flood_warning_level_en_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_flood_warning_level_en_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
