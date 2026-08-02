#pragma once
// AUTO-GENERATED from azarashi 0.16.4 with CI-CD
// Source module : qzss_dcx_camf_d14_snow_depth
// Variable      : qzss_dcx_camf_d14_snow_depth
// Entries       : 31
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

inline constexpr uint8_t QZSS_DCX_CAMF_D14_SNOW_DEPTH_BASE = 0;
inline constexpr uint8_t QZSS_DCX_CAMF_D14_SNOW_DEPTH_SIZE = 31;
#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D14_SNOW_DEPTH_POOL[] = "0cm < daily snow depth ≤ 20cm\00020cm < daily snow depth ≤ 40cm\00040cm < daily snow depth ≤ 60cm\00060cm < daily snow depth ≤ 80cm\00080cm < daily snow depth ≤ 100cm\000100cm < daily snow depth ≤ 120cm\000120cm < daily snow depth ≤ 140cm\000140cm < daily snow depth ≤ 160cm\000160cm < daily snow depth ≤ 180cm\000180cm < daily snow depth ≤ 200cm\000200cm < daily snow depth ≤ 220cm\000220cm < daily snow depth ≤ 240cm\000240cm < daily snow depth ≤ 260cm\000260cm < daily snow depth ≤ 280cm\000280cm < daily snow depth ≤ 300cm\000300cm < daily snow depth ≤ 320cm\000320cm < daily snow depth ≤ 340cm\000340cm < daily snow depth ≤ 360cm\000360cm < daily snow depth ≤ 380cm\000380cm < daily snow depth ≤ 400cm\000400cm < daily snow depth ≤ 420cm\000420cm < daily snow depth ≤ 440cm\000440cm < daily snow depth ≤ 460cm\000460cm < daily snow depth ≤ 480cm\000480cm < daily snow depth ≤ 500cm\000500cm < daily snow depth ≤ 520cm\000520cm < daily snow depth ≤ 540cm\000540cm < daily snow depth ≤ 560cm\000560cm < daily snow depth ≤ 580cm\000580cm < daily snow depth ≤ 600cm\000daily snow depth > 600cm\000";
struct QZSS_DCX_CAMF_D14_SNOW_DEPTH_Entry { uint16_t offset; uint16_t len; };
static const QZSS_DCX_CAMF_D14_SNOW_DEPTH_Entry QZSS_DCX_CAMF_D14_SNOW_DEPTH_TABLE[] AZARAC_PROGMEM = {
    {0u, 31u},
    {32u, 32u},
    {65u, 32u},
    {98u, 32u},
    {131u, 33u},
    {165u, 34u},
    {200u, 34u},
    {235u, 34u},
    {270u, 34u},
    {305u, 34u},
    {340u, 34u},
    {375u, 34u},
    {410u, 34u},
    {445u, 34u},
    {480u, 34u},
    {515u, 34u},
    {550u, 34u},
    {585u, 34u},
    {620u, 34u},
    {655u, 34u},
    {690u, 34u},
    {725u, 34u},
    {760u, 34u},
    {795u, 34u},
    {830u, 34u},
    {865u, 34u},
    {900u, 34u},
    {935u, 34u},
    {970u, 34u},
    {1005u, 34u},
    {1040u, 24u}
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d14_snow_depth_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCX_CAMF_D14_SNOW_DEPTH_BASE || id >= QZSS_DCX_CAMF_D14_SNOW_DEPTH_BASE + QZSS_DCX_CAMF_D14_SNOW_DEPTH_SIZE) return std::nullopt;
    const char* AZARAC_PROGMEM p = reinterpret_cast<const char*>(&QZSS_DCX_CAMF_D14_SNOW_DEPTH_TABLE[id - 0u]);
    uint16_t off = pgm_read_word(p + offsetof(QZSS_DCX_CAMF_D14_SNOW_DEPTH_Entry, offset));
    uint16_t n = pgm_read_word(p + offsetof(QZSS_DCX_CAMF_D14_SNOW_DEPTH_Entry, len));
    if (n == 0) return std::nullopt;
    return azarac_pgm_view(QZSS_DCX_CAMF_D14_SNOW_DEPTH_POOL + off, n);
}
#else
inline constexpr std::optional<std::string_view> QZSS_DCX_CAMF_D14_SNOW_DEPTH_TABLE[] = {
    std::string_view{"0cm < daily snow depth ≤ 20cm", 31},
    std::string_view{"20cm < daily snow depth ≤ 40cm", 32},
    std::string_view{"40cm < daily snow depth ≤ 60cm", 32},
    std::string_view{"60cm < daily snow depth ≤ 80cm", 32},
    std::string_view{"80cm < daily snow depth ≤ 100cm", 33},
    std::string_view{"100cm < daily snow depth ≤ 120cm", 34},
    std::string_view{"120cm < daily snow depth ≤ 140cm", 34},
    std::string_view{"140cm < daily snow depth ≤ 160cm", 34},
    std::string_view{"160cm < daily snow depth ≤ 180cm", 34},
    std::string_view{"180cm < daily snow depth ≤ 200cm", 34},
    std::string_view{"200cm < daily snow depth ≤ 220cm", 34},
    std::string_view{"220cm < daily snow depth ≤ 240cm", 34},
    std::string_view{"240cm < daily snow depth ≤ 260cm", 34},
    std::string_view{"260cm < daily snow depth ≤ 280cm", 34},
    std::string_view{"280cm < daily snow depth ≤ 300cm", 34},
    std::string_view{"300cm < daily snow depth ≤ 320cm", 34},
    std::string_view{"320cm < daily snow depth ≤ 340cm", 34},
    std::string_view{"340cm < daily snow depth ≤ 360cm", 34},
    std::string_view{"360cm < daily snow depth ≤ 380cm", 34},
    std::string_view{"380cm < daily snow depth ≤ 400cm", 34},
    std::string_view{"400cm < daily snow depth ≤ 420cm", 34},
    std::string_view{"420cm < daily snow depth ≤ 440cm", 34},
    std::string_view{"440cm < daily snow depth ≤ 460cm", 34},
    std::string_view{"460cm < daily snow depth ≤ 480cm", 34},
    std::string_view{"480cm < daily snow depth ≤ 500cm", 34},
    std::string_view{"500cm < daily snow depth ≤ 520cm", 34},
    std::string_view{"520cm < daily snow depth ≤ 540cm", 34},
    std::string_view{"540cm < daily snow depth ≤ 560cm", 34},
    std::string_view{"560cm < daily snow depth ≤ 580cm", 34},
    std::string_view{"580cm < daily snow depth ≤ 600cm", 34},
    std::string_view{"daily snow depth > 600cm", 24}
};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d14_snow_depth_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCX_CAMF_D14_SNOW_DEPTH_BASE || id >= QZSS_DCX_CAMF_D14_SNOW_DEPTH_BASE + QZSS_DCX_CAMF_D14_SNOW_DEPTH_SIZE) return std::nullopt;
    return QZSS_DCX_CAMF_D14_SNOW_DEPTH_TABLE[id - QZSS_DCX_CAMF_D14_SNOW_DEPTH_BASE];
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d14_snow_depth_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d14_snow_depth_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
