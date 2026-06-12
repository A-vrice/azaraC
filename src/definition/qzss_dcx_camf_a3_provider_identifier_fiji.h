#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcx_camf_a3_provider_identifier
// Variable      : qzss_dcx_camf_a3_provider_identifier_fiji
// Entries       : 5
// Strategy      : switch

#include <cstdint>
#include <optional>
#include <string_view>
#include "../azaraC.h"

namespace azaraC {
namespace def {

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_a3_provider_identifier_fiji_lookup(uint8_t id) {
    switch (id) {
        case 1: return std::string_view{"National Disaster Management Office", 35};
        case 2: return std::string_view{"Fiji Meteorological Service", 27};
        case 3: return std::string_view{"Hydrology Section, Fiji Water Authority", 39};
        case 4: return std::string_view{"Mineral Resources Department", 28};
        case 5: return std::string_view{"Fiji Broadcasting Corporation", 29};
        default: return std::nullopt;
    }
}

} // namespace def
} // namespace azaraC
