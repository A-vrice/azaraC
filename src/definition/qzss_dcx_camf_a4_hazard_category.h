#pragma once
// AUTO-GENERATED from azarashi 0.17.1 — do not edit
// azarashi.definitions.camf.a4_hazard_category_and_type → qzss_dcx_camf_a4_hazard_category: 114 entries, strategy array
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

inline constexpr uint8_t QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_BASE = 0;
inline constexpr uint8_t QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_SIZE = 114;
#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_POOL[] = "Not used\000C\000C\000C\000C\000C\000C\000C\000C\000C\000C\000C\000C\000C\000E\000E\000E\000E\000E\000E\000E\000E\000E\000E\000FIRE\000FIRE\000FIRE\000FIRE\000FIRE\000FIRE\000FIRE\000FIRE\000GEO\000GEO\000GEO\000GEO\000GEO\000GEO\000GEO\000GEO\000GEO\000GEO\000GEO\000GEO\000GEO\000GEO\000GEO\000GEO\000H\000H\000H\000H\000H\000H\000I\000I\000I\000I\000I\000I\000I\000MET\000MET\000MET\000MET\000MET\000MET\000MET\000MET\000MET\000MET\000MET\000MET\000MET\000MET\000MET\000MET\000MET\000MET\000MET\000MET\000MET\000MET\000R\000R\000R\000R\000R\000S\000S\000S\000S\000S\000S\000S\000S\000S\000S\000S\000S\000S\000S\000S\000S\000T\000T\000T\000T\000T\000T\000T\000T\000T\000OTHER\000";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_PARENT_POOL[] = "AFETY\000BRNE\000EALTH\000ECURITY\000ESCUE\000NFRASTRUCTURE\000NVIRONMENT\000RANSPORT\000";
struct QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_PARENT_Entry { uint16_t offset; };
static const QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_PARENT_Entry QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_PARENT_TABLE[] AZARAC_PROGMEM = {
    {0u},
    {6u},
    {11u},
    {17u},
    {25u},
    {31u},
    {45u},
    {56u},
};
struct QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_Entry { uint16_t offset; uint8_t parent; };
static const QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_Entry QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_TABLE[] AZARAC_PROGMEM = {
    {0u, 255u},
    {9u, 1u},
    {11u, 1u},
    {13u, 1u},
    {15u, 1u},
    {17u, 1u},
    {19u, 1u},
    {21u, 1u},
    {23u, 1u},
    {25u, 1u},
    {27u, 1u},
    {29u, 1u},
    {31u, 1u},
    {33u, 1u},
    {35u, 6u},
    {37u, 6u},
    {39u, 6u},
    {41u, 6u},
    {43u, 6u},
    {45u, 6u},
    {47u, 6u},
    {49u, 6u},
    {51u, 6u},
    {53u, 6u},
    {55u, 255u},
    {60u, 255u},
    {65u, 255u},
    {70u, 255u},
    {75u, 255u},
    {80u, 255u},
    {85u, 255u},
    {90u, 255u},
    {95u, 255u},
    {99u, 255u},
    {103u, 255u},
    {107u, 255u},
    {111u, 255u},
    {115u, 255u},
    {119u, 255u},
    {123u, 255u},
    {127u, 255u},
    {131u, 255u},
    {135u, 255u},
    {139u, 255u},
    {143u, 255u},
    {147u, 255u},
    {151u, 255u},
    {155u, 255u},
    {159u, 2u},
    {161u, 2u},
    {163u, 2u},
    {165u, 2u},
    {167u, 2u},
    {169u, 2u},
    {171u, 5u},
    {173u, 5u},
    {175u, 5u},
    {177u, 5u},
    {179u, 5u},
    {181u, 5u},
    {183u, 5u},
    {185u, 255u},
    {189u, 255u},
    {193u, 255u},
    {197u, 255u},
    {201u, 255u},
    {205u, 255u},
    {209u, 255u},
    {213u, 255u},
    {217u, 255u},
    {221u, 255u},
    {225u, 255u},
    {229u, 255u},
    {233u, 255u},
    {237u, 255u},
    {241u, 255u},
    {245u, 255u},
    {249u, 255u},
    {253u, 255u},
    {257u, 255u},
    {261u, 255u},
    {265u, 255u},
    {269u, 255u},
    {273u, 4u},
    {275u, 4u},
    {277u, 4u},
    {279u, 4u},
    {281u, 4u},
    {283u, 0u},
    {285u, 0u},
    {287u, 0u},
    {289u, 0u},
    {291u, 0u},
    {293u, 0u},
    {295u, 0u},
    {297u, 0u},
    {299u, 0u},
    {301u, 0u},
    {303u, 3u},
    {305u, 3u},
    {307u, 3u},
    {309u, 3u},
    {311u, 3u},
    {313u, 3u},
    {315u, 7u},
    {317u, 7u},
    {319u, 7u},
    {321u, 7u},
    {323u, 7u},
    {325u, 7u},
    {327u, 7u},
    {329u, 7u},
    {331u, 7u},
    {333u, 255u}
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_a4_hazard_category_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_BASE || id >= QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_BASE + QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_SIZE) return std::nullopt;
    azarac_pgm_ptr p = AZARAC_PGM_PTR(QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_TABLE) + static_cast<size_t>(id - 0u) * sizeof(QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_Entry);
    uint16_t off = azarac_read_word(p, offsetof(QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_Entry, offset));
    uint8_t pi = azarac_read_byte(p, offsetof(QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_Entry, parent));
    if (pi == 255u) return azarac_pgm_view_z(AZARAC_PGM_PTR(QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_POOL) + off);
    azarac_pgm_ptr pp = AZARAC_PGM_PTR(QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_PARENT_TABLE) + static_cast<size_t>(pi) * sizeof(QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_PARENT_Entry);
    uint16_t poff = azarac_read_word(pp, offsetof(QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_PARENT_Entry, offset));
    return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_POOL) + off, AZARAC_PGM_PTR(QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_PARENT_POOL) + poff);
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
