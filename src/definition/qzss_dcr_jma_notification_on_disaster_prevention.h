#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcr_jma_notification_on_disaster_prevention
// Variable      : qzss_dcr_jma_notification_on_disaster_prevention
// Entries       : 55
// Strategy      : binary_search

#include <cstdint>
#include <optional>
#include <string_view>
#include "../azaraC.h"

namespace azaraC {
namespace def {

#if (AZARAC_ENABLE_EEW || AZARAC_ENABLE_HYPOCENTER)

struct QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_Entry { uint16_t id; std::string_view label; };
inline constexpr QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_Entry QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_TABLE[] = {
    {0u, std::string_view{"なし", 6}},

    {101u, std::string_view{"今後若干の海面変動があるかもしれません。", 60}},

    {102u, std::string_view{"今後若干の海面変動があるかもしれませんが、被害の心配はありません。", 99}},

    {103u, std::string_view{"今後もしばらく海面変動が続くと思われます。", 63}},

    {104u, std::string_view{"今後もしばらく海面変動が続くと思われますので、海水浴や磯釣り等を行う際は注意してください。", 135}},

    {105u, std::string_view{"今後もしばらく海面変動が続くと思われますので、磯釣り等を行う際は注意してください。", 123}},

    {107u, std::string_view{"現在、大津波警報・津波警報・津波注意報を発表している沿岸はありません。", 105}},

    {109u, std::string_view{"津波と満潮が重なると、津波はより高くなりますので一層厳重な警戒が必要です。", 111}},

    {110u, std::string_view{"津波と満潮が重なると、津波はより高くなりますので十分な注意が必要です。", 105}},

    {111u, std::string_view{"場所によっては、観測した津波の高さよりさらに大きな津波が到達しているおそれがあります。", 129}},

    {112u, std::string_view{"今後、津波の高さは更に高くなることも考えられます。", 75}},

    {113u, std::string_view{"沖合での観測値をもとに津波が推定されている沿岸では、早いところでは、既に津波が到達していると推定されます。", 159}},

    {114u, std::string_view{"津波による潮位変化が観測されてから最大波が観測されるまでに数時間以上かかることがあります。", 135}},

    {115u, std::string_view{"沖合での観測値であり、沿岸では津波はさらに高くなります。", 84}},

    {121u, std::string_view{"＜大津波警報＞\n大きな津波が襲い甚大な被害が発生します。\n沿岸部や川沿いにいる人はただちに高台や避難ビルなど安全な場所へ避難してください。\n津波は繰り返し襲ってきます。警報が解除されるまで安全な場所から離れないでください。", 330}},

    {122u, std::string_view{"＜津波警報＞\n津波による被害が発生します。\n沿岸部や川沿いにいる人はただちに高台や避難ビルなど安全な場所へ避難してください。\n津波は繰り返し襲ってきます。警報が解除されるまで安全な場所から離れないでください。", 309}},

    {123u, std::string_view{"＜津波注意報＞\n海の中や海岸付近は危険です。\n海の中にいる人はただちに海から上がって、海岸から離れてください。\n潮の流れが速い状態が続きますので、注意報が解除されるまで海に入ったり海岸に近づいたりしないようにしてください。", 330}},

    {124u, std::string_view{"＜津波予報(若干の海面変動)＞\n若干の海面変動が予想されますが、被害の心配はありません。", 127}},

    {131u, std::string_view{"警報が発表された沿岸部や川沿いにいる人はただちに高台や避難ビルなど安全な場所へ避難してください。\n到達予想時刻は、予報区のなかで最も早く津波が到達する時刻です。場所によっては、この時刻よりもかなり遅れて津波が襲ってくることがあります。\n到達予想時刻から津波が最も高くなるまでに数時間以上かかることがありますので、観測された津波の高さにかかわらず、警報が解除されるまで安全な場所から離れないでください。", 598}},

    {132u, std::string_view{"場所によっては津波の高さが「予想される津波の高さ」より高くなる可能性があります。", 120}},

    {141u, std::string_view{"東日本大震災クラスの津波が来襲します。", 57}},

    {142u, std::string_view{"沖合で高い津波を観測したため大津波警報・津波警報に切り替えました。", 99}},

    {143u, std::string_view{"沖合で高い津波を観測したため大津波警報・津波警報を切り替えました。", 99}},

    {144u, std::string_view{"沖合で高い津波を観測したため大津波警報に切り替えました。", 84}},

    {145u, std::string_view{"沖合で高い津波を観測したため大津波警報を切り替えました。", 84}},

    {146u, std::string_view{"沖合で高い津波を観測したため津波警報に切り替えました。", 81}},

    {147u, std::string_view{"沖合で高い津波を観測したため津波警報を切り替えました。", 81}},

    {148u, std::string_view{"沖合で高い津波を観測したため予想される津波の高さを切り替えました。", 99}},

    {149u, std::string_view{"ただちに避難してください。", 39}},

    {150u, std::string_view{"南海トラフ地震臨時情報を発表しています。", 60}},

    {201u, std::string_view{"強い揺れに警戒してください。", 42}},

    {211u, std::string_view{"津波警報等(大津波警報・津波警報あるいは津波注意報)を発表中です。", 95}},

    {212u, std::string_view{"この地震により、日本の沿岸では若干の海面変動があるかもしれませんが、被害の心配はありません。", 138}},

    {213u, std::string_view{"今後もしばらく海面変動が続くと思われますので、海水浴や磯釣り等を行う際は注意してください。", 135}},

    {214u, std::string_view{"今後もしばらく海面変動が続くと思われますので、磯釣り等を行う際は注意してください。", 123}},

    {215u, std::string_view{"この地震による津波の心配はありません。", 57}},

    {216u, std::string_view{"震源が海底の場合、津波が発生するおそれがあります。", 75}},

    {217u, std::string_view{"今後の情報に注意してください。", 45}},

    {221u, std::string_view{"太平洋の広域に津波発生の可能性があります。", 63}},

    {222u, std::string_view{"太平洋で津波発生の可能性があります。", 54}},

    {223u, std::string_view{"北西太平洋で津波発生の可能性があります。", 60}},

    {224u, std::string_view{"インド洋の広域に津波発生の可能性があります。", 66}},

    {225u, std::string_view{"インド洋で津波発生の可能性があります。", 57}},

    {226u, std::string_view{"震源の近傍で津波発生の可能性があります。", 60}},

    {227u, std::string_view{"震源の近傍で小さな津波発生の可能性がありますが、被害をもたらす津波の心配はありません。", 129}},

    {228u, std::string_view{"一般的に、この規模の地震が海域の浅い領域で発生すると、津波が発生することがあります。", 126}},

    {229u, std::string_view{"日本への津波の有無については現在調査中です。", 66}},

    {230u, std::string_view{"この地震による日本への津波の影響はありません。", 69}},

    {241u, std::string_view{"この地震について、緊急地震速報を発表しています。", 72}},

    {242u, std::string_view{"この地震について、緊急地震速報を発表しています。この地震の最大震度は2でした。", 115}},

    {243u, std::string_view{"この地震について、緊急地震速報を発表しています。この地震の最大震度は1でした。", 115}},

    {244u, std::string_view{"この地震について、緊急地震速報を発表しています。この地震で震度1以上は観測されていません。", 133}},

    {245u, std::string_view{"この地震で緊急地震速報を発表しましたが、強い揺れは観測されませんでした。", 108}},

    {256u, std::string_view{"震源要素を訂正します。", 33}},

    {500u, std::string_view{"その他の防災上の留意事項", 36}},
};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_notification_on_disaster_prevention_lookup(uint16_t id) {
    uint8_t lo = 0, hi = 55;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        if (QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_TABLE[mid].id == id) return QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_TABLE[mid].label;
        if (QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_TABLE[mid].id < id) lo = mid + 1;
        else hi = mid;
    }
    return std::nullopt;
}

#else

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_notification_on_disaster_prevention_lookup(uint16_t id) {
    (void)id;
    return std::nullopt;
}

#endif

} // namespace def
} // namespace azaraC
