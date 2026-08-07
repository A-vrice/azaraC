#pragma once
// AUTO-GENERATED from azarashi 0.16.4 with CI-CD
// Source module : qzss_dcx_camf_b4_lower_level_fields_tables
// Variable      : qzss_dcx_camf_d12_hail_scale
// Entries       : 11
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

inline constexpr uint8_t QZSS_DCX_CAMF_D12_HAIL_SCALE_BASE = 0;
inline constexpr uint8_t QZSS_DCX_CAMF_D12_HAIL_SCALE_SIZE = 11;
#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D12_HAIL_SCALE_POOL[] = "H0 Hard hail. Typical hail diameter of 5 mm, No damage\000H1 Potentially damaging. Typical hail diameter of 5-15 mm. Slight general damage to plants, crops\000H2 Significant. Typical hail diameter of 10-20 mm. Slight general damage to fruit, crops, vegetation\000H3 Severe. Typical hail diameter of 20-30 mm (size of a walnut). Severe damage to fruit and crops, damage to glass and plastic structures, paint and wood scored\000H4 Severe. Typical hail diameter of 25-40 mm (size of a squash ball). Widespread glass damage, vehicle bodywork damage\000H5 Destructive. Typical hail diameter of 30-50 mm (size of a golf ball). Wholesale destruction of glass, damage to tiled roofs, significant risk of injuries\000H6 Destructive. Typical hail diameter of 40-60 mm. Bodywork of grounded aircraft dented, brick walls pitted\000H7 Destructive. Typical hail diameter of 50-75 mm (size of a tennis ball). Severe roof damage, risk of serious injuries\000H8 Destructive. Typical hail diameter of 60-90 mm (size of a large orange). Severe damage to aircraft bodywork\000H9 Super Hailstorms. Typical hail diameter of 75-100 mm (size of a grapefruit). Extensive structural damage. Risk of severe or even fatal injuries to persons caught in the open\000H10 Super Hailstorms. Typical hail diameter > 100 mm (size of a melon). Extensive structural damage. Risk of severe or even fatal injuries to persons caught in the open\000";
struct QZSS_DCX_CAMF_D12_HAIL_SCALE_Entry { uint16_t offset; uint16_t len; };
static const QZSS_DCX_CAMF_D12_HAIL_SCALE_Entry QZSS_DCX_CAMF_D12_HAIL_SCALE_TABLE[] AZARAC_PROGMEM = {
    {0u, 54u},
    {55u, 97u},
    {153u, 100u},
    {254u, 160u},
    {415u, 118u},
    {534u, 156u},
    {691u, 107u},
    {799u, 119u},
    {919u, 110u},
    {1030u, 176u},
    {1207u, 168u}
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d12_hail_scale_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCX_CAMF_D12_HAIL_SCALE_BASE || id >= QZSS_DCX_CAMF_D12_HAIL_SCALE_BASE + QZSS_DCX_CAMF_D12_HAIL_SCALE_SIZE) return std::nullopt;
    const char* AZARAC_PROGMEM p = reinterpret_cast<const char*>(&QZSS_DCX_CAMF_D12_HAIL_SCALE_TABLE[id - 0u]);
    uint16_t off = pgm_read_word(p + offsetof(QZSS_DCX_CAMF_D12_HAIL_SCALE_Entry, offset));
    uint16_t n = pgm_read_word(p + offsetof(QZSS_DCX_CAMF_D12_HAIL_SCALE_Entry, len));
    if (n == 0) return std::nullopt;
    return azarac_pgm_view(QZSS_DCX_CAMF_D12_HAIL_SCALE_POOL + off, n);
}
#else
inline constexpr std::optional<std::string_view> QZSS_DCX_CAMF_D12_HAIL_SCALE_TABLE[] = {
    std::string_view{"H0 Hard hail. Typical hail diameter of 5 mm, No damage", 54},
    std::string_view{"H1 Potentially damaging. Typical hail diameter of 5-15 mm. Slight general damage to plants, crops", 97},
    std::string_view{"H2 Significant. Typical hail diameter of 10-20 mm. Slight general damage to fruit, crops, vegetation", 100},
    std::string_view{"H3 Severe. Typical hail diameter of 20-30 mm (size of a walnut). Severe damage to fruit and crops, damage to glass and plastic structures, paint and wood scored", 160},
    std::string_view{"H4 Severe. Typical hail diameter of 25-40 mm (size of a squash ball). Widespread glass damage, vehicle bodywork damage", 118},
    std::string_view{"H5 Destructive. Typical hail diameter of 30-50 mm (size of a golf ball). Wholesale destruction of glass, damage to tiled roofs, significant risk of injuries", 156},
    std::string_view{"H6 Destructive. Typical hail diameter of 40-60 mm. Bodywork of grounded aircraft dented, brick walls pitted", 107},
    std::string_view{"H7 Destructive. Typical hail diameter of 50-75 mm (size of a tennis ball). Severe roof damage, risk of serious injuries", 119},
    std::string_view{"H8 Destructive. Typical hail diameter of 60-90 mm (size of a large orange). Severe damage to aircraft bodywork", 110},
    std::string_view{"H9 Super Hailstorms. Typical hail diameter of 75-100 mm (size of a grapefruit). Extensive structural damage. Risk of severe or even fatal injuries to persons caught in the open", 176},
    std::string_view{"H10 Super Hailstorms. Typical hail diameter > 100 mm (size of a melon). Extensive structural damage. Risk of severe or even fatal injuries to persons caught in the open", 168}
};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d12_hail_scale_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCX_CAMF_D12_HAIL_SCALE_BASE || id >= QZSS_DCX_CAMF_D12_HAIL_SCALE_BASE + QZSS_DCX_CAMF_D12_HAIL_SCALE_SIZE) return std::nullopt;
    return QZSS_DCX_CAMF_D12_HAIL_SCALE_TABLE[id - QZSS_DCX_CAMF_D12_HAIL_SCALE_BASE];
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d12_hail_scale_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d12_hail_scale_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
