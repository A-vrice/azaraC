#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcx_camf_a3_provider_identifier_japan
// Variable      : qzss_dcx_camf_a3_provider_identifier_japan
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
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_a3_provider_identifier_japan_lookup(uint8_t id) noexcept {
    switch (id) {
        case 1: { static const char AZARAC_PROGMEM s[] = "Foundation for MultiMedia Communications"; return azarac_pgm_view(s, 40); }
        case 2: { static const char AZARAC_PROGMEM s[] = "Fire and Disaster Management Agency"; return azarac_pgm_view(s, 35); }
        case 3: { static const char AZARAC_PROGMEM s[] = "Related Ministries"; return azarac_pgm_view(s, 18); }
        case 4: { static const char AZARAC_PROGMEM s[] = "Local Government"; return azarac_pgm_view(s, 16); }
        default: return std::nullopt;
    }
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_a3_provider_identifier_japan_lookup(uint8_t id) noexcept {
    switch (id) {
        case 1: return std::string_view{"Foundation for MultiMedia Communications", 40};
        case 2: return std::string_view{"Fire and Disaster Management Agency", 35};
        case 3: return std::string_view{"Related Ministries", 18};
        case 4: return std::string_view{"Local Government", 16};
        default: return std::nullopt;
    }
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_a3_provider_identifier_japan_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_a3_provider_identifier_japan_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
