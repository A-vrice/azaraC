#pragma once
// AUTO-GENERATED from azarashi 0.17.1 — do not edit
// azarashi.definitions.camf.d_fields → qzss_dcx_camf_d13_visibility: 10 entries, strategy switch
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

static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D13_VISIBILITY_C0[] = "Dense fog: visibility < 20m";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D13_VISIBILITY_C1[] = "Thick fog: 20m < visibility < 200m";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D13_VISIBILITY_C2[] = "Moderate fog: 200m < visibility < 500m";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D13_VISIBILITY_C3[] = "Light fog: 500m < visibility < 1000m";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D13_VISIBILITY_C4[] = "Thin fog: 1km < visibility < 2km";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D13_VISIBILITY_C5[] = "Haze: 2km < visibility < 4km";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D13_VISIBILITY_C6[] = "Light haze: 4km < visibility < 10km";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D13_VISIBILITY_C7[] = "Clear: 10km < visibility < 20km";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D13_VISIBILITY_C8[] = "Very clear: 20km < visibility < 50km";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D13_VISIBILITY_C9[] = "Exceptionally clear: visibility > 50km";
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d13_visibility_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D13_VISIBILITY_C0), 27);
        case 1: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D13_VISIBILITY_C1), 34);
        case 2: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D13_VISIBILITY_C2), 38);
        case 3: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D13_VISIBILITY_C3), 36);
        case 4: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D13_VISIBILITY_C4), 32);
        case 5: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D13_VISIBILITY_C5), 28);
        case 6: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D13_VISIBILITY_C6), 35);
        case 7: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D13_VISIBILITY_C7), 31);
        case 8: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D13_VISIBILITY_C8), 36);
        case 9: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D13_VISIBILITY_C9), 38);
        default: return std::nullopt;
    }
}

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d13_visibility_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d13_visibility_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
