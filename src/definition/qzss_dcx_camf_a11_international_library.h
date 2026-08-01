#pragma once
// AUTO-GENERATED from azarashi 0.16.4 with CI-CD
// Source module : qzss_dcx_camf_a11_international_library
// Variable      : qzss_dcx_camf_a11_international_library
// Entries       : 32
// Strategy      : array

// NOTE: This function may return nullptr for unknown IDs.
// Callers MUST perform a null-check before using the result.

#include <cstdint>
#include <optional>
#include <string_view>
#include "../azaraC.h"
#include "../internal/FlashString.h"

namespace azaraC {
namespace def {

#if (AZARAC_ENABLE_DCX_CAMF)

inline constexpr uint8_t QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_BASE = 0;
inline constexpr uint8_t QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_SIZE = 32;
#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_POOL[] = "\0You are in the danger zone, leave the area immediately. Listen to radio or media for directions and information.\0You are in the danger zone, leave the area immediately and reach the evacuation point indicated by the area plotted in yellow. Listen to radio or media for directions and information.\0Seek shelter in a building immediately. Stay under cover and stay informed.\0Seek out a cellar or interior rooms on lower floors.\0If you are in an alpine terrain, start descending immediately and seek for shelter.\0Quickly move into interior rooms. If you are in a vehicle: Stop driving immediately on the edge of the road. If a building is nearby, seek shelter in that building.\0If you are in open terrain and you cannot find shelter, lie face-down on the ground and protect your head and neck with your hands, in a hollow where possible.\0Prepare for evacuation. Take only the essentials with you, especially ID cards, passport, credit cards and cash. Evacuate only after the instruction of the emergency authorities.\0Prepare emergency food and relief material: Check and restock your equipment and supplies of water, food, medicine, cash and batteries.\0Stay away from glass surfaces such as windows and glass doors. There is a risk of injury from glass splinters.\0Reduce your power consumption to a minimum.\0Reduce your water consumption to a minimum.\0Boil water before drinking it or using it in the kitchen.\0Keep at least one metre away from any conversation partners. Avoid physical contact with other people such as kissing and shaking hands. Wash your hands regularly and thoroughly.\0Do not drink any tap water. Avoid any skin contact with tap water. Only drink mineral water from a bottle. Turn off the water supply to your house.\0Watch out for escaping gas. This can be indicated by hissing noises or a typical gas odour. Do not use matches, lighters or the like: naked flames in combination with leaking gas can lead to explosions and fires.\0Do not go outside and do not use your car.\0Do not touch any objects that seem suspicious to you. Debris can cause additional hazards such as fires and explosions. Inform the emergency services about damage and debris.\0Do not enter smoke-filled rooms. Deadly gases can form there.\0Do not enter cellars or underground car parks.\0Do not leave pets or livestock outside.\0Do not touch any dead animals. Report any findings of dead wild animals to the authorities.\0Avoid driving.\0Avoid all items with metal parts such as umbrellas and bicycles. Do not bathe or shower during a thunderstorm. Bathing and showering can be life-threatening.\0Avoid rooms directly underneath the roof truss. Avoid very large rooms, such as halls, in which the ceiling is not supported by pillars.\0Avoid going outdoors. Keep away from trees, towers and masts. Keep at least 20 m away from power lines. Watch out for flying objects and falling objects.\0Avoid the danger area.\0Avoid going out when it is not necessary.\0This is only a test. You do not have to take any action or to adopt any particular sheltering behaviour.\0This replaces the warning previously in effect for this area.\0Conditions have improved and are no longer expected to meet alert criteria.\0";
struct QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_Entry { uint16_t offset; uint16_t len; };
static const QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_Entry QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_TABLE[] AZARAC_PROGMEM = {
    {0u, 0u},
    {1u, 112u},
    {114u, 183u},
    {298u, 75u},
    {374u, 52u},
    {427u, 83u},
    {511u, 164u},
    {676u, 159u},
    {836u, 178u},
    {1015u, 135u},
    {1151u, 110u},
    {1262u, 43u},
    {1306u, 43u},
    {1350u, 57u},
    {1408u, 178u},
    {1587u, 147u},
    {1735u, 212u},
    {1948u, 42u},
    {1991u, 174u},
    {2166u, 61u},
    {2228u, 46u},
    {2275u, 39u},
    {2315u, 91u},
    {2407u, 14u},
    {2422u, 157u},
    {2580u, 136u},
    {2717u, 153u},
    {2871u, 22u},
    {2894u, 41u},
    {2936u, 104u},
    {3041u, 61u},
    {3103u, 75u}
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_a11_international_library_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_BASE || id >= QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_BASE + QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_SIZE) return std::nullopt;
    const char* AZARAC_PROGMEM p = reinterpret_cast<const char*>(&QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_TABLE[id - 0u]);
    uint16_t off = pgm_read_word(p + offsetof(QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_Entry, offset));
    uint16_t n = pgm_read_word(p + offsetof(QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_Entry, len));
    if (n == 0) return std::nullopt;
    return azarac_pgm_view(QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_POOL + off, n);
}
#else
inline constexpr std::optional<std::string_view> QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_TABLE[] = {
    std::string_view{"", 0},
    std::string_view{"You are in the danger zone, leave the area immediately. Listen to radio or media for directions and information.", 112},
    std::string_view{"You are in the danger zone, leave the area immediately and reach the evacuation point indicated by the area plotted in yellow. Listen to radio or media for directions and information.", 183},
    std::string_view{"Seek shelter in a building immediately. Stay under cover and stay informed.", 75},
    std::string_view{"Seek out a cellar or interior rooms on lower floors.", 52},
    std::string_view{"If you are in an alpine terrain, start descending immediately and seek for shelter.", 83},
    std::string_view{"Quickly move into interior rooms. If you are in a vehicle: Stop driving immediately on the edge of the road. If a building is nearby, seek shelter in that building.", 164},
    std::string_view{"If you are in open terrain and you cannot find shelter, lie face-down on the ground and protect your head and neck with your hands, in a hollow where possible.", 159},
    std::string_view{"Prepare for evacuation. Take only the essentials with you, especially ID cards, passport, credit cards and cash. Evacuate only after the instruction of the emergency authorities.", 178},
    std::string_view{"Prepare emergency food and relief material: Check and restock your equipment and supplies of water, food, medicine, cash and batteries.", 135},
    std::string_view{"Stay away from glass surfaces such as windows and glass doors. There is a risk of injury from glass splinters.", 110},
    std::string_view{"Reduce your power consumption to a minimum.", 43},
    std::string_view{"Reduce your water consumption to a minimum.", 43},
    std::string_view{"Boil water before drinking it or using it in the kitchen.", 57},
    std::string_view{"Keep at least one metre away from any conversation partners. Avoid physical contact with other people such as kissing and shaking hands. Wash your hands regularly and thoroughly.", 178},
    std::string_view{"Do not drink any tap water. Avoid any skin contact with tap water. Only drink mineral water from a bottle. Turn off the water supply to your house.", 147},
    std::string_view{"Watch out for escaping gas. This can be indicated by hissing noises or a typical gas odour. Do not use matches, lighters or the like: naked flames in combination with leaking gas can lead to explosions and fires.", 212},
    std::string_view{"Do not go outside and do not use your car.", 42},
    std::string_view{"Do not touch any objects that seem suspicious to you. Debris can cause additional hazards such as fires and explosions. Inform the emergency services about damage and debris.", 174},
    std::string_view{"Do not enter smoke-filled rooms. Deadly gases can form there.", 61},
    std::string_view{"Do not enter cellars or underground car parks.", 46},
    std::string_view{"Do not leave pets or livestock outside.", 39},
    std::string_view{"Do not touch any dead animals. Report any findings of dead wild animals to the authorities.", 91},
    std::string_view{"Avoid driving.", 14},
    std::string_view{"Avoid all items with metal parts such as umbrellas and bicycles. Do not bathe or shower during a thunderstorm. Bathing and showering can be life-threatening.", 157},
    std::string_view{"Avoid rooms directly underneath the roof truss. Avoid very large rooms, such as halls, in which the ceiling is not supported by pillars.", 136},
    std::string_view{"Avoid going outdoors. Keep away from trees, towers and masts. Keep at least 20 m away from power lines. Watch out for flying objects and falling objects.", 153},
    std::string_view{"Avoid the danger area.", 22},
    std::string_view{"Avoid going out when it is not necessary.", 41},
    std::string_view{"This is only a test. You do not have to take any action or to adopt any particular sheltering behaviour.", 104},
    std::string_view{"This replaces the warning previously in effect for this area.", 61},
    std::string_view{"Conditions have improved and are no longer expected to meet alert criteria.", 75}
};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_a11_international_library_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_BASE || id >= QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_BASE + QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_SIZE) return std::nullopt;
    return QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_TABLE[id - QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_BASE];
}
#endif

#else

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_a11_international_library_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}

#endif

} // namespace def
} // namespace azaraC
