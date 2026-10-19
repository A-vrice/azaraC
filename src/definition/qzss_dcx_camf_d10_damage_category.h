#pragma once
// AUTO-GENERATED from azarashi 0.17.1 — do not edit
// azarashi.definitions.camf.d_fields → qzss_dcx_camf_d10_damage_category: 6 entries, strategy switch
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
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D10_DAMAGE_CATEGORY_C0[] = "1 - Very dangerous winds will produce some damage. Scale 1 and Intensity 1";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D10_DAMAGE_CATEGORY_C1[] = "2 - Extremely dangerous winds will cause extensive damage. Scale 1 and Intensity 2";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D10_DAMAGE_CATEGORY_C2[] = "3 - Devastating damage will occur. Scale 1 and Intensity 3";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D10_DAMAGE_CATEGORY_C3[] = "4 - Catastrophic damage will occur. Scale 2 and Intensity 1";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D10_DAMAGE_CATEGORY_C4[] = "5 - Catastrophic damage will occur. Scale 2 and Intensity 2";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D10_DAMAGE_CATEGORY_C5[] = "5 - Catastrophic damage will occur. Scale 3 and Intensity 3";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D10_DAMAGE_CATEGORY_PARENT_POOL[] = "Category \000";
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d10_damage_category_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D10_DAMAGE_CATEGORY_PARENT_POOL) + 0u, AZARAC_PGM_PTR(QZSS_DCX_CAMF_D10_DAMAGE_CATEGORY_C0));
        case 1: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D10_DAMAGE_CATEGORY_PARENT_POOL) + 0u, AZARAC_PGM_PTR(QZSS_DCX_CAMF_D10_DAMAGE_CATEGORY_C1));
        case 2: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D10_DAMAGE_CATEGORY_PARENT_POOL) + 0u, AZARAC_PGM_PTR(QZSS_DCX_CAMF_D10_DAMAGE_CATEGORY_C2));
        case 3: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D10_DAMAGE_CATEGORY_PARENT_POOL) + 0u, AZARAC_PGM_PTR(QZSS_DCX_CAMF_D10_DAMAGE_CATEGORY_C3));
        case 4: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D10_DAMAGE_CATEGORY_PARENT_POOL) + 0u, AZARAC_PGM_PTR(QZSS_DCX_CAMF_D10_DAMAGE_CATEGORY_C4));
        case 5: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D10_DAMAGE_CATEGORY_PARENT_POOL) + 0u, AZARAC_PGM_PTR(QZSS_DCX_CAMF_D10_DAMAGE_CATEGORY_C5));
        default: return std::nullopt;
    }
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d10_damage_category_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return std::string_view{"Category 1 - Very dangerous winds will produce some damage. Scale 1 and Intensity 1", 83};
        case 1: return std::string_view{"Category 2 - Extremely dangerous winds will cause extensive damage. Scale 1 and Intensity 2", 91};
        case 2: return std::string_view{"Category 3 - Devastating damage will occur. Scale 1 and Intensity 3", 67};
        case 3: return std::string_view{"Category 4 - Catastrophic damage will occur. Scale 2 and Intensity 1", 68};
        case 4: return std::string_view{"Category 5 - Catastrophic damage will occur. Scale 2 and Intensity 2", 68};
        case 5: return std::string_view{"Category 5 - Catastrophic damage will occur. Scale 3 and Intensity 3", 68};
        default: return std::nullopt;
    }
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d10_damage_category_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d10_damage_category_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
