#pragma once
// AUTO-GENERATED from azarashi 0.16.4 with CI-CD
// Source module : qzss_dcx_camf_d22_terrorism_threat_level
// Variable      : qzss_dcx_camf_d22_terrorism_threat_level
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

#if (AZARAC_ENABLE_DCX_CAMF)

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d22_terrorism_threat_level_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: { static const char AZARAC_PROGMEM s[] = "Very low threat level. A violent act of terrorism is highly unlikely. Measures are in place to keep the population safe."; return azarac_pgm_view(s, 120); }
        case 1: { static const char AZARAC_PROGMEM s[] = "Low threat level. A violent act of terrorism is possible but unlikely. Measures are in place to keep the population safe."; return azarac_pgm_view(s, 121); }
        case 2: { static const char AZARAC_PROGMEM s[] = "Medium threat level. A violent act of terrorism could occur. Additional measures are in place to keep the population safe."; return azarac_pgm_view(s, 122); }
        case 3: { static const char AZARAC_PROGMEM s[] = "High threat level. A violent act of terrorism is likely. Heightened measures are in place to keep the population safe."; return azarac_pgm_view(s, 118); }
        case 4: { static const char AZARAC_PROGMEM s[] = "Critical threat level. A violent act of terrorism is highly likely and could occur imminently. Exceptional measures are in place to keep the population safe."; return azarac_pgm_view(s, 157); }
        default: return std::nullopt;
    }
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d22_terrorism_threat_level_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return std::string_view{"Very low threat level. A violent act of terrorism is highly unlikely. Measures are in place to keep the population safe.", 120};
        case 1: return std::string_view{"Low threat level. A violent act of terrorism is possible but unlikely. Measures are in place to keep the population safe.", 121};
        case 2: return std::string_view{"Medium threat level. A violent act of terrorism could occur. Additional measures are in place to keep the population safe.", 122};
        case 3: return std::string_view{"High threat level. A violent act of terrorism is likely. Heightened measures are in place to keep the population safe.", 118};
        case 4: return std::string_view{"Critical threat level. A violent act of terrorism is highly likely and could occur imminently. Exceptional measures are in place to keep the population safe.", 157};
        default: return std::nullopt;
    }
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d22_terrorism_threat_level_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d22_terrorism_threat_level_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
