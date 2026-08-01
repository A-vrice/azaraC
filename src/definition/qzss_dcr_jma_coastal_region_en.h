#pragma once
// AUTO-GENERATED from azarashi 0.16.4 with CI-CD
// Source module : qzss_dcr_jma_coastal_region_en
// Variable      : qzss_dcr_jma_coastal_region_en
// Entries       : 63
// Strategy      : array

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

#if (AZARAC_ENABLE_NW_PAC_TSUNAMI) && (AZARAC_LANG_EN)

inline constexpr uint8_t QZSS_DCR_JMA_COASTAL_REGION_EN_BASE = 1;
inline constexpr uint8_t QZSS_DCR_JMA_COASTAL_REGION_EN_SIZE = 63;
#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCR_JMA_COASTAL_REGION_EN_POOL[] = "Ust-Kamchatsk (East Coasts of Kamchatka Peninsula)\0Petropavlovsk-K (East Coasts of Kamchatka Peninsula)\0Severo Kurilsk (Kuril Islands)\0Urup Islands (Kuril Islands)\0Busan (South Coasts of Korean Peninsula)\0Nohwa (South Coasts of Korean Peninsula)\0Seogwipo (South Coasts of Korean Peninsula)\0Hualien (Taiwan)\0Basco (East Coasts of Philippines)\0Palanan (East Coasts of Philippines)\0Legaspi (East Coasts of Philippines)\0Laoang (East Coasts of Philippines)\0Madrid (East Coasts of Philippines)\0Davao (East Coasts of Philippines)\0Berebere (North Coasts of Irian Jaya)\0Patani (North Coasts of Irian Jaya)\0Sorong (North Coasts of Irian Jaya)\0Manokwari (North Coasts of Irian Jaya)\0Warsa (North Coasts of Irian Jaya)\0Jayapura (North Coasts of Irian Jaya)\0Vanimo (North Coasts of Papua New Guinea)\0Wewak (North Coasts of Papua New Guinea)\0Madang (North Coasts of Papua New Guinea)\0Manus Islands (North Coasts of Papua New Guinea)\0Rabaul (North Coasts of Papua New Guinea)\0Kavieng (North Coasts of Papua New Guinea)\0Kimbe (North Coasts of Papua New Guinea)\0Kieta (North Coasts of Papua New Guinea)\0Guam (Mariana Islands)\0Saipan (Mariana Islands)\0Malakal (Palau)\0Yap Island (Micronesia)\0Chuuk Island (Micronesia)\0Pohnpei Island (Micronesia)\0Kosrae Island (Micronesia)\0Eniwetok Island (Marshall Islands)\0Panggoe (North Coasts of Solomon Islands)\0Auki (North Coasts of Solomon Islands)\0Kirakira (North Coasts of Solomon Islands)\0Munda (Solomon Sea)\0Honiara (Solomon Sea)\0Ostrov-Karaginskiy (East Coasts of Kamchatka Peninsula)\0Nikolskoya (East Coasts of Kamchatka Peninsula)\0Tongyeong (South Coasts of Korean Peninsula)\0Heuksando (South Coasts of Korean Peninsula)\0Cheju-Island (South Coasts of Korean Peninsula)\0Chilung (Taiwan)\0Taitung (Taiwan)\0Homel (Taiwan)\0Geme (North Coasts of Irian Jaya)\0Ulamona (North Coasts of Papua New Guinea)\0Ghatere (North Coasts of Solomon Islands)\0Amun (Solomon Sea)\0Falamae (Solomon Sea)\0Misima (Solomon Sea)\0Alotau (Solomon Sea)\0Lae (Solomon Sea)\0Port-Moresby (Coral Sea)\0Shanghai (Coasts of East China Sea)\0Zhoushan (Coasts of East China Sea)\0Wenzhou (Coasts of East China Sea)\0Unknown\0Other region\0";
struct QZSS_DCR_JMA_COASTAL_REGION_EN_Entry { uint16_t offset; uint16_t len; };
static const QZSS_DCR_JMA_COASTAL_REGION_EN_Entry QZSS_DCR_JMA_COASTAL_REGION_EN_TABLE[] AZARAC_PROGMEM = {
    {0u, 50u},
    {51u, 52u},
    {104u, 30u},
    {135u, 28u},
    {164u, 40u},
    {205u, 40u},
    {246u, 43u},
    {290u, 16u},
    {307u, 34u},
    {342u, 36u},
    {379u, 36u},
    {416u, 35u},
    {452u, 35u},
    {488u, 34u},
    {523u, 37u},
    {561u, 35u},
    {597u, 35u},
    {633u, 38u},
    {672u, 34u},
    {707u, 37u},
    {745u, 41u},
    {787u, 40u},
    {828u, 41u},
    {870u, 48u},
    {919u, 41u},
    {961u, 42u},
    {1004u, 40u},
    {1045u, 40u},
    {1086u, 22u},
    {1109u, 24u},
    {1134u, 15u},
    {1150u, 23u},
    {1174u, 25u},
    {1200u, 27u},
    {1228u, 26u},
    {1255u, 34u},
    {1290u, 41u},
    {1332u, 38u},
    {1371u, 42u},
    {1414u, 19u},
    {1434u, 21u},
    {1456u, 55u},
    {1512u, 47u},
    {1560u, 44u},
    {1605u, 44u},
    {1650u, 47u},
    {1698u, 16u},
    {1715u, 16u},
    {1732u, 14u},
    {1747u, 33u},
    {1781u, 42u},
    {1824u, 41u},
    {1866u, 18u},
    {1885u, 21u},
    {1907u, 20u},
    {1928u, 20u},
    {1949u, 17u},
    {1967u, 24u},
    {1992u, 35u},
    {2028u, 35u},
    {2064u, 34u},
    {2099u, 7u},
    {2107u, 12u}
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_coastal_region_en_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCR_JMA_COASTAL_REGION_EN_BASE || id >= QZSS_DCR_JMA_COASTAL_REGION_EN_BASE + QZSS_DCR_JMA_COASTAL_REGION_EN_SIZE) return std::nullopt;
    const char* AZARAC_PROGMEM p = reinterpret_cast<const char*>(&QZSS_DCR_JMA_COASTAL_REGION_EN_TABLE[id - 1u]);
    uint16_t off = pgm_read_word(p + offsetof(QZSS_DCR_JMA_COASTAL_REGION_EN_Entry, offset));
    uint16_t n = pgm_read_word(p + offsetof(QZSS_DCR_JMA_COASTAL_REGION_EN_Entry, len));
    if (n == 0) return std::nullopt;
    return azarac_pgm_view(QZSS_DCR_JMA_COASTAL_REGION_EN_POOL + off, n);
}
#else
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
    std::string_view{"Ostrov-Karaginskiy (East Coasts of Kamchatka Peninsula)", 55},
    std::string_view{"Nikolskoya (East Coasts of Kamchatka Peninsula)", 47},
    std::string_view{"Tongyeong (South Coasts of Korean Peninsula)", 44},
    std::string_view{"Heuksando (South Coasts of Korean Peninsula)", 44},
    std::string_view{"Cheju-Island (South Coasts of Korean Peninsula)", 47},
    std::string_view{"Chilung (Taiwan)", 16},
    std::string_view{"Taitung (Taiwan)", 16},
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
    std::string_view{"Unknown", 7},
    std::string_view{"Other region", 12}
};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_coastal_region_en_lookup(uint8_t id) noexcept {
    if (id < QZSS_DCR_JMA_COASTAL_REGION_EN_BASE || id >= QZSS_DCR_JMA_COASTAL_REGION_EN_BASE + QZSS_DCR_JMA_COASTAL_REGION_EN_SIZE) return std::nullopt;
    return QZSS_DCR_JMA_COASTAL_REGION_EN_TABLE[id - QZSS_DCR_JMA_COASTAL_REGION_EN_BASE];
}
#endif

#else

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_coastal_region_en_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}

#endif

} // namespace def
} // namespace azaraC
