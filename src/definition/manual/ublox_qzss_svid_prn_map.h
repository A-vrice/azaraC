#pragma once
// HAND-MAINTAINED（手書き）— 自動生成ではない。scripts/gen/gen_definitions.py はこの表を SKIP_MODULES
// (extra_headers) に挙げて決して上書きしないため、ここは azarashi を自動追跡しない。
// azarashi の azarashi.definitions.qzss.ubx.svid_to_prn と手作業で同期させること
// （azarashi 0.17.1 と一致を確認済み: {1: 183, 2: 184, 3: 185, 4: 186, 7: 189}）。
// モジュール : ublox_qzss_svid_prn_map
// 変数       : ublox_qzss_svid_prn_map
// エントリ数 : 5
// 方式       : switch

#if defined(__AVR__)
#include "../../internal/avr_std/cstdint"
#else
#include <cstdint>
#endif
#if defined(__AVR__)
#include "../../internal/avr_std/optional"
#else
#include <optional>
#endif
#if defined(__AVR__)
#include "../../internal/avr_std/string_view"
#else
#include <string_view>
#endif
#include "../../azaraC_config.h"
#include "../../internal/FlashString.h"

namespace azaraC {
namespace def {

#if defined(__AVR__)

// ラベルは関数ローカル static ではなく名前空間スコープの配列にする: Arduino コアは LTO で
// ビルドされ、inline 関数のローカル static（one-only シンボル）では `__section__` 属性が落ちるため、
// そのラベルは .rodata（= SRAM）に置かれてしまう。生成表と同じ形にしている
// （gen_definitions.py の switch_labels 参照）。
static const char AZARAC_PROGMEM UBLOX_QZSS_SVID_PRN_MAP_C1[] = "183";
static const char AZARAC_PROGMEM UBLOX_QZSS_SVID_PRN_MAP_C2[] = "184";
static const char AZARAC_PROGMEM UBLOX_QZSS_SVID_PRN_MAP_C3[] = "185";
static const char AZARAC_PROGMEM UBLOX_QZSS_SVID_PRN_MAP_C4[] = "186";
static const char AZARAC_PROGMEM UBLOX_QZSS_SVID_PRN_MAP_C7[] = "189";

[[nodiscard]] inline std::optional<std::string_view> ublox_qzss_svid_prn_map_lookup(uint8_t id) noexcept {
    switch (id) {
        case 1: return azarac_pgm_view(AZARAC_PGM_PTR(UBLOX_QZSS_SVID_PRN_MAP_C1), 3);
        case 2: return azarac_pgm_view(AZARAC_PGM_PTR(UBLOX_QZSS_SVID_PRN_MAP_C2), 3);
        case 3: return azarac_pgm_view(AZARAC_PGM_PTR(UBLOX_QZSS_SVID_PRN_MAP_C3), 3);
        case 4: return azarac_pgm_view(AZARAC_PGM_PTR(UBLOX_QZSS_SVID_PRN_MAP_C4), 3);
        case 7: return azarac_pgm_view(AZARAC_PGM_PTR(UBLOX_QZSS_SVID_PRN_MAP_C7), 3);
        default: return std::nullopt;
    }
}

#else

[[nodiscard]] inline constexpr std::optional<std::string_view> ublox_qzss_svid_prn_map_lookup(uint8_t id) {
    switch (id) {
        case 1: return std::string_view{"183", 3};
        case 2: return std::string_view{"184", 3};
        case 3: return std::string_view{"185", 3};
        case 4: return std::string_view{"186", 3};
        case 7: return std::string_view{"189", 3};
        default: return std::nullopt;
    }
}

#endif

} // namespace def
} // namespace azaraC
