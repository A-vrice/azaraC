#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcx_camf_a17_main_subject_for_specific_settings
// Variable      : qzss_dcx_camf_a17_main_subject_for_specific_settings
// Entries       : 4
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

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_a17_main_subject_for_specific_settings_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return std::string_view{"B1 - Improved Resolution of Main Ellipse", 40};
        case 1: return std::string_view{"B2 - Position of the Centre of the Hazard", 41};
        case 2: return std::string_view{"B3 - Secondary Ellipse Definition", 33};
        case 3: return std::string_view{"B4 - Quantitative and detailed information about the Hazard", 59};
        default: return std::nullopt;
    }
}

#else

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_a17_main_subject_for_specific_settings_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}

#endif

} // namespace def
} // namespace azaraC
