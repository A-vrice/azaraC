#pragma once
// Nankai Trough Earthquake multi-page aggregation buffer
//
// Pages write directly into aggregated_text[] at (page_num-1)*TEXT_PER_PAGE; a 64-bit bitmap tracks received pages — no PageData array (saves ~1KB at MAX_PAGES=63), no sorting, O(1) dedup. total_pages > MAX_PAGES truncates.

#if defined(__AVR__)
#include "avr_std/cstdint"
#else
#include <cstdint>
#endif
#if defined(__AVR__)
#include "avr_std/cstring"
#else
#include <cstring>
#endif
#include "../azaraC_config.h"

namespace azaraC {
namespace internal {

// Event key. svid は除外（複数衛星が同一電文を中継するため重複する）。
// Identity = {info_code, information_type, raw report_time DHM}。
// DHM は正規化前の生プロトコルビット（NankaiData::report_*）: Mt43Data::event_time は resolveTime() が 2/30→3/1 を書き換え月 0 を補完するため、report_unix の有無でハッシュが割れ1事象が複数バッファに分かれる。
// information_type（It: 0=発表 / 2=取消）も鍵に必要（無いと発表と取消が同じ Pn を先着優先で潰し合い文面が混ざる）。
// dedup 側も同じ 6 フィールドを使う（Dedup.h dedupEventToken）。
struct NankaiPageKey {
    uint8_t  info_code = 0;        // 1B — Is (Information Serial Code, 4b)
    uint8_t  report_month  = 0;    // 1B — raw report_time month (4b)
    uint8_t  report_day    = 0;    // 1B — raw report_time day (5b)
    uint8_t  report_hour   = 0;    // 1B — raw report_time hour (5b)
    uint8_t  report_minute = 0;    // 1B — raw report_time minute (6b)
    uint8_t  information_type = 0; // 1B — It (2b: 0=発表, 2=取消)
    // 合計 6B（パディングなし）

    constexpr NankaiPageKey() = default;
    // it は末尾の既定引数（既存呼び出し {ic, mo, d, h, m} の意味を変えない）。
    constexpr NankaiPageKey(uint8_t ic, uint8_t mo = 0, uint8_t d = 0, uint8_t h = 0, uint8_t m = 0,
                            uint8_t it = 0)
        : info_code(ic), report_month(mo), report_day(d), report_hour(h),
          report_minute(m), information_type(it) {}

    bool operator==(const NankaiPageKey& o) const {
        return info_code == o.info_code &&
               information_type == o.information_type &&
               report_month  == o.report_month &&
               report_day    == o.report_day &&
               report_hour   == o.report_hour &&
               report_minute == o.report_minute;
    }

    void clear() {
        info_code = 0;
        information_type = 0;
        report_month = 0;
        report_day = 0;
        report_hour = 0;
        report_minute = 0;
    }
};

// 6 バイト（パディングなし）を固定する: 鍵はページ受信のたびにコピーされ、バッファごとに 1 個常駐する。
static_assert(sizeof(NankaiPageKey) == 6, "NankaiPageKey must stay 6 bytes");

// Page aggregation buffer for a single event.
// Truncation: total_pages > MAX_PAGES なら pages 1..MAX_PAGES を残して truncated を立て、残りは静かに破棄する。
// ページ数上限・バッファ数は azaraC_config.h の AZARAC_NANKAI_MAX_PAGES / AZARAC_NANKAI_BUFFERS が唯一の定義元（範囲は spec の Pn/Pm: 1-63, 6bit）。

// MAX_PAGES は 64-bit bitmap に収まる 63 まで（spec の Pn/Pm 上限）
static_assert(AZARAC_NANKAI_MAX_PAGES > 0 && AZARAC_NANKAI_MAX_PAGES <= 63,
              "AZARAC_NANKAI_MAX_PAGES must be in range 1-63");

struct NankaiPageBuffer {
    static constexpr uint8_t MAX_PAGES = AZARAC_NANKAI_MAX_PAGES;
    static constexpr uint8_t SPEC_MAX_PAGES = 63;  // Official maximum (6 bits)
    static constexpr uint8_t TEXT_PER_PAGE = 18;
    static constexpr uint32_t TIMEOUT_MS = 60000;

