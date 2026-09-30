#pragma once
// Duplicate suppression per アプリケーションノートv2 (原PDF p.23–25).
//
//   ① 複数衛星からの受信 — 250 BITS 完全一致する場合は同じ情報。
//   ② 連続受信 — 保存した履歴と照合し、一致すれば通知しない。
//
// The 250-bit frame carries no satellite identifier (svid comes from the
// NMEA/UBX header), so one information is identified by its CONTENT
// {msg_type, crc24} — a per-satellite key would re-announce the same
// information once per relay satellite.
//
// History is dropped the way the note's 手順④' describes: an information that
// has not been received within its validity window no longer counts as a
// duplicate, so it is either replaced or reported again. The window differs per
// disaster type (原PDF p.26–27: 緊急地震速報 5 分 … 津波 最大 24 時間), so it is
// a caller argument — see AZARAC_DEDUP_WINDOW_MS for the caller-side default.
//
// When the table is full the entry with the oldest last-seen time is evicted:
// a uniform ring would instead drop the newest information, re-announcing a
// live alert and keeping a stale one.

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

// Identity of one information = the content the spec compares (MT～VN):
// msg_type (6 bit) and crc24 (24 bit) — exactly one word. Receiving satellite and
// reception time are not part of it. 8 B per slot: same footprint as the
// previous {svid, msg_type, crc24} ring, with the last-seen time added for free.
struct DedupKey {
    uint8_t  msg_type;
    uint32_t crc24;
    // 情報そのものが持つ identity（電文の CRC ではない）であることの印。集約した
    // 南海トラフメッセージは多数の電文から組み立てられ、Message が引き継ぐのは
    // ページ集合を完成させた電文のヘッダなので、その CRC は情報を識別しない。
    // タグ付きの鍵は電文鍵と決して一致しない。
    bool     synthetic = false;

    constexpr uint32_t packed() const {
        return synthetic
            ? (SYNTHETIC | (crc24 & 0xFFFFFFu))
            : (((uint32_t)msg_type << 24) | (crc24 & 0xFFFFFFu));
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

    Entry _ring[DEDUP_SETS][DEDUP_WAYS];
};

} // namespace internal
} // namespace azaraC
