#pragma once
// AUTO-GENERATED from azarashi 0.17.1 with CI-CD
// Source module : azarashi.definitions.qzss.dcr.tsunami_forecast_region
// Variable      : qzss_dcr_jma_tsunami_forecast_region
// Entries       : 99
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

#if (AZARAC_ENABLE_TSUNAMI) && (AZARAC_LANG_JA)

#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_POOL[] = "北海道太平洋沿岸東部\000北海道太平洋沿岸中部\000北海道太平洋沿岸西部\000北海道日本海沿岸北部\000北海道日本海沿岸南部\000オホーツク\000北海道太平洋沿岸\000北海道\000青森県\000青森県\000陸奥湾\000岩手\000宮城\000秋田\000山形\000福島\000青森\000東北地方\000東北地方\000茨城\000千葉県九十九里・外房\000千葉県内房\000東京湾内湾\000伊豆\000小笠原\000相模湾・三浦半\000新潟県上中下越\000佐渡\000富山\000石川県能登\000石川県加賀\000福井\000静岡\000愛知県外海\000伊勢・三河湾\000三重県南\000千葉\000神奈川\000新潟\000石川\000愛知\000三重\000関東\000伊豆・小笠原\000北陸\000東海\000京都府\000大阪府\000兵庫県北\000兵庫\000淡路島南\000和歌山\000鳥取\000島根県出雲・石見\000隠岐\000岡山\000広島\000徳島\000香川\000愛媛県宇和\000愛媛\000高知\000兵庫\000島根\000愛媛\000近畿四国\000近畿中国\000瀬戸\000山口県\000山口\000福岡\000福岡県\000有明・八代海\000佐賀県北\000長崎県西\000壱岐・対馬\000熊本県天草灘\000大分\000大分県豊後水道\000宮崎\000鹿児島県東\000種子島・屋久島\000奄美群島・トカラ列\000鹿児島県西\000山口\000福岡\000佐賀\000長崎\000熊本\000大分\000鹿児島\000九州地方東\000九州地方西\000薩南\000沖縄本島\000大東島\000宮古島・八重山\000沖縄県\000その他の津波予報区\000";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_PARENT_POOL[] = "内海沿岸\000地方\000太平洋沿岸\000島\000方\000日本海沿岸\000沿岸\000海沿岸\000県\000県瀬戸内海沿岸\000諸島\000部\000";
struct QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_PARENT_Entry { uint16_t offset; uint8_t len; };
static const QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_PARENT_Entry QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_PARENT_TABLE[] AZARAC_PROGMEM = {
    {0u, 12u},
    {13u, 6u},
    {20u, 15u},
    {36u, 3u},
    {40u, 3u},
    {44u, 15u},
    {60u, 6u},
    {67u, 9u},
    {77u, 3u},
    {81u, 21u},
    {103u, 6u},
    {110u, 3u},
};
struct QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_Entry { uint16_t id; uint8_t parent; uint16_t offset; uint8_t len; };
static const QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_Entry QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_TABLE[] AZARAC_PROGMEM = {
    {100u, 255u, 0u, 30u},
    {101u, 255u, 31u, 30u},
    {102u, 255u, 62u, 30u},
    {110u, 255u, 93u, 30u},
    {111u, 255u, 124u, 30u},
    {120u, 7u, 155u, 15u},
    {191u, 255u, 171u, 24u},
    {192u, 5u, 196u, 9u},
    {200u, 5u, 206u, 9u},
    {201u, 2u, 216u, 9u},
    {202u, 255u, 226u, 9u},
    {210u, 8u, 236u, 6u},
    {220u, 8u, 243u, 6u},
    {230u, 8u, 250u, 6u},
    {240u, 8u, 257u, 6u},
    {250u, 8u, 264u, 6u},
    {281u, 8u, 271u, 6u},
    {291u, 2u, 278u, 12u},
    {292u, 5u, 291u, 12u},
    {300u, 8u, 304u, 6u},
    {310u, 255u, 311u, 30u},
    {311u, 255u, 342u, 15u},
    {312u, 255u, 358u, 15u},
    {320u, 10u, 374u, 6u},
    {321u, 10u, 381u, 9u},
    {330u, 3u, 391u, 21u},
    {340u, 255u, 413u, 21u},
    {341u, 255u, 435u, 6u},
    {350u, 8u, 442u, 6u},
    {360u, 255u, 449u, 15u},
    {361u, 255u, 465u, 15u},
    {370u, 8u, 481u, 6u},
    {380u, 8u, 488u, 6u},
    {390u, 255u, 495u, 15u},
    {391u, 255u, 511u, 18u},
    {400u, 11u, 530u, 12u},
    {481u, 8u, 543u, 6u},
    {482u, 8u, 550u, 9u},
    {483u, 8u, 560u, 6u},
    {484u, 8u, 567u, 6u},
    {485u, 8u, 574u, 6u},
    {486u, 8u, 581u, 6u},
    {491u, 1u, 588u, 6u},
    {492u, 10u, 595u, 18u},
    {493u, 1u, 614u, 6u},
    {494u, 1u, 621u, 6u},
    {500u, 255u, 628u, 9u},
    {510u, 255u, 638u, 9u},
    {520u, 11u, 648u, 12u},
    {521u, 9u, 661u, 6u},
    {522u, 11u, 668u, 12u},
    {530u, 8u, 681u, 9u},
    {540u, 8u, 691u, 6u},
    {550u, 255u, 698u, 24u},
    {551u, 255u, 723u, 6u},
    {560u, 8u, 730u, 6u},
    {570u, 8u, 737u, 6u},
    {580u, 8u, 744u, 6u},
    {590u, 8u, 751u, 6u},
    {600u, 7u, 758u, 15u},
    {601u, 9u, 774u, 6u},
    {610u, 8u, 781u, 6u},
    {681u, 8u, 788u, 6u},
    {682u, 8u, 795u, 6u},
    {683u, 8u, 802u, 6u},
    {691u, 2u, 809u, 12u},
    {692u, 5u, 822u, 12u},
    {693u, 0u, 835u, 6u},
    {700u, 5u, 842u, 9u},
    {701u, 9u, 852u, 6u},
    {710u, 9u, 859u, 6u},
    {711u, 5u, 866u, 9u},
    {712u, 255u, 876u, 18u},
    {720u, 11u, 895u, 12u},
    {730u, 4u, 908u, 12u},
    {731u, 255u, 921u, 15u},
    {740u, 6u, 937u, 18u},
    {750u, 9u, 956u, 6u},
    {751u, 6u, 963u, 21u},
    {760u, 8u, 985u, 6u},
    {770u, 11u, 992u, 15u},
    {771u, 1u, 1008u, 21u},
    {772u, 3u, 1030u, 27u},
    {773u, 11u, 1058u, 15u},
    {781u, 8u, 1074u, 6u},
    {782u, 8u, 1081u, 6u},
    {783u, 8u, 1088u, 6u},
    {784u, 8u, 1095u, 6u},
    {785u, 8u, 1102u, 6u},
    {786u, 8u, 1109u, 6u},
    {787u, 8u, 1116u, 9u},
    {791u, 11u, 1126u, 15u},
    {792u, 11u, 1142u, 15u},
    {793u, 10u, 1158u, 6u},
    {800u, 1u, 1165u, 12u},
    {801u, 1u, 1178u, 9u},
    {802u, 1u, 1188u, 21u},
    {891u, 1u, 1210u, 9u},
    {1000u, 255u, 1220u, 27u},
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_tsunami_forecast_region_lookup(uint16_t id) noexcept {
    uint8_t lo = 0, hi = 99;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        const char* AZARAC_PROGMEM ep = reinterpret_cast<const char*>(&QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_TABLE[mid]);
        uint16_t eid = pgm_read_word(ep + offsetof(QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_Entry, id));
        if (eid == id) {
            uint16_t off = pgm_read_word(ep + offsetof(QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_Entry, offset));
            uint8_t n = pgm_read_byte(ep + offsetof(QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_Entry, len));
            uint8_t pi = pgm_read_byte(ep + offsetof(QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_Entry, parent));
            if (pi == 255u) return azarac_pgm_view(QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_POOL + off, n);
            const char* AZARAC_PROGMEM pp = reinterpret_cast<const char*>(&QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_PARENT_TABLE[pi]);
            uint16_t poff = pgm_read_word(pp + offsetof(QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_PARENT_Entry, offset));
            uint8_t pn = pgm_read_byte(pp + offsetof(QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_PARENT_Entry, len));
            return azarac_pgm_join(QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_POOL + off, n, QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_PARENT_POOL + poff, pn);
        }
        if (eid < id) lo = static_cast<uint8_t>(mid + 1); else hi = mid;
    }
    return std::nullopt;
}
#else
struct QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_Entry { uint16_t id; const char* label; };
inline constexpr QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_Entry QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_TABLE[] = {
    {100u, "北海道太平洋沿岸東部"},
    {101u, "北海道太平洋沿岸中部"},
    {102u, "北海道太平洋沿岸西部"},
    {110u, "北海道日本海沿岸北部"},
    {111u, "北海道日本海沿岸南部"},
    {120u, "オホーツク海沿岸"},
    {191u, "北海道太平洋沿岸"},
    {192u, "北海道日本海沿岸"},
    {200u, "青森県日本海沿岸"},
    {201u, "青森県太平洋沿岸"},
    {202u, "陸奥湾"},
    {210u, "岩手県"},
    {220u, "宮城県"},
    {230u, "秋田県"},
    {240u, "山形県"},
    {250u, "福島県"},
    {281u, "青森県"},
    {291u, "東北地方太平洋沿岸"},
    {292u, "東北地方日本海沿岸"},
    {300u, "茨城県"},
    {310u, "千葉県九十九里・外房"},
    {311u, "千葉県内房"},
    {312u, "東京湾内湾"},
    {320u, "伊豆諸島"},
    {321u, "小笠原諸島"},
    {330u, "相模湾・三浦半島"},
    {340u, "新潟県上中下越"},
    {341u, "佐渡"},
    {350u, "富山県"},
    {360u, "石川県能登"},
    {361u, "石川県加賀"},
    {370u, "福井県"},
    {380u, "静岡県"},
    {390u, "愛知県外海"},
    {391u, "伊勢・三河湾"},
    {400u, "三重県南部"},
    {481u, "千葉県"},
    {482u, "神奈川県"},
    {483u, "新潟県"},
    {484u, "石川県"},
    {485u, "愛知県"},
    {486u, "三重県"},
    {491u, "関東地方"},
    {492u, "伊豆・小笠原諸島"},
    {493u, "北陸地方"},
    {494u, "東海地方"},
    {500u, "京都府"},
    {510u, "大阪府"},
    {520u, "兵庫県北部"},
    {521u, "兵庫県瀬戸内海沿岸"},
    {522u, "淡路島南部"},
    {530u, "和歌山県"},
    {540u, "鳥取県"},
    {550u, "島根県出雲・石見"},
    {551u, "隠岐"},
    {560u, "岡山県"},
    {570u, "広島県"},
    {580u, "徳島県"},
    {590u, "香川県"},
    {600u, "愛媛県宇和海沿岸"},
    {601u, "愛媛県瀬戸内海沿岸"},
    {610u, "高知県"},
    {681u, "兵庫県"},
    {682u, "島根県"},
    {683u, "愛媛県"},
    {691u, "近畿四国太平洋沿岸"},
    {692u, "近畿中国日本海沿岸"},
    {693u, "瀬戸内海沿岸"},
    {700u, "山口県日本海沿岸"},
    {701u, "山口県瀬戸内海沿岸"},
    {710u, "福岡県瀬戸内海沿岸"},
    {711u, "福岡県日本海沿岸"},
    {712u, "有明・八代海"},
    {720u, "佐賀県北部"},
    {730u, "長崎県西方"},
    {731u, "壱岐・対馬"},
    {740u, "熊本県天草灘沿岸"},
    {750u, "大分県瀬戸内海沿岸"},
    {751u, "大分県豊後水道沿岸"},
    {760u, "宮崎県"},
    {770u, "鹿児島県東部"},
    {771u, "種子島・屋久島地方"},
    {772u, "奄美群島・トカラ列島"},
    {773u, "鹿児島県西部"},
    {781u, "山口県"},
    {782u, "福岡県"},
    {783u, "佐賀県"},
    {784u, "長崎県"},
    {785u, "熊本県"},
    {786u, "大分県"},
    {787u, "鹿児島県"},
    {791u, "九州地方東部"},
    {792u, "九州地方西部"},
    {793u, "薩南諸島"},
    {800u, "沖縄本島地方"},
    {801u, "大東島地方"},
    {802u, "宮古島・八重山地方"},
    {891u, "沖縄県地方"},
    {1000u, "その他の津波予報区"},};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_tsunami_forecast_region_lookup(uint16_t id) noexcept {
    uint8_t lo = 0, hi = 99;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        if (QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_TABLE[mid].id == id) {
            const char* s = QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_TABLE[mid].label;
            return s ? std::optional<std::string_view>(std::string_view{s}) : std::nullopt;
        }
        if (QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_TABLE[mid].id < id) lo = mid + 1;
        else hi = mid;
    }
    return std::nullopt;
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_tsunami_forecast_region_lookup(uint16_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_tsunami_forecast_region_lookup(uint16_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
