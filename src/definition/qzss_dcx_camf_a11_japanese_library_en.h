#pragma once
// AUTO-GENERATED from azarashi 0.17.1 with CI-CD
// Source module : azarashi.definitions.camf.a11_japanese_library
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
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_A11_JAPANESE_LIBRARY_EN_POOL[] = "No instruction\000the best immediate action to save your life.\000This is a test message for DCX.\000the best immediate action to save your life.\000Missile launched, missile launched. It is believed that a missile was launched. Please take shelter inside buildings or underground.\000Missile passed, missile passed. It is believed that the previous missile has passed over the area. The call for evacuation will be canceled. If you find any suspicious object, please stay away from it and inform the police or the fire department immediately.\000It is believed that the previous missile has dropped in the sea. The call for evacuation will be canceled. If you find any suspicious object, please stay away from it and inform the police or the fire department immediately.\000It is believed that the previous missile will not come to Japan. The call for evacuation will be canceled.\000shelter immediately, take shelter immediately. Please take shelter inside buildings or underground. It is believed that a missile will drop around this area. Please take shelter immediately.\000The previous missile has been intercepted and destroyed. There is a possibility of pieces of the destroyed missile dropping. We will keep you informed. Please stay indoors for shelter.\000Missile dropped, missile dropped. It is believed that a missile has dropped around this area. We will keep you informed. Please stay indoors for shelter.\000It is believed that the previous missile will not drop in Japan. The call for evacuation will be canceled.\000This is a test message for J-Alert.\000immediate action to save your life.\000.\000Under/inside a solid structure.\0003rd floor or higher.\000Stay. Underground.\000Mountain.\000Water area.\000Building where chemicals are handled, such as a factory.\000Cliffs and areas at risk of collapse.\000d\000Under/inside a solid structure.\0003rd floor or higher.\000Underground.\000Mountain.\000Water area.\000Building where chemicals are handled, such as a factory.\000Cliffs and areas at risk of collapse.\000m\000Under/inside a solid structure.\0003rd floor or higher.\000Underground.\000Mountain.\000Water area.\000Building where chemicals are handled, such as a factory.\000Cliffs and areas at risk of collapse.\000";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_A11_JAPANESE_LIBRARY_EN_PARENT_POOL[] = "Keep away fro\000Keep away from \000Move to/towar\000Move to/toward \000Stay\000Stay. \000Take \000";
struct QZSS_DCX_CAMF_A11_JAPANESE_LIBRARY_EN_PARENT_Entry { uint16_t offset; };
static const QZSS_DCX_CAMF_A11_JAPANESE_LIBRARY_EN_PARENT_Entry QZSS_DCX_CAMF_A11_JAPANESE_LIBRARY_EN_PARENT_TABLE[] AZARAC_PROGMEM = {
    {0u},
    {14u},
    {30u},
    {44u},
    {60u},
    {65u},
    {72u},
};
struct QZSS_DCX_CAMF_A11_JAPANESE_LIBRARY_EN_Entry { uint16_t id; uint8_t parent; uint16_t offset; };
static const QZSS_DCX_CAMF_A11_JAPANESE_LIBRARY_EN_Entry QZSS_DCX_CAMF_A11_JAPANESE_LIBRARY_EN_TABLE[] AZARAC_PROGMEM = {
    {0u, 255u, 0u},
    {1u, 6u, 15u},
    {126u, 255u, 60u},
    {127u, 6u, 92u},
    {128u, 255u, 137u},
    {129u, 255u, 270u},
    {130u, 255u, 529u},
    {131u, 255u, 754u},
    {132u, 6u, 861u},
    {133u, 255u, 1052u},
    {134u, 255u, 1237u},
    {135u, 255u, 1391u},
    {136u, 255u, 1498u},
    {255u, 6u, 1534u},
    {256u, 4u, 1570u},
    {257u, 5u, 1572u},
    {258u, 5u, 1604u},
    {259u, 255u, 1625u},
    {260u, 5u, 1644u},
    {261u, 5u, 1654u},
    {262u, 5u, 1666u},
    {263u, 5u, 1723u},
    {512u, 2u, 1761u},
    {513u, 3u, 1763u},
    {514u, 3u, 1795u},
    {515u, 3u, 1816u},
    {516u, 3u, 1829u},
    {517u, 3u, 1839u},
    {518u, 3u, 1851u},
    {519u, 3u, 1908u},
    {768u, 0u, 1946u},
    {769u, 1u, 1948u},
    {770u, 1u, 1980u},
    {771u, 1u, 2001u},
    {772u, 1u, 2014u},
    {773u, 1u, 2024u},
    {774u, 1u, 2036u},
    {775u, 1u, 2093u},
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_a11_japanese_library_en_lookup(uint16_t id) noexcept {
    uint8_t lo = 0, hi = 38;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        azarac_pgm_ptr ep = AZARAC_PGM_PTR(QZSS_DCX_CAMF_A11_JAPANESE_LIBRARY_EN_TABLE) + static_cast<size_t>(mid) * sizeof(QZSS_DCX_CAMF_A11_JAPANESE_LIBRARY_EN_Entry);
        uint16_t eid = azarac_read_word(ep, offsetof(QZSS_DCX_CAMF_A11_JAPANESE_LIBRARY_EN_Entry, id));
        if (eid == id) {
            uint16_t off = azarac_read_word(ep, offsetof(QZSS_DCX_CAMF_A11_JAPANESE_LIBRARY_EN_Entry, offset));
            uint8_t pi = azarac_read_byte(ep, offsetof(QZSS_DCX_CAMF_A11_JAPANESE_LIBRARY_EN_Entry, parent));
            if (pi == 255u) return azarac_pgm_view_z(AZARAC_PGM_PTR(QZSS_DCX_CAMF_A11_JAPANESE_LIBRARY_EN_POOL) + off);
            azarac_pgm_ptr pp = AZARAC_PGM_PTR(QZSS_DCX_CAMF_A11_JAPANESE_LIBRARY_EN_PARENT_TABLE) + static_cast<size_t>(pi) * sizeof(QZSS_DCX_CAMF_A11_JAPANESE_LIBRARY_EN_PARENT_Entry);
            uint16_t poff = azarac_read_word(pp, offsetof(QZSS_DCX_CAMF_A11_JAPANESE_LIBRARY_EN_PARENT_Entry, offset));
            return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCX_CAMF_A11_JAPANESE_LIBRARY_EN_PARENT_POOL) + poff, AZARAC_PGM_PTR(QZSS_DCX_CAMF_A11_JAPANESE_LIBRARY_EN_POOL) + off);
        }
        if (eid < id) lo = static_cast<uint8_t>(mid + 1); else hi = mid;
    }
    return std::nullopt;
}
#else
struct QZSS_DCX_CAMF_A11_JAPANESE_LIBRARY_EN_Entry { uint16_t id; const char* label; };
inline constexpr QZSS_DCX_CAMF_A11_JAPANESE_LIBRARY_EN_Entry QZSS_DCX_CAMF_A11_JAPANESE_LIBRARY_EN_TABLE[] = {
    {0u, "No instruction"},
    {1u, "Take the best immediate action to save your life."},
    {126u, "This is a test message for DCX."},
    {127u, "Take the best immediate action to save your life."},
    {128u, "Missile launched, missile launched. It is believed that a missile was launched. Please take shelter inside buildings or underground."},
    {129u, "Missile passed, missile passed. It is believed that the previous missile has passed over the area. The call for evacuation will be canceled. If you find any suspicious object, please stay away from it and inform the police or the fire department immediately."},
    {130u, "It is believed that the previous missile has dropped in the sea. The call for evacuation will be canceled. If you find any suspicious object, please stay away from it and inform the police or the fire department immediately."},
    {131u, "It is believed that the previous missile will not come to Japan. The call for evacuation will be canceled."},
    {132u, "Take shelter immediately, take shelter immediately. Please take shelter inside buildings or underground. It is believed that a missile will drop around this area. Please take shelter immediately."},
    {133u, "The previous missile has been intercepted and destroyed. There is a possibility of pieces of the destroyed missile dropping. We will keep you informed. Please stay indoors for shelter."},
    {134u, "Missile dropped, missile dropped. It is believed that a missile has dropped around this area. We will keep you informed. Please stay indoors for shelter."},
    {135u, "It is believed that the previous missile will not drop in Japan. The call for evacuation will be canceled."},
    {136u, "This is a test message for J-Alert."},
    {255u, "Take immediate action to save your life."},
    {256u, "Stay."},
    {257u, "Stay. Under/inside a solid structure."},
    {258u, "Stay. 3rd floor or higher."},
    {259u, "Stay. Underground."},
    {260u, "Stay. Mountain."},
    {261u, "Stay. Water area."},
    {262u, "Stay. Building where chemicals are handled, such as a factory."},
    {263u, "Stay. Cliffs and areas at risk of collapse."},
    {512u, "Move to/toward"},
    {513u, "Move to/toward Under/inside a solid structure."},
    {514u, "Move to/toward 3rd floor or higher."},
    {515u, "Move to/toward Underground."},
    {516u, "Move to/toward Mountain."},
    {517u, "Move to/toward Water area."},
    {518u, "Move to/toward Building where chemicals are handled, such as a factory."},
    {519u, "Move to/toward Cliffs and areas at risk of collapse."},
    {768u, "Keep away from"},
    {769u, "Keep away from Under/inside a solid structure."},
    {770u, "Keep away from 3rd floor or higher."},
    {771u, "Keep away from Underground."},
    {772u, "Keep away from Mountain."},
    {773u, "Keep away from Water area."},
    {774u, "Keep away from Building where chemicals are handled, such as a factory."},
    {775u, "Keep away from Cliffs and areas at risk of collapse."},};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_a11_japanese_library_en_lookup(uint16_t id) noexcept {
    uint8_t lo = 0, hi = 38;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        if (QZSS_DCX_CAMF_A11_JAPANESE_LIBRARY_EN_TABLE[mid].id == id) {
            const char* s = QZSS_DCX_CAMF_A11_JAPANESE_LIBRARY_EN_TABLE[mid].label;
            return s ? std::optional<std::string_view>(std::string_view{s}) : std::nullopt;
        }
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
