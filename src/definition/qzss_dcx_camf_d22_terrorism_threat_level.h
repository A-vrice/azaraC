#pragma once
// AUTO-GENERATED from azarashi 0.16.4 with CI-CD
// Source module : qzss_dcx_camf_b4_lower_level_fields_tables
// Variable      : qzss_dcx_camf_d22_terrorism_threat_level
// Entries       : 5
// Strategy      : switch

// NOTE: This function may return nullptr for unknown IDs.
// Callers MUST perform a null-check before using the result.

#include <cstdint>
#include <optional>
#include <string_view>
#include "../azaraC_config.h"

namespace azaraC {
namespace def {

#if (AZARAC_ENABLE_DCX_CAMF)

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d22_terrorism_threat_level_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return std::string_view{"Very low threat level. A violent act of terrorism is highly unlikely. Measures are in place to keep the population safe.", 120};
        case 1: return std::string_view{"Low threat level. A violent act of terrorism is possible but unlikely. Measures are in place to keep the population safe.", 121};
        case 2: return std::string_view{"Medium threat level. A violent act of terrorism could occur. Additional measures are in place to keep the population safe.", 122};
        case 3: return std::string_view{"High threat level. A violent act of terrorism is likely. Heightened measures are in place to keep the population safe.", 118};
        case 4: return std::string_view{"Critical threat level. A violent act of terrorism is highly likely and could occur imminently. Exceptional measures are in place to keep the population safe.", 157};
        default: return std::nullopt;
    }
}

#else

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d22_terrorism_threat_level_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}

#endif

} // namespace def
} // namespace azaraC
