#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcx_camf_b4_lower_level_fields_tables
// Variable      : qzss_dcx_camf_d31_chemical_hazard_type
// Entries       : 16
// Strategy      : array

#include <cstdint>
#include <optional>
#include <string_view>
#include "../azaraC.h"

namespace azaraC {
namespace def {

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
inline constexpr uint8_t QZSS_DCX_CAMF_D31_CHEMICAL_HAZARD_TYPE_BASE = 0;
inline constexpr uint8_t QZSS_DCX_CAMF_D31_CHEMICAL_HAZARD_TYPE_SIZE = 16;
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d31_chemical_hazard_type_lookup(uint8_t id) {
    if (id < QZSS_DCX_CAMF_D31_CHEMICAL_HAZARD_TYPE_BASE || id >= QZSS_DCX_CAMF_D31_CHEMICAL_HAZARD_TYPE_BASE + QZSS_DCX_CAMF_D31_CHEMICAL_HAZARD_TYPE_SIZE) return std::nullopt;
    return QZSS_DCX_CAMF_D31_CHEMICAL_HAZARD_TYPE_TABLE[id - QZSS_DCX_CAMF_D31_CHEMICAL_HAZARD_TYPE_BASE];
}

} // namespace def
} // namespace azaraC
