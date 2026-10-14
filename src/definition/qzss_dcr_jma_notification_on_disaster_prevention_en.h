#pragma once
// AUTO-GENERATED from azarashi 0.17.1 with CI-CD
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
static const char AZARAC_PROGMEM QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_EN_POOL[] = "None\000There may be slight sea-level changes from now on\000There may be slight sea-level changes from now on, but no damage is expected\000Sea-level changes may be observ\000Pay attention when fishing, swimm\000Pay attention when fish\000No Major Tsunami Warnings, Tsunami Warnings or Advisories are currently in effec\000Exercise extreme caution if a tsunami arrives at high tide, as this boosts the height of wav\000Pay full attention if a tsunami arrives at high tide, as this boosts the height of waves\000In some coastal regions, tsunami waves higher than those recorded may have arriv\000Tsunami heights may become even higher from now on\000Along the coasts where the tsunami is estimated from offshore observations, it is estimated to have already arrived at the earliest places\000The maximum wave may be observed a few hours or more after a tsunami-driven change in sea level is first observed\000These values were observed offshore. The tsunami will be higher on the coast\000<Major Tsunami Warning>\nA huge tsunami is expected to hit and cause serious damage.\nEvacuate immediately from coastal regions and riverside areas to a safer place such as high ground or an evacuation building.\nTsunami waves are expected to hit repeatedly. Do not leave safe ground until the warning is lif\000<Tsunami Warning>\nDamage due to tsunami waves is expected.\nEvacuate immediately from coastal regions and riverside areas to a safer place such as high ground or an evacuation building.\nTsunami waves are expected to hit repeatedly. Do not leave safe ground until the warning is lif\000<Tsunami Advisory>\nA marine threat is present.\nGet out of the water and leave coastal regions immediately.\nDue to the risk of ongoing strong currents, do not enter the sea or approach coastal regions until the advisory is lif\000<Tsunami Forecast (Slight sea-level change)>\nSlight sea-level changes may be observed in coastal regions, but no tsunami damage is expec\000Evacuate immediately from coastal regions and riverside areas where the warning is issued to a safer place such as high ground or an evacuation building.\nEstimated tsunami arrival times show the earliest expected strikes for each tsunami forecast region. In some coastal regions, tsunami waves may hit after this time.\nAs tsunami waves may reach their maximum height a few hours or more after the estimated arrival time, do not leave safe ground until the warning is lifted regardless of recorded tsunami height\000Actual tsunami heights may exceed estimations in some coastal region\000A gigantic tsunami is expected to hi\000Upgrade to Major Tsunami Warnings/Tsunami Warnings implemented in response to high tsunami waves observed\000Major Tsunami Warnings/Tsunami Warnings updated,\000Upgrade to Major Tsunami Warnings implemented in response to high tsunami waves observed\000Major Tsunami Warnings updated,\000Upgrade to Tsunami Warnings implemented high tsunami waves observed\000Tsunami Warnings updated,\000Estimated tsunami heights updated\000Evacuate immediately\000Nankai Trough Earthquake Extra Information is in effec\000Watch out for strong tremor\000Tsunami warnings or advisories are currently in effec\000Although there may be slight sea-level changes in coastal regions/ this earthquake has caused no damage to Jap\000Pay attention when fishing, swimm\000Pay attention when fish\000This earthquake poses no tsunami risk\000If the hypocenter is beneath the sea floor, a tsunami may be generated\000Check the information which will be issued from now o\000There is a possiblity of a destructive ocean-wide tsunami in the Pacific Ocean.\000There is a possiblity of a destructive regional tsunami in the Pacific Ocean.\000There is a possiblity of a destructive regional tsunami in the Northwest Pacific Ocean.\000There is a possiblity of a destructive ocean-wide tsunami in the Indian Ocean.\000There is a possiblity of a destructive regional tsunami in the Indian Ocean.\000There is a possibility of a destructive local tsunami near the epicenter.\000Minor local tsunami may occur near the epicenter, but no tsunami damage is expec\000A shallow earthquake with the same magnitude in a sea area may generate a tsunami\000The possibility of tsunami generation toward Japan in currently under evaluatio\000This earthquake poses no tsunami risk to Jap\000Earthquake Early Warning is in effect for this earthquake.\000Earthquake Early Warning is in effect for this earthquake. Its maximum seismic intensity was 2.\000Earthquake Early Warning is in effect for this earthquake. Its maximum seismic intensity was 1.\000Earthquake Early Warning is in effect for this earthquake. There was no observation of seismic intensity 1 or above.\000Earthquake Early Warning was issued for this earthquake, however no strong tremors were observed.\000Information related to the hypocenter has been correc\000Other Notes on Disaster Prevention\000";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_EN_PARENT_POOL[] = " in response to high tsunami waves offshore\000 offshore\000.\000. (Translated by azarashi)\000an.\000ed.\000es.\000ing or engaging in other marine activities, as there may still be slight sea-level changes.\000n.\000s.\000t.\000ted.\000";
struct QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_EN_PARENT_Entry { uint16_t offset; uint8_t len; };
static const QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_EN_PARENT_Entry QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_EN_PARENT_TABLE[] AZARAC_PROGMEM = {
    {0u, 43u},
    {44u, 9u},
    {54u, 1u},
    {56u, 26u},
    {83u, 3u},
    {87u, 3u},
    {91u, 3u},
    {95u, 91u},
    {187u, 2u},
    {190u, 2u},
    {193u, 2u},
    {196u, 4u},
};
struct QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_EN_Entry { uint16_t id; uint8_t parent; uint16_t offset; uint16_t len; };
static const QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_EN_Entry QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_EN_TABLE[] AZARAC_PROGMEM = {
    {0u, 255u, 0u, 4u},
    {101u, 3u, 5u, 49u},
    {102u, 3u, 55u, 76u},
    {103u, 5u, 132u, 31u},
    {104u, 7u, 164u, 33u},
    {105u, 7u, 198u, 23u},
    {107u, 10u, 222u, 80u},
    {109u, 6u, 303u, 92u},
    {110u, 3u, 396u, 88u},
    {111u, 5u, 485u, 80u},
    {112u, 3u, 566u, 50u},
    {113u, 3u, 617u, 138u},
    {114u, 3u, 756u, 113u},
    {115u, 3u, 870u, 76u},
    {121u, 11u, 947u, 305u},
    {122u, 11u, 1253u, 280u},
    {123u, 11u, 1534u, 225u},
    {124u, 11u, 1760u, 136u},
    {131u, 9u, 1897u, 511u},
    {132u, 9u, 2409u, 68u},
    {141u, 10u, 2478u, 36u},
    {142u, 1u, 2515u, 105u},
    {143u, 0u, 2621u, 48u},
    {144u, 1u, 2670u, 88u},
    {145u, 0u, 2759u, 31u},
    {146u, 1u, 2791u, 67u},
    {147u, 0u, 2859u, 25u},
    {148u, 0u, 2885u, 33u},
    {149u, 255u, 2919u, 20u},
    {150u, 10u, 2940u, 54u},
    {201u, 9u, 2995u, 27u},
    {211u, 10u, 3023u, 53u},
    {212u, 4u, 3077u, 110u},
    {213u, 7u, 3188u, 33u},
    {214u, 7u, 3222u, 23u},
    {215u, 2u, 3246u, 37u},
    {216u, 3u, 3284u, 70u},
    {217u, 8u, 3355u, 53u},
    {221u, 255u, 3409u, 79u},
    {222u, 255u, 3489u, 77u},
    {223u, 255u, 3567u, 87u},
    {224u, 255u, 3655u, 78u},
    {225u, 255u, 3734u, 76u},
    {226u, 255u, 3811u, 73u},
    {227u, 11u, 3885u, 80u},
    {228u, 2u, 3966u, 81u},
    {229u, 8u, 4048u, 79u},
    {230u, 4u, 4128u, 44u},
    {241u, 255u, 4173u, 58u},
    {242u, 255u, 4232u, 95u},
    {243u, 255u, 4328u, 95u},
    {244u, 255u, 4424u, 116u},
    {245u, 255u, 4541u, 97u},
    {256u, 11u, 4639u, 53u},
    {500u, 255u, 4693u, 34u},
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
            uint8_t pi = pgm_read_byte(ep + offsetof(QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_EN_Entry, parent));
            if (pi == 255u) return azarac_pgm_view(QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_EN_POOL + off, n);
            const char* AZARAC_PROGMEM pp = reinterpret_cast<const char*>(&QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_EN_PARENT_TABLE[pi]);
            uint16_t poff = pgm_read_word(pp + offsetof(QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_EN_PARENT_Entry, offset));
            uint8_t pn = pgm_read_byte(pp + offsetof(QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_EN_PARENT_Entry, len));
            return azarac_pgm_join(QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_EN_POOL + off, n, QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_EN_PARENT_POOL + poff, pn);
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
