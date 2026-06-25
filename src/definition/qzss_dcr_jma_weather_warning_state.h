#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcr_jma_weather_warning_state
// Variable      : qzss_dcr_jma_weather_warning_state
// Entries       : 2
// Strategy      : switch

// NOTE: This function may return nullptr for unknown IDs.
// Callers MUST perform a null-check before using the result.

#include <cstdint>
#include <optional>
#include <string_view>
#include "../azaraC.h"

namespace azaraC {
namespace def {

#if (AZARAC_ENABLE_WEATHER)

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_weather_warning_state_lookup(uint8_t id) noexcept {
    switch (id) {
        case 1: return std::string_view{"発表", 6};
        case 2: return std::string_view{"解除", 6};
        default: return std::nullopt;
    }
}

#else

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_weather_warning_state_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}

#endif

} // namespace def
} // namespace azaraC
