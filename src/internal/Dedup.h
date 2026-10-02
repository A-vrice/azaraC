#pragma once
// Duplicate suppression per アプリケーションノートv2 (手順③④', 原PDF p.23–25).
//
// 同一性は MT～VN（フレーム bit 8..219 = 212 bit）の CRC-24Q。付属フローチャートも
// 「MT～Vnの212bitについて比較する」と明記する。鍵に含めないもの:
//   - プリアンブル（bit 0..7）と Reserved（bit 220..225）。放送で巡回する
//     （A→B→C、Reserved は 16 値）ため、含めると 1 情報が分裂する。
//   - svid。250 bit のフレームに衛星 ID は無く（NMEA/UBX ヘッダ由来の別レイヤ）、
//     含めると中継衛星ごとに同じ情報を再通知する。
// Callers pass the digest of MT～VN as `identity` — see Parser::handleFrame.
//
// 履歴は手順④' のとおり有効時間で失効する。窓は災害種別ごと（原PDF p.26–27、
// internal/DedupWindow.h）で、表に無いカテゴリは AZARAC_DEDUP_WINDOW_MS。
//
// 満杯時は最終受信が最も古い 1 件を追い出す。窓内で生きている情報は自身の再受信で
// 時刻が更新されるため押し出されず、容量不足は「再通知」として現れる（警報は落ちない）。

#include "../azaraC_config.h"  // single source of truth for AZARAC_DEDUP_SLOTS
#include "MtCommonTypes.h"      // shared integer types (cstdint AVR switch lives here)
static_assert(AZARAC_DEDUP_SLOTS > 0, "AZARAC_DEDUP_SLOTS must be > 0");
#if defined(__AVR__)
#include "avr_std/cstring"
#else
#include <cstring>
#endif

namespace azaraC {
namespace internal {

// Identity of one information: msg_type (6 bit) and the digest of MT～VN
// (24 bit) — exactly one word. Receiving satellite and reception time are not
// part of it. 8 B per slot (identity 4 B + last-seen 4 B).
struct DedupKey {
    uint8_t  msg_type;
    uint32_t identity;   // MT～VN (bit 8..219) の CRC-24Q。プリアンブルを含まない。
    // 情報そのものが持つ identity（電文の CRC ではない）であることの印。集約した
    // 南海トラフメッセージは多数の電文から組み立てられ、Message が引き継ぐのは
    // ページ集合を完成させた電文のヘッダなので、その CRC は情報を識別しない。
    // タグ付きの鍵は電文鍵と決して一致しない。
    bool     synthetic = false;

    constexpr uint32_t packed() const {
        return synthetic
            ? (SYNTHETIC | (identity & 0xFFFFFFu))
            : (((uint32_t)msg_type << 24) | (identity & 0xFFFFFFu));
    }

private:
    static constexpr uint32_t SYNTHETIC = 0x40000000u;  // bit 30（msg_type は bits 24-29）
};

// 電文の CRC ではなく情報自身のトークンで識別する情報の DedupKey —
// 南海トラフ地震（identity = {info_code, report time}、NankaiPageKey 参照）。
constexpr inline DedupKey dedupEventKey(uint32_t token) {
    return DedupKey{0, token & 0xFFFFFFu, true};
}

// 事象（NankaiPageKey）の 24 ビットをそのまま鍵にする: info_code 4 + month 4 +
// day 5 + hour 5 + minute 6 = 24。幅は電文のフィールド幅と同じなので衝突しない。
constexpr inline uint32_t dedupEventToken(uint8_t info_code, uint8_t month, uint8_t day,
                                          uint8_t hour, uint8_t minute) {
    return ((uint32_t)(info_code & 0x0Fu) << 20)
         | ((uint32_t)(month & 0x0Fu) << 16)
         | ((uint32_t)(day   & 0x1Fu) << 11)
         | ((uint32_t)(hour  & 0x1Fu) << 6)
         | ((uint32_t)(minute & 0x3Fu));
}

// Fixed-size set-associative table: WAYS entries per set, sets selected by a
// cheap hash of the content. Cost per decision is bounded by WAYS, not by
// AZARAC_DEDUP_SLOTS (a flat scan walks the whole capacity even when only a few
// informations are live — the throughput path the benchmark reports as
// CHURN_NANOS_PER_OP). Victim selection inside a set is least-recently-seen.
static constexpr uint8_t  DEDUP_WAYS = AZARAC_DEDUP_WAYS;
static constexpr uint16_t DEDUP_SETS = AZARAC_DEDUP_SLOTS / DEDUP_WAYS;
static_assert(AZARAC_DEDUP_SLOTS % DEDUP_WAYS == 0,
              "AZARAC_DEDUP_SLOTS must be a multiple of AZARAC_DEDUP_WAYS");
static_assert((DEDUP_SETS & (DEDUP_SETS - 1)) == 0,
              "AZARAC_DEDUP_SLOTS / AZARAC_DEDUP_WAYS must be a power of two");

class DedupFilter {
public:
    DedupFilter() { reset(); }

    // True when this information was already received within window_ms.
    // Refreshes the entry's last-seen time either way, per 手順④'
    // (情報有効時間は、重複した場合にも更新され、最後に同情報を受信してから一定時間有効とする).
    bool isDuplicate(const DedupKey& key, uint32_t now_ms, uint32_t window_ms);

    void reset();

private:
    // Bit 31 marks a valid entry: msg_type only occupies bits 24-29, so a real
    // content never sets it and an all-zero table is "empty".
    static constexpr uint32_t VALID = 0x80000000u;

    struct Entry {
        uint32_t content;        // VALID | packed identity; 0 = unused
        uint32_t last_seen_ms;   // reception time of the newest frame carrying it
    };

    // RAM 予算はここで決まる（AZARAC_DEDUP_SLOTS × 8 B）。鍵を広げる・svid を足す
    // ・窓を保存するといった変更は必ずこの assert に当たるので、黙って増えない。
    static_assert(sizeof(Entry) == 8,
                  "DedupFilter::Entry must stay 8 bytes: identity 4 B + last_seen 4 B. "
                  "A wider key (e.g. storing svid) multiplies the RAM of every slot.");

    Entry _ring[DEDUP_SETS][DEDUP_WAYS];
};

} // namespace internal
} // namespace azaraC
