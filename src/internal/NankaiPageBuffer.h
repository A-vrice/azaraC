#pragma once
// Nankai Trough Earthquake multi-page aggregation buffer
//
// Pages are written DIRECTLY into aggregated_text[] at offset (page_num-1)*TEXT_PER_PAGE;
// a 64-bit bitmap tracks received pages. No separate PageData array (saves ~1KB at
// MAX_PAGES=63), no sorting, O(1) duplicate detection. total_pages > MAX_PAGES truncates.

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
#if defined(__AVR__)
#include "avr_std/climits"
#else
#include <climits>
#endif
#include "TimeFields.h"

namespace azaraC {
namespace internal {

// Event key. svid deliberately excluded: multiple QZSS satellites relay the same
// message, so including svid would create duplicate buffers for one event.
struct NankaiPageKey {
    uint32_t event_time_unix = 0;  // 4B — largest alignment first
    uint8_t  info_code = 0;        // 1B
    uint8_t  fallback_day    = 0;  // 1B
    uint8_t  fallback_hour   = 0;  // 1B
    uint8_t  fallback_minute = 0;  // 1B
    // 合計 8B（パディングなし）

    bool operator==(const NankaiPageKey& o) const {
        if (event_time_unix != 0 || o.event_time_unix != 0) {
            return info_code == o.info_code &&
                   event_time_unix == o.event_time_unix;
        }
        return info_code == o.info_code &&
               fallback_day   == o.fallback_day &&
               fallback_hour  == o.fallback_hour &&
               fallback_minute == o.fallback_minute;
    }

    bool operator!=(const NankaiPageKey& o) const {
        return !(*this == o);
    }

    bool isValid() const {
        return event_time_unix != 0 || fallback_day != 0;
    }

    void clear() {
        info_code = 0;
        event_time_unix = 0;
        fallback_day = 0;
        fallback_hour = 0;
        fallback_minute = 0;
    }
};

// Page aggregation buffer for a single event. Pages written directly at
// (page_num-1)*TEXT_PER_PAGE; bitmap tracks received pages.
// Truncation: if total_pages > MAX_PAGES, keep pages 1..MAX_PAGES and set
// truncated; the rest are silently dropped.
// Config AZARAC_NANKAI_MAX_PAGES (default 12, max 63, Pn/Pm range 1-63 = 6 bits).
#ifndef AZARAC_NANKAI_MAX_PAGES
#define AZARAC_NANKAI_MAX_PAGES 12
#endif

// Static assertion ensures MAX_PAGES fits in a 64-bit bitmap (63 max per spec)
static_assert(AZARAC_NANKAI_MAX_PAGES > 0 && AZARAC_NANKAI_MAX_PAGES <= 63,
              "AZARAC_NANKAI_MAX_PAGES must be in range 1-63");

struct NankaiPageBuffer {
    static constexpr uint8_t MAX_PAGES = AZARAC_NANKAI_MAX_PAGES;
    static constexpr uint8_t SPEC_MAX_PAGES = 63;  // Official maximum (6 bits)
    static constexpr uint8_t TEXT_PER_PAGE = 18;
    static constexpr uint32_t TIMEOUT_MS = 60000;  // 60 seconds timeout

    NankaiPageKey key;                  // 8B
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

    // Add a page (page_num 1-based, total_pages from Pm, text_data 18 bytes).
    // Returns true if added.
    bool addPage(uint8_t page_num, uint8_t total_pages, const uint8_t* text_data, uint64_t current_ms) {
        // Page number range check (1-63 per spec)
        if (page_num == 0 || page_num > SPEC_MAX_PAGES) {
            return false;
        }

        // total_pages exceeds capacity → cap to MAX_PAGES
        uint8_t effective_total = total_pages;
        if (total_pages > MAX_PAGES) {
            effective_total = MAX_PAGES;
            // truncated flag set once (first call)
            if (this->total_pages == 0) {
                truncated = true;
            }
        }

        // Page number must be within effective range
        if (page_num > effective_total) {
            return false;
        }

        // Set total_pages on first call
        if (this->total_pages == 0) {
            this->total_pages = effective_total;
            this->original_total_pages = total_pages;
        }

        // total_pages must match (original value for consistency check)
        if (this->original_total_pages != total_pages) {
            return false;
        }

        // Duplicate check via bitmap (O(1))
        uint64_t mask = 1ULL << (page_num - 1);
        if (received_bitmap & mask) {
            return false;  // Already received
        }

        // Write directly to aggregated_text at offset (page_num-1) * 18
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

    // Text length excluding null terminator; stops at first 0x00 per page (UTF-8 has no NUL).
    // Safe on incomplete buffers: only reads received pages.
    uint16_t getTextLength() const {
        uint16_t len = 0;

        // Iterate only received pages (checked via bitmap)
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

    // Combined text in page order (offset-based storage guarantees order),
    // stopping at first 0x00 per page. Only reads received pages.
    void getText(char* out, uint16_t max_len) const {
        if (!out || max_len == 0) return;

        uint16_t pos = 0;
        uint64_t bm = received_bitmap;
        uint8_t p = 0;

        while (bm && p < total_pages && pos < max_len - 1) {
            if (bm & 1) {
                const char* src = aggregated_text + p * TEXT_PER_PAGE;
                uint8_t page_len = pageTextLength_(src);
                uint8_t to_copy = (page_len < (max_len - 1 - pos))
                                  ? page_len
                                  : (max_len - 1 - pos);
                if (to_copy > 0) {
                    memcpy(out + pos, src, to_copy);
                    pos += to_copy;
                }
            }
            bm >>= 1;
            ++p;
        }

        out[pos] = '\0';  // Null terminate
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
    }

    bool isEmpty() const {
        return total_pages == 0;
    }

    bool matchesKey(const NankaiPageKey& k) const {
        return key == k;
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

// Manages multiple page buffers with bitmap tracking + LRU eviction;
// buffer count = AZARAC_NANKAI_BUFFERS.

// Default buffer count if not user-defined
#ifndef AZARAC_NANKAI_BUFFERS
#define AZARAC_NANKAI_BUFFERS 4
#endif

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
        // Expire old buffers
        expireBuffers(current_ms);

        int8_t idx = findBuffer(key);

        if (idx < 0) {
            // No existing buffer, find empty slot
            idx = findEmptyBuffer();
            if (idx < 0) {
                // No empty slot, use LRU eviction (oldest buffer)
                idx = findOldestBuffer(current_ms);
            }
            // Initialize new buffer
            _buffers[idx].clearAll();
            _buffers[idx].setKey(key);
        }

        // Add page to buffer
        if (_buffers[idx].addPage(page_num, total_pages, text_data, current_ms)) {
            if (_buffers[idx].isComplete()) {
                return &_buffers[idx];
            }
        }

        return nullptr;
    }

    NankaiPageBuffer* getBuffer(const NankaiPageKey& key) {
        int8_t idx = findBuffer(key);
        return (idx >= 0) ? &_buffers[idx] : nullptr;
    }

    const NankaiPageBuffer* getBuffer(const NankaiPageKey& key) const {
        int8_t idx = findBuffer(key);
        return (idx >= 0) ? &_buffers[idx] : nullptr;
    }

    // Clear all buffers
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
            // Empty buffers have age 0 and are picked only if nothing is older
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
