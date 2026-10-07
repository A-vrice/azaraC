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
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_A4_HAZARD_TYPE_POOL[] = "Not used\000Air strike\000Attack on IT systems\000Attack with nuclear weapons\000Biological hazard\000Chemical hazard\000Explosive hazard\000Meteorite impact\000Missile attack\000Nuclear hazard\000Nuclear power station accident\000Radiological hazard\000Satellite/space re-entry debris\000Siren test\000Acid rain\000Air pollution\000Contaminated drinking water\000Gas leak\000Marine pollution\000Noise pollution\000Plague of insects\000River pollution\000Suspended dust\000UV radiation\000Conflagration\000Fire brigade deployment\000Fire gases\000Forest fire\000Fumes\000Odour nuisance\000Risk of fire\000Structure fire / Industrial fire\000Ash fall\000Avalanche risk\000Crack in the ground / sinkhole\000Debris flow\000Earthquake\000Geomagnetic or solar storm\000Glacial ice avalanche\000Landslide\000Lava flow\000Pyroclastic flow\000Snowdrifts\000Tidal wave\000Tsunami\000Volcanic mud flow\000Volcano eruption\000Wind / wave / storm surge\000Epizootic\000Food safety alert\000Health hazard\000Pandemic\000Pest infestation\000Risk of infection\000Building collapse\000Emergency number outage\000Gas supply outage\000Outage of IT systems\000Power outage\000Raw sewage\000Telephone line outage\000Black Ice\000Coastal flooding\000Cold wave\000Derecho\000Drought\000Dust storm\000Floating ice / icebergs\000Flood\000Fog\000Hail\000Heat wave\000Lightning\000Pollens\000Rainfall\000Snow storm / blizzard\000Snowfall\000Storm or thunderstorm\000Thawing\000Tornado\000Tropical cyclone (hurricane)\000Wind chill / frost\000Tropical cyclone (typhoon)\000Dam failure or bursting of a dam\000Dike failure or bursting of a dike\000Explosive ordnance disposal\000Factory accident\000Mine hazard\000Bomb / ammunition discovery\000Demonstration\000Hazardous material accident\000Life Threatening situation\000Major event\000Missing person / abduction\000Risk of explosion\000Safety warning\000Undefined flying object\000Unidentified animal\000Chemical attack\000Guerrilla attack\000Hijack\000Shooting or danger due to weapons\000Special forces attack\000Terrorism\000Aircraft crash\000Bridge collapse\000Dangerous goods accident\000Inland waterway transport accident\000Nautical disaster / Maritime / Marine Security\000Oil spill\000Road traffic incident\000Train/rail accident\000Tunnel accident\000Test alert\000";
struct QZSS_DCX_CAMF_A4_HAZARD_TYPE_Entry { uint16_t offset; uint16_t len; };
static const QZSS_DCX_CAMF_A4_HAZARD_TYPE_Entry QZSS_DCX_CAMF_A4_HAZARD_TYPE_TABLE[] AZARAC_PROGMEM = {
    {0u, 8u},
    {9u, 10u},
    {20u, 20u},
    {41u, 27u},
    {69u, 17u},
    {87u, 15u},
    {103u, 16u},
    {120u, 16u},
    {137u, 14u},
    {152u, 14u},
    {167u, 30u},
    {198u, 19u},
    {218u, 31u},
    {250u, 10u},
    {261u, 9u},
    {271u, 13u},
    {285u, 27u},
    {313u, 8u},
    {322u, 16u},
    {339u, 15u},
    {355u, 17u},
    {373u, 15u},
    {389u, 14u},
    {404u, 12u},
    {417u, 13u},
    {431u, 23u},
    {455u, 10u},
    {466u, 11u},
    {478u, 5u},
    {484u, 14u},
    {499u, 12u},
    {512u, 32u},
    {545u, 8u},
    {554u, 14u},
    {569u, 30u},
    {600u, 11u},
    {612u, 10u},
    {623u, 26u},
    {650u, 21u},
    {672u, 9u},
    {682u, 9u},
    {692u, 16u},
    {709u, 10u},
    {720u, 10u},
    {731u, 7u},
    {739u, 17u},
    {757u, 16u},
    {774u, 25u},
    {800u, 9u},
    {810u, 17u},
    {828u, 13u},
    {842u, 8u},
    {851u, 16u},
    {868u, 17u},
    {886u, 17u},
    {904u, 23u},
    {928u, 17u},
    {946u, 20u},
    {967u, 12u},
    {980u, 10u},
    {991u, 21u},
    {1013u, 9u},
    {1023u, 16u},
    {1040u, 9u},
    {1050u, 7u},
    {1058u, 7u},
    {1066u, 10u},
    {1077u, 23u},
    {1101u, 5u},
    {1107u, 3u},
    {1111u, 4u},
    {1116u, 9u},
    {1126u, 9u},
    {1136u, 7u},
    {1144u, 8u},
    {1153u, 21u},
    {1175u, 8u},
    {1184u, 21u},
    {1206u, 7u},
    {1214u, 7u},
    {1222u, 28u},
    {1251u, 18u},
    {1270u, 26u},
    {1297u, 32u},
    {1330u, 34u},
    {1365u, 27u},
    {1393u, 16u},
    {1410u, 11u},
    {1422u, 27u},
    {1450u, 13u},
    {1464u, 27u},
    {1492u, 26u},
    {1519u, 11u},
    {1531u, 26u},
    {1558u, 17u},
    {1576u, 14u},
    {1591u, 23u},
    {1615u, 19u},
    {1635u, 15u},
    {1651u, 16u},
    {1668u, 6u},
    {1675u, 33u},
    {1709u, 21u},
    {1731u, 9u},
    {1741u, 14u},
    {1756u, 15u},
    {1772u, 24u},
    {1797u, 34u},
    {1832u, 46u},
    {1879u, 9u},
    {1889u, 21u},
    {1911u, 19u},
    {1931u, 15u},
    {1947u, 10u}
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_a4_hazard_type_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCX_CAMF_A4_HAZARD_TYPE_BASE || id >= QZSS_DCX_CAMF_A4_HAZARD_TYPE_BASE + QZSS_DCX_CAMF_A4_HAZARD_TYPE_SIZE) return std::nullopt;
    const char* AZARAC_PROGMEM p = reinterpret_cast<const char*>(&QZSS_DCX_CAMF_A4_HAZARD_TYPE_TABLE[id - 0u]);
    uint16_t off = pgm_read_word(p + offsetof(QZSS_DCX_CAMF_A4_HAZARD_TYPE_Entry, offset));
    uint16_t n = pgm_read_word(p + offsetof(QZSS_DCX_CAMF_A4_HAZARD_TYPE_Entry, len));
    return azarac_pgm_view(QZSS_DCX_CAMF_A4_HAZARD_TYPE_POOL + off, n);
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
