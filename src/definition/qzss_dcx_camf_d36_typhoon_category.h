#pragma once
// AUTO-GENERATED from azarashi 0.16.4 with CI-CD
// Source module : qzss_dcx_camf_d36_typhoon_category
// Variable      : qzss_dcx_camf_d36_typhoon_category
// Entries       : 5
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
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d36_typhoon_category_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: { static const char AZARAC_PROGMEM s[] = "Scale 1 and Intensity 1"; return azarac_pgm_view(s, 23); }
        case 1: { static const char AZARAC_PROGMEM s[] = "Scale 1 and Intensity 2"; return azarac_pgm_view(s, 23); }
        case 2: { static const char AZARAC_PROGMEM s[] = "Scale 1 and Intensity 3"; return azarac_pgm_view(s, 23); }
        case 3: { static const char AZARAC_PROGMEM s[] = "Scale 2 and Intensity 1"; return azarac_pgm_view(s, 23); }
        case 4: { static const char AZARAC_PROGMEM s[] = "Scale 2 and Intensity 2"; return azarac_pgm_view(s, 23); }
        default: return std::nullopt;
    }
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d36_typhoon_category_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return std::string_view{"Scale 1 and Intensity 1", 23};
        case 1: return std::string_view{"Scale 1 and Intensity 2", 23};
        case 2: return std::string_view{"Scale 1 and Intensity 3", 23};
        case 3: return std::string_view{"Scale 2 and Intensity 1", 23};
        case 4: return std::string_view{"Scale 2 and Intensity 2", 23};
        default: return std::nullopt;
    }
}
#endif

#else

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d36_typhoon_category_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}

#endif

} // namespace def
} // namespace azaraC
