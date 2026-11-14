#pragma once
// AUTO-GENERATED from azarashi 0.17.1 — do not edit
// Specs: IS-QZSS-DCR-017 / IS-QZSS-DCX-004 Rev.004 / EWSS CAMF Issue 1.2
// azarashi.definitions.qzss.dcr.northwest_pacific_tsunami_height → qzss_dcr_jma_northwest_pacific_tsunami_height_en: 8 entries, strategy switch
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

#if (AZARAC_ENABLE_NW_PAC_TSUNAMI)

static const char AZARAC_PROGMEM QZSS_DCR_JMA_NORTHWEST_PACIFIC_TSUNAMI_HEIGHT_EN_C1[] = "0.3m~1m";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_NORTHWEST_PACIFIC_TSUNAMI_HEIGHT_EN_C2[] = "1m~3m";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_NORTHWEST_PACIFIC_TSUNAMI_HEIGHT_EN_C3[] = "3m~5m";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_NORTHWEST_PACIFIC_TSUNAMI_HEIGHT_EN_C4[] = "5m~10m";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_NORTHWEST_PACIFIC_TSUNAMI_HEIGHT_EN_C508[] = "More than 10m";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_NORTHWEST_PACIFIC_TSUNAMI_HEIGHT_EN_C509[] = "Huge";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_NORTHWEST_PACIFIC_TSUNAMI_HEIGHT_EN_C510[] = "High";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_NORTHWEST_PACIFIC_TSUNAMI_HEIGHT_EN_C511[] = "Unknown";
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_northwest_pacific_tsunami_height_en_lookup(uint16_t id) noexcept {
    switch (id) {
        case 1: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCR_JMA_NORTHWEST_PACIFIC_TSUNAMI_HEIGHT_EN_C1), 7);
        case 2: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCR_JMA_NORTHWEST_PACIFIC_TSUNAMI_HEIGHT_EN_C2), 5);
        case 3: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCR_JMA_NORTHWEST_PACIFIC_TSUNAMI_HEIGHT_EN_C3), 5);
        case 4: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCR_JMA_NORTHWEST_PACIFIC_TSUNAMI_HEIGHT_EN_C4), 6);
        case 508: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCR_JMA_NORTHWEST_PACIFIC_TSUNAMI_HEIGHT_EN_C508), 13);
        case 509: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCR_JMA_NORTHWEST_PACIFIC_TSUNAMI_HEIGHT_EN_C509), 4);
        case 510: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCR_JMA_NORTHWEST_PACIFIC_TSUNAMI_HEIGHT_EN_C510), 4);
        case 511: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCR_JMA_NORTHWEST_PACIFIC_TSUNAMI_HEIGHT_EN_C511), 7);
        default: return std::nullopt;
    }
}

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_northwest_pacific_tsunami_height_en_lookup(uint16_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_northwest_pacific_tsunami_height_en_lookup(uint16_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
