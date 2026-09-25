#pragma once
// AUTO-GENERATED from azarashi 0.16.4 with CI-CD
// Source module : qzss_dcx_camf_a4_hazard_category_and_type
// Variable      : qzss_dcx_camf_a4_hazard_type
// Entries       : 113
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

inline constexpr uint8_t QZSS_DCX_CAMF_A4_HAZARD_TYPE_BASE = 1;
inline constexpr uint8_t QZSS_DCX_CAMF_A4_HAZARD_TYPE_SIZE = 113;
#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_A4_HAZARD_TYPE_POOL[] = "Air strike\000Attack on IT systems\000Attack with nuclear weapons\000Biological hazard\000Chemical hazard\000Explosive hazard\000Meteorite impact\000Missile attack\000Nuclear hazard\000Nuclear power station accident\000Radiological hazard\000Satellite/space re-entry debris\000Siren test\000Acid rain\000Air pollution\000Contaminated drinking water\000Gas leak\000Marine pollution\000Noise pollution\000Plague of insects\000River pollution\000Suspended dust\000UV radiation\000Conflagration\000Fire brigade deployment\000Fire gases\000Forest fire\000Fumes\000Odour nuisance\000Risk of fire\000Structure fire / Industrial fire\000Ash fall\000Avalanche risk\000Crack in the ground / sinkhole\000Debris flow\000Earthquake\000Geomagnetic or solar storm\000Glacial ice avalanche\000Landslide\000Lava flow\000Pyroclastic flow\000Snowdrifts\000Tidal wave\000Tsunami\000Volcanic mud flow\000Volcano eruption\000Wind / wave / storm surge\000Epizootic\000Food safety alert\000Health hazard\000Pandemic\000Pest infestation\000Risk of infection\000Building collapse\000Emergency number outage\000Gas supply outage\000Outage of IT systems\000Power outage\000Raw sewage\000Telephone line outage\000Black Ice\000Coastal flooding\000Cold wave\000Derecho\000Drought\000Dust storm\000Floating ice / icebergs\000Flood\000Fog\000Hail\000Heat wave\000Lightning\000Pollens\000Rainfall\000Snow storm / blizzard\000Snowfall\000Storm or thunderstorm\000Thawing\000Tornado\000Tropical cyclone (hurricane)\000Wind chill / frost\000Tropical cyclone (typhoon)\000Dam failure or bursting of a dam\000Dike failure or bursting of a dike\000Explosive ordnance disposal\000Factory accident\000Mine hazard\000Bomb / ammunition discovery\000Demonstration\000Hazardous material accident\000Life Threatening situation\000Major event\000Missing person / abduction\000Risk of explosion\000Safety warning\000Undefined flying object\000Unidentified animal\000Chemical attack\000Guerrilla attack\000Hijack\000Shooting or danger due to weapons\000Special forces attack\000Terrorism\000Aircraft crash\000Bridge collapse\000Dangerous goods accident\000Inland waterway transport accident\000Nautical disaster / Maritime / Marine Security\000Oil spill\000Road traffic incident\000Train/rail accident\000Tunnel accident\000Test alert\000";
struct QZSS_DCX_CAMF_A4_HAZARD_TYPE_Entry { uint16_t offset; uint16_t len; };
static const QZSS_DCX_CAMF_A4_HAZARD_TYPE_Entry QZSS_DCX_CAMF_A4_HAZARD_TYPE_TABLE[] AZARAC_PROGMEM = {
    {0u, 10u},
    {11u, 20u},
    {32u, 27u},
    {60u, 17u},
    {78u, 15u},
    {94u, 16u},
    {111u, 16u},
    {128u, 14u},
    {143u, 14u},
    {158u, 30u},
    {189u, 19u},
    {209u, 31u},
    {241u, 10u},
    {252u, 9u},
    {262u, 13u},
    {276u, 27u},
    {304u, 8u},
    {313u, 16u},
    {330u, 15u},
    {346u, 17u},
    {364u, 15u},
    {380u, 14u},
    {395u, 12u},
    {408u, 13u},
    {422u, 23u},
    {446u, 10u},
    {457u, 11u},
    {469u, 5u},
    {475u, 14u},
    {490u, 12u},
    {503u, 32u},
    {536u, 8u},
    {545u, 14u},
    {560u, 30u},
    {591u, 11u},
    {603u, 10u},
    {614u, 26u},
    {641u, 21u},
    {663u, 9u},
    {673u, 9u},
    {683u, 16u},
    {700u, 10u},
    {711u, 10u},
    {722u, 7u},
    {730u, 17u},
    {748u, 16u},
    {765u, 25u},
    {791u, 9u},
    {801u, 17u},
    {819u, 13u},
    {833u, 8u},
    {842u, 16u},
    {859u, 17u},
    {877u, 17u},
    {895u, 23u},
    {919u, 17u},
    {937u, 20u},
    {958u, 12u},
    {971u, 10u},
    {982u, 21u},
    {1004u, 9u},
    {1014u, 16u},
    {1031u, 9u},
    {1041u, 7u},
    {1049u, 7u},
    {1057u, 10u},
    {1068u, 23u},
    {1092u, 5u},
    {1098u, 3u},
    {1102u, 4u},
    {1107u, 9u},
    {1117u, 9u},
    {1127u, 7u},
    {1135u, 8u},
    {1144u, 21u},
    {1166u, 8u},
    {1175u, 21u},
    {1197u, 7u},
    {1205u, 7u},
    {1213u, 28u},
    {1242u, 18u},
    {1261u, 26u},
    {1288u, 32u},
    {1321u, 34u},
    {1356u, 27u},
    {1384u, 16u},
    {1401u, 11u},
    {1413u, 27u},
    {1441u, 13u},
    {1455u, 27u},
    {1483u, 26u},
    {1510u, 11u},
    {1522u, 26u},
    {1549u, 17u},
    {1567u, 14u},
    {1582u, 23u},
    {1606u, 19u},
    {1626u, 15u},
    {1642u, 16u},
    {1659u, 6u},
    {1666u, 33u},
    {1700u, 21u},
    {1722u, 9u},
    {1732u, 14u},
    {1747u, 15u},
    {1763u, 24u},
    {1788u, 34u},
    {1823u, 46u},
    {1870u, 9u},
    {1880u, 21u},
    {1902u, 19u},
    {1922u, 15u},
    {1938u, 10u}
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_a4_hazard_type_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCX_CAMF_A4_HAZARD_TYPE_BASE || id >= QZSS_DCX_CAMF_A4_HAZARD_TYPE_BASE + QZSS_DCX_CAMF_A4_HAZARD_TYPE_SIZE) return std::nullopt;
    const char* AZARAC_PROGMEM p = reinterpret_cast<const char*>(&QZSS_DCX_CAMF_A4_HAZARD_TYPE_TABLE[id - 1u]);
    uint16_t off = pgm_read_word(p + offsetof(QZSS_DCX_CAMF_A4_HAZARD_TYPE_Entry, offset));
    uint16_t n = pgm_read_word(p + offsetof(QZSS_DCX_CAMF_A4_HAZARD_TYPE_Entry, len));
    return azarac_pgm_view(QZSS_DCX_CAMF_A4_HAZARD_TYPE_POOL + off, n);
}
#else
inline constexpr const char* QZSS_DCX_CAMF_A4_HAZARD_TYPE_TABLE[] = {
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
