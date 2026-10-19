#pragma once
// AUTO-GENERATED from azarashi 0.17.1 — do not edit
// azarashi.definitions.camf.d_fields → qzss_dcx_camf_d2_seismic_coefficient: 8 entries, strategy switch
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
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D2_SEISMIC_COEFFICIENT_C0[] = "2";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D2_SEISMIC_COEFFICIENT_C1[] = "3";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D2_SEISMIC_COEFFICIENT_C2[] = "4";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D2_SEISMIC_COEFFICIENT_C3[] = "5 weak";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D2_SEISMIC_COEFFICIENT_C4[] = "5 strong";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D2_SEISMIC_COEFFICIENT_C5[] = "6 weak";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D2_SEISMIC_COEFFICIENT_C6[] = "6 strong";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D2_SEISMIC_COEFFICIENT_C7[] = "7";
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d2_seismic_coefficient_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D2_SEISMIC_COEFFICIENT_C0), 1);
        case 1: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D2_SEISMIC_COEFFICIENT_C1), 1);
        case 2: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D2_SEISMIC_COEFFICIENT_C2), 1);
        case 3: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D2_SEISMIC_COEFFICIENT_C3), 6);
        case 4: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D2_SEISMIC_COEFFICIENT_C4), 8);
        case 5: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D2_SEISMIC_COEFFICIENT_C5), 6);
        case 6: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D2_SEISMIC_COEFFICIENT_C6), 8);
        case 7: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D2_SEISMIC_COEFFICIENT_C7), 1);
        default: return std::nullopt;
    }
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d2_seismic_coefficient_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return std::string_view{"2", 1};
        case 1: return std::string_view{"3", 1};
        case 2: return std::string_view{"4", 1};
        case 3: return std::string_view{"5 weak", 6};
        case 4: return std::string_view{"5 strong", 8};
        case 5: return std::string_view{"6 weak", 6};
        case 6: return std::string_view{"6 strong", 8};
        case 7: return std::string_view{"7", 1};
        default: return std::nullopt;
    }
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d2_seismic_coefficient_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d2_seismic_coefficient_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
