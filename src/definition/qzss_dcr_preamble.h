#pragma once
// AUTO-GENERATED from azarashi 0.16.4 with CI-CD
// Source module : qzss_dcr_preamble
// Variable      : qzss_dcr_preamble
// Entries       : 3
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

#if (AZARAC_ENABLE_QZSS_DCR_PREAMBLE)

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_preamble_lookup(uint8_t id) noexcept {
    switch (id) {
        case 83: { static const char AZARAC_PROGMEM s[] = "A"; return azarac_pgm_view(s, 1); }
        case 154: { static const char AZARAC_PROGMEM s[] = "B"; return azarac_pgm_view(s, 1); }
        case 198: { static const char AZARAC_PROGMEM s[] = "C"; return azarac_pgm_view(s, 1); }
        default: return std::nullopt;
    }
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_preamble_lookup(uint8_t id) noexcept {
    switch (id) {
        case 83: return std::string_view{"A", 1};
        case 154: return std::string_view{"B", 1};
        case 198: return std::string_view{"C", 1};
        default: return std::nullopt;
    }
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_preamble_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_preamble_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
