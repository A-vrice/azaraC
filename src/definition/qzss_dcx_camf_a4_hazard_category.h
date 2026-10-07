#pragma once
// AUTO-GENERATED from azarashi 0.17.1 with CI-CD
// Source module : azarashi.definitions.camf.a4_hazard_category_and_type
// Variable      : qzss_dcx_camf_a4_hazard_category
// Entries       : 114
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

inline constexpr uint8_t QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_BASE = 0;
inline constexpr uint8_t QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_SIZE = 114;
#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_POOL[] = "Not used\000CBRNE\000CBRNE\000CBRNE\000CBRNE\000CBRNE\000CBRNE\000CBRNE\000CBRNE\000CBRNE\000CBRNE\000CBRNE\000CBRNE\000CBRNE\000ENVIRONMENT\000ENVIRONMENT\000ENVIRONMENT\000ENVIRONMENT\000ENVIRONMENT\000ENVIRONMENT\000ENVIRONMENT\000ENVIRONMENT\000ENVIRONMENT\000ENVIRONMENT\000FIRE\000FIRE\000FIRE\000FIRE\000FIRE\000FIRE\000FIRE\000FIRE\000GEO\000GEO\000GEO\000GEO\000GEO\000GEO\000GEO\000GEO\000GEO\000GEO\000GEO\000GEO\000GEO\000GEO\000GEO\000GEO\000HEALTH\000HEALTH\000HEALTH\000HEALTH\000HEALTH\000HEALTH\000INFRASTRUCTURE\000INFRASTRUCTURE\000INFRASTRUCTURE\000INFRASTRUCTURE\000INFRASTRUCTURE\000INFRASTRUCTURE\000INFRASTRUCTURE\000MET\000MET\000MET\000MET\000MET\000MET\000MET\000MET\000MET\000MET\000MET\000MET\000MET\000MET\000MET\000MET\000MET\000MET\000MET\000MET\000MET\000MET\000RESCUE\000RESCUE\000RESCUE\000RESCUE\000RESCUE\000SAFETY\000SAFETY\000SAFETY\000SAFETY\000SAFETY\000SAFETY\000SAFETY\000SAFETY\000SAFETY\000SAFETY\000SECURITY\000SECURITY\000SECURITY\000SECURITY\000SECURITY\000SECURITY\000TRANSPORT\000TRANSPORT\000TRANSPORT\000TRANSPORT\000TRANSPORT\000TRANSPORT\000TRANSPORT\000TRANSPORT\000TRANSPORT\000OTHER\000";
struct QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_Entry { uint16_t offset; uint16_t len; };
static const QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_Entry QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_TABLE[] AZARAC_PROGMEM = {
    {0u, 8u},
    {9u, 5u},
    {15u, 5u},
    {21u, 5u},
    {27u, 5u},
    {33u, 5u},
    {39u, 5u},
    {45u, 5u},
    {51u, 5u},
    {57u, 5u},
    {63u, 5u},
    {69u, 5u},
    {75u, 5u},
    {81u, 5u},
    {87u, 11u},
    {99u, 11u},
    {111u, 11u},
    {123u, 11u},
    {135u, 11u},
    {147u, 11u},
    {159u, 11u},
    {171u, 11u},
    {183u, 11u},
    {195u, 11u},
    {207u, 4u},
    {212u, 4u},
    {217u, 4u},
    {222u, 4u},
    {227u, 4u},
    {232u, 4u},
    {237u, 4u},
    {242u, 4u},
    {247u, 3u},
    {251u, 3u},
    {255u, 3u},
    {259u, 3u},
    {263u, 3u},
    {267u, 3u},
    {271u, 3u},
    {275u, 3u},
    {279u, 3u},
    {283u, 3u},
    {287u, 3u},
    {291u, 3u},
    {295u, 3u},
    {299u, 3u},
    {303u, 3u},
    {307u, 3u},
    {311u, 6u},
    {318u, 6u},
    {325u, 6u},
    {332u, 6u},
    {339u, 6u},
    {346u, 6u},
    {353u, 14u},
    {368u, 14u},
    {383u, 14u},
    {398u, 14u},
    {413u, 14u},
    {428u, 14u},
    {443u, 14u},
    {458u, 3u},
    {462u, 3u},
    {466u, 3u},
    {470u, 3u},
    {474u, 3u},
    {478u, 3u},
    {482u, 3u},
    {486u, 3u},
    {490u, 3u},
    {494u, 3u},
    {498u, 3u},
    {502u, 3u},
    {506u, 3u},
    {510u, 3u},
    {514u, 3u},
    {518u, 3u},
    {522u, 3u},
    {526u, 3u},
    {530u, 3u},
    {534u, 3u},
    {538u, 3u},
    {542u, 3u},
    {546u, 6u},
    {553u, 6u},
    {560u, 6u},
    {567u, 6u},
    {574u, 6u},
    {581u, 6u},
    {588u, 6u},
    {595u, 6u},
    {602u, 6u},
    {609u, 6u},
    {616u, 6u},
    {623u, 6u},
    {630u, 6u},
    {637u, 6u},
    {644u, 6u},
    {651u, 8u},
    {660u, 8u},
    {669u, 8u},
    {678u, 8u},
    {687u, 8u},
    {696u, 8u},
    {705u, 9u},
    {715u, 9u},
    {725u, 9u},
    {735u, 9u},
    {745u, 9u},
    {755u, 9u},
    {765u, 9u},
    {775u, 9u},
    {785u, 9u},
    {795u, 5u}
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_a4_hazard_category_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_BASE || id >= QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_BASE + QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_SIZE) return std::nullopt;
    const char* AZARAC_PROGMEM p = reinterpret_cast<const char*>(&QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_TABLE[id - 0u]);
    uint16_t off = pgm_read_word(p + offsetof(QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_Entry, offset));
    uint16_t n = pgm_read_word(p + offsetof(QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_Entry, len));
    return azarac_pgm_view(QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_POOL + off, n);
}
#else
inline constexpr const char* QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_TABLE[] = {
    "Not used",
    "CBRNE",
    "CBRNE",
    "CBRNE",
    "CBRNE",
    "CBRNE",
    "CBRNE",
    "CBRNE",
    "CBRNE",
    "CBRNE",
    "CBRNE",
    "CBRNE",
    "CBRNE",
    "CBRNE",
    "ENVIRONMENT",
    "ENVIRONMENT",
    "ENVIRONMENT",
    "ENVIRONMENT",
    "ENVIRONMENT",
    "ENVIRONMENT",
    "ENVIRONMENT",
    "ENVIRONMENT",
    "ENVIRONMENT",
    "ENVIRONMENT",
    "FIRE",
    "FIRE",
    "FIRE",
    "FIRE",
    "FIRE",
    "FIRE",
    "FIRE",
    "FIRE",
    "GEO",
    "GEO",
    "GEO",
    "GEO",
    "GEO",
    "GEO",
    "GEO",
    "GEO",
    "GEO",
    "GEO",
    "GEO",
    "GEO",
    "GEO",
    "GEO",
    "GEO",
    "GEO",
    "HEALTH",
    "HEALTH",
    "HEALTH",
    "HEALTH",
    "HEALTH",
    "HEALTH",
    "INFRASTRUCTURE",
    "INFRASTRUCTURE",
    "INFRASTRUCTURE",
    "INFRASTRUCTURE",
    "INFRASTRUCTURE",
    "INFRASTRUCTURE",
    "INFRASTRUCTURE",
    "MET",
    "MET",
    "MET",
    "MET",
    "MET",
    "MET",
    "MET",
    "MET",
    "MET",
    "MET",
    "MET",
    "MET",
    "MET",
    "MET",
    "MET",
    "MET",
    "MET",
    "MET",
    "MET",
    "MET",
    "MET",
    "MET",
    "RESCUE",
    "RESCUE",
    "RESCUE",
    "RESCUE",
    "RESCUE",
    "SAFETY",
    "SAFETY",
    "SAFETY",
    "SAFETY",
    "SAFETY",
    "SAFETY",
    "SAFETY",
    "SAFETY",
    "SAFETY",
    "SAFETY",
    "SECURITY",
    "SECURITY",
    "SECURITY",
    "SECURITY",
    "SECURITY",
    "SECURITY",
    "TRANSPORT",
    "TRANSPORT",
    "TRANSPORT",
    "TRANSPORT",
    "TRANSPORT",
    "TRANSPORT",
    "TRANSPORT",
    "TRANSPORT",
    "TRANSPORT",
    "OTHER"
};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_a4_hazard_category_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_BASE || id >= QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_BASE + QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_SIZE) return std::nullopt;
    const char* s = QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_TABLE[id - QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_BASE];
    return s ? std::optional<std::string_view>(std::string_view{s}) : std::nullopt;
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_a4_hazard_category_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_a4_hazard_category_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
