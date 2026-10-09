#pragma once
// 情報有効時間（手順④ 配信終了条件）: アプリケーションノートv2 原PDF p.26–27。
//
// Header-only so the Parser, the benchmark and test/tools/dedup_realday.cpp share one table. A second copy would drift silently: the realday tool measures the false re-notifications the Parser's windows produce.

#include "../azaraC_config.h"
#include "../Message.h"

namespace azaraC {
namespace internal {

// 1 通に複数の副種別（気象の Ww、洪水の Lv、海上の Dw）が入る場合は「条件にて該当する情報の配信が終了する」ので、条件を満たす情報のうち最長の窓を採る: 窓を短くする誤りは「まだ生きている情報を新規として再通知する」側に倒れるため、長い側が安全。
// fallback_ms は条件の無いカテゴリ（MT=44 CAMF、表に無い災害種別）に使う。
//
// 定数は必ず UL を付ける。AVR の unsigned int は 16 bit なので `60u*60u*1000u` は 65536 で剰余を踏み（= 61056 ms）、`24u*60u*60u*1000u` も同様に（= 23552 ms）、全カテゴリの窓が 20〜61 秒に潰れる。ホストの pgm-stub は int が 32 bit なのでこの欠陥を検出できない。
constexpr uint32_t kMinuteMs = 60UL * 1000UL;
constexpr uint32_t kHourMs   = 60UL * kMinuteMs;
constexpr uint32_t kDayMs    = 24UL * kHourMs;

constexpr uint32_t dedupWindowMs(uint32_t fallback_ms, uint8_t disaster_category,
                                 uint8_t information_type, const void* payload) {
    switch (disaster_category) {
    case 1: return 5UL * kMinuteMs;                        // 緊急地震速報 5 分
    case 2: case 3: return 2UL * kHourMs;                  // 震源 / 震度 2 時間
    case 4: return (information_type == 2)                 // 南海トラフ
                       ? 2UL * kHourMs                     //   取消 2 時間
                       : kDayMs;                           //   発表 24 時間
    case 5: {                                              // 津波
        // 発表かつ警報コード 3/4/5（津波警報・大津波警報）が最大 24 時間、他は 10 時間。
        const TsunamiData* t = static_cast<const TsunamiData*>(payload);
        const uint8_t dw = t ? t->warning_code : 0;
        return ((information_type == 0) && (dw == 3 || dw == 4 || dw == 5))
                   ? kDayMs
                   : 10UL * kHourMs;
    }
    case 6: return 10UL * kHourMs;                         // 北西太平洋津波 10 時間
    case 8: return kDayMs;                                 // 火山 24 時間
    case 9: return kHourMs;                                // 降灰 最大 1 時間
    case 10: {                                             // 気象
        // 24 時間は「発表状況 Ar=1（発表）」かつ「Ww が 1..6 or 23（特別警報系・土砂災害警戒情報）」のときだけ。Ww=21/22（大雨・竜巻注意情報）や解除は 3 時間。
        const WeatherData* w = static_cast<const WeatherData*>(payload);
        bool special = false;
        for (uint8_t i = 0; w && i < w->count && i < 6; ++i) {
            const uint8_t ww = w->entries[i].sub_category;
            if ((ww >= 1 && ww <= 6) || ww == 23) special = true;
        }
        return (w && w->warning_state == 1 && special)
                   ? kDayMs
                   : 3UL * kHourMs;
    }
    case 11: {                                             // 洪水
        // 24 時間は発表/訂正かつ警戒レベル 2..4（氾濫警戒/危険/発生）。解除・取消は 3 時間。
        const FloodData* f = static_cast<const FloodData*>(payload);
        bool warn = false;
        for (uint8_t i = 0; f && i < f->count && i < 3; ++i) {
            const uint8_t lv = f->entries[i].warning_level;
            if (lv >= 2 && lv <= 4) warn = true;
        }
        return (information_type != 2 && warn) ? kDayMs
                                               : 3UL * kHourMs;
    }
    case 12: return 3UL * kHourMs;                         // 台風 3 時間
    case 14: {                                             // 海上
        // 各警報コード 10/11/12/20/21/22/23 が最大 24 時間、解除 Dw=0 は最大 3 時間。
        // Dw は 5 bit（0..31）で、定義表は {0,10,11,12,20,21,22,23,31} を持つ。
        const MarineData* mi = static_cast<const MarineData*>(payload);
        bool warn = false;
        for (uint8_t i = 0; mi && i < mi->count && i < 8; ++i) {
            switch (mi->entries[i].warning_code) {
            case 10: case 11: case 12: case 20: case 21: case 22: case 23: warn = true; break;
            default: break;
            }
        }
        return warn ? kDayMs
                    : 3UL * kHourMs;
    }
    default: return fallback_ms;
    }
}

// 単位定数を固定する（AVR の 16 bit int での剰余を Arduino ジョブで落とす。pgm-stub は int が 32 bit なので検出できない）。各 case はこの 3 定数と `NUL * 定数` だけで組み立てる（関数自体は payload を cast するため定数式にはできず、static_assert から呼べない）。
static_assert(kMinuteMs == 60000UL,    "1 minute must be exact on a 16-bit int");
static_assert(kHourMs   == 3600000UL,   "1 hour must be exact on a 16-bit int");
static_assert(kDayMs    == 86400000UL,  "1 day must be exact on a 16-bit int");

// Message 版: MT=43 のときだけ有効な payload を渡す（MT=44 は条件が無い）。
inline uint32_t dedupWindowMs(const Message& m) {
    const Mt43Data* d = (m.payload_type == MsgPayloadType::Mt43) ? m.getMt43() : nullptr;
    if (!d) return AZARAC_DEDUP_WINDOW_MS;
    const void* payload = nullptr;
    switch (d->active_type) {
    case Mt43Data::ActiveType::Tsunami:     payload = d->getTsunami(); break;
    case Mt43Data::ActiveType::Weather:     payload = d->getWeather(); break;
    case Mt43Data::ActiveType::Flood:       payload = d->getFlood(); break;
    case Mt43Data::ActiveType::Marine:      payload = d->getMarine(); break;
    default: break;
    }
    return dedupWindowMs(AZARAC_DEDUP_WINDOW_MS, d->disaster_category,
                         d->information_type, payload);
}

} // namespace internal
} // namespace azaraC
