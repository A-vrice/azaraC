#pragma once
// AUTO-GENERATED from azarashi 0.16.4 with CI-CD
// Source module : qzss_dcx_camf_b4_lower_level_fields_tables
// Variable      : qzss_dcx_camf_d30_nuclear_event_scale
// Entries       : 9
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
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d30_nuclear_event_scale_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: { static const char AZARAC_PROGMEM s[] = "Unknown"; return azarac_pgm_view(s, 7); }
        case 1: { static const char AZARAC_PROGMEM s[] = "Level 0/7. Deviation. No safety significance"; return azarac_pgm_view(s, 44); }
        case 2: { static const char AZARAC_PROGMEM s[] = "Level 1/7. Anomaly. Overexposure in excess of statutory annual limits. Minor problems with safety components with significant defence-in-depth remaining. Low activity lost or stolen radioactive source, device, or transport package."; return azarac_pgm_view(s, 231); }
        case 3: { static const char AZARAC_PROGMEM s[] = "Level 2/7. Incident. Impact on people and environment: Exposure of the public in excess of 10 mSv. Exposure of workers in excess of the statutory annual limits. Impact on radiological barriers and control: Radiation levels in an operating area of more than 50 mSv/h. Significant contamination within the facility into an area not expected by design. Possible cause: Significant failures in safety provisions but with no actual consequences. Found highly radioactive sealed orphan source, device or transport package with safety provisions intact. Inadequate packaging of a highly radioactive sealed source."; return azarac_pgm_view(s, 606); }
        case 4: { static const char AZARAC_PROGMEM s[] = "Level 3/7. Serious incident. Impact on people and environment: Exposure in excess of ten times the statutory annual limit for workers. Non-lethal deterministic health effect (e.g., burns) from radiation. Impact on radiological barriers and control: Exposure rates of more than 1 Sv/h in an operating area. Severe contamination in an area not expected by design, with a low probability of significant public exposure. Possible cause: Near-accident at a nuclear power plant with no safety provisions remaining. Lost or stolen highly radioactive sealed source. Misdelivered highly radioactive sealed source without adequate procedures in place to handle it."; return azarac_pgm_view(s, 654); }
        case 5: { static const char AZARAC_PROGMEM s[] = "Level 4/7. Accident with local consequences. Impact on people and environment: Minor release of radioactive material unlikely to result in implementation of planned countermeasures other than local food controls. Impact on radiological barriers and control: Release of significant quantities of radioactive material within an installation with a high probability of significant public exposure."; return azarac_pgm_view(s, 394); }
        case 6: { static const char AZARAC_PROGMEM s[] = "Level 5/7. Accident with wider consequences. Impact on people and environment: Limited release of radioactive material likely to require implementation of some planned countermeasures. Major health impact from radiation is likely. Impact on radiological barriers and control: Severe damage to reactor core. Release of large quantities of radioactive material within an installation with a high probability of significant public exposure. This could arise from a major criticality accident or fire."; return azarac_pgm_view(s, 497); }
        case 7: { static const char AZARAC_PROGMEM s[] = "Level 6/7. Serious accident. Impact on people and environment: Significant release of radioactive material likely to require implementation of planned countermeasures."; return azarac_pgm_view(s, 167); }
        case 8: { static const char AZARAC_PROGMEM s[] = "Level 7/7. Major accident. Impact on people and environment: Major release of radioactive material with widespread health and environmental effects requiring implementation of planned and extended countermeasures."; return azarac_pgm_view(s, 213); }
        default: return std::nullopt;
    }
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d30_nuclear_event_scale_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return std::string_view{"Unknown", 7};
        case 1: return std::string_view{"Level 0/7. Deviation. No safety significance", 44};
        case 2: return std::string_view{"Level 1/7. Anomaly. Overexposure in excess of statutory annual limits. Minor problems with safety components with significant defence-in-depth remaining. Low activity lost or stolen radioactive source, device, or transport package.", 231};
        case 3: return std::string_view{"Level 2/7. Incident. Impact on people and environment: Exposure of the public in excess of 10 mSv. Exposure of workers in excess of the statutory annual limits. Impact on radiological barriers and control: Radiation levels in an operating area of more than 50 mSv/h. Significant contamination within the facility into an area not expected by design. Possible cause: Significant failures in safety provisions but with no actual consequences. Found highly radioactive sealed orphan source, device or transport package with safety provisions intact. Inadequate packaging of a highly radioactive sealed source.", 606};
        case 4: return std::string_view{"Level 3/7. Serious incident. Impact on people and environment: Exposure in excess of ten times the statutory annual limit for workers. Non-lethal deterministic health effect (e.g., burns) from radiation. Impact on radiological barriers and control: Exposure rates of more than 1 Sv/h in an operating area. Severe contamination in an area not expected by design, with a low probability of significant public exposure. Possible cause: Near-accident at a nuclear power plant with no safety provisions remaining. Lost or stolen highly radioactive sealed source. Misdelivered highly radioactive sealed source without adequate procedures in place to handle it.", 654};
        case 5: return std::string_view{"Level 4/7. Accident with local consequences. Impact on people and environment: Minor release of radioactive material unlikely to result in implementation of planned countermeasures other than local food controls. Impact on radiological barriers and control: Release of significant quantities of radioactive material within an installation with a high probability of significant public exposure.", 394};
        case 6: return std::string_view{"Level 5/7. Accident with wider consequences. Impact on people and environment: Limited release of radioactive material likely to require implementation of some planned countermeasures. Major health impact from radiation is likely. Impact on radiological barriers and control: Severe damage to reactor core. Release of large quantities of radioactive material within an installation with a high probability of significant public exposure. This could arise from a major criticality accident or fire.", 497};
        case 7: return std::string_view{"Level 6/7. Serious accident. Impact on people and environment: Significant release of radioactive material likely to require implementation of planned countermeasures.", 167};
        case 8: return std::string_view{"Level 7/7. Major accident. Impact on people and environment: Major release of radioactive material with widespread health and environmental effects requiring implementation of planned and extended countermeasures.", 213};
        default: return std::nullopt;
    }
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d30_nuclear_event_scale_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d30_nuclear_event_scale_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
