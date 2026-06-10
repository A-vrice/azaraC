#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcx_camf_b4_lower_level_fields_tables
// Variable      : qzss_dcx_camf_d34_explosive_hazard_type
// Entries       : 4
// Strategy      : switch

#include <cstdint>
#include <optional>
#include <string_view>

namespace azaraC {
namespace def {

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d34_explosive_hazard_type_lookup(uint8_t id) {
    switch (id) {
        case 0: return std::string_view{"PE1 - Mass explosion hazard in which the entire body of explosives explodes as one.", 83};
        case 1: return std::string_view{"PE2 - Serious projectile hazard but does not have a mass explosion hazard.", 74};
        case 2: return std::string_view{"PE3 - Fire hazard and either a minor blast hazard or a minor projection hazard, or both, but does not have a mass explosion hazard. Explosives which give rise to considerable radiant heat or which burn to produce a minor blast or projection hazard.", 248};
        case 3: return std::string_view{"PE4 - Fire or slight explosion hazard, or both, with only local effect. Explosives which present only a low hazard in the event of ignition or initiation, where no significant blast or projection of fragments of appreciable size or range is expected.", 250};
        default: return std::nullopt;
    }
}

} // namespace def
} // namespace azaraC
