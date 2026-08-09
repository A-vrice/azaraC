#pragma once
// AUTO-GENERATED from azarashi 0.16.4 with CI-CD
// Source module : qzss_dcx_camf_a1_message_type
// Variable      : qzss_dcx_camf_a1_message_type
// Entries       : 4
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
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_a1_message_type_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: { static const char AZARAC_PROGMEM s[] = "Test"; return azarac_pgm_view(s, 4); }
        case 1: { static const char AZARAC_PROGMEM s[] = "Alert"; return azarac_pgm_view(s, 5); }
        case 2: { static const char AZARAC_PROGMEM s[] = "Update"; return azarac_pgm_view(s, 6); }
        case 3: { static const char AZARAC_PROGMEM s[] = "All Clear"; return azarac_pgm_view(s, 9); }
        default: return std::nullopt;
    }
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_a1_message_type_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return std::string_view{"Test", 4};
        case 1: return std::string_view{"Alert", 5};
        case 2: return std::string_view{"Update", 6};
        case 3: return std::string_view{"All Clear", 9};
        default: return std::nullopt;
    }
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_a1_message_type_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_a1_message_type_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
