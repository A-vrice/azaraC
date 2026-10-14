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
static const char AZARAC_PROGMEM QZSS_DCR_JMA_COASTAL_REGION_EN_POOL[] = "Ust-Kamchatsk\000Petropavlovsk-K\000Severo Kurilsk (Kuril\000Urup Islands (Kuril\000Busan\000Nohwa\000Seogwipo\000Hualien\000Basco\000Palanan\000Legaspi\000Laoang\000Madrid\000Davao\000Berebere\000Patani\000Sorong\000Manokwari\000Warsa\000Jayapura\000Vanimo\000Wewak\000Madang\000Manus Islands\000Rabaul\000Kavieng\000Kimbe\000Kieta\000Guam (Mariana\000Saipan (Mariana\000Malakal (Palau\000Yap \000Chuuk \000Pohnpei \000Kosrae \000Eniwetok Island (Marshall\000Panggoe\000Auki\000Kirakira\000Munda\000Honiara\000Ostrov-Karaginskiy\000Nikolskoya\000Tongyeong\000Heuksando\000Cheju-Island\000Chilung\000Taitung\000Homel\000Geme\000Ulamona\000Ghatere\000Amun\000Falamae\000Misima\000Alotau\000Lae \000Port-Moresby (Coral\000Shanghai (Coasts of East China\000Zhoushan (Coasts of East China\000Wenzhou (Coasts of East China\000Unknown\000Other region\000";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_COASTAL_REGION_EN_PARENT_POOL[] = " (East Coasts of Kamchatka Peninsula)\000 (East Coasts of Philippines)\000 (North Coasts of Irian Jaya)\000 (North Coasts of Papua New Guinea)\000 (North Coasts of Solomon Islands)\000 (Solomon Sea)\000 (South Coasts of Korean Peninsula)\000 (Taiwan)\000 Islands)\000 Sea)\000(Solomon Sea)\000)\000Island (Micronesia)\000";
struct QZSS_DCR_JMA_COASTAL_REGION_EN_PARENT_Entry { uint16_t offset; uint8_t len; };
static const QZSS_DCR_JMA_COASTAL_REGION_EN_PARENT_Entry QZSS_DCR_JMA_COASTAL_REGION_EN_PARENT_TABLE[] AZARAC_PROGMEM = {
    {0u, 37u},
    {38u, 29u},
    {68u, 29u},
    {98u, 35u},
    {134u, 34u},
    {169u, 14u},
    {184u, 35u},
    {220u, 9u},
    {230u, 9u},
    {240u, 5u},
    {246u, 13u},
    {260u, 1u},
    {262u, 19u},
};
struct QZSS_DCR_JMA_COASTAL_REGION_EN_Entry { uint8_t id; uint8_t parent; uint16_t offset; uint8_t len; };
static const QZSS_DCR_JMA_COASTAL_REGION_EN_Entry QZSS_DCR_JMA_COASTAL_REGION_EN_TABLE[] AZARAC_PROGMEM = {
    {1u, 0u, 0u, 13u},
    {2u, 0u, 14u, 15u},
    {3u, 8u, 30u, 21u},
    {4u, 8u, 52u, 19u},
    {5u, 6u, 72u, 5u},
    {6u, 6u, 78u, 5u},
    {7u, 6u, 84u, 8u},
    {8u, 7u, 93u, 7u},
    {9u, 1u, 101u, 5u},
    {10u, 1u, 107u, 7u},
    {11u, 1u, 115u, 7u},
    {12u, 1u, 123u, 6u},
    {13u, 1u, 130u, 6u},
    {14u, 1u, 137u, 5u},
    {15u, 2u, 143u, 8u},
    {16u, 2u, 152u, 6u},
    {17u, 2u, 159u, 6u},
    {18u, 2u, 166u, 9u},
    {19u, 2u, 176u, 5u},
    {20u, 2u, 182u, 8u},
    {21u, 3u, 191u, 6u},
    {22u, 3u, 198u, 5u},
    {23u, 3u, 204u, 6u},
    {24u, 3u, 211u, 13u},
    {25u, 3u, 225u, 6u},
    {26u, 3u, 232u, 7u},
    {27u, 3u, 240u, 5u},
    {28u, 3u, 246u, 5u},
    {29u, 8u, 252u, 13u},
    {30u, 8u, 266u, 15u},
    {31u, 11u, 282u, 14u},
    {32u, 12u, 297u, 4u},
    {33u, 12u, 302u, 6u},
    {34u, 12u, 309u, 8u},
    {35u, 12u, 318u, 7u},
    {36u, 8u, 326u, 25u},
    {37u, 4u, 352u, 7u},
    {38u, 4u, 360u, 4u},
    {39u, 4u, 365u, 8u},
    {40u, 5u, 374u, 5u},
    {41u, 5u, 380u, 7u},
    {66u, 0u, 388u, 18u},
    {67u, 0u, 407u, 10u},
    {68u, 6u, 418u, 9u},
    {69u, 6u, 428u, 9u},
    {70u, 6u, 438u, 12u},
    {71u, 7u, 451u, 7u},
    {72u, 7u, 459u, 7u},
    {74u, 7u, 467u, 5u},
    {75u, 2u, 473u, 4u},
    {76u, 3u, 478u, 7u},
    {77u, 4u, 486u, 7u},
    {78u, 5u, 494u, 4u},
    {79u, 5u, 499u, 7u},
    {80u, 5u, 507u, 6u},
    {81u, 5u, 514u, 6u},
    {82u, 10u, 521u, 4u},
    {83u, 9u, 526u, 19u},
    {84u, 9u, 546u, 30u},
    {85u, 9u, 577u, 30u},
    {86u, 9u, 608u, 29u},
    {99u, 255u, 638u, 7u},
    {100u, 255u, 646u, 12u},
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_coastal_region_en_lookup(uint8_t id) noexcept {
    uint8_t lo = 0, hi = 63;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        const char* AZARAC_PROGMEM ep = reinterpret_cast<const char*>(&QZSS_DCR_JMA_COASTAL_REGION_EN_TABLE[mid]);
        uint8_t eid = static_cast<uint8_t>(pgm_read_byte(ep + offsetof(QZSS_DCR_JMA_COASTAL_REGION_EN_Entry, id)));
        if (eid == id) {
            uint16_t off = pgm_read_word(ep + offsetof(QZSS_DCR_JMA_COASTAL_REGION_EN_Entry, offset));
            uint8_t n = pgm_read_byte(ep + offsetof(QZSS_DCR_JMA_COASTAL_REGION_EN_Entry, len));
            uint8_t pi = pgm_read_byte(ep + offsetof(QZSS_DCR_JMA_COASTAL_REGION_EN_Entry, parent));
            if (pi == 255u) return azarac_pgm_view(QZSS_DCR_JMA_COASTAL_REGION_EN_POOL + off, n);
            const char* AZARAC_PROGMEM pp = reinterpret_cast<const char*>(&QZSS_DCR_JMA_COASTAL_REGION_EN_PARENT_TABLE[pi]);
            uint16_t poff = pgm_read_word(pp + offsetof(QZSS_DCR_JMA_COASTAL_REGION_EN_PARENT_Entry, offset));
            uint8_t pn = pgm_read_byte(pp + offsetof(QZSS_DCR_JMA_COASTAL_REGION_EN_PARENT_Entry, len));
            return azarac_pgm_join(QZSS_DCR_JMA_COASTAL_REGION_EN_POOL + off, n, QZSS_DCR_JMA_COASTAL_REGION_EN_PARENT_POOL + poff, pn);
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
