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
static const char AZARAC_PROGMEM QZSS_DCR_JMA_VOLCANO_NAME_POOL[] = "知床硫黄山\000羅臼岳\000摩周\000アトサヌプリ\000雌阿寒岳\000丸山\000大雪山\000十勝岳\000樽前山\000恵庭岳\000倶多楽\000有珠山\000北海道駒ヶ岳\000恵山\000渡島大島\000利尻山\000羊蹄山\000ニセコ\000天頂山\000雄阿寒岳\000茂世路岳\000散布山\000指臼岳\000小田萌山\000択捉焼山\000択捉阿登佐岳\000ベルタルベ山\000爺爺岳\000羅臼山\000泊山\000ルルイ岳\000恐山\000岩木山\000八甲田山\000十和田\000秋田焼山\000八幡平\000岩手山\000秋田駒ヶ岳\000鳥\000栗駒山\000鳴子\000蔵王山\000吾妻山\000安達太良山\000磐梯山\000燧ヶ岳\000肘折\000沼沢\000那須岳\000日光白根山\000赤城山\000榛名山\000草津白根山\000浅間山\000新潟焼山\000妙高山\000弥陀ヶ原\000焼岳\000乗鞍岳\000御嶽山\000白山\000富士山\000箱根山\000伊豆東部火山群\000伊豆大島\000新島\000神津島\000三宅島\000八丈島\000青ヶ島\000ベヨネース列岩\000須美寿島\000伊豆鳥島\000西之島\000海徳\000噴火浅根\000硫黄島\000北福徳堆\000福徳岡ノ場\000高原山\000横岳\000アカンダナ山\000利島\000御蔵島\000孀婦岩\000海形\000南日吉\000日光\000男体山\000草津白根山(白根山(湯釜付近))\000草津白根山(本白根山)\000三瓶山\000九重山\000阿蘇山\000雲仙岳\000霧島山\000桜島\000開聞岳\000薩摩硫黄島\000口永良部島\000中之島\000諏訪之瀬島\000阿武火山群\000鶴見岳・伽藍岳\000由布岳\000福江火山群\000米丸・住吉池\000若尊\000池田・山川\000口之島\000霧島山(御鉢)\000霧島山(新燃岳)\000霧島山(えびの高原(硫黄山)周辺)\000霧島山(大幡池)\000硫黄鳥島\000西表島北北東海底\000全国の活\000その他の活\000新たな活\000その他の\000";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_VOLCANO_NAME_PARENT_POOL[] = "海山\000火山\000";
struct QZSS_DCR_JMA_VOLCANO_NAME_PARENT_Entry { uint16_t offset; };
static const QZSS_DCR_JMA_VOLCANO_NAME_PARENT_Entry QZSS_DCR_JMA_VOLCANO_NAME_PARENT_TABLE[] AZARAC_PROGMEM = {
    {0u},
    {7u},
};
struct QZSS_DCR_JMA_VOLCANO_NAME_Entry { uint16_t id; uint8_t parent; uint16_t offset; };
static const QZSS_DCR_JMA_VOLCANO_NAME_Entry QZSS_DCR_JMA_VOLCANO_NAME_TABLE[] AZARAC_PROGMEM = {
    {101u, 255u, 0u},
    {102u, 255u, 16u},
    {103u, 255u, 26u},
    {104u, 255u, 33u},
    {105u, 255u, 52u},
    {106u, 255u, 65u},
    {107u, 255u, 72u},
    {108u, 255u, 82u},
    {109u, 255u, 92u},
    {110u, 255u, 102u},
    {111u, 255u, 112u},
    {112u, 255u, 122u},
    {113u, 255u, 132u},
    {114u, 255u, 151u},
    {115u, 255u, 158u},
    {116u, 255u, 171u},
    {117u, 255u, 181u},
    {118u, 255u, 191u},
    {119u, 255u, 201u},
    {120u, 255u, 211u},
    {151u, 255u, 224u},
    {152u, 255u, 237u},
    {153u, 255u, 247u},
    {154u, 255u, 257u},
    {155u, 255u, 270u},
    {156u, 255u, 283u},
    {157u, 255u, 302u},
    {158u, 255u, 321u},
    {159u, 255u, 331u},
    {160u, 255u, 341u},
    {161u, 255u, 348u},
    {201u, 255u, 361u},
    {202u, 255u, 368u},
    {203u, 255u, 378u},
    {204u, 255u, 391u},
    {205u, 255u, 401u},
    {206u, 255u, 414u},
    {207u, 255u, 424u},
    {208u, 255u, 434u},
    {209u, 0u, 450u},
    {210u, 255u, 454u},
    {211u, 255u, 464u},
    {212u, 255u, 471u},
    {213u, 255u, 481u},
    {214u, 255u, 491u},
    {215u, 255u, 507u},
    {216u, 255u, 517u},
    {217u, 255u, 527u},
    {218u, 255u, 534u},
    {301u, 255u, 541u},
    {302u, 255u, 551u},
    {303u, 255u, 567u},
    {304u, 255u, 577u},
    {305u, 255u, 587u},
    {306u, 255u, 603u},
    {307u, 255u, 613u},
    {308u, 255u, 626u},
    {309u, 255u, 636u},
    {310u, 255u, 649u},
    {311u, 255u, 656u},
    {312u, 255u, 666u},
    {313u, 255u, 676u},
    {314u, 255u, 683u},
    {315u, 255u, 693u},
    {316u, 255u, 703u},
    {317u, 255u, 725u},
    {318u, 255u, 738u},
    {319u, 255u, 745u},
    {320u, 255u, 755u},
    {321u, 255u, 765u},
    {322u, 255u, 775u},
    {323u, 255u, 785u},
    {324u, 255u, 807u},
    {325u, 255u, 820u},
    {326u, 255u, 833u},
    {327u, 0u, 843u},
    {328u, 255u, 850u},
    {329u, 255u, 863u},
    {330u, 255u, 873u},
    {331u, 255u, 886u},
    {333u, 255u, 902u},
    {334u, 255u, 912u},
    {335u, 255u, 919u},
    {336u, 255u, 938u},
    {337u, 255u, 945u},
    {338u, 255u, 955u},
    {339u, 0u, 965u},
    {340u, 0u, 972u},
    {341u, 0u, 982u},
    {342u, 255u, 989u},
    {350u, 255u, 999u},
    {351u, 255u, 1040u},
    {401u, 255u, 1070u},
    {502u, 255u, 1080u},
    {503u, 255u, 1090u},
    {504u, 255u, 1100u},
    {505u, 255u, 1110u},
    {506u, 255u, 1120u},
    {507u, 255u, 1127u},
    {508u, 255u, 1137u},
    {509u, 255u, 1153u},
    {510u, 255u, 1169u},
    {511u, 255u, 1179u},
    {512u, 255u, 1195u},
    {513u, 255u, 1211u},
    {514u, 255u, 1233u},
    {515u, 255u, 1243u},
    {516u, 255u, 1259u},
    {517u, 255u, 1278u},
    {518u, 255u, 1285u},
    {519u, 255u, 1301u},
    {550u, 255u, 1311u},
    {551u, 255u, 1329u},
    {552u, 255u, 1350u},
    {553u, 255u, 1394u},
    {601u, 255u, 1415u},
    {602u, 1u, 1428u},
    {900u, 1u, 1453u},
    {901u, 1u, 1466u},
    {902u, 1u, 1482u},
    {4000u, 1u, 1495u},
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_volcano_name_lookup(uint16_t id) noexcept {
    uint8_t lo = 0, hi = 121;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        azarac_pgm_ptr ep = AZARAC_PGM_PTR(QZSS_DCR_JMA_VOLCANO_NAME_TABLE) + static_cast<size_t>(mid) * sizeof(QZSS_DCR_JMA_VOLCANO_NAME_Entry);
        uint16_t eid = azarac_read_word(ep, offsetof(QZSS_DCR_JMA_VOLCANO_NAME_Entry, id));
        if (eid == id) {
            uint16_t off = azarac_read_word(ep, offsetof(QZSS_DCR_JMA_VOLCANO_NAME_Entry, offset));
            uint8_t pi = azarac_read_byte(ep, offsetof(QZSS_DCR_JMA_VOLCANO_NAME_Entry, parent));
            if (pi == 255u) return azarac_pgm_view_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_VOLCANO_NAME_POOL) + off);
            azarac_pgm_ptr pp = AZARAC_PGM_PTR(QZSS_DCR_JMA_VOLCANO_NAME_PARENT_TABLE) + static_cast<size_t>(pi) * sizeof(QZSS_DCR_JMA_VOLCANO_NAME_PARENT_Entry);
            uint16_t poff = azarac_read_word(pp, offsetof(QZSS_DCR_JMA_VOLCANO_NAME_PARENT_Entry, offset));
            return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_VOLCANO_NAME_POOL) + off, AZARAC_PGM_PTR(QZSS_DCR_JMA_VOLCANO_NAME_PARENT_POOL) + poff);
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
