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

#if (AZARAC_ENABLE_VOLCANO || AZARAC_ENABLE_ASH_FALL)

#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCR_JMA_VOLCANO_NAME_POOL[] = "知床硫黄山\000羅臼岳\000摩周\000アトサヌプリ\000雌阿寒岳\000丸山\000大雪山\000十勝岳\000樽前山\000恵庭岳\000倶多楽\000有珠山\000北海道駒ヶ岳\000恵山\000渡島大島\000利尻山\000羊蹄山\000ニセコ\000天頂山\000雄阿寒岳\000茂世路岳\000散布山\000指臼岳\000小田萌山\000択捉焼山\000択捉阿登佐岳\000ベルタルベ山\000爺爺岳\000羅臼山\000泊山\000ルルイ岳\000恐山\000岩木山\000八甲田山\000十和田\000秋田焼山\000八幡平\000岩手山\000秋田駒ヶ岳\000鳥海山\000栗駒山\000鳴子\000蔵王山\000吾妻山\000安達太良山\000磐梯山\000燧ヶ岳\000肘折\000沼沢\000那須岳\000日光白根山\000赤城山\000榛名山\000草津白根山\000浅間山\000新潟焼山\000妙高山\000弥陀ヶ原\000焼岳\000乗鞍岳\000御嶽山\000白山\000富士山\000箱根山\000伊豆東部火山群\000伊豆大島\000新島\000神津島\000三宅島\000八丈島\000青ヶ島\000ベヨネース列岩\000須美寿島\000伊豆鳥島\000西之島\000海徳海山\000噴火浅根\000硫黄島\000北福徳堆\000福徳岡ノ場\000高原山\000横岳\000アカンダナ山\000利島\000御蔵島\000孀婦岩\000海形海山\000南日吉海山\000日光海山\000男体山\000草津白根山(白根山(湯釜付近))\000草津白根山(本白根山)\000三瓶山\000九重山\000阿蘇山\000雲仙岳\000霧島山\000桜島\000開聞岳\000薩摩硫黄島\000口永良部島\000中之島\000諏訪之瀬島\000阿武火山群\000鶴見岳・伽藍岳\000由布岳\000福江火山群\000米丸・住吉池\000若尊\000池田・山川\000口之島\000霧島山(御鉢)\000霧島山(新燃岳)\000霧島山(えびの高原(硫黄山)周辺)\000霧島山(大幡池)\000硫黄鳥島\000西表島北北東海底火山\000全国の活火山\000その他の活火山\000新たな活火山\000その他の火山\000";
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
            return azarac_pgm_view(QZSS_DCR_JMA_VOLCANO_NAME_POOL + off, n);
        }
        if (eid < id) lo = static_cast<uint8_t>(mid + 1); else hi = mid;
    }
    return std::nullopt;
}
#else
struct QZSS_DCR_JMA_VOLCANO_NAME_Entry { uint16_t id; const char* label; };
inline constexpr QZSS_DCR_JMA_VOLCANO_NAME_Entry QZSS_DCR_JMA_VOLCANO_NAME_TABLE[] = {
    {101u, "知床硫黄山"},
    {102u, "羅臼岳"},
    {103u, "摩周"},
    {104u, "アトサヌプリ"},
    {105u, "雌阿寒岳"},
    {106u, "丸山"},
    {107u, "大雪山"},
    {108u, "十勝岳"},
    {109u, "樽前山"},
    {110u, "恵庭岳"},
    {111u, "倶多楽"},
    {112u, "有珠山"},
    {113u, "北海道駒ヶ岳"},
    {114u, "恵山"},
    {115u, "渡島大島"},
    {116u, "利尻山"},
    {117u, "羊蹄山"},
    {118u, "ニセコ"},
    {119u, "天頂山"},
    {120u, "雄阿寒岳"},
    {151u, "茂世路岳"},
    {152u, "散布山"},
    {153u, "指臼岳"},
    {154u, "小田萌山"},
    {155u, "択捉焼山"},
    {156u, "択捉阿登佐岳"},
    {157u, "ベルタルベ山"},
    {158u, "爺爺岳"},
    {159u, "羅臼山"},
    {160u, "泊山"},
    {161u, "ルルイ岳"},
    {201u, "恐山"},
    {202u, "岩木山"},
    {203u, "八甲田山"},
    {204u, "十和田"},
    {205u, "秋田焼山"},
    {206u, "八幡平"},
    {207u, "岩手山"},
    {208u, "秋田駒ヶ岳"},
    {209u, "鳥海山"},
    {210u, "栗駒山"},
    {211u, "鳴子"},
    {212u, "蔵王山"},
    {213u, "吾妻山"},
    {214u, "安達太良山"},
    {215u, "磐梯山"},
    {216u, "燧ヶ岳"},
    {217u, "肘折"},
    {218u, "沼沢"},
    {301u, "那須岳"},
    {302u, "日光白根山"},
    {303u, "赤城山"},
    {304u, "榛名山"},
    {305u, "草津白根山"},
    {306u, "浅間山"},
    {307u, "新潟焼山"},
    {308u, "妙高山"},
    {309u, "弥陀ヶ原"},
    {310u, "焼岳"},
    {311u, "乗鞍岳"},
    {312u, "御嶽山"},
    {313u, "白山"},
    {314u, "富士山"},
    {315u, "箱根山"},
    {316u, "伊豆東部火山群"},
    {317u, "伊豆大島"},
    {318u, "新島"},
    {319u, "神津島"},
    {320u, "三宅島"},
    {321u, "八丈島"},
    {322u, "青ヶ島"},
    {323u, "ベヨネース列岩"},
    {324u, "須美寿島"},
    {325u, "伊豆鳥島"},
    {326u, "西之島"},
    {327u, "海徳海山"},
    {328u, "噴火浅根"},
    {329u, "硫黄島"},
    {330u, "北福徳堆"},
    {331u, "福徳岡ノ場"},
    {333u, "高原山"},
    {334u, "横岳"},
    {335u, "アカンダナ山"},
    {336u, "利島"},
    {337u, "御蔵島"},
    {338u, "孀婦岩"},
    {339u, "海形海山"},
    {340u, "南日吉海山"},
    {341u, "日光海山"},
    {342u, "男体山"},
    {350u, "草津白根山(白根山(湯釜付近))"},
    {351u, "草津白根山(本白根山)"},
    {401u, "三瓶山"},
    {502u, "九重山"},
    {503u, "阿蘇山"},
    {504u, "雲仙岳"},
    {505u, "霧島山"},
    {506u, "桜島"},
    {507u, "開聞岳"},
    {508u, "薩摩硫黄島"},
    {509u, "口永良部島"},
    {510u, "中之島"},
    {511u, "諏訪之瀬島"},
    {512u, "阿武火山群"},
    {513u, "鶴見岳・伽藍岳"},
    {514u, "由布岳"},
    {515u, "福江火山群"},
    {516u, "米丸・住吉池"},
    {517u, "若尊"},
    {518u, "池田・山川"},
    {519u, "口之島"},
    {550u, "霧島山(御鉢)"},
    {551u, "霧島山(新燃岳)"},
    {552u, "霧島山(えびの高原(硫黄山)周辺)"},
    {553u, "霧島山(大幡池)"},
    {601u, "硫黄鳥島"},
    {602u, "西表島北北東海底火山"},
    {900u, "全国の活火山"},
    {901u, "その他の活火山"},
    {902u, "新たな活火山"},
    {4000u, "その他の火山"},};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_volcano_name_lookup(uint16_t id) noexcept {
    uint8_t lo = 0, hi = 121;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        if (QZSS_DCR_JMA_VOLCANO_NAME_TABLE[mid].id == id) {
            const char* s = QZSS_DCR_JMA_VOLCANO_NAME_TABLE[mid].label;
            return s ? std::optional<std::string_view>(std::string_view{s}) : std::nullopt;
        }
        if (QZSS_DCR_JMA_VOLCANO_NAME_TABLE[mid].id < id) lo = mid + 1;
        else hi = mid;
    }
    return std::nullopt;
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_volcano_name_lookup(uint16_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_volcano_name_lookup(uint16_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