    NankaiPageKey key;                  // 6B
    uint64_t received_bitmap = 0;       // 8B — bitmap: bit (page_num-1) set when received
    uint64_t last_update_ms = 0;        // 8B
    uint8_t total_pages = 0;            // 1B — Effective total (capped at MAX_PAGES)
    uint8_t original_total_pages = 0;   // 1B — Original total_pages from protocol
    uint8_t received_count = 0;         // 1B — Number of pages received
    bool truncated = false;             // 1B — true if total_pages > MAX_PAGES
    // aggregated_text at offset 28 (no padding needed, char alignment = 1)
    char aggregated_text[MAX_PAGES * TEXT_PER_PAGE + 1];

    NankaiPageBuffer() : aggregated_text{} {
        clearAll();
    }

    // Add a page (page_num 1-based, total_pages_in from Pm, text_data 18 bytes); true if added.
    bool addPage(uint8_t page_num, uint8_t total_pages_in, const uint8_t* text_data, uint64_t current_ms) {
        // Pn は 1-63 (spec)
        if (page_num == 0 || page_num > SPEC_MAX_PAGES) {
            return false;
        }

        uint8_t effective_total = total_pages_in;
        if (total_pages_in > MAX_PAGES) {
            effective_total = MAX_PAGES;
            // truncated は初回呼び出しで一度だけ立てる
            if (this->total_pages == 0) {
                truncated = true;
            }
        }

        if (page_num > effective_total) {
            return false;
        }

        if (this->total_pages == 0) {
            this->total_pages = effective_total;
            this->original_total_pages = total_pages_in;
        }

        // 以降の total_pages_in は初回値と一致必須
        if (this->original_total_pages != total_pages_in) {
            return false;
        }

        // bitmap による重複判定 O(1)
        uint64_t mask = 1ULL << (page_num - 1);
        if (received_bitmap & mask) {
            return false;
        }

        uint16_t offset = static_cast<uint16_t>(page_num - 1) * TEXT_PER_PAGE;
        memcpy(aggregated_text + offset, text_data, TEXT_PER_PAGE);
        received_bitmap |= mask;
        received_count++;
        last_update_ms = current_ms;

        return true;
    }

    bool isComplete() const {
        if (total_pages == 0) return false;
        return received_count >= total_pages;
    }

    // Text length excluding NUL; stops at the first 0x00 per page (UTF-8 has no NUL). Safe on incomplete buffers (only received pages are read).
    uint16_t getTextLength() const {
        uint16_t len = 0;

        uint64_t bm = received_bitmap;
        uint8_t p = 0;
        while (bm && p < total_pages) {
            if (bm & 1) {
                const char* page_start = aggregated_text + p * TEXT_PER_PAGE;
                len += pageTextLength_(page_start);
            }
            bm >>= 1;
            ++p;
        }

        return len;
    }

    // Compact received pages into a contiguous C string (call only when complete).
    // Non-final pages may be short (NUL hole) — serialize emits [ptr, ptr+len) contiguously, so holes would leak NULs.
    // In-place is safe: w <= p*TEXT_PER_PAGE, and writes never reach past the next source page.
    uint16_t compactText() {
        uint16_t w = 0;
        for (uint8_t p = 0; p < total_pages; ++p) {
            const char* src = aggregated_text + (uint16_t)p * TEXT_PER_PAGE;
            uint8_t n = pageTextLength_(src);
            if ((uint16_t)p * TEXT_PER_PAGE != w)
                memmove(aggregated_text + w, src, n);
            w += n;
        }
        aggregated_text[w] = '\0';
        return w;
    }

    bool isExpired(uint64_t current_ms) const {
        if (total_pages == 0) return false;
        return (current_ms - last_update_ms) > TIMEOUT_MS;
    }

    void clearAll() {
        key.clear();
        total_pages = 0;
        original_total_pages = 0;
        received_count = 0;
        received_bitmap = 0;
        last_update_ms = 0;
        truncated = false;
        memset(aggregated_text, 0, sizeof(aggregated_text));
    }

