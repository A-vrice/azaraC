#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcx_camf_a4_hazard_category_and_type
// Variable      : qzss_dcx_camf_a4_hazard_type
// Entries       : 113
// Strategy      : array

#include <cstdint>
#include <optional>
#include <string_view>
#include "../azaraC.h"

namespace azaraC {
namespace def {

inline constexpr std::optional<std::string_view> QZSS_DCX_CAMF_A4_HAZARD_TYPE_TABLE[] = {
    std::string_view{"Air strike", 10},
    std::string_view{"Attack on IT systems", 20},
    std::string_view{"Attack with nuclear weapons", 27},
    std::string_view{"Biological hazard", 17},
    std::string_view{"Chemical hazard", 15},
    std::string_view{"Explosive hazard", 16},
    std::string_view{"Meteorite impact", 16},
    std::string_view{"Missile attack", 14},
    std::string_view{"Nuclear hazard", 14},
    std::string_view{"Nuclear power station accident", 30},
    std::string_view{"Radiological hazard", 19},
    std::string_view{"Satellite/space re-entry debris", 31},
    std::string_view{"Siren test", 10},
    std::string_view{"Acid rain", 9},
    std::string_view{"Air pollution", 13},
    std::string_view{"Contaminated drinking water", 27},
    std::string_view{"Gas leak", 8},
    std::string_view{"Marine pollution", 16},
    std::string_view{"Noise pollution", 15},
    std::string_view{"Plague of insects", 17},
    std::string_view{"River pollution", 15},
    std::string_view{"Suspended dust", 14},
    std::string_view{"UV radiation", 12},
    std::string_view{"Conflagration", 13},
    std::string_view{"Fire brigade deployment", 23},
    std::string_view{"Fire gases", 10},
    std::string_view{"Forest fire", 11},
    std::string_view{"Fumes", 5},
    std::string_view{"Odour nuisance", 14},
    std::string_view{"Risk of fire", 12},
    std::string_view{"Structure fire / Industrial fire", 32},
    std::string_view{"Ash fall", 8},
    std::string_view{"Avalanche risk", 14},
    std::string_view{"Crack in the ground / sinkhole", 30},
    std::string_view{"Debris flow", 11},
    std::string_view{"Earthquake", 10},
    std::string_view{"Geomagnetic or solar storm", 26},
    std::string_view{"Glacial ice avalanche", 21},
    std::string_view{"Landslide", 9},
    std::string_view{"Lava flow", 9},
    std::string_view{"Pyroclastic flow", 16},
    std::string_view{"Snowdrifts", 10},
    std::string_view{"Tidal wave", 10},
    std::string_view{"Tsunami", 7},
    std::string_view{"Volcanic mud flow", 17},
    std::string_view{"Volcano eruption", 16},
    std::string_view{"Wind / wave / storm surge", 25},
    std::string_view{"Epizootic", 9},
    std::string_view{"Food safety alert", 17},
    std::string_view{"Health hazard", 13},
    std::string_view{"Pandemic", 8},
    std::string_view{"Pest infestation", 16},
    std::string_view{"Risk of infection", 17},
    std::string_view{"Building collapse", 17},
    std::string_view{"Emergency number outage", 23},
    std::string_view{"Gas supply outage", 17},
    std::string_view{"Outage of IT systems", 20},
    std::string_view{"Power outage", 12},
    std::string_view{"Raw sewage", 10},
    std::string_view{"Telephone line outage", 21},
    std::string_view{"Black Ice", 9},
    std::string_view{"Coastal flooding", 16},
    std::string_view{"Cold wave", 9},
    std::string_view{"Derecho", 7},
    std::string_view{"Drought", 7},
    std::string_view{"Dust storm", 10},
    std::string_view{"Floating ice / icebergs", 23},
    std::string_view{"Flood", 5},
    std::string_view{"Fog", 3},
    std::string_view{"Hail", 4},
    std::string_view{"Heat wave", 9},
    std::string_view{"Lightning", 9},
    std::string_view{"Pollens", 7},
    std::string_view{"Rainfall", 8},
    std::string_view{"Snow storm / blizzard", 21},
    std::string_view{"Snowfall", 8},
    std::string_view{"Storm or thunderstorm", 21},
    std::string_view{"Thawing", 7},
    std::string_view{"Tornado", 7},
    std::string_view{"Tropical cyclone (hurricane)", 28},
    std::string_view{"Wind chill / frost", 18},
    std::string_view{"Tropical cyclone (typhoon)", 26},
    std::string_view{"Dam failure or bursting of a dam", 32},
    std::string_view{"Dike failure or bursting of a dike", 34},
    std::string_view{"Explosive ordnance disposal", 27},
    std::string_view{"Factory accident", 16},
    std::string_view{"Mine hazard", 11},
    std::string_view{"Bomb / ammunition discovery", 27},
    std::string_view{"Demonstration", 13},
    std::string_view{"Hazardous material accident", 27},
    std::string_view{"Life Threatening situation", 26},
    std::string_view{"Major event", 11},
    std::string_view{"Missing person / abduction", 26},
    std::string_view{"Risk of explosion", 17},
    std::string_view{"Safety warning", 14},
    std::string_view{"Undefined flying object", 23},
    std::string_view{"Unidentified animal", 19},
    std::string_view{"Chemical attack", 15},
    std::string_view{"Guerrilla attack", 16},
    std::string_view{"Hijack", 6},
    std::string_view{"Shooting or danger due to weapons", 33},
    std::string_view{"Special forces attack", 21},
    std::string_view{"Terrorism", 9},
    std::string_view{"Aircraft crash", 14},
    std::string_view{"Bridge collapse", 15},
    std::string_view{"Dangerous goods accident", 24},
    std::string_view{"Inland waterway transport accident", 34},
    std::string_view{"Nautical disaster / Maritime / Marine Security", 46},
    std::string_view{"Oil spill", 9},
    std::string_view{"Road traffic incident", 21},
    std::string_view{"Train/rail accident", 19},
    std::string_view{"Tunnel accident", 15},
    std::string_view{"Test alert", 10}
};
inline constexpr uint8_t QZSS_DCX_CAMF_A4_HAZARD_TYPE_BASE = 1;
inline constexpr uint8_t QZSS_DCX_CAMF_A4_HAZARD_TYPE_SIZE = 113;
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_a4_hazard_type_lookup(uint8_t id) {
    if (id < QZSS_DCX_CAMF_A4_HAZARD_TYPE_BASE || id >= QZSS_DCX_CAMF_A4_HAZARD_TYPE_BASE + QZSS_DCX_CAMF_A4_HAZARD_TYPE_SIZE) return std::nullopt;
    return QZSS_DCX_CAMF_A4_HAZARD_TYPE_TABLE[id - QZSS_DCX_CAMF_A4_HAZARD_TYPE_BASE];
}

} // namespace def
} // namespace azaraC
