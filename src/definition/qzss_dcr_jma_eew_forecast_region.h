#pragma once
// AUTO-GENERATED from azarashi 0.16.4 with CI-CD
// Source module : qzss_dcr_jma_eew_forecast_region
// Variable      : qzss_dcr_jma_eew_forecast_region
// Entries       : 71
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

#if (AZARAC_ENABLE_EEW)

#if defined(__AVR__)
static const char AZARAC_PROGMEM QZSS_DCR_JMA_EEW_FORECAST_REGION_POOL[] = "北海道道央\000北海道道南\000北海道道北\000北海道道東\000青森\000岩手\000宮城\000秋田\000山形\000福島\000茨城\000栃木\000群馬\000埼玉\000千葉\000東京\000伊豆諸島\000小笠原\000神奈川\000新潟\000富山\000石川\000福井\000山梨\000長野\000岐阜\000静岡\000愛知\000三重\000滋賀\000京都\000大阪\000兵庫\000奈良\000和歌山\000鳥取\000島根\000岡山\000広島\000山口\000徳島\000香川\000愛媛\000高知\000福岡\000佐賀\000長崎\000熊本\000大分\000宮崎\000鹿児島\000奄美(群島)\000沖縄本島\000大東島\000宮古島\000八重山\000北海道\000東北\000関東\000伊豆諸島\000小笠原\000北陸\000甲信\000東海\000近畿\000中国\000四国\000九州\000奄美(群島)\000沖縄\000その他の府県予報区および地方予報区\000";
struct QZSS_DCR_JMA_EEW_FORECAST_REGION_Entry { uint8_t id; uint16_t offset; uint16_t len; };
static const QZSS_DCR_JMA_EEW_FORECAST_REGION_Entry QZSS_DCR_JMA_EEW_FORECAST_REGION_TABLE[] AZARAC_PROGMEM = {
    {1u, 0u, 15u},
    {2u, 16u, 15u},
    {3u, 32u, 15u},
    {4u, 48u, 15u},
    {5u, 64u, 6u},
    {6u, 71u, 6u},
    {7u, 78u, 6u},
    {8u, 85u, 6u},
    {9u, 92u, 6u},
    {10u, 99u, 6u},
    {11u, 106u, 6u},
    {12u, 113u, 6u},
    {13u, 120u, 6u},
    {14u, 127u, 6u},
    {15u, 134u, 6u},
    {16u, 141u, 6u},
    {17u, 148u, 12u},
    {18u, 161u, 9u},
    {19u, 171u, 9u},
    {20u, 181u, 6u},
    {21u, 188u, 6u},
    {22u, 195u, 6u},
    {23u, 202u, 6u},
    {24u, 209u, 6u},
    {25u, 216u, 6u},
    {26u, 223u, 6u},
    {27u, 230u, 6u},
    {28u, 237u, 6u},
    {29u, 244u, 6u},
    {30u, 251u, 6u},
    {31u, 258u, 6u},
    {32u, 265u, 6u},
    {33u, 272u, 6u},
    {34u, 279u, 6u},
    {35u, 286u, 9u},
    {36u, 296u, 6u},
    {37u, 303u, 6u},
    {38u, 310u, 6u},
    {39u, 317u, 6u},
    {40u, 324u, 6u},
    {41u, 331u, 6u},
    {42u, 338u, 6u},
    {43u, 345u, 6u},
    {44u, 352u, 6u},
    {45u, 359u, 6u},
    {46u, 366u, 6u},
    {47u, 373u, 6u},
    {48u, 380u, 6u},
    {49u, 387u, 6u},
    {50u, 394u, 6u},
    {51u, 401u, 9u},
    {52u, 411u, 14u},
    {53u, 426u, 12u},
    {54u, 439u, 9u},
    {55u, 449u, 9u},
    {56u, 459u, 9u},
    {57u, 469u, 9u},
    {58u, 479u, 6u},
    {59u, 486u, 6u},
    {60u, 493u, 12u},
    {61u, 506u, 9u},
    {62u, 516u, 6u},
    {63u, 523u, 6u},
    {64u, 530u, 6u},
    {65u, 537u, 6u},
    {66u, 544u, 6u},
    {67u, 551u, 6u},
    {68u, 558u, 6u},
    {69u, 565u, 14u},
    {70u, 580u, 6u},
    {80u, 587u, 51u},
};
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_eew_forecast_region_lookup(uint8_t id) noexcept {
    uint8_t lo = 0, hi = 71;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        const char* AZARAC_PROGMEM ep = reinterpret_cast<const char*>(&QZSS_DCR_JMA_EEW_FORECAST_REGION_TABLE[mid]);
        uint8_t eid = static_cast<uint8_t>(pgm_read_byte(ep + offsetof(QZSS_DCR_JMA_EEW_FORECAST_REGION_Entry, id)));
        if (eid == id) {
            uint16_t off = pgm_read_word(ep + offsetof(QZSS_DCR_JMA_EEW_FORECAST_REGION_Entry, offset));
            uint16_t n = pgm_read_word(ep + offsetof(QZSS_DCR_JMA_EEW_FORECAST_REGION_Entry, len));
            if (n == 0) return std::nullopt;
            return azarac_pgm_view(QZSS_DCR_JMA_EEW_FORECAST_REGION_POOL + off, n);
        }
        if (eid < id) lo = static_cast<uint8_t>(mid + 1); else hi = mid;
    }
    return std::nullopt;
}
#else
struct QZSS_DCR_JMA_EEW_FORECAST_REGION_Entry { uint8_t id; std::optional<std::string_view> label; };
inline constexpr QZSS_DCR_JMA_EEW_FORECAST_REGION_Entry QZSS_DCR_JMA_EEW_FORECAST_REGION_TABLE[] = {
    {1u, std::string_view{"北海道道央", 15}},
    {2u, std::string_view{"北海道道南", 15}},
    {3u, std::string_view{"北海道道北", 15}},
    {4u, std::string_view{"北海道道東", 15}},
    {5u, std::string_view{"青森", 6}},
    {6u, std::string_view{"岩手", 6}},
    {7u, std::string_view{"宮城", 6}},
    {8u, std::string_view{"秋田", 6}},
    {9u, std::string_view{"山形", 6}},
    {10u, std::string_view{"福島", 6}},
    {11u, std::string_view{"茨城", 6}},
    {12u, std::string_view{"栃木", 6}},
    {13u, std::string_view{"群馬", 6}},
    {14u, std::string_view{"埼玉", 6}},
    {15u, std::string_view{"千葉", 6}},
    {16u, std::string_view{"東京", 6}},
    {17u, std::string_view{"伊豆諸島", 12}},
    {18u, std::string_view{"小笠原", 9}},
    {19u, std::string_view{"神奈川", 9}},
    {20u, std::string_view{"新潟", 6}},
    {21u, std::string_view{"富山", 6}},
    {22u, std::string_view{"石川", 6}},
    {23u, std::string_view{"福井", 6}},
    {24u, std::string_view{"山梨", 6}},
    {25u, std::string_view{"長野", 6}},
    {26u, std::string_view{"岐阜", 6}},
    {27u, std::string_view{"静岡", 6}},
    {28u, std::string_view{"愛知", 6}},
    {29u, std::string_view{"三重", 6}},
    {30u, std::string_view{"滋賀", 6}},
    {31u, std::string_view{"京都", 6}},
    {32u, std::string_view{"大阪", 6}},
    {33u, std::string_view{"兵庫", 6}},
    {34u, std::string_view{"奈良", 6}},
    {35u, std::string_view{"和歌山", 9}},
    {36u, std::string_view{"鳥取", 6}},
    {37u, std::string_view{"島根", 6}},
    {38u, std::string_view{"岡山", 6}},
    {39u, std::string_view{"広島", 6}},
    {40u, std::string_view{"山口", 6}},
    {41u, std::string_view{"徳島", 6}},
    {42u, std::string_view{"香川", 6}},
    {43u, std::string_view{"愛媛", 6}},
    {44u, std::string_view{"高知", 6}},
    {45u, std::string_view{"福岡", 6}},
    {46u, std::string_view{"佐賀", 6}},
    {47u, std::string_view{"長崎", 6}},
    {48u, std::string_view{"熊本", 6}},
    {49u, std::string_view{"大分", 6}},
    {50u, std::string_view{"宮崎", 6}},
    {51u, std::string_view{"鹿児島", 9}},
    {52u, std::string_view{"奄美(群島)", 14}},
    {53u, std::string_view{"沖縄本島", 12}},
    {54u, std::string_view{"大東島", 9}},
    {55u, std::string_view{"宮古島", 9}},
    {56u, std::string_view{"八重山", 9}},
    {57u, std::string_view{"北海道", 9}},
    {58u, std::string_view{"東北", 6}},
    {59u, std::string_view{"関東", 6}},
    {60u, std::string_view{"伊豆諸島", 12}},
    {61u, std::string_view{"小笠原", 9}},
    {62u, std::string_view{"北陸", 6}},
    {63u, std::string_view{"甲信", 6}},
    {64u, std::string_view{"東海", 6}},
    {65u, std::string_view{"近畿", 6}},
    {66u, std::string_view{"中国", 6}},
    {67u, std::string_view{"四国", 6}},
    {68u, std::string_view{"九州", 6}},
    {69u, std::string_view{"奄美(群島)", 14}},
    {70u, std::string_view{"沖縄", 6}},
    {80u, std::string_view{"その他の府県予報区および地方予報区", 51}},};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_eew_forecast_region_lookup(uint8_t id) noexcept {
    uint8_t lo = 0, hi = 71;
    while (lo < hi) {
        uint8_t mid = static_cast<uint8_t>(lo + (hi - lo) / 2);
        if (QZSS_DCR_JMA_EEW_FORECAST_REGION_TABLE[mid].id == id) return QZSS_DCR_JMA_EEW_FORECAST_REGION_TABLE[mid].label;
        if (QZSS_DCR_JMA_EEW_FORECAST_REGION_TABLE[mid].id < id) lo = mid + 1;
        else hi = mid;
    }
    return std::nullopt;
}
#endif

#else

#if defined(__AVR__)
[[nodiscard]] inline std::optional<std::string_view> qzss_dcr_jma_eew_forecast_region_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#else
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_eew_forecast_region_lookup(uint8_t id) noexcept {
    (void)id;
    return std::nullopt;
}
#endif

#endif

} // namespace def
} // namespace azaraC
