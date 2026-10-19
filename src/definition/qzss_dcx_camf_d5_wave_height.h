#pragma once
// AUTO-GENERATED from azarashi 0.17.1 — do not edit
// azarashi.definitions.camf.d_fields → qzss_dcx_camf_d5_wave_height: 8 entries, strategy switch
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
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D5_WAVE_HEIGHT_C0[] = "H ≤ 0.5m";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D5_WAVE_HEIGHT_C1[] = "0.5m < H ≤ 1.0m";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D5_WAVE_HEIGHT_C2[] = "1.0m < H ≤ 1.5m";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D5_WAVE_HEIGHT_C3[] = "1.5m < H ≤ 2.0m";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D5_WAVE_HEIGHT_C4[] = "2.0m < H ≤ 3.0m";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D5_WAVE_HEIGHT_C5[] = "3.0m < H ≤ 5.0m";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D5_WAVE_HEIGHT_C6[] = "5.0m < H ≤ 10.0m";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D5_WAVE_HEIGHT_C7[] = "H > 10.0m";
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d5_wave_height_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D5_WAVE_HEIGHT_C0), 10);
        case 1: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D5_WAVE_HEIGHT_C1), 17);
        case 2: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D5_WAVE_HEIGHT_C2), 17);
        case 3: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D5_WAVE_HEIGHT_C3), 17);
        case 4: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D5_WAVE_HEIGHT_C4), 17);
        case 5: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D5_WAVE_HEIGHT_C5), 17);
        case 6: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D5_WAVE_HEIGHT_C6), 18);
        case 7: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D5_WAVE_HEIGHT_C7), 9);
        default: return std::nullopt;
    }
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d5_wave_height_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return std::string_view{"H ≤ 0.5m", 10};
        case 1: return std::string_view{"0.5m < H ≤ 1.0m", 17};
        case 2: return std::string_view{"1.0m < H ≤ 1.5m", 17};
        case 3: return std::string_view{"1.5m < H ≤ 2.0m", 17};
        case 4: return std::string_view{"2.0m < H ≤ 3.0m", 17};
        case 5: return std::string_view{"3.0m < H ≤ 5.0m", 17};
        case 6: return std::string_view{"5.0m < H ≤ 10.0m", 18};
        case 7: return std::string_view{"H > 10.0m", 9};
        default: return std::nullopt;
    }
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d5_wave_height_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d5_wave_height_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
