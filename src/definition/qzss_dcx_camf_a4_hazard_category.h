#pragma once
// AUTO-GENERATED from azarashi 0.16.4 with CI-CD
// Source module : qzss_dcx_camf_a4_hazard_category_and_type
// Variable      : qzss_dcx_camf_a4_hazard_category
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

inline constexpr uint8_t QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_BASE = 1;
inline constexpr uint8_t QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_SIZE = 113;
#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_POOL[] = "CBRNE\000CBRNE\000CBRNE\000CBRNE\000CBRNE\000CBRNE\000CBRNE\000CBRNE\000CBRNE\000CBRNE\000CBRNE\000CBRNE\000CBRNE\000ENVIRONMENT\000ENVIRONMENT\000ENVIRONMENT\000ENVIRONMENT\000ENVIRONMENT\000ENVIRONMENT\000ENVIRONMENT\000ENVIRONMENT\000ENVIRONMENT\000ENVIRONMENT\000FIRE\000FIRE\000FIRE\000FIRE\000FIRE\000FIRE\000FIRE\000FIRE\000GEO\000GEO\000GEO\000GEO\000GEO\000GEO\000GEO\000GEO\000GEO\000GEO\000GEO\000GEO\000GEO\000GEO\000GEO\000GEO\000HEALTH\000HEALTH\000HEALTH\000HEALTH\000HEALTH\000HEALTH\000INFRASTRUCTURE\000INFRASTRUCTURE\000INFRASTRUCTURE\000INFRASTRUCTURE\000INFRASTRUCTURE\000INFRASTRUCTURE\000INFRASTRUCTURE\000MET\000MET\000MET\000MET\000MET\000MET\000MET\000MET\000MET\000MET\000MET\000MET\000MET\000MET\000MET\000MET\000MET\000MET\000MET\000MET\000MET\000MET\000RESCUE\000RESCUE\000RESCUE\000RESCUE\000RESCUE\000SAFETY\000SAFETY\000SAFETY\000SAFETY\000SAFETY\000SAFETY\000SAFETY\000SAFETY\000SAFETY\000SAFETY\000SECURITY\000SECURITY\000SECURITY\000SECURITY\000SECURITY\000SECURITY\000TRANSPORT\000TRANSPORT\000TRANSPORT\000TRANSPORT\000TRANSPORT\000TRANSPORT\000TRANSPORT\000TRANSPORT\000TRANSPORT\000OTHER\000";
struct QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_Entry { uint16_t offset; uint16_t len; };
static const QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_Entry QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_TABLE[] AZARAC_PROGMEM = {
    {0u, 5u},
    {6u, 5u},
    {12u, 5u},
    {18u, 5u},
    {24u, 5u},
    {30u, 5u},
    {36u, 5u},
    {42u, 5u},
    {48u, 5u},
    {54u, 5u},
    {60u, 5u},
    {66u, 5u},
    {72u, 5u},
    {78u, 11u},
    {90u, 11u},
    {102u, 11u},
    {114u, 11u},
    {126u, 11u},
    {138u, 11u},
    {150u, 11u},
    {162u, 11u},
    {174u, 11u},
    {186u, 11u},
    {198u, 4u},
    {203u, 4u},
    {208u, 4u},
    {213u, 4u},
    {218u, 4u},
    {223u, 4u},
    {228u, 4u},
    {233u, 4u},
    {238u, 3u},
    {242u, 3u},
    {246u, 3u},
    {250u, 3u},
    {254u, 3u},
    {258u, 3u},
    {262u, 3u},
    {266u, 3u},
    {270u, 3u},
    {274u, 3u},
    {278u, 3u},
    {282u, 3u},
    {286u, 3u},
    {290u, 3u},
    {294u, 3u},
    {298u, 3u},
    {302u, 6u},
    {309u, 6u},
    {316u, 6u},
    {323u, 6u},
    {330u, 6u},
    {337u, 6u},
    {344u, 14u},
    {359u, 14u},
    {374u, 14u},
    {389u, 14u},
    {404u, 14u},
    {419u, 14u},
    {434u, 14u},
    {449u, 3u},
    {453u, 3u},
    {457u, 3u},
    {461u, 3u},
    {465u, 3u},
    {469u, 3u},
    {473u, 3u},
    {477u, 3u},
    {481u, 3u},
    {485u, 3u},
    {489u, 3u},
    {493u, 3u},
    {497u, 3u},
    {501u, 3u},
    {505u, 3u},
    {509u, 3u},
    {513u, 3u},
    {517u, 3u},
    {521u, 3u},
    {525u, 3u},
    {529u, 3u},
    {533u, 3u},
    {537u, 6u},
    {544u, 6u},
    {551u, 6u},
    {558u, 6u},
    {565u, 6u},
    {572u, 6u},
    {579u, 6u},
    {586u, 6u},
    {593u, 6u},
    {600u, 6u},
    {607u, 6u},
    {614u, 6u},
    {621u, 6u},
    {628u, 6u},
    {635u, 6u},
    {642u, 8u},
    {651u, 8u},
    {660u, 8u},
    {669u, 8u},
    {678u, 8u},
    {687u, 8u},
    {696u, 9u},
    {706u, 9u},
    {716u, 9u},
    {726u, 9u},
    {736u, 9u},
    {746u, 9u},
    {756u, 9u},
    {766u, 9u},
    {776u, 9u},
    {786u, 5u}
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_a4_hazard_category_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_BASE || id >= QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_BASE + QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_SIZE) return std::nullopt;
    const char* AZARAC_PROGMEM p = reinterpret_cast<const char*>(&QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_TABLE[id - 1u]);
    uint16_t off = pgm_read_word(p + offsetof(QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_Entry, offset));
    uint16_t n = pgm_read_word(p + offsetof(QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_Entry, len));
    if (n == 0) return std::nullopt;
    return azarac_pgm_view(QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_POOL + off, n);
}
#else
inline constexpr std::optional<std::string_view> QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_TABLE[] = {
    std::string_view{"CBRNE", 5},
    std::string_view{"CBRNE", 5},
    std::string_view{"CBRNE", 5},
    std::string_view{"CBRNE", 5},
    std::string_view{"CBRNE", 5},
    std::string_view{"CBRNE", 5},
    std::string_view{"CBRNE", 5},
    std::string_view{"CBRNE", 5},
    std::string_view{"CBRNE", 5},
    std::string_view{"CBRNE", 5},
    std::string_view{"CBRNE", 5},
    std::string_view{"CBRNE", 5},
    std::string_view{"CBRNE", 5},
    std::string_view{"ENVIRONMENT", 11},
    std::string_view{"ENVIRONMENT", 11},
    std::string_view{"ENVIRONMENT", 11},
    std::string_view{"ENVIRONMENT", 11},
    std::string_view{"ENVIRONMENT", 11},
    std::string_view{"ENVIRONMENT", 11},
    std::string_view{"ENVIRONMENT", 11},
    std::string_view{"ENVIRONMENT", 11},
    std::string_view{"ENVIRONMENT", 11},
    std::string_view{"ENVIRONMENT", 11},
    std::string_view{"FIRE", 4},
    std::string_view{"FIRE", 4},
    std::string_view{"FIRE", 4},
    std::string_view{"FIRE", 4},
    std::string_view{"FIRE", 4},
    std::string_view{"FIRE", 4},
    std::string_view{"FIRE", 4},
    std::string_view{"FIRE", 4},
    std::string_view{"GEO", 3},
    std::string_view{"GEO", 3},
    std::string_view{"GEO", 3},
    std::string_view{"GEO", 3},
    std::string_view{"GEO", 3},
    std::string_view{"GEO", 3},
    std::string_view{"GEO", 3},
    std::string_view{"GEO", 3},
    std::string_view{"GEO", 3},
    std::string_view{"GEO", 3},
    std::string_view{"GEO", 3},
    std::string_view{"GEO", 3},
    std::string_view{"GEO", 3},
    std::string_view{"GEO", 3},
    std::string_view{"GEO", 3},
    std::string_view{"GEO", 3},
    std::string_view{"HEALTH", 6},
    std::string_view{"HEALTH", 6},
    std::string_view{"HEALTH", 6},
    std::string_view{"HEALTH", 6},
    std::string_view{"HEALTH", 6},
    std::string_view{"HEALTH", 6},
    std::string_view{"INFRASTRUCTURE", 14},
    std::string_view{"INFRASTRUCTURE", 14},
    std::string_view{"INFRASTRUCTURE", 14},
    std::string_view{"INFRASTRUCTURE", 14},
    std::string_view{"INFRASTRUCTURE", 14},
    std::string_view{"INFRASTRUCTURE", 14},
    std::string_view{"INFRASTRUCTURE", 14},
    std::string_view{"MET", 3},
    std::string_view{"MET", 3},
    std::string_view{"MET", 3},
    std::string_view{"MET", 3},
    std::string_view{"MET", 3},
    std::string_view{"MET", 3},
    std::string_view{"MET", 3},
    std::string_view{"MET", 3},
    std::string_view{"MET", 3},
    std::string_view{"MET", 3},
    std::string_view{"MET", 3},
    std::string_view{"MET", 3},
    std::string_view{"MET", 3},
    std::string_view{"MET", 3},
    std::string_view{"MET", 3},
    std::string_view{"MET", 3},
    std::string_view{"MET", 3},
    std::string_view{"MET", 3},
    std::string_view{"MET", 3},
    std::string_view{"MET", 3},
    std::string_view{"MET", 3},
    std::string_view{"MET", 3},
    std::string_view{"RESCUE", 6},
    std::string_view{"RESCUE", 6},
    std::string_view{"RESCUE", 6},
    std::string_view{"RESCUE", 6},
    std::string_view{"RESCUE", 6},
    std::string_view{"SAFETY", 6},
    std::string_view{"SAFETY", 6},
    std::string_view{"SAFETY", 6},
    std::string_view{"SAFETY", 6},
    std::string_view{"SAFETY", 6},
    std::string_view{"SAFETY", 6},
    std::string_view{"SAFETY", 6},
    std::string_view{"SAFETY", 6},
    std::string_view{"SAFETY", 6},
    std::string_view{"SAFETY", 6},
    std::string_view{"SECURITY", 8},
    std::string_view{"SECURITY", 8},
    std::string_view{"SECURITY", 8},
    std::string_view{"SECURITY", 8},
    std::string_view{"SECURITY", 8},
    std::string_view{"SECURITY", 8},
    std::string_view{"TRANSPORT", 9},
    std::string_view{"TRANSPORT", 9},
    std::string_view{"TRANSPORT", 9},
    std::string_view{"TRANSPORT", 9},
    std::string_view{"TRANSPORT", 9},
    std::string_view{"TRANSPORT", 9},
    std::string_view{"TRANSPORT", 9},
    std::string_view{"TRANSPORT", 9},
    std::string_view{"TRANSPORT", 9},
    std::string_view{"OTHER", 5}
};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_a4_hazard_category_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_BASE || id >= QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_BASE + QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_SIZE) return std::nullopt;
    return QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_TABLE[id - QZSS_DCX_CAMF_A4_HAZARD_CATEGORY_BASE];
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_a4_hazard_category_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_a4_hazard_category_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
