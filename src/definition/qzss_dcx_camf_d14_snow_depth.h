#pragma once
// AUTO-GENERATED from azarashi 0.17.1 — do not edit
// Specs: IS-QZSS-DCR-017 / IS-QZSS-DCX-004 Rev.004 / EWSS CAMF Issue 1.2
// azarashi.definitions.camf.d_fields → qzss_dcx_camf_d14_snow_depth: 31 entries, strategy array
// Unknown id returns nullptr — callers MUST null-check.

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
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D14_SNOW_DEPTH_POOL[] = "0cm < daily snow depth ≤ \00020cm < daily snow depth ≤ \00040cm < daily snow depth ≤ \00060cm < daily snow depth ≤ \00080cm < daily snow depth ≤ 1\000100cm < daily snow depth ≤ 1\000120cm < daily snow depth ≤ 1\000140cm < daily snow depth ≤ 1\000160cm < daily snow depth ≤ 1\000180cm < daily snow depth ≤ 2\000200cm < daily snow depth ≤ 2\000220cm < daily snow depth ≤ 2\000240cm < daily snow depth ≤ 2\000260cm < daily snow depth ≤ 2\000280cm < daily snow depth ≤ 3\000300cm < daily snow depth ≤ 3\000320cm < daily snow depth ≤ 3\000340cm < daily snow depth ≤ 3\000360cm < daily snow depth ≤ 3\000380cm < daily snow depth ≤ 4\000400cm < daily snow depth ≤ 4\000420cm < daily snow depth ≤ 4\000440cm < daily snow depth ≤ 4\000460cm < daily snow depth ≤ 4\000480cm < daily snow depth ≤ 5\000500cm < daily snow depth ≤ 5\000520cm < daily snow depth ≤ 5\000540cm < daily snow depth ≤ 5\000560cm < daily snow depth ≤ 5\000580cm < daily snow depth ≤ 6\000daily snow depth > 6\000";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D14_SNOW_DEPTH_PARENT_POOL[] = "00cm\00020cm\00040cm\00060cm\00080cm\000";
struct QZSS_DCX_CAMF_D14_SNOW_DEPTH_PARENT_Entry { uint16_t offset; };
static const QZSS_DCX_CAMF_D14_SNOW_DEPTH_PARENT_Entry QZSS_DCX_CAMF_D14_SNOW_DEPTH_PARENT_TABLE[] AZARAC_PROGMEM = {
    {0u},
    {5u},
    {10u},
    {15u},
    {20u},
};
struct QZSS_DCX_CAMF_D14_SNOW_DEPTH_Entry { uint16_t offset; uint8_t parent; };
static const QZSS_DCX_CAMF_D14_SNOW_DEPTH_Entry QZSS_DCX_CAMF_D14_SNOW_DEPTH_TABLE[] AZARAC_PROGMEM = {
    {0u, 1u},
    {28u, 2u},
    {57u, 3u},
    {86u, 4u},
    {115u, 0u},
    {145u, 1u},
    {176u, 2u},
    {207u, 3u},
    {238u, 4u},
    {269u, 0u},
    {300u, 1u},
    {331u, 2u},
    {362u, 3u},
    {393u, 4u},
    {424u, 0u},
    {455u, 1u},
    {486u, 2u},
    {517u, 3u},
    {548u, 4u},
    {579u, 0u},
    {610u, 1u},
    {641u, 2u},
    {672u, 3u},
    {703u, 4u},
    {734u, 0u},
    {765u, 1u},
    {796u, 2u},
    {827u, 3u},
    {858u, 4u},
    {889u, 0u},
    {920u, 0u}
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d14_snow_depth_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCX_CAMF_D14_SNOW_DEPTH_BASE || id >= QZSS_DCX_CAMF_D14_SNOW_DEPTH_BASE + QZSS_DCX_CAMF_D14_SNOW_DEPTH_SIZE) return std::nullopt;
    azarac_pgm_ptr p = AZARAC_PGM_PTR(QZSS_DCX_CAMF_D14_SNOW_DEPTH_TABLE) + static_cast<size_t>(id - 0u) * sizeof(QZSS_DCX_CAMF_D14_SNOW_DEPTH_Entry);
    uint16_t off = azarac_read_word(p, offsetof(QZSS_DCX_CAMF_D14_SNOW_DEPTH_Entry, offset));
    uint8_t pi = azarac_read_byte(p, offsetof(QZSS_DCX_CAMF_D14_SNOW_DEPTH_Entry, parent));
    if (pi == 255u) return azarac_pgm_view_z(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D14_SNOW_DEPTH_POOL) + off);
    azarac_pgm_ptr pp = AZARAC_PGM_PTR(QZSS_DCX_CAMF_D14_SNOW_DEPTH_PARENT_TABLE) + static_cast<size_t>(pi) * sizeof(QZSS_DCX_CAMF_D14_SNOW_DEPTH_PARENT_Entry);
    uint16_t poff = azarac_read_word(pp, offsetof(QZSS_DCX_CAMF_D14_SNOW_DEPTH_PARENT_Entry, offset));
    return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D14_SNOW_DEPTH_POOL) + off, AZARAC_PGM_PTR(QZSS_DCX_CAMF_D14_SNOW_DEPTH_PARENT_POOL) + poff);
}

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
