#pragma once
// AUTO-GENERATED from azarashi 0.16.4 with CI-CD
// Source module : qzss_dcx_camf_b4_lower_level_fields_tables
// Variable      : qzss_dcx_camf_d20_ash_fall_amount_and_impact
// Entries       : 5
// Strategy      : switch

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

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d20_ash_fall_amount_and_impact_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: { static const char AZARAC_PROGMEM s[] = "Less than 1 mm ash thickness. Possible impact: Will act as an irritant to lungs and eyes. Possible minor damage to vehicles, houses and equipment caused by fine abrasive ash. Possible contamination of water supplies, particularly roof-fed tank supplies. Dust may affect road visibility and traction for an extended period."; return azarac_pgm_view(s, 322); }
        case 1: { static const char AZARAC_PROGMEM s[] = "1-5 mm ash thickness. Possible impact: Will act as an irritant to lungs and eyes. Minor damage to vehicles, houses and equipment caused by fine abrasive ash. Possible contamination of water supplies, particularly roof-fed tank supplies. Electricity and water supplies may be cut or limited. Dust may affect road visibility and traction for an extended period. Roads may need to be cleared to reduce the dust nuisance and prevent storm-water systems from becoming blocked. Possible crop damage. Some livestock may be affected."; return azarac_pgm_view(s, 525); }
        case 2: { static const char AZARAC_PROGMEM s[] = "5-100 mm ash thickness. Possible impact: Will act as an irritant to lungs and eyes. Damage to vehicles, houses and equipment caused by fine abrasive ash. Most buildings will support the ash load but weaker roof structures may collapse at 100 mm ash thickness, particularly if the ash is wet. Possible contamination of water supplies, particularly roof-fed tank supplies. Electricity and water supplies may be cut or limited. Road transport may be halted due to the build-up of ash on roads. Cars still working may soon stop due to clogging of air-filters. Rail transport may be forced to stop due to signal failure bought on by short circuiting if ash becomes wet. Likely crop damage. Most pastures will be killed by over 50 mm of ash. Some livestock may be affected."; return azarac_pgm_view(s, 767); }
        case 3: { static const char AZARAC_PROGMEM s[] = "100-300 mm ash thickness. Possible impact: Will act as an irritant to lungs and eyes. Damage to vehicles, houses and equipment caused by fine abrasive ash. Buildings that are not cleared of ash will run the risk of roof collapse, especially large flat roofed structures and if ash becomes wet. Possible contamination of water supplies, particularly roof-fed tank supplies. Electricity and water supplies may be cut or limited. Road transport may be halted due to the build-up of ash on roads. Cars still working may soon stop due to clogging of air-filters. Rail transport may be forced to stop due to signal failure bought on by short circuiting if ash becomes wet. Likely crop damage. Most pastures will be killed by over 50 mm of ash. Some livestock may be affected."; return azarac_pgm_view(s, 769); }
        case 4: { static const char AZARAC_PROGMEM s[] = "> 300 mm ash thickness. Possible impact: Will act as an irritant to lungs and eyes. Damage to vehicles, houses and equipment caused by fine abrasive ash. Buildings that are not cleared of ash will run the risk of roof collapse, especially large flat roofed structures and if ash becomes wet. Possible contamination of water supplies, particularly roof-fed tank supplies. Electricity and water supplies may be cut or limited. Road unusable until cleared. Rail transport may be forced to stop due to signal failure bought on by short circuiting if ash becomes wet. Heavy kill of vegetation. Livestock and other animals killed or heavily distressed."; return azarac_pgm_view(s, 646); }
        default: return std::nullopt;
    }
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d20_ash_fall_amount_and_impact_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return std::string_view{"Less than 1 mm ash thickness. Possible impact: Will act as an irritant to lungs and eyes. Possible minor damage to vehicles, houses and equipment caused by fine abrasive ash. Possible contamination of water supplies, particularly roof-fed tank supplies. Dust may affect road visibility and traction for an extended period.", 322};
        case 1: return std::string_view{"1-5 mm ash thickness. Possible impact: Will act as an irritant to lungs and eyes. Minor damage to vehicles, houses and equipment caused by fine abrasive ash. Possible contamination of water supplies, particularly roof-fed tank supplies. Electricity and water supplies may be cut or limited. Dust may affect road visibility and traction for an extended period. Roads may need to be cleared to reduce the dust nuisance and prevent storm-water systems from becoming blocked. Possible crop damage. Some livestock may be affected.", 525};
        case 2: return std::string_view{"5-100 mm ash thickness. Possible impact: Will act as an irritant to lungs and eyes. Damage to vehicles, houses and equipment caused by fine abrasive ash. Most buildings will support the ash load but weaker roof structures may collapse at 100 mm ash thickness, particularly if the ash is wet. Possible contamination of water supplies, particularly roof-fed tank supplies. Electricity and water supplies may be cut or limited. Road transport may be halted due to the build-up of ash on roads. Cars still working may soon stop due to clogging of air-filters. Rail transport may be forced to stop due to signal failure bought on by short circuiting if ash becomes wet. Likely crop damage. Most pastures will be killed by over 50 mm of ash. Some livestock may be affected.", 767};
        case 3: return std::string_view{"100-300 mm ash thickness. Possible impact: Will act as an irritant to lungs and eyes. Damage to vehicles, houses and equipment caused by fine abrasive ash. Buildings that are not cleared of ash will run the risk of roof collapse, especially large flat roofed structures and if ash becomes wet. Possible contamination of water supplies, particularly roof-fed tank supplies. Electricity and water supplies may be cut or limited. Road transport may be halted due to the build-up of ash on roads. Cars still working may soon stop due to clogging of air-filters. Rail transport may be forced to stop due to signal failure bought on by short circuiting if ash becomes wet. Likely crop damage. Most pastures will be killed by over 50 mm of ash. Some livestock may be affected.", 769};
        case 4: return std::string_view{"> 300 mm ash thickness. Possible impact: Will act as an irritant to lungs and eyes. Damage to vehicles, houses and equipment caused by fine abrasive ash. Buildings that are not cleared of ash will run the risk of roof collapse, especially large flat roofed structures and if ash becomes wet. Possible contamination of water supplies, particularly roof-fed tank supplies. Electricity and water supplies may be cut or limited. Road unusable until cleared. Rail transport may be forced to stop due to signal failure bought on by short circuiting if ash becomes wet. Heavy kill of vegetation. Livestock and other animals killed or heavily distressed.", 646};
        default: return std::nullopt;
    }
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d20_ash_fall_amount_and_impact_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d20_ash_fall_amount_and_impact_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
