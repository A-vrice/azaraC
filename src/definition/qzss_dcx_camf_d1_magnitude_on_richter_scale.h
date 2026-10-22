#pragma once
// AUTO-GENERATED from azarashi 0.17.1 — do not edit
// azarashi.definitions.camf.d_fields → qzss_dcx_camf_d1_magnitude_on_richter_scale: 9 entries, strategy switch
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
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D1_MAGNITUDE_ON_RICHTER_SCALE_C0[] = "1.0-1.9 - Micro";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D1_MAGNITUDE_ON_RICHTER_SCALE_C1[] = "2.0-2.9 - Minor";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D1_MAGNITUDE_ON_RICHTER_SCALE_C2[] = "3.0-3.9 - Minor";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D1_MAGNITUDE_ON_RICHTER_SCALE_C3[] = "4.0-4.9 - Light";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D1_MAGNITUDE_ON_RICHTER_SCALE_C4[] = "5.0-5.9 - Moderate";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D1_MAGNITUDE_ON_RICHTER_SCALE_C5[] = "6.0-6.9 - Strong";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D1_MAGNITUDE_ON_RICHTER_SCALE_C6[] = "7.0-7.9 - Major";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D1_MAGNITUDE_ON_RICHTER_SCALE_C7[] = "8.0-8.9 - Great";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D1_MAGNITUDE_ON_RICHTER_SCALE_C8[] = "9.0 and greater - Great";
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d1_magnitude_on_richter_scale_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D1_MAGNITUDE_ON_RICHTER_SCALE_C0), 15);
        case 1: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D1_MAGNITUDE_ON_RICHTER_SCALE_C1), 15);
        case 2: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D1_MAGNITUDE_ON_RICHTER_SCALE_C2), 15);
        case 3: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D1_MAGNITUDE_ON_RICHTER_SCALE_C3), 15);
        case 4: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D1_MAGNITUDE_ON_RICHTER_SCALE_C4), 18);
        case 5: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D1_MAGNITUDE_ON_RICHTER_SCALE_C5), 16);
        case 6: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D1_MAGNITUDE_ON_RICHTER_SCALE_C6), 15);
        case 7: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D1_MAGNITUDE_ON_RICHTER_SCALE_C7), 15);
        case 8: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D1_MAGNITUDE_ON_RICHTER_SCALE_C8), 23);
        default: return std::nullopt;
    }
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d1_magnitude_on_richter_scale_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return std::string_view{"1.0-1.9 - Micro", 15};
        case 1: return std::string_view{"2.0-2.9 - Minor", 15};
        case 2: return std::string_view{"3.0-3.9 - Minor", 15};
        case 3: return std::string_view{"4.0-4.9 - Light", 15};
        case 4: return std::string_view{"5.0-5.9 - Moderate", 18};
        case 5: return std::string_view{"6.0-6.9 - Strong", 16};
        case 6: return std::string_view{"7.0-7.9 - Major", 15};
        case 7: return std::string_view{"8.0-8.9 - Great", 15};
        case 8: return std::string_view{"9.0 and greater - Great", 23};
        default: return std::nullopt;
    }
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d1_magnitude_on_richter_scale_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d1_magnitude_on_richter_scale_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
