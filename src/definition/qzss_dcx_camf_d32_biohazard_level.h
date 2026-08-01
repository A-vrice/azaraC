#pragma once
// AUTO-GENERATED from azarashi 0.16.4 with CI-CD
// Source module : qzss_dcx_camf_d32_biohazard_level
// Variable      : qzss_dcx_camf_d32_biohazard_level
// Entries       : 4
// Strategy      : switch

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

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcx_camf_d32_biohazard_level_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: { static const char AZARAC_PROGMEM s[] = "Biohazard Level 1/4: Often pertains to agents that include viruses and bacteria, this biosafety level requires minimal precaution, such as wearing face masks and maintaining no close contact. The biological hazard examples in the first level include E. coli and other non-infectious bacteria."; return azarac_pgm_view(s, 292); }
        case 1: { static const char AZARAC_PROGMEM s[] = "Biohazard Level 2/4: Usually causing severe diseases to humans, the second level classifies agents that can be transmitted through direct contact with infected materials. HIV and hepatitis B are some biological hazard examples that pose moderate risks to humans."; return azarac_pgm_view(s, 262); }
        case 2: { static const char AZARAC_PROGMEM s[] = "Biohazard Level 3/4: Mainly through respiratory transmission, pathogens that are highly likely to become airborne can cause serious or lethal diseases to humans. Mycobacterium tuberculosis, the bacteria that causes tuberculosis, is an example of a level-3 biohazard."; return azarac_pgm_view(s, 266); }
        case 3: { static const char AZARAC_PROGMEM s[] = "Biohazard Level 4/4: Extremely dangerous pathogens that expose humans to life-threatening diseases, the fourth and last level requires workers to utilise maximum protection and containment. Some biological hazard examples are the Ebola virus and the Lassa virus."; return azarac_pgm_view(s, 262); }
        default: return std::nullopt;
    }
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d32_biohazard_level_lookup(uint8_t id) noexcept {
    switch (id) {
        case 0: return std::string_view{"Biohazard Level 1/4: Often pertains to agents that include viruses and bacteria, this biosafety level requires minimal precaution, such as wearing face masks and maintaining no close contact. The biological hazard examples in the first level include E. coli and other non-infectious bacteria.", 292};
        case 1: return std::string_view{"Biohazard Level 2/4: Usually causing severe diseases to humans, the second level classifies agents that can be transmitted through direct contact with infected materials. HIV and hepatitis B are some biological hazard examples that pose moderate risks to humans.", 262};
        case 2: return std::string_view{"Biohazard Level 3/4: Mainly through respiratory transmission, pathogens that are highly likely to become airborne can cause serious or lethal diseases to humans. Mycobacterium tuberculosis, the bacteria that causes tuberculosis, is an example of a level-3 biohazard.", 266};
        case 3: return std::string_view{"Biohazard Level 4/4: Extremely dangerous pathogens that expose humans to life-threatening diseases, the fourth and last level requires workers to utilise maximum protection and containment. Some biological hazard examples are the Ebola virus and the Lassa virus.", 262};
        default: return std::nullopt;
    }
}
#endif

#else

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d32_biohazard_level_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}

#endif

} // namespace def
} // namespace azaraC
