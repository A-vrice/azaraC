#pragma once
// AUTO-GENERATED from azarashi 0.16.4 with CI-CD
// Source module : qzss_dcx_camf_b4_lower_level_fields_tables
// Variable      : qzss_dcx_camf_d27_noise_range
// Entries       : 12
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

inline constexpr uint8_t QZSS_DCX_CAMF_D27_NOISE_RANGE_BASE = 0;
inline constexpr uint8_t QZSS_DCX_CAMF_D27_NOISE_RANGE_SIZE = 12;
#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D27_NOISE_RANGE_POOL[] = "40 < dB ≤ 45\00045 < dB ≤ 50\00050 < dB ≤ 60\00060 < dB ≤ 70\00070 < dB ≤ 80 (loud)\00080 < dB ≤ 90 (very loud)\00090 < dB ≤ 100 (very loud)\000100 < dB ≤ 110 (very loud)\000110 < dB ≤ 120 (extremely loud)\000120 < dB ≤ 130 (extremely loud)\000130 < dB ≤ 140 (threshold of pain)\000dB > 140 (pain)\000";
struct QZSS_DCX_CAMF_D27_NOISE_RANGE_Entry { uint16_t offset; uint16_t len; };
static const QZSS_DCX_CAMF_D27_NOISE_RANGE_Entry QZSS_DCX_CAMF_D27_NOISE_RANGE_TABLE[] AZARAC_PROGMEM = {
    {0u, 14u},
    {15u, 14u},
    {30u, 14u},
    {45u, 14u},
    {60u, 21u},
    {82u, 26u},
    {109u, 27u},
    {137u, 28u},
    {166u, 33u},
    {200u, 33u},
    {234u, 36u},
    {271u, 15u}
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d27_noise_range_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCX_CAMF_D27_NOISE_RANGE_BASE || id >= QZSS_DCX_CAMF_D27_NOISE_RANGE_BASE + QZSS_DCX_CAMF_D27_NOISE_RANGE_SIZE) return std::nullopt;
    const char* AZARAC_PROGMEM p = reinterpret_cast<const char*>(&QZSS_DCX_CAMF_D27_NOISE_RANGE_TABLE[id - 0u]);
    uint16_t off = pgm_read_word(p + offsetof(QZSS_DCX_CAMF_D27_NOISE_RANGE_Entry, offset));
    uint16_t n = pgm_read_word(p + offsetof(QZSS_DCX_CAMF_D27_NOISE_RANGE_Entry, len));
    if (n == 0) return std::nullopt;
    return azarac_pgm_view(QZSS_DCX_CAMF_D27_NOISE_RANGE_POOL + off, n);
}
#else
inline constexpr std::optional<std::string_view> QZSS_DCX_CAMF_D27_NOISE_RANGE_TABLE[] = {
    std::string_view{"40 < dB ≤ 45", 14},
    std::string_view{"45 < dB ≤ 50", 14},
    std::string_view{"50 < dB ≤ 60", 14},
    std::string_view{"60 < dB ≤ 70", 14},
    std::string_view{"70 < dB ≤ 80 (loud)", 21},
    std::string_view{"80 < dB ≤ 90 (very loud)", 26},
    std::string_view{"90 < dB ≤ 100 (very loud)", 27},
    std::string_view{"100 < dB ≤ 110 (very loud)", 28},
    std::string_view{"110 < dB ≤ 120 (extremely loud)", 33},
    std::string_view{"120 < dB ≤ 130 (extremely loud)", 33},
    std::string_view{"130 < dB ≤ 140 (threshold of pain)", 36},
    std::string_view{"dB > 140 (pain)", 15}
};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d27_noise_range_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCX_CAMF_D27_NOISE_RANGE_BASE || id >= QZSS_DCX_CAMF_D27_NOISE_RANGE_BASE + QZSS_DCX_CAMF_D27_NOISE_RANGE_SIZE) return std::nullopt;
    return QZSS_DCX_CAMF_D27_NOISE_RANGE_TABLE[id - QZSS_DCX_CAMF_D27_NOISE_RANGE_BASE];
}
#endif

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
