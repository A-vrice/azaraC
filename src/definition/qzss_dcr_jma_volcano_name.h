#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcr_jma_volcano_name
// Variable      : qzss_dcr_jma_volcano_name
// Entries       : 121
// Strategy      : binary_search

// NOTE: This function may return nullptr for unknown IDs.
// Callers MUST perform a null-check before using the result.

#include <cstdint>
#include <optional>
#include <string_view>
#include "../azaraC.h"

namespace azaraC {
namespace def {

#if (AZARAC_ENABLE_VOLCANO)

struct QZSS_DCR_JMA_VOLCANO_NAME_Entry { uint16_t id; std::optional<std::string_view> label; };
inline constexpr QZSS_DCR_JMA_VOLCANO_NAME_Entry QZSS_DCR_JMA_VOLCANO_NAME_TABLE[] = {
    {101u, std::string_view{"知床硫黄山", 5}},
    {102u, std::string_view{"羅臼岳", 3}},
    {103u, std::string_view{"摩周", 2}},
    {104u, std::string_view{"アトサヌプリ", 6}},
    {105u, std::string_view{"雌阿寒岳", 4}},
    {106u, std::string_view{"丸山", 2}},
    {107u, std::string_view{"大雪山", 3}},
    {108u, std::string_view{"十勝岳", 3}},
    {109u, std::string_view{"樽前山", 3}},
    {110u, std::string_view{"恵庭岳", 3}},
    {111u, std::string_view{"倶多楽", 3}},
    {112u, std::string_view{"有珠山", 3}},
    {113u, std::string_view{"北海道駒ヶ岳", 6}},
    {114u, std::string_view{"恵山", 2}},
    {115u, std::string_view{"渡島大島", 4}},
    {116u, std::string_view{"利尻山", 3}},
    {117u, std::string_view{"羊蹄山", 3}},
    {118u, std::string_view{"ニセコ", 3}},
    {119u, std::string_view{"天頂山", 3}},
    {120u, std::string_view{"雄阿寒岳", 4}},
    {151u, std::string_view{"茂世路岳", 4}},
    {152u, std::string_view{"散布山", 3}},
    {153u, std::string_view{"指臼岳", 3}},
    {154u, std::string_view{"小田萌山", 4}},
    {155u, std::string_view{"択捉焼山", 4}},
    {156u, std::string_view{"択捉阿登佐岳", 6}},
    {157u, std::string_view{"ベルタルベ山", 6}},
    {158u, std::string_view{"爺爺岳", 3}},
    {159u, std::string_view{"羅臼山", 3}},
    {160u, std::string_view{"泊山", 2}},
    {161u, std::string_view{"ルルイ岳", 4}},
    {201u, std::string_view{"恐山", 2}},
    {202u, std::string_view{"岩木山", 3}},
    {203u, std::string_view{"八甲田山", 4}},
    {204u, std::string_view{"十和田", 3}},
    {205u, std::string_view{"秋田焼山", 4}},
    {206u, std::string_view{"八幡平", 3}},
    {207u, std::string_view{"岩手山", 3}},
    {208u, std::string_view{"秋田駒ヶ岳", 5}},
    {209u, std::string_view{"鳥海山", 3}},
    {210u, std::string_view{"栗駒山", 3}},
    {211u, std::string_view{"鳴子", 2}},
    {212u, std::string_view{"蔵王山", 3}},
    {213u, std::string_view{"吾妻山", 3}},
    {214u, std::string_view{"安達太良山", 5}},
    {215u, std::string_view{"磐梯山", 3}},
    {216u, std::string_view{"燧ヶ岳", 3}},
    {217u, std::string_view{"肘折", 2}},
    {218u, std::string_view{"沼沢", 2}},
    {301u, std::string_view{"那須岳", 3}},
    {302u, std::string_view{"日光白根山", 5}},
    {303u, std::string_view{"赤城山", 3}},
    {304u, std::string_view{"榛名山", 3}},
    {305u, std::string_view{"草津白根山", 5}},
    {306u, std::string_view{"浅間山", 3}},
    {307u, std::string_view{"新潟焼山", 4}},
    {308u, std::string_view{"妙高山", 3}},
    {309u, std::string_view{"弥陀ヶ原", 4}},
    {310u, std::string_view{"焼岳", 2}},
    {311u, std::string_view{"乗鞍岳", 3}},
    {312u, std::string_view{"御嶽山", 3}},
    {313u, std::string_view{"白山", 2}},
    {314u, std::string_view{"富士山", 3}},
    {315u, std::string_view{"箱根山", 3}},
    {316u, std::string_view{"伊豆東部火山群", 7}},
    {317u, std::string_view{"伊豆大島", 4}},
    {318u, std::string_view{"新島", 2}},
    {319u, std::string_view{"神津島", 3}},
    {320u, std::string_view{"三宅島", 3}},
    {321u, std::string_view{"八丈島", 3}},
    {322u, std::string_view{"青ヶ島", 3}},
    {323u, std::string_view{"ベヨネース列岩", 7}},
    {324u, std::string_view{"須美寿島", 4}},
    {325u, std::string_view{"伊豆鳥島", 4}},
    {326u, std::string_view{"西之島", 3}},
    {327u, std::string_view{"海徳海山", 4}},
    {328u, std::string_view{"噴火浅根", 4}},
    {329u, std::string_view{"硫黄島", 3}},
    {330u, std::string_view{"北福徳堆", 4}},
    {331u, std::string_view{"福徳岡ノ場", 5}},
    {333u, std::string_view{"高原山", 3}},
    {334u, std::string_view{"横岳", 2}},
    {335u, std::string_view{"アカンダナ山", 6}},
    {336u, std::string_view{"利島", 2}},
    {337u, std::string_view{"御蔵島", 3}},
    {338u, std::string_view{"孀婦岩", 3}},
    {339u, std::string_view{"海形海山", 4}},
    {340u, std::string_view{"南日吉海山", 5}},
    {341u, std::string_view{"日光海山", 4}},
    {342u, std::string_view{"男体山", 3}},
    {350u, std::string_view{"草津白根山(白根山(湯釜付近))", 16}},
    {351u, std::string_view{"草津白根山(本白根山)", 11}},
    {401u, std::string_view{"三瓶山", 3}},
    {502u, std::string_view{"九重山", 3}},
    {503u, std::string_view{"阿蘇山", 3}},
    {504u, std::string_view{"雲仙岳", 3}},
    {505u, std::string_view{"霧島山", 3}},
    {506u, std::string_view{"桜島", 2}},
    {507u, std::string_view{"開聞岳", 3}},
    {508u, std::string_view{"薩摩硫黄島", 5}},
    {509u, std::string_view{"口永良部島", 5}},
    {510u, std::string_view{"中之島", 3}},
    {511u, std::string_view{"諏訪之瀬島", 5}},
    {512u, std::string_view{"阿武火山群", 5}},
    {513u, std::string_view{"鶴見岳・伽藍岳", 7}},
    {514u, std::string_view{"由布岳", 3}},
    {515u, std::string_view{"福江火山群", 5}},
    {516u, std::string_view{"米丸・住吉池", 6}},
    {517u, std::string_view{"若尊", 2}},
    {518u, std::string_view{"池田・山川", 5}},
    {519u, std::string_view{"口之島", 3}},
    {550u, std::string_view{"霧島山(御鉢)", 7}},
    {551u, std::string_view{"霧島山(新燃岳)", 8}},
    {552u, std::string_view{"霧島山(えびの高原(硫黄山)周辺)", 17}},
    {553u, std::string_view{"霧島山(大幡池)", 8}},
    {601u, std::string_view{"硫黄鳥島", 4}},
    {602u, std::string_view{"西表島北北東海底火山", 10}},
    {900u, std::string_view{"全国の活火山", 6}},
    {901u, std::string_view{"その他の活火山", 7}},
    {902u, std::string_view{"新たな活火山", 6}},
    {4000u, std::string_view{"その他の火山", 6}},};
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

#else

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_volcano_name_lookup(uint16_t id) noexcept {
    (void)id;
    return std::nullopt;
}

#endif

} // namespace def
} // namespace azaraC
