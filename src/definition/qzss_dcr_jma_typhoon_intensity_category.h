#pragma once
// AUTO-GENERATED from azarashi 0.16.4 with CI-CD
// Source module : qzss_dcr_jma_typhoon_intensity_category
// Variable      : qzss_dcr_jma_typhoon_intensity_category
// Entries       : 5
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

#if (AZARAC_ENABLE_TYPHOON)

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_typhoon_intensity_category_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: { static const char AZARAC_PROGMEM s[] = "なし"; return azarac_pgm_view(s, 6); }
        case 1: { static const char AZARAC_PROGMEM s[] = "強い"; return azarac_pgm_view(s, 6); }
        case 2: { static const char AZARAC_PROGMEM s[] = "非常に強い"; return azarac_pgm_view(s, 15); }
        case 3: { static const char AZARAC_PROGMEM s[] = "猛烈な"; return azarac_pgm_view(s, 9); }
        case 15: { static const char AZARAC_PROGMEM s[] = "その他の強さ階級分類"; return azarac_pgm_view(s, 30); }
        default: return std::nullopt;
    }
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_typhoon_intensity_category_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return std::string_view{"なし", 6};
        case 1: return std::string_view{"強い", 6};
        case 2: return std::string_view{"非常に強い", 15};
        case 3: return std::string_view{"猛烈な", 9};
        case 15: return std::string_view{"その他の強さ階級分類", 30};
        default: return std::nullopt;
    }
}
#endif

#else

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_typhoon_intensity_category_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}

#endif

} // namespace def
} // namespace azaraC
