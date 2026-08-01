#pragma once
// AUTO-GENERATED from azarashi 0.16.4 with CI-CD
// Source module : qzss_dcx_camf_a8_hazard_duration
// Variable      : qzss_dcx_camf_a8_hazard_duration
// Entries       : 4
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
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_a8_hazard_duration_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: { static const char AZARAC_PROGMEM s[] = "Unknown"; return azarac_pgm_view(s, 7); }
        case 1: { static const char AZARAC_PROGMEM s[] = "Duration < 6H"; return azarac_pgm_view(s, 13); }
        case 2: { static const char AZARAC_PROGMEM s[] = "6H <= Duration < 12H"; return azarac_pgm_view(s, 20); }
        case 3: { static const char AZARAC_PROGMEM s[] = "12H <= Duration < 24H"; return azarac_pgm_view(s, 21); }
        default: return std::nullopt;
    }
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_a8_hazard_duration_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return std::string_view{"Unknown", 7};
        case 1: return std::string_view{"Duration < 6H", 13};
        case 2: return std::string_view{"6H <= Duration < 12H", 20};
        case 3: return std::string_view{"12H <= Duration < 24H", 21};
        default: return std::nullopt;
    }
}
#endif

#else

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_a8_hazard_duration_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}

#endif

} // namespace def
} // namespace azaraC
