#pragma once
// AUTO-GENERATED from azarashi 0.17.1 — do not edit
// azarashi.definitions.qzss.dcr.ash_fall_warning_type → qzss_dcr_jma_ash_fall_warning_type_en: 2 entries, strategy switch
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

#if (AZARAC_ENABLE_ASH_FALL) && (AZARAC_LANG_EN)

#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCR_JMA_ASH_FALL_WARNING_TYPE_EN_C1[] = "Preliminary";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_ASH_FALL_WARNING_TYPE_EN_C2[] = "Detailed";
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_ash_fall_warning_type_en_lookup(uint8_t id) noexcept {
    switch (id) {
        case 1: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCR_JMA_ASH_FALL_WARNING_TYPE_EN_C1), 11);
        case 2: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCR_JMA_ASH_FALL_WARNING_TYPE_EN_C2), 8);
        default: return std::nullopt;
    }
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_ash_fall_warning_type_en_lookup(uint8_t id) noexcept {
    switch (id) {
        case 1: return std::string_view{"Preliminary", 11};
        case 2: return std::string_view{"Detailed", 8};
        default: return std::nullopt;
    }
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_ash_fall_warning_type_en_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_ash_fall_warning_type_en_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
