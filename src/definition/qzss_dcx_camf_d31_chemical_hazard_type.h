#pragma once
// AUTO-GENERATED from azarashi 0.16.4 with CI-CD
// Source module : qzss_dcx_camf_d31_chemical_hazard_type
// Variable      : qzss_dcx_camf_d31_chemical_hazard_type
// Entries       : 16
// Strategy      : array

// NOTE: This function may return nullptr for unknown IDs.
// Callers MUST perform a null-check before using the result.

#include <cstdint>
#include <optional>
#include <string_view>
#include "../azaraC.h"
#include "../internal/FlashString.h"

namespace azaraC {
namespace def {

#if (AZARAC_ENABLE_DCX_CAMF)

inline constexpr uint8_t QZSS_DCX_CAMF_D31_CHEMICAL_HAZARD_TYPE_BASE = 0;
inline constexpr uint8_t QZSS_DCX_CAMF_D31_CHEMICAL_HAZARD_TYPE_SIZE = 16;
#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D31_CHEMICAL_HAZARD_TYPE_POOL[] = "Explosives\0Flammable gases\0Flammable aerosols and aerosols\0Oxidizing gases\0Gases under pressure\0Flammable liquids\0Flammable solids\0Self-reactive substance/mixture\0Pyrophoric liquids. Pyrophoric materials are often water-reactive as well and will ignite when they contact water or humid air.\0Pyrophoric solids. Pyrophoric materials are often water-reactive as well and will ignite when they contact water or humid air.\0Self-heating substance/mixture\0Water-reactive - emits flammable gases\0Oxidising liquids\0Oxidising solids\0Organic peroxides\0Corrosive to metals\0";
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
    if (n == 0) return std::nullopt;
    return azarac_pgm_view(QZSS_DCX_CAMF_D31_CHEMICAL_HAZARD_TYPE_POOL + off, n);
}
#else
inline constexpr std::optional<std::string_view> QZSS_DCX_CAMF_D31_CHEMICAL_HAZARD_TYPE_TABLE[] = {
    std::string_view{"Explosives", 10},
    std::string_view{"Flammable gases", 15},
    std::string_view{"Flammable aerosols and aerosols", 31},
    std::string_view{"Oxidizing gases", 15},
    std::string_view{"Gases under pressure", 20},
    std::string_view{"Flammable liquids", 17},
    std::string_view{"Flammable solids", 16},
    std::string_view{"Self-reactive substance/mixture", 31},
    std::string_view{"Pyrophoric liquids. Pyrophoric materials are often water-reactive as well and will ignite when they contact water or humid air.", 127},
    std::string_view{"Pyrophoric solids. Pyrophoric materials are often water-reactive as well and will ignite when they contact water or humid air.", 126},
    std::string_view{"Self-heating substance/mixture", 30},
    std::string_view{"Water-reactive - emits flammable gases", 38},
    std::string_view{"Oxidising liquids", 17},
    std::string_view{"Oxidising solids", 16},
    std::string_view{"Organic peroxides", 17},
    std::string_view{"Corrosive to metals", 19}
};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d31_chemical_hazard_type_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCX_CAMF_D31_CHEMICAL_HAZARD_TYPE_BASE || id >= QZSS_DCX_CAMF_D31_CHEMICAL_HAZARD_TYPE_BASE + QZSS_DCX_CAMF_D31_CHEMICAL_HAZARD_TYPE_SIZE) return std::nullopt;
    return QZSS_DCX_CAMF_D31_CHEMICAL_HAZARD_TYPE_TABLE[id - QZSS_DCX_CAMF_D31_CHEMICAL_HAZARD_TYPE_BASE];
}
#endif

#else

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d31_chemical_hazard_type_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}

#endif

} // namespace def
} // namespace azaraC
