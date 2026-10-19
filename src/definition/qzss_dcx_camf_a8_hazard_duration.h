#pragma once
// AUTO-GENERATED from azarashi 0.17.1 — do not edit
// azarashi.definitions.camf.a8_hazard_duration → qzss_dcx_camf_a8_hazard_duration: 4 entries, strategy switch
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
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_A8_HAZARD_DURATION_C0[] = "Unknown";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_A8_HAZARD_DURATION_C1[] = "Duration < 6H";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_A8_HAZARD_DURATION_C2[] = "6H <= Duration < 12H";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_A8_HAZARD_DURATION_C3[] = "12H <= Duration < 24H";
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_a8_hazard_duration_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCX_CAMF_A8_HAZARD_DURATION_C0), 7);
        case 1: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCX_CAMF_A8_HAZARD_DURATION_C1), 13);
        case 2: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCX_CAMF_A8_HAZARD_DURATION_C2), 20);
        case 3: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCX_CAMF_A8_HAZARD_DURATION_C3), 21);
        default: return std::nullopt;
    }
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_a8_hazard_duration_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return std::string_view{"Unknown", 7};
        case 1: return std::string_view{"Duration < 6H", 13};
        case 2: return std::string_view{"6H <= Duration < 12H", 20};
        case 3: return std::string_view{"12H <= Duration < 24H", 21};
        default: return std::nullopt;
    }
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_a8_hazard_duration_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_a8_hazard_duration_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
