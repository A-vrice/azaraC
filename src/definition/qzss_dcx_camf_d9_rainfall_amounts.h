#pragma once
// AUTO-GENERATED from azarashi 0.17.1 — do not edit
// azarashi.definitions.camf.d_fields → qzss_dcx_camf_d9_rainfall_amounts: 8 entries, strategy switch
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
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D9_RAINFALL_AMOUNTS_C0[] = "p ≤ 2.5";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D9_RAINFALL_AMOUNTS_C1[] = "2.5mm/h < p ≤ 7.5";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D9_RAINFALL_AMOUNTS_C2[] = "7.5mm/h < p ≤ 1";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D9_RAINFALL_AMOUNTS_C3[] = "10mm/h < p ≤ 2";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D9_RAINFALL_AMOUNTS_C4[] = "20mm/h < p ≤ 3";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D9_RAINFALL_AMOUNTS_C5[] = "30mm/h < p ≤ 5";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D9_RAINFALL_AMOUNTS_C6[] = "50mm/h < p ≤ 8";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D9_RAINFALL_AMOUNTS_C7[] = "80mm/h < p";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D9_RAINFALL_AMOUNTS_PARENT_POOL[] = "0mm/h\000mm/h\000";
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d9_rainfall_amounts_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D9_RAINFALL_AMOUNTS_C0), AZARAC_PGM_PTR(QZSS_DCX_CAMF_D9_RAINFALL_AMOUNTS_PARENT_POOL) + 6u);
        case 1: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D9_RAINFALL_AMOUNTS_C1), AZARAC_PGM_PTR(QZSS_DCX_CAMF_D9_RAINFALL_AMOUNTS_PARENT_POOL) + 6u);
        case 2: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D9_RAINFALL_AMOUNTS_C2), AZARAC_PGM_PTR(QZSS_DCX_CAMF_D9_RAINFALL_AMOUNTS_PARENT_POOL) + 0u);
        case 3: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D9_RAINFALL_AMOUNTS_C3), AZARAC_PGM_PTR(QZSS_DCX_CAMF_D9_RAINFALL_AMOUNTS_PARENT_POOL) + 0u);
        case 4: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D9_RAINFALL_AMOUNTS_C4), AZARAC_PGM_PTR(QZSS_DCX_CAMF_D9_RAINFALL_AMOUNTS_PARENT_POOL) + 0u);
        case 5: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D9_RAINFALL_AMOUNTS_C5), AZARAC_PGM_PTR(QZSS_DCX_CAMF_D9_RAINFALL_AMOUNTS_PARENT_POOL) + 0u);
        case 6: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D9_RAINFALL_AMOUNTS_C6), AZARAC_PGM_PTR(QZSS_DCX_CAMF_D9_RAINFALL_AMOUNTS_PARENT_POOL) + 0u);
        case 7: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D9_RAINFALL_AMOUNTS_C7), 10);
        default: return std::nullopt;
    }
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d9_rainfall_amounts_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return std::string_view{"p ≤ 2.5mm/h", 13};
        case 1: return std::string_view{"2.5mm/h < p ≤ 7.5mm/h", 23};
        case 2: return std::string_view{"7.5mm/h < p ≤ 10mm/h", 22};
        case 3: return std::string_view{"10mm/h < p ≤ 20mm/h", 21};
        case 4: return std::string_view{"20mm/h < p ≤ 30mm/h", 21};
        case 5: return std::string_view{"30mm/h < p ≤ 50mm/h", 21};
        case 6: return std::string_view{"50mm/h < p ≤ 80mm/h", 21};
        case 7: return std::string_view{"80mm/h < p", 10};
        default: return std::nullopt;
    }
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d9_rainfall_amounts_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d9_rainfall_amounts_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
