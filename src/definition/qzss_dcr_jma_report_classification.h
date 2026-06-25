#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcr_jma_report_classification
// Variable      : qzss_dcr_jma_report_classification
// Entries       : 4
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

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_report_classification_lookup(uint8_t id) noexcept {
    switch (id) {
        case 1: return std::string_view{"最優先", 9};
        case 2: return std::string_view{"優先", 6};
        case 3: return std::string_view{"通常", 6};
        case 7: return std::string_view{"訓練/試験", 13};
        default: return std::nullopt;
    }
}

#else

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_report_classification_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}

#endif

} // namespace def
} // namespace azaraC
