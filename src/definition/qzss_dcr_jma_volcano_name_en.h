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
static const char AZARAC_PROGMEM QZSS_DCR_JMA_VOLCANO_NAME_EN_POOL[] = "Shiretoko-Io\000Rausu\000Mashu\000Atosanupur\000Meaka\000Maru\000Taisetsu\000Tokachi\000Taruma\000Eniwa\000Kuttar\000Usuz\000Hokkaido-Komagat\000Esan\000Oshima-O\000Rishiri\000Yotei\000Nisek\000Tencho\000Oaka\000Moyoro\000Chirippu\000Sashiusu\000Odamo\000Etorofu-Yak\000Etorofu-Atosanupur\000Berutarub\000Chacha\000Rausu\000Tomari\000Rurui\000Osore\000Iwak\000Hakkoda\000Towad\000Akita-Yak\000Hachimanta\000Iwat\000Akita-Komagat\000Choka\000Kurikom\000Naruk\000Zaozan (Zaosan\000Azum\000Adatar\000Banda\000Hiuchigat\000Hijior\000Numazaw\000Nasu\000Nikko-Shiran\000Akag\000Haruna\000Kusatsu-Shiran\000Asam\000Niigata-Yak\000Myoko\000Midagahar\000Yake\000Norikura\000Ontak\000Haku\000Fuji\000Hakon\000Izu-Tobu V\000Izu-O\000Niij\000Kozu\000Miyake\000Hachijo\000Aoga\000Beyonesu (Bayonnaise) Rock\000Sumisujima (Smith Rocks\000Izu-Tori\000Nishino\000Kaitoku\000Funka Asan\000Ioto\000Kita-Fukutokuta\000Fukutoku-Oka-no-B\000Takahar\000Yoko\000Akandan\000Tosh\000Mikura\000Sofug\000Kaikata\000Minami-Hiyoshi\000Nikko\000Nanta\000Mt. Kusatsu-Shirane(Mt. Shirane(Yugama Area)\000Mt. Kusatsu-Shirane(Mt. Motoshirane\000Sanb\000Kuju\000Asos\000Unze\000Kirishimayama\000Sakura\000Kaimo\000Satsuma-Io\000Kuchinoerabu\000Nakano\000Suwanose\000Abu V\000Tsurumidake and Gara\000Yufu\000Fukue V\000Yonemaru and Sumiyoshii\000Wakamik\000Ikeda and Yamagaw\000Kuchino\000Kirishimayama (Ohachi)\000Kirishimayama (Shinmoedake)\000Kirishimayama (Ebino Highland)\000Kirishimayama (Ohataike)\000Io-Tori\000Submarine Volcano NNE of Iriomote\000Active volcanoes nationwid\000Other active v\000New active v\000Other Volcan\000";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_VOLCANO_NAME_EN_PARENT_POOL[] = " Seamount\000)\000a\000ake\000an\000ayama\000dake\000e\000esan\000eyama\000i\000ima\000isan\000jima\000ke\000ndake\000o\000olcanoes\000s\000san\000shima\000yama\000zan\000";
struct QZSS_DCR_JMA_VOLCANO_NAME_EN_PARENT_Entry { uint16_t offset; uint8_t len; };
static const QZSS_DCR_JMA_VOLCANO_NAME_EN_PARENT_Entry QZSS_DCR_JMA_VOLCANO_NAME_EN_PARENT_TABLE[] AZARAC_PROGMEM = {
    {0u, 9u},
    {10u, 1u},
    {12u, 1u},
    {14u, 3u},
    {18u, 2u},
    {21u, 5u},
    {27u, 4u},
    {32u, 1u},
    {34u, 4u},
    {39u, 5u},
    {45u, 1u},
    {47u, 3u},
    {51u, 4u},
    {56u, 4u},
    {61u, 2u},
    {64u, 5u},
    {70u, 1u},
    {72u, 8u},
    {81u, 1u},
    {83u, 3u},
    {87u, 5u},
    {93u, 4u},
    {98u, 3u},
};
struct QZSS_DCR_JMA_VOLCANO_NAME_EN_Entry { uint16_t id; uint8_t parent; uint16_t offset; uint8_t len; };
static const QZSS_DCR_JMA_VOLCANO_NAME_EN_Entry QZSS_DCR_JMA_VOLCANO_NAME_EN_TABLE[] AZARAC_PROGMEM = {
    {101u, 22u, 0u, 12u},
    {102u, 6u, 13u, 5u},
    {103u, 255u, 19u, 5u},
    {104u, 10u, 25u, 10u},
    {105u, 15u, 36u, 5u},
    {106u, 21u, 42u, 4u},
    {107u, 22u, 47u, 8u},
    {108u, 6u, 56u, 7u},
    {109u, 8u, 64u, 6u},
    {110u, 6u, 71u, 5u},
    {111u, 2u, 77u, 6u},
    {112u, 4u, 84u, 4u},
    {113u, 3u, 89u, 16u},
    {114u, 255u, 106u, 4u},
    {115u, 20u, 111u, 8u},
    {116u, 22u, 120u, 7u},
    {117u, 22u, 128u, 5u},
    {118u, 16u, 134u, 5u},
    {119u, 22u, 140u, 6u},
    {120u, 15u, 147u, 4u},
    {151u, 6u, 152u, 6u},
    {152u, 19u, 159u, 8u},
    {153u, 6u, 168u, 8u},
    {154u, 12u, 177u, 5u},
    {155u, 9u, 183u, 11u},
    {156u, 10u, 195u, 18u},
    {157u, 8u, 214u, 9u},
    {158u, 6u, 224u, 6u},
    {159u, 19u, 231u, 5u},
    {160u, 21u, 237u, 6u},
    {161u, 6u, 244u, 5u},
    {201u, 22u, 250u, 5u},
    {202u, 12u, 256u, 4u},
    {203u, 19u, 261u, 7u},
    {204u, 2u, 269u, 5u},
    {205u, 9u, 275u, 9u},
    {206u, 10u, 285u, 10u},
    {207u, 8u, 296u, 4u},
    {208u, 3u, 301u, 13u},
    {209u, 12u, 315u, 5u},
    {210u, 5u, 321u, 7u},
    {211u, 16u, 329u, 5u},
    {212u, 1u, 335u, 14u},
    {213u, 5u, 350u, 4u},
    {214u, 5u, 355u, 6u},
    {215u, 12u, 362u, 5u},
    {216u, 3u, 368u, 9u},
    {217u, 10u, 378u, 6u},
    {218u, 2u, 385u, 7u},
    {301u, 6u, 393u, 4u},
    {302u, 8u, 398u, 12u},
    {303u, 12u, 411u, 4u},
    {304u, 19u, 416u, 6u},
    {305u, 8u, 423u, 14u},
    {306u, 5u, 438u, 4u},
    {307u, 9u, 443u, 11u},
    {308u, 19u, 455u, 5u},
    {309u, 2u, 461u, 9u},
    {310u, 6u, 471u, 4u},
    {311u, 6u, 476u, 8u},
    {312u, 8u, 485u, 5u},
    {313u, 19u, 491u, 4u},
    {314u, 19u, 496u, 4u},
    {315u, 9u, 501u, 5u},
    {316u, 17u, 507u, 10u},
    {317u, 20u, 518u, 5u},
    {318u, 11u, 524u, 4u},
    {319u, 20u, 529u, 4u},
    {320u, 13u, 534u, 6u},
    {321u, 13u, 541u, 7u},
    {322u, 20u, 549u, 4u},
    {323u, 18u, 554u, 26u},
    {324u, 1u, 581u, 23u},
    {325u, 20u, 605u, 8u},
    {326u, 20u, 614u, 7u},
    {327u, 0u, 622u, 7u},
    {328u, 7u, 630u, 10u},
    {329u, 255u, 641u, 4u},
    {330u, 10u, 646u, 15u},
    {331u, 2u, 662u, 17u},
    {333u, 5u, 680u, 7u},
    {334u, 6u, 688u, 4u},
    {335u, 5u, 693u, 7u},
    {336u, 11u, 701u, 4u},
    {337u, 13u, 706u, 6u},
    {338u, 4u, 713u, 5u},
    {339u, 0u, 719u, 7u},
    {340u, 0u, 727u, 14u},
    {341u, 0u, 742u, 5u},
    {342u, 12u, 748u, 5u},
    {350u, 1u, 754u, 44u},
    {351u, 1u, 799u, 35u},
    {401u, 8u, 835u, 4u},
    {502u, 19u, 840u, 4u},
    {503u, 4u, 845u, 4u},
    {504u, 15u, 850u, 4u},
    {505u, 255u, 855u, 13u},
    {506u, 13u, 869u, 6u},
    {507u, 15u, 876u, 5u},
    {508u, 13u, 882u, 10u},
    {509u, 13u, 893u, 12u},
    {510u, 20u, 906u, 6u},
    {511u, 13u, 913u, 8u},
    {512u, 17u, 922u, 5u},
    {513u, 15u, 928u, 20u},
    {514u, 6u, 949u, 4u},
    {515u, 17u, 954u, 7u},
    {516u, 14u, 962u, 23u},
    {517u, 16u, 986u, 7u},
    {518u, 2u, 994u, 17u},
    {519u, 20u, 1012u, 7u},
    {550u, 255u, 1020u, 22u},
    {551u, 255u, 1043u, 27u},
    {552u, 255u, 1071u, 30u},
    {553u, 255u, 1102u, 24u},
    {601u, 20u, 1127u, 7u},
    {602u, 13u, 1135u, 33u},
    {900u, 7u, 1169u, 26u},
    {901u, 17u, 1196u, 14u},
    {902u, 17u, 1211u, 12u},
    {4000u, 16u, 1224u, 12u},
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_volcano_name_en_lookup(uint16_t id) noexcept {
    uint8_t lo = 0, hi = 121;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        const char* AZARAC_PROGMEM ep = reinterpret_cast<const char*>(&QZSS_DCR_JMA_VOLCANO_NAME_EN_TABLE[mid]);
        uint16_t eid = pgm_read_word(ep + offsetof(QZSS_DCR_JMA_VOLCANO_NAME_EN_Entry, id));
        if (eid == id) {
            uint16_t off = pgm_read_word(ep + offsetof(QZSS_DCR_JMA_VOLCANO_NAME_EN_Entry, offset));
            uint8_t n = pgm_read_byte(ep + offsetof(QZSS_DCR_JMA_VOLCANO_NAME_EN_Entry, len));
            uint8_t pi = pgm_read_byte(ep + offsetof(QZSS_DCR_JMA_VOLCANO_NAME_EN_Entry, parent));
            if (pi == 255u) return azarac_pgm_view(QZSS_DCR_JMA_VOLCANO_NAME_EN_POOL + off, n);
            const char* AZARAC_PROGMEM pp = reinterpret_cast<const char*>(&QZSS_DCR_JMA_VOLCANO_NAME_EN_PARENT_TABLE[pi]);
            uint16_t poff = pgm_read_word(pp + offsetof(QZSS_DCR_JMA_VOLCANO_NAME_EN_PARENT_Entry, offset));
            uint8_t pn = pgm_read_byte(pp + offsetof(QZSS_DCR_JMA_VOLCANO_NAME_EN_PARENT_Entry, len));
            return azarac_pgm_join(QZSS_DCR_JMA_VOLCANO_NAME_EN_POOL + off, n, QZSS_DCR_JMA_VOLCANO_NAME_EN_PARENT_POOL + poff, pn);
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
