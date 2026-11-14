#pragma once
// AUTO-GENERATED from azarashi 0.17.1 — do not edit
// Specs: IS-QZSS-DCR-017 / IS-QZSS-DCX-004 Rev.004 / EWSS CAMF Issue 1.2
// azarashi.definitions.camf.d_fields → qzss_dcx_camf_d22_terrorism_threat_level: 5 entries, strategy switch
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

static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D22_TERRORISM_THREAT_LEVEL_C0[] = "Very low threat level. A violent act of terrorism is highly unlikely. M";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D22_TERRORISM_THREAT_LEVEL_C1[] = "Low threat level. A violent act of terrorism is possible but unlikely. M";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D22_TERRORISM_THREAT_LEVEL_C2[] = "Medium threat level. A violent act of terrorism could occur. Additional m";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D22_TERRORISM_THREAT_LEVEL_C3[] = "High threat level. A violent act of terrorism is likely. Heightened m";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D22_TERRORISM_THREAT_LEVEL_C4[] = "Critical threat level. A violent act of terrorism is highly likely and could occur imminently. Exceptional m";
static const char AZARAC_PROGMEM QZSS_DCX_CAMF_D22_TERRORISM_THREAT_LEVEL_PARENT_POOL[] = "easures are in place to keep the population safe.\000";
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d22_terrorism_threat_level_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D22_TERRORISM_THREAT_LEVEL_C0), AZARAC_PGM_PTR(QZSS_DCX_CAMF_D22_TERRORISM_THREAT_LEVEL_PARENT_POOL) + 0u);
        case 1: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D22_TERRORISM_THREAT_LEVEL_C1), AZARAC_PGM_PTR(QZSS_DCX_CAMF_D22_TERRORISM_THREAT_LEVEL_PARENT_POOL) + 0u);
        case 2: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D22_TERRORISM_THREAT_LEVEL_C2), AZARAC_PGM_PTR(QZSS_DCX_CAMF_D22_TERRORISM_THREAT_LEVEL_PARENT_POOL) + 0u);
        case 3: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D22_TERRORISM_THREAT_LEVEL_C3), AZARAC_PGM_PTR(QZSS_DCX_CAMF_D22_TERRORISM_THREAT_LEVEL_PARENT_POOL) + 0u);
        case 4: return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCX_CAMF_D22_TERRORISM_THREAT_LEVEL_C4), AZARAC_PGM_PTR(QZSS_DCX_CAMF_D22_TERRORISM_THREAT_LEVEL_PARENT_POOL) + 0u);
        default: return std::nullopt;
    }
}

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d22_terrorism_threat_level_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d22_terrorism_threat_level_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
