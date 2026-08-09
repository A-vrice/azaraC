#pragma once
// AUTO-GENERATED from azarashi 0.16.4 with CI-CD
// Source module : qzss_dcx_camf_b4_lower_level_fields_tables
// Variable      : qzss_dcx_camf_d18_drought_level
// Entries       : 4
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
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d18_drought_level_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: { static const char AZARAC_PROGMEM s[] = "D1 – Moderate Drought – PDSI = -2.0 to -2.9. Some damage to crops, pastures. Streams, reservoirs, or wells low, some water shortages developing or imminent. Voluntary water-use restrictions requested."; return azarac_pgm_view(s, 204); }
        case 1: { static const char AZARAC_PROGMEM s[] = "D2 – Severe Drought – PDSI = -3.0 to -3.9. Crop or pasture losses likely. Water shortages common. Water restrictions imposed."; return azarac_pgm_view(s, 129); }
        case 2: { static const char AZARAC_PROGMEM s[] = "D3 – Extreme Drought – PDSI = -4.0 to -4.9. Major crop/pasture losses. Widespread water shortages or restrictions."; return azarac_pgm_view(s, 118); }
        case 3: { static const char AZARAC_PROGMEM s[] = "D4 – Exceptional Drought – PDSI = -5.0 or less. Exceptional and widespread crop/pasture losses. Shortages of water in reservoirs, streams, and wells creating water emergencies."; return azarac_pgm_view(s, 180); }
        default: return std::nullopt;
    }
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d18_drought_level_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return std::string_view{"D1 – Moderate Drought – PDSI = -2.0 to -2.9. Some damage to crops, pastures. Streams, reservoirs, or wells low, some water shortages developing or imminent. Voluntary water-use restrictions requested.", 204};
        case 1: return std::string_view{"D2 – Severe Drought – PDSI = -3.0 to -3.9. Crop or pasture losses likely. Water shortages common. Water restrictions imposed.", 129};
        case 2: return std::string_view{"D3 – Extreme Drought – PDSI = -4.0 to -4.9. Major crop/pasture losses. Widespread water shortages or restrictions.", 118};
        case 3: return std::string_view{"D4 – Exceptional Drought – PDSI = -5.0 or less. Exceptional and widespread crop/pasture losses. Shortages of water in reservoirs, streams, and wells creating water emergencies.", 180};
        default: return std::nullopt;
    }
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d18_drought_level_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d18_drought_level_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
