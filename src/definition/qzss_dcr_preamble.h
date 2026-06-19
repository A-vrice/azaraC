#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcr_preamble
// Variable      : qzss_dcr_preamble
// Entries       : 3
// Strategy      : switch

// NOTE: This function may return nullptr for unknown IDs.
// Callers MUST perform a null-check before using the result.

#include <cstdint>
#include <optional>
#include <string_view>
#include "../azaraC.h"

namespace azaraC {
namespace def {

#if (AZARAC_ENABLE_QZSS_DCR_PREAMBLE)

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_preamble_lookup(uint8_t id) noexcept {
    switch (id) {
        case 83: return std::string_view{"A", 1};
        case 154: return std::string_view{"B", 1};
        case 198: return std::string_view{"C", 1};
        default: return std::nullopt;
    }
}

#else

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_preamble_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}

#endif

} // namespace def
} // namespace azaraC
