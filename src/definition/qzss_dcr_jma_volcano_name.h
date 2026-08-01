#pragma once
// AUTO-GENERATED from azarashi 0.16.4 with CI-CD
// Source module : qzss_dcr_jma_volcano_name
// Variable      : qzss_dcr_jma_volcano_name
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

#if (AZARAC_ENABLE_VOLCANO)

#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCR_JMA_VOLCANO_NAME_POOL[] = "知床硫黄山\0羅臼岳\0摩周\0アトサヌプリ\0雌阿寒岳\0丸山\0大雪山\0十勝岳\0樽前山\0恵庭岳\0倶多楽\0有珠山\0北海道駒ヶ岳\0恵山\0渡島大島\0利尻山\0羊蹄山\0ニセコ\0天頂山\0雄阿寒岳\0茂世路岳\0散布山\0指臼岳\0小田萌山\0択捉焼山\0択捉阿登佐岳\0ベルタルベ山\0爺爺岳\0羅臼山\0泊山\0ルルイ岳\0恐山\0岩木山\0八甲田山\0十和田\0秋田焼山\0八幡平\0岩手山\0秋田駒ヶ岳\0鳥海山\0栗駒山\0鳴子\0蔵王山\0吾妻山\0安達太良山\0磐梯山\0燧ヶ岳\0肘折\0沼沢\0那須岳\0日光白根山\0赤城山\0榛名山\0草津白根山\0浅間山\0新潟焼山\0妙高山\0弥陀ヶ原\0焼岳\0乗鞍岳\0御嶽山\0白山\0富士山\0箱根山\0伊豆東部火山群\0伊豆大島\0新島\0神津島\0三宅島\0八丈島\0青ヶ島\0ベヨネース列岩\0須美寿島\0伊豆鳥島\0西之島\0海徳海山\0噴火浅根\0硫黄島\0北福徳堆\0福徳岡ノ場\0高原山\0横岳\0アカンダナ山\0利島\0御蔵島\0孀婦岩\0海形海山\0南日吉海山\0日光海山\0男体山\0草津白根山(白根山(湯釜付近))\0草津白根山(本白根山)\0三瓶山\0九重山\0阿蘇山\0雲仙岳\0霧島山\0桜島\0開聞岳\0薩摩硫黄島\0口永良部島\0中之島\0諏訪之瀬島\0阿武火山群\0鶴見岳・伽藍岳\0由布岳\0福江火山群\0米丸・住吉池\0若尊\0池田・山川\0口之島\0霧島山(御鉢)\0霧島山(新燃岳)\0霧島山(えびの高原(硫黄山)周辺)\0霧島山(大幡池)\0硫黄鳥島\0西表島北北東海底火山\0全国の活火山\0その他の活火山\0新たな活火山\0その他の火山\0";
struct QZSS_DCR_JMA_VOLCANO_NAME_Entry { uint16_t id; uint16_t offset; uint16_t len; };
static const QZSS_DCR_JMA_VOLCANO_NAME_Entry QZSS_DCR_JMA_VOLCANO_NAME_TABLE[] AZARAC_PROGMEM = {
    {101u, 0u, 15u},
    {102u, 16u, 9u},
    {103u, 26u, 6u},
    {104u, 33u, 18u},
    {105u, 52u, 12u},
    {106u, 65u, 6u},
    {107u, 72u, 9u},
    {108u, 82u, 9u},
    {109u, 92u, 9u},
    {110u, 102u, 9u},
    {111u, 112u, 9u},
    {112u, 122u, 9u},
    {113u, 132u, 18u},
    {114u, 151u, 6u},
    {115u, 158u, 12u},
    {116u, 171u, 9u},
    {117u, 181u, 9u},
    {118u, 191u, 9u},
    {119u, 201u, 9u},
    {120u, 211u, 12u},
    {151u, 224u, 12u},
    {152u, 237u, 9u},
    {153u, 247u, 9u},
    {154u, 257u, 12u},
    {155u, 270u, 12u},
    {156u, 283u, 18u},
    {157u, 302u, 18u},
    {158u, 321u, 9u},
    {159u, 331u, 9u},
    {160u, 341u, 6u},
    {161u, 348u, 12u},
    {201u, 361u, 6u},
    {202u, 368u, 9u},
    {203u, 378u, 12u},
    {204u, 391u, 9u},
    {205u, 401u, 12u},
    {206u, 414u, 9u},
    {207u, 424u, 9u},
    {208u, 434u, 15u},
    {209u, 450u, 9u},
    {210u, 460u, 9u},
    {211u, 470u, 6u},
    {212u, 477u, 9u},
    {213u, 487u, 9u},
    {214u, 497u, 15u},
    {215u, 513u, 9u},
    {216u, 523u, 9u},
    {217u, 533u, 6u},
    {218u, 540u, 6u},
    {301u, 547u, 9u},
    {302u, 557u, 15u},
    {303u, 573u, 9u},
    {304u, 583u, 9u},
    {305u, 593u, 15u},
    {306u, 609u, 9u},
    {307u, 619u, 12u},
    {308u, 632u, 9u},
    {309u, 642u, 12u},
    {310u, 655u, 6u},
    {311u, 662u, 9u},
    {312u, 672u, 9u},
    {313u, 682u, 6u},
    {314u, 689u, 9u},
    {315u, 699u, 9u},
    {316u, 709u, 21u},
    {317u, 731u, 12u},
    {318u, 744u, 6u},
    {319u, 751u, 9u},
    {320u, 761u, 9u},
    {321u, 771u, 9u},
    {322u, 781u, 9u},
    {323u, 791u, 21u},
    {324u, 813u, 12u},
    {325u, 826u, 12u},
    {326u, 839u, 9u},
    {327u, 849u, 12u},
    {328u, 862u, 12u},
    {329u, 875u, 9u},
    {330u, 885u, 12u},
    {331u, 898u, 15u},
    {333u, 914u, 9u},
    {334u, 924u, 6u},
    {335u, 931u, 18u},
    {336u, 950u, 6u},
    {337u, 957u, 9u},
    {338u, 967u, 9u},
    {339u, 977u, 12u},
    {340u, 990u, 15u},
    {341u, 1006u, 12u},
    {342u, 1019u, 9u},
    {350u, 1029u, 40u},
    {351u, 1070u, 29u},
    {401u, 1100u, 9u},
    {502u, 1110u, 9u},
    {503u, 1120u, 9u},
    {504u, 1130u, 9u},
    {505u, 1140u, 9u},
    {506u, 1150u, 6u},
    {507u, 1157u, 9u},
    {508u, 1167u, 15u},
    {509u, 1183u, 15u},
    {510u, 1199u, 9u},
    {511u, 1209u, 15u},
    {512u, 1225u, 15u},
    {513u, 1241u, 21u},
    {514u, 1263u, 9u},
    {515u, 1273u, 15u},
    {516u, 1289u, 18u},
    {517u, 1308u, 6u},
    {518u, 1315u, 15u},
    {519u, 1331u, 9u},
    {550u, 1341u, 17u},
    {551u, 1359u, 20u},
    {552u, 1380u, 43u},
    {553u, 1424u, 20u},
    {601u, 1445u, 12u},
    {602u, 1458u, 30u},
    {900u, 1489u, 18u},
    {901u, 1508u, 21u},
    {902u, 1530u, 18u},
    {4000u, 1549u, 18u},
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_volcano_name_lookup(uint16_t id) noexcept {
    uint8_t lo = 0, hi = 121;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        const char* AZARAC_PROGMEM ep = reinterpret_cast<const char*>(&QZSS_DCR_JMA_VOLCANO_NAME_TABLE[mid]);
        uint16_t eid = pgm_read_word(ep + offsetof(QZSS_DCR_JMA_VOLCANO_NAME_Entry, id));
        if (eid == id) {
            uint16_t off = pgm_read_word(ep + offsetof(QZSS_DCR_JMA_VOLCANO_NAME_Entry, offset));
            uint16_t n = pgm_read_word(ep + offsetof(QZSS_DCR_JMA_VOLCANO_NAME_Entry, len));
            if (n == 0) return std::nullopt;
            return azarac_pgm_view(QZSS_DCR_JMA_VOLCANO_NAME_POOL + off, n);
        }
        if (eid < id) lo = static_cast<uint8_t>(mid + 1); else hi = mid;
    }
    return std::nullopt;
}
#else
struct QZSS_DCR_JMA_VOLCANO_NAME_Entry { uint16_t id; std::optional<std::string_view> label; };
inline constexpr QZSS_DCR_JMA_VOLCANO_NAME_Entry QZSS_DCR_JMA_VOLCANO_NAME_TABLE[] = {
    {101u, std::string_view{"知床硫黄山", 15}},
    {102u, std::string_view{"羅臼岳", 9}},
    {103u, std::string_view{"摩周", 6}},
    {104u, std::string_view{"アトサヌプリ", 18}},
    {105u, std::string_view{"雌阿寒岳", 12}},
    {106u, std::string_view{"丸山", 6}},
    {107u, std::string_view{"大雪山", 9}},
    {108u, std::string_view{"十勝岳", 9}},
    {109u, std::string_view{"樽前山", 9}},
    {110u, std::string_view{"恵庭岳", 9}},
    {111u, std::string_view{"倶多楽", 9}},
    {112u, std::string_view{"有珠山", 9}},
    {113u, std::string_view{"北海道駒ヶ岳", 18}},
    {114u, std::string_view{"恵山", 6}},
    {115u, std::string_view{"渡島大島", 12}},
    {116u, std::string_view{"利尻山", 9}},
    {117u, std::string_view{"羊蹄山", 9}},
    {118u, std::string_view{"ニセコ", 9}},
    {119u, std::string_view{"天頂山", 9}},
    {120u, std::string_view{"雄阿寒岳", 12}},
    {151u, std::string_view{"茂世路岳", 12}},
    {152u, std::string_view{"散布山", 9}},
    {153u, std::string_view{"指臼岳", 9}},
    {154u, std::string_view{"小田萌山", 12}},
    {155u, std::string_view{"択捉焼山", 12}},
    {156u, std::string_view{"択捉阿登佐岳", 18}},
    {157u, std::string_view{"ベルタルベ山", 18}},
    {158u, std::string_view{"爺爺岳", 9}},
    {159u, std::string_view{"羅臼山", 9}},
    {160u, std::string_view{"泊山", 6}},
    {161u, std::string_view{"ルルイ岳", 12}},
    {201u, std::string_view{"恐山", 6}},
    {202u, std::string_view{"岩木山", 9}},
    {203u, std::string_view{"八甲田山", 12}},
    {204u, std::string_view{"十和田", 9}},
    {205u, std::string_view{"秋田焼山", 12}},
    {206u, std::string_view{"八幡平", 9}},
    {207u, std::string_view{"岩手山", 9}},
    {208u, std::string_view{"秋田駒ヶ岳", 15}},
    {209u, std::string_view{"鳥海山", 9}},
    {210u, std::string_view{"栗駒山", 9}},
    {211u, std::string_view{"鳴子", 6}},
    {212u, std::string_view{"蔵王山", 9}},
    {213u, std::string_view{"吾妻山", 9}},
    {214u, std::string_view{"安達太良山", 15}},
    {215u, std::string_view{"磐梯山", 9}},
    {216u, std::string_view{"燧ヶ岳", 9}},
    {217u, std::string_view{"肘折", 6}},
    {218u, std::string_view{"沼沢", 6}},
    {301u, std::string_view{"那須岳", 9}},
    {302u, std::string_view{"日光白根山", 15}},
    {303u, std::string_view{"赤城山", 9}},
    {304u, std::string_view{"榛名山", 9}},
    {305u, std::string_view{"草津白根山", 15}},
    {306u, std::string_view{"浅間山", 9}},
    {307u, std::string_view{"新潟焼山", 12}},
    {308u, std::string_view{"妙高山", 9}},
    {309u, std::string_view{"弥陀ヶ原", 12}},
    {310u, std::string_view{"焼岳", 6}},
    {311u, std::string_view{"乗鞍岳", 9}},
    {312u, std::string_view{"御嶽山", 9}},
    {313u, std::string_view{"白山", 6}},
    {314u, std::string_view{"富士山", 9}},
    {315u, std::string_view{"箱根山", 9}},
    {316u, std::string_view{"伊豆東部火山群", 21}},
    {317u, std::string_view{"伊豆大島", 12}},
    {318u, std::string_view{"新島", 6}},
    {319u, std::string_view{"神津島", 9}},
    {320u, std::string_view{"三宅島", 9}},
    {321u, std::string_view{"八丈島", 9}},
    {322u, std::string_view{"青ヶ島", 9}},
    {323u, std::string_view{"ベヨネース列岩", 21}},
    {324u, std::string_view{"須美寿島", 12}},
    {325u, std::string_view{"伊豆鳥島", 12}},
    {326u, std::string_view{"西之島", 9}},
    {327u, std::string_view{"海徳海山", 12}},
    {328u, std::string_view{"噴火浅根", 12}},
    {329u, std::string_view{"硫黄島", 9}},
    {330u, std::string_view{"北福徳堆", 12}},
    {331u, std::string_view{"福徳岡ノ場", 15}},
    {333u, std::string_view{"高原山", 9}},
    {334u, std::string_view{"横岳", 6}},
    {335u, std::string_view{"アカンダナ山", 18}},
    {336u, std::string_view{"利島", 6}},
    {337u, std::string_view{"御蔵島", 9}},
    {338u, std::string_view{"孀婦岩", 9}},
    {339u, std::string_view{"海形海山", 12}},
    {340u, std::string_view{"南日吉海山", 15}},
    {341u, std::string_view{"日光海山", 12}},
    {342u, std::string_view{"男体山", 9}},
    {350u, std::string_view{"草津白根山(白根山(湯釜付近))", 40}},
    {351u, std::string_view{"草津白根山(本白根山)", 29}},
    {401u, std::string_view{"三瓶山", 9}},
    {502u, std::string_view{"九重山", 9}},
    {503u, std::string_view{"阿蘇山", 9}},
    {504u, std::string_view{"雲仙岳", 9}},
    {505u, std::string_view{"霧島山", 9}},
    {506u, std::string_view{"桜島", 6}},
    {507u, std::string_view{"開聞岳", 9}},
    {508u, std::string_view{"薩摩硫黄島", 15}},
    {509u, std::string_view{"口永良部島", 15}},
    {510u, std::string_view{"中之島", 9}},
    {511u, std::string_view{"諏訪之瀬島", 15}},
    {512u, std::string_view{"阿武火山群", 15}},
    {513u, std::string_view{"鶴見岳・伽藍岳", 21}},
    {514u, std::string_view{"由布岳", 9}},
    {515u, std::string_view{"福江火山群", 15}},
    {516u, std::string_view{"米丸・住吉池", 18}},
    {517u, std::string_view{"若尊", 6}},
    {518u, std::string_view{"池田・山川", 15}},
    {519u, std::string_view{"口之島", 9}},
    {550u, std::string_view{"霧島山(御鉢)", 17}},
    {551u, std::string_view{"霧島山(新燃岳)", 20}},
    {552u, std::string_view{"霧島山(えびの高原(硫黄山)周辺)", 43}},
    {553u, std::string_view{"霧島山(大幡池)", 20}},
    {601u, std::string_view{"硫黄鳥島", 12}},
    {602u, std::string_view{"西表島北北東海底火山", 30}},
    {900u, std::string_view{"全国の活火山", 18}},
    {901u, std::string_view{"その他の活火山", 21}},
    {902u, std::string_view{"新たな活火山", 18}},
    {4000u, std::string_view{"その他の火山", 18}},};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_volcano_name_lookup(uint16_t id) noexcept {
    uint8_t lo = 0, hi = 121;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        if (QZSS_DCR_JMA_VOLCANO_NAME_TABLE[mid].id == id) return QZSS_DCR_JMA_VOLCANO_NAME_TABLE[mid].label;
        if (QZSS_DCR_JMA_VOLCANO_NAME_TABLE[mid].id < id) lo = mid + 1;
        else hi = mid;
    }
    return std::nullopt;
}
#endif

#else

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_volcano_name_lookup(uint16_t id) noexcept {
    (void)id;
    return std::nullopt;
}

#endif

} // namespace def
} // namespace azaraC
