#pragma once
// AUTO-GENERATED from azarashi 0.16.4 with CI-CD
// Source module : qzss_dcx_camf_d9_rainfall_amounts
// Variable      : qzss_dcx_camf_d9_rainfall_amounts
// Entries       : 8
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

#if (AZARAC_ENABLE_DCX_CAMF)

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d9_rainfall_amounts_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: { static const char AZARAC_PROGMEM s[] = "p ≤ 2.5mm/h"; return azarac_pgm_view(s, 13); }
        case 1: { static const char AZARAC_PROGMEM s[] = "2.5mm/h < p ≤ 7.5mm/h"; return azarac_pgm_view(s, 23); }
        case 2: { static const char AZARAC_PROGMEM s[] = "7.5mm/h < p ≤ 10mm/h"; return azarac_pgm_view(s, 22); }
        case 3: { static const char AZARAC_PROGMEM s[] = "10mm/h < p ≤ 20mm/h"; return azarac_pgm_view(s, 21); }
        case 4: { static const char AZARAC_PROGMEM s[] = "20mm/h < p ≤ 30mm/h"; return azarac_pgm_view(s, 21); }
        case 5: { static const char AZARAC_PROGMEM s[] = "30mm/h < p ≤ 50mm/h"; return azarac_pgm_view(s, 21); }
        case 6: { static const char AZARAC_PROGMEM s[] = "50mm/h < p ≤ 80mm/h"; return azarac_pgm_view(s, 21); }
        case 7: { static const char AZARAC_PROGMEM s[] = "80mm/h < p"; return azarac_pgm_view(s, 10); }
        default: return std::nullopt;
    }
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d9_rainfall_amounts_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return std::string_view{"p ≤ 2.5mm/h", 13};
        case 1: return std::string_view{"2.5mm/h < p ≤ 7.5mm/h", 23};
        case 2: return std::string_view{"7.5mm/h < p ≤ 10mm/h", 22};
        case 3: return std::string_view{"10mm/h < p ≤ 20mm/h", 21};
        case 4: return std::string_view{"20mm/h < p ≤ 30mm/h", 21};
        case 5: return std::string_view{"30mm/h < p ≤ 50mm/h", 21};
        case 6: return std::string_view{"50mm/h < p ≤ 80mm/h", 21};
        case 7: return std::string_view{"80mm/h < p", 10};
        default: return std::nullopt;
    }
}
#endif

#else

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d9_rainfall_amounts_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}

#endif

} // namespace def
} // namespace azaraC
