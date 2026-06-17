#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcr_satellite_prn
// Variable      : qzss_dcr_satellite_prn
// Entries       : 5
// Strategy      : switch

#include <cstdint>
#include <optional>
#include <string_view>
#include "../azaraC.h"

namespace azaraC {
namespace def {

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_satellite_prn_lookup(uint8_t id) {
    switch (id) {
        case 55: return std::string_view{"PRN183", 6};
        case 56: return std::string_view{"PRN184", 6};
        case 57: return std::string_view{"PRN185", 6};
        case 58: return std::string_view{"PRN186", 6};
        case 61: return std::string_view{"PRN189", 6};
        default: return std::nullopt;
    }
}

} // namespace def
} // namespace azaraC
