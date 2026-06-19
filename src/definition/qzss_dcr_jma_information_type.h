#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcr_jma_information_type
// Variable      : qzss_dcr_jma_information_type
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

#if (AZARAC_LANG_JA)

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_information_type_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return std::string_view{"発表", 2};
        case 1: return std::string_view{"訂正", 2};
        case 2: return std::string_view{"取消", 2};
        default: return std::nullopt;
    }
}

#else

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_information_type_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}

#endif

} // namespace def
} // namespace azaraC
