#pragma once
// AUTO-GENERATED from azarashi 0.16.4 with CI-CD
// Source module : qzss_dcx_camf_b4_lower_level_fields_tables
// Variable      : qzss_dcx_camf_d16_lightning_intensity
// Entries       : 6
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
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d16_lightning_intensity_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: { static const char AZARAC_PROGMEM s[] = "LAL 1 - No thunderstorms"; return azarac_pgm_view(s, 24); }
        case 1: { static const char AZARAC_PROGMEM s[] = "LAL 2 - Isolated thunderstorms. Light rain will occasionally reach the ground. Lightning is very infrequent, 1 to 5 cloud to ground strikes in a 5-minute period."; return azarac_pgm_view(s, 161); }
        case 2: { static const char AZARAC_PROGMEM s[] = "LAL 3 - Widely scattered thunderstorms. Light to moderate rain will reach the ground. Lightning is infrequent, 6 to 10 cloud to ground strikes in a 5-minute period."; return azarac_pgm_view(s, 164); }
        case 3: { static const char AZARAC_PROGMEM s[] = "LAL 4 - Scattered thunderstorms. Moderate rain is commonly produced Lightning is frequent, 11 to 15 cloud to ground strikes in a 5-minute period."; return azarac_pgm_view(s, 145); }
        case 4: { static const char AZARAC_PROGMEM s[] = "LAL 5 - Numerous thunderstorms. Rainfall is moderate to heavy. Lightning is frequent and intense, greater than 15 cloud to ground strikes in a 5-minute period."; return azarac_pgm_view(s, 159); }
        case 5: { static const char AZARAC_PROGMEM s[] = "LAL 6 - Dry lightning (same as LAL 3 but without the rain). This type of lightning has the potential for extreme fire activity and is normally highlighted in fire weather forecasts with Red Flag Warning."; return azarac_pgm_view(s, 203); }
        default: return std::nullopt;
    }
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d16_lightning_intensity_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return std::string_view{"LAL 1 - No thunderstorms", 24};
        case 1: return std::string_view{"LAL 2 - Isolated thunderstorms. Light rain will occasionally reach the ground. Lightning is very infrequent, 1 to 5 cloud to ground strikes in a 5-minute period.", 161};
        case 2: return std::string_view{"LAL 3 - Widely scattered thunderstorms. Light to moderate rain will reach the ground. Lightning is infrequent, 6 to 10 cloud to ground strikes in a 5-minute period.", 164};
        case 3: return std::string_view{"LAL 4 - Scattered thunderstorms. Moderate rain is commonly produced Lightning is frequent, 11 to 15 cloud to ground strikes in a 5-minute period.", 145};
        case 4: return std::string_view{"LAL 5 - Numerous thunderstorms. Rainfall is moderate to heavy. Lightning is frequent and intense, greater than 15 cloud to ground strikes in a 5-minute period.", 159};
        case 5: return std::string_view{"LAL 6 - Dry lightning (same as LAL 3 but without the rain). This type of lightning has the potential for extreme fire activity and is normally highlighted in fire weather forecasts with Red Flag Warning.", 203};
        default: return std::nullopt;
    }
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d16_lightning_intensity_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d16_lightning_intensity_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
