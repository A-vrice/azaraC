#pragma once
// AUTO-GENERATED from azarashi 0.16.4 with CI-CD
// Source module : qzss_dcx_camf_b4_lower_level_fields_tables
// Variable      : qzss_dcx_camf_d33_biohazard_type
// Entries       : 4
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

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d33_biohazard_type_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return std::string_view{"Biological agents. These include bacteria, viruses, parasites, and fungi (such as yeasts and molds).", 100};
        case 1: return std::string_view{"Biotoxins. These refer to a group of substances with a biological origin that are toxic and poisonous to humans. Often, biotoxins are produced by plants, bacteria, insects, or certain animals, among others. Continuous exposure to these may cause, at the very least, a series of inflammatory reactions throughout the body.", 321};
        case 2: return std::string_view{"Blood and blood products. While blood isn't considered a biological hazard, it can still bring potential risks if it's contaminated or its source is in any way infected. Also, blood products such as red blood cells, white blood cells, plasma, tissues, and platelets are also hazardous if not properly handled.", 309};
        case 3: return std::string_view{"Environmental specimens. Generally, these refer to plants, soil, or water that potentially contain biological agents(include bacteria, viruses, parasites, and fungi) and biotoxins.", 180};
        default: return std::nullopt;
    }
}

#else

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d33_biohazard_type_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}

#endif

} // namespace def
} // namespace azaraC
