#pragma once
// AUTO-GENERATED from azarashi 0.16.4 with CI-CD
// Source module : qzss_dcr_jma_information_type_en
// Variable      : qzss_dcr_jma_information_type_en
// Entries       : 3
// Strategy      : switch

// NOTE: This function may return nullptr for unknown IDs.
// Callers MUST perform a null-check before using the result.

#include <cstdint>
#include <optional>
#include <string_view>
#include "../azaraC.h"
#include "../internal/FlashString.h"

namespace azaraC {
namespace def {

#if (AZARAC_LANG_EN)

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_information_type_en_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: { static const char AZARAC_PROGMEM s[] = "Issue"; return azarac_pgm_view(s, 5); }
        case 1: { static const char AZARAC_PROGMEM s[] = "Correction"; return azarac_pgm_view(s, 10); }
        case 2: { static const char AZARAC_PROGMEM s[] = "Cancellation"; return azarac_pgm_view(s, 12); }
        default: return std::nullopt;
    }
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_information_type_en_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return std::string_view{"Issue", 5};
        case 1: return std::string_view{"Correction", 10};
        case 2: return std::string_view{"Cancellation", 12};
        default: return std::nullopt;
    }
}
#endif

#else

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_information_type_en_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}

#endif

} // namespace def
} // namespace azaraC
