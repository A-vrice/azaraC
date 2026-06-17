#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcr_jma_information_type
// Variable      : qzss_dcr_jma_information_type_en
// Entries       : 3
// Strategy      : switch

#include <cstdint>
#include <optional>
#include <string_view>
#include "../azaraC.h"

namespace azaraC {
namespace def {

#if (AZARAC_LANG_EN)

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_information_type_en_lookup(uint8_t id) {
    switch (id) {
        case 0: return std::string_view{"Issue", 5};
        case 1: return std::string_view{"Correction", 10};
        case 2: return std::string_view{"Cancellation", 12};
        default: return std::nullopt;
    }
}

#else

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_information_type_en_lookup(uint8_t id) {
    (void)id;
    return std::nullopt;
}

#endif

} // namespace def
} // namespace azaraC
