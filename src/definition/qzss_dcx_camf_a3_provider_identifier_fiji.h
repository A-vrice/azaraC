#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcx_camf_a3_provider_identifier_fiji
// Variable      : qzss_dcx_camf_a3_provider_identifier_fiji
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

#if (AZARAC_ENABLE_DCX_CAMF)

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_a3_provider_identifier_fiji_lookup(uint8_t id) noexcept {
    switch (id) {
        case 1: { static const char AZARAC_PROGMEM s[] = "National Disaster Management Office"; return azarac_pgm_view(s, 35); }
        case 2: { static const char AZARAC_PROGMEM s[] = "Fiji Meteorological Service"; return azarac_pgm_view(s, 27); }
        case 3: { static const char AZARAC_PROGMEM s[] = "Hydrology Section, Fiji Water Authority"; return azarac_pgm_view(s, 39); }
        case 4: { static const char AZARAC_PROGMEM s[] = "Mineral Resources Department"; return azarac_pgm_view(s, 28); }
        case 5: { static const char AZARAC_PROGMEM s[] = "Fiji Broadcasting Corporation"; return azarac_pgm_view(s, 29); }
        default: return std::nullopt;
    }
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_a3_provider_identifier_fiji_lookup(uint8_t id) noexcept {
    switch (id) {
        case 1: return std::string_view{"National Disaster Management Office", 35};
        case 2: return std::string_view{"Fiji Meteorological Service", 27};
        case 3: return std::string_view{"Hydrology Section, Fiji Water Authority", 39};
        case 4: return std::string_view{"Mineral Resources Department", 28};
        case 5: return std::string_view{"Fiji Broadcasting Corporation", 29};
        default: return std::nullopt;
    }
}
#endif

#else

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_a3_provider_identifier_fiji_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}

#endif

} // namespace def
} // namespace azaraC
