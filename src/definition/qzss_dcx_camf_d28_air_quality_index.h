#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcx_camf_b4_lower_level_fields_tables
// Variable      : qzss_dcx_camf_d28_air_quality_index
// Entries       : 6
// Strategy      : switch

// NOTE: This function may return nullptr for unknown IDs.
// Callers MUST perform a null-check before using the result.

#include <cstdint>
#include <optional>
#include <string_view>
#include "../azaraC.h"

namespace azaraC {
namespace def {

#if (AZARAC_ENABLE_DCX_CAMF)

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

#else

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d28_air_quality_index_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}

#endif

} // namespace def
} // namespace azaraC
