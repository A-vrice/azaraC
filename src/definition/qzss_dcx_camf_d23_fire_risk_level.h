#pragma once
// AUTO-GENERATED from azarashi 0.17.1 — do not edit
// azarashi.definitions.camf.d_fields → qzss_dcx_camf_d23_fire_risk_level: 5 entries, strategy switch
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
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D23_FIRE_RISK_LEVEL_C0[] = "1/5 (low or none danger). Small fires cannot be entirely ruled out, but require a high energy input. Lightning hardly ever causes a fire. Rate of spread: Generally slow. Characteristics: Surface or crawling fires, crowns of trees are not affected, topsoil does not burn. Fire-fighting: Forest fire is easy to extinguish. Behaviour: Do not carelessly discard cigarettes, tobacco products or lighters.";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D23_FIRE_RISK_LEVEL_C1[] = "2/5 (moderate danger). Local fires can start spontaneously. Lightning only rarely causes a conflagration. Rate of spread: Slow to medium. Characteristics: Surface or crawling fires, crowns of trees are rarely affected, topsoil is burnt a little or not at all. Fire-fighting: Forest fire is ordinarily easy to extinguish. Behaviour: Do not carelessly discard cigarettes, tobacco products or lighters. Always watch barbecue fires and immediately extinguish stray sparks.";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D23_FIRE_RISK_LEVEL_C2[] = "3/5 (considerable danger): Burning matches and flying sparks from barbecue fires can ignite a fire. Lightning can also trigger widespread fires. Rate of spread: High in open terrain, medium in the forest. Characteristics. Topsoil is partly burnt; individual crown fires are possible. Fire-fighting: Forest fire can be extinguished only by experts using modern equipment. Behaviour: Light barbecue fires only in existing fire places. Always watch the fire and immediately extinguish stray sparks.";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D23_FIRE_RISK_LEVEL_C3[] = "4/5 (high danger). Burning matches, flying sparks from barbecue fires and lightning will very probably ignite a fire. Rate of spread: High, including in forests. Characteristics: Intense surface fires can ignite the crowns of individual trees, spotting is possible, burning topsoil. Fire-fighting: Forest fire is difficult to extinguish and commands extensive resources. Behaviour: As a general rule, do not make any fires outdoors. Permanent fire places (concreted base) in locations designated by the authorities can be used with the utmost caution. Do not make fires in strong winds.";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D23_FIRE_RISK_LEVEL_C4[] = "5/5 (very high danger). Fires can start at any time. Rate of spread: Very high over a long period. Characteristics: Very intense burning, extensive crown fires, long-distance spotting. Fire-fighting: Forest fire is virtually impossible to extinguish. Behaviour: Do not make any fires outdoors. Follow the instructions and observe the fire bans imposed by the local authorities.";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D23_FIRE_RISK_LEVEL_PARENT_POOL[] = "Danger level \000";
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d23_fire_risk_level_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D23_FIRE_RISK_LEVEL_PARENT_POOL) + 0u, AZARAC_PGM_PTR(QZSS_DCX_CAMF_D23_FIRE_RISK_LEVEL_C0));
        case 1: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D23_FIRE_RISK_LEVEL_PARENT_POOL) + 0u, AZARAC_PGM_PTR(QZSS_DCX_CAMF_D23_FIRE_RISK_LEVEL_C1));
        case 2: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D23_FIRE_RISK_LEVEL_PARENT_POOL) + 0u, AZARAC_PGM_PTR(QZSS_DCX_CAMF_D23_FIRE_RISK_LEVEL_C2));
        case 3: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D23_FIRE_RISK_LEVEL_PARENT_POOL) + 0u, AZARAC_PGM_PTR(QZSS_DCX_CAMF_D23_FIRE_RISK_LEVEL_C3));
        case 4: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D23_FIRE_RISK_LEVEL_PARENT_POOL) + 0u, AZARAC_PGM_PTR(QZSS_DCX_CAMF_D23_FIRE_RISK_LEVEL_C4));
        default: return std::nullopt;
    }
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d23_fire_risk_level_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return std::string_view{"Danger level 1/5 (low or none danger). Small fires cannot be entirely ruled out, but require a high energy input. Lightning hardly ever causes a fire. Rate of spread: Generally slow. Characteristics: Surface or crawling fires, crowns of trees are not affected, topsoil does not burn. Fire-fighting: Forest fire is easy to extinguish. Behaviour: Do not carelessly discard cigarettes, tobacco products or lighters.", 412};
        case 1: return std::string_view{"Danger level 2/5 (moderate danger). Local fires can start spontaneously. Lightning only rarely causes a conflagration. Rate of spread: Slow to medium. Characteristics: Surface or crawling fires, crowns of trees are rarely affected, topsoil is burnt a little or not at all. Fire-fighting: Forest fire is ordinarily easy to extinguish. Behaviour: Do not carelessly discard cigarettes, tobacco products or lighters. Always watch barbecue fires and immediately extinguish stray sparks.", 481};
        case 2: return std::string_view{"Danger level 3/5 (considerable danger): Burning matches and flying sparks from barbecue fires can ignite a fire. Lightning can also trigger widespread fires. Rate of spread: High in open terrain, medium in the forest. Characteristics. Topsoil is partly burnt; individual crown fires are possible. Fire-fighting: Forest fire can be extinguished only by experts using modern equipment. Behaviour: Light barbecue fires only in existing fire places. Always watch the fire and immediately extinguish stray sparks.", 508};
        case 3: return std::string_view{"Danger level 4/5 (high danger). Burning matches, flying sparks from barbecue fires and lightning will very probably ignite a fire. Rate of spread: High, including in forests. Characteristics: Intense surface fires can ignite the crowns of individual trees, spotting is possible, burning topsoil. Fire-fighting: Forest fire is difficult to extinguish and commands extensive resources. Behaviour: As a general rule, do not make any fires outdoors. Permanent fire places (concreted base) in locations designated by the authorities can be used with the utmost caution. Do not make fires in strong winds.", 599};
        case 4: return std::string_view{"Danger level 5/5 (very high danger). Fires can start at any time. Rate of spread: Very high over a long period. Characteristics: Very intense burning, extensive crown fires, long-distance spotting. Fire-fighting: Forest fire is virtually impossible to extinguish. Behaviour: Do not make any fires outdoors. Follow the instructions and observe the fire bans imposed by the local authorities.", 390};
        default: return std::nullopt;
    }
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d23_fire_risk_level_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d23_fire_risk_level_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
