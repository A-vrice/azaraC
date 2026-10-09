#pragma once
// AUTO-GENERATED from azarashi 0.17.1 with CI-CD
// Source module : azarashi.definitions.qzss.dcr.volcano_name
// Variable      : qzss_dcr_jma_volcano_name_en
// Entries       : 121
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

#if (AZARAC_ENABLE_VOLCANO || AZARAC_ENABLE_ASH_FALL) && (AZARAC_LANG_EN)

#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCR_JMA_VOLCANO_NAME_EN_POOL[] = "Shiretoko-Iozan\000Rausudake\000Mashu\000Atosanupuri\000Meakandake\000Maruyama\000Taisetsuzan\000Tokachidake\000Tarumaesan\000Eniwadake\000Kuttara\000Usuzan\000Hokkaido-Komagatake\000Esan\000Oshima-Oshima\000Rishirizan\000Yoteizan\000Niseko\000Tenchozan\000Oakandake\000Moyorodake\000Chirippusan\000Sashiusudake\000Odamoisan\000Etorofu-Yakeyama\000Etorofu-Atosanupuri\000Berutarubesan\000Chachadake\000Raususan\000Tomariyama\000Ruruidake\000Osorezan\000Iwakisan\000Hakkodasan\000Towada\000Akita-Yakeyama\000Hachimantai\000Iwatesan\000Akita-Komagatake\000Chokaisan\000Kurikomayama\000Naruko\000Zaozan (Zaosan)\000Azumayama\000Adatarayama\000Bandaisan\000Hiuchigatake\000Hijiori\000Numazawa\000Nasudake\000Nikko-Shiranesan\000Akagisan\000Harunasan\000Kusatsu-Shiranesan\000Asamayama\000Niigata-Yakeyama\000Myokosan\000Midagahara\000Yakedake\000Norikuradake\000Ontakesan\000Hakusan\000Fujisan\000Hakoneyama\000Izu-Tobu Volcanoes\000Izu-Oshima\000Niijima\000Kozushima\000Miyakejima\000Hachijojima\000Aogashima\000Beyonesu (Bayonnaise) Rocks\000Sumisujima (Smith Rocks)\000Izu-Torishima\000Nishinoshima\000Kaitoku Seamount\000Funka Asane\000Ioto\000Kita-Fukutokutai\000Fukutoku-Oka-no-Ba\000Takaharayama\000Yokodake\000Akandanayama\000Toshima\000Mikurajima\000Sofugan\000Kaikata Seamount\000Minami-Hiyoshi Seamount\000Nikko Seamount\000Nantaisan\000Mt. Kusatsu-Shirane(Mt. Shirane(Yugama Area))\000Mt. Kusatsu-Shirane(Mt. Motoshirane)\000Sanbesan\000Kujusan\000Asosan\000Unzendake\000Kirishimayama\000Sakurajima\000Kaimondake\000Satsuma-Iojima\000Kuchinoerabujima\000Nakanoshima\000Suwanosejima\000Abu Volcanoes\000Tsurumidake and Garandake\000Yufudake\000Fukue Volcanoes\000Yonemaru and Sumiyoshiike\000Wakamiko\000Ikeda and Yamagawa\000Kuchinoshima\000Kirishimayama (Ohachi)\000Kirishimayama (Shinmoedake)\000Kirishimayama (Ebino Highland)\000Kirishimayama (Ohataike)\000Io-Torishima\000Submarine Volcano NNE of Iriomotejima\000Active volcanoes nationwide\000Other active volcanoes\000New active volcanoes\000Other Volcano\000";
struct QZSS_DCR_JMA_VOLCANO_NAME_EN_Entry { uint16_t id; uint16_t offset; uint16_t len; };
static const QZSS_DCR_JMA_VOLCANO_NAME_EN_Entry QZSS_DCR_JMA_VOLCANO_NAME_EN_TABLE[] AZARAC_PROGMEM = {
    {101u, 0u, 15u},
    {102u, 16u, 9u},
    {103u, 26u, 5u},
    {104u, 32u, 11u},
    {105u, 44u, 10u},
    {106u, 55u, 8u},
    {107u, 64u, 11u},
    {108u, 76u, 11u},
    {109u, 88u, 10u},
    {110u, 99u, 9u},
    {111u, 109u, 7u},
    {112u, 117u, 6u},
    {113u, 124u, 19u},
    {114u, 144u, 4u},
    {115u, 149u, 13u},
    {116u, 163u, 10u},
    {117u, 174u, 8u},
    {118u, 183u, 6u},
    {119u, 190u, 9u},
    {120u, 200u, 9u},
    {151u, 210u, 10u},
    {152u, 221u, 11u},
    {153u, 233u, 12u},
    {154u, 246u, 9u},
    {155u, 256u, 16u},
    {156u, 273u, 19u},
    {157u, 293u, 13u},
    {158u, 307u, 10u},
    {159u, 318u, 8u},
    {160u, 327u, 10u},
    {161u, 338u, 9u},
    {201u, 348u, 8u},
    {202u, 357u, 8u},
    {203u, 366u, 10u},
    {204u, 377u, 6u},
    {205u, 384u, 14u},
    {206u, 399u, 11u},
    {207u, 411u, 8u},
    {208u, 420u, 16u},
    {209u, 437u, 9u},
    {210u, 447u, 12u},
    {211u, 460u, 6u},
    {212u, 467u, 15u},
    {213u, 483u, 9u},
    {214u, 493u, 11u},
    {215u, 505u, 9u},
    {216u, 515u, 12u},
    {217u, 528u, 7u},
    {218u, 536u, 8u},
    {301u, 545u, 8u},
    {302u, 554u, 16u},
    {303u, 571u, 8u},
    {304u, 580u, 9u},
    {305u, 590u, 18u},
    {306u, 609u, 9u},
    {307u, 619u, 16u},
    {308u, 636u, 8u},
    {309u, 645u, 10u},
    {310u, 656u, 8u},
    {311u, 665u, 12u},
    {312u, 678u, 9u},
    {313u, 688u, 7u},
    {314u, 696u, 7u},
    {315u, 704u, 10u},
    {316u, 715u, 18u},
    {317u, 734u, 10u},
    {318u, 745u, 7u},
    {319u, 753u, 9u},
    {320u, 763u, 10u},
    {321u, 774u, 11u},
    {322u, 786u, 9u},
    {323u, 796u, 27u},
    {324u, 824u, 24u},
    {325u, 849u, 13u},
    {326u, 863u, 12u},
    {327u, 876u, 16u},
    {328u, 893u, 11u},
    {329u, 905u, 4u},
    {330u, 910u, 16u},
    {331u, 927u, 18u},
    {333u, 946u, 12u},
    {334u, 959u, 8u},
    {335u, 968u, 12u},
    {336u, 981u, 7u},
    {337u, 989u, 10u},
    {338u, 1000u, 7u},
    {339u, 1008u, 16u},
    {340u, 1025u, 23u},
    {341u, 1049u, 14u},
    {342u, 1064u, 9u},
    {350u, 1074u, 45u},
    {351u, 1120u, 36u},
    {401u, 1157u, 8u},
    {502u, 1166u, 7u},
    {503u, 1174u, 6u},
    {504u, 1181u, 9u},
    {505u, 1191u, 13u},
    {506u, 1205u, 10u},
    {507u, 1216u, 10u},
    {508u, 1227u, 14u},
    {509u, 1242u, 16u},
    {510u, 1259u, 11u},
    {511u, 1271u, 12u},
    {512u, 1284u, 13u},
    {513u, 1298u, 25u},
    {514u, 1324u, 8u},
    {515u, 1333u, 15u},
    {516u, 1349u, 25u},
    {517u, 1375u, 8u},
    {518u, 1384u, 18u},
    {519u, 1403u, 12u},
    {550u, 1416u, 22u},
    {551u, 1439u, 27u},
    {552u, 1467u, 30u},
    {553u, 1498u, 24u},
    {601u, 1523u, 12u},
    {602u, 1536u, 37u},
    {900u, 1574u, 27u},
    {901u, 1602u, 22u},
    {902u, 1625u, 20u},
    {4000u, 1646u, 13u},
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_volcano_name_en_lookup(uint16_t id) noexcept {
    uint8_t lo = 0, hi = 121;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        const char* AZARAC_PROGMEM ep = reinterpret_cast<const char*>(&QZSS_DCR_JMA_VOLCANO_NAME_EN_TABLE[mid]);
        uint16_t eid = pgm_read_word(ep + offsetof(QZSS_DCR_JMA_VOLCANO_NAME_EN_Entry, id));
        if (eid == id) {
            uint16_t off = pgm_read_word(ep + offsetof(QZSS_DCR_JMA_VOLCANO_NAME_EN_Entry, offset));
            uint16_t n = pgm_read_word(ep + offsetof(QZSS_DCR_JMA_VOLCANO_NAME_EN_Entry, len));
            return azarac_pgm_view(QZSS_DCR_JMA_VOLCANO_NAME_EN_POOL + off, n);
        }
        if (eid < id) lo = static_cast<uint8_t>(mid + 1); else hi = mid;
    }
    return std::nullopt;
}
#else
struct QZSS_DCR_JMA_VOLCANO_NAME_EN_Entry { uint16_t id; const char* label; };
inline constexpr QZSS_DCR_JMA_VOLCANO_NAME_EN_Entry QZSS_DCR_JMA_VOLCANO_NAME_EN_TABLE[] = {
    {101u, "Shiretoko-Iozan"},
    {102u, "Rausudake"},
    {103u, "Mashu"},
    {104u, "Atosanupuri"},
    {105u, "Meakandake"},
    {106u, "Maruyama"},
    {107u, "Taisetsuzan"},
    {108u, "Tokachidake"},
    {109u, "Tarumaesan"},
    {110u, "Eniwadake"},
    {111u, "Kuttara"},
    {112u, "Usuzan"},
    {113u, "Hokkaido-Komagatake"},
    {114u, "Esan"},
    {115u, "Oshima-Oshima"},
    {116u, "Rishirizan"},
    {117u, "Yoteizan"},
    {118u, "Niseko"},
    {119u, "Tenchozan"},
    {120u, "Oakandake"},
    {151u, "Moyorodake"},
    {152u, "Chirippusan"},
    {153u, "Sashiusudake"},
    {154u, "Odamoisan"},
    {155u, "Etorofu-Yakeyama"},
    {156u, "Etorofu-Atosanupuri"},
    {157u, "Berutarubesan"},
    {158u, "Chachadake"},
    {159u, "Raususan"},
    {160u, "Tomariyama"},
    {161u, "Ruruidake"},
    {201u, "Osorezan"},
    {202u, "Iwakisan"},
    {203u, "Hakkodasan"},
    {204u, "Towada"},
    {205u, "Akita-Yakeyama"},
    {206u, "Hachimantai"},
    {207u, "Iwatesan"},
    {208u, "Akita-Komagatake"},
    {209u, "Chokaisan"},
    {210u, "Kurikomayama"},
    {211u, "Naruko"},
    {212u, "Zaozan (Zaosan)"},
    {213u, "Azumayama"},
    {214u, "Adatarayama"},
    {215u, "Bandaisan"},
    {216u, "Hiuchigatake"},
    {217u, "Hijiori"},
    {218u, "Numazawa"},
    {301u, "Nasudake"},
    {302u, "Nikko-Shiranesan"},
    {303u, "Akagisan"},
    {304u, "Harunasan"},
    {305u, "Kusatsu-Shiranesan"},
    {306u, "Asamayama"},
    {307u, "Niigata-Yakeyama"},
    {308u, "Myokosan"},
    {309u, "Midagahara"},
    {310u, "Yakedake"},
    {311u, "Norikuradake"},
    {312u, "Ontakesan"},
    {313u, "Hakusan"},
    {314u, "Fujisan"},
    {315u, "Hakoneyama"},
    {316u, "Izu-Tobu Volcanoes"},
    {317u, "Izu-Oshima"},
    {318u, "Niijima"},
    {319u, "Kozushima"},
    {320u, "Miyakejima"},
    {321u, "Hachijojima"},
    {322u, "Aogashima"},
    {323u, "Beyonesu (Bayonnaise) Rocks"},
    {324u, "Sumisujima (Smith Rocks)"},
    {325u, "Izu-Torishima"},
    {326u, "Nishinoshima"},
    {327u, "Kaitoku Seamount"},
    {328u, "Funka Asane"},
    {329u, "Ioto"},
    {330u, "Kita-Fukutokutai"},
    {331u, "Fukutoku-Oka-no-Ba"},
    {333u, "Takaharayama"},
    {334u, "Yokodake"},
    {335u, "Akandanayama"},
    {336u, "Toshima"},
    {337u, "Mikurajima"},
    {338u, "Sofugan"},
    {339u, "Kaikata Seamount"},
    {340u, "Minami-Hiyoshi Seamount"},
    {341u, "Nikko Seamount"},
    {342u, "Nantaisan"},
    {350u, "Mt. Kusatsu-Shirane(Mt. Shirane(Yugama Area))"},
    {351u, "Mt. Kusatsu-Shirane(Mt. Motoshirane)"},
    {401u, "Sanbesan"},
    {502u, "Kujusan"},
    {503u, "Asosan"},
    {504u, "Unzendake"},
    {505u, "Kirishimayama"},
    {506u, "Sakurajima"},
    {507u, "Kaimondake"},
    {508u, "Satsuma-Iojima"},
    {509u, "Kuchinoerabujima"},
    {510u, "Nakanoshima"},
    {511u, "Suwanosejima"},
    {512u, "Abu Volcanoes"},
    {513u, "Tsurumidake and Garandake"},
    {514u, "Yufudake"},
    {515u, "Fukue Volcanoes"},
    {516u, "Yonemaru and Sumiyoshiike"},
    {517u, "Wakamiko"},
    {518u, "Ikeda and Yamagawa"},
    {519u, "Kuchinoshima"},
    {550u, "Kirishimayama (Ohachi)"},
    {551u, "Kirishimayama (Shinmoedake)"},
    {552u, "Kirishimayama (Ebino Highland)"},
    {553u, "Kirishimayama (Ohataike)"},
    {601u, "Io-Torishima"},
    {602u, "Submarine Volcano NNE of Iriomotejima"},
    {900u, "Active volcanoes nationwide"},
    {901u, "Other active volcanoes"},
    {902u, "New active volcanoes"},
    {4000u, "Other Volcano"},};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_volcano_name_en_lookup(uint16_t id) noexcept {
    uint8_t lo = 0, hi = 121;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        if (QZSS_DCR_JMA_VOLCANO_NAME_EN_TABLE[mid].id == id) {
            const char* s = QZSS_DCR_JMA_VOLCANO_NAME_EN_TABLE[mid].label;
            return s ? std::optional<std::string_view>(std::string_view{s}) : std::nullopt;
        }
        if (QZSS_DCR_JMA_VOLCANO_NAME_EN_TABLE[mid].id < id) lo = mid + 1;
        else hi = mid;
    }
    return std::nullopt;
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_volcano_name_en_lookup(uint16_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_volcano_name_en_lookup(uint16_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
