#pragma once
// AUTO-GENERATED from azarashi 0.16.4 with CI-CD
// Source module : qzss_dcr_satellite_prn
// Variable      : qzss_dcr_satellite_prn
// Entries       : 5
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

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_satellite_prn_lookup(uint8_t id) noexcept {
    switch (id) {
        case 55: { static const char AZARAC_PROGMEM s[] = "PRN183"; return azarac_pgm_view(s, 6); }
        case 56: { static const char AZARAC_PROGMEM s[] = "PRN184"; return azarac_pgm_view(s, 6); }
        case 57: { static const char AZARAC_PROGMEM s[] = "PRN185"; return azarac_pgm_view(s, 6); }
        case 58: { static const char AZARAC_PROGMEM s[] = "PRN186"; return azarac_pgm_view(s, 6); }
        case 61: { static const char AZARAC_PROGMEM s[] = "PRN189"; return azarac_pgm_view(s, 6); }
        default: return std::nullopt;
    }
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_satellite_prn_lookup(uint8_t id) noexcept {
    switch (id) {
        case 55: return std::string_view{"PRN183", 6};
        case 56: return std::string_view{"PRN184", 6};
        case 57: return std::string_view{"PRN185", 6};
        case 58: return std::string_view{"PRN186", 6};
        case 61: return std::string_view{"PRN189", 6};
        default: return std::nullopt;
    }
}
#endif

} // namespace def
} // namespace azaraC
