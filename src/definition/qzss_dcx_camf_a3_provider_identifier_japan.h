#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcx_camf_a3_provider_identifier
// Variable      : qzss_dcx_camf_a3_provider_identifier_japan
// Entries       : 4
// Strategy      : switch

#include <cstdint>
#include <optional>
#include <string_view>

namespace azaraC {
namespace def {

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_a3_provider_identifier_japan_lookup(uint8_t id) {
    switch (id) {
        case 1: return std::string_view{"Foundation for MultiMedia Communications", 40};
        case 2: return std::string_view{"Fire and Disaster Management Agency", 35};
        case 3: return std::string_view{"Related Ministries", 18};
        case 4: return std::string_view{"Local Government", 16};
        default: return std::nullopt;
    }
}

} // namespace def
} // namespace azaraC
