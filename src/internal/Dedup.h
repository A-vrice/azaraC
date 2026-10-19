#pragma once
// Duplicate suppression per アプリケーションノートv2 (手順③④', 原PDF p.23–25).
//
// 同一性は MT～VN（フレーム bit 8..219 = 212 bit）の CRC-24Q（付属フローチャートも「MT～Vnの212bitについて比較する」と明記）。鍵に含めないもの:
//   - プリアンブル（bit 0..7）と Reserved（bit 220..225）: 放送で巡回する（A→B→C、Reserved は 16 値）ため、含めると 1 情報が分裂する。
//   - svid: 250 bit のフレームに衛星 ID は無く（NMEA/UBX ヘッダ由来の別レイヤ）、含めると中継衛星ごとに同じ情報を再通知する。
//   - MT=44 の SD（SDMT bit 14 + SDM bit 15..23）: QZS 事務局回答の照合範囲「MT および CAMF〜EM」に含まれないため、ゼロにしてから digest を取る（Decoder::messageIdentity）。
// Callers pass the digest of MT～VN as `identity` — see Parser::handleFrame.
//
// 履歴は手順④' のとおり有効時間で失効し、窓は災害種別ごと（原PDF p.26–27、internal/DedupWindow.h）。
// 表に無いカテゴリは AZARAC_DEDUP_WINDOW_MS。
// 満杯時は最終受信が最も古い 1 件を追い出す。
// 窓内の情報は再受信で時刻が更新されるため押し出されず、容量不足は「再通知」として現れる（警報は落ちない）。

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

// 1 情報の identity: msg_type (6 bit) + MT～VN の digest (24 bit) で 1 ワード（スロット 8 B = identity 4 B + last-seen 4 B）。
// 受信衛星・受信時刻は含まない。
// 合成鍵の payload は bits 0..29。
// bit 30 が合成判別子、bit 31 は VALID なので、実鍵（bits 24..29 が msg_type、bit 30 は常に 0）とは値が一致しても衝突しない。
constexpr uint32_t kSyntheticPayloadMask = 0x3FFFFFFFu;

struct DedupKey {
    uint8_t  msg_type;
    uint32_t identity;   // MT～VN (bit 8..219) の CRC-24Q
    // 集約後の南海トラフは情報自身のトークンで識別する（Message が手渡す電文 CRC は、ページ集合を完成させただけの電文のヘッダ由来で情報を識別しない）。タグ付きの鍵は電文鍵と一致しない。
    bool     synthetic = false;

    constexpr uint32_t packed() const {
        return synthetic
            ? (SYNTHETIC | (identity & kSyntheticPayloadMask))
            : (((uint32_t)msg_type << 24) | (identity & 0xFFFFFFu));
    }

private:
    static constexpr uint32_t SYNTHETIC = 0x40000000u;  // bit 30（msg_type は bits 24-29）
};

// 情報自身のトークンで識別する情報（南海トラフ地震）の鍵。identity = {info_code, information_type, report time}（NankaiPageKey 参照）。
constexpr inline DedupKey dedupEventKey(uint32_t token) {
    return DedupKey{0, token & kSyntheticPayloadMask, true};
}

// 事象（NankaiPageKey）の 26 ビットをそのまま鍵にする: Is 4 + It 2 + month 4 + day 5 + hour 5 + minute 6 = 26。
// フィールド幅は電文と同じなので 6 つ揃えば衝突しない。
// It を含めるのは NankaiPageKey と同じ理由（発表と取消を同一事象に潰さない）。
constexpr inline uint32_t dedupEventToken(uint8_t info_code, uint8_t information_type, uint8_t month,
                                          uint8_t day, uint8_t hour, uint8_t minute) {
    return ((uint32_t)(information_type & 0x3u) << 24)
         | ((uint32_t)(info_code & 0x0Fu) << 20)
         | ((uint32_t)(month & 0x0Fu) << 16)
         | ((uint32_t)(day   & 0x1Fu) << 11)
         | ((uint32_t)(hour  & 0x1Fu) << 6)
         | ((uint32_t)(minute & 0x3Fu));
}

// Fixed-size set-associative table: WAYS entries per set, the set picked by a cheap hash of the content.
// One decision costs at most WAYS, not AZARAC_DEDUP_SLOTS (a flat scan walks the whole capacity even with few live informations — the CHURN_NANOS_PER_OP path).
// Victim inside a set = least-recently-seen.
static constexpr uint8_t  DEDUP_WAYS = AZARAC_DEDUP_WAYS;
static constexpr uint16_t DEDUP_SETS = AZARAC_DEDUP_SLOTS / DEDUP_WAYS;
static_assert(AZARAC_DEDUP_SLOTS % DEDUP_WAYS == 0,
              "AZARAC_DEDUP_SLOTS must be a multiple of AZARAC_DEDUP_WAYS");
static_assert((DEDUP_SETS & (DEDUP_SETS - 1)) == 0,
              "AZARAC_DEDUP_SLOTS / AZARAC_DEDUP_WAYS must be a power of two");

class DedupFilter {
public:
    DedupFilter() { reset(); }

    // window_ms 以内に受信済みなら true。手順④' のとおり、どちらの場合も last-seen を更新する（情報有効時間は重複した場合にも更新され、最後に同情報を受信してから一定時間有効）。
    bool isDuplicate(const DedupKey& key, uint32_t now_ms, uint32_t window_ms);

    void reset();

private:
    // Bit 31 marks a valid entry: msg_type occupies only bits 24-29, so a real key never sets it and an all-zero table reads as empty.
    static constexpr uint32_t VALID = 0x80000000u;

    struct Entry {
        uint32_t content;        // VALID | packed identity; 0 = unused
        uint32_t last_seen_ms;   // reception time of the newest frame carrying it
    };

    // RAM 予算はここで決まる（AZARAC_DEDUP_SLOTS × 8 B）。鍵を広げる・svid を足す・窓を保存する変更は必ずこの assert に当たるので、黙って増えない。
    static_assert(sizeof(Entry) == 8,
                  "DedupFilter::Entry must stay 8 bytes: identity 4 B + last_seen 4 B. "
                  "A wider key (e.g. storing svid) multiplies the RAM of every slot.");

    Entry _ring[DEDUP_SETS][DEDUP_WAYS];
};

} // namespace internal
} // namespace azaraC
