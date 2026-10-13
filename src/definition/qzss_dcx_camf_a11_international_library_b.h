#pragma once
// AUTO-GENERATED from azarashi 0.17.1 with CI-CD
// Source module : azarashi.definitions.camf.a11_international_library
// Variable      : qzss_dcx_camf_a11_international_library_b
// Entries       : 30
// Strategy      : binary_search

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

#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_B_POOL[] = "\000Check with the weather services and local authorities for additional information\000Find out the location of the information points set up by the authorities on official channels (radio, internet, TV, social networks…)\000Sensitive or vulnerable people should not go out unless they must.\000Rescue operation under process by security forces and emergency services. Avoid moving to facilitate security and emergency actions.\000Protect the most vulnerable and hear from your loved ones. Be aware of their special needs and support, as required. If you notice distressed or vulnerable persons, call the emergency services. Provide first aid if necessary but do not put yourself in any danger.\000Pay attention to announcements made by the police, fire brigade and by officials.\000Stay aware, keep listening to official instructions broadcast on the radio, television, websites and social networks pages\000If you need help leaving your home, call the emergency services.\000Only make phone calls in serious emergencies to avoid overloading the mobile network.\000Extreme intensity weather phenomena expected. The weather is very dangerous and implies high level of threat to health, even the life hazard. BE AWARE and keep up to date with the latest weather forecast.\000Severe weather expected. BE PREPARED. Take precautions and keep up to date with the latest weather forecast. Severe damages to people and properties may occur, especially to those vulnerable or in exposed areas.\000Moderate intensity weather phenomena expected. BE AWARE, keep up to date with the latest weather forecast. Moderate damages to people and properties may occur, especially to those vulnerable or in exposed areas\000BE PREPARED to protect yourself and your property. Flooding of properties and transport networks is expected. Disruption to power, communications and water supplies are possible. Evacuation may be required. Dangerous driving conditions due to reduced visibility and aquaplaning\000Do not go near or in flooded waters. Do not walk or drive on a submerged road. Flood waves may surprise you, the river bank may collapse or you could be sucked in a manhole or hit by a floating debris. Keep drains and shafts clear so that the water can drain away. Secure and/or move assets away from vulnerable area (car along the river, basements).\000Take shelter in the most resistant part of a permanent building, a municipal shelter if possible, and keep away from windows. BE AWARE of the “eye of the storm”, the calm area in its centre. It will be followed by an inversion and the strengthening of winds. Do not go outside and do not use your car. Wait until the alert is over.\000TAKE PRECAUTIONS, High temperatures are expected. Protect yourself from the heat and avoid physical and sports activities. Wet your body several times a day. Drink plenty of water and eat light food.\000Forest fire danger. Under these conditions fires may develop and spread rapidly resulting in damage to property and possible loss of human and/or animal life. Do not throw away any burning cigarettes or matches to the environment. Do not make a fire outdoors. Do not light any fireworks. Do not barbeque in open places. Vegetation is easily ignited and large areas may be affected. Follow the instructions from the local authorities.\000Risks of fire. Use permanent fireplaces when barbecuing. Make sure your fire is completely extinguished before you leave. Only light fireworks with the permission of the municipality, keep a safe distance from the forest and have water to hand.\000Keep as far away as possible from coastal areas, beaches and rivers. Get immediately to the highest ground possible and wait until the alert is over. If you are in danger of being overtaken by waves, climb onto a roof or up a solid tree, or cling on to a floating object carried along by the water.\000Do not go to sea and keep as far away as possible from the coast and wait until the alert is over. If you are at sea, don’t return to port. Keep away from the coast. Waves are much less dangerous out at sea.\000Leave the affected area immediately and seek higher ground or move to higher parts of the building. Listen to radio or media for directions and information\000Indoors: during the quake, take shelter near a wall or a solid piece of furniture. Outside: during the quake, keep away from anything that might collapse. In a car: during the quake, stop as far away from buildings as you can. After, be prepared for aftershocks. If you are indoor, leave by the stairs.\000Leave the impact site immediately and cover your mouth and nose with improvised respiratory protection (cloth, garment, surgical mask). This protects you from dust, but not from gaseous hazardous substances. Seek out a building. Move wherever possible at a right angle to the wind direction as this is the quickest way to leave the danger zone with a possible cloud of hazardous substances.\000Switch off the ventilation and air conditioning systems. Close all windows, doors and shutters. Cover your mouth and nose and breathe through a facemask or an improvised respiratory protection (cloth, garment, surgical mask) if the air is filled with smoke and ashes\000Have iodine tablets ready. DO NOT take the iodine tablets now. If this becomes necessary, we will inform you in good time.\000Take the iodine tablets NOW according to the package insert.\000Avoid watering your plants during the hottest hours, avoid using water for secondary uses such as washing your car.\000Seek shelter if you cannot leave the area immediately.\000This replaces the warning previously in effect for this area.\000";
struct QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_B_Entry { uint8_t id; uint16_t offset; uint16_t len; };
static const QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_B_Entry QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_B_TABLE[] AZARAC_PROGMEM = {
    {0u, 0u, 0u},
    {1u, 1u, 80u},
    {2u, 82u, 136u},
    {3u, 219u, 66u},
    {4u, 286u, 132u},
    {5u, 419u, 263u},
    {6u, 683u, 81u},
    {7u, 765u, 122u},
    {8u, 888u, 64u},
    {9u, 953u, 85u},
    {10u, 1039u, 204u},
    {11u, 1244u, 211u},
    {12u, 1456u, 210u},
    {13u, 1667u, 277u},
    {14u, 1945u, 350u},
    {15u, 2296u, 335u},
    {16u, 2632u, 199u},
    {17u, 2832u, 433u},
    {18u, 3266u, 244u},
    {19u, 3511u, 298u},
    {20u, 3810u, 209u},
    {21u, 4020u, 155u},
    {22u, 4176u, 302u},
    {23u, 4479u, 390u},
    {24u, 4870u, 266u},
    {25u, 5137u, 122u},
    {26u, 5260u, 60u},
    {27u, 5321u, 115u},
    {28u, 5437u, 54u},
    {31u, 5492u, 61u},
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_a11_international_library_b_lookup(uint8_t id) noexcept {
    uint8_t lo = 0, hi = 30;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        const char* AZARAC_PROGMEM ep = reinterpret_cast<const char*>(&QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_B_TABLE[mid]);
        uint8_t eid = static_cast<uint8_t>(pgm_read_byte(ep + offsetof(QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_B_Entry, id)));
        if (eid == id) {
            uint16_t off = pgm_read_word(ep + offsetof(QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_B_Entry, offset));
            uint16_t n = pgm_read_word(ep + offsetof(QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_B_Entry, len));
            return azarac_pgm_view(QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_B_POOL + off, n);
        }
        if (eid < id) lo = static_cast<uint8_t>(mid + 1); else hi = mid;
    }
    return std::nullopt;
}
#else
struct QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_B_Entry { uint8_t id; const char* label; };
inline constexpr QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_B_Entry QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_B_TABLE[] = {
    {0u, ""},
    {1u, "Check with the weather services and local authorities for additional information"},
    {2u, "Find out the location of the information points set up by the authorities on official channels (radio, internet, TV, social networks…)"},
    {3u, "Sensitive or vulnerable people should not go out unless they must."},
    {4u, "Rescue operation under process by security forces and emergency services. Avoid moving to facilitate security and emergency actions."},
    {5u, "Protect the most vulnerable and hear from your loved ones. Be aware of their special needs and support, as required. If you notice distressed or vulnerable persons, call the emergency services. Provide first aid if necessary but do not put yourself in any danger."},
    {6u, "Pay attention to announcements made by the police, fire brigade and by officials."},
    {7u, "Stay aware, keep listening to official instructions broadcast on the radio, television, websites and social networks pages"},
    {8u, "If you need help leaving your home, call the emergency services."},
    {9u, "Only make phone calls in serious emergencies to avoid overloading the mobile network."},
    {10u, "Extreme intensity weather phenomena expected. The weather is very dangerous and implies high level of threat to health, even the life hazard. BE AWARE and keep up to date with the latest weather forecast."},
    {11u, "Severe weather expected. BE PREPARED. Take precautions and keep up to date with the latest weather forecast. Severe damages to people and properties may occur, especially to those vulnerable or in exposed areas."},
    {12u, "Moderate intensity weather phenomena expected. BE AWARE, keep up to date with the latest weather forecast. Moderate damages to people and properties may occur, especially to those vulnerable or in exposed areas"},
    {13u, "BE PREPARED to protect yourself and your property. Flooding of properties and transport networks is expected. Disruption to power, communications and water supplies are possible. Evacuation may be required. Dangerous driving conditions due to reduced visibility and aquaplaning"},
    {14u, "Do not go near or in flooded waters. Do not walk or drive on a submerged road. Flood waves may surprise you, the river bank may collapse or you could be sucked in a manhole or hit by a floating debris. Keep drains and shafts clear so that the water can drain away. Secure and/or move assets away from vulnerable area (car along the river, basements)."},
    {15u, "Take shelter in the most resistant part of a permanent building, a municipal shelter if possible, and keep away from windows. BE AWARE of the “eye of the storm”, the calm area in its centre. It will be followed by an inversion and the strengthening of winds. Do not go outside and do not use your car. Wait until the alert is over."},
    {16u, "TAKE PRECAUTIONS, High temperatures are expected. Protect yourself from the heat and avoid physical and sports activities. Wet your body several times a day. Drink plenty of water and eat light food."},
    {17u, "Forest fire danger. Under these conditions fires may develop and spread rapidly resulting in damage to property and possible loss of human and/or animal life. Do not throw away any burning cigarettes or matches to the environment. Do not make a fire outdoors. Do not light any fireworks. Do not barbeque in open places. Vegetation is easily ignited and large areas may be affected. Follow the instructions from the local authorities."},
    {18u, "Risks of fire. Use permanent fireplaces when barbecuing. Make sure your fire is completely extinguished before you leave. Only light fireworks with the permission of the municipality, keep a safe distance from the forest and have water to hand."},
    {19u, "Keep as far away as possible from coastal areas, beaches and rivers. Get immediately to the highest ground possible and wait until the alert is over. If you are in danger of being overtaken by waves, climb onto a roof or up a solid tree, or cling on to a floating object carried along by the water."},
    {20u, "Do not go to sea and keep as far away as possible from the coast and wait until the alert is over. If you are at sea, don’t return to port. Keep away from the coast. Waves are much less dangerous out at sea."},
    {21u, "Leave the affected area immediately and seek higher ground or move to higher parts of the building. Listen to radio or media for directions and information"},
    {22u, "Indoors: during the quake, take shelter near a wall or a solid piece of furniture. Outside: during the quake, keep away from anything that might collapse. In a car: during the quake, stop as far away from buildings as you can. After, be prepared for aftershocks. If you are indoor, leave by the stairs."},
    {23u, "Leave the impact site immediately and cover your mouth and nose with improvised respiratory protection (cloth, garment, surgical mask). This protects you from dust, but not from gaseous hazardous substances. Seek out a building. Move wherever possible at a right angle to the wind direction as this is the quickest way to leave the danger zone with a possible cloud of hazardous substances."},
    {24u, "Switch off the ventilation and air conditioning systems. Close all windows, doors and shutters. Cover your mouth and nose and breathe through a facemask or an improvised respiratory protection (cloth, garment, surgical mask) if the air is filled with smoke and ashes"},
    {25u, "Have iodine tablets ready. DO NOT take the iodine tablets now. If this becomes necessary, we will inform you in good time."},
    {26u, "Take the iodine tablets NOW according to the package insert."},
    {27u, "Avoid watering your plants during the hottest hours, avoid using water for secondary uses such as washing your car."},
    {28u, "Seek shelter if you cannot leave the area immediately."},
    {31u, "This replaces the warning previously in effect for this area."},};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_a11_international_library_b_lookup(uint8_t id) noexcept {
    uint8_t lo = 0, hi = 30;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        if (QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_B_TABLE[mid].id == id) {
            const char* s = QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_B_TABLE[mid].label;
            return s ? std::optional<std::string_view>(std::string_view{s}) : std::nullopt;
        }
        if (QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_B_TABLE[mid].id < id) lo = mid + 1;
        else hi = mid;
    }
    return std::nullopt;
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_a11_international_library_b_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_a11_international_library_b_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
