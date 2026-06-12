#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcx_camf_a9_selection_of_library
// Variable      : qzss_dcx_camf_a9_selection_of_library
// Entries       : 2
// Strategy      : switch

#include <cstdint>
#include <optional>
#include <string_view>
#include "../azaraC.h"

namespace azaraC {
namespace def {

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_a9_selection_of_library_lookup(uint8_t id) {
    switch (id) {
        case 0: return std::string_view{"International library", 21};
        case 1: return std::string_view{"Country/region guidance library", 31};
        default: return std::nullopt;
    }
}

} // namespace def
} // namespace azaraC
