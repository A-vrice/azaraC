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
static const char AZARAC_PROGMEM QZSS_DCR_JMA_VOLCANO_NAME_EN_POOL[] = "Shiretoko-Iozan\000Raus\000Mashu\000Atosanupuri\000Meaka\000Maru\000Taisetsuzan\000Tokachi\000Taruma\000Eniwa\000Kuttara\000Usuzan\000Hokkaido-Komagatake\000Esan\000Oshima-O\000Rishirizan\000Yoteizan\000Niseko\000Tenchozan\000Oaka\000Moyoro\000Chiripp\000Sashius\000Odamo\000Etorofu-Yak\000Etorofu-Atosanupuri\000Berutarub\000Chacha\000Raus\000Tomari\000Rurui\000Osorezan\000Iwak\000Hakkodasan\000Towada\000Akita-Yak\000Hachimantai\000Iwat\000Akita-Komagatake\000Choka\000Kuriko\000Naruko\000Zaozan (Zaosan)\000Azu\000Adatar\000Banda\000Hiuchigatake\000Hijiori\000Numazawa\000Nas\000Nikko-Shiran\000Akag\000Harunasan\000Kusatsu-Shiran\000Asa\000Niigata-Yak\000Myokosan\000Midagahara\000Yake\000Norikura\000Ontak\000Hak\000Fuj\000Hakon\000Izu-Tobu V\000Izu-O\000Nii\000Kozu\000Miyake\000Hachijo\000Aoga\000Beyonesu (Bayonnaise) Rocks\000Sumisujima (Smith Rocks)\000Izu-Tori\000Nishin\000Kaitoku\000Funka Asane\000Ioto\000Kita-Fukutokutai\000Fukutoku-Oka-no-Ba\000Takahar\000Yoko\000Akandan\000T\000Mikura\000Sofugan\000Kaikata\000Minami-Hiyoshi\000Nikko\000Nanta\000Mt. Kusatsu-Shirane(Mt. Shirane(Yugama Area))\000Mt. Kusatsu-Shirane(Mt. Motoshirane)\000Sanb\000Kuj\000Asosan\000Unze\000Kirishimayama\000Sakura\000Kaimo\000Satsuma-Io\000Kuchinoerabu\000Nakan\000Suwanose\000Abu V\000Tsurumidake and Gara\000Yuf\000Fukue V\000Yonemaru and Sumiyoshiike\000Wakamiko\000Ikeda and Yamagawa\000Kuchin\000Kirishimayama (Ohachi)\000Kirishimayama (Shinmoedake)\000Kirishimayama (Ebino Highland)\000Kirishimayama (Ohataike)\000Io-Tori\000Submarine Volcano NNE of Iriomote\000Active volcanoes nationwide\000Other active v\000New active v\000Other Volcano\000";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_VOLCANO_NAME_EN_PARENT_POOL[] = " Seamount\000ayama\000dake\000esan\000eyama\000isan\000jima\000mayama\000ndake\000olcanoes\000oshima\000shima\000udake\000usan\000yama\000";
struct QZSS_DCR_JMA_VOLCANO_NAME_EN_PARENT_Entry { uint16_t offset; };
static const QZSS_DCR_JMA_VOLCANO_NAME_EN_PARENT_Entry QZSS_DCR_JMA_VOLCANO_NAME_EN_PARENT_TABLE[] AZARAC_PROGMEM = {
    {0u},
    {10u},
    {16u},
    {21u},
    {26u},
    {32u},
    {37u},
    {42u},
    {49u},
    {55u},
    {64u},
    {71u},
    {77u},
    {83u},
    {88u},
};
struct QZSS_DCR_JMA_VOLCANO_NAME_EN_Entry { uint16_t id; uint8_t parent; uint16_t offset; };
static const QZSS_DCR_JMA_VOLCANO_NAME_EN_Entry QZSS_DCR_JMA_VOLCANO_NAME_EN_TABLE[] AZARAC_PROGMEM = {
    {101u, 255u, 0u},
    {102u, 12u, 16u},
    {103u, 255u, 21u},
    {104u, 255u, 27u},
    {105u, 8u, 39u},
    {106u, 14u, 45u},
    {107u, 255u, 50u},
    {108u, 2u, 62u},
    {109u, 3u, 70u},
    {110u, 2u, 77u},
    {111u, 255u, 83u},
    {112u, 255u, 91u},
    {113u, 255u, 98u},
    {114u, 255u, 118u},
    {115u, 11u, 123u},
    {116u, 255u, 132u},
    {117u, 255u, 143u},
    {118u, 255u, 152u},
    {119u, 255u, 159u},
    {120u, 8u, 169u},
    {151u, 2u, 174u},
    {152u, 13u, 181u},
    {153u, 12u, 189u},
    {154u, 5u, 197u},
    {155u, 4u, 203u},
    {156u, 255u, 215u},
    {157u, 3u, 235u},
    {158u, 2u, 245u},
    {159u, 13u, 252u},
    {160u, 14u, 257u},
    {161u, 2u, 264u},
    {201u, 255u, 270u},
    {202u, 5u, 279u},
    {203u, 255u, 284u},
    {204u, 255u, 295u},
    {205u, 4u, 302u},
    {206u, 255u, 312u},
    {207u, 3u, 324u},
    {208u, 255u, 329u},
    {209u, 5u, 346u},
    {210u, 7u, 352u},
    {211u, 255u, 359u},
    {212u, 255u, 366u},
    {213u, 7u, 382u},
    {214u, 1u, 386u},
    {215u, 5u, 393u},
    {216u, 255u, 399u},
    {217u, 255u, 412u},
    {218u, 255u, 420u},
    {301u, 12u, 429u},
    {302u, 3u, 433u},
    {303u, 5u, 446u},
    {304u, 255u, 451u},
    {305u, 3u, 461u},
    {306u, 7u, 476u},
    {307u, 4u, 480u},
    {308u, 255u, 492u},
    {309u, 255u, 501u},
    {310u, 2u, 512u},
    {311u, 2u, 517u},
    {312u, 3u, 526u},
    {313u, 13u, 532u},
    {314u, 5u, 536u},
    {315u, 4u, 540u},
    {316u, 9u, 546u},
    {317u, 11u, 557u},
    {318u, 6u, 563u},
    {319u, 11u, 567u},
    {320u, 6u, 572u},
    {321u, 6u, 579u},
    {322u, 11u, 587u},
    {323u, 255u, 592u},
    {324u, 255u, 620u},
    {325u, 11u, 645u},
    {326u, 10u, 654u},
    {327u, 0u, 661u},
    {328u, 255u, 669u},
    {329u, 255u, 681u},
    {330u, 255u, 686u},
    {331u, 255u, 703u},
    {333u, 1u, 722u},
    {334u, 2u, 730u},
    {335u, 1u, 735u},
    {336u, 10u, 743u},
    {337u, 6u, 745u},
    {338u, 255u, 752u},
    {339u, 0u, 760u},
    {340u, 0u, 768u},
    {341u, 0u, 783u},
    {342u, 5u, 789u},
    {350u, 255u, 795u},
    {351u, 255u, 841u},
    {401u, 3u, 878u},
    {502u, 13u, 883u},
    {503u, 255u, 887u},
    {504u, 8u, 894u},
    {505u, 255u, 899u},
    {506u, 6u, 913u},
    {507u, 8u, 920u},
    {508u, 6u, 926u},
    {509u, 6u, 937u},
    {510u, 10u, 950u},
    {511u, 6u, 956u},
    {512u, 9u, 965u},
    {513u, 8u, 971u},
    {514u, 12u, 992u},
    {515u, 9u, 996u},
    {516u, 255u, 1004u},
    {517u, 255u, 1030u},
    {518u, 255u, 1039u},
    {519u, 10u, 1058u},
    {550u, 255u, 1065u},
    {551u, 255u, 1088u},
    {552u, 255u, 1116u},
    {553u, 255u, 1147u},
    {601u, 11u, 1172u},
    {602u, 6u, 1180u},
    {900u, 255u, 1214u},
    {901u, 9u, 1242u},
    {902u, 9u, 1257u},
    {4000u, 255u, 1270u},
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_volcano_name_en_lookup(uint16_t id) noexcept {
    uint8_t lo = 0, hi = 121;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        const char* AZARAC_PROGMEM ep = reinterpret_cast<const char*>(&QZSS_DCR_JMA_VOLCANO_NAME_EN_TABLE[mid]);
        uint16_t eid = pgm_read_word(ep + offsetof(QZSS_DCR_JMA_VOLCANO_NAME_EN_Entry, id));
        if (eid == id) {
            uint16_t off = pgm_read_word(ep + offsetof(QZSS_DCR_JMA_VOLCANO_NAME_EN_Entry, offset));
            uint8_t pi = pgm_read_byte(ep + offsetof(QZSS_DCR_JMA_VOLCANO_NAME_EN_Entry, parent));
            if (pi == 255u) return azarac_pgm_view_z(QZSS_DCR_JMA_VOLCANO_NAME_EN_POOL + off);
            const char* AZARAC_PROGMEM pp = reinterpret_cast<const char*>(&QZSS_DCR_JMA_VOLCANO_NAME_EN_PARENT_TABLE[pi]);
            uint16_t poff = pgm_read_word(pp + offsetof(QZSS_DCR_JMA_VOLCANO_NAME_EN_PARENT_Entry, offset));
            return azarac_pgm_join_z(QZSS_DCR_JMA_VOLCANO_NAME_EN_POOL + off, QZSS_DCR_JMA_VOLCANO_NAME_EN_PARENT_POOL + poff);
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
