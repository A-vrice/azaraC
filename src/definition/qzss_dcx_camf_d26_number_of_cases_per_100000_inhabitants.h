#pragma once
// AUTO-GENERATED from azarashi 0.17.1 with CI-CD
// Source module : azarashi.definitions.camf.d_fields
// Variable      : qzss_dcx_camf_d26_number_of_cases_per_100000_inhabitants
// Entries       : 21
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

inline constexpr uint8_t QZSS_DCX_CAMF_D26_NUMBER_OF_CASES_PER_100000_INHABITANTS_BASE = 0;
inline constexpr uint8_t QZSS_DCX_CAMF_D26_NUMBER_OF_CASES_PER_100000_INHABITANTS_SIZE = 21;
#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D26_NUMBER_OF_CASES_PER_100000_INHABITANTS_POOL[] = "0 - 9\00010 - 2\00021 - \00051 - 7\00071 - 1\000101- 125\000126 - 1\000151 - 175\000176 - 2\000201 - 2\000251 - 3\000301 - 3\000351 - 4\000401 - 4\000451 - 5\000501 - 7\000751 - 10\000> 10\000> 20\000> 30\000> 50\000";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D26_NUMBER_OF_CASES_PER_100000_INHABITANTS_PARENT_POOL[] = "0\00000\00050\000";
struct QZSS_DCX_CAMF_D26_NUMBER_OF_CASES_PER_100000_INHABITANTS_PARENT_Entry { uint16_t offset; uint8_t len; };
static const QZSS_DCX_CAMF_D26_NUMBER_OF_CASES_PER_100000_INHABITANTS_PARENT_Entry QZSS_DCX_CAMF_D26_NUMBER_OF_CASES_PER_100000_INHABITANTS_PARENT_TABLE[] AZARAC_PROGMEM = {
    {0u, 1u},
    {2u, 2u},
    {5u, 2u},
};
struct QZSS_DCX_CAMF_D26_NUMBER_OF_CASES_PER_100000_INHABITANTS_Entry { uint16_t offset; uint8_t len; uint8_t parent; };
static const QZSS_DCX_CAMF_D26_NUMBER_OF_CASES_PER_100000_INHABITANTS_Entry QZSS_DCX_CAMF_D26_NUMBER_OF_CASES_PER_100000_INHABITANTS_TABLE[] AZARAC_PROGMEM = {
    {0u, 5u, 255u},
    {6u, 6u, 0u},
    {13u, 5u, 2u},
    {19u, 6u, 0u},
    {26u, 6u, 1u},
    {33u, 8u, 255u},
    {42u, 7u, 2u},
    {50u, 9u, 255u},
    {60u, 7u, 1u},
    {68u, 7u, 2u},
    {76u, 7u, 1u},
    {84u, 7u, 2u},
    {92u, 7u, 1u},
    {100u, 7u, 2u},
    {108u, 7u, 1u},
    {116u, 7u, 2u},
    {124u, 8u, 1u},
    {133u, 4u, 1u},
    {138u, 4u, 1u},
    {143u, 4u, 1u},
    {148u, 4u, 1u}
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d26_number_of_cases_per_100000_inhabitants_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCX_CAMF_D26_NUMBER_OF_CASES_PER_100000_INHABITANTS_BASE || id >= QZSS_DCX_CAMF_D26_NUMBER_OF_CASES_PER_100000_INHABITANTS_BASE + QZSS_DCX_CAMF_D26_NUMBER_OF_CASES_PER_100000_INHABITANTS_SIZE) return std::nullopt;
    const char* AZARAC_PROGMEM p = reinterpret_cast<const char*>(&QZSS_DCX_CAMF_D26_NUMBER_OF_CASES_PER_100000_INHABITANTS_TABLE[id - 0u]);
    uint16_t off = pgm_read_word(p + offsetof(QZSS_DCX_CAMF_D26_NUMBER_OF_CASES_PER_100000_INHABITANTS_Entry, offset));
    uint8_t n = pgm_read_byte(p + offsetof(QZSS_DCX_CAMF_D26_NUMBER_OF_CASES_PER_100000_INHABITANTS_Entry, len));
    uint8_t pi = pgm_read_byte(p + offsetof(QZSS_DCX_CAMF_D26_NUMBER_OF_CASES_PER_100000_INHABITANTS_Entry, parent));
    if (pi == 255u) return azarac_pgm_view(QZSS_DCX_CAMF_D26_NUMBER_OF_CASES_PER_100000_INHABITANTS_POOL + off, n);
    const char* AZARAC_PROGMEM pp = reinterpret_cast<const char*>(&QZSS_DCX_CAMF_D26_NUMBER_OF_CASES_PER_100000_INHABITANTS_PARENT_TABLE[pi]);
    uint16_t poff = pgm_read_word(pp + offsetof(QZSS_DCX_CAMF_D26_NUMBER_OF_CASES_PER_100000_INHABITANTS_PARENT_Entry, offset));
    uint8_t pn = pgm_read_byte(pp + offsetof(QZSS_DCX_CAMF_D26_NUMBER_OF_CASES_PER_100000_INHABITANTS_PARENT_Entry, len));
    return azarac_pgm_join(QZSS_DCX_CAMF_D26_NUMBER_OF_CASES_PER_100000_INHABITANTS_POOL + off, n, QZSS_DCX_CAMF_D26_NUMBER_OF_CASES_PER_100000_INHABITANTS_PARENT_POOL + poff, pn);
}
#else
inline constexpr const char* QZSS_DCX_CAMF_D26_NUMBER_OF_CASES_PER_100000_INHABITANTS_TABLE[] = {
    "0 - 9",
    "10 - 20",
    "21 - 50",
    "51 - 70",
    "71 - 100",
    "101- 125",
    "126 - 150",
    "151 - 175",
    "176 - 200",
    "201 - 250",
    "251 - 300",
    "301 - 350",
    "351 - 400",
    "401 - 450",
    "451 - 500",
    "501 - 750",
    "751 - 1000",
    "> 1000",
    "> 2000",
    "> 3000",
    "> 5000"
};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d26_number_of_cases_per_100000_inhabitants_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCX_CAMF_D26_NUMBER_OF_CASES_PER_100000_INHABITANTS_BASE || id >= QZSS_DCX_CAMF_D26_NUMBER_OF_CASES_PER_100000_INHABITANTS_BASE + QZSS_DCX_CAMF_D26_NUMBER_OF_CASES_PER_100000_INHABITANTS_SIZE) return std::nullopt;
    const char* s = QZSS_DCX_CAMF_D26_NUMBER_OF_CASES_PER_100000_INHABITANTS_TABLE[id - QZSS_DCX_CAMF_D26_NUMBER_OF_CASES_PER_100000_INHABITANTS_BASE];
    return s ? std::optional<std::string_view>(std::string_view{s}) : std::nullopt;
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d26_number_of_cases_per_100000_inhabitants_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d26_number_of_cases_per_100000_inhabitants_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
