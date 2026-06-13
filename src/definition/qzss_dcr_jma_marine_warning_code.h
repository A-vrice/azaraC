#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcr_jma_marine_warning_code
// Variable      : qzss_dcr_jma_marine_warning_code
// Entries       : 9
// Strategy      : switch

#include <cstdint>
#include <optional>
#include <string_view>
#include "../azaraC.h"

namespace azaraC {
namespace def {

#if (AZARAC_ENABLE_MARINE)

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_marine_warning_code_lookup(uint8_t id) {
    switch (id) {
        case 0: return std::string_view{"海上警報解除", 18};
        case 10: return std::string_view{"海上着氷警報", 18};
        case 11: return std::string_view{"海上濃霧警報", 18};
        case 12: return std::string_view{"海上うねり警報", 21};
        case 20: return std::string_view{"海上風警報", 15};
        case 21: return std::string_view{"海上強風警報", 18};
        case 22: return std::string_view{"海上暴風警報", 18};
        case 23: return std::string_view{"海上台風警報", 18};
        case 31: return std::string_view{"その他の警報等情報要素 海上警報", 46};
        default: return std::nullopt;
    }
}

#else

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_marine_warning_code_lookup(uint8_t id) {
    (void)id;
    return std::nullopt;
}

#endif

} // namespace def
} // namespace azaraC
