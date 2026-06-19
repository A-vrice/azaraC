#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcx_camf_b4_lower_level_fields_tables
// Variable      : qzss_dcx_camf_d19_avalanche_warning_level
// Entries       : 5
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

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d19_avalanche_warning_level_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return std::string_view{"1 – Low. Generally stable conditions. Triggering is generally possible only from high additional loads in isolated areas of very steep, extreme terrain. Only small and medium natural avalanches are possible.", 207};
        case 1: return std::string_view{"2 – Moderate. Heightened avalanche conditions on specific terrain features. Triggering is possible, primarily from high additional loads, particularly on the indicated steep slopes. Very large natural avalanches are unlikely.", 225};
        case 2: return std::string_view{"3 – Considerable. Dangerous avalanche conditions Triggering is possible, even from low additional loads, particularly on the indicated steep slopes. In certain situations, some large, and in isolated cases very large natural avalanches are possible.", 249};
        case 3: return std::string_view{"4 – High. Very dangerous avalanche conditions. Triggering is likely, even from low additional loads, on many steep slopes. In some cases, numerous large and often very large natural avalanches can be expected.", 209};
        case 4: return std::string_view{"5 – Very high. Extraordinary avalanche conditions. Numerous very large and often extremely large natural avalanches can be expected, even in moderately steep terrain.", 166};
        default: return std::nullopt;
    }
}

#else

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d19_avalanche_warning_level_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}

#endif

} // namespace def
} // namespace azaraC
