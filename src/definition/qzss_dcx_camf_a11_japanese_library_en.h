#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcx_camf_a11_japanese_library
// Variable      : qzss_dcx_camf_a11_japanese_library_en
// Entries       : 38
// Strategy      : binary_search

#include <cstdint>
#include <optional>
#include <string_view>

namespace azaraC {
namespace def {

struct QZSS_DCX_CAMF_A11_JAPANESE_LIBRARY_EN_Entry { uint16_t id; std::string_view label; };
inline constexpr QZSS_DCX_CAMF_A11_JAPANESE_LIBRARY_EN_Entry QZSS_DCX_CAMF_A11_JAPANESE_LIBRARY_EN_TABLE[] = {
    {0u, std::string_view{"", 0}},

    {1u, std::string_view{"Take the best immediate action to save your life.", 49}},

    {126u, std::string_view{"This is a test message for DCX.", 31}},

    {127u, std::string_view{"Take the best immediate action to save your life.", 49}},

    {128u, std::string_view{"Missile launched, missile launched. It is believed that a missile was launched. Please take shelter inside buildings or underground.", 132}},

    {129u, std::string_view{"Missile passed, missile passed. It is believed that the previous missile has passed over the area. The call for evacuation will be canceled. If you find any suspicious object, please stay away from it and inform the police or the fire department immediately.", 258}},

    {130u, std::string_view{"It is believed that the previous missile has dropped in the sea. The call for evacuation will be canceled. If you find any suspicious object, please stay away from it and inform the police or the fire department immediately.", 224}},

    {131u, std::string_view{"It is believed that the previous missile will not come to Japan. The call for evacuation will be canceled.", 106}},

    {132u, std::string_view{"Take shelter immediately, take shelter immediately. Please take shelter inside buildings or underground. It is believed that a missile will drop around this area. Please take shelter immediately.", 195}},

    {133u, std::string_view{"The previous missile has been intercepted and destroyed. There is a possibility of pieces of the destroyed missile dropping. We will keep you informed. Please stay indoors for shelter.", 184}},

    {134u, std::string_view{"Missile dropped, missile dropped. It is believed that a missile has dropped around this area. We will keep you informed. Please stay indoors for shelter.", 153}},

    {135u, std::string_view{"It is believed that the previous missile will not drop in Japan. The call for evacuation will be canceled.", 106}},

    {136u, std::string_view{"This is a test message for J-Alert.", 35}},

    {255u, std::string_view{"Take immediate action to save your life.", 40}},

    {256u, std::string_view{"Stay.", 5}},

    {257u, std::string_view{"Stay. Under/inside a solid structure.", 37}},

    {258u, std::string_view{"Stay. 3rd floor or higher.", 26}},

    {259u, std::string_view{"Stay. Underground.", 18}},

    {260u, std::string_view{"Stay. Mountain.", 15}},

    {261u, std::string_view{"Stay. Water area.", 17}},

    {262u, std::string_view{"Stay. Building where chemicals are handled, such as a factory.", 62}},

    {263u, std::string_view{"Stay. Cliffs and areas at risk of collapse.", 43}},

    {512u, std::string_view{"Move to/toward", 14}},

    {513u, std::string_view{"Move to/toward Under/inside a solid structure.", 46}},

    {514u, std::string_view{"Move to/toward 3rd floor or higher.", 35}},

    {515u, std::string_view{"Move to/toward Underground.", 27}},

    {516u, std::string_view{"Move to/toward Mountain.", 24}},

    {517u, std::string_view{"Move to/toward Water area.", 26}},

    {518u, std::string_view{"Move to/toward Building where chemicals are handled, such as a factory.", 71}},

    {519u, std::string_view{"Move to/toward Cliffs and areas at risk of collapse.", 52}},

    {768u, std::string_view{"Keep away from", 14}},

    {769u, std::string_view{"Keep away from Under/inside a solid structure.", 46}},

    {770u, std::string_view{"Keep away from 3rd floor or higher.", 35}},

    {771u, std::string_view{"Keep away from Underground.", 27}},

    {772u, std::string_view{"Keep away from Mountain.", 24}},

    {773u, std::string_view{"Keep away from Water area.", 26}},

    {774u, std::string_view{"Keep away from Building where chemicals are handled, such as a factory.", 71}},

    {775u, std::string_view{"Keep away from Cliffs and areas at risk of collapse.", 52}},
};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_a11_japanese_library_en_lookup(uint16_t id) {
    uint8_t lo = 0, hi = 38;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        if (QZSS_DCX_CAMF_A11_JAPANESE_LIBRARY_EN_TABLE[mid].id == id) return QZSS_DCX_CAMF_A11_JAPANESE_LIBRARY_EN_TABLE[mid].label;
        if (QZSS_DCX_CAMF_A11_JAPANESE_LIBRARY_EN_TABLE[mid].id < id) lo = mid + 1;
        else hi = mid;
    }
    return std::nullopt;
}

} // namespace def
} // namespace azaraC
