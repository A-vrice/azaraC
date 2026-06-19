#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcr_jma_ash_fall_warning_code
// Variable      : qzss_dcr_jma_ash_fall_warning_code
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

#if (AZARAC_ENABLE_ASH_FALL)

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_ash_fall_warning_code_lookup(uint8_t id) noexcept {
    switch (id) {
        case 1: return std::string_view{"少量の降灰", 5};
        case 2: return std::string_view{"やや多量の降灰", 7};
        case 3: return std::string_view{"多量の降灰", 5};
        case 4: return std::string_view{"小さな噴石の落下", 8};
        case 7: return std::string_view{"その他の防災気象情報要素2", 13};
        default: return std::nullopt;
    }
}

#else

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_ash_fall_warning_code_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}

#endif

} // namespace def
} // namespace azaraC
