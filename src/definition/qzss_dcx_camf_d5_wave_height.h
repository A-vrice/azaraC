#pragma once
// AUTO-GENERATED from azarashi 0.16.4 with CI-CD
// Source module : qzss_dcx_camf_d5_wave_height
// Variable      : qzss_dcx_camf_d5_wave_height
// Entries       : 8
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
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d5_wave_height_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: { static const char AZARAC_PROGMEM s[] = "H ≤ 0.5m"; return azarac_pgm_view(s, 10); }
        case 1: { static const char AZARAC_PROGMEM s[] = "0.5m < H ≤ 1.0m"; return azarac_pgm_view(s, 17); }
        case 2: { static const char AZARAC_PROGMEM s[] = "1.0m < H ≤ 1.5m"; return azarac_pgm_view(s, 17); }
        case 3: { static const char AZARAC_PROGMEM s[] = "1.5m < H ≤ 2.0m"; return azarac_pgm_view(s, 17); }
        case 4: { static const char AZARAC_PROGMEM s[] = "2.0m < H ≤ 3.0m"; return azarac_pgm_view(s, 17); }
        case 5: { static const char AZARAC_PROGMEM s[] = "3.0m < H ≤ 5.0m"; return azarac_pgm_view(s, 17); }
        case 6: { static const char AZARAC_PROGMEM s[] = "5.0m < H ≤ 10.0m"; return azarac_pgm_view(s, 18); }
        case 7: { static const char AZARAC_PROGMEM s[] = "H > 10.0m"; return azarac_pgm_view(s, 9); }
        default: return std::nullopt;
    }
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d5_wave_height_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return std::string_view{"H ≤ 0.5m", 10};
        case 1: return std::string_view{"0.5m < H ≤ 1.0m", 17};
        case 2: return std::string_view{"1.0m < H ≤ 1.5m", 17};
        case 3: return std::string_view{"1.5m < H ≤ 2.0m", 17};
        case 4: return std::string_view{"2.0m < H ≤ 3.0m", 17};
        case 5: return std::string_view{"3.0m < H ≤ 5.0m", 17};
        case 6: return std::string_view{"5.0m < H ≤ 10.0m", 18};
        case 7: return std::string_view{"H > 10.0m", 9};
        default: return std::nullopt;
    }
}
#endif

#else

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d5_wave_height_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}

#endif

} // namespace def
} // namespace azaraC
