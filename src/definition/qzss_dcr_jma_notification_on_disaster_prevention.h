#pragma once
// AUTO-GENERATED from azarashi 0.17.1 with CI-CD
// Source module : azarashi.definitions.qzss.dcr.notification_on_disaster_prevention
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

#if (AZARAC_ENABLE_EEW || AZARAC_ENABLE_HYPOCENTER) && (AZARAC_LANG_JA)

#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_POOL[] = "なし\000今後若干の海面変動があるかもしれ\000今後若干の海面変動があるかもしれませんが、被害の心配はあり\000今後もしばらく海面変動が続くと思われ\000今後もしばらく海面変動が続くと思われますので、海水浴や磯釣り等を行う際は注意\000今後もしばらく海面変動が続くと思われますので、磯釣り等を行う際は注意\000現在、大津波警報・津波警報・津波注意報を発表している沿岸はあり\000津波と満潮が重なると、津波はより高くなりますので一層厳重な警戒が必要で\000津波と満潮が重なると、津波はより高くなりますので十分な注意が必要で\000場所によっては、観測した津波の高さよりさらに大きな津波が到達しているおそれ\000今後、津波の高さは更に高くなることも考えられ\000沖合での観測値をもとに津波が推定されている沿岸では、早いところでは、既に津波が到達していると推定され\000津波による潮位変化が観測されてから最大波が観測されるまでに数時間以上かかること\000沖合での観測値であり、沿岸では津波はさらに高くな\000＜大津波警報＞\n大きな津波が襲い甚大な被害が発生します。\n沿岸部や川沿いにいる人はただちに高台や避難ビルなど安全な場所へ避難してください。\n津波は繰り返し襲ってきます。警報が解除されるまで安全な場所から離れないで\000＜津波警報＞\n津波による被害が発生します。\n沿岸部や川沿いにいる人はただちに高台や避難ビルなど安全な場所へ避難してください。\n津波は繰り返し襲ってきます。警報が解除されるまで安全な場所から離れないで\000＜津波注意報＞\n海の中や海岸付近は危険です。\n海の中にいる人はただちに海から上がって、海岸から離れてください。\n潮の流れが速い状態が続きますので、注意報が解除されるまで海に入ったり海岸に近づいたりしないように\000＜津波予報(若干の海面変動)＞\n若干の海面変動が予想されますが、被害の心配はあり\000警報が発表された沿岸部や川沿いにいる人はただちに高台や避難ビルなど安全な場所へ避難してください。\n到達予想時刻は、予報区のなかで最も早く津波が到達する時刻です。場所によっては、この時刻よりもかなり遅れて津波が襲ってくることがあります。\n到達予想時刻から津波が最も高くなるまでに数時間以上かかることがありますので、観測された津波の高さにかかわらず、警報が解除されるまで安全な場所から離れないで\000場所によっては津波の高さが「予想される津波の高さ」より高くなる可能性\000東日本大震災クラスの津波が来襲し\000沖合で高い津波を観測したため大津波警報・津波警報に切り替えま\000沖合で高い津波を観測したため大津波警報・津波警報を切り替えま\000沖合で高い津波を観測したため大津波警報に切り替えま\000沖合で高い津波を観測したため大津波警報を切り替えま\000沖合で高い津波を観測したため津波警報に切り替えま\000沖合で高い津波を観測したため津波警報を切り替えま\000沖合で高い津波を観測したため予想される津波の高さを切り替えま\000ただちに避難\000南海トラフ地震臨時情報を発表してい\000強い揺れに警戒\000津波警報等(大津波警報・津波警報あるいは津波注意報)を発表中で\000この地震により、日本の沿岸では若干の海面変動があるかもしれませんが、被害の心配はあり\000今後もしばらく海面変動が続くと思われますので、海水浴や磯釣り等を行う際は注意\000今後もしばらく海面変動が続くと思われますので、磯釣り等を行う際は注意\000この地震による津波の心配はあり\000震源が海底の場合、津波が発生するおそれ\000今後の情報に注意\000太平洋の広域に津波発生の可能性\000太平洋で津波発生の可能性\000北西太平洋で津波発生の可能性\000インド洋の広域に津波発生の可能性\000インド洋で津波発生の可能性\000震源の近傍で津波発生の可能性\000震源の近傍で小さな津波発生の可能性がありますが、被害をもたらす津波の心配はあり\000一般的に、この規模の地震が海域の浅い領域で発生すると、津波が発生すること\000日本への津波の有無については現在調査中で\000この地震による日本への津波の影響はあり\000この地震について、緊急地震速報を発表しています。\000この地震について、緊急地震速報を発表しています。この地震の最大震度は2でした。\000この地震について、緊急地震速報を発表しています。この地震の最大震度は1でした。\000この地震について、緊急地震速報を発表しています。この地震で震度1以上は観測されてい\000この地震で緊急地震速報を発表しましたが、強い揺れは観測されませんでした。\000震源要素を訂正し\000その他の防災上の留意事項\000";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_PARENT_POOL[] = "があります。\000ください。\000した。\000してください。\000す。\000ます。\000ません。\000ります。\000";
struct QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_PARENT_Entry { uint16_t offset; uint8_t len; };
static const QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_PARENT_Entry QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_PARENT_TABLE[] AZARAC_PROGMEM = {
    {0u, 18u},
    {19u, 15u},
    {35u, 9u},
    {45u, 21u},
    {67u, 6u},
    {74u, 9u},
    {84u, 12u},
    {97u, 12u},
};
struct QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_Entry { uint16_t id; uint8_t parent; uint16_t offset; uint16_t len; };
static const QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_Entry QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_TABLE[] AZARAC_PROGMEM = {
    {0u, 255u, 0u, 6u},
    {101u, 6u, 7u, 48u},
    {102u, 6u, 56u, 87u},
    {103u, 5u, 144u, 54u},
    {104u, 3u, 199u, 114u},
    {105u, 3u, 314u, 102u},
    {107u, 6u, 417u, 93u},
    {109u, 4u, 511u, 105u},
    {110u, 4u, 617u, 99u},
    {111u, 0u, 717u, 111u},
    {112u, 5u, 829u, 66u},
    {113u, 5u, 896u, 150u},
    {114u, 0u, 1047u, 117u},
    {115u, 7u, 1165u, 72u},
    {121u, 1u, 1238u, 312u},
    {122u, 1u, 1551u, 291u},
    {123u, 3u, 1843u, 306u},
    {124u, 6u, 2150u, 114u},
    {131u, 1u, 2265u, 581u},
    {132u, 0u, 2847u, 102u},
    {141u, 5u, 2950u, 48u},
    {142u, 2u, 2999u, 90u},
    {143u, 2u, 3090u, 90u},
    {144u, 2u, 3181u, 75u},
    {145u, 2u, 3257u, 75u},
    {146u, 2u, 3333u, 72u},
    {147u, 2u, 3406u, 72u},
    {148u, 2u, 3479u, 90u},
    {149u, 3u, 3570u, 18u},
    {150u, 5u, 3589u, 51u},
    {201u, 3u, 3641u, 21u},
    {211u, 4u, 3663u, 89u},
    {212u, 6u, 3753u, 126u},
    {213u, 3u, 3880u, 114u},
    {214u, 3u, 3995u, 102u},
    {215u, 6u, 4098u, 45u},
    {216u, 0u, 4144u, 57u},
    {217u, 3u, 4202u, 24u},
    {221u, 0u, 4227u, 45u},
    {222u, 0u, 4273u, 36u},
    {223u, 0u, 4310u, 42u},
    {224u, 0u, 4353u, 48u},
    {225u, 0u, 4402u, 39u},
    {226u, 0u, 4442u, 42u},
    {227u, 6u, 4485u, 117u},
    {228u, 0u, 4603u, 108u},
    {229u, 4u, 4712u, 60u},
    {230u, 6u, 4773u, 57u},
    {241u, 255u, 4831u, 72u},
    {242u, 255u, 4904u, 115u},
    {243u, 255u, 5020u, 115u},
    {244u, 6u, 5136u, 121u},
    {245u, 255u, 5258u, 108u},
    {256u, 5u, 5367u, 24u},
    {500u, 255u, 5392u, 36u},
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
            uint8_t pi = pgm_read_byte(ep + offsetof(QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_Entry, parent));
            if (pi == 255u) return azarac_pgm_view(QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_POOL + off, n);
            const char* AZARAC_PROGMEM pp = reinterpret_cast<const char*>(&QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_PARENT_TABLE[pi]);
            uint16_t poff = pgm_read_word(pp + offsetof(QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_PARENT_Entry, offset));
            uint8_t pn = pgm_read_byte(pp + offsetof(QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_PARENT_Entry, len));
            return azarac_pgm_join(QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_POOL + off, n, QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_PARENT_POOL + poff, pn);
        }
        if (eid < id) lo = static_cast<uint8_t>(mid + 1); else hi = mid;
    }
    return std::nullopt;
}
#else
struct QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_Entry { uint16_t id; const char* label; };
inline constexpr QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_Entry QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_TABLE[] = {
    {0u, "なし"},
    {101u, "今後若干の海面変動があるかもしれません。"},
    {102u, "今後若干の海面変動があるかもしれませんが、被害の心配はありません。"},
    {103u, "今後もしばらく海面変動が続くと思われます。"},
    {104u, "今後もしばらく海面変動が続くと思われますので、海水浴や磯釣り等を行う際は注意してください。"},
    {105u, "今後もしばらく海面変動が続くと思われますので、磯釣り等を行う際は注意してください。"},
    {107u, "現在、大津波警報・津波警報・津波注意報を発表している沿岸はありません。"},
    {109u, "津波と満潮が重なると、津波はより高くなりますので一層厳重な警戒が必要です。"},
    {110u, "津波と満潮が重なると、津波はより高くなりますので十分な注意が必要です。"},
    {111u, "場所によっては、観測した津波の高さよりさらに大きな津波が到達しているおそれがあります。"},
    {112u, "今後、津波の高さは更に高くなることも考えられます。"},
    {113u, "沖合での観測値をもとに津波が推定されている沿岸では、早いところでは、既に津波が到達していると推定されます。"},
    {114u, "津波による潮位変化が観測されてから最大波が観測されるまでに数時間以上かかることがあります。"},
    {115u, "沖合での観測値であり、沿岸では津波はさらに高くなります。"},
    {121u, "＜大津波警報＞\n大きな津波が襲い甚大な被害が発生します。\n沿岸部や川沿いにいる人はただちに高台や避難ビルなど安全な場所へ避難してください。\n津波は繰り返し襲ってきます。警報が解除されるまで安全な場所から離れないでください。"},
    {122u, "＜津波警報＞\n津波による被害が発生します。\n沿岸部や川沿いにいる人はただちに高台や避難ビルなど安全な場所へ避難してください。\n津波は繰り返し襲ってきます。警報が解除されるまで安全な場所から離れないでください。"},
    {123u, "＜津波注意報＞\n海の中や海岸付近は危険です。\n海の中にいる人はただちに海から上がって、海岸から離れてください。\n潮の流れが速い状態が続きますので、注意報が解除されるまで海に入ったり海岸に近づいたりしないようにしてください。"},
    {124u, "＜津波予報(若干の海面変動)＞\n若干の海面変動が予想されますが、被害の心配はありません。"},
    {131u, "警報が発表された沿岸部や川沿いにいる人はただちに高台や避難ビルなど安全な場所へ避難してください。\n到達予想時刻は、予報区のなかで最も早く津波が到達する時刻です。場所によっては、この時刻よりもかなり遅れて津波が襲ってくることがあります。\n到達予想時刻から津波が最も高くなるまでに数時間以上かかることがありますので、観測された津波の高さにかかわらず、警報が解除されるまで安全な場所から離れないでください。"},
    {132u, "場所によっては津波の高さが「予想される津波の高さ」より高くなる可能性があります。"},
    {141u, "東日本大震災クラスの津波が来襲します。"},
    {142u, "沖合で高い津波を観測したため大津波警報・津波警報に切り替えました。"},
    {143u, "沖合で高い津波を観測したため大津波警報・津波警報を切り替えました。"},
    {144u, "沖合で高い津波を観測したため大津波警報に切り替えました。"},
    {145u, "沖合で高い津波を観測したため大津波警報を切り替えました。"},
    {146u, "沖合で高い津波を観測したため津波警報に切り替えました。"},
    {147u, "沖合で高い津波を観測したため津波警報を切り替えました。"},
    {148u, "沖合で高い津波を観測したため予想される津波の高さを切り替えました。"},
    {149u, "ただちに避難してください。"},
    {150u, "南海トラフ地震臨時情報を発表しています。"},
    {201u, "強い揺れに警戒してください。"},
    {211u, "津波警報等(大津波警報・津波警報あるいは津波注意報)を発表中です。"},
    {212u, "この地震により、日本の沿岸では若干の海面変動があるかもしれませんが、被害の心配はありません。"},
    {213u, "今後もしばらく海面変動が続くと思われますので、海水浴や磯釣り等を行う際は注意してください。"},
    {214u, "今後もしばらく海面変動が続くと思われますので、磯釣り等を行う際は注意してください。"},
    {215u, "この地震による津波の心配はありません。"},
    {216u, "震源が海底の場合、津波が発生するおそれがあります。"},
    {217u, "今後の情報に注意してください。"},
    {221u, "太平洋の広域に津波発生の可能性があります。"},
    {222u, "太平洋で津波発生の可能性があります。"},
    {223u, "北西太平洋で津波発生の可能性があります。"},
    {224u, "インド洋の広域に津波発生の可能性があります。"},
    {225u, "インド洋で津波発生の可能性があります。"},
    {226u, "震源の近傍で津波発生の可能性があります。"},
    {227u, "震源の近傍で小さな津波発生の可能性がありますが、被害をもたらす津波の心配はありません。"},
    {228u, "一般的に、この規模の地震が海域の浅い領域で発生すると、津波が発生することがあります。"},
    {229u, "日本への津波の有無については現在調査中です。"},
    {230u, "この地震による日本への津波の影響はありません。"},
    {241u, "この地震について、緊急地震速報を発表しています。"},
    {242u, "この地震について、緊急地震速報を発表しています。この地震の最大震度は2でした。"},
    {243u, "この地震について、緊急地震速報を発表しています。この地震の最大震度は1でした。"},
    {244u, "この地震について、緊急地震速報を発表しています。この地震で震度1以上は観測されていません。"},
    {245u, "この地震で緊急地震速報を発表しましたが、強い揺れは観測されませんでした。"},
    {256u, "震源要素を訂正します。"},
    {500u, "その他の防災上の留意事項"},};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_notification_on_disaster_prevention_lookup(uint16_t id) noexcept {
    uint8_t lo = 0, hi = 55;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        if (QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_TABLE[mid].id == id) {
            const char* s = QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_TABLE[mid].label;
            return s ? std::optional<std::string_view>(std::string_view{s}) : std::nullopt;
        }
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
