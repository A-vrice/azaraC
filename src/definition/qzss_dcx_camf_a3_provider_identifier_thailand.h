#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcx_camf_a3_provider_identifier_thailand
// Variable      : qzss_dcx_camf_a3_provider_identifier_thailand
// Entries       : 13
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

inline constexpr uint8_t QZSS_DCX_CAMF_A3_PROVIDER_IDENTIFIER_THAILAND_BASE = 1;
inline constexpr uint8_t QZSS_DCX_CAMF_A3_PROVIDER_IDENTIFIER_THAILAND_SIZE = 13;
#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_A3_PROVIDER_IDENTIFIER_THAILAND_POOL[] = "Department of Disaster Prevention and Mitigation\000Thai Meteorological Department\000National Disaster Warning Center\000Department of Mineral Resources\000Navy Hydrographic Department, Royal Thai Navy\000Department of Water Resources\000Royal Irrigation Department\000Department of Pollution Control\000Geo-Informatics and Space Technology Development Agency\000Electricity Generating Authority of Thailand\000Royal Forest Department\000Department of Parks, Wildlife and Plant Conservation\000Water Crisis Prevention Center\000";
struct QZSS_DCX_CAMF_A3_PROVIDER_IDENTIFIER_THAILAND_Entry { uint16_t offset; uint16_t len; };
static const QZSS_DCX_CAMF_A3_PROVIDER_IDENTIFIER_THAILAND_Entry QZSS_DCX_CAMF_A3_PROVIDER_IDENTIFIER_THAILAND_TABLE[] AZARAC_PROGMEM = {
    {0u, 48u},
    {49u, 30u},
    {80u, 32u},
    {113u, 31u},
    {145u, 45u},
    {191u, 29u},
    {221u, 27u},
    {249u, 31u},
    {281u, 55u},
    {337u, 44u},
    {382u, 23u},
    {406u, 52u},
    {459u, 30u}
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_a3_provider_identifier_thailand_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCX_CAMF_A3_PROVIDER_IDENTIFIER_THAILAND_BASE || id >= QZSS_DCX_CAMF_A3_PROVIDER_IDENTIFIER_THAILAND_BASE + QZSS_DCX_CAMF_A3_PROVIDER_IDENTIFIER_THAILAND_SIZE) return std::nullopt;
    const char* AZARAC_PROGMEM p = reinterpret_cast<const char*>(&QZSS_DCX_CAMF_A3_PROVIDER_IDENTIFIER_THAILAND_TABLE[id - 1u]);
    uint16_t off = pgm_read_word(p + offsetof(QZSS_DCX_CAMF_A3_PROVIDER_IDENTIFIER_THAILAND_Entry, offset));
    uint16_t n = pgm_read_word(p + offsetof(QZSS_DCX_CAMF_A3_PROVIDER_IDENTIFIER_THAILAND_Entry, len));
    if (n == 0) return std::nullopt;
    return azarac_pgm_view(QZSS_DCX_CAMF_A3_PROVIDER_IDENTIFIER_THAILAND_POOL + off, n);
}
#else
inline constexpr std::optional<std::string_view> QZSS_DCX_CAMF_A3_PROVIDER_IDENTIFIER_THAILAND_TABLE[] = {
    std::string_view{"Department of Disaster Prevention and Mitigation", 48},
    std::string_view{"Thai Meteorological Department", 30},
    std::string_view{"National Disaster Warning Center", 32},
    std::string_view{"Department of Mineral Resources", 31},
    std::string_view{"Navy Hydrographic Department, Royal Thai Navy", 45},
    std::string_view{"Department of Water Resources", 29},
    std::string_view{"Royal Irrigation Department", 27},
    std::string_view{"Department of Pollution Control", 31},
    std::string_view{"Geo-Informatics and Space Technology Development Agency", 55},
    std::string_view{"Electricity Generating Authority of Thailand", 44},
    std::string_view{"Royal Forest Department", 23},
    std::string_view{"Department of Parks, Wildlife and Plant Conservation", 52},
    std::string_view{"Water Crisis Prevention Center", 30}
};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_a3_provider_identifier_thailand_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCX_CAMF_A3_PROVIDER_IDENTIFIER_THAILAND_BASE || id >= QZSS_DCX_CAMF_A3_PROVIDER_IDENTIFIER_THAILAND_BASE + QZSS_DCX_CAMF_A3_PROVIDER_IDENTIFIER_THAILAND_SIZE) return std::nullopt;
    return QZSS_DCX_CAMF_A3_PROVIDER_IDENTIFIER_THAILAND_TABLE[id - QZSS_DCX_CAMF_A3_PROVIDER_IDENTIFIER_THAILAND_BASE];
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_a3_provider_identifier_thailand_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_a3_provider_identifier_thailand_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
