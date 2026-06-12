#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : ublox_qzss_svid_prn_map
// Variable      : ublox_qzss_svid_prn_map
// Entries       : 4
// Strategy      : switch

#include <cstdint>
#include <optional>
#include <string_view>
#include "../azaraC.h"

namespace azaraC {
namespace def {

[[nodiscard]] inline constexpr std::optional<std::string_view> ublox_qzss_svid_prn_map_lookup(uint8_t id) {
    switch (id) {
        case 2: return std::string_view{"184", 3};
        case 3: return std::string_view{"185", 3};
        case 4: return std::string_view{"186", 3};
        case 7: return std::string_view{"189", 3};
        default: return std::nullopt;
    }
}

} // namespace def
} // namespace azaraC
