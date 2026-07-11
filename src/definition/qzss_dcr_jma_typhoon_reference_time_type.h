#pragma once
// AUTO-GENERATED from azarashi 0.16.4 with CI-CD
// Source module : qzss_dcr_jma_typhoon_reference_time_type
// Variable      : qzss_dcr_jma_typhoon_reference_time_type
// Entries       : 3
// Strategy      : switch

// NOTE: This function may return nullptr for unknown IDs.
// Callers MUST perform a null-check before using the result.

#include <cstdint>
#include <optional>
#include <string_view>
#include "../azaraC_config.h"

namespace azaraC {
namespace def {

#if (AZARAC_ENABLE_TYPHOON)

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_typhoon_reference_time_type_lookup(uint8_t id) noexcept {
    switch (id) {
        case 1: return std::string_view{"実況", 6};
        case 2: return std::string_view{"推定", 6};
        case 3: return std::string_view{"予報", 6};
        default: return std::nullopt;
    }
}

#else

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_typhoon_reference_time_type_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}

#endif

} // namespace def
} // namespace azaraC
