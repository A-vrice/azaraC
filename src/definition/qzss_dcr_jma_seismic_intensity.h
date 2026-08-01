#pragma once
// AUTO-GENERATED from azarashi 0.16.4 with CI-CD
// Source module : qzss_dcr_jma_seismic_intensity
// Variable      : qzss_dcr_jma_seismic_intensity
// Entries       : 7
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

#if (AZARAC_ENABLE_SEISMIC)

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_seismic_intensity_lookup(uint8_t id) noexcept {
    switch (id) {
        case 1: { static const char AZARAC_PROGMEM s[] = "4未満"; return azarac_pgm_view(s, 7); }
        case 2: { static const char AZARAC_PROGMEM s[] = "4"; return azarac_pgm_view(s, 1); }
        case 3: { static const char AZARAC_PROGMEM s[] = "5弱"; return azarac_pgm_view(s, 4); }
        case 4: { static const char AZARAC_PROGMEM s[] = "5強"; return azarac_pgm_view(s, 4); }
        case 5: { static const char AZARAC_PROGMEM s[] = "6弱"; return azarac_pgm_view(s, 4); }
        case 6: { static const char AZARAC_PROGMEM s[] = "6強"; return azarac_pgm_view(s, 4); }
        case 7: { static const char AZARAC_PROGMEM s[] = "7"; return azarac_pgm_view(s, 1); }
        default: return std::nullopt;
    }
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_seismic_intensity_lookup(uint8_t id) noexcept {
    switch (id) {
        case 1: return std::string_view{"4未満", 7};
        case 2: return std::string_view{"4", 1};
        case 3: return std::string_view{"5弱", 4};
        case 4: return std::string_view{"5強", 4};
        case 5: return std::string_view{"6弱", 4};
        case 6: return std::string_view{"6強", 4};
        case 7: return std::string_view{"7", 1};
        default: return std::nullopt;
    }
}
#endif

#else

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_seismic_intensity_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}

#endif

} // namespace def
} // namespace azaraC
