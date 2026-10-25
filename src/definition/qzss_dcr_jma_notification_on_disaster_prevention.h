#pragma once
// AUTO-GENERATED from azarashi 0.17.1 — do not edit
// azarashi.definitions.qzss.dcr.notification_on_disaster_prevention → qzss_dcr_jma_notification_on_disaster_prevention: 55 entries, strategy binary_search
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

#if (AZARAC_ENABLE_EEW || AZARAC_ENABLE_HYPOCENTER) && (AZARAC_LANG_JA)

static const char AZARAC_PROGMEM QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_POOL[] = "なし\000今後若干の海面変動があるかもしれ\000今後若干の海面変動があるかもしれませんが、被害の心配はあり\000今後もしばらく海面変動が続くと思われ\000今後もしばらく海面変動が続くと思われますので、海水浴や磯釣り等を行う際は注意\000今後もしばらく海面変動が続くと思われますので、磯釣り等を行う際は注意\000現在、大津波警報・津波警報・津波注意報を発表している沿岸はあり\000津波と満潮が重なると、津波はより高くなりますので一層厳重な警戒が必要で\000津波と満潮が重なると、津波はより高くなりますので十分な注意が必要で\000場所によっては、観測した津波の高さよりさらに大きな津波が到達しているおそれ\000今後、津波の高さは更に高くなることも考えられ\000沖合での観測値をもとに津波が推定されている沿岸では、早いところでは、既に津波が到達していると推定され\000津波による潮位変化が観測されてから最大波が観測されるまでに数時間以上かかること\000沖合での観測値であり、沿岸では津波はさらに高くな\000＜大津波警報＞\n大きな津波が襲い甚大な被害が発生します。\n沿岸部や川沿いにいる人はただちに高台や避難ビルなど安全な場所へ避難してください。\n津波は繰り返し襲ってきます。警報が解除されるまで安全な場所から離れないで\000＜津波警報＞\n津波による被害が発生します。\n沿岸部や川沿いにいる人はただちに高台や避難ビルなど安全な場所へ避難してください。\n津波は繰り返し襲ってきます。警報が解除されるまで安全な場所から離れないで\000＜津波注意報＞\n海の中や海岸付近は危険です。\n海の中にいる人はただちに海から上がって、海岸から離れてください。\n潮の流れが速い状態が続きますので、注意報が解除されるまで海に入ったり海岸に近づいたりしないように\000＜津波予報(若干の海面変動)＞\n若干の海面変動が予想されますが、被害の心配はあり\000警報が発表された沿岸部や川沿いにいる人はただちに高台や避難ビルなど安全な場所へ避難してください。\n到達予想時刻は、予報区のなかで最も早く津波が到達する時刻です。場所によっては、この時刻よりもかなり遅れて津波が襲ってくることがあります。\n到達予想時刻から津波が最も高くなるまでに数時間以上かかることがありますので、観測された津波の高さにかかわらず、警報が解除されるまで安全な場所から離れないで\000場所によっては津波の高さが「予想される津波の高さ」より高くなる可能性\000東日本大震災クラスの津波が来襲し\000沖合で高い津波を観測したため大津波警報・津波警報に切り替えま\000沖合で高い津波を観測したため大津波警報・津波警報を切り替えま\000沖合で高い津波を観測したため大津波警報に切り替えま\000沖合で高い津波を観測したため大津波警報を切り替えま\000沖合で高い津波を観測したため津波警報に切り替えま\000沖合で高い津波を観測したため津波警報を切り替えま\000沖合で高い津波を観測したため予想される津波の高さを切り替えま\000ただちに避難\000南海トラフ地震臨時情報を発表してい\000強い揺れに警戒\000津波警報等(大津波警報・津波警報あるいは津波注意報)を発表中で\000この地震により、日本の沿岸では若干の海面変動があるかもしれませんが、被害の心配はあり\000今後もしばらく海面変動が続くと思われますので、海水浴や磯釣り等を行う際は注意\000今後もしばらく海面変動が続くと思われますので、磯釣り等を行う際は注意\000この地震による津波の心配はあり\000震源が海底の場合、津波が発生するおそれ\000今後の情報に注意\000太平洋の広域に津波発生の可能性\000太平洋で津波発生の可能性\000北西太平洋で津波発生の可能性\000インド洋の広域に津波発生の可能性\000インド洋で津波発生の可能性\000震源の近傍で津波発生の可能性\000震源の近傍で小さな津波発生の可能性がありますが、被害をもたらす津波の心配はあり\000一般的に、この規模の地震が海域の浅い領域で発生すると、津波が発生すること\000日本への津波の有無については現在調査中で\000この地震による日本への津波の影響はあり\000この地震について、緊急地震速報を発表しています。\000この地震について、緊急地震速報を発表しています。この地震の最大震度は2でした。\000この地震について、緊急地震速報を発表しています。この地震の最大震度は1でした。\000この地震について、緊急地震速報を発表しています。この地震で震度1以上は観測されてい\000この地震で緊急地震速報を発表しましたが、強い揺れは観測されませんでした。\000震源要素を訂正し\000その他の防災上の留意事項\000";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_PARENT_POOL[] = "があります。\000ください。\000した。\000してください。\000す。\000ます。\000ません。\000ります。\000";
struct QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_PARENT_Entry { uint16_t offset; };
static const QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_PARENT_Entry QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_PARENT_TABLE[] AZARAC_PROGMEM = {
    {0u},
    {19u},
    {35u},
    {45u},
    {67u},
    {74u},
    {84u},
    {97u},
};
struct QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_Entry { uint16_t id; uint8_t parent; uint16_t offset; };
static const QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_Entry QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_TABLE[] AZARAC_PROGMEM = {
    {0u, 255u, 0u},
    {101u, 6u, 7u},
    {102u, 6u, 56u},
    {103u, 5u, 144u},
    {104u, 3u, 199u},
    {105u, 3u, 314u},
    {107u, 6u, 417u},
    {109u, 4u, 511u},
    {110u, 4u, 617u},
    {111u, 0u, 717u},
    {112u, 5u, 829u},
    {113u, 5u, 896u},
    {114u, 0u, 1047u},
    {115u, 7u, 1165u},
    {121u, 1u, 1238u},
    {122u, 1u, 1551u},
    {123u, 3u, 1843u},
    {124u, 6u, 2150u},
    {131u, 1u, 2265u},
    {132u, 0u, 2847u},
    {141u, 5u, 2950u},
    {142u, 2u, 2999u},
    {143u, 2u, 3090u},
    {144u, 2u, 3181u},
    {145u, 2u, 3257u},
    {146u, 2u, 3333u},
    {147u, 2u, 3406u},
    {148u, 2u, 3479u},
    {149u, 3u, 3570u},
    {150u, 5u, 3589u},
    {201u, 3u, 3641u},
    {211u, 4u, 3663u},
    {212u, 6u, 3753u},
    {213u, 3u, 3880u},
    {214u, 3u, 3995u},
    {215u, 6u, 4098u},
    {216u, 0u, 4144u},
    {217u, 3u, 4202u},
    {221u, 0u, 4227u},
    {222u, 0u, 4273u},
    {223u, 0u, 4310u},
    {224u, 0u, 4353u},
    {225u, 0u, 4402u},
    {226u, 0u, 4442u},
    {227u, 6u, 4485u},
    {228u, 0u, 4603u},
    {229u, 4u, 4712u},
    {230u, 6u, 4773u},
    {241u, 255u, 4831u},
    {242u, 255u, 4904u},
    {243u, 255u, 5020u},
    {244u, 6u, 5136u},
    {245u, 255u, 5258u},
    {256u, 5u, 5367u},
    {500u, 255u, 5392u},
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_notification_on_disaster_prevention_lookup(uint16_t id) noexcept {
    uint8_t lo = 0, hi = 55;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        azarac_pgm_ptr ep = AZARAC_PGM_PTR(QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_TABLE) + static_cast<size_t>(mid) * sizeof(QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_Entry);
        uint16_t eid = azarac_read_word(ep, offsetof(QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_Entry, id));
        if (eid == id) {
            uint16_t off = azarac_read_word(ep, offsetof(QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_Entry, offset));
            uint8_t pi = azarac_read_byte(ep, offsetof(QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_Entry, parent));
            if (pi == 255u) return azarac_pgm_view_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_POOL) + off);
            azarac_pgm_ptr pp = AZARAC_PGM_PTR(QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_PARENT_TABLE) + static_cast<size_t>(pi) * sizeof(QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_PARENT_Entry);
            uint16_t poff = azarac_read_word(pp, offsetof(QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_PARENT_Entry, offset));
            return azarac_pgm_join_z(AZARAC_PGM_PTR(QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_POOL) + off, AZARAC_PGM_PTR(QZSS_DCR_JMA_NOTIFICATION_ON_DISASTER_PREVENTION_PARENT_POOL) + poff);
        }
        if (eid < id) lo = static_cast<uint8_t>(mid + 1); else hi = mid;
    }
    return std::nullopt;
}

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
