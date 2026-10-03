#pragma once
// AUTO-GENERATED from azarashi 0.17.0 with CI-CD
// Source module : azarashi.definitions.qzss.dcr.expected_ash_fall_time
// Variable      : qzss_dcr_jma_expected_ash_fall_time
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

#if (AZARAC_ENABLE_ASH_FALL) && (AZARAC_LANG_JA)

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_expected_ash_fall_time_lookup(uint8_t id) noexcept {
    switch (id) {
        case 1: { static const char AZARAC_PROGMEM s[] = "1時間"; return azarac_pgm_view(s, 7); }
        case 2: { static const char AZARAC_PROGMEM s[] = "2時間"; return azarac_pgm_view(s, 7); }
        case 3: { static const char AZARAC_PROGMEM s[] = "3時間"; return azarac_pgm_view(s, 7); }
        case 4: { static const char AZARAC_PROGMEM s[] = "4時間"; return azarac_pgm_view(s, 7); }
        case 5: { static const char AZARAC_PROGMEM s[] = "5時間"; return azarac_pgm_view(s, 7); }
        case 6: { static const char AZARAC_PROGMEM s[] = "6時間"; return azarac_pgm_view(s, 7); }
        default: return std::nullopt;
    }
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_expected_ash_fall_time_lookup(uint8_t id) noexcept {
    switch (id) {
        case 1: return std::string_view{"1時間", 7};
        case 2: return std::string_view{"2時間", 7};
        case 3: return std::string_view{"3時間", 7};
        case 4: return std::string_view{"4時間", 7};
        case 5: return std::string_view{"5時間", 7};
        case 6: return std::string_view{"6時間", 7};
        default: return std::nullopt;
    }
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_expected_ash_fall_time_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_expected_ash_fall_time_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
