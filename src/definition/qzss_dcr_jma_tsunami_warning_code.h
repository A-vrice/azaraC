#pragma once
// AUTO-GENERATED from azarashi 0.16.4 with CI-CD
// Source module : qzss_dcr_jma_tsunami_warning_code
// Variable      : qzss_dcr_jma_tsunami_warning_code
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

#if (AZARAC_ENABLE_TSUNAMI)

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_tsunami_warning_code_lookup(uint8_t id) noexcept {
    switch (id) {
        case 1: { static const char AZARAC_PROGMEM s[] = "津波なし"; return azarac_pgm_view(s, 12); }
        case 2: { static const char AZARAC_PROGMEM s[] = "警報解除"; return azarac_pgm_view(s, 12); }
        case 3: { static const char AZARAC_PROGMEM s[] = "津波警報"; return azarac_pgm_view(s, 12); }
        case 4: { static const char AZARAC_PROGMEM s[] = "大津波警報"; return azarac_pgm_view(s, 15); }
        case 5: { static const char AZARAC_PROGMEM s[] = "大津波警報：発表"; return azarac_pgm_view(s, 24); }
        case 15: { static const char AZARAC_PROGMEM s[] = "その他の警報"; return azarac_pgm_view(s, 18); }
        default: return std::nullopt;
    }
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_tsunami_warning_code_lookup(uint8_t id) noexcept {
    switch (id) {
        case 1: return std::string_view{"津波なし", 12};
        case 2: return std::string_view{"警報解除", 12};
        case 3: return std::string_view{"津波警報", 12};
        case 4: return std::string_view{"大津波警報", 15};
        case 5: return std::string_view{"大津波警報：発表", 24};
        case 15: return std::string_view{"その他の警報", 18};
        default: return std::nullopt;
    }
}
#endif

#else

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_tsunami_warning_code_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}

#endif

} // namespace def
} // namespace azaraC
