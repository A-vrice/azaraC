#pragma once
// AUTO-GENERATED from azarashi 0.17.1 with CI-CD
// Source module : azarashi.definitions.qzss.dcr.coastal_region
// Variable      : qzss_dcr_jma_coastal_region_en
// Entries       : 63
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

#if (AZARAC_ENABLE_NW_PAC_TSUNAMI)

#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCR_JMA_COASTAL_REGION_EN_POOL[] = "Ust-Kamchatsk\000Petropavlovsk-K\000Severo Kurilsk (Kuril\000Urup Islands (Kuril\000Busan\000Nohwa\000Seogwipo\000Hualien\000Basco\000Palanan\000Legaspi\000Laoang\000Madrid\000Davao\000Berebere\000Patani\000Sorong\000Manokwari\000Warsa\000Jayapura\000Vanimo\000Wewak\000Madang\000Manus Islands\000Rabaul\000Kavieng\000Kimbe\000Kieta\000Guam (Mariana\000Saipan (Mariana\000Malakal (Palau)\000Yap\000Chuuk\000Pohnpei\000Kosrae\000Eniwetok Island (Marshall\000Panggoe\000Auki\000Kirakira\000Munda\000Honiara\000Ostrov-Karaginskiy\000Nikolskoya\000Tongyeong\000Heuksando\000Cheju-Island\000Chilung\000Taitung\000Homel\000Geme\000Ulamona\000Ghatere\000Amun\000Falamae\000Misima\000Alotau\000Lae\000Port-Moresby (Coral\000Shanghai (Coasts of East China\000Zhoushan (Coasts of East China\000Wenzhou (Coasts of East China\000Unknown\000Other region\000";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_COASTAL_REGION_EN_PARENT_POOL[] = " (East Coasts of Kamchatka Peninsula)\000 (East Coasts of Philippines)\000 (North Coasts of Irian Jaya)\000 (North Coasts of Papua New Guinea)\000 (North Coasts of Solomon Islands)\000 (Solomon Sea)\000 (South Coasts of Korean Peninsula)\000 (Taiwan)\000 Island (Micronesia)\000 Islands)\000 Sea)\000";
struct QZSS_DCR_JMA_COASTAL_REGION_EN_PARENT_Entry { uint16_t offset; };
static const QZSS_DCR_JMA_COASTAL_REGION_EN_PARENT_Entry QZSS_DCR_JMA_COASTAL_REGION_EN_PARENT_TABLE[] AZARAC_PROGMEM = {
    {0u},
    {38u},
    {68u},
    {98u},
    {134u},
    {169u},
    {184u},
    {220u},
    {230u},
    {251u},
    {261u},
};
struct QZSS_DCR_JMA_COASTAL_REGION_EN_Entry { uint8_t id; uint8_t parent; uint16_t offset; };
static const QZSS_DCR_JMA_COASTAL_REGION_EN_Entry QZSS_DCR_JMA_COASTAL_REGION_EN_TABLE[] AZARAC_PROGMEM = {
    {1u, 0u, 0u},
    {2u, 0u, 14u},
    {3u, 9u, 30u},
    {4u, 9u, 52u},
    {5u, 6u, 72u},
    {6u, 6u, 78u},
    {7u, 6u, 84u},
    {8u, 7u, 93u},
    {9u, 1u, 101u},
    {10u, 1u, 107u},
    {11u, 1u, 115u},
    {12u, 1u, 123u},
    {13u, 1u, 130u},
    {14u, 1u, 137u},
    {15u, 2u, 143u},
    {16u, 2u, 152u},
    {17u, 2u, 159u},
    {18u, 2u, 166u},
    {19u, 2u, 176u},
    {20u, 2u, 182u},
    {21u, 3u, 191u},
    {22u, 3u, 198u},
    {23u, 3u, 204u},
    {24u, 3u, 211u},
    {25u, 3u, 225u},
    {26u, 3u, 232u},
    {27u, 3u, 240u},
    {28u, 3u, 246u},
    {29u, 9u, 252u},
    {30u, 9u, 266u},
    {31u, 255u, 282u},
    {32u, 8u, 298u},
    {33u, 8u, 302u},
    {34u, 8u, 308u},
    {35u, 8u, 316u},
    {36u, 9u, 323u},
    {37u, 4u, 349u},
    {38u, 4u, 357u},
    {39u, 4u, 362u},
    {40u, 5u, 371u},
    {41u, 5u, 377u},
    {66u, 0u, 385u},
    {67u, 0u, 404u},
    {68u, 6u, 415u},
    {69u, 6u, 425u},
    {70u, 6u, 435u},
    {71u, 7u, 448u},
    {72u, 7u, 456u},
    {74u, 7u, 464u},
    {75u, 2u, 470u},
    {76u, 3u, 475u},
    {77u, 4u, 483u},
    {78u, 5u, 491u},
    {79u, 5u, 496u},
    {80u, 5u, 504u},
    {81u, 5u, 511u},
    {82u, 5u, 518u},
    {83u, 10u, 522u},
    {84u, 10u, 542u},
    {85u, 10u, 573u},
    {86u, 10u, 604u},
    {99u, 255u, 634u},
    {100u, 255u, 642u},
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_coastal_region_en_lookup(uint8_t id) noexcept {
    uint8_t lo = 0, hi = 63;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        const char* AZARAC_PROGMEM ep = reinterpret_cast<const char*>(&QZSS_DCR_JMA_COASTAL_REGION_EN_TABLE[mid]);
        uint8_t eid = static_cast<uint8_t>(pgm_read_byte(ep + offsetof(QZSS_DCR_JMA_COASTAL_REGION_EN_Entry, id)));
        if (eid == id) {
            uint16_t off = pgm_read_word(ep + offsetof(QZSS_DCR_JMA_COASTAL_REGION_EN_Entry, offset));
            uint8_t pi = pgm_read_byte(ep + offsetof(QZSS_DCR_JMA_COASTAL_REGION_EN_Entry, parent));
            if (pi == 255u) return azarac_pgm_view_z(QZSS_DCR_JMA_COASTAL_REGION_EN_POOL + off);
            const char* AZARAC_PROGMEM pp = reinterpret_cast<const char*>(&QZSS_DCR_JMA_COASTAL_REGION_EN_PARENT_TABLE[pi]);
            uint16_t poff = pgm_read_word(pp + offsetof(QZSS_DCR_JMA_COASTAL_REGION_EN_PARENT_Entry, offset));
            return azarac_pgm_join_z(QZSS_DCR_JMA_COASTAL_REGION_EN_POOL + off, QZSS_DCR_JMA_COASTAL_REGION_EN_PARENT_POOL + poff);
        }
        if (eid < id) lo = static_cast<uint8_t>(mid + 1); else hi = mid;
    }
    return std::nullopt;
}
#else
struct QZSS_DCR_JMA_COASTAL_REGION_EN_Entry { uint8_t id; const char* label; };
inline constexpr QZSS_DCR_JMA_COASTAL_REGION_EN_Entry QZSS_DCR_JMA_COASTAL_REGION_EN_TABLE[] = {
    {1u, "Ust-Kamchatsk (East Coasts of Kamchatka Peninsula)"},
    {2u, "Petropavlovsk-K (East Coasts of Kamchatka Peninsula)"},
    {3u, "Severo Kurilsk (Kuril Islands)"},
    {4u, "Urup Islands (Kuril Islands)"},
    {5u, "Busan (South Coasts of Korean Peninsula)"},
    {6u, "Nohwa (South Coasts of Korean Peninsula)"},
    {7u, "Seogwipo (South Coasts of Korean Peninsula)"},
    {8u, "Hualien (Taiwan)"},
    {9u, "Basco (East Coasts of Philippines)"},
    {10u, "Palanan (East Coasts of Philippines)"},
    {11u, "Legaspi (East Coasts of Philippines)"},
    {12u, "Laoang (East Coasts of Philippines)"},
    {13u, "Madrid (East Coasts of Philippines)"},
    {14u, "Davao (East Coasts of Philippines)"},
    {15u, "Berebere (North Coasts of Irian Jaya)"},
    {16u, "Patani (North Coasts of Irian Jaya)"},
    {17u, "Sorong (North Coasts of Irian Jaya)"},
    {18u, "Manokwari (North Coasts of Irian Jaya)"},
    {19u, "Warsa (North Coasts of Irian Jaya)"},
    {20u, "Jayapura (North Coasts of Irian Jaya)"},
    {21u, "Vanimo (North Coasts of Papua New Guinea)"},
    {22u, "Wewak (North Coasts of Papua New Guinea)"},
    {23u, "Madang (North Coasts of Papua New Guinea)"},
    {24u, "Manus Islands (North Coasts of Papua New Guinea)"},
    {25u, "Rabaul (North Coasts of Papua New Guinea)"},
    {26u, "Kavieng (North Coasts of Papua New Guinea)"},
    {27u, "Kimbe (North Coasts of Papua New Guinea)"},
    {28u, "Kieta (North Coasts of Papua New Guinea)"},
    {29u, "Guam (Mariana Islands)"},
    {30u, "Saipan (Mariana Islands)"},
    {31u, "Malakal (Palau)"},
    {32u, "Yap Island (Micronesia)"},
    {33u, "Chuuk Island (Micronesia)"},
    {34u, "Pohnpei Island (Micronesia)"},
    {35u, "Kosrae Island (Micronesia)"},
    {36u, "Eniwetok Island (Marshall Islands)"},
    {37u, "Panggoe (North Coasts of Solomon Islands)"},
    {38u, "Auki (North Coasts of Solomon Islands)"},
    {39u, "Kirakira (North Coasts of Solomon Islands)"},
    {40u, "Munda (Solomon Sea)"},
    {41u, "Honiara (Solomon Sea)"},
    {66u, "Ostrov-Karaginskiy (East Coasts of Kamchatka Peninsula)"},
    {67u, "Nikolskoya (East Coasts of Kamchatka Peninsula)"},
    {68u, "Tongyeong (South Coasts of Korean Peninsula)"},
    {69u, "Heuksando (South Coasts of Korean Peninsula)"},
    {70u, "Cheju-Island (South Coasts of Korean Peninsula)"},
    {71u, "Chilung (Taiwan)"},
    {72u, "Taitung (Taiwan)"},
    {74u, "Homel (Taiwan)"},
    {75u, "Geme (North Coasts of Irian Jaya)"},
    {76u, "Ulamona (North Coasts of Papua New Guinea)"},
    {77u, "Ghatere (North Coasts of Solomon Islands)"},
    {78u, "Amun (Solomon Sea)"},
    {79u, "Falamae (Solomon Sea)"},
    {80u, "Misima (Solomon Sea)"},
    {81u, "Alotau (Solomon Sea)"},
    {82u, "Lae (Solomon Sea)"},
    {83u, "Port-Moresby (Coral Sea)"},
    {84u, "Shanghai (Coasts of East China Sea)"},
    {85u, "Zhoushan (Coasts of East China Sea)"},
    {86u, "Wenzhou (Coasts of East China Sea)"},
    {99u, "Unknown"},
    {100u, "Other region"},};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_coastal_region_en_lookup(uint8_t id) noexcept {
    uint8_t lo = 0, hi = 63;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        if (QZSS_DCR_JMA_COASTAL_REGION_EN_TABLE[mid].id == id) {
            const char* s = QZSS_DCR_JMA_COASTAL_REGION_EN_TABLE[mid].label;
            return s ? std::optional<std::string_view>(std::string_view{s}) : std::nullopt;
        }
        if (QZSS_DCR_JMA_COASTAL_REGION_EN_TABLE[mid].id < id) lo = mid + 1;
        else hi = mid;
    }
    return std::nullopt;
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
