#pragma once
// AUTO-GENERATED from azarashi 0.17.1 — do not edit
// Specs: IS-QZSS-DCR-017 / IS-QZSS-DCX-004 Rev.004 / EWSS CAMF Issue 1.2
// azarashi.definitions.camf.d_fields → qzss_dcx_camf_d27_noise_range: 12 entries, strategy array
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

inline constexpr uint8_t QZSS_DCX_CAMF_D27_NOISE_RANGE_BASE = 0;
inline constexpr uint8_t QZSS_DCX_CAMF_D27_NOISE_RANGE_SIZE = 12;
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D27_NOISE_RANGE_POOL[] = "40 < dB ≤ 45\00045 < dB ≤ 50\00050 < dB ≤ 60\00060 < dB ≤ 70\00070 < dB ≤ 80 (\00080 < dB ≤ 90 (ver\00090 < dB ≤ 100 (ver\000100 < dB ≤ 110 (ver\000110 < dB ≤ 120 (extremel\000120 < dB ≤ 130 (extremel\000130 < dB ≤ 140 (threshold of pain)\000dB > 140 (pain)\000";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D27_NOISE_RANGE_PARENT_POOL[] = "loud)\000y loud)\000";
struct QZSS_DCX_CAMF_D27_NOISE_RANGE_PARENT_Entry { uint16_t offset; };
static const QZSS_DCX_CAMF_D27_NOISE_RANGE_PARENT_Entry QZSS_DCX_CAMF_D27_NOISE_RANGE_PARENT_TABLE[] AZARAC_PROGMEM = {
    {0u},
    {6u},
};
struct QZSS_DCX_CAMF_D27_NOISE_RANGE_Entry { uint16_t offset; uint8_t parent; };
static const QZSS_DCX_CAMF_D27_NOISE_RANGE_Entry QZSS_DCX_CAMF_D27_NOISE_RANGE_TABLE[] AZARAC_PROGMEM = {
    {0u, 255u},
    {15u, 255u},
    {30u, 255u},
    {45u, 255u},
    {60u, 0u},
    {77u, 1u},
    {97u, 1u},
    {118u, 1u},
    {140u, 1u},
    {167u, 1u},
    {194u, 255u},
    {231u, 255u}
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d27_noise_range_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCX_CAMF_D27_NOISE_RANGE_BASE || id >= QZSS_DCX_CAMF_D27_NOISE_RANGE_BASE + QZSS_DCX_CAMF_D27_NOISE_RANGE_SIZE) return std::nullopt;
    azarac_pgm_ptr p = AZARAC_PGM_PTR(QZSS_DCX_CAMF_D27_NOISE_RANGE_TABLE) + static_cast<size_t>(id - 0u) * sizeof(QZSS_DCX_CAMF_D27_NOISE_RANGE_Entry);
    uint16_t off = azarac_read_word(p, offsetof(QZSS_DCX_CAMF_D27_NOISE_RANGE_Entry, offset));
    uint8_t pi = azarac_read_byte(p, offsetof(QZSS_DCX_CAMF_D27_NOISE_RANGE_Entry, parent));
    if (pi == 255u) return azarac_pgm_view_z(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D27_NOISE_RANGE_POOL) + off);
    azarac_pgm_ptr pp = AZARAC_PGM_PTR(QZSS_DCX_CAMF_D27_NOISE_RANGE_PARENT_TABLE) + static_cast<size_t>(pi) * sizeof(QZSS_DCX_CAMF_D27_NOISE_RANGE_PARENT_Entry);
    uint16_t poff = azarac_read_word(pp, offsetof(QZSS_DCX_CAMF_D27_NOISE_RANGE_PARENT_Entry, offset));
    return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D27_NOISE_RANGE_POOL) + off, AZARAC_PGM_PTR(QZSS_DCX_CAMF_D27_NOISE_RANGE_PARENT_POOL) + poff);
}

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d27_noise_range_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d27_noise_range_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
