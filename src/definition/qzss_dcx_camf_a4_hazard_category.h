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
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_POOL[] = "Not used\000E\000E\000E\000E\000E\000E\000E\000E\000E\000E\000E\000E\000E\000T\000T\000T\000T\000T\000T\000T\000T\000T\000T\000FIRE\000FIRE\000FIRE\000FIRE\000FIRE\000FIRE\000FIRE\000FIRE\000GEO\000GEO\000GEO\000GEO\000GEO\000GEO\000GEO\000GEO\000GEO\000GEO\000GEO\000GEO\000GEO\000GEO\000GEO\000GEO\000H\000H\000H\000H\000H\000H\000E\000E\000E\000E\000E\000E\000E\000MET\000MET\000MET\000MET\000MET\000MET\000MET\000MET\000MET\000MET\000MET\000MET\000MET\000MET\000MET\000MET\000MET\000MET\000MET\000MET\000MET\000MET\000E\000E\000E\000E\000E\000Y\000Y\000Y\000Y\000Y\000Y\000Y\000Y\000Y\000Y\000Y\000Y\000Y\000Y\000Y\000Y\000T\000T\000T\000T\000T\000T\000T\000T\000T\000OTHER\000";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_PARENT_POOL[] = "CBRN\000ENVIRONMEN\000HEALT\000INFRASTRUCTUR\000RESCU\000SAFET\000SECURIT\000TRANSPOR\000";
struct QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_PARENT_Entry { uint16_t offset; uint8_t len; };
static const QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_PARENT_Entry QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_PARENT_TABLE[] AZARAC_PROGMEM = {
    {0u, 4u},
    {5u, 10u},
    {16u, 5u},
    {22u, 13u},
    {36u, 5u},
    {42u, 5u},
    {48u, 7u},
    {56u, 8u},
};
struct QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_Entry { uint16_t offset; uint8_t len; uint8_t parent; };
static const QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_Entry QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_TABLE[] AZARAC_PROGMEM = {
    {0u, 8u, 255u},
    {9u, 1u, 0u},
    {11u, 1u, 0u},
    {13u, 1u, 0u},
    {15u, 1u, 0u},
    {17u, 1u, 0u},
    {19u, 1u, 0u},
    {21u, 1u, 0u},
    {23u, 1u, 0u},
    {25u, 1u, 0u},
    {27u, 1u, 0u},
    {29u, 1u, 0u},
    {31u, 1u, 0u},
    {33u, 1u, 0u},
    {35u, 1u, 1u},
    {37u, 1u, 1u},
    {39u, 1u, 1u},
    {41u, 1u, 1u},
    {43u, 1u, 1u},
    {45u, 1u, 1u},
    {47u, 1u, 1u},
    {49u, 1u, 1u},
    {51u, 1u, 1u},
    {53u, 1u, 1u},
    {55u, 4u, 255u},
    {60u, 4u, 255u},
    {65u, 4u, 255u},
    {70u, 4u, 255u},
    {75u, 4u, 255u},
    {80u, 4u, 255u},
    {85u, 4u, 255u},
    {90u, 4u, 255u},
    {95u, 3u, 255u},
    {99u, 3u, 255u},
    {103u, 3u, 255u},
    {107u, 3u, 255u},
    {111u, 3u, 255u},
    {115u, 3u, 255u},
    {119u, 3u, 255u},
    {123u, 3u, 255u},
    {127u, 3u, 255u},
    {131u, 3u, 255u},
    {135u, 3u, 255u},
    {139u, 3u, 255u},
    {143u, 3u, 255u},
    {147u, 3u, 255u},
    {151u, 3u, 255u},
    {155u, 3u, 255u},
    {159u, 1u, 2u},
    {161u, 1u, 2u},
    {163u, 1u, 2u},
    {165u, 1u, 2u},
    {167u, 1u, 2u},
    {169u, 1u, 2u},
    {171u, 1u, 3u},
    {173u, 1u, 3u},
    {175u, 1u, 3u},
    {177u, 1u, 3u},
    {179u, 1u, 3u},
    {181u, 1u, 3u},
    {183u, 1u, 3u},
    {185u, 3u, 255u},
    {189u, 3u, 255u},
    {193u, 3u, 255u},
    {197u, 3u, 255u},
    {201u, 3u, 255u},
    {205u, 3u, 255u},
    {209u, 3u, 255u},
    {213u, 3u, 255u},
    {217u, 3u, 255u},
    {221u, 3u, 255u},
    {225u, 3u, 255u},
    {229u, 3u, 255u},
    {233u, 3u, 255u},
    {237u, 3u, 255u},
    {241u, 3u, 255u},
    {245u, 3u, 255u},
    {249u, 3u, 255u},
    {253u, 3u, 255u},
    {257u, 3u, 255u},
    {261u, 3u, 255u},
    {265u, 3u, 255u},
    {269u, 3u, 255u},
    {273u, 1u, 4u},
    {275u, 1u, 4u},
    {277u, 1u, 4u},
    {279u, 1u, 4u},
    {281u, 1u, 4u},
    {283u, 1u, 5u},
    {285u, 1u, 5u},
    {287u, 1u, 5u},
    {289u, 1u, 5u},
    {291u, 1u, 5u},
    {293u, 1u, 5u},
    {295u, 1u, 5u},
    {297u, 1u, 5u},
    {299u, 1u, 5u},
    {301u, 1u, 5u},
    {303u, 1u, 6u},
    {305u, 1u, 6u},
    {307u, 1u, 6u},
    {309u, 1u, 6u},
    {311u, 1u, 6u},
    {313u, 1u, 6u},
    {315u, 1u, 7u},
    {317u, 1u, 7u},
    {319u, 1u, 7u},
    {321u, 1u, 7u},
    {323u, 1u, 7u},
    {325u, 1u, 7u},
    {327u, 1u, 7u},
    {329u, 1u, 7u},
    {331u, 1u, 7u},
    {333u, 5u, 255u}
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_a4_hazard_category_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_BASE || id >= QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_BASE + QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_SIZE) return std::nullopt;
    const char* AZARAC_PROGMEM p = reinterpret_cast<const char*>(&QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_TABLE[id - 0u]);
    uint16_t off = pgm_read_word(p + offsetof(QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_Entry, offset));
    uint8_t n = pgm_read_byte(p + offsetof(QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_Entry, len));
    uint8_t pi = pgm_read_byte(p + offsetof(QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_Entry, parent));
    if (pi == 255u) return azarac_pgm_view(QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_POOL + off, n);
    const char* AZARAC_PROGMEM pp = reinterpret_cast<const char*>(&QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_PARENT_TABLE[pi]);
    uint16_t poff = pgm_read_word(pp + offsetof(QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_PARENT_Entry, offset));
    uint8_t pn = pgm_read_byte(pp + offsetof(QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_PARENT_Entry, len));
    return azarac_pgm_join(QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_PARENT_POOL + poff, pn, QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_POOL + off, n);
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
