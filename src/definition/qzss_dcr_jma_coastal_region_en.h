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
static const char AZARAC_PROGMEM QZSS_DCR_JMA_COASTAL_REGION_EN_POOL[] = "Ust-Kamchatsk (East Coasts of Kamchatka Peninsula)\000Petropavlovsk-K (East Coasts of Kamchatka Peninsula)\000Severo Kurilsk (Kuril Islands)\000Urup Islands (Kuril Islands)\000Busan (South Coasts of Korean Peninsula)\000Nohwa (South Coasts of Korean Peninsula)\000Seogwipo (South Coasts of Korean Peninsula)\000Hualien (Taiwan)\000Basco (East Coasts of Philippines)\000Palanan (East Coasts of Philippines)\000Legaspi (East Coasts of Philippines)\000Laoang (East Coasts of Philippines)\000Madrid (East Coasts of Philippines)\000Davao (East Coasts of Philippines)\000Berebere (North Coasts of Irian Jaya)\000Patani (North Coasts of Irian Jaya)\000Sorong (North Coasts of Irian Jaya)\000Manokwari (North Coasts of Irian Jaya)\000Warsa (North Coasts of Irian Jaya)\000Jayapura (North Coasts of Irian Jaya)\000Vanimo (North Coasts of Papua New Guinea)\000Wewak (North Coasts of Papua New Guinea)\000Madang (North Coasts of Papua New Guinea)\000Manus Islands (North Coasts of Papua New Guinea)\000Rabaul (North Coasts of Papua New Guinea)\000Kavieng (North Coasts of Papua New Guinea)\000Kimbe (North Coasts of Papua New Guinea)\000Kieta (North Coasts of Papua New Guinea)\000Guam (Mariana Islands)\000Saipan (Mariana Islands)\000Malakal (Palau)\000Yap Island (Micronesia)\000Chuuk Island (Micronesia)\000Pohnpei Island (Micronesia)\000Kosrae Island (Micronesia)\000Eniwetok Island (Marshall Islands)\000Panggoe (North Coasts of Solomon Islands)\000Auki (North Coasts of Solomon Islands)\000Kirakira (North Coasts of Solomon Islands)\000Munda (Solomon Sea)\000Honiara (Solomon Sea)\000Ostrov-Karaginskiy (East Coasts of Kamchatka Peninsula)\000Nikolskoya (East Coasts of Kamchatka Peninsula)\000Tongyeong (South Coasts of Korean Peninsula)\000Heuksando (South Coasts of Korean Peninsula)\000Cheju-Island (South Coasts of Korean Peninsula)\000Chilung (Taiwan)\000Taitung (Taiwan)\000Homel (Taiwan)\000Geme (North Coasts of Irian Jaya)\000Ulamona (North Coasts of Papua New Guinea)\000Ghatere (North Coasts of Solomon Islands)\000Amun (Solomon Sea)\000Falamae (Solomon Sea)\000Misima (Solomon Sea)\000Alotau (Solomon Sea)\000Lae (Solomon Sea)\000Port-Moresby (Coral Sea)\000Shanghai (Coasts of East China Sea)\000Zhoushan (Coasts of East China Sea)\000Wenzhou (Coasts of East China Sea)\000Unknown\000Other region\000";
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

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_coastal_region_en_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_coastal_region_en_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
