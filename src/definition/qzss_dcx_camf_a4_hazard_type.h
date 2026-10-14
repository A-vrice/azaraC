#pragma once
// AUTO-GENERATED from azarashi 0.17.1 with CI-CD
// Source module : azarashi.definitions.camf.a4_hazard_category_and_type
// Variable      : qzss_dcx_camf_a4_hazard_type
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

inline constexpr uint8_t QZSS_DCX_CAMF_A4_HAZARD_TYPE_BASE = 0;
inline constexpr uint8_t QZSS_DCX_CAMF_A4_HAZARD_TYPE_SIZE = 114;
#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_A4_HAZARD_TYPE_POOL[] = "Not use\000Air strik\000Attack on IT system\000Attack with nuclear weapon\000Biological\000Chemical\000Explosive\000Meteorite impac\000Missile\000Nuclear\000Nuclear power station\000Radiological\000Satellite/space re-entry debri\000Siren tes\000Acid rai\000Air \000Contaminated drinking water\000Gas lea\000Marine \000Noise \000Plague of insect\000River \000Suspended dus\000UV radi\000Conflagr\000Fire brigade deploym\000Fire gase\000Forest fir\000Fume\000Odour nuisanc\000Risk of fir\000Structure fire / Industrial fir\000Ash fa\000Avalanche ris\000Crack in the ground / sinkhol\000Debris\000Earthquak\000Geomagnetic or solar stor\000Glacial ice avalanch\000Landslid\000Lava\000Pyroclastic\000Snowdrift\000Tidal wav\000Tsunami\000Volcanic mud\000Volcano erup\000Wind / wave / storm sur\000Epizootic\000Food safety aler\000Health\000Pandemic\000Pest infest\000Risk of infec\000Building collaps\000Emergency number\000Gas supply\000Outage of IT system\000Power\000Raw sew\000Telephone line\000Black Ic\000Coastal flood\000Cold wav\000Derecho\000Drough\000Dust stor\000Floating ice / iceberg\000Floo\000Fog\000Hail\000Heat wav\000Lightn\000Pollen\000Rainfa\000Snow storm / bliz\000Snowfa\000Storm or thunderstor\000Thaw\000Tornado\000Tropical cyclone (hurricane)\000Wind chill / fros\000Tropical cyclone (typhoon)\000Dam failure or bursting of a da\000Dike failure or bursting of a dik\000Explosive ordnance disposa\000Factory\000Mine\000Bomb / ammunition discovery\000Demonstr\000Hazardous material\000Life Threatening situ\000Major ev\000Missing person / abduc\000Risk of explos\000Safety warn\000Undefined flying objec\000Unidentified anima\000Chemical\000Guerrilla\000Hija\000Shooting or danger due to weapon\000Special forces\000Terroris\000Aircraft crash\000Bridge collaps\000Dangerous goods\000Inland waterway transport\000Nautical disaster / Maritime / Marine Security\000Oil spi\000Road traffic in\000Train/rail\000Tunnel\000Test aler\000";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_A4_HAZARD_TYPE_PARENT_POOL[] = " accident\000 attack\000 flow\000 hazard\000 outage\000age\000ation\000cident\000ck\000d\000e\000ent\000ge\000ing\000ion\000k\000l\000ll\000m\000n\000pollution\000s\000t\000tion\000zard\000";
struct QZSS_DCX_CAMF_A4_HAZARD_TYPE_PARENT_Entry { uint16_t offset; uint8_t len; };
static const QZSS_DCX_CAMF_A4_HAZARD_TYPE_PARENT_Entry QZSS_DCX_CAMF_A4_HAZARD_TYPE_PARENT_TABLE[] AZARAC_PROGMEM = {
    {0u, 9u},
    {10u, 7u},
    {18u, 5u},
    {24u, 7u},
    {32u, 7u},
    {40u, 3u},
    {44u, 5u},
    {50u, 6u},
    {57u, 2u},
    {60u, 1u},
    {62u, 1u},
    {64u, 3u},
    {68u, 2u},
    {71u, 3u},
    {75u, 3u},
    {79u, 1u},
    {81u, 1u},
    {83u, 2u},
    {86u, 1u},
    {88u, 1u},
    {90u, 9u},
    {100u, 1u},
    {102u, 1u},
    {104u, 4u},
    {109u, 4u},
};
struct QZSS_DCX_CAMF_A4_HAZARD_TYPE_Entry { uint16_t offset; uint8_t len; uint8_t parent; };
static const QZSS_DCX_CAMF_A4_HAZARD_TYPE_Entry QZSS_DCX_CAMF_A4_HAZARD_TYPE_TABLE[] AZARAC_PROGMEM = {
    {0u, 7u, 9u},
    {8u, 9u, 10u},
    {18u, 19u, 21u},
    {38u, 26u, 21u},
    {65u, 10u, 3u},
    {76u, 8u, 3u},
    {85u, 9u, 3u},
    {95u, 15u, 22u},
    {111u, 7u, 1u},
    {119u, 7u, 3u},
    {127u, 21u, 0u},
    {149u, 12u, 3u},
    {162u, 30u, 21u},
    {193u, 9u, 22u},
    {203u, 8u, 19u},
    {212u, 4u, 20u},
    {217u, 27u, 255u},
    {245u, 7u, 15u},
    {253u, 7u, 20u},
    {261u, 6u, 20u},
    {268u, 16u, 21u},
    {285u, 6u, 20u},
    {292u, 13u, 22u},
    {306u, 7u, 6u},
    {314u, 8u, 6u},
    {323u, 20u, 11u},
    {344u, 9u, 21u},
    {354u, 10u, 10u},
    {365u, 4u, 21u},
    {370u, 13u, 10u},
    {384u, 11u, 10u},
    {396u, 31u, 10u},
    {428u, 6u, 17u},
    {435u, 13u, 15u},
    {449u, 29u, 10u},
    {479u, 6u, 2u},
    {486u, 9u, 10u},
    {496u, 25u, 18u},
    {522u, 20u, 10u},
    {543u, 8u, 10u},
    {552u, 4u, 2u},
    {557u, 11u, 2u},
    {569u, 9u, 21u},
    {579u, 9u, 10u},
    {589u, 7u, 255u},
    {597u, 12u, 2u},
    {610u, 12u, 23u},
    {623u, 23u, 12u},
    {647u, 9u, 255u},
    {657u, 16u, 22u},
    {674u, 6u, 3u},
    {681u, 8u, 255u},
    {690u, 11u, 6u},
    {702u, 13u, 23u},
    {716u, 16u, 10u},
    {733u, 16u, 4u},
    {750u, 10u, 4u},
    {761u, 19u, 21u},
    {781u, 5u, 4u},
    {787u, 7u, 5u},
    {795u, 14u, 4u},
    {810u, 8u, 10u},
    {819u, 13u, 13u},
    {833u, 8u, 10u},
    {842u, 7u, 255u},
    {850u, 6u, 22u},
    {857u, 9u, 18u},
    {867u, 22u, 21u},
    {890u, 4u, 9u},
    {895u, 3u, 255u},
    {899u, 4u, 255u},
    {904u, 8u, 10u},
    {913u, 6u, 13u},
    {920u, 6u, 21u},
    {927u, 6u, 17u},
    {934u, 17u, 24u},
    {952u, 6u, 17u},
    {959u, 20u, 18u},
    {980u, 4u, 13u},
    {985u, 7u, 255u},
    {993u, 28u, 255u},
    {1022u, 17u, 22u},
    {1040u, 26u, 255u},
    {1067u, 31u, 18u},
    {1099u, 33u, 10u},
    {1133u, 26u, 16u},
    {1160u, 7u, 0u},
    {1168u, 4u, 3u},
    {1173u, 27u, 255u},
    {1201u, 8u, 6u},
    {1210u, 18u, 0u},
    {1229u, 21u, 6u},
    {1251u, 8u, 11u},
    {1260u, 22u, 23u},
    {1283u, 14u, 14u},
    {1298u, 11u, 13u},
    {1310u, 22u, 22u},
    {1333u, 18u, 16u},
    {1352u, 8u, 1u},
    {1361u, 9u, 1u},
    {1371u, 4u, 8u},
    {1376u, 32u, 21u},
    {1409u, 14u, 1u},
    {1424u, 8u, 18u},
    {1433u, 14u, 255u},
    {1448u, 14u, 10u},
    {1463u, 15u, 0u},
    {1479u, 25u, 0u},
    {1505u, 46u, 255u},
    {1552u, 7u, 17u},
    {1560u, 15u, 7u},
    {1576u, 10u, 0u},
    {1587u, 6u, 0u},
    {1594u, 9u, 22u}
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_a4_hazard_type_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCX_CAMF_A4_HAZARD_TYPE_BASE || id >= QZSS_DCX_CAMF_A4_HAZARD_TYPE_BASE + QZSS_DCX_CAMF_A4_HAZARD_TYPE_SIZE) return std::nullopt;
    const char* AZARAC_PROGMEM p = reinterpret_cast<const char*>(&QZSS_DCX_CAMF_A4_HAZARD_TYPE_TABLE[id - 0u]);
    uint16_t off = pgm_read_word(p + offsetof(QZSS_DCX_CAMF_A4_HAZARD_TYPE_Entry, offset));
    uint8_t n = pgm_read_byte(p + offsetof(QZSS_DCX_CAMF_A4_HAZARD_TYPE_Entry, len));
    uint8_t pi = pgm_read_byte(p + offsetof(QZSS_DCX_CAMF_A4_HAZARD_TYPE_Entry, parent));
    if (pi == 255u) return azarac_pgm_view(QZSS_DCX_CAMF_A4_HAZARD_TYPE_POOL + off, n);
    const char* AZARAC_PROGMEM pp = reinterpret_cast<const char*>(&QZSS_DCX_CAMF_A4_HAZARD_TYPE_PARENT_TABLE[pi]);
    uint16_t poff = pgm_read_word(pp + offsetof(QZSS_DCX_CAMF_A4_HAZARD_TYPE_PARENT_Entry, offset));
    uint8_t pn = pgm_read_byte(pp + offsetof(QZSS_DCX_CAMF_A4_HAZARD_TYPE_PARENT_Entry, len));
    return azarac_pgm_join(QZSS_DCX_CAMF_A4_HAZARD_TYPE_POOL + off, n, QZSS_DCX_CAMF_A4_HAZARD_TYPE_PARENT_POOL + poff, pn);
}
#else
inline constexpr const char* QZSS_DCX_CAMF_A4_HAZARD_TYPE_TABLE[] = {
    "Not used",
    "Air strike",
    "Attack on IT systems",
    "Attack with nuclear weapons",
    "Biological hazard",
    "Chemical hazard",
    "Explosive hazard",
    "Meteorite impact",
    "Missile attack",
    "Nuclear hazard",
    "Nuclear power station accident",
    "Radiological hazard",
    "Satellite/space re-entry debris",
    "Siren test",
    "Acid rain",
    "Air pollution",
    "Contaminated drinking water",
    "Gas leak",
    "Marine pollution",
    "Noise pollution",
    "Plague of insects",
    "River pollution",
    "Suspended dust",
    "UV radiation",
    "Conflagration",
    "Fire brigade deployment",
    "Fire gases",
    "Forest fire",
    "Fumes",
    "Odour nuisance",
    "Risk of fire",
    "Structure fire / Industrial fire",
    "Ash fall",
    "Avalanche risk",
    "Crack in the ground / sinkhole",
    "Debris flow",
    "Earthquake",
    "Geomagnetic or solar storm",
    "Glacial ice avalanche",
    "Landslide",
    "Lava flow",
    "Pyroclastic flow",
    "Snowdrifts",
    "Tidal wave",
    "Tsunami",
    "Volcanic mud flow",
    "Volcano eruption",
    "Wind / wave / storm surge",
    "Epizootic",
    "Food safety alert",
    "Health hazard",
    "Pandemic",
    "Pest infestation",
    "Risk of infection",
    "Building collapse",
    "Emergency number outage",
    "Gas supply outage",
    "Outage of IT systems",
    "Power outage",
    "Raw sewage",
    "Telephone line outage",
    "Black Ice",
    "Coastal flooding",
    "Cold wave",
    "Derecho",
    "Drought",
    "Dust storm",
    "Floating ice / icebergs",
    "Flood",
    "Fog",
    "Hail",
    "Heat wave",
    "Lightning",
    "Pollens",
    "Rainfall",
    "Snow storm / blizzard",
    "Snowfall",
    "Storm or thunderstorm",
    "Thawing",
    "Tornado",
    "Tropical cyclone (hurricane)",
    "Wind chill / frost",
    "Tropical cyclone (typhoon)",
    "Dam failure or bursting of a dam",
    "Dike failure or bursting of a dike",
    "Explosive ordnance disposal",
    "Factory accident",
    "Mine hazard",
    "Bomb / ammunition discovery",
    "Demonstration",
    "Hazardous material accident",
    "Life Threatening situation",
    "Major event",
    "Missing person / abduction",
    "Risk of explosion",
    "Safety warning",
    "Undefined flying object",
    "Unidentified animal",
    "Chemical attack",
    "Guerrilla attack",
    "Hijack",
    "Shooting or danger due to weapons",
    "Special forces attack",
    "Terrorism",
    "Aircraft crash",
    "Bridge collapse",
    "Dangerous goods accident",
    "Inland waterway transport accident",
    "Nautical disaster / Maritime / Marine Security",
    "Oil spill",
    "Road traffic incident",
    "Train/rail accident",
    "Tunnel accident",
    "Test alert"
};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_a4_hazard_type_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCX_CAMF_A4_HAZARD_TYPE_BASE || id >= QZSS_DCX_CAMF_A4_HAZARD_TYPE_BASE + QZSS_DCX_CAMF_A4_HAZARD_TYPE_SIZE) return std::nullopt;
    const char* s = QZSS_DCX_CAMF_A4_HAZARD_TYPE_TABLE[id - QZSS_DCX_CAMF_A4_HAZARD_TYPE_BASE];
    return s ? std::optional<std::string_view>(std::string_view{s}) : std::nullopt;
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_a4_hazard_type_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_a4_hazard_type_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