    bool isEmpty() const {
        return total_pages == 0;
    }

    // 空バッファの鍵は all-zero で zero-key 事象と一致してしまうため、空バッファは決してマッチさせない。
    bool matchesKey(const NankaiPageKey& k) const {
        return !isEmpty() && key == k;
    }

    void setKey(const NankaiPageKey& k) {
        key = k;
    }

private:
    // Per-page effective length (bytes up to first NUL, bounded by TEXT_PER_PAGE)
    uint8_t pageTextLength_(const char* page_start) const {
        uint8_t n = 0;
        while (n < TEXT_PER_PAGE && page_start[n] != 0) ++n;
        return n;
    }
};

// Manages multiple page buffers with bitmap tracking + LRU eviction; buffer count = AZARAC_NANKAI_BUFFERS (azaraC_config.h).

static_assert(AZARAC_NANKAI_BUFFERS > 0 && AZARAC_NANKAI_BUFFERS <= 32,
              "AZARAC_NANKAI_BUFFERS must be in range 1-32");

class NankaiPageBufferManager {
public:
    static constexpr uint8_t MAX_BUFFERS = AZARAC_NANKAI_BUFFERS;

    NankaiPageBufferManager() {
        for (uint8_t i = 0; i < MAX_BUFFERS; ++i) {
            _buffers[i].clearAll();
        }
    }

    // Add a page; returns completed-buffer pointer if all pages received, else nullptr
    NankaiPageBuffer* addPage(const NankaiPageKey& key, uint8_t page_num,
                               uint8_t total_pages, const uint8_t* text_data,
                               uint64_t current_ms) {
        expireBuffers(current_ms);

        int8_t idx = findBuffer(key);

        if (idx < 0) {
            idx = findEmptyBuffer();
            if (idx < 0) {
                idx = findOldestBuffer(current_ms);
            }
            _buffers[idx].clearAll();
            _buffers[idx].setKey(key);
        }

        if (_buffers[idx].addPage(page_num, total_pages, text_data, current_ms)) {
            if (_buffers[idx].isComplete()) {
                return &_buffers[idx];
            }
        }

        return nullptr;
    }

    const NankaiPageBuffer* getBuffer(const NankaiPageKey& key) const {
        int8_t idx = findBuffer(key);
        return (idx >= 0) ? &_buffers[idx] : nullptr;
    }

    void clearAll() {
        for (uint8_t i = 0; i < MAX_BUFFERS; ++i) {
            _buffers[i].clearAll();
        }
    }

private:
    NankaiPageBuffer _buffers[MAX_BUFFERS];

    int8_t findBuffer(const NankaiPageKey& key) const {
        for (uint8_t i = 0; i < MAX_BUFFERS; ++i) {
            if (_buffers[i].matchesKey(key)) {
                return i;
            }
        }
        return -1;
    }

    int8_t findEmptyBuffer() {
        for (uint8_t i = 0; i < MAX_BUFFERS; ++i) {
            if (_buffers[i].isEmpty()) {
                return i;
            }
        }
        return -1;
    }

    // LRU eviction: oldest buffer by age (wrap-aware via unsigned subtraction)
    int8_t findOldestBuffer(uint64_t current_ms) {
        uint64_t max_age = 0;
        int8_t oldest_idx = 0;

        for (uint8_t i = 0; i < MAX_BUFFERS; ++i) {
            // 空バッファの age は 0（他に古いものが無い場合のみ選ばれる）
            uint64_t age = _buffers[i].isEmpty() ? 0 : (current_ms - _buffers[i].last_update_ms);
            if (age > max_age) {
                max_age = age;
                oldest_idx = i;
            }
        }

        return oldest_idx;
    }

    void expireBuffers(uint64_t current_ms) {
        for (uint8_t i = 0; i < MAX_BUFFERS; ++i) {
            if (!_buffers[i].isEmpty() && _buffers[i].isExpired(current_ms)) {
                _buffers[i].clearAll();
            }
        }
    }
};

} // namespace internal
} // namespace azaraC
