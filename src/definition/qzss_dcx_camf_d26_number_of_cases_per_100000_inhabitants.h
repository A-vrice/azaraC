#pragma once
// AUTO-GENERATED from azarashi 0.16.4 with CI-CD
// Source module : qzss_dcx_camf_b4_lower_level_fields_tables
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
struct QZSS_DCX_CAMF_D26_NUMBER_OF_CASES_PER_100000_INHABITANTS_Entry { uint16_t offset; uint16_t len; };
static const QZSS_DCX_CAMF_D26_NUMBER_OF_CASES_PER_100000_INHABITANTS_Entry QZSS_DCX_CAMF_D26_NUMBER_OF_CASES_PER_100000_INHABITANTS_TABLE[] AZARAC_PROGMEM = {
    {0u, 5u},
    {6u, 7u},
    {14u, 7u},
    {22u, 7u},
    {30u, 8u},
    {39u, 8u},
    {48u, 9u},
    {58u, 9u},
    {68u, 9u},
    {78u, 9u},
    {88u, 9u},
    {98u, 9u},
    {108u, 9u},
    {118u, 9u},
    {128u, 9u},
    {138u, 9u},
    {148u, 10u},
    {159u, 6u},
    {166u, 6u},
    {173u, 6u},
    {180u, 6u}
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d26_number_of_cases_per_100000_inhabitants_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCX_CAMF_D26_NUMBER_OF_CASES_PER_100000_INHABITANTS_BASE || id >= QZSS_DCX_CAMF_D26_NUMBER_OF_CASES_PER_100000_INHABITANTS_BASE + QZSS_DCX_CAMF_D26_NUMBER_OF_CASES_PER_100000_INHABITANTS_SIZE) return std::nullopt;
    const char* AZARAC_PROGMEM p = reinterpret_cast<const char*>(&QZSS_DCX_CAMF_D26_NUMBER_OF_CASES_PER_100000_INHABITANTS_TABLE[id - 0u]);
    uint16_t off = pgm_read_word(p + offsetof(QZSS_DCX_CAMF_D26_NUMBER_OF_CASES_PER_100000_INHABITANTS_Entry, offset));
    uint16_t n = pgm_read_word(p + offsetof(QZSS_DCX_CAMF_D26_NUMBER_OF_CASES_PER_100000_INHABITANTS_Entry, len));
    if (n == 0) return std::nullopt;
    return azarac_pgm_view(QZSS_DCX_CAMF_D26_NUMBER_OF_CASES_PER_100000_INHABITANTS_POOL + off, n);
}
#else
inline constexpr std::optional<std::string_view> QZSS_DCX_CAMF_D26_NUMBER_OF_CASES_PER_100000_INHABITANTS_TABLE[] = {
    std::string_view{"0 - 9", 5},
    std::string_view{"10 - 20", 7},
    std::string_view{"21 - 50", 7},
    std::string_view{"51 - 70", 7},
    std::string_view{"71 - 100", 8},
    std::string_view{"101- 125", 8},
    std::string_view{"126 - 150", 9},
    std::string_view{"151 - 175", 9},
    std::string_view{"176 - 200", 9},
    std::string_view{"201 - 250", 9},
    std::string_view{"251 - 300", 9},
    std::string_view{"301 - 350", 9},
    std::string_view{"351 - 400", 9},
    std::string_view{"401 - 450", 9},
    std::string_view{"451 - 500", 9},
    std::string_view{"501 - 750", 9},
    std::string_view{"751 - 1000", 10},
    std::string_view{"> 1000", 6},
    std::string_view{"> 2000", 6},
    std::string_view{"> 3000", 6},
    std::string_view{"> 5000", 6}
};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d26_number_of_cases_per_100000_inhabitants_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCX_CAMF_D26_NUMBER_OF_CASES_PER_100000_INHABITANTS_BASE || id >= QZSS_DCX_CAMF_D26_NUMBER_OF_CASES_PER_100000_INHABITANTS_BASE + QZSS_DCX_CAMF_D26_NUMBER_OF_CASES_PER_100000_INHABITANTS_SIZE) return std::nullopt;
    return QZSS_DCX_CAMF_D26_NUMBER_OF_CASES_PER_100000_INHABITANTS_TABLE[id - QZSS_DCX_CAMF_D26_NUMBER_OF_CASES_PER_100000_INHABITANTS_BASE];
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
