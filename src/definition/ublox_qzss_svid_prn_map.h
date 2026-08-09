#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : ublox_qzss_svid_prn_map
// Variable      : ublox_qzss_svid_prn_map
// Entries       : 4
// Strategy      : switch

#if defined(__AVR__)
#include "../internal/avr_std/cstdint"
#else
#include <cstdint>
#endif
#if defined(__AVR__)
#include "../internal/avr_std/optional"
#else
#include <optional>
#endif
#if defined(__AVR__)
#include "../internal/avr_std/string_view"
#else
#include <string_view>
#endif
#include "../azaraC_config.h"
#include "../internal/FlashString.h"

namespace azaraC {
namespace def {

#if defined(__AVR__)

[[nodiscard]] inline std::optional<std::string_view> ublox_qzss_svid_prn_map_lookup(uint8_t id) noexcept {
    switch (id) {
        case 1: { static const char AZARAC_PROGMEM s[] = "183"; return azarac_pgm_view(s, 3); }
        case 2: { static const char AZARAC_PROGMEM s[] = "184"; return azarac_pgm_view(s, 3); }
        case 3: { static const char AZARAC_PROGMEM s[] = "185"; return azarac_pgm_view(s, 3); }
        case 4: { static const char AZARAC_PROGMEM s[] = "186"; return azarac_pgm_view(s, 3); }
        case 7: { static const char AZARAC_PROGMEM s[] = "189"; return azarac_pgm_view(s, 3); }
        default: return std::nullopt;
    }
}

#else

[[nodiscard]] inline constexpr std::optional<std::string_view> ublox_qzss_svid_prn_map_lookup(uint8_t id) {
    switch (id) {
        case 1: return std::string_view{"183", 3};
        case 2: return std::string_view{"184", 3};
        case 3: return std::string_view{"185", 3};
        case 4: return std::string_view{"186", 3};
        case 7: return std::string_view{"189", 3};
        default: return std::nullopt;
    }
}

#endif

} // namespace def
} // namespace azaraC
