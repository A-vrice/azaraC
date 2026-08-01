#pragma once
// AUTO-GENERATED from azarashi 0.16.4 with CI-CD
// Source module : qzss_dcx_camf_d10_damage_category
// Variable      : qzss_dcx_camf_d10_damage_category
// Entries       : 6
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
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d10_damage_category_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: { static const char AZARAC_PROGMEM s[] = "Category 1 - Very dangerous winds will produce some damage. Scale 1 and Intensity 1"; return azarac_pgm_view(s, 83); }
        case 1: { static const char AZARAC_PROGMEM s[] = "Category 2 - Extremely dangerous winds will cause extensive damage. Scale 1 and Intensity 2"; return azarac_pgm_view(s, 91); }
        case 2: { static const char AZARAC_PROGMEM s[] = "Category 3 - Devastating damage will occur. Scale 1 and Intensity 3"; return azarac_pgm_view(s, 67); }
        case 3: { static const char AZARAC_PROGMEM s[] = "Category 4 - Catastrophic damage will occur. Scale 2 and Intensity 1"; return azarac_pgm_view(s, 68); }
        case 4: { static const char AZARAC_PROGMEM s[] = "Category 5 - Catastrophic damage will occur. Scale 2 and Intensity 2"; return azarac_pgm_view(s, 68); }
        case 5: { static const char AZARAC_PROGMEM s[] = "Category 5 - Catastrophic damage will occur. Scale 3 and Intensity 3"; return azarac_pgm_view(s, 68); }
        default: return std::nullopt;
    }
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d10_damage_category_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return std::string_view{"Category 1 - Very dangerous winds will produce some damage. Scale 1 and Intensity 1", 83};
        case 1: return std::string_view{"Category 2 - Extremely dangerous winds will cause extensive damage. Scale 1 and Intensity 2", 91};
        case 2: return std::string_view{"Category 3 - Devastating damage will occur. Scale 1 and Intensity 3", 67};
        case 3: return std::string_view{"Category 4 - Catastrophic damage will occur. Scale 2 and Intensity 1", 68};
        case 4: return std::string_view{"Category 5 - Catastrophic damage will occur. Scale 2 and Intensity 2", 68};
        case 5: return std::string_view{"Category 5 - Catastrophic damage will occur. Scale 3 and Intensity 3", 68};
        default: return std::nullopt;
    }
}
#endif

#else

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d10_damage_category_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}

#endif

} // namespace def
} // namespace azaraC
