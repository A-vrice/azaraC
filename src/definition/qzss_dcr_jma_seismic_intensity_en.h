#pragma once
// AUTO-GENERATED from azarashi 0.17.1 with CI-CD
// Source module : azarashi.definitions.qzss.dcr.seismic_intensity
// Variable      : qzss_dcr_jma_seismic_intensity_en
// Entries       : 7
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

#if (AZARAC_ENABLE_SEISMIC) && (AZARAC_LANG_EN)

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_seismic_intensity_en_lookup(uint8_t id) noexcept {
    switch (id) {
        case 1: { static const char AZARAC_PROGMEM s[] = "Less than 4"; return azarac_pgm_view(s, 11); }
        case 2: { static const char AZARAC_PROGMEM s[] = "4"; return azarac_pgm_view(s, 1); }
        case 3: { static const char AZARAC_PROGMEM s[] = "5-lower"; return azarac_pgm_view(s, 7); }
        case 4: { static const char AZARAC_PROGMEM s[] = "5-upper"; return azarac_pgm_view(s, 7); }
        case 5: { static const char AZARAC_PROGMEM s[] = "6-lower"; return azarac_pgm_view(s, 7); }
        case 6: { static const char AZARAC_PROGMEM s[] = "6-upper"; return azarac_pgm_view(s, 7); }
        case 7: { static const char AZARAC_PROGMEM s[] = "7"; return azarac_pgm_view(s, 1); }
        default: return std::nullopt;
    }
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_seismic_intensity_en_lookup(uint8_t id) noexcept {
    switch (id) {
        case 1: return std::string_view{"Less than 4", 11};
        case 2: return std::string_view{"4", 1};
        case 3: return std::string_view{"5-lower", 7};
        case 4: return std::string_view{"5-upper", 7};
        case 5: return std::string_view{"6-lower", 7};
        case 6: return std::string_view{"6-upper", 7};
        case 7: return std::string_view{"7", 1};
        default: return std::nullopt;
    }
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_seismic_intensity_en_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_seismic_intensity_en_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
