#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcx_camf_b4_lower_level_fields_tables
// Variable      : qzss_dcx_camf_d11_tornado_probability
// Entries       : 6
// Strategy      : switch

#include <cstdint>
#include <optional>
#include <string_view>

namespace azaraC {
namespace def {

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcx_camf_d11_tornado_probability_lookup(uint8_t id) {
    switch (id) {
        case 0: return std::string_view{"Non-Threatening - Threat: No discernible threat to life and property. Minimum Action: Listen for forecast changes; review tornado safety rules. Potential Impact: None expected; strong wind gusts may still occur.", 211};
        case 1: return std::string_view{"Very Low - Threat: A very low threat to life and property. Minimum Action: Preparations should be made for a very low likelihood (or a 2 to 4% probability) of tornadoes; isolated tornadoes of F0 to F1 intensity possible. Potential Impact: The potential for isolated locations to experience minor to moderate tornado damage.", 323};
        case 2: return std::string_view{"Low - Threat: A low threat to life and property. Minimum Action: Preparations should be made for a low likelihood (or a 5 to 14% probability) of tornadoes; scattered tornadoes of F0 to F1 intensity possible. Potential Impact: The potential for scattered locations to experience minor to moderate tornado damage.", 311};
        case 3: return std::string_view{"Moderate - Threat: A moderate threat to life and property. Minimum Action: Preparations should be made for a moderate likelihood (or a 15 to 29% probability) of tornadoes; many tornadoes (even families) of F0 to F1 intensity possible. Potential Impact: The potential for many locations to experience minor to moderate tornado damage (see below). Some tornadoes may have longer damage tracks.", 391};
        case 4: return std::string_view{"High - Threat: A high threat to life and property. Minimum Action: Preparations should be made for a high likelihood (or a 30 to 44% probability) of tornadoes; scattered tornadoes possible with isolated tornadoes of F2 to F5 intensity also possible. Potential Impact: The potential for isolated locations to experience major tornado damage (see below), among scattered locations of minor to moderate tornado damage. Some tornadoes may have longer damage tracks.", 461};
        case 5: return std::string_view{"Extreme - Threat: An extreme threat to life and property. Minimum Action: Preparations should be made for a very high likelihood (or a 45% probability or greater) of tornadoes; many tornadoes (even families) possible with scattered tornadoes of F2 to F5 intensity also possible. Potential Impact: The potential for scattered locations to experience major tornado damage (see below), among many locations of minor to moderate tornado damage. Some tornadoes may have longer damage tracks.", 486};
        default: return std::nullopt;
    }
}

} // namespace def
} // namespace azaraC
