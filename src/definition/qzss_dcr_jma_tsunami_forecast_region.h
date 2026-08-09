#pragma once
// AUTO-GENERATED from azarashi 0.16.4 with CI-CD
// Source module : qzss_dcr_jma_tsunami_forecast_region
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

#if (AZARAC_ENABLE_TSUNAMI)

#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_POOL[] = "北海道太平洋沿岸東部\000北海道太平洋沿岸中部\000北海道太平洋沿岸西部\000北海道日本海沿岸北部\000北海道日本海沿岸南部\000オホーツク海沿岸\000北海道太平洋沿岸\000北海道日本海沿岸\000青森県日本海沿岸\000青森県太平洋沿岸\000陸奥湾\000岩手県\000宮城県\000秋田県\000山形県\000福島県\000青森県\000東北地方太平洋沿岸\000東北地方日本海沿岸\000茨城県\000千葉県九十九里・外房\000千葉県内房\000東京湾内湾\000伊豆諸島\000小笠原諸島\000相模湾・三浦半島\000新潟県上中下越\000佐渡\000富山県\000石川県能登\000石川県加賀\000福井県\000静岡県\000愛知県外海\000伊勢・三河湾\000三重県南部\000千葉県\000神奈川県\000新潟県\000石川県\000愛知県\000三重県\000関東地方\000伊豆・小笠原諸島\000北陸地方\000東海地方\000京都府\000大阪府\000兵庫県北部\000兵庫県瀬戸内海沿岸\000淡路島南部\000和歌山県\000鳥取県\000島根県出雲・石見\000隠岐\000岡山県\000広島県\000徳島県\000香川県\000愛媛県宇和海沿岸\000愛媛県瀬戸内海沿岸\000高知県\000兵庫県\000島根県\000愛媛県\000近畿四国太平洋沿岸\000近畿中国日本海沿岸\000瀬戸内海沿岸\000山口県日本海沿岸\000山口県瀬戸内海沿岸\000福岡県瀬戸内海沿岸\000福岡県日本海沿岸\000有明・八代海\000佐賀県北部\000長崎県西方\000壱岐・対馬\000熊本県天草灘沿岸\000大分県瀬戸内海沿岸\000大分県豊後水道沿岸\000宮崎県\000鹿児島県東部\000種子島・屋久島地方\000奄美群島・トカラ列島\000鹿児島県西部\000山口県\000福岡県\000佐賀県\000長崎県\000熊本県\000大分県\000鹿児島県\000九州地方東部\000九州地方西部\000薩南諸島\000沖縄本島地方\000大東島地方\000宮古島・八重山地方\000沖縄県地方\000その他の津波予報区\000";
struct QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_Entry { uint16_t id; uint16_t offset; uint16_t len; };
static const QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_Entry QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_TABLE[] AZARAC_PROGMEM = {
    {100u, 0u, 30u},
    {101u, 31u, 30u},
    {102u, 62u, 30u},
    {110u, 93u, 30u},
    {111u, 124u, 30u},
    {120u, 155u, 24u},
    {191u, 180u, 24u},
    {192u, 205u, 24u},
    {200u, 230u, 24u},
    {201u, 255u, 24u},
    {202u, 280u, 9u},
    {210u, 290u, 9u},
    {220u, 300u, 9u},
    {230u, 310u, 9u},
    {240u, 320u, 9u},
    {250u, 330u, 9u},
    {281u, 340u, 9u},
    {291u, 350u, 27u},
    {292u, 378u, 27u},
    {300u, 406u, 9u},
    {310u, 416u, 30u},
    {311u, 447u, 15u},
    {312u, 463u, 15u},
    {320u, 479u, 12u},
    {321u, 492u, 15u},
    {330u, 508u, 24u},
    {340u, 533u, 21u},
    {341u, 555u, 6u},
    {350u, 562u, 9u},
    {360u, 572u, 15u},
    {361u, 588u, 15u},
    {370u, 604u, 9u},
    {380u, 614u, 9u},
    {390u, 624u, 15u},
    {391u, 640u, 18u},
    {400u, 659u, 15u},
    {481u, 675u, 9u},
    {482u, 685u, 12u},
    {483u, 698u, 9u},
    {484u, 708u, 9u},
    {485u, 718u, 9u},
    {486u, 728u, 9u},
    {491u, 738u, 12u},
    {492u, 751u, 24u},
    {493u, 776u, 12u},
    {494u, 789u, 12u},
    {500u, 802u, 9u},
    {510u, 812u, 9u},
    {520u, 822u, 15u},
    {521u, 838u, 27u},
    {522u, 866u, 15u},
    {530u, 882u, 12u},
    {540u, 895u, 9u},
    {550u, 905u, 24u},
    {551u, 930u, 6u},
    {560u, 937u, 9u},
    {570u, 947u, 9u},
    {580u, 957u, 9u},
    {590u, 967u, 9u},
    {600u, 977u, 24u},
    {601u, 1002u, 27u},
    {610u, 1030u, 9u},
    {681u, 1040u, 9u},
    {682u, 1050u, 9u},
    {683u, 1060u, 9u},
    {691u, 1070u, 27u},
    {692u, 1098u, 27u},
    {693u, 1126u, 18u},
    {700u, 1145u, 24u},
    {701u, 1170u, 27u},
    {710u, 1198u, 27u},
    {711u, 1226u, 24u},
    {712u, 1251u, 18u},
    {720u, 1270u, 15u},
    {730u, 1286u, 15u},
    {731u, 1302u, 15u},
    {740u, 1318u, 24u},
    {750u, 1343u, 27u},
    {751u, 1371u, 27u},
    {760u, 1399u, 9u},
    {770u, 1409u, 18u},
    {771u, 1428u, 27u},
    {772u, 1456u, 30u},
    {773u, 1487u, 18u},
    {781u, 1506u, 9u},
    {782u, 1516u, 9u},
    {783u, 1526u, 9u},
    {784u, 1536u, 9u},
    {785u, 1546u, 9u},
    {786u, 1556u, 9u},
    {787u, 1566u, 12u},
    {791u, 1579u, 18u},
    {792u, 1598u, 18u},
    {793u, 1617u, 12u},
    {800u, 1630u, 18u},
    {801u, 1649u, 15u},
    {802u, 1665u, 27u},
    {891u, 1693u, 15u},
    {1000u, 1709u, 27u},
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_tsunami_forecast_region_lookup(uint16_t id) noexcept {
    uint8_t lo = 0, hi = 99;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        const char* AZARAC_PROGMEM ep = reinterpret_cast<const char*>(&QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_TABLE[mid]);
        uint16_t eid = pgm_read_word(ep + offsetof(QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_Entry, id));
        if (eid == id) {
            uint16_t off = pgm_read_word(ep + offsetof(QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_Entry, offset));
            uint16_t n = pgm_read_word(ep + offsetof(QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_Entry, len));
            if (n == 0) return std::nullopt;
            return azarac_pgm_view(QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_POOL + off, n);
        }
        if (eid < id) lo = static_cast<uint8_t>(mid + 1); else hi = mid;
    }
    return std::nullopt;
}
#else
struct QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_Entry { uint16_t id; std::optional<std::string_view> label; };
inline constexpr QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_Entry QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_TABLE[] = {
    {100u, std::string_view{"北海道太平洋沿岸東部", 30}},
    {101u, std::string_view{"北海道太平洋沿岸中部", 30}},
    {102u, std::string_view{"北海道太平洋沿岸西部", 30}},
    {110u, std::string_view{"北海道日本海沿岸北部", 30}},
    {111u, std::string_view{"北海道日本海沿岸南部", 30}},
    {120u, std::string_view{"オホーツク海沿岸", 24}},
    {191u, std::string_view{"北海道太平洋沿岸", 24}},
    {192u, std::string_view{"北海道日本海沿岸", 24}},
    {200u, std::string_view{"青森県日本海沿岸", 24}},
    {201u, std::string_view{"青森県太平洋沿岸", 24}},
    {202u, std::string_view{"陸奥湾", 9}},
    {210u, std::string_view{"岩手県", 9}},
    {220u, std::string_view{"宮城県", 9}},
    {230u, std::string_view{"秋田県", 9}},
    {240u, std::string_view{"山形県", 9}},
    {250u, std::string_view{"福島県", 9}},
    {281u, std::string_view{"青森県", 9}},
    {291u, std::string_view{"東北地方太平洋沿岸", 27}},
    {292u, std::string_view{"東北地方日本海沿岸", 27}},
    {300u, std::string_view{"茨城県", 9}},
    {310u, std::string_view{"千葉県九十九里・外房", 30}},
    {311u, std::string_view{"千葉県内房", 15}},
    {312u, std::string_view{"東京湾内湾", 15}},
    {320u, std::string_view{"伊豆諸島", 12}},
    {321u, std::string_view{"小笠原諸島", 15}},
    {330u, std::string_view{"相模湾・三浦半島", 24}},
    {340u, std::string_view{"新潟県上中下越", 21}},
    {341u, std::string_view{"佐渡", 6}},
    {350u, std::string_view{"富山県", 9}},
    {360u, std::string_view{"石川県能登", 15}},
    {361u, std::string_view{"石川県加賀", 15}},
    {370u, std::string_view{"福井県", 9}},
    {380u, std::string_view{"静岡県", 9}},
    {390u, std::string_view{"愛知県外海", 15}},
    {391u, std::string_view{"伊勢・三河湾", 18}},
    {400u, std::string_view{"三重県南部", 15}},
    {481u, std::string_view{"千葉県", 9}},
    {482u, std::string_view{"神奈川県", 12}},
    {483u, std::string_view{"新潟県", 9}},
    {484u, std::string_view{"石川県", 9}},
    {485u, std::string_view{"愛知県", 9}},
    {486u, std::string_view{"三重県", 9}},
    {491u, std::string_view{"関東地方", 12}},
    {492u, std::string_view{"伊豆・小笠原諸島", 24}},
    {493u, std::string_view{"北陸地方", 12}},
    {494u, std::string_view{"東海地方", 12}},
    {500u, std::string_view{"京都府", 9}},
    {510u, std::string_view{"大阪府", 9}},
    {520u, std::string_view{"兵庫県北部", 15}},
    {521u, std::string_view{"兵庫県瀬戸内海沿岸", 27}},
    {522u, std::string_view{"淡路島南部", 15}},
    {530u, std::string_view{"和歌山県", 12}},
    {540u, std::string_view{"鳥取県", 9}},
    {550u, std::string_view{"島根県出雲・石見", 24}},
    {551u, std::string_view{"隠岐", 6}},
    {560u, std::string_view{"岡山県", 9}},
    {570u, std::string_view{"広島県", 9}},
    {580u, std::string_view{"徳島県", 9}},
    {590u, std::string_view{"香川県", 9}},
    {600u, std::string_view{"愛媛県宇和海沿岸", 24}},
    {601u, std::string_view{"愛媛県瀬戸内海沿岸", 27}},
    {610u, std::string_view{"高知県", 9}},
    {681u, std::string_view{"兵庫県", 9}},
    {682u, std::string_view{"島根県", 9}},
    {683u, std::string_view{"愛媛県", 9}},
    {691u, std::string_view{"近畿四国太平洋沿岸", 27}},
    {692u, std::string_view{"近畿中国日本海沿岸", 27}},
    {693u, std::string_view{"瀬戸内海沿岸", 18}},
    {700u, std::string_view{"山口県日本海沿岸", 24}},
    {701u, std::string_view{"山口県瀬戸内海沿岸", 27}},
    {710u, std::string_view{"福岡県瀬戸内海沿岸", 27}},
    {711u, std::string_view{"福岡県日本海沿岸", 24}},
    {712u, std::string_view{"有明・八代海", 18}},
    {720u, std::string_view{"佐賀県北部", 15}},
    {730u, std::string_view{"長崎県西方", 15}},
    {731u, std::string_view{"壱岐・対馬", 15}},
    {740u, std::string_view{"熊本県天草灘沿岸", 24}},
    {750u, std::string_view{"大分県瀬戸内海沿岸", 27}},
    {751u, std::string_view{"大分県豊後水道沿岸", 27}},
    {760u, std::string_view{"宮崎県", 9}},
    {770u, std::string_view{"鹿児島県東部", 18}},
    {771u, std::string_view{"種子島・屋久島地方", 27}},
    {772u, std::string_view{"奄美群島・トカラ列島", 30}},
    {773u, std::string_view{"鹿児島県西部", 18}},
    {781u, std::string_view{"山口県", 9}},
    {782u, std::string_view{"福岡県", 9}},
    {783u, std::string_view{"佐賀県", 9}},
    {784u, std::string_view{"長崎県", 9}},
    {785u, std::string_view{"熊本県", 9}},
    {786u, std::string_view{"大分県", 9}},
    {787u, std::string_view{"鹿児島県", 12}},
    {791u, std::string_view{"九州地方東部", 18}},
    {792u, std::string_view{"九州地方西部", 18}},
    {793u, std::string_view{"薩南諸島", 12}},
    {800u, std::string_view{"沖縄本島地方", 18}},
    {801u, std::string_view{"大東島地方", 15}},
    {802u, std::string_view{"宮古島・八重山地方", 27}},
    {891u, std::string_view{"沖縄県地方", 15}},
    {1000u, std::string_view{"その他の津波予報区", 27}},};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_tsunami_forecast_region_lookup(uint16_t id) noexcept {
    uint8_t lo = 0, hi = 99;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        if (QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_TABLE[mid].id == id) return QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_TABLE[mid].label;
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
