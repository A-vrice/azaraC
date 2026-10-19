#pragma once
// AUTO-GENERATED from azarashi 0.17.1 — do not edit
// azarashi.definitions.camf.d_fields → qzss_dcx_camf_d11_tornado_probability: 6 entries, strategy switch
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
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D11_TORNADO_PROBABILITY_C0[] = "Non-Threatening - Threat: No discernible threat to life and property. Minimum Action: Listen for forecast changes; review tornado safety rules. Potential Impact: None expected; strong wind gusts may still occur.";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D11_TORNADO_PROBABILITY_C1[] = "Very Low - Threat: A very low threat to life and property. Minimum Action: Preparations should be made for a very low likelihood (or a 2 to 4% probability) of tornadoes; isolated tornadoes of F0 to F1 intensity possible. Potential Impact: The potential for isolated locations to experience minor to moderate tornado damage.";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D11_TORNADO_PROBABILITY_C2[] = "Low - Threat: A low threat to life and property. Minimum Action: Preparations should be made for a low likelihood (or a 5 to 14% probability) of tornadoes; scattered tornadoes of F0 to F1 intensity possible. Potential Impact: The potential for scattered locations to experience minor to moderate tornado damage.";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D11_TORNADO_PROBABILITY_C3[] = "Moderate - Threat: A moderate threat to life and property. Minimum Action: Preparations should be made for a moderate likelihood (or a 15 to 29% probability) of tornadoes; many tornadoes (even families) of F0 to F1 intensity possible. Potential Impact: The potential for many locations to experience minor to moderate tornado damage (see below). Some tornadoes may have longer damage tracks.";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D11_TORNADO_PROBABILITY_C4[] = "High - Threat: A high threat to life and property. Minimum Action: Preparations should be made for a high likelihood (or a 30 to 44% probability) of tornadoes; scattered tornadoes possible with isolated tornadoes of F2 to F5 intensity also possible. Potential Impact: The potential for isolated locations to experience major tornado damage (see below), among scattered locations of minor to moderate tornado damage. Some tornadoes may have longer damage tracks.";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D11_TORNADO_PROBABILITY_C5[] = "Extreme - Threat: An extreme threat to life and property. Minimum Action: Preparations should be made for a very high likelihood (or a 45% probability or greater) of tornadoes; many tornadoes (even families) possible with scattered tornadoes of F2 to F5 intensity also possible. Potential Impact: The potential for scattered locations to experience major tornado damage (see below), among many locations of minor to moderate tornado damage. Some tornadoes may have longer damage tracks.";
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d11_tornado_probability_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D11_TORNADO_PROBABILITY_C0), 211);
        case 1: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D11_TORNADO_PROBABILITY_C1), 323);
        case 2: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D11_TORNADO_PROBABILITY_C2), 311);
        case 3: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D11_TORNADO_PROBABILITY_C3), 391);
        case 4: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D11_TORNADO_PROBABILITY_C4), 461);
        case 5: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D11_TORNADO_PROBABILITY_C5), 486);
        default: return std::nullopt;
    }
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d11_tornado_probability_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return std::string_view{"Non-Threatening - Threat: No discernible threat to life and property. Minimum Action: Listen for forecast changes; review tornado safety rules. Potential Impact: None expected; strong wind gusts may still occur.", 211};
        case 1: return std::string_view{"Very Low - Threat: A very low threat to life and property. Minimum Action: Preparations should be made for a very low likelihood (or a 2 to 4% probability) of tornadoes; isolated tornadoes of F0 to F1 intensity possible. Potential Impact: The potential for isolated locations to experience minor to moderate tornado damage.", 323};
        case 2: return std::string_view{"Low - Threat: A low threat to life and property. Minimum Action: Preparations should be made for a low likelihood (or a 5 to 14% probability) of tornadoes; scattered tornadoes of F0 to F1 intensity possible. Potential Impact: The potential for scattered locations to experience minor to moderate tornado damage.", 311};
        case 3: return std::string_view{"Moderate - Threat: A moderate threat to life and property. Minimum Action: Preparations should be made for a moderate likelihood (or a 15 to 29% probability) of tornadoes; many tornadoes (even families) of F0 to F1 intensity possible. Potential Impact: The potential for many locations to experience minor to moderate tornado damage (see below). Some tornadoes may have longer damage tracks.", 391};
        case 4: return std::string_view{"High - Threat: A high threat to life and property. Minimum Action: Preparations should be made for a high likelihood (or a 30 to 44% probability) of tornadoes; scattered tornadoes possible with isolated tornadoes of F2 to F5 intensity also possible. Potential Impact: The potential for isolated locations to experience major tornado damage (see below), among scattered locations of minor to moderate tornado damage. Some tornadoes may have longer damage tracks.", 461};
        case 5: return std::string_view{"Extreme - Threat: An extreme threat to life and property. Minimum Action: Preparations should be made for a very high likelihood (or a 45% probability or greater) of tornadoes; many tornadoes (even families) possible with scattered tornadoes of F2 to F5 intensity also possible. Potential Impact: The potential for scattered locations to experience major tornado damage (see below), among many locations of minor to moderate tornado damage. Some tornadoes may have longer damage tracks.", 486};
        default: return std::nullopt;
    }
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d11_tornado_probability_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d11_tornado_probability_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
