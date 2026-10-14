#pragma once
// AUTO-GENERATED from azarashi 0.17.1 with CI-CD
// Source module : azarashi.definitions.camf.d_fields
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
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D31_CHEMICAL_HAZARD_TYPE_POOL[] = "Explosives\000gases\000aerosols and aerosols\000Oxidizing gases\000Gases under pressure\000liquids\000solids\000Self-reactive substance/mixture\000Pyrophoric liquids. Pyrophoric materials are often water-reactive as well and will ignite when they contact water or humid air.\000Pyrophoric solids. Pyrophoric materials are often water-reactive as well and will ignite when they contact water or humid air.\000Self-heating substance/mixture\000Water-reactive - emits flammable gases\000Oxidising liquids\000Oxidising solids\000Organic peroxides\000Corrosive to metals\000";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D31_CHEMICAL_HAZARD_TYPE_PARENT_POOL[] = "Flammable \000";
struct QZSS_DCX_CAMF_D31_CHEMICAL_HAZARD_TYPE_PARENT_Entry { uint16_t offset; };
static const QZSS_DCX_CAMF_D31_CHEMICAL_HAZARD_TYPE_PARENT_Entry QZSS_DCX_CAMF_D31_CHEMICAL_HAZARD_TYPE_PARENT_TABLE[] AZARAC_PROGMEM = {
    {0u},
};
struct QZSS_DCX_CAMF_D31_CHEMICAL_HAZARD_TYPE_Entry { uint16_t offset; uint8_t parent; };
static const QZSS_DCX_CAMF_D31_CHEMICAL_HAZARD_TYPE_Entry QZSS_DCX_CAMF_D31_CHEMICAL_HAZARD_TYPE_TABLE[] AZARAC_PROGMEM = {
    {0u, 255u},
    {11u, 0u},
    {17u, 0u},
    {39u, 255u},
    {55u, 255u},
    {76u, 0u},
    {84u, 0u},
    {91u, 255u},
    {123u, 255u},
    {251u, 255u},
    {378u, 255u},
    {409u, 255u},
    {448u, 255u},
    {466u, 255u},
    {483u, 255u},
    {501u, 255u}
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d31_chemical_hazard_type_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCX_CAMF_D31_CHEMICAL_HAZARD_TYPE_BASE || id >= QZSS_DCX_CAMF_D31_CHEMICAL_HAZARD_TYPE_BASE + QZSS_DCX_CAMF_D31_CHEMICAL_HAZARD_TYPE_SIZE) return std::nullopt;
    const char* AZARAC_PROGMEM p = reinterpret_cast<const char*>(&QZSS_DCX_CAMF_D31_CHEMICAL_HAZARD_TYPE_TABLE[id - 0u]);
    uint16_t off = pgm_read_word(p + offsetof(QZSS_DCX_CAMF_D31_CHEMICAL_HAZARD_TYPE_Entry, offset));
    uint8_t pi = pgm_read_byte(p + offsetof(QZSS_DCX_CAMF_D31_CHEMICAL_HAZARD_TYPE_Entry, parent));
    if (pi == 255u) return azarac_pgm_view_z(QZSS_DCX_CAMF_D31_CHEMICAL_HAZARD_TYPE_POOL + off);
    const char* AZARAC_PROGMEM pp = reinterpret_cast<const char*>(&QZSS_DCX_CAMF_D31_CHEMICAL_HAZARD_TYPE_PARENT_TABLE[pi]);
    uint16_t poff = pgm_read_word(pp + offsetof(QZSS_DCX_CAMF_D31_CHEMICAL_HAZARD_TYPE_PARENT_Entry, offset));
    return azarac_pgm_join_z(QZSS_DCX_CAMF_D31_CHEMICAL_HAZARD_TYPE_PARENT_POOL + poff, QZSS_DCX_CAMF_D31_CHEMICAL_HAZARD_TYPE_POOL + off);
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
