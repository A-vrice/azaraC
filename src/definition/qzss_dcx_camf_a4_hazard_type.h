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
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_A4_HAZARD_TYPE_POOL[] = "Not used\000Air strike\000Attack on IT systems\000Attack with nuclear weapons\000Biological\000Chemical\000Explosive\000Meteorite impact\000Missile\000Nuclear\000Nuclear power station\000Radiological\000Satellite/space re-entry debris\000Siren test\000Acid rain\000Air\000Contaminated drinking water\000Gas leak\000Marine\000Noise\000Plague of insects\000River\000Suspended dust\000UV radi\000Conflagr\000Fire brigade deployment\000Fire gases\000Forest fire\000Fumes\000Odour nuisance\000Risk of fire\000Structure fire / Industrial fire\000Ash fall\000Avalanche risk\000Crack in the ground / sinkhole\000Debris\000Earthquake\000Geomagnetic or solar storm\000Glacial ice avalanche\000Landslide\000Lava\000Pyroclastic\000Snowdrifts\000Tidal wave\000Tsunami\000Volcanic mud\000Volcano erup\000Wind / wave / storm surge\000Epizootic\000Food safety alert\000Health\000Pandemic\000Pest infest\000Risk of infec\000Building collapse\000Emergency number\000Gas supply\000Outage of IT systems\000Power\000Raw sewage\000Telephone line\000Black Ice\000Coastal flooding\000Cold wave\000Derecho\000Drought\000Dust storm\000Floating ice / icebergs\000Flood\000Fog\000Hail\000Heat wave\000Lightning\000Pollens\000Rainfall\000Snow storm / bliz\000Snowfall\000Storm or thunderstorm\000Thawing\000Tornado\000Tropical cyclone (hurricane)\000Wind chill / frost\000Tropical cyclone (typhoon)\000Dam failure or bursting of a dam\000Dike failure or bursting of a dike\000Explosive ordnance disposal\000Factory\000Mine\000Bomb / ammunition discovery\000Demonstr\000Hazardous material\000Life Threatening situ\000Major event\000Missing person / abduc\000Risk of explosion\000Safety warning\000Undefined flying object\000Unidentified animal\000Chemical\000Guerrilla\000Hijack\000Shooting or danger due to weapons\000Special forces\000Terrorism\000Aircraft crash\000Bridge collapse\000Dangerous goods\000Inland waterway transport\000Nautical disaster / Maritime / Marine Security\000Oil spill\000Road traffic in\000Train/rail\000Tunnel\000Test alert\000";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_A4_HAZARD_TYPE_PARENT_POOL[] = " accident\000 attack\000 flow\000 hazard\000 outage\000 pollution\000ation\000cident\000tion\000zard\000";
struct QZSS_DCX_CAMF_A4_HAZARD_TYPE_PARENT_Entry { uint16_t offset; };
static const QZSS_DCX_CAMF_A4_HAZARD_TYPE_PARENT_Entry QZSS_DCX_CAMF_A4_HAZARD_TYPE_PARENT_TABLE[] AZARAC_PROGMEM = {
    {0u},
    {10u},
    {18u},
    {24u},
    {32u},
    {40u},
    {51u},
    {57u},
    {64u},
    {69u},
};
struct QZSS_DCX_CAMF_A4_HAZARD_TYPE_Entry { uint16_t offset; uint8_t parent; };
static const QZSS_DCX_CAMF_A4_HAZARD_TYPE_Entry QZSS_DCX_CAMF_A4_HAZARD_TYPE_TABLE[] AZARAC_PROGMEM = {
    {0u, 255u},
    {9u, 255u},
    {20u, 255u},
    {41u, 255u},
    {69u, 3u},
    {80u, 3u},
    {89u, 3u},
    {99u, 255u},
    {116u, 1u},
    {124u, 3u},
    {132u, 0u},
    {154u, 3u},
    {167u, 255u},
    {199u, 255u},
    {210u, 255u},
    {220u, 5u},
    {224u, 255u},
    {252u, 255u},
    {261u, 5u},
    {268u, 5u},
    {274u, 255u},
    {292u, 5u},
    {298u, 255u},
    {313u, 6u},
    {321u, 6u},
    {330u, 255u},
    {354u, 255u},
    {365u, 255u},
    {377u, 255u},
    {383u, 255u},
    {398u, 255u},
    {411u, 255u},
    {444u, 255u},
    {453u, 255u},
    {468u, 255u},
    {499u, 2u},
    {506u, 255u},
    {517u, 255u},
    {544u, 255u},
    {566u, 255u},
    {576u, 2u},
    {581u, 2u},
    {593u, 255u},
    {604u, 255u},
    {615u, 255u},
    {623u, 2u},
    {636u, 8u},
    {649u, 255u},
    {675u, 255u},
    {685u, 255u},
    {703u, 3u},
    {710u, 255u},
    {719u, 6u},
    {731u, 8u},
    {745u, 255u},
    {763u, 4u},
    {780u, 4u},
    {791u, 255u},
    {812u, 4u},
    {818u, 255u},
    {829u, 4u},
    {844u, 255u},
    {854u, 255u},
    {871u, 255u},
    {881u, 255u},
    {889u, 255u},
    {897u, 255u},
    {908u, 255u},
    {932u, 255u},
    {938u, 255u},
    {942u, 255u},
    {947u, 255u},
    {957u, 255u},
    {967u, 255u},
    {975u, 255u},
    {984u, 9u},
    {1002u, 255u},
    {1011u, 255u},
    {1033u, 255u},
    {1041u, 255u},
    {1049u, 255u},
    {1078u, 255u},
    {1097u, 255u},
    {1124u, 255u},
    {1157u, 255u},
    {1192u, 255u},
    {1220u, 0u},
    {1228u, 3u},
    {1233u, 255u},
    {1261u, 6u},
    {1270u, 0u},
    {1289u, 6u},
    {1311u, 255u},
    {1323u, 8u},
    {1346u, 255u},
    {1364u, 255u},
    {1379u, 255u},
    {1403u, 255u},
    {1423u, 1u},
    {1432u, 1u},
    {1442u, 255u},
    {1449u, 255u},
    {1483u, 1u},
    {1498u, 255u},
    {1508u, 255u},
    {1523u, 255u},
    {1539u, 0u},
    {1555u, 0u},
    {1581u, 255u},
    {1628u, 255u},
    {1638u, 7u},
    {1654u, 0u},
    {1665u, 0u},
    {1672u, 255u}
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_a4_hazard_type_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCX_CAMF_A4_HAZARD_TYPE_BASE || id >= QZSS_DCX_CAMF_A4_HAZARD_TYPE_BASE + QZSS_DCX_CAMF_A4_HAZARD_TYPE_SIZE) return std::nullopt;
    azarac_pgm_ptr p = AZARAC_PGM_PTR(QZSS_DCX_CAMF_A4_HAZARD_TYPE_TABLE) + static_cast<size_t>(id - 0u) * sizeof(QZSS_DCX_CAMF_A4_HAZARD_TYPE_Entry);
    uint16_t off = azarac_read_word(p, offsetof(QZSS_DCX_CAMF_A4_HAZARD_TYPE_Entry, offset));
    uint8_t pi = azarac_read_byte(p, offsetof(QZSS_DCX_CAMF_A4_HAZARD_TYPE_Entry, parent));
    if (pi == 255u) return azarac_pgm_view_z(AZARAC_PGM_PTR(QZSS_DCX_CAMF_A4_HAZARD_TYPE_POOL) + off);
    azarac_pgm_ptr pp = AZARAC_PGM_PTR(QZSS_DCX_CAMF_A4_HAZARD_TYPE_PARENT_TABLE) + static_cast<size_t>(pi) * sizeof(QZSS_DCX_CAMF_A4_HAZARD_TYPE_PARENT_Entry);
    uint16_t poff = azarac_read_word(pp, offsetof(QZSS_DCX_CAMF_A4_HAZARD_TYPE_PARENT_Entry, offset));
    return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCX_CAMF_A4_HAZARD_TYPE_POOL) + off, AZARAC_PGM_PTR(QZSS_DCX_CAMF_A4_HAZARD_TYPE_PARENT_POOL) + poff);
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
