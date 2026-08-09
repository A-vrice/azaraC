#pragma once
// AUTO-GENERATED from azarashi 0.16.4 with CI-CD
// Source module : qzss_dcx_camf_a11_japanese_library
// Variable      : qzss_dcx_camf_a11_japanese_library_en
// Entries       : 38
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

#if (AZARAC_ENABLE_DCX_CAMF) && (AZARAC_LANG_EN)

#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_A11_JAPANESE_LIBRARY_EN_POOL[] = "\000Take the best immediate action to save your life.\000This is a test message for DCX.\000Take the best immediate action to save your life.\000Missile launched, missile launched. It is believed that a missile was launched. Please take shelter inside buildings or underground.\000Missile passed, missile passed. It is believed that the previous missile has passed over the area. The call for evacuation will be canceled. If you find any suspicious object, please stay away from it and inform the police or the fire department immediately.\000It is believed that the previous missile has dropped in the sea. The call for evacuation will be canceled. If you find any suspicious object, please stay away from it and inform the police or the fire department immediately.\000It is believed that the previous missile will not come to Japan. The call for evacuation will be canceled.\000Take shelter immediately, take shelter immediately. Please take shelter inside buildings or underground. It is believed that a missile will drop around this area. Please take shelter immediately.\000The previous missile has been intercepted and destroyed. There is a possibility of pieces of the destroyed missile dropping. We will keep you informed. Please stay indoors for shelter.\000Missile dropped, missile dropped. It is believed that a missile has dropped around this area. We will keep you informed. Please stay indoors for shelter.\000It is believed that the previous missile will not drop in Japan. The call for evacuation will be canceled.\000This is a test message for J-Alert.\000Take immediate action to save your life.\000Stay.\000Stay. Under/inside a solid structure.\000Stay. 3rd floor or higher.\000Stay. Underground.\000Stay. Mountain.\000Stay. Water area.\000Stay. Building where chemicals are handled, such as a factory.\000Stay. Cliffs and areas at risk of collapse.\000Move to/toward\000Move to/toward Under/inside a solid structure.\000Move to/toward 3rd floor or higher.\000Move to/toward Underground.\000Move to/toward Mountain.\000Move to/toward Water area.\000Move to/toward Building where chemicals are handled, such as a factory.\000Move to/toward Cliffs and areas at risk of collapse.\000Keep away from\000Keep away from Under/inside a solid structure.\000Keep away from 3rd floor or higher.\000Keep away from Underground.\000Keep away from Mountain.\000Keep away from Water area.\000Keep away from Building where chemicals are handled, such as a factory.\000Keep away from Cliffs and areas at risk of collapse.\000";
struct QZSS_DCX_CAMF_A11_JAPANESE_LIBRARY_EN_Entry { uint16_t id; uint16_t offset; uint16_t len; };
static const QZSS_DCX_CAMF_A11_JAPANESE_LIBRARY_EN_Entry QZSS_DCX_CAMF_A11_JAPANESE_LIBRARY_EN_TABLE[] AZARAC_PROGMEM = {
    {0u, 0u, 0u},
    {1u, 1u, 49u},
    {126u, 51u, 31u},
    {127u, 83u, 49u},
    {128u, 133u, 132u},
    {129u, 266u, 258u},
    {130u, 525u, 224u},
    {131u, 750u, 106u},
    {132u, 857u, 195u},
    {133u, 1053u, 184u},
    {134u, 1238u, 153u},
    {135u, 1392u, 106u},
    {136u, 1499u, 35u},
    {255u, 1535u, 40u},
    {256u, 1576u, 5u},
    {257u, 1582u, 37u},
    {258u, 1620u, 26u},
    {259u, 1647u, 18u},
    {260u, 1666u, 15u},
    {261u, 1682u, 17u},
    {262u, 1700u, 62u},
    {263u, 1763u, 43u},
    {512u, 1807u, 14u},
    {513u, 1822u, 46u},
    {514u, 1869u, 35u},
    {515u, 1905u, 27u},
    {516u, 1933u, 24u},
    {517u, 1958u, 26u},
    {518u, 1985u, 71u},
    {519u, 2057u, 52u},
    {768u, 2110u, 14u},
    {769u, 2125u, 46u},
    {770u, 2172u, 35u},
    {771u, 2208u, 27u},
    {772u, 2236u, 24u},
    {773u, 2261u, 26u},
    {774u, 2288u, 71u},
    {775u, 2360u, 52u},
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_a11_japanese_library_en_lookup(uint16_t id) noexcept {
    uint8_t lo = 0, hi = 38;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        const char* AZARAC_PROGMEM ep = reinterpret_cast<const char*>(&QZSS_DCX_CAMF_A11_JAPANESE_LIBRARY_EN_TABLE[mid]);
        uint16_t eid = pgm_read_word(ep + offsetof(QZSS_DCX_CAMF_A11_JAPANESE_LIBRARY_EN_Entry, id));
        if (eid == id) {
            uint16_t off = pgm_read_word(ep + offsetof(QZSS_DCX_CAMF_A11_JAPANESE_LIBRARY_EN_Entry, offset));
            uint16_t n = pgm_read_word(ep + offsetof(QZSS_DCX_CAMF_A11_JAPANESE_LIBRARY_EN_Entry, len));
            if (n == 0) return std::nullopt;
            return azarac_pgm_view(QZSS_DCX_CAMF_A11_JAPANESE_LIBRARY_EN_POOL + off, n);
        }
        if (eid < id) lo = static_cast<uint8_t>(mid + 1); else hi = mid;
    }
    return std::nullopt;
}
#else
struct QZSS_DCX_CAMF_A11_JAPANESE_LIBRARY_EN_Entry { uint16_t id; std::optional<std::string_view> label; };
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
    {775u, std::string_view{"Keep away from Cliffs and areas at risk of collapse.", 52}},};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_a11_japanese_library_en_lookup(uint16_t id) noexcept {
    uint8_t lo = 0, hi = 38;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        if (QZSS_DCX_CAMF_A11_JAPANESE_LIBRARY_EN_TABLE[mid].id == id) return QZSS_DCX_CAMF_A11_JAPANESE_LIBRARY_EN_TABLE[mid].label;
        if (QZSS_DCX_CAMF_A11_JAPANESE_LIBRARY_EN_TABLE[mid].id < id) lo = mid + 1;
        else hi = mid;
    }
    return std::nullopt;
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_a11_japanese_library_en_lookup(uint16_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_a11_japanese_library_en_lookup(uint16_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
