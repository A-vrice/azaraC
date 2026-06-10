#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcx_camf_c10_guidance_library_for_second_ellipse
// Variable      : qzss_dcx_camf_c10_guidance_library_for_second_ellipse
// Entries       : 19
// Strategy      : binary_search

#include <cstdint>
#include <optional>
#include <string_view>

namespace azaraC {
namespace def {

struct QZSS_DCX_CAMF_C10_GUIDANCE_LIBRARY_FOR_SECOND_ELLIPSE_Entry { uint8_t id; std::string_view label; };
inline constexpr QZSS_DCX_CAMF_C10_GUIDANCE_LIBRARY_FOR_SECOND_ELLIPSE_Entry QZSS_DCX_CAMF_C10_GUIDANCE_LIBRARY_FOR_SECOND_ELLIPSE_TABLE[] = {
    {0u, std::string_view{"", 0}},

    {1u, std::string_view{"Prepare for evacuation. Take only the essentials with you, especially ID cards, passport, credit cards and cash. Evacuate only after the instruction of the emergency authorities.", 178}},

    {2u, std::string_view{"Prepare emergency food and relief material: Check and restock your equipment and supplies of water, food, medicine, cash and batteries.", 135}},

    {3u, std::string_view{"Be prepared to protect yourself and your property. Flooding of properties and transport networks is expected. Disruption to power, communications and water supplies are possible. Evacuation may be required. Dangerous driving conditions due to reduced visibility and aquaplaning.", 278}},

    {4u, std::string_view{"Have iodine tablets ready. DO NOT take the iodine tablets now. If this becomes necessary, we will inform you in good time.", 122}},

    {5u, std::string_view{"Keep your smartphone charged to be able to receive further instructions and information.", 88}},

    {6u, std::string_view{"Avoid using lifts.", 18}},

    {7u, std::string_view{"Avoid the danger area.", 22}},

    {8u, std::string_view{"Avoid driving.", 14}},

    {9u, std::string_view{"Rescue operation under process by security forces and emergency services. Avoid moving to facilitate security and emergency actions.", 132}},

    {10u, std::string_view{"Check with the weather services and local authorities for additional information.", 81}},

    {11u, std::string_view{"Find out the location of the information points set up by the authorities on official channels (radio, internet, TV, social networks...).", 137}},

    {12u, std::string_view{"Sensitive or vulnerable people should not go out unless they must.", 66}},

    {13u, std::string_view{"Protect the most vulnerable and hear from your loved ones. Be aware of their special needs and support, as required. If you notice distressed or vulnerable persons, contact the emergency services. Provide first aid if necessary but do not put yourself in any danger.", 266}},

    {14u, std::string_view{"Pay attention to announcements made by the police, fire brigade and by officials.", 81}},

    {15u, std::string_view{"Stay aware, keep listening to official instructions broadcast on the radio, television, websites and social networks pages.", 123}},

    {16u, std::string_view{"Only make phone calls in serious emergencies to avoid overloading the mobile network.", 85}},

    {30u, std::string_view{"This is only a test. You do not have to take any action or to adopt any particular sheltering behaviour.", 104}},

    {31u, std::string_view{"Conditions have improved and are no longer expected to meet alert criteria.", 75}},
};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_c10_guidance_library_for_second_ellipse_lookup(uint8_t id) {
    uint8_t lo = 0, hi = 19;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        if (QZSS_DCX_CAMF_C10_GUIDANCE_LIBRARY_FOR_SECOND_ELLIPSE_TABLE[mid].id == id) return QZSS_DCX_CAMF_C10_GUIDANCE_LIBRARY_FOR_SECOND_ELLIPSE_TABLE[mid].label;
        if (QZSS_DCX_CAMF_C10_GUIDANCE_LIBRARY_FOR_SECOND_ELLIPSE_TABLE[mid].id < id) lo = mid + 1;
        else hi = mid;
    }
    return std::nullopt;
}

} // namespace def
} // namespace azaraC
