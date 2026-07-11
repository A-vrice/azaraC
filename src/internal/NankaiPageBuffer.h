#pragma once
// azaraC - src/internal/NankaiPageBuffer.h
// Nankai Trough Earthquake multi-page aggregation buffer

#include <cstdint>
#include <cstring>
#include <climits>
#include "TimeFields.h"

namespace azaraC {
namespace internal {

// ---------------------------------------------------------------------------
// NankaiPageKey - Event identifier for page aggregation
// ---------------------------------------------------------------------------
// Note: svid is NOT included in the key because QZSS multiple satellites
// may relay the same message. Using svid would cause duplicate buffers
// for the same event.
// ---------------------------------------------------------------------------
struct NankaiPageKey {
    uint8_t  info_code;        // Information Serial Code (4 bits)
    uint32_t event_time_unix;  // Event time as UNIX timestamp

    bool operator==(const NankaiPageKey& o) const {
        return info_code == o.info_code &&
               event_time_unix == o.event_time_unix;
    }

    bool operator!=(const NankaiPageKey& o) const {
        return !(*this == o);
    }

    bool isValid() const {
        return event_time_unix != 0;
    }

    void clear() {
        info_code = 0;
        event_time_unix = 0;
    }
};

// ---------------------------------------------------------------------------
// NankaiPageBuffer - Page aggregation buffer for single event
// ---------------------------------------------------------------------------
// Specification: Pn/Pm range is 1-63 (6 bits)
// ---------------------------------------------------------------------------
// Memory optimization: AZARAC_NANKAI_MAX_PAGES controls the maximum number of
// pages that can be buffered per event. Default: 12 (covers >99% of messages).
// Original max: 63.  Reducing saves ~19 bytes per unused slot.
// Set AZARAC_NANKAI_MAX_PAGES 63 before including azaraC.h for full spec coverage.
// ---------------------------------------------------------------------------
#ifndef AZARAC_NANKAI_MAX_PAGES
#define AZARAC_NANKAI_MAX_PAGES 12
#endif

struct NankaiPageBuffer {
    static constexpr uint8_t MAX_PAGES = AZARAC_NANKAI_MAX_PAGES;
    static constexpr uint8_t SPEC_MAX_PAGES = 63;  // Official maximum (6 bits)
    static_assert(MAX_PAGES > 0 && MAX_PAGES <= SPEC_MAX_PAGES,
                  "AZARAC_NANKAI_MAX_PAGES must be in range 1-63");
    static constexpr uint8_t TEXT_PER_PAGE = 18;
    static constexpr uint32_t TIMEOUT_MS = 60000;  // 60 seconds timeout

    // Page data structure
    struct PageData {
        uint8_t page_num;       // 1-based page number
        uint8_t text[TEXT_PER_PAGE];  // 18 bytes of text data

        // Sort by page_num for ordered output
        bool operator<(const PageData& other) const {
            return page_num < other.page_num;
        }
    };

    NankaiPageKey key;
    uint8_t total_pages = 0;
    uint8_t received_pages = 0;
    uint64_t last_update_ms = 0;

    // Sparse array: only first [received_pages] entries are valid.
    // Size is limited by AZARAC_NANKAI_MAX_PAGES (default 12, max 63).
    PageData pages[MAX_PAGES] = {};

    NankaiPageBuffer() {
        clearAll();
    }

    // Add a page to buffer
    // page_num: 1-based page number
    // total_pages: total number of pages (from Pm field)
    // text_data: pointer to 18 bytes of text data
    // current_ms: current timestamp in milliseconds (for consistent time source)
    // Returns true if page was added successfully
    bool addPage(uint8_t page_num, uint8_t total_pages, const uint8_t* text_data, uint64_t current_ms) {
        // total_pages must not exceed buffer capacity (check before mutating state)
        if (total_pages > MAX_PAGES) {
            return false;
        }

        // Set total_pages on first call
        if (this->total_pages == 0) {
            this->total_pages = total_pages;
        }

        // total_pages must match
        if (this->total_pages != total_pages) {
            return false;
        }

        // Page number range check (1-63 per spec)
        if (page_num == 0 || page_num > SPEC_MAX_PAGES || page_num > total_pages) {
            return false;
        }

        // Skip if already received (duplicate check)
        if (isPageReceived(page_num)) {
            return false;
        }

        // Add page data to sparse array
        if (received_pages < MAX_PAGES) {
            pages[received_pages].page_num = page_num;
            memcpy(pages[received_pages].text, text_data, TEXT_PER_PAGE);
            received_pages++;
            last_update_ms = current_ms;

            // Keep pages sorted by page_num for ordered output
            // Simple insertion sort (received_pages is small, typically < 10)
            for (uint8_t i = received_pages - 1; i > 0; --i) {
                if (pages[i] < pages[i - 1]) {
                    PageData tmp = pages[i];
                    pages[i] = pages[i - 1];
                    pages[i - 1] = tmp;
                } else {
                    break;
                }
            }

            return true;
        }

        return false;
    }

