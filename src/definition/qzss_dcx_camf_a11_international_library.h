#pragma once
// AUTO-GENERATED from azarashi 0.17.1 with CI-CD
// Source module : azarashi.definitions.camf.a11_international_library
// Variable      : qzss_dcx_camf_a11_international_library
// Entries       : 32
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

inline constexpr uint8_t QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_BASE = 0;
inline constexpr uint8_t QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_SIZE = 32;
#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_POOL[] = "\000You are in the danger zone, leave the area immediately. Listen to radio or media for directions and information\000You are in the danger zone, leave the area immediately and reach the evacuation point indicated by the area plotted in yellow. Listen to radio or media for directions and information\000Seek shelter in a building immediately. Stay under cover and stay informed\000Seek out a cellar or interior rooms on lower floor\000If you are in an alpine terrain, start descending immediately and seek for shelter\000Quickly move into interior rooms. If you are in a vehicle: Stop driving immediately on the edge of the road. If a building is nearby, seek shelter in that building\000If you are in open terrain and you cannot find shelter, lie face-down on the ground and protect your head and neck with your hands, in a hollow where possible\000Prepare for evacuation. Take only the essentials with you, especially ID cards, passport, credit cards and cash. Evacuate only after the instruction of the emergency authoritie\000Prepare emergency food and relief material: Check and restock your equipment and supplies of water, food, medicine, cash and batterie\000Stay away from glass surfaces such as windows and glass doors. There is a risk of injury from glass splinter\000Reduce your power consumption to a minimum\000Reduce your water consumption to a minimum\000Boil water before drinking it or using it in the kitchen\000Keep at least one metre away from any conversation partners. Avoid physical contact with other people such as kissing and shaking hands. Wash your hands regularly and thoroughly\000Do not drink any tap water. Avoid any skin contact with tap water. Only drink mineral water from a bottle. Turn off the water supply to your house\000Watch out for escaping gas. This can be indicated by hissing noises or a typical gas odour. Do not use matches, lighters or the like: naked flames in combination with leaking gas can lead to explosions and fire\000Do not go outside and do not use your car\000Do not touch any objects that seem suspicious to you. Debris can cause additional hazards such as fires and explosions. Inform the emergency services about damage and debri\000Do not enter smoke-filled rooms. Deadly gases can form there\000Do not enter cellars or underground car park\000Do not leave pets or livestock outside\000Do not touch any dead animals. Report any findings of dead wild animals to the authoritie\000Avoid driving\000Avoid all items with metal parts such as umbrellas and bicycles. Do not bathe or shower during a thunderstorm. Bathing and showering can be life-threatening\000Avoid rooms directly underneath the roof truss. Avoid very large rooms, such as halls, in which the ceiling is not supported by pillar\000Avoid going outdoors. Keep away from trees, towers and masts. Keep at least 20 m away from power lines. Watch out for flying objects and falling object\000Avoid the danger area\000Avoid going out when it is not necessary\000This is only a test. You do not have to take any action or to adopt any particular sheltering behaviour\000This replaces the warning previously in effect for this area\000Conditions have improved and are no longer expected to meet alert criteria\000";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_PARENT_POOL[] = ".\000s.\000";
struct QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_PARENT_Entry { uint16_t offset; uint8_t len; };
static const QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_PARENT_Entry QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_PARENT_TABLE[] AZARAC_PROGMEM = {
    {0u, 1u},
    {2u, 2u},
};
struct QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_Entry { uint16_t offset; uint8_t len; uint8_t parent; };
static const QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_Entry QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_TABLE[] AZARAC_PROGMEM = {
    {0u, 0u, 255u},
    {1u, 111u, 0u},
    {113u, 182u, 0u},
    {296u, 74u, 0u},
    {371u, 50u, 1u},
    {422u, 82u, 0u},
    {505u, 163u, 0u},
    {669u, 158u, 0u},
    {828u, 176u, 1u},
    {1005u, 133u, 1u},
    {1139u, 108u, 1u},
    {1248u, 42u, 0u},
    {1291u, 42u, 0u},
    {1334u, 56u, 0u},
    {1391u, 177u, 0u},
    {1569u, 146u, 0u},
    {1716u, 210u, 1u},
    {1927u, 41u, 0u},
    {1969u, 172u, 1u},
    {2142u, 60u, 0u},
    {2203u, 44u, 1u},
    {2248u, 38u, 0u},
    {2287u, 89u, 1u},
    {2377u, 13u, 0u},
    {2391u, 156u, 0u},
    {2548u, 134u, 1u},
    {2683u, 151u, 1u},
    {2835u, 21u, 0u},
    {2857u, 40u, 0u},
    {2898u, 103u, 0u},
    {3002u, 60u, 0u},
    {3063u, 74u, 0u}
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_a11_international_library_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_BASE || id >= QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_BASE + QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_SIZE) return std::nullopt;
    const char* AZARAC_PROGMEM p = reinterpret_cast<const char*>(&QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_TABLE[id - 0u]);
    uint16_t off = pgm_read_word(p + offsetof(QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_Entry, offset));
    uint8_t n = pgm_read_byte(p + offsetof(QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_Entry, len));
    uint8_t pi = pgm_read_byte(p + offsetof(QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_Entry, parent));
    if (pi == 255u) return azarac_pgm_view(QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_POOL + off, n);
    const char* AZARAC_PROGMEM pp = reinterpret_cast<const char*>(&QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_PARENT_TABLE[pi]);
    uint16_t poff = pgm_read_word(pp + offsetof(QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_PARENT_Entry, offset));
    uint8_t pn = pgm_read_byte(pp + offsetof(QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_PARENT_Entry, len));
    return azarac_pgm_join(QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_POOL + off, n, QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_PARENT_POOL + poff, pn);
}
#else
inline constexpr const char* QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_TABLE[] = {
    "",
    "You are in the danger zone, leave the area immediately. Listen to radio or media for directions and information.",
    "You are in the danger zone, leave the area immediately and reach the evacuation point indicated by the area plotted in yellow. Listen to radio or media for directions and information.",
    "Seek shelter in a building immediately. Stay under cover and stay informed.",
    "Seek out a cellar or interior rooms on lower floors.",
    "If you are in an alpine terrain, start descending immediately and seek for shelter.",
    "Quickly move into interior rooms. If you are in a vehicle: Stop driving immediately on the edge of the road. If a building is nearby, seek shelter in that building.",
    "If you are in open terrain and you cannot find shelter, lie face-down on the ground and protect your head and neck with your hands, in a hollow where possible.",
    "Prepare for evacuation. Take only the essentials with you, especially ID cards, passport, credit cards and cash. Evacuate only after the instruction of the emergency authorities.",
    "Prepare emergency food and relief material: Check and restock your equipment and supplies of water, food, medicine, cash and batteries.",
    "Stay away from glass surfaces such as windows and glass doors. There is a risk of injury from glass splinters.",
    "Reduce your power consumption to a minimum.",
    "Reduce your water consumption to a minimum.",
    "Boil water before drinking it or using it in the kitchen.",
    "Keep at least one metre away from any conversation partners. Avoid physical contact with other people such as kissing and shaking hands. Wash your hands regularly and thoroughly.",
    "Do not drink any tap water. Avoid any skin contact with tap water. Only drink mineral water from a bottle. Turn off the water supply to your house.",
    "Watch out for escaping gas. This can be indicated by hissing noises or a typical gas odour. Do not use matches, lighters or the like: naked flames in combination with leaking gas can lead to explosions and fires.",
    "Do not go outside and do not use your car.",
    "Do not touch any objects that seem suspicious to you. Debris can cause additional hazards such as fires and explosions. Inform the emergency services about damage and debris.",
    "Do not enter smoke-filled rooms. Deadly gases can form there.",
    "Do not enter cellars or underground car parks.",
    "Do not leave pets or livestock outside.",
    "Do not touch any dead animals. Report any findings of dead wild animals to the authorities.",
    "Avoid driving.",
    "Avoid all items with metal parts such as umbrellas and bicycles. Do not bathe or shower during a thunderstorm. Bathing and showering can be life-threatening.",
    "Avoid rooms directly underneath the roof truss. Avoid very large rooms, such as halls, in which the ceiling is not supported by pillars.",
    "Avoid going outdoors. Keep away from trees, towers and masts. Keep at least 20 m away from power lines. Watch out for flying objects and falling objects.",
    "Avoid the danger area.",
    "Avoid going out when it is not necessary.",
    "This is only a test. You do not have to take any action or to adopt any particular sheltering behaviour.",
    "This replaces the warning previously in effect for this area.",
    "Conditions have improved and are no longer expected to meet alert criteria."
};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_a11_international_library_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_BASE || id >= QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_BASE + QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_SIZE) return std::nullopt;
    const char* s = QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_TABLE[id - QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_BASE];
    return s ? std::optional<std::string_view>(std::string_view{s}) : std::nullopt;
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_a11_international_library_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_a11_international_library_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
