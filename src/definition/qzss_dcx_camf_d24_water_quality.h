#pragma once
// AUTO-GENERATED from azarashi 0.17.1 — do not edit
// azarashi.definitions.camf.d_fields → qzss_dcx_camf_d24_water_quality: 6 entries, strategy switch
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
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D24_WATER_QUALITY_C0[] = "Excellent";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D24_WATER_QUALITY_C1[] = "Good";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D24_WATER_QUALITY_C2[] = "Poor";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D24_WATER_QUALITY_C3[] = "Very poor";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D24_WATER_QUALITY_C4[] = "Suitable for drinking purposes";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D24_WATER_QUALITY_C5[] = "Unsuitable for drinking purposes";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D24_WATER_QUALITY_PARENT_POOL[] = " water quality\000";
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d24_water_quality_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D24_WATER_QUALITY_C0), AZARAC_PGM_PTR(QZSS_DCX_CAMF_D24_WATER_QUALITY_PARENT_POOL) + 0u);
        case 1: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D24_WATER_QUALITY_C1), AZARAC_PGM_PTR(QZSS_DCX_CAMF_D24_WATER_QUALITY_PARENT_POOL) + 0u);
        case 2: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D24_WATER_QUALITY_C2), AZARAC_PGM_PTR(QZSS_DCX_CAMF_D24_WATER_QUALITY_PARENT_POOL) + 0u);
        case 3: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D24_WATER_QUALITY_C3), AZARAC_PGM_PTR(QZSS_DCX_CAMF_D24_WATER_QUALITY_PARENT_POOL) + 0u);
        case 4: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D24_WATER_QUALITY_C4), 30);
        case 5: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D24_WATER_QUALITY_C5), 32);
        default: return std::nullopt;
    }
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d24_water_quality_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return std::string_view{"Excellent water quality", 23};
        case 1: return std::string_view{"Good water quality", 18};
        case 2: return std::string_view{"Poor water quality", 18};
        case 3: return std::string_view{"Very poor water quality", 23};
        case 4: return std::string_view{"Suitable for drinking purposes", 30};
        case 5: return std::string_view{"Unsuitable for drinking purposes", 32};
        default: return std::nullopt;
    }
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d24_water_quality_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d24_water_quality_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
