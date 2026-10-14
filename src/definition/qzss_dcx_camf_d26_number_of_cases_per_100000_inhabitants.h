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
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D26_NUMBER_OF_CASES_PER_100000_INHABITANTS_POOL[] = "0 - 9\00010 - 20\00021 - 50\00051 - 70\00071 - 100\000101- 125\000126 - 150\000151 - 175\000176 - 200\000201 - 250\000251 - 300\000301 - 350\000351 - 400\000401 - 450\000451 - 500\000501 - 750\000751 - 1000\000> 1000\000> 2000\000> 3000\000> 5000\000";
struct QZSS_DCX_CAMF_D26_NUMBER_OF_CASES_PER_100000_INHABITANTS_Entry { uint16_t offset; };
static const QZSS_DCX_CAMF_D26_NUMBER_OF_CASES_PER_100000_INHABITANTS_Entry QZSS_DCX_CAMF_D26_NUMBER_OF_CASES_PER_100000_INHABITANTS_TABLE[] AZARAC_PROGMEM = {
    {0u},
    {6u},
    {14u},
    {22u},
    {30u},
    {39u},
    {48u},
    {58u},
    {68u},
    {78u},
    {88u},
    {98u},
    {108u},
    {118u},
    {128u},
    {138u},
    {148u},
    {159u},
    {166u},
    {173u},
    {180u}
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d26_number_of_cases_per_100000_inhabitants_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCX_CAMF_D26_NUMBER_OF_CASES_PER_100000_INHABITANTS_BASE || id >= QZSS_DCX_CAMF_D26_NUMBER_OF_CASES_PER_100000_INHABITANTS_BASE + QZSS_DCX_CAMF_D26_NUMBER_OF_CASES_PER_100000_INHABITANTS_SIZE) return std::nullopt;
    const char* AZARAC_PROGMEM p = reinterpret_cast<const char*>(&QZSS_DCX_CAMF_D26_NUMBER_OF_CASES_PER_100000_INHABITANTS_TABLE[id - 0u]);
    uint16_t off = pgm_read_word(p + offsetof(QZSS_DCX_CAMF_D26_NUMBER_OF_CASES_PER_100000_INHABITANTS_Entry, offset));
    return azarac_pgm_view_z(QZSS_DCX_CAMF_D26_NUMBER_OF_CASES_PER_100000_INHABITANTS_POOL + off);
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
