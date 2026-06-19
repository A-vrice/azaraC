#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcr_jma_flood_warning_level
// Variable      : qzss_dcr_jma_flood_warning_level
// Entries       : 5
// Strategy      : switch

// NOTE: This function may return nullptr for unknown IDs.
// Callers MUST perform a null-check before using the result.

#include <cstdint>
#include <optional>
#include <string_view>
#include "../azaraC.h"

namespace azaraC {
namespace def {

#if (AZARAC_ENABLE_FLOOD)

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_flood_warning_level_lookup(uint8_t id) noexcept {
    switch (id) {
        case 1: return std::string_view{"警報解除", 4};
        case 2: return std::string_view{"氾濫警戒情報", 6};
        case 3: return std::string_view{"氾濫危険情報", 6};
        case 4: return std::string_view{"氾濫発生情報", 6};
        case 15: return std::string_view{"その他の警戒レベル", 9};
        default: return std::nullopt;
    }
}

#else

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_flood_warning_level_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}

#endif

} // namespace def
} // namespace azaraC
