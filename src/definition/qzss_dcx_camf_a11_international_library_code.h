#pragma once
// AUTO-GENERATED from azarashi 0.16.4 with CI-CD
// Source module : qzss_dcx_camf_a11_international_library_code
// Variable      : qzss_dcx_camf_a11_international_library_code
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

inline constexpr uint8_t QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_CODE_BASE = 0;
inline constexpr uint8_t QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_CODE_SIZE = 32;
#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_CODE_POOL[] = "IC-A-01\000IC-A-02\000IC-A-03\000IC-A-04\000IC-A-05\000IC-A-06\000IC-A-07\000IC-A-08\000IC-A-09\000IC-A-10\000IC-A-11\000IC-A-12\000IC-A-13\000IC-A-14\000IC-A-15\000IC-A-16\000IC-A-17\000IC-A-18\000IC-A-19\000IC-A-20\000IC-A-21\000IC-A-22\000IC-A-23\000IC-A-24\000IC-A-25\000IC-A-26\000IC-A-27\000IC-A-28\000IC-A-29\000IC-A-30\000IC-A-31\000IC-A-32\000";
struct QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_CODE_Entry { uint16_t offset; uint16_t len; };
static const QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_CODE_Entry QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_CODE_TABLE[] AZARAC_PROGMEM = {
    {0u, 7u},
    {8u, 7u},
    {16u, 7u},
    {24u, 7u},
    {32u, 7u},
    {40u, 7u},
    {48u, 7u},
    {56u, 7u},
    {64u, 7u},
    {72u, 7u},
    {80u, 7u},
    {88u, 7u},
    {96u, 7u},
    {104u, 7u},
    {112u, 7u},
    {120u, 7u},
    {128u, 7u},
    {136u, 7u},
    {144u, 7u},
    {152u, 7u},
    {160u, 7u},
    {168u, 7u},
    {176u, 7u},
    {184u, 7u},
    {192u, 7u},
    {200u, 7u},
    {208u, 7u},
    {216u, 7u},
    {224u, 7u},
    {232u, 7u},
    {240u, 7u},
    {248u, 7u}
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_a11_international_library_code_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_CODE_BASE || id >= QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_CODE_BASE + QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_CODE_SIZE) return std::nullopt;
    const char* AZARAC_PROGMEM p = reinterpret_cast<const char*>(&QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_CODE_TABLE[id - 0u]);
    uint16_t off = pgm_read_word(p + offsetof(QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_CODE_Entry, offset));
    uint16_t n = pgm_read_word(p + offsetof(QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_CODE_Entry, len));
    if (n == 0) return std::nullopt;
    return azarac_pgm_view(QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_CODE_POOL + off, n);
}
#else
inline constexpr std::optional<std::string_view> QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_CODE_TABLE[] = {
    std::string_view{"IC-A-01", 7},
    std::string_view{"IC-A-02", 7},
    std::string_view{"IC-A-03", 7},
    std::string_view{"IC-A-04", 7},
    std::string_view{"IC-A-05", 7},
    std::string_view{"IC-A-06", 7},
    std::string_view{"IC-A-07", 7},
    std::string_view{"IC-A-08", 7},
    std::string_view{"IC-A-09", 7},
    std::string_view{"IC-A-10", 7},
    std::string_view{"IC-A-11", 7},
    std::string_view{"IC-A-12", 7},
    std::string_view{"IC-A-13", 7},
    std::string_view{"IC-A-14", 7},
    std::string_view{"IC-A-15", 7},
    std::string_view{"IC-A-16", 7},
    std::string_view{"IC-A-17", 7},
    std::string_view{"IC-A-18", 7},
    std::string_view{"IC-A-19", 7},
    std::string_view{"IC-A-20", 7},
    std::string_view{"IC-A-21", 7},
    std::string_view{"IC-A-22", 7},
    std::string_view{"IC-A-23", 7},
    std::string_view{"IC-A-24", 7},
    std::string_view{"IC-A-25", 7},
    std::string_view{"IC-A-26", 7},
    std::string_view{"IC-A-27", 7},
    std::string_view{"IC-A-28", 7},
    std::string_view{"IC-A-29", 7},
    std::string_view{"IC-A-30", 7},
    std::string_view{"IC-A-31", 7},
    std::string_view{"IC-A-32", 7}
};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_a11_international_library_code_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_CODE_BASE || id >= QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_CODE_BASE + QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_CODE_SIZE) return std::nullopt;
    return QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_CODE_TABLE[id - QZSS_DCX_CAMF_A11_INTERNATIONAL_LIBRARY_CODE_BASE];
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_a11_international_library_code_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_a11_international_library_code_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
