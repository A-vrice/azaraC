#pragma once
// AUTO-GENERATED from azarashi 0.17.1 — do not edit
// azarashi.definitions.qzss.dcr.seismic_intensity → qzss_dcr_jma_seismic_intensity: 7 entries, strategy switch
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

#if (AZARAC_ENABLE_SEISMIC) && (AZARAC_LANG_JA)

#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCR_JMA_SEISMIC_INTENSITY_C1[] = "4未満";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_SEISMIC_INTENSITY_C2[] = "4";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_SEISMIC_INTENSITY_C3[] = "5弱";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_SEISMIC_INTENSITY_C4[] = "5強";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_SEISMIC_INTENSITY_C5[] = "6弱";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_SEISMIC_INTENSITY_C6[] = "6強";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_SEISMIC_INTENSITY_C7[] = "7";
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_seismic_intensity_lookup(uint8_t id) noexcept {
    switch (id) {
        case 1: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCR_JMA_SEISMIC_INTENSITY_C1), 7);
        case 2: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCR_JMA_SEISMIC_INTENSITY_C2), 1);
        case 3: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCR_JMA_SEISMIC_INTENSITY_C3), 4);
        case 4: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCR_JMA_SEISMIC_INTENSITY_C4), 4);
        case 5: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCR_JMA_SEISMIC_INTENSITY_C5), 4);
        case 6: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCR_JMA_SEISMIC_INTENSITY_C6), 4);
        case 7: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCR_JMA_SEISMIC_INTENSITY_C7), 1);
        default: return std::nullopt;
    }
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_seismic_intensity_lookup(uint8_t id) noexcept {
    switch (id) {
        case 1: return std::string_view{"4未満", 7};
        case 2: return std::string_view{"4", 1};
        case 3: return std::string_view{"5弱", 4};
        case 4: return std::string_view{"5強", 4};
        case 5: return std::string_view{"6弱", 4};
        case 6: return std::string_view{"6強", 4};
        case 7: return std::string_view{"7", 1};
        default: return std::nullopt;
    }
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_seismic_intensity_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_seismic_intensity_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
