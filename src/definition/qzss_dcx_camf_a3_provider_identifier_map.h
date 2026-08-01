#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcx_camf_a3_provider_identifier
// Variable      : qzss_dcx_camf_a3_provider_identifier_map
// Entries       : 0
// Strategy      : switch

// NOTE: This function may return nullptr for unknown IDs.
// Callers MUST perform a null-check before using the result.

#if defined(__AVR__)
#include "../internal/avr_std/cstdint"
#else
#include <cstdint>
#endif
#if defined(__AVR__)
#include "../internal/avr_std/optional"
#else
#include <optional>
#endif
#if defined(__AVR__)
#include "../internal/avr_std/string_view"
#else
#include <string_view>
#endif
#include "../azaraC.h"
#include "../internal/FlashString.h"

namespace azaraC {
namespace def {

#if (AZARAC_ENABLE_DCX_CAMF)

#if defined(__AVR__)
[[nodiscard]] inline const char* qzss_dcx_camf_a3_provider_identifier_map_lookup(uint8_t id) noexcept {
    (void)id;
    return nullptr;
}
#else
[[nodiscard]] inline constexpr const char* qzss_dcx_camf_a3_provider_identifier_map_lookup(uint8_t id) noexcept {
    switch (id) {
        default: return nullptr;
    }
}
#endif

#else

[[nodiscard]] inline constexpr const char* qzss_dcx_camf_a3_provider_identifier_map_lookup(uint8_t id) noexcept {
    (void)id;
    return nullptr;
}

#endif

} // namespace def
} // namespace azaraC
