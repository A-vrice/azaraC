#pragma once
// AUTO-GENERATED from azarashi 0.16.4 with CI-CD
// Source module : qzss_dcr_jma_tsunami_height
// Variable      : qzss_dcr_jma_tsunami_height
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

#if (AZARAC_ENABLE_TSUNAMI)

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_tsunami_height_lookup(uint8_t id) noexcept {
    switch (id) {
        case 1: { static const char AZARAC_PROGMEM s[] = "0.2m未満"; return azarac_pgm_view(s, 10); }
        case 2: { static const char AZARAC_PROGMEM s[] = "1m"; return azarac_pgm_view(s, 2); }
        case 3: { static const char AZARAC_PROGMEM s[] = "3m"; return azarac_pgm_view(s, 2); }
        case 4: { static const char AZARAC_PROGMEM s[] = "5m"; return azarac_pgm_view(s, 2); }
        case 5: { static const char AZARAC_PROGMEM s[] = "10m"; return azarac_pgm_view(s, 3); }
        case 6: { static const char AZARAC_PROGMEM s[] = "10m超"; return azarac_pgm_view(s, 6); }
        case 14: { static const char AZARAC_PROGMEM s[] = "不明"; return azarac_pgm_view(s, 6); }
        case 15: { static const char AZARAC_PROGMEM s[] = "その他の津波の高さ"; return azarac_pgm_view(s, 27); }
        default: return std::nullopt;
    }
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_tsunami_height_lookup(uint8_t id) noexcept {
    switch (id) {
        case 1: return std::string_view{"0.2m未満", 10};
        case 2: return std::string_view{"1m", 2};
        case 3: return std::string_view{"3m", 2};
        case 4: return std::string_view{"5m", 2};
        case 5: return std::string_view{"10m", 3};
        case 6: return std::string_view{"10m超", 6};
        case 14: return std::string_view{"不明", 6};
        case 15: return std::string_view{"その他の津波の高さ", 27};
        default: return std::nullopt;
    }
}
#endif

#else

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_tsunami_height_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}

#endif

} // namespace def
} // namespace azaraC
