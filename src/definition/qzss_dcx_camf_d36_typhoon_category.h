#pragma once
// AUTO-GENERATED from azarashi 0.17.1 — do not edit
// azarashi.definitions.camf.d_fields → qzss_dcx_camf_d36_typhoon_category: 5 entries, strategy switch
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
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D36_TYPHOON_CATEGORY_C0[] = "1 and Intensity 1";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D36_TYPHOON_CATEGORY_C1[] = "1 and Intensity 2";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D36_TYPHOON_CATEGORY_C2[] = "1 and Intensity 3";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D36_TYPHOON_CATEGORY_C3[] = "2 and Intensity 1";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D36_TYPHOON_CATEGORY_C4[] = "2 and Intensity 2";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D36_TYPHOON_CATEGORY_PARENT_POOL[] = "Scale \000";
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d36_typhoon_category_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D36_TYPHOON_CATEGORY_PARENT_POOL) + 0u, AZARAC_PGM_PTR(QZSS_DCX_CAMF_D36_TYPHOON_CATEGORY_C0));
        case 1: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D36_TYPHOON_CATEGORY_PARENT_POOL) + 0u, AZARAC_PGM_PTR(QZSS_DCX_CAMF_D36_TYPHOON_CATEGORY_C1));
        case 2: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D36_TYPHOON_CATEGORY_PARENT_POOL) + 0u, AZARAC_PGM_PTR(QZSS_DCX_CAMF_D36_TYPHOON_CATEGORY_C2));
        case 3: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D36_TYPHOON_CATEGORY_PARENT_POOL) + 0u, AZARAC_PGM_PTR(QZSS_DCX_CAMF_D36_TYPHOON_CATEGORY_C3));
        case 4: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D36_TYPHOON_CATEGORY_PARENT_POOL) + 0u, AZARAC_PGM_PTR(QZSS_DCX_CAMF_D36_TYPHOON_CATEGORY_C4));
        default: return std::nullopt;
    }
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d36_typhoon_category_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return std::string_view{"Scale 1 and Intensity 1", 23};
        case 1: return std::string_view{"Scale 1 and Intensity 2", 23};
        case 2: return std::string_view{"Scale 1 and Intensity 3", 23};
        case 3: return std::string_view{"Scale 2 and Intensity 1", 23};
        case 4: return std::string_view{"Scale 2 and Intensity 2", 23};
        default: return std::nullopt;
    }
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d36_typhoon_category_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d36_typhoon_category_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
