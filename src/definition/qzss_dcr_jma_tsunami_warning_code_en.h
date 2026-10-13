#pragma once
// AUTO-GENERATED from azarashi 0.17.1 with CI-CD
// Source module : azarashi.definitions.qzss.dcr.tsunami_warning_code
// Variable      : qzss_dcr_jma_tsunami_warning_code_en
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

#if (AZARAC_ENABLE_TSUNAMI) && (AZARAC_LANG_EN)

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_tsunami_warning_code_en_lookup(uint8_t id) noexcept {
    switch (id) {
        case 1: { static const char AZARAC_PROGMEM s[] = "No Tsunami"; return azarac_pgm_view(s, 10); }
        case 2: { static const char AZARAC_PROGMEM s[] = "Warning Lifted"; return azarac_pgm_view(s, 14); }
        case 3: { static const char AZARAC_PROGMEM s[] = "Tsunami Warning"; return azarac_pgm_view(s, 15); }
        case 4: { static const char AZARAC_PROGMEM s[] = "Major Tsunami Warning"; return azarac_pgm_view(s, 21); }
        case 5: { static const char AZARAC_PROGMEM s[] = "Major Tsunami Warning: Issued"; return azarac_pgm_view(s, 29); }
        case 15: { static const char AZARAC_PROGMEM s[] = "Other Warning"; return azarac_pgm_view(s, 13); }
        default: return std::nullopt;
    }
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_tsunami_warning_code_en_lookup(uint8_t id) noexcept {
    switch (id) {
        case 1: return std::string_view{"No Tsunami", 10};
        case 2: return std::string_view{"Warning Lifted", 14};
        case 3: return std::string_view{"Tsunami Warning", 15};
        case 4: return std::string_view{"Major Tsunami Warning", 21};
        case 5: return std::string_view{"Major Tsunami Warning: Issued", 29};
        case 15: return std::string_view{"Other Warning", 13};
        default: return std::nullopt;
    }
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_tsunami_warning_code_en_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_tsunami_warning_code_en_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
