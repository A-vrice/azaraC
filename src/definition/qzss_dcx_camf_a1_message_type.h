#pragma once
// AUTO-GENERATED from azarashi 0.17.1 — do not edit
// azarashi.definitions.camf.a1_message_type → qzss_dcx_camf_a1_message_type: 4 entries, strategy switch
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
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_A1_MESSAGE_TYPE_C0[] = "Test";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_A1_MESSAGE_TYPE_C1[] = "Alert";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_A1_MESSAGE_TYPE_C2[] = "Update";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_A1_MESSAGE_TYPE_C3[] = "All Clear";
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_a1_message_type_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCX_CAMF_A1_MESSAGE_TYPE_C0), 4);
        case 1: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCX_CAMF_A1_MESSAGE_TYPE_C1), 5);
        case 2: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCX_CAMF_A1_MESSAGE_TYPE_C2), 6);
        case 3: return azarac_pgm_view(AZARAC_PGM_PTR(QZSS_DCX_CAMF_A1_MESSAGE_TYPE_C3), 9);
        default: return std::nullopt;
    }
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_a1_message_type_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return std::string_view{"Test", 4};
        case 1: return std::string_view{"Alert", 5};
        case 2: return std::string_view{"Update", 6};
        case 3: return std::string_view{"All Clear", 9};
        default: return std::nullopt;
    }
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_a1_message_type_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_a1_message_type_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
