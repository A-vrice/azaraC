#pragma once
// AUTO-GENERATED from azarashi 0.17.1 — do not edit
// azarashi.definitions.camf.a6_hazard_onset_week → qzss_dcx_camf_a6_hazard_onset_week: 2 entries, strategy switch
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

#if (AZARAC_ENABLE_DCX_CAMF)

#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_A6_HAZARD_ONSET_WEEK_C0[] = "Current";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_A6_HAZARD_ONSET_WEEK_C1[] = "Next";
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_a6_hazard_onset_week_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCX_CAMF_A6_HAZARD_ONSET_WEEK_C0), 7);
        case 1: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCX_CAMF_A6_HAZARD_ONSET_WEEK_C1), 4);
        default: return std::nullopt;
    }
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_a6_hazard_onset_week_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return std::string_view{"Current", 7};
        case 1: return std::string_view{"Next", 4};
        default: return std::nullopt;
    }
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_a6_hazard_onset_week_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_a6_hazard_onset_week_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
