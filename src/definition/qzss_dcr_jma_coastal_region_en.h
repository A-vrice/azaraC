#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcr_jma_coastal_region
// Variable      : qzss_dcr_jma_coastal_region_en
// Entries       : 63
// Strategy      : array

#include <cstdint>
#include <optional>
#include <string_view>

namespace azaraC {
namespace def {

inline constexpr std::optional<std::string_view> QZSS_DCR_JMA_COASTAL_REGION_EN_TABLE[] = {
    std::string_view{"Ust-Kamchatsk (East Coasts of Kamchatka Peninsula)", 50},
    std::string_view{"Petropavlovsk-K (East Coasts of Kamchatka Peninsula)", 52},
    std::string_view{"Severo Kurilsk (Kuril Islands)", 30},
    std::string_view{"Urup Islands (Kuril Islands)", 28},
    std::string_view{"Busan (South Coasts of Korean Peninsula)", 40},
    std::string_view{"Nohwa (South Coasts of Korean Peninsula)", 40},
    std::string_view{"Seogwipo (South Coasts of Korean Peninsula)", 43},
    std::string_view{"Hualien (Taiwan)", 16},
    std::string_view{"Basco (East Coasts of Philippines)", 34},
    std::string_view{"Palanan (East Coasts of Philippines)", 36},
    std::string_view{"Legaspi (East Coasts of Philippines)", 36},
    std::string_view{"Laoang (East Coasts of Philippines)", 35},
    std::string_view{"Madrid (East Coasts of Philippines)", 35},
    std::string_view{"Davao (East Coasts of Philippines)", 34},
    std::string_view{"Berebere (North Coasts of Irian Jaya)", 37},
    std::string_view{"Patani (North Coasts of Irian Jaya)", 35},
    std::string_view{"Sorong (North Coasts of Irian Jaya)", 35},
    std::string_view{"Manokwari (North Coasts of Irian Jaya)", 38},
    std::string_view{"Warsa (North Coasts of Irian Jaya)", 34},
    std::string_view{"Jayapura (North Coasts of Irian Jaya)", 37},
    std::string_view{"Vanimo (North Coasts of Papua New Guinea)", 41},
    std::string_view{"Wewak (North Coasts of Papua New Guinea)", 40},
    std::string_view{"Madang (North Coasts of Papua New Guinea)", 41},
    std::string_view{"Manus Islands (North Coasts of Papua New Guinea)", 48},
    std::string_view{"Rabaul (North Coasts of Papua New Guinea)", 41},
    std::string_view{"Kavieng (North Coasts of Papua New Guinea)", 42},
    std::string_view{"Kimbe (North Coasts of Papua New Guinea)", 40},
    std::string_view{"Kieta (North Coasts of Papua New Guinea)", 40},
    std::string_view{"Guam (Mariana Islands)", 22},
    std::string_view{"Saipan (Mariana Islands)", 24},
    std::string_view{"Malakal (Palau)", 15},
    std::string_view{"Yap Island (Micronesia)", 23},
    std::string_view{"Chuuk Island (Micronesia)", 25},
    std::string_view{"Pohnpei Island (Micronesia)", 27},
    std::string_view{"Kosrae Island (Micronesia)", 26},
    std::string_view{"Eniwetok Island (Marshall Islands)", 34},
    std::string_view{"Panggoe (North Coasts of Solomon Islands)", 41},
    std::string_view{"Auki (North Coasts of Solomon Islands)", 38},
    std::string_view{"Kirakira (North Coasts of Solomon Islands)", 42},
    std::string_view{"Munda (Solomon Sea)", 19},
    std::string_view{"Honiara (Solomon Sea)", 21},
    std::nullopt,
    std::nullopt,
    std::nullopt,
    std::nullopt,
    std::nullopt,
    std::nullopt,
    std::nullopt,
    std::nullopt,
    std::nullopt,
    std::nullopt,
    std::nullopt,
    std::nullopt,
    std::nullopt,
    std::nullopt,
    std::nullopt,
    std::nullopt,
    std::nullopt,
    std::nullopt,
    std::nullopt,
    std::nullopt,
    std::nullopt,
    std::nullopt,
    std::nullopt,
    std::nullopt,
    std::string_view{"Ostrov-Karaginskiy (East Coasts of Kamchatka Peninsula)", 55},
    std::string_view{"Nikolskoya (East Coasts of Kamchatka Peninsula)", 47},
    std::string_view{"Tongyeong (South Coasts of Korean Peninsula)", 44},
    std::string_view{"Heuksando (South Coasts of Korean Peninsula)", 44},
    std::string_view{"Cheju-Island (South Coasts of Korean Peninsula)", 47},
    std::string_view{"Chilung (Taiwan)", 16},
    std::string_view{"Taitung (Taiwan)", 16},
    std::nullopt,
    std::string_view{"Homel (Taiwan)", 14},
    std::string_view{"Geme (North Coasts of Irian Jaya)", 33},
    std::string_view{"Ulamona (North Coasts of Papua New Guinea)", 42},
    std::string_view{"Ghatere (North Coasts of Solomon Islands)", 41},
    std::string_view{"Amun (Solomon Sea)", 18},
    std::string_view{"Falamae (Solomon Sea)", 21},
    std::string_view{"Misima (Solomon Sea)", 20},
    std::string_view{"Alotau (Solomon Sea)", 20},
    std::string_view{"Lae (Solomon Sea)", 17},
    std::string_view{"Port-Moresby (Coral Sea)", 24},
    std::string_view{"Shanghai (Coasts of East China Sea)", 35},
    std::string_view{"Zhoushan (Coasts of East China Sea)", 35},
    std::string_view{"Wenzhou (Coasts of East China Sea)", 34},
    std::nullopt,
    std::nullopt,
    std::nullopt,
    std::nullopt,
    std::nullopt,
    std::nullopt,
    std::nullopt,
    std::nullopt,
    std::nullopt,
    std::nullopt,
    std::nullopt,
    std::nullopt,
    std::string_view{"Unknown", 7},
    std::string_view{"Other region", 12}
};
inline constexpr uint8_t QZSS_DCR_JMA_COASTAL_REGION_EN_BASE = 1;
inline constexpr uint8_t QZSS_DCR_JMA_COASTAL_REGION_EN_SIZE = 100;
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_coastal_region_en_lookup(uint8_t id) {
    if (id < QZSS_DCR_JMA_COASTAL_REGION_EN_BASE || id >= QZSS_DCR_JMA_COASTAL_REGION_EN_BASE + QZSS_DCR_JMA_COASTAL_REGION_EN_SIZE) return std::nullopt;
    return QZSS_DCR_JMA_COASTAL_REGION_EN_TABLE[id - QZSS_DCR_JMA_COASTAL_REGION_EN_BASE];
}

} // namespace def
} // namespace azaraC
