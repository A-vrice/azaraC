#pragma once
// AUTO-GENERATED from azarashi 0.17.0 with CI-CD
// Source module : azarashi.definitions.qzss.dcr.notification_on_disaster_prevention
// Variable      : qzss_dcr_jma_notification_on_disaster_prevention_en
// Entries       : 55
// Strategy      : binary_search

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

#if (AZARAC_ENABLE_EEW || AZARAC_ENABLE_HYPOCENTER) && (AZARAC_LANG_EN)

#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_EN_POOL[] = "None\000There may be slight sea-level changes from now on. (Translated by azarashi)\000There may be slight sea-level changes from now on, but no damage is expected. (Translated by azarashi)\000Sea-level changes may be observed.\000Pay attention when fishing, swimming or engaging in other marine activities, as there may still be slight sea-level changes.\000Pay attention when fishing or engaging in other marine activities, as there may still be slight sea-level changes.\000No Major Tsunami Warnings, Tsunami Warnings or Advisories are currently in effect.\000Exercise extreme caution if a tsunami arrives at high tide, as this boosts the height of waves.\000Pay full attention if a tsunami arrives at high tide, as this boosts the height of waves. (Translated by azarashi)\000In some coastal regions, tsunami waves higher than those recorded may have arrived.\000Tsunami heights may become even higher from now on. (Translated by azarashi)\000Along the coasts where the tsunami is estimated from offshore observations, it is estimated to have already arrived at the earliest places. (Translated by azarashi)\000The maximum wave may be observed a few hours or more after a tsunami-driven change in sea level is first observed. (Translated by azarashi)\000These values were observed offshore. The tsunami will be higher on the coast. (Translated by azarashi)\000<Major Tsunami Warning>\nA huge tsunami is expected to hit and cause serious damage.\nEvacuate immediately from coastal regions and riverside areas to a safer place such as high ground or an evacuation building.\nTsunami waves are expected to hit repeatedly. Do not leave safe ground until the warning is lifted.\000<Tsunami Warning>\nDamage due to tsunami waves is expected.\nEvacuate immediately from coastal regions and riverside areas to a safer place such as high ground or an evacuation building.\nTsunami waves are expected to hit repeatedly. Do not leave safe ground until the warning is lifted.\000<Tsunami Advisory>\nA marine threat is present.\nGet out of the water and leave coastal regions immediately.\nDue to the risk of ongoing strong currents, do not enter the sea or approach coastal regions until the advisory is lifted.\000<Tsunami Forecast (Slight sea-level change)>\nSlight sea-level changes may be observed in coastal regions, but no tsunami damage is expected.\000Evacuate immediately from coastal regions and riverside areas where the warning is issued to a safer place such as high ground or an evacuation building.\nEstimated tsunami arrival times show the earliest expected strikes for each tsunami forecast region. In some coastal regions, tsunami waves may hit after this time.\nAs tsunami waves may reach their maximum height a few hours or more after the estimated arrival time, do not leave safe ground until the warning is lifted regardless of recorded tsunami heights.\000Actual tsunami heights may exceed estimations in some coastal regions.\000A gigantic tsunami is expected to hit.\000Upgrade to Major Tsunami Warnings/Tsunami Warnings implemented in response to high tsunami waves observed offshore\000Major Tsunami Warnings/Tsunami Warnings updated, in response to high tsunami waves offshore\000Upgrade to Major Tsunami Warnings implemented in response to high tsunami waves observed offshore\000Major Tsunami Warnings updated, in response to high tsunami waves offshore\000Upgrade to Tsunami Warnings implemented high tsunami waves observed offshore\000Tsunami Warnings updated, in response to high tsunami waves offshore\000Estimated tsunami heights updated in response to high tsunami waves offshore\000Evacuate immediately\000Nankai Trough Earthquake Extra Information is in effect.\000Watch out for strong tremors.\000Tsunami warnings or advisories are currently in effect.\000Although there may be slight sea-level changes in coastal regions/ this earthquake has caused no damage to Japan.\000Pay attention when fishing, swimming or engaging in other marine activities, as there may still be slight sea-level changes.\000Pay attention when fishing or engaging in other marine activities, as there may still be slight sea-level changes.\000This earthquake poses no tsunami risk.\000If the hypocenter is beneath the sea floor, a tsunami may be generated. (Translated by azarashi)\000Check the information which will be issued from now on.\000There is a possiblity of a destructive ocean-wide tsunami in the Pacific Ocean.\000There is a possiblity of a destructive regional tsunami in the Pacific Ocean.\000There is a possiblity of a destructive regional tsunami in the Northwest Pacific Ocean.\000There is a possiblity of a destructive ocean-wide tsunami in the Indian Ocean.\000There is a possiblity of a destructive regional tsunami in the Indian Ocean.\000There is a possibility of a destructive local tsunami near the epicenter.\000Minor local tsunami may occur near the epicenter, but no tsunami damage is expected.\000A shallow earthquake with the same magnitude in a sea area may generate a tsunami.\000The possibility of tsunami generation toward Japan in currently under evaluation.\000This earthquake poses no tsunami risk to Japan.\000Earthquake Early Warning is in effect for this earthquake.\000Earthquake Early Warning is in effect for this earthquake. Its maximum seismic intensity was 2.\000Earthquake Early Warning is in effect for this earthquake. Its maximum seismic intensity was 1.\000Earthquake Early Warning is in effect for this earthquake. There was no observation of seismic intensity 1 or above.\000Earthquake Early Warning was issued for this earthquake, however no strong tremors were observed.\000Information related to the hypocenter has been corrected.\000Other Notes on Disaster Prevention\000";
struct QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_EN_Entry { uint16_t id; uint16_t offset; uint16_t len; };
static const QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_EN_Entry QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_EN_TABLE[] AZARAC_PROGMEM = {
    {0u, 0u, 4u},
    {101u, 5u, 75u},
    {102u, 81u, 102u},
    {103u, 184u, 34u},
    {104u, 219u, 124u},
    {105u, 344u, 114u},
    {107u, 459u, 82u},
    {109u, 542u, 95u},
    {110u, 638u, 114u},
    {111u, 753u, 83u},
    {112u, 837u, 76u},
    {113u, 914u, 164u},
    {114u, 1079u, 139u},
    {115u, 1219u, 102u},
    {121u, 1322u, 309u},
    {122u, 1632u, 284u},
    {123u, 1917u, 229u},
    {124u, 2147u, 140u},
    {131u, 2288u, 513u},
    {132u, 2802u, 70u},
    {141u, 2873u, 38u},
    {142u, 2912u, 114u},
    {143u, 3027u, 91u},
    {144u, 3119u, 97u},
    {145u, 3217u, 74u},
    {146u, 3292u, 76u},
    {147u, 3369u, 68u},
    {148u, 3438u, 76u},
    {149u, 3515u, 20u},
    {150u, 3536u, 56u},
    {201u, 3593u, 29u},
    {211u, 3623u, 55u},
    {212u, 3679u, 113u},
    {213u, 3793u, 124u},
    {214u, 3918u, 114u},
    {215u, 4033u, 38u},
    {216u, 4072u, 96u},
    {217u, 4169u, 55u},
    {221u, 4225u, 79u},
    {222u, 4305u, 77u},
    {223u, 4383u, 87u},
    {224u, 4471u, 78u},
    {225u, 4550u, 76u},
    {226u, 4627u, 73u},
    {227u, 4701u, 84u},
    {228u, 4786u, 82u},
    {229u, 4869u, 81u},
    {230u, 4951u, 47u},
    {241u, 4999u, 58u},
    {242u, 5058u, 95u},
    {243u, 5154u, 95u},
    {244u, 5250u, 116u},
    {245u, 5367u, 97u},
    {256u, 5465u, 57u},
    {500u, 5523u, 34u},
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_notification_on_disaster_prevention_en_lookup(uint16_t id) noexcept {
    uint8_t lo = 0, hi = 55;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        const char* AZARAC_PROGMEM ep = reinterpret_cast<const char*>(&QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_EN_TABLE[mid]);
        uint16_t eid = pgm_read_word(ep + offsetof(QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_EN_Entry, id));
        if (eid == id) {
            uint16_t off = pgm_read_word(ep + offsetof(QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_EN_Entry, offset));
            uint16_t n = pgm_read_word(ep + offsetof(QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_EN_Entry, len));
            return azarac_pgm_view(QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_EN_POOL + off, n);
        }
        if (eid < id) lo = static_cast<uint8_t>(mid + 1); else hi = mid;
    }
    return std::nullopt;
}
#else
struct QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_EN_Entry { uint16_t id; const char* label; };
inline constexpr QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_EN_Entry QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_EN_TABLE[] = {
    {0u, "None"},
    {101u, "There may be slight sea-level changes from now on. (Translated by azarashi)"},
    {102u, "There may be slight sea-level changes from now on, but no damage is expected. (Translated by azarashi)"},
    {103u, "Sea-level changes may be observed."},
    {104u, "Pay attention when fishing, swimming or engaging in other marine activities, as there may still be slight sea-level changes."},
    {105u, "Pay attention when fishing or engaging in other marine activities, as there may still be slight sea-level changes."},
    {107u, "No Major Tsunami Warnings, Tsunami Warnings or Advisories are currently in effect."},
    {109u, "Exercise extreme caution if a tsunami arrives at high tide, as this boosts the height of waves."},
    {110u, "Pay full attention if a tsunami arrives at high tide, as this boosts the height of waves. (Translated by azarashi)"},
    {111u, "In some coastal regions, tsunami waves higher than those recorded may have arrived."},
    {112u, "Tsunami heights may become even higher from now on. (Translated by azarashi)"},
    {113u, "Along the coasts where the tsunami is estimated from offshore observations, it is estimated to have already arrived at the earliest places. (Translated by azarashi)"},
    {114u, "The maximum wave may be observed a few hours or more after a tsunami-driven change in sea level is first observed. (Translated by azarashi)"},
    {115u, "These values were observed offshore. The tsunami will be higher on the coast. (Translated by azarashi)"},
    {121u, "<Major Tsunami Warning>\nA huge tsunami is expected to hit and cause serious damage.\nEvacuate immediately from coastal regions and riverside areas to a safer place such as high ground or an evacuation building.\nTsunami waves are expected to hit repeatedly. Do not leave safe ground until the warning is lifted."},
    {122u, "<Tsunami Warning>\nDamage due to tsunami waves is expected.\nEvacuate immediately from coastal regions and riverside areas to a safer place such as high ground or an evacuation building.\nTsunami waves are expected to hit repeatedly. Do not leave safe ground until the warning is lifted."},
    {123u, "<Tsunami Advisory>\nA marine threat is present.\nGet out of the water and leave coastal regions immediately.\nDue to the risk of ongoing strong currents, do not enter the sea or approach coastal regions until the advisory is lifted."},
    {124u, "<Tsunami Forecast (Slight sea-level change)>\nSlight sea-level changes may be observed in coastal regions, but no tsunami damage is expected."},
    {131u, "Evacuate immediately from coastal regions and riverside areas where the warning is issued to a safer place such as high ground or an evacuation building.\nEstimated tsunami arrival times show the earliest expected strikes for each tsunami forecast region. In some coastal regions, tsunami waves may hit after this time.\nAs tsunami waves may reach their maximum height a few hours or more after the estimated arrival time, do not leave safe ground until the warning is lifted regardless of recorded tsunami heights."},
    {132u, "Actual tsunami heights may exceed estimations in some coastal regions."},
    {141u, "A gigantic tsunami is expected to hit."},
    {142u, "Upgrade to Major Tsunami Warnings/Tsunami Warnings implemented in response to high tsunami waves observed offshore"},
    {143u, "Major Tsunami Warnings/Tsunami Warnings updated, in response to high tsunami waves offshore"},
    {144u, "Upgrade to Major Tsunami Warnings implemented in response to high tsunami waves observed offshore"},
    {145u, "Major Tsunami Warnings updated, in response to high tsunami waves offshore"},
    {146u, "Upgrade to Tsunami Warnings implemented high tsunami waves observed offshore"},
    {147u, "Tsunami Warnings updated, in response to high tsunami waves offshore"},
    {148u, "Estimated tsunami heights updated in response to high tsunami waves offshore"},
    {149u, "Evacuate immediately"},
    {150u, "Nankai Trough Earthquake Extra Information is in effect."},
    {201u, "Watch out for strong tremors."},
    {211u, "Tsunami warnings or advisories are currently in effect."},
    {212u, "Although there may be slight sea-level changes in coastal regions/ this earthquake has caused no damage to Japan."},
    {213u, "Pay attention when fishing, swimming or engaging in other marine activities, as there may still be slight sea-level changes."},
    {214u, "Pay attention when fishing or engaging in other marine activities, as there may still be slight sea-level changes."},
    {215u, "This earthquake poses no tsunami risk."},
    {216u, "If the hypocenter is beneath the sea floor, a tsunami may be generated. (Translated by azarashi)"},
    {217u, "Check the information which will be issued from now on."},
    {221u, "There is a possiblity of a destructive ocean-wide tsunami in the Pacific Ocean."},
    {222u, "There is a possiblity of a destructive regional tsunami in the Pacific Ocean."},
    {223u, "There is a possiblity of a destructive regional tsunami in the Northwest Pacific Ocean."},
    {224u, "There is a possiblity of a destructive ocean-wide tsunami in the Indian Ocean."},
    {225u, "There is a possiblity of a destructive regional tsunami in the Indian Ocean."},
    {226u, "There is a possibility of a destructive local tsunami near the epicenter."},
    {227u, "Minor local tsunami may occur near the epicenter, but no tsunami damage is expected."},
    {228u, "A shallow earthquake with the same magnitude in a sea area may generate a tsunami."},
    {229u, "The possibility of tsunami generation toward Japan in currently under evaluation."},
    {230u, "This earthquake poses no tsunami risk to Japan."},
    {241u, "Earthquake Early Warning is in effect for this earthquake."},
    {242u, "Earthquake Early Warning is in effect for this earthquake. Its maximum seismic intensity was 2."},
    {243u, "Earthquake Early Warning is in effect for this earthquake. Its maximum seismic intensity was 1."},
    {244u, "Earthquake Early Warning is in effect for this earthquake. There was no observation of seismic intensity 1 or above."},
    {245u, "Earthquake Early Warning was issued for this earthquake, however no strong tremors were observed."},
    {256u, "Information related to the hypocenter has been corrected."},
    {500u, "Other Notes on Disaster Prevention"},};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_notification_on_disaster_prevention_en_lookup(uint16_t id) noexcept {
    uint8_t lo = 0, hi = 55;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        if (QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_EN_TABLE[mid].id == id) {
            const char* s = QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_EN_TABLE[mid].label;
            return s ? std::optional<std::string_view>(std::string_view{s}) : std::nullopt;
        }
        if (QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_EN_TABLE[mid].id < id) lo = mid + 1;
        else hi = mid;
    }
    return std::nullopt;
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_notification_on_disaster_prevention_en_lookup(uint16_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_notification_on_disaster_prevention_en_lookup(uint16_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
