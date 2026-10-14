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
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D31_CHEMICAL_HAZARD_TYPE_POOL[] = "Explosive\000Flammable gase\000Flammable aerosols and aerosol\000Oxidizing gase\000Gases under pressure\000Flammable liquid\000Flammable solid\000Self-reactive substance/mixture\000Pyrophoric liquids. Pyrophoric materials are often water-reactive as well and will ignite when they contact water or humid air.\000Pyrophoric solids. Pyrophoric materials are often water-reactive as well and will ignite when they contact water or humid air.\000Self-heating substance/mixture\000Water-reactive - emits flammable gase\000Oxidising liquid\000Oxidising solid\000Organic peroxide\000Corrosive to metal\000";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D31_CHEMICAL_HAZARD_TYPE_PARENT_POOL[] = "s\000";
struct QZSS_DCX_CAMF_D31_CHEMICAL_HAZARD_TYPE_PARENT_Entry { uint16_t offset; uint8_t len; };
static const QZSS_DCX_CAMF_D31_CHEMICAL_HAZARD_TYPE_PARENT_Entry QZSS_DCX_CAMF_D31_CHEMICAL_HAZARD_TYPE_PARENT_TABLE[] AZARAC_PROGMEM = {
    {0u, 1u},
};
struct QZSS_DCX_CAMF_D31_CHEMICAL_HAZARD_TYPE_Entry { uint16_t offset; uint8_t len; uint8_t parent; };
static const QZSS_DCX_CAMF_D31_CHEMICAL_HAZARD_TYPE_Entry QZSS_DCX_CAMF_D31_CHEMICAL_HAZARD_TYPE_TABLE[] AZARAC_PROGMEM = {
    {0u, 9u, 0u},
    {10u, 14u, 0u},
    {25u, 30u, 0u},
    {56u, 14u, 0u},
    {71u, 20u, 255u},
    {92u, 16u, 0u},
    {109u, 15u, 0u},
    {125u, 31u, 255u},
    {157u, 127u, 255u},
    {285u, 126u, 255u},
    {412u, 30u, 255u},
    {443u, 37u, 0u},
    {481u, 16u, 0u},
    {498u, 15u, 0u},
    {514u, 16u, 0u},
    {531u, 18u, 0u}
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d31_chemical_hazard_type_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCX_CAMF_D31_CHEMICAL_HAZARD_TYPE_BASE || id >= QZSS_DCX_CAMF_D31_CHEMICAL_HAZARD_TYPE_BASE + QZSS_DCX_CAMF_D31_CHEMICAL_HAZARD_TYPE_SIZE) return std::nullopt;
    const char* AZARAC_PROGMEM p = reinterpret_cast<const char*>(&QZSS_DCX_CAMF_D31_CHEMICAL_HAZARD_TYPE_TABLE[id - 0u]);
    uint16_t off = pgm_read_word(p + offsetof(QZSS_DCX_CAMF_D31_CHEMICAL_HAZARD_TYPE_Entry, offset));
    uint8_t n = pgm_read_byte(p + offsetof(QZSS_DCX_CAMF_D31_CHEMICAL_HAZARD_TYPE_Entry, len));
    uint8_t pi = pgm_read_byte(p + offsetof(QZSS_DCX_CAMF_D31_CHEMICAL_HAZARD_TYPE_Entry, parent));
    if (pi == 255u) return azarac_pgm_view(QZSS_DCX_CAMF_D31_CHEMICAL_HAZARD_TYPE_POOL + off, n);
    const char* AZARAC_PROGMEM pp = reinterpret_cast<const char*>(&QZSS_DCX_CAMF_D31_CHEMICAL_HAZARD_TYPE_PARENT_TABLE[pi]);
    uint16_t poff = pgm_read_word(pp + offsetof(QZSS_DCX_CAMF_D31_CHEMICAL_HAZARD_TYPE_PARENT_Entry, offset));
    uint8_t pn = pgm_read_byte(pp + offsetof(QZSS_DCX_CAMF_D31_CHEMICAL_HAZARD_TYPE_PARENT_Entry, len));
    return azarac_pgm_join(QZSS_DCX_CAMF_D31_CHEMICAL_HAZARD_TYPE_POOL + off, n, QZSS_DCX_CAMF_D31_CHEMICAL_HAZARD_TYPE_PARENT_POOL + poff, pn);
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
