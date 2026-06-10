#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcr_jma_tsunamigenic_potential
// Variable      : qzss_dcr_jma_tsunamigenic_potential_en
// Entries       : 6
// Strategy      : switch

#include <cstdint>
#include <optional>
#include <string_view>

namespace azaraC {
namespace def {

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_tsunamigenic_potential_en_lookup(uint8_t id) {
    switch (id) {
        case 0: return std::string_view{"There is No Possibility of a Tsunami", 36};
        case 1: return std::string_view{"There is a Possibility of a Destructive Ocean-Wide Tsunami", 58};
        case 2: return std::string_view{"There is a Possibility of a Destructive Regional Tsunami", 56};
        case 3: return std::string_view{"There is a Possibility of a Destructive Local Tsunami Near the Epicenter", 72};
        case 4: return std::string_view{"There is a Very Small Possibility of a Destructive Local Tsunami", 64};
        case 7: return std::string_view{"There is a Possibility of a Tsunami", 35};
        default: return std::nullopt;
    }
}

} // namespace def
} // namespace azaraC
