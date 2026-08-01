#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcx_camf_a3_provider_identifier_australia
// Variable      : qzss_dcx_camf_a3_provider_identifier_australia
// Entries       : 12
// Strategy      : array

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

inline constexpr uint8_t QZSS_DCX_CAMF_A3_PROVIDER_IDENTIFIER_AUSTRALIA_BASE = 1;
inline constexpr uint8_t QZSS_DCX_CAMF_A3_PROVIDER_IDENTIFIER_AUSTRALIA_SIZE = 12;
#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_A3_PROVIDER_IDENTIFIER_AUSTRALIA_POOL[] = "National Emergency Management Agency\0Bureau of Meteorology\0Australian Climate Service\0Geoscience Australia\0Commonwealth Scientific and Industrial Research Organisation\0Australian Bureau of Statistics\0Resilience New South Wales\0State Emergency Service New South Wales\0New South Wales Rural Fire Service\0Joint Australian Tsunami Warning Centre\0Flood Knowledge Centre\0Australian Broadcasting Corporation\0";
struct QZSS_DCX_CAMF_A3_PROVIDER_IDENTIFIER_AUSTRALIA_Entry { uint16_t offset; uint16_t len; };
static const QZSS_DCX_CAMF_A3_PROVIDER_IDENTIFIER_AUSTRALIA_Entry QZSS_DCX_CAMF_A3_PROVIDER_IDENTIFIER_AUSTRALIA_TABLE[] AZARAC_PROGMEM = {
    {0u, 36u},
    {37u, 21u},
    {59u, 26u},
    {86u, 20u},
    {107u, 60u},
    {168u, 31u},
    {200u, 26u},
    {227u, 39u},
    {267u, 34u},
    {302u, 39u},
    {342u, 22u},
    {365u, 35u}
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_a3_provider_identifier_australia_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCX_CAMF_A3_PROVIDER_IDENTIFIER_AUSTRALIA_BASE || id >= QZSS_DCX_CAMF_A3_PROVIDER_IDENTIFIER_AUSTRALIA_BASE + QZSS_DCX_CAMF_A3_PROVIDER_IDENTIFIER_AUSTRALIA_SIZE) return std::nullopt;
    const char* AZARAC_PROGMEM p = reinterpret_cast<const char*>(&QZSS_DCX_CAMF_A3_PROVIDER_IDENTIFIER_AUSTRALIA_TABLE[id - 1u]);
    uint16_t off = pgm_read_word(p + offsetof(QZSS_DCX_CAMF_A3_PROVIDER_IDENTIFIER_AUSTRALIA_Entry, offset));
    uint16_t n = pgm_read_word(p + offsetof(QZSS_DCX_CAMF_A3_PROVIDER_IDENTIFIER_AUSTRALIA_Entry, len));
    if (n == 0) return std::nullopt;
    return azarac_pgm_view(QZSS_DCX_CAMF_A3_PROVIDER_IDENTIFIER_AUSTRALIA_POOL + off, n);
}
#else
inline constexpr std::optional<std::string_view> QZSS_DCX_CAMF_A3_PROVIDER_IDENTIFIER_AUSTRALIA_TABLE[] = {
    std::string_view{"National Emergency Management Agency", 36},
    std::string_view{"Bureau of Meteorology", 21},
    std::string_view{"Australian Climate Service", 26},
    std::string_view{"Geoscience Australia", 20},
    std::string_view{"Commonwealth Scientific and Industrial Research Organisation", 60},
    std::string_view{"Australian Bureau of Statistics", 31},
    std::string_view{"Resilience New South Wales", 26},
    std::string_view{"State Emergency Service New South Wales", 39},
    std::string_view{"New South Wales Rural Fire Service", 34},
    std::string_view{"Joint Australian Tsunami Warning Centre", 39},
    std::string_view{"Flood Knowledge Centre", 22},
    std::string_view{"Australian Broadcasting Corporation", 35}
};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_a3_provider_identifier_australia_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCX_CAMF_A3_PROVIDER_IDENTIFIER_AUSTRALIA_BASE || id >= QZSS_DCX_CAMF_A3_PROVIDER_IDENTIFIER_AUSTRALIA_BASE + QZSS_DCX_CAMF_A3_PROVIDER_IDENTIFIER_AUSTRALIA_SIZE) return std::nullopt;
    return QZSS_DCX_CAMF_A3_PROVIDER_IDENTIFIER_AUSTRALIA_TABLE[id - QZSS_DCX_CAMF_A3_PROVIDER_IDENTIFIER_AUSTRALIA_BASE];
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_a3_provider_identifier_australia_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_a3_provider_identifier_australia_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
