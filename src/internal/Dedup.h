#pragma once
// Duplicate suppression per アプリケーションノートv2 (原PDF p.23–25).
//
//   ① 複数衛星からの受信 — 同じ情報を 250 BITS で照合する（後段③ のとおり、
//      照合に使うのは MT～VN の 212 bit）。
//   ② 連続受信 — 保存した履歴と照合し、一致すれば通知しない。
//   ③ 照合の対象は MT～VN（フレーム bit 8..219 = 212 bit）。付属フローチャートも
//      「MT～Vnの212bitについて比較する」と明記する。プリアンブル（bit 0..7）も
//      Reserved（bit 220..225）も含めない。
//
// The 250-bit frame carries no satellite identifier (svid comes from the
// NMEA/UBX header), so a per-satellite key would re-announce the same
// information once per relay satellite: the key carries no svid.
//
// The key excludes the preamble (bit 0..7) AND the Reserved 6 bits (220..225) on
// purpose. The broadcast cycles the preamble A(0x53)→B(0x9A)→C(0xC6) and rotates
// the Reserved field through all 16 values, so a wider key splits one
// information into many: measured on one real day, the correct 212-bit span
// yields 162 distinct informations, 218 bits yields 1,764, and all 250 bits
// 3,697. Callers pass the digest of MT～VN as `identity` — see
// Parser::handleFrame.
//
// History is dropped the way the note's 手順④' describes: an information that
// has not been received within its validity window no longer counts as a
// duplicate, so it is either replaced or reported again. The window differs per
// disaster type (原PDF p.26–27: 緊急地震速報 5 分 … 津波 最大 24 時間) — see
// internal/DedupWindow.h for the per-category table and AZARAC_DEDUP_WINDOW_MS
// for its fallback.
//
// When the table is full the entry with the oldest last-seen time is evicted:
// a uniform ring would instead drop the newest information, re-announcing a
// live alert and keeping a stale one.
//
// ── 取りこぼし（ドロップ）率 ────────────────────────────────────────────────
// 容量が足りないときの失敗の仕方は 2 種類あり、この実装は前者にしか倒れない:
//   ・再通知 (FALSE_RE) — 窓内で生きている情報を「新規」と誤判定。通知が二重に
//     出るだけで、警報そのものは失われない。
//   ・取りこぼし (MISSED) — 生きていない情報を「重複」と誤判定し、通知が落ちる。
// 追い出しは「最も古い=窓切れに近い」1 件を選ぶので、窓内で再受信し続けている
// 情報が押し出される前に必ず自身の再受信で時刻が更新される。したがって容量不足は
// 再通知として現れ、MISSED は 0 のままになる（実測でも 30 日 × 全容量で 0）。
// つまり **この表の容量不足で警報が消えることはない**。影響は「同じ情報を二度
// 通知しうる」ことに限られる。実測（2024 年の QZSS アーカイブ 30 日分、
// `make -C test dedup-realday`）: 生存ピークは 20〜327（中央値 66）、512×8 は
// 30 日すべて偽再通知 0、256×8 で偽再通知が出るのは最悪日（生存ピーク 327）1 日
// のみ 2 件。**MISSED は 30 日 × 全容量で 0**。カテゴリ別の内訳は同ツールの
// REALDAY_CAT<n>_* を参照。
// この性質は「同一性が MT～VN に一致している」ことにも依存する: 鍵が広すぎると
// 1 情報が複数の鍵に分裂し、その分だけ生きた情報が居座って再通知が増える。

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
// part of it. 8 B per slot: same footprint as the previous {svid, msg_type,
// crc24} ring, with the last-seen time added for free.
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
