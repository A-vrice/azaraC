#pragma once
// AUTO-GENERATED from azarashi 0.17.1 with CI-CD
// Source module : azarashi.definitions.camf.d_fields
// Variable      : qzss_dcx_camf_d28_air_quality_index
// Entries       : 6
// Strategy      : switch

// NOTE: This function may return nullptr for unknown IDs.
// Callers MUST perform a null-check before using the result.

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
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D28_AIR_QUALITY_INDEX_PARENT_POOL[] = "Index \000";
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d28_air_quality_index_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: { static const char AZARAC_PROGMEM s[] = "value 0 - 50. Good. Green. Advisory: None."; return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D28_AIR_QUALITY_INDEX_PARENT_POOL) + 0u, AZARAC_PGM_PTR(s)); }
        case 1: { static const char AZARAC_PROGMEM s[] = "value 51 - 100. Moderate. Yellow. Unusually sensitive individuals should consider limiting prolonged outdoor exertion."; return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D28_AIR_QUALITY_INDEX_PARENT_POOL) + 0u, AZARAC_PGM_PTR(s)); }
        case 2: { static const char AZARAC_PROGMEM s[] = "101 - 150. Unhealthy for sensitive groups. Orange. Children, active adults and people with respiratory disease, such as asthma, should limit prolonged outdoor exertion"; return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D28_AIR_QUALITY_INDEX_PARENT_POOL) + 0u, AZARAC_PGM_PTR(s)); }
        case 3: { static const char AZARAC_PROGMEM s[] = "151 - 200. Unhealthy. Red. Children, active adults and people with respiratory disease, such as asthma, should limit prolonged outdoor exertion. Everyone else should limit prolonged outdoor exertion."; return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D28_AIR_QUALITY_INDEX_PARENT_POOL) + 0u, AZARAC_PGM_PTR(s)); }
        case 4: { static const char AZARAC_PROGMEM s[] = "201 - 300. Very unhealthy. Purple. Children, active adults and people with respiratory disease, such as asthma, should limit prolonged outdoor exertion. Everyone else should limit outdoor exertion."; return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D28_AIR_QUALITY_INDEX_PARENT_POOL) + 0u, AZARAC_PGM_PTR(s)); }
        case 5: { static const char AZARAC_PROGMEM s[] = "301 - 500. Hazardous. Brown. Everyone should avoid all physical activity outdoors."; return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D28_AIR_QUALITY_INDEX_PARENT_POOL) + 0u, AZARAC_PGM_PTR(s)); }
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
