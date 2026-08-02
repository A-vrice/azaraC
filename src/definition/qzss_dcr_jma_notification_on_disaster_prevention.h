#pragma once
// AUTO-GENERATED from azarashi 0.16.4 with CI-CD
// Source module : qzss_dcr_jma_notification_on_disaster_prevention
// Variable      : qzss_dcr_jma_notification_on_disaster_prevention
// Entries       : 55
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

#if (AZARAC_ENABLE_EEW || AZARAC_ENABLE_HYPOCENTER)

#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_POOL[] = "なし\000今後若干の海面変動があるかもしれません。\000今後若干の海面変動があるかもしれませんが、被害の心配はありません。\000今後もしばらく海面変動が続くと思われます。\000今後もしばらく海面変動が続くと思われますので、海水浴や磯釣り等を行う際は注意してください。\000今後もしばらく海面変動が続くと思われますので、磯釣り等を行う際は注意してください。\000現在、大津波警報・津波警報・津波注意報を発表している沿岸はありません。\000津波と満潮が重なると、津波はより高くなりますので一層厳重な警戒が必要です。\000津波と満潮が重なると、津波はより高くなりますので十分な注意が必要です。\000場所によっては、観測した津波の高さよりさらに大きな津波が到達しているおそれがあります。\000今後、津波の高さは更に高くなることも考えられます。\000沖合での観測値をもとに津波が推定されている沿岸では、早いところでは、既に津波が到達していると推定されます。\000津波による潮位変化が観測されてから最大波が観測されるまでに数時間以上かかることがあります。\000沖合での観測値であり、沿岸では津波はさらに高くなります。\000＜大津波警報＞\n大きな津波が襲い甚大な被害が発生します。\n沿岸部や川沿いにいる人はただちに高台や避難ビルなど安全な場所へ避難してください。\n津波は繰り返し襲ってきます。警報が解除されるまで安全な場所から離れないでください。\000＜津波警報＞\n津波による被害が発生します。\n沿岸部や川沿いにいる人はただちに高台や避難ビルなど安全な場所へ避難してください。\n津波は繰り返し襲ってきます。警報が解除されるまで安全な場所から離れないでください。\000＜津波注意報＞\n海の中や海岸付近は危険です。\n海の中にいる人はただちに海から上がって、海岸から離れてください。\n潮の流れが速い状態が続きますので、注意報が解除されるまで海に入ったり海岸に近づいたりしないようにしてください。\000＜津波予報(若干の海面変動)＞\n若干の海面変動が予想されますが、被害の心配はありません。\000警報が発表された沿岸部や川沿いにいる人はただちに高台や避難ビルなど安全な場所へ避難してください。\n到達予想時刻は、予報区のなかで最も早く津波が到達する時刻です。場所によっては、この時刻よりもかなり遅れて津波が襲ってくることがあります。\n到達予想時刻から津波が最も高くなるまでに数時間以上かかることがありますので、観測された津波の高さにかかわらず、警報が解除されるまで安全な場所から離れないでください。\000場所によっては津波の高さが「予想される津波の高さ」より高くなる可能性があります。\000東日本大震災クラスの津波が来襲します。\000沖合で高い津波を観測したため大津波警報・津波警報に切り替えました。\000沖合で高い津波を観測したため大津波警報・津波警報を切り替えました。\000沖合で高い津波を観測したため大津波警報に切り替えました。\000沖合で高い津波を観測したため大津波警報を切り替えました。\000沖合で高い津波を観測したため津波警報に切り替えました。\000沖合で高い津波を観測したため津波警報を切り替えました。\000沖合で高い津波を観測したため予想される津波の高さを切り替えました。\000ただちに避難してください。\000南海トラフ地震臨時情報を発表しています。\000強い揺れに警戒してください。\000津波警報等(大津波警報・津波警報あるいは津波注意報)を発表中です。\000この地震により、日本の沿岸では若干の海面変動があるかもしれませんが、被害の心配はありません。\000今後もしばらく海面変動が続くと思われますので、海水浴や磯釣り等を行う際は注意してください。\000今後もしばらく海面変動が続くと思われますので、磯釣り等を行う際は注意してください。\000この地震による津波の心配はありません。\000震源が海底の場合、津波が発生するおそれがあります。\000今後の情報に注意してください。\000太平洋の広域に津波発生の可能性があります。\000太平洋で津波発生の可能性があります。\000北西太平洋で津波発生の可能性があります。\000インド洋の広域に津波発生の可能性があります。\000インド洋で津波発生の可能性があります。\000震源の近傍で津波発生の可能性があります。\000震源の近傍で小さな津波発生の可能性がありますが、被害をもたらす津波の心配はありません。\000一般的に、この規模の地震が海域の浅い領域で発生すると、津波が発生することがあります。\000日本への津波の有無については現在調査中です。\000この地震による日本への津波の影響はありません。\000この地震について、緊急地震速報を発表しています。\000この地震について、緊急地震速報を発表しています。この地震の最大震度は2でした。\000この地震について、緊急地震速報を発表しています。この地震の最大震度は1でした。\000この地震について、緊急地震速報を発表しています。この地震で震度1以上は観測されていません。\000この地震で緊急地震速報を発表しましたが、強い揺れは観測されませんでした。\000震源要素を訂正します。\000その他の防災上の留意事項\000";
struct QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_Entry { uint16_t id; uint16_t offset; uint16_t len; };
static const QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_Entry QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_TABLE[] AZARAC_PROGMEM = {
    {0u, 0u, 6u},
    {101u, 7u, 60u},
    {102u, 68u, 99u},
    {103u, 168u, 63u},
    {104u, 232u, 135u},
    {105u, 368u, 123u},
    {107u, 492u, 105u},
    {109u, 598u, 111u},
    {110u, 710u, 105u},
    {111u, 816u, 129u},
    {112u, 946u, 75u},
    {113u, 1022u, 159u},
    {114u, 1182u, 135u},
    {115u, 1318u, 84u},
    {121u, 1403u, 327u},
    {122u, 1731u, 306u},
    {123u, 2038u, 327u},
    {124u, 2366u, 126u},
    {131u, 2493u, 596u},
    {132u, 3090u, 120u},
    {141u, 3211u, 57u},
    {142u, 3269u, 99u},
    {143u, 3369u, 99u},
    {144u, 3469u, 84u},
    {145u, 3554u, 84u},
    {146u, 3639u, 81u},
    {147u, 3721u, 81u},
    {148u, 3803u, 99u},
    {149u, 3903u, 39u},
    {150u, 3943u, 60u},
    {201u, 4004u, 42u},
    {211u, 4047u, 95u},
    {212u, 4143u, 138u},
    {213u, 4282u, 135u},
    {214u, 4418u, 123u},
    {215u, 4542u, 57u},
    {216u, 4600u, 75u},
    {217u, 4676u, 45u},
    {221u, 4722u, 63u},
    {222u, 4786u, 54u},
    {223u, 4841u, 60u},
    {224u, 4902u, 66u},
    {225u, 4969u, 57u},
    {226u, 5027u, 60u},
    {227u, 5088u, 129u},
    {228u, 5218u, 126u},
    {229u, 5345u, 66u},
    {230u, 5412u, 69u},
    {241u, 5482u, 72u},
    {242u, 5555u, 115u},
    {243u, 5671u, 115u},
    {244u, 5787u, 133u},
    {245u, 5921u, 108u},
    {256u, 6030u, 33u},
    {500u, 6064u, 36u},
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_notification_on_disaster_prevention_lookup(uint16_t id) noexcept {
    uint8_t lo = 0, hi = 55;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        const char* AZARAC_PROGMEM ep = reinterpret_cast<const char*>(&QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_TABLE[mid]);
        uint16_t eid = pgm_read_word(ep + offsetof(QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_Entry, id));
        if (eid == id) {
            uint16_t off = pgm_read_word(ep + offsetof(QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_Entry, offset));
            uint16_t n = pgm_read_word(ep + offsetof(QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_Entry, len));
            if (n == 0) return std::nullopt;
            return azarac_pgm_view(QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_POOL + off, n);
        }
        if (eid < id) lo = static_cast<uint8_t>(mid + 1); else hi = mid;
    }
    return std::nullopt;
}
#else
struct QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_Entry { uint16_t id; std::optional<std::string_view> label; };
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
    {121u, std::string_view{"＜大津波警報＞\n大きな津波が襲い甚大な被害が発生します。\n沿岸部や川沿いにいる人はただちに高台や避難ビルなど安全な場所へ避難してください。\n津波は繰り返し襲ってきます。警報が解除されるまで安全な場所から離れないでください。", 327}},
    {122u, std::string_view{"＜津波警報＞\n津波による被害が発生します。\n沿岸部や川沿いにいる人はただちに高台や避難ビルなど安全な場所へ避難してください。\n津波は繰り返し襲ってきます。警報が解除されるまで安全な場所から離れないでください。", 306}},
    {123u, std::string_view{"＜津波注意報＞\n海の中や海岸付近は危険です。\n海の中にいる人はただちに海から上がって、海岸から離れてください。\n潮の流れが速い状態が続きますので、注意報が解除されるまで海に入ったり海岸に近づいたりしないようにしてください。", 327}},
    {124u, std::string_view{"＜津波予報(若干の海面変動)＞\n若干の海面変動が予想されますが、被害の心配はありません。", 126}},
    {131u, std::string_view{"警報が発表された沿岸部や川沿いにいる人はただちに高台や避難ビルなど安全な場所へ避難してください。\n到達予想時刻は、予報区のなかで最も早く津波が到達する時刻です。場所によっては、この時刻よりもかなり遅れて津波が襲ってくることがあります。\n到達予想時刻から津波が最も高くなるまでに数時間以上かかることがありますので、観測された津波の高さにかかわらず、警報が解除されるまで安全な場所から離れないでください。", 596}},
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
    {500u, std::string_view{"その他の防災上の留意事項", 36}},};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_notification_on_disaster_prevention_lookup(uint16_t id) noexcept {
    uint8_t lo = 0, hi = 55;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        if (QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_TABLE[mid].id == id) return QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_TABLE[mid].label;
        if (QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_TABLE[mid].id < id) lo = mid + 1;
        else hi = mid;
    }
    return std::nullopt;
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_notification_on_disaster_prevention_lookup(uint16_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_notification_on_disaster_prevention_lookup(uint16_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
