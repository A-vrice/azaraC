#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcx_camf_b4_lower_level_fields_tables
// Variable      : qzss_dcx_camf_d17_fog_level
// Entries       : 5
// Strategy      : switch

#include <cstdint>
#include <optional>
#include <string_view>
#include "../azaraC.h"

namespace azaraC {
namespace def {

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d17_fog_level_lookup(uint8_t id) {
    switch (id) {
        case 0: return std::string_view{"Level 1 of 5: Slight fog or Mist. On land, object appear hazy or blurry. Road and rail traffic are unhindered. On sea, horizon cannot be seen. Lights and landmarks can be seen at working distances.", 197};
        case 1: return std::string_view{"Level 2 of 5: Slight fog. On land, railroad traffic takes additional caution. On sea, Lights on passing vessel are generally not distinct at distances under 1 mile. Fog signals are sounded.", 189};
        case 2: return std::string_view{"Level 3 of 5: Moderate fog. On land, rail and road traffic is obstructed. On sea, Lights on passing vessels are generally not distinct at distances under 1 mile. Fog signals are sounded. On river, navigation is unhindered but extra caution is required.", 252};
        case 3: return std::string_view{"Level 4 of 5: Moderate fog. On land, rail and road traffic impeded. On sea, lights on ships and other vessels cannot be seen at distances of 4 miles or less. On river, navigation is suspended.", 192};
        case 4: return std::string_view{"Level 5 of 5: Thick fog. On land, all traffic is impeded and totally disorganised. On sea, lights on ships and other vessels cannot be seen at distances of 4 miles or less. On river, navigation is suspended.", 207};
        default: return std::nullopt;
    }
}

} // namespace def
} // namespace azaraC
