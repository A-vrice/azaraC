#pragma once
// AUTO-GENERATED from azarashi 0.16.4 with CI-CD
// Source module : qzss_dcx_camf_b4_lower_level_fields_tables
// Variable      : qzss_dcx_camf_d34_explosive_hazard_type
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
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d34_explosive_hazard_type_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: { static const char AZARAC_PROGMEM s[] = "PE1 - Mass explosion hazard in which the entire body of explosives explodes as one."; return azarac_pgm_view(s, 83); }
        case 1: { static const char AZARAC_PROGMEM s[] = "PE2 - Serious projectile hazard but does not have a mass explosion hazard."; return azarac_pgm_view(s, 74); }
        case 2: { static const char AZARAC_PROGMEM s[] = "PE3 - Fire hazard and either a minor blast hazard or a minor projection hazard, or both, but does not have a mass explosion hazard. Explosives which give rise to considerable radiant heat or which burn to produce a minor blast or projection hazard."; return azarac_pgm_view(s, 248); }
        case 3: { static const char AZARAC_PROGMEM s[] = "PE4 - Fire or slight explosion hazard, or both, with only local effect. Explosives which present only a low hazard in the event of ignition or initiation, where no significant blast or projection of fragments of appreciable size or range is expected."; return azarac_pgm_view(s, 250); }
        default: return std::nullopt;
    }
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d34_explosive_hazard_type_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return std::string_view{"PE1 - Mass explosion hazard in which the entire body of explosives explodes as one.", 83};
        case 1: return std::string_view{"PE2 - Serious projectile hazard but does not have a mass explosion hazard.", 74};
        case 2: return std::string_view{"PE3 - Fire hazard and either a minor blast hazard or a minor projection hazard, or both, but does not have a mass explosion hazard. Explosives which give rise to considerable radiant heat or which burn to produce a minor blast or projection hazard.", 248};
        case 3: return std::string_view{"PE4 - Fire or slight explosion hazard, or both, with only local effect. Explosives which present only a low hazard in the event of ignition or initiation, where no significant blast or projection of fragments of appreciable size or range is expected.", 250};
        default: return std::nullopt;
    }
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d34_explosive_hazard_type_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d34_explosive_hazard_type_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
