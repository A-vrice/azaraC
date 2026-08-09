#pragma once
// AUTO-GENERATED from azarashi 0.16.4 with CI-CD
// Source module : qzss_dcx_camf_a5_severity
// Variable      : qzss_dcx_camf_a5_severity
// Entries       : 4
// Strategy      : switch

// NOTE: This function may return nullptr for unknown IDs.
// Callers MUST perform a null-check before using the result.

#if defined(__AVR__)
#include "../internal/avr_std/cstdint"
#include "../internal/avr_std/optional"
#include "../internal/avr_std/string_view"
#else
#include <cstdint>
#include <optional>
#include <string_view>
#endif
#include "../azaraC.h"
#include "../internal/FlashString.h"

namespace azaraC {
namespace def {

#if (AZARAC_ENABLE_DCX_CAMF)

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_a5_severity_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: { static const char AZARAC_PROGMEM s[] = "Unknown"; return azarac_pgm_view(s, 7); }
        case 1: { static const char AZARAC_PROGMEM s[] = "Moderate - Possible threat to life or property"; return azarac_pgm_view(s, 46); }
        case 2: { static const char AZARAC_PROGMEM s[] = "Severe - Significant threat to life or property"; return azarac_pgm_view(s, 47); }
        case 3: { static const char AZARAC_PROGMEM s[] = "Extreme - Extraordinary threat to life or property"; return azarac_pgm_view(s, 50); }
        default: return std::nullopt;
    }
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_a5_severity_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return std::string_view{"Unknown", 7};
        case 1: return std::string_view{"Moderate - Possible threat to life or property", 46};
        case 2: return std::string_view{"Severe - Significant threat to life or property", 47};
        case 3: return std::string_view{"Extreme - Extraordinary threat to life or property", 50};
        default: return std::nullopt;
    }
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_a5_severity_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_a5_severity_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
