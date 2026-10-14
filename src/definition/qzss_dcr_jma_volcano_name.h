#pragma once
// AUTO-GENERATED from azarashi 0.17.1 with CI-CD
// Source module : azarashi.definitions.qzss.dcr.volcano_name
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

#if (AZARAC_ENABLE_VOLCANO || AZARAC_ENABLE_ASH_FALL) && (AZARAC_LANG_JA)

#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCR_JMA_VOLCANO_NAME_POOL[] = "知床硫黄\000羅臼\000摩周\000アトサヌプリ\000雌阿寒\000丸山\000大雪\000十勝\000樽前\000恵庭\000倶多楽\000有珠\000北海道駒ヶ\000恵山\000渡島大\000利尻\000羊蹄\000ニセコ\000天頂\000雄阿寒\000茂世路\000散布\000指臼\000小田萌\000択捉焼\000択捉阿登佐\000ベルタルベ\000爺爺\000羅臼\000泊山\000ルルイ\000恐山\000岩木\000八甲田\000十和田\000秋田焼\000八幡平\000岩手\000秋田駒ヶ\000鳥海\000栗駒\000鳴子\000蔵王\000吾妻\000安達太良\000磐梯\000燧ヶ\000肘折\000沼沢\000那須\000日光白根\000赤城\000榛名\000草津白根\000浅間\000新潟焼\000妙高\000弥陀ヶ原\000焼岳\000乗鞍\000御嶽\000白山\000富士\000箱根\000伊豆東部火山群\000伊豆大\000新島\000神津\000三宅\000八丈\000青ヶ\000ベヨネース列岩\000須美寿\000伊豆鳥\000西之\000海徳\000噴火浅根\000硫黄\000北福徳堆\000福徳岡ノ場\000高原\000横岳\000アカンダナ\000利島\000御蔵\000孀婦岩\000海形\000南日吉\000日光\000男体\000草津白根山(白根山(湯釜付近)\000草津白根山(本白根山\000三瓶\000九重\000阿蘇\000雲仙\000霧島山\000桜島\000開聞\000薩摩硫黄\000口永良部\000中之\000諏訪之瀬\000阿武火山群\000鶴見岳・伽藍\000由布\000福江火山群\000米丸・住吉池\000若尊\000池田・山川\000口之\000霧島山(御鉢)\000霧島山(新燃岳)\000霧島山(えびの高原(硫黄山)周辺)\000霧島山(大幡池)\000硫黄鳥\000西表島北北東海底\000全国の活\000その他の活\000新たな活\000その他の\000";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_VOLCANO_NAME_PARENT_POOL[] = ")\000山\000岳\000島\000海山\000火山\000";
struct QZSS_DCR_JMA_VOLCANO_NAME_PARENT_Entry { uint16_t offset; uint8_t len; };
static const QZSS_DCR_JMA_VOLCANO_NAME_PARENT_Entry QZSS_DCR_JMA_VOLCANO_NAME_PARENT_TABLE[] AZARAC_PROGMEM = {
    {0u, 1u},
    {2u, 3u},
    {6u, 3u},
    {10u, 3u},
    {14u, 6u},
    {21u, 6u},
};
struct QZSS_DCR_JMA_VOLCANO_NAME_Entry { uint16_t id; uint8_t parent; uint16_t offset; uint8_t len; };
static const QZSS_DCR_JMA_VOLCANO_NAME_Entry QZSS_DCR_JMA_VOLCANO_NAME_TABLE[] AZARAC_PROGMEM = {
    {101u, 1u, 0u, 12u},
    {102u, 2u, 13u, 6u},
    {103u, 255u, 20u, 6u},
    {104u, 255u, 27u, 18u},
    {105u, 2u, 46u, 9u},
    {106u, 255u, 56u, 6u},
    {107u, 1u, 63u, 6u},
    {108u, 2u, 70u, 6u},
    {109u, 1u, 77u, 6u},
    {110u, 2u, 84u, 6u},
    {111u, 255u, 91u, 9u},
    {112u, 1u, 101u, 6u},
    {113u, 2u, 108u, 15u},
    {114u, 255u, 124u, 6u},
    {115u, 3u, 131u, 9u},
    {116u, 1u, 141u, 6u},
    {117u, 1u, 148u, 6u},
    {118u, 255u, 155u, 9u},
    {119u, 1u, 165u, 6u},
    {120u, 2u, 172u, 9u},
    {151u, 2u, 182u, 9u},
    {152u, 1u, 192u, 6u},
    {153u, 2u, 199u, 6u},
    {154u, 1u, 206u, 9u},
    {155u, 1u, 216u, 9u},
    {156u, 2u, 226u, 15u},
    {157u, 1u, 242u, 15u},
    {158u, 2u, 258u, 6u},
    {159u, 1u, 265u, 6u},
    {160u, 255u, 272u, 6u},
    {161u, 2u, 279u, 9u},
    {201u, 255u, 289u, 6u},
    {202u, 1u, 296u, 6u},
    {203u, 1u, 303u, 9u},
    {204u, 255u, 313u, 9u},
    {205u, 1u, 323u, 9u},
    {206u, 255u, 333u, 9u},
    {207u, 1u, 343u, 6u},
    {208u, 2u, 350u, 12u},
    {209u, 1u, 363u, 6u},
    {210u, 1u, 370u, 6u},
    {211u, 255u, 377u, 6u},
    {212u, 1u, 384u, 6u},
    {213u, 1u, 391u, 6u},
    {214u, 1u, 398u, 12u},
    {215u, 1u, 411u, 6u},
    {216u, 2u, 418u, 6u},
    {217u, 255u, 425u, 6u},
    {218u, 255u, 432u, 6u},
    {301u, 2u, 439u, 6u},
    {302u, 1u, 446u, 12u},
    {303u, 1u, 459u, 6u},
    {304u, 1u, 466u, 6u},
    {305u, 1u, 473u, 12u},
    {306u, 1u, 486u, 6u},
    {307u, 1u, 493u, 9u},
    {308u, 1u, 503u, 6u},
    {309u, 255u, 510u, 12u},
    {310u, 255u, 523u, 6u},
    {311u, 2u, 530u, 6u},
    {312u, 1u, 537u, 6u},
    {313u, 255u, 544u, 6u},
    {314u, 1u, 551u, 6u},
    {315u, 1u, 558u, 6u},
    {316u, 255u, 565u, 21u},
    {317u, 3u, 587u, 9u},
    {318u, 255u, 597u, 6u},
    {319u, 3u, 604u, 6u},
    {320u, 3u, 611u, 6u},
    {321u, 3u, 618u, 6u},
    {322u, 3u, 625u, 6u},
    {323u, 255u, 632u, 21u},
    {324u, 3u, 654u, 9u},
    {325u, 3u, 664u, 9u},
    {326u, 3u, 674u, 6u},
    {327u, 4u, 681u, 6u},
    {328u, 255u, 688u, 12u},
    {329u, 3u, 701u, 6u},
    {330u, 255u, 708u, 12u},
    {331u, 255u, 721u, 15u},
    {333u, 1u, 737u, 6u},
    {334u, 255u, 744u, 6u},
    {335u, 1u, 751u, 15u},
    {336u, 255u, 767u, 6u},
    {337u, 3u, 774u, 6u},
    {338u, 255u, 781u, 9u},
    {339u, 4u, 791u, 6u},
    {340u, 4u, 798u, 9u},
    {341u, 4u, 808u, 6u},
    {342u, 1u, 815u, 6u},
    {350u, 0u, 822u, 39u},
    {351u, 0u, 862u, 28u},
    {401u, 1u, 891u, 6u},
    {502u, 1u, 898u, 6u},
    {503u, 1u, 905u, 6u},
    {504u, 2u, 912u, 6u},
    {505u, 255u, 919u, 9u},
    {506u, 255u, 929u, 6u},
    {507u, 2u, 936u, 6u},
    {508u, 3u, 943u, 12u},
    {509u, 3u, 956u, 12u},
    {510u, 3u, 969u, 6u},
    {511u, 3u, 976u, 12u},
    {512u, 255u, 989u, 15u},
    {513u, 2u, 1005u, 18u},
    {514u, 2u, 1024u, 6u},
    {515u, 255u, 1031u, 15u},
    {516u, 255u, 1047u, 18u},
    {517u, 255u, 1066u, 6u},
    {518u, 255u, 1073u, 15u},
    {519u, 3u, 1089u, 6u},
    {550u, 255u, 1096u, 17u},
    {551u, 255u, 1114u, 20u},
    {552u, 255u, 1135u, 43u},
    {553u, 255u, 1179u, 20u},
    {601u, 3u, 1200u, 9u},
    {602u, 5u, 1210u, 24u},
    {900u, 5u, 1235u, 12u},
    {901u, 5u, 1248u, 15u},
    {902u, 5u, 1264u, 12u},
    {4000u, 5u, 1277u, 12u},
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_volcano_name_lookup(uint16_t id) noexcept {
    uint8_t lo = 0, hi = 121;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        const char* AZARAC_PROGMEM ep = reinterpret_cast<const char*>(&QZSS_DCR_JMA_VOLCANO_NAME_TABLE[mid]);
        uint16_t eid = pgm_read_word(ep + offsetof(QZSS_DCR_JMA_VOLCANO_NAME_Entry, id));
        if (eid == id) {
            uint16_t off = pgm_read_word(ep + offsetof(QZSS_DCR_JMA_VOLCANO_NAME_Entry, offset));
            uint8_t n = pgm_read_byte(ep + offsetof(QZSS_DCR_JMA_VOLCANO_NAME_Entry, len));
            uint8_t pi = pgm_read_byte(ep + offsetof(QZSS_DCR_JMA_VOLCANO_NAME_Entry, parent));
            if (pi == 255u) return azarac_pgm_view(QZSS_DCR_JMA_VOLCANO_NAME_POOL + off, n);
            const char* AZARAC_PROGMEM pp = reinterpret_cast<const char*>(&QZSS_DCR_JMA_VOLCANO_NAME_PARENT_TABLE[pi]);
            uint16_t poff = pgm_read_word(pp + offsetof(QZSS_DCR_JMA_VOLCANO_NAME_PARENT_Entry, offset));
            uint8_t pn = pgm_read_byte(pp + offsetof(QZSS_DCR_JMA_VOLCANO_NAME_PARENT_Entry, len));
            return azarac_pgm_join(QZSS_DCR_JMA_VOLCANO_NAME_POOL + off, n, QZSS_DCR_JMA_VOLCANO_NAME_PARENT_POOL + poff, pn);
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
