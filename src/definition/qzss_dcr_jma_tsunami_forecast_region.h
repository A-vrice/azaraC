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
static const char AZARAC_PROGMEM QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_POOL[] = "北海道太平洋沿岸東部\000北海道太平洋沿岸中部\000北海道太平洋沿岸西部\000北海道日本海沿岸北部\000北海道日本海沿岸南部\000オホーツク\000北海道太平洋沿岸\000北海道\000青森県\000青森県\000陸奥湾\000岩手県\000宮城県\000秋田県\000山形県\000福\000青森県\000東北地方\000東北地方\000茨城県\000千葉県九十九里・外房\000千葉県内房\000東京湾内湾\000伊豆\000小笠原\000相模湾・三浦半島\000新潟県上中下越\000佐渡\000富山県\000石川県能登\000石川県加賀\000福井県\000静岡県\000愛知県外海\000伊勢・三河湾\000三重県南部\000千葉県\000神奈川県\000新潟県\000石川県\000愛知県\000三重県\000関東\000伊豆・小笠原\000北陸\000東海\000京都府\000大阪府\000兵庫県北部\000兵庫\000淡路島南部\000和歌山県\000鳥取県\000島根県出雲・石見\000隠岐\000岡山県\000広\000徳\000香川県\000愛媛県宇和\000愛媛\000高知県\000兵庫県\000島根県\000愛媛県\000近畿四国\000近畿中国\000瀬\000山口県\000山口\000福岡\000福岡県\000有明・八代海\000佐賀県北部\000長崎県西方\000壱岐・対馬\000熊本県天草灘\000大分\000大分県豊後水道\000宮崎県\000鹿児島県東部\000種子島・屋久島\000奄美群島・トカラ列島\000鹿児島県西部\000山口県\000福岡県\000佐賀県\000長崎県\000熊本県\000大分県\000鹿児\000九州地方東部\000九州地方西部\000薩南\000沖縄本島\000大東島\000宮古島・八重山\000沖縄県\000その他の津波予報区\000";
static const char AZARAC_PROGMEM QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_PARENT_POOL[] = "地方\000太平洋沿岸\000島県\000戸内海沿岸\000日本海沿岸\000沿岸\000海沿岸\000県瀬戸内海沿岸\000諸島\000";
struct QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_PARENT_Entry { uint16_t offset; };
static const QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_PARENT_Entry QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_PARENT_TABLE[] AZARAC_PROGMEM = {
    {0u},
    {7u},
    {23u},
    {30u},
    {46u},
    {62u},
    {69u},
    {79u},
    {101u},
};
struct QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_Entry { uint16_t id; uint8_t parent; uint16_t offset; };
static const QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_Entry QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_TABLE[] AZARAC_PROGMEM = {
    {100u, 255u, 0u},
    {101u, 255u, 31u},
    {102u, 255u, 62u},
    {110u, 255u, 93u},
    {111u, 255u, 124u},
    {120u, 6u, 155u},
    {191u, 255u, 171u},
    {192u, 4u, 196u},
    {200u, 4u, 206u},
    {201u, 1u, 216u},
    {202u, 255u, 226u},
    {210u, 255u, 236u},
    {220u, 255u, 246u},
    {230u, 255u, 256u},
    {240u, 255u, 266u},
    {250u, 2u, 276u},
    {281u, 255u, 280u},
    {291u, 1u, 290u},
    {292u, 4u, 303u},
    {300u, 255u, 316u},
    {310u, 255u, 326u},
    {311u, 255u, 357u},
    {312u, 255u, 373u},
    {320u, 8u, 389u},
    {321u, 8u, 396u},
    {330u, 255u, 406u},
    {340u, 255u, 431u},
    {341u, 255u, 453u},
    {350u, 255u, 460u},
    {360u, 255u, 470u},
    {361u, 255u, 486u},
    {370u, 255u, 502u},
    {380u, 255u, 512u},
    {390u, 255u, 522u},
    {391u, 255u, 538u},
    {400u, 255u, 557u},
    {481u, 255u, 573u},
    {482u, 255u, 583u},
    {483u, 255u, 596u},
    {484u, 255u, 606u},
    {485u, 255u, 616u},
    {486u, 255u, 626u},
    {491u, 0u, 636u},
    {492u, 8u, 643u},
    {493u, 0u, 662u},
    {494u, 0u, 669u},
    {500u, 255u, 676u},
    {510u, 255u, 686u},
    {520u, 255u, 696u},
    {521u, 7u, 712u},
    {522u, 255u, 719u},
    {530u, 255u, 735u},
    {540u, 255u, 748u},
    {550u, 255u, 758u},
    {551u, 255u, 783u},
    {560u, 255u, 790u},
    {570u, 2u, 800u},
    {580u, 2u, 804u},
    {590u, 255u, 808u},
    {600u, 6u, 818u},
    {601u, 7u, 834u},
    {610u, 255u, 841u},
    {681u, 255u, 851u},
    {682u, 255u, 861u},
    {683u, 255u, 871u},
    {691u, 1u, 881u},
    {692u, 4u, 894u},
    {693u, 3u, 907u},
    {700u, 4u, 911u},
    {701u, 7u, 921u},
    {710u, 7u, 928u},
    {711u, 4u, 935u},
    {712u, 255u, 945u},
    {720u, 255u, 964u},
    {730u, 255u, 980u},
    {731u, 255u, 996u},
    {740u, 5u, 1012u},
    {750u, 7u, 1031u},
    {751u, 5u, 1038u},
    {760u, 255u, 1060u},
    {770u, 255u, 1070u},
    {771u, 0u, 1089u},
    {772u, 255u, 1111u},
    {773u, 255u, 1142u},
    {781u, 255u, 1161u},
    {782u, 255u, 1171u},
    {783u, 255u, 1181u},
    {784u, 255u, 1191u},
    {785u, 255u, 1201u},
    {786u, 255u, 1211u},
    {787u, 2u, 1221u},
    {791u, 255u, 1228u},
    {792u, 255u, 1247u},
    {793u, 8u, 1266u},
    {800u, 0u, 1273u},
    {801u, 0u, 1286u},
    {802u, 0u, 1296u},
    {891u, 0u, 1318u},
    {1000u, 255u, 1328u},
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_tsunami_forecast_region_lookup(uint16_t id) noexcept {
    uint8_t lo = 0, hi = 99;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        const char* AZARAC_PROGMEM ep = reinterpret_cast<const char*>(&QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_TABLE[mid]);
        uint16_t eid = pgm_read_word(ep + offsetof(QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_Entry, id));
        if (eid == id) {
            uint16_t off = pgm_read_word(ep + offsetof(QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_Entry, offset));
            uint8_t pi = pgm_read_byte(ep + offsetof(QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_Entry, parent));
            if (pi == 255u) return azarac_pgm_view_z(QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_POOL + off);
            const char* AZARAC_PROGMEM pp = reinterpret_cast<const char*>(&QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_PARENT_TABLE[pi]);
            uint16_t poff = pgm_read_word(pp + offsetof(QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_PARENT_Entry, offset));
            return azarac_pgm_join_z(QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_POOL + off, QZSS_DCR_JMA_TSUNAMI_FORECAST_REGION_PARENT_POOL + poff);
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
