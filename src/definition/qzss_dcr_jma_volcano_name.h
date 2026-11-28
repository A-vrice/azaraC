#pragma once
// AUTO-GENERATED from azarashi 0.17.1 — do not edit
// Specs: IS-QZSS-DCR-017 / IS-QZSS-DCX-004 Rev.004 / EWSS CAMF Issue 1.2
// azarashi.definitions.qzss.dcr.volcano_name → qzss_dcr_jma_volcano_name: 121 entries, strategy binary_search
// Unknown id returns nullptr — callers MUST null-check.

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

static const char AZARAC_PROGMEM QZSS_DCR_JMA_VOLCANO_NAME_POOL[] = "知床硫黄山\000羅臼岳\000摩周\000アトサヌプリ\000雌阿寒岳\000丸山\000大雪山\000十勝岳\000樽前山\000恵庭岳\000倶多楽\000有珠山\000北海道駒ヶ岳\000恵山\000渡島大島\000利尻山\000羊蹄山\000ニセコ\000天頂山\000雄阿寒岳\000茂世路岳\000散布山\000指臼岳\000小田萌山\000択捉焼山\000択捉阿登佐岳\000ベルタルベ山\000爺爺岳\000羅臼山\000泊山\000ルルイ岳\000恐山\000岩木山\000八甲田山\000十和田\000秋田焼山\000八幡平\000岩手山\000秋田駒ヶ岳\000鳥海山\000栗駒山\000鳴子\000蔵王山\000吾妻山\000安達太良山\000磐梯山\000燧ヶ岳\000肘折\000沼沢\000那須岳\000日光白根山\000赤城山\000榛名山\000草津白根山\000浅間山\000新潟焼山\000妙高山\000弥陀ヶ原\000焼岳\000乗鞍岳\000御嶽山\000白山\000富士山\000箱根山\000伊豆東部火山群\000伊豆大島\000新島\000神津島\000三宅島\000八丈島\000青ヶ島\000ベヨネース列岩\000須美寿島\000伊豆鳥島\000西之島\000海徳海山\000噴火浅根\000硫黄島\000北福徳堆\000福徳岡ノ場\000高原山\000横岳\000アカンダナ山\000利島\000御蔵島\000孀婦岩\000海形海山\000南日吉海山\000日光海山\000男体山\000草津白根山(白根山(湯釜付近))\000草津白根山(本白根山)\000三瓶山\000九重山\000阿蘇山\000雲仙岳\000霧島山\000桜島\000開聞岳\000薩摩硫黄島\000口永良部島\000中之島\000諏訪之瀬島\000阿武火山群\000鶴見岳・伽藍岳\000由布岳\000福江火山群\000米丸・住吉池\000若尊\000池田・山川\000口之島\000霧島山(御鉢)\000霧島山(新燃岳)\000霧島山(えびの高原(硫黄山)周辺)\000霧島山(大幡池)\000硫黄鳥島\000西表島北北東海底火山\000全国の活火山\000その他の活火山\000新たな活火山\000その他の火山\000";
struct QZSS_DCR_JMA_VOLCANO_NAME_Entry { uint16_t id; uint16_t offset; };
static const QZSS_DCR_JMA_VOLCANO_NAME_Entry QZSS_DCR_JMA_VOLCANO_NAME_TABLE[] AZARAC_PROGMEM = {
    {101u, 0u},
    {102u, 16u},
    {103u, 26u},
    {104u, 33u},
    {105u, 52u},
    {106u, 65u},
    {107u, 72u},
    {108u, 82u},
    {109u, 92u},
    {110u, 102u},
    {111u, 112u},
    {112u, 122u},
    {113u, 132u},
    {114u, 151u},
    {115u, 158u},
    {116u, 171u},
    {117u, 181u},
    {118u, 191u},
    {119u, 201u},
    {120u, 211u},
    {151u, 224u},
    {152u, 237u},
    {153u, 247u},
    {154u, 257u},
    {155u, 270u},
    {156u, 283u},
    {157u, 302u},
    {158u, 321u},
    {159u, 331u},
    {160u, 341u},
    {161u, 348u},
    {201u, 361u},
    {202u, 368u},
    {203u, 378u},
    {204u, 391u},
    {205u, 401u},
    {206u, 414u},
    {207u, 424u},
    {208u, 434u},
    {209u, 450u},
    {210u, 460u},
    {211u, 470u},
    {212u, 477u},
    {213u, 487u},
    {214u, 497u},
    {215u, 513u},
    {216u, 523u},
    {217u, 533u},
    {218u, 540u},
    {301u, 547u},
    {302u, 557u},
    {303u, 573u},
    {304u, 583u},
    {305u, 593u},
    {306u, 609u},
    {307u, 619u},
    {308u, 632u},
    {309u, 642u},
    {310u, 655u},
    {311u, 662u},
    {312u, 672u},
    {313u, 682u},
    {314u, 689u},
    {315u, 699u},
    {316u, 709u},
    {317u, 731u},
    {318u, 744u},
    {319u, 751u},
    {320u, 761u},
    {321u, 771u},
    {322u, 781u},
    {323u, 791u},
    {324u, 813u},
    {325u, 826u},
    {326u, 839u},
    {327u, 849u},
    {328u, 862u},
    {329u, 875u},
    {330u, 885u},
    {331u, 898u},
    {333u, 914u},
    {334u, 924u},
    {335u, 931u},
    {336u, 950u},
    {337u, 957u},
    {338u, 967u},
    {339u, 977u},
    {340u, 990u},
    {341u, 1006u},
    {342u, 1019u},
    {350u, 1029u},
    {351u, 1070u},
    {401u, 1100u},
    {502u, 1110u},
    {503u, 1120u},
    {504u, 1130u},
    {505u, 1140u},
    {506u, 1150u},
    {507u, 1157u},
    {508u, 1167u},
    {509u, 1183u},
    {510u, 1199u},
    {511u, 1209u},
    {512u, 1225u},
    {513u, 1241u},
    {514u, 1263u},
    {515u, 1273u},
    {516u, 1289u},
    {517u, 1308u},
    {518u, 1315u},
    {519u, 1331u},
    {550u, 1341u},
    {551u, 1359u},
    {552u, 1380u},
    {553u, 1424u},
    {601u, 1445u},
    {602u, 1458u},
    {900u, 1489u},
    {901u, 1508u},
    {902u, 1530u},
    {4000u, 1549u},
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_volcano_name_lookup(uint16_t id) noexcept {
    uint8_t lo = 0, hi = 121;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        azarac_pgm_ptr ep = AZARAC_PGM_PTR(QZSS_DCR_JMA_VOLCANO_NAME_TABLE) + static_cast<size_t>(mid) * sizeof(QZSS_DCR_JMA_VOLCANO_NAME_Entry);
        uint16_t eid = azarac_read_word(ep, offsetof(QZSS_DCR_JMA_VOLCANO_NAME_Entry, id));
        if (eid == id) {
            uint16_t off = azarac_read_word(ep, offsetof(QZSS_DCR_JMA_VOLCANO_NAME_Entry, offset));
            return azarac_pgm_view_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_VOLCANO_NAME_POOL) + off);
        }
        if (eid < id) lo = static_cast<uint8_t>(mid + 1); else hi = mid;
    }
    return std::nullopt;
}

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
