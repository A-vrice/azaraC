#pragma once
// AUTO-GENERATED from azarashi 0.16.4 with CI-CD
// Source module : qzss_dcx_camf_b4_lower_level_fields_tables
// Variable      : qzss_dcx_camf_d31_chemical_hazard_type
// Entries       : 16
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

inline constexpr uint8_t QZSS_DCX_CAMF_D31_CHEMICAL_HAZARD_TYPE_BASE = 0;
inline constexpr uint8_t QZSS_DCX_CAMF_D31_CHEMICAL_HAZARD_TYPE_SIZE = 16;
#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D31_CHEMICAL_HAZARD_TYPE_POOL[] = "Explosives\000Flammable gases\000Flammable aerosols and aerosols\000Oxidizing gases\000Gases under pressure\000Flammable liquids\000Flammable solids\000Self-reactive substance/mixture\000Pyrophoric liquids. Pyrophoric materials are often water-reactive as well and will ignite when they contact water or humid air.\000Pyrophoric solids. Pyrophoric materials are often water-reactive as well and will ignite when they contact water or humid air.\000Self-heating substance/mixture\000Water-reactive - emits flammable gases\000Oxidising liquids\000Oxidising solids\000Organic peroxides\000Corrosive to metals\000";
struct QZSS_DCX_CAMF_D31_CHEMICAL_HAZARD_TYPE_Entry { uint16_t offset; uint16_t len; };
static const QZSS_DCX_CAMF_D31_CHEMICAL_HAZARD_TYPE_Entry QZSS_DCX_CAMF_D31_CHEMICAL_HAZARD_TYPE_TABLE[] AZARAC_PROGMEM = {
    {0u, 10u},
    {11u, 15u},
    {27u, 31u},
    {59u, 15u},
    {75u, 20u},
    {96u, 17u},
    {114u, 16u},
    {131u, 31u},
    {163u, 127u},
    {291u, 126u},
    {418u, 30u},
    {449u, 38u},
    {488u, 17u},
    {506u, 16u},
    {523u, 17u},
    {541u, 19u}
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d31_chemical_hazard_type_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCX_CAMF_D31_CHEMICAL_HAZARD_TYPE_BASE || id >= QZSS_DCX_CAMF_D31_CHEMICAL_HAZARD_TYPE_BASE + QZSS_DCX_CAMF_D31_CHEMICAL_HAZARD_TYPE_SIZE) return std::nullopt;
    const char* AZARAC_PROGMEM p = reinterpret_cast<const char*>(&QZSS_DCX_CAMF_D31_CHEMICAL_HAZARD_TYPE_TABLE[id - 0u]);
    uint16_t off = pgm_read_word(p + offsetof(QZSS_DCX_CAMF_D31_CHEMICAL_HAZARD_TYPE_Entry, offset));
    uint16_t n = pgm_read_word(p + offsetof(QZSS_DCX_CAMF_D31_CHEMICAL_HAZARD_TYPE_Entry, len));
    return azarac_pgm_view(QZSS_DCX_CAMF_D31_CHEMICAL_HAZARD_TYPE_POOL + off, n);
}
#else
inline constexpr const char* QZSS_DCX_CAMF_D31_CHEMICAL_HAZARD_TYPE_TABLE[] = {
    "Explosives",
    "Flammable gases",
    "Flammable aerosols and aerosols",
    "Oxidizing gases",
    "Gases under pressure",
    "Flammable liquids",
    "Flammable solids",
    "Self-reactive substance/mixture",
    "Pyrophoric liquids. Pyrophoric materials are often water-reactive as well and will ignite when they contact water or humid air.",
    "Pyrophoric solids. Pyrophoric materials are often water-reactive as well and will ignite when they contact water or humid air.",
    "Self-heating substance/mixture",
    "Water-reactive - emits flammable gases",
    "Oxidising liquids",
    "Oxidising solids",
    "Organic peroxides",
    "Corrosive to metals"
};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d31_chemical_hazard_type_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCX_CAMF_D31_CHEMICAL_HAZARD_TYPE_BASE || id >= QZSS_DCX_CAMF_D31_CHEMICAL_HAZARD_TYPE_BASE + QZSS_DCX_CAMF_D31_CHEMICAL_HAZARD_TYPE_SIZE) return std::nullopt;
    const char* s = QZSS_DCX_CAMF_D31_CHEMICAL_HAZARD_TYPE_TABLE[id - QZSS_DCX_CAMF_D31_CHEMICAL_HAZARD_TYPE_BASE];
    return s ? std::optional<std::string_view>(std::string_view{s}) : std::nullopt;
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d31_chemical_hazard_type_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d31_chemical_hazard_type_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
