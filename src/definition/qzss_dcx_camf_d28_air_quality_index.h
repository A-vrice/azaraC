#pragma once
// AUTO-GENERATED from azarashi 0.17.1 — do not edit
// azarashi.definitions.camf.d_fields → qzss_dcx_camf_d28_air_quality_index: 6 entries, strategy switch
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
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D28_AIR_QUALITY_INDEX_C0[] = "value 0 - 50. Good. Green. Advisory: None.";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D28_AIR_QUALITY_INDEX_C1[] = "value 51 - 100. Moderate. Yellow. Unusually sensitive individuals should consider limiting prolonged outdoor exertion.";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D28_AIR_QUALITY_INDEX_C2[] = "101 - 150. Unhealthy for sensitive groups. Orange. Children, active adults and people with respiratory disease, such as asthma, should limit prolonged outdoor exertion";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D28_AIR_QUALITY_INDEX_C3[] = "151 - 200. Unhealthy. Red. Children, active adults and people with respiratory disease, such as asthma, should limit prolonged outdoor exertion. Everyone else should limit prolonged outdoor exertion.";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D28_AIR_QUALITY_INDEX_C4[] = "201 - 300. Very unhealthy. Purple. Children, active adults and people with respiratory disease, such as asthma, should limit prolonged outdoor exertion. Everyone else should limit outdoor exertion.";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D28_AIR_QUALITY_INDEX_C5[] = "301 - 500. Hazardous. Brown. Everyone should avoid all physical activity outdoors.";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D28_AIR_QUALITY_INDEX_PARENT_POOL[] = "Index \000";
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d28_air_quality_index_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D28_AIR_QUALITY_INDEX_PARENT_POOL) + 0u, AZARAC_PGM_PTR(QZSS_DCX_CAMF_D28_AIR_QUALITY_INDEX_C0));
        case 1: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D28_AIR_QUALITY_INDEX_PARENT_POOL) + 0u, AZARAC_PGM_PTR(QZSS_DCX_CAMF_D28_AIR_QUALITY_INDEX_C1));
        case 2: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D28_AIR_QUALITY_INDEX_PARENT_POOL) + 0u, AZARAC_PGM_PTR(QZSS_DCX_CAMF_D28_AIR_QUALITY_INDEX_C2));
        case 3: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D28_AIR_QUALITY_INDEX_PARENT_POOL) + 0u, AZARAC_PGM_PTR(QZSS_DCX_CAMF_D28_AIR_QUALITY_INDEX_C3));
        case 4: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D28_AIR_QUALITY_INDEX_PARENT_POOL) + 0u, AZARAC_PGM_PTR(QZSS_DCX_CAMF_D28_AIR_QUALITY_INDEX_C4));
        case 5: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D28_AIR_QUALITY_INDEX_PARENT_POOL) + 0u, AZARAC_PGM_PTR(QZSS_DCX_CAMF_D28_AIR_QUALITY_INDEX_C5));
        default: return std::nullopt;
    }
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d28_air_quality_index_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return std::string_view{"Index value 0 - 50. Good. Green. Advisory: None.", 48};
        case 1: return std::string_view{"Index value 51 - 100. Moderate. Yellow. Unusually sensitive individuals should consider limiting prolonged outdoor exertion.", 124};
        case 2: return std::string_view{"Index 101 - 150. Unhealthy for sensitive groups. Orange. Children, active adults and people with respiratory disease, such as asthma, should limit prolonged outdoor exertion", 173};
        case 3: return std::string_view{"Index 151 - 200. Unhealthy. Red. Children, active adults and people with respiratory disease, such as asthma, should limit prolonged outdoor exertion. Everyone else should limit prolonged outdoor exertion.", 205};
        case 4: return std::string_view{"Index 201 - 300. Very unhealthy. Purple. Children, active adults and people with respiratory disease, such as asthma, should limit prolonged outdoor exertion. Everyone else should limit outdoor exertion.", 203};
        case 5: return std::string_view{"Index 301 - 500. Hazardous. Brown. Everyone should avoid all physical activity outdoors.", 88};
        default: return std::nullopt;
    }
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d28_air_quality_index_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d28_air_quality_index_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
