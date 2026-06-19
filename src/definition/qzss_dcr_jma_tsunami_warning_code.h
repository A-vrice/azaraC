#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcr_jma_tsunami_warning_code
// Variable      : qzss_dcr_jma_tsunami_warning_code
// Entries       : 6
// Strategy      : switch

// NOTE: This function may return nullptr for unknown IDs.
// Callers MUST perform a null-check before using the result.

#include <cstdint>
#include <optional>
#include <string_view>
#include "../azaraC.h"

namespace azaraC {
namespace def {

#if (AZARAC_ENABLE_TSUNAMI)

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_tsunami_warning_code_lookup(uint8_t id) noexcept {
    switch (id) {
        case 1: return std::string_view{"津波なし", 4};
        case 2: return std::string_view{"警報解除", 4};
        case 3: return std::string_view{"津波警報", 4};
        case 4: return std::string_view{"大津波警報", 5};
        case 5: return std::string_view{"大津波警報：発表", 8};
        case 15: return std::string_view{"その他の警報", 6};
        default: return std::nullopt;
    }
}

#else

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_tsunami_warning_code_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}

#endif

} // namespace def
} // namespace azaraC
