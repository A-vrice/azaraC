#pragma once
// AUTO-GENERATED from azarashi 0.16.4 with CI-CD
// Source module : qzss_dcx_camf_b4_lower_level_fields_tables
// Variable      : qzss_dcx_camf_d1_magnitude_on_richter_scale
// Entries       : 9
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
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d1_magnitude_on_richter_scale_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: { static const char AZARAC_PROGMEM s[] = "1.0-1.9 - Micro"; return azarac_pgm_view(s, 15); }
        case 1: { static const char AZARAC_PROGMEM s[] = "2.0-2.9 - Minor"; return azarac_pgm_view(s, 15); }
        case 2: { static const char AZARAC_PROGMEM s[] = "3.0-3.9 - Minor"; return azarac_pgm_view(s, 15); }
        case 3: { static const char AZARAC_PROGMEM s[] = "4.0-4.9 - Light"; return azarac_pgm_view(s, 15); }
        case 4: { static const char AZARAC_PROGMEM s[] = "5.0-5.9 - Moderate"; return azarac_pgm_view(s, 18); }
        case 5: { static const char AZARAC_PROGMEM s[] = "6.0-6.9 - Strong"; return azarac_pgm_view(s, 16); }
        case 6: { static const char AZARAC_PROGMEM s[] = "7.0-7.9 - Major"; return azarac_pgm_view(s, 15); }
        case 7: { static const char AZARAC_PROGMEM s[] = "8.0-8.9 - Great"; return azarac_pgm_view(s, 15); }
        case 8: { static const char AZARAC_PROGMEM s[] = "9.0 and greater - Great"; return azarac_pgm_view(s, 23); }
        default: return std::nullopt;
    }
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d1_magnitude_on_richter_scale_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return std::string_view{"1.0-1.9 - Micro", 15};
        case 1: return std::string_view{"2.0-2.9 - Minor", 15};
        case 2: return std::string_view{"3.0-3.9 - Minor", 15};
        case 3: return std::string_view{"4.0-4.9 - Light", 15};
        case 4: return std::string_view{"5.0-5.9 - Moderate", 18};
        case 5: return std::string_view{"6.0-6.9 - Strong", 16};
        case 6: return std::string_view{"7.0-7.9 - Major", 15};
        case 7: return std::string_view{"8.0-8.9 - Great", 15};
        case 8: return std::string_view{"9.0 and greater - Great", 23};
        default: return std::nullopt;
    }
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d1_magnitude_on_richter_scale_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d1_magnitude_on_richter_scale_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