    // Check if a specific page has been received
    bool isPageReceived(uint8_t page_num) const {
        for (uint8_t i = 0; i < received_pages; ++i) {
            if (pages[i].page_num == page_num) {
                return true;
            }
        }
        return false;
    }

    // Check if all pages have been received
    bool isComplete() const {
        if (total_pages == 0) return false;
        return received_pages >= total_pages;
    }

    // Get text length (excluding null terminator)
    // Stops at first 0x00 byte in each page (UTF-8 text contains no NUL bytes)
    uint16_t getTextLength() const {
        uint16_t len = 0;

        for (uint8_t i = 0; i < received_pages; ++i) {
            for (uint8_t j = 0; j < TEXT_PER_PAGE; ++j) {
                if (pages[i].text[j] == 0) {
                    break;
                }
                len++;
            }
        }

        return len;
    }

    // Get combined text as string
    // Stops at first 0x00 byte in each page (null terminator)
    // Pages are output in order (sorted by page_num)
    void getText(char* out, uint16_t max_len) const {
        if (!out || max_len == 0) return;

        uint16_t len = getTextLength();
        uint16_t copy_len = (len < max_len - 1) ? len : (max_len - 1);

        uint16_t pos = 0;
        for (uint8_t i = 0; i < received_pages && pos < copy_len; ++i) {
            uint8_t page_len = 0;
            // Compute valid byte count for this page (up to NUL or TEXT_PER_PAGE)
            while (page_len < TEXT_PER_PAGE && pages[i].text[page_len] != 0) {
                ++page_len;
            }
            uint8_t to_copy = (page_len < (copy_len - pos)) ? page_len : (copy_len - pos);
            if (to_copy > 0) {
                memcpy(out + pos, pages[i].text, to_copy);
                pos += to_copy;
            }
        }

        out[pos] = '\0';  // Null terminate
    }

    // Check if buffer has expired (timeout)
    // Uses uint64_t for overflow-safe time handling
    bool isExpired(uint64_t current_ms) const {
        if (total_pages == 0) return false;
        return (current_ms - last_update_ms) > TIMEOUT_MS;
    }

    // Clear buffer for reuse
    void clear() {
        key.clear();
        total_pages = 0;
        received_pages = 0;
        last_update_ms = 0;
        // No need to clear pages[] - received_pages marks valid data
    }

    // Clear entire buffer including key
    void clearAll() {
        clear();
        key.clear();
    }

    // Check if buffer is empty (no pages received)
    bool isEmpty() const {
        return total_pages == 0;
    }

    // Check if buffer matches given key
    bool matchesKey(const NankaiPageKey& k) const {
        return key == k;
    }

    // Set key for this buffer
    void setKey(const NankaiPageKey& k) {
        key = k;
    }
};

// ---------------------------------------------------------------------------
// NankaiPageBufferManager - Manages multiple page buffers
// ---------------------------------------------------------------------------
// Memory-efficient design:
// - Uses sparse page storage (only received pages stored)
// - LRU eviction when all buffers are full
// - Configurable buffer count via AZARAC_NANKAI_BUFFERS
// ---------------------------------------------------------------------------

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

    // Add a page to appropriate buffer
    // Returns pointer to completed buffer if all pages received, nullptr otherwise
    NankaiPageBuffer* addPage(const NankaiPageKey& key, uint8_t page_num,
                               uint8_t total_pages, const uint8_t* text_data,
                               uint64_t current_ms) {
        // Expire old buffers
        expireBuffers(current_ms);

        // Find existing buffer for this key
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
            // Check if complete
            if (_buffers[idx].isComplete()) {
                return &_buffers[idx];
            }
        }

        return nullptr;
    }

    // Get buffer for given key
    NankaiPageBuffer* getBuffer(const NankaiPageKey& key) {
        int8_t idx = findBuffer(key);
        return (idx >= 0) ? &_buffers[idx] : nullptr;
    }

    // Get buffer for given key (const version)
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

    // Get count of active (non-empty) buffers
    uint8_t getActiveCount() const {
        uint8_t count = 0;
        for (uint8_t i = 0; i < MAX_BUFFERS; ++i) {
            if (!_buffers[i].isEmpty()) {
                count++;
            }
        }
        return count;
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

    // LRU eviction: find the oldest buffer by age relative to current_ms
    // Uses wrap-aware elapsed computation (unsigned subtraction) so correct
    // across millis() rollover.
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
