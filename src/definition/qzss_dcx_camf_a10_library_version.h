#pragma once
// AUTO-GENERATED from azarashi 0.17.1 — do not edit
// azarashi.definitions.camf.a10_library_version → qzss_dcx_camf_a10_library_version: 1 entries, strategy switch
// Unknown id returns nullptr — callers MUST null-check.

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
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_A10_LIBRARY_VERSION_C0[] = "#1";
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_a10_library_version_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCX_CAMF_A10_LIBRARY_VERSION_C0), 2);
        default: return std::nullopt;
    }
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_a10_library_version_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return std::string_view{"#1", 2};
        default: return std::nullopt;
    }
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_a10_library_version_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_a10_library_version_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
