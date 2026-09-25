// test/integration/test_nankai.cpp — 南海トラフ単体テスト
// E2E テストは test_nankai_e2e.cpp に分離済み

#include <string>
#include <chrono>
#include "doctest.h"
#include "../src/internal/NankaiPageBuffer.h"
#include "../src/Parser.h"
#include "../test_helpers.h"

using namespace azaraC::internal;

// Helper to get current time in milliseconds (non-Arduino)
static uint32_t currentMillis() {
    auto now = std::chrono::steady_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch()).count();
    return static_cast<uint32_t>(ms);
}

#if (AZARAC_ENABLE_NANKAI)
TEST_CASE("NankaiPageKey equality") {
    // Identity = info_code + report_time DHM (month/day/hour/minute).
    NankaiPageKey key1 = {1, 4, 10, 30, 15};
    NankaiPageKey key2 = {1, 4, 10, 30, 15};
    NankaiPageKey key3 = {2, 4, 10, 30, 15};  // different info_code
    NankaiPageKey key4 = {1, 4, 10, 30, 16};  // different minute
    NankaiPageKey key5 = {1, 5, 10, 30, 15};  // different month

    SUBCASE("Same keys are equal") {
        CHECK(key1 == key2);
    }

    SUBCASE("Different info_code") {
        CHECK(!(key1 == key3));
    }

    SUBCASE("Different report_time") {
        CHECK(!(key1 == key4));
        CHECK(!(key1 == key5));
    }

    SUBCASE("Identity depends only on report_time, not resolution") {
        // The key carries no resolved UNIX time, so the same message yields the
        // same key whether or not report_unix is available.
        NankaiPageKey from_unresolved = {1, 4, 10, 30, 15};
        NankaiPageKey from_resolved   = {1, 4, 10, 30, 15};
        CHECK(from_resolved == from_unresolved);
    }
}

TEST_CASE("NankaiPageBuffer basic operations") {
    NankaiPageBuffer buffer;
    uint32_t now = currentMillis();
    
    SUBCASE("Initial state") {
        CHECK(buffer.isEmpty());
        CHECK(!buffer.isComplete());
        CHECK(buffer.total_pages == 0);
        CHECK(buffer.received_bitmap == 0);
        CHECK(buffer.received_count == 0);
        CHECK_FALSE(buffer.truncated);
    }
    
    SUBCASE("Add first page sets total_pages") {
        uint8_t text[18] = {'H', 'e', 'l', 'l', 'o', 0};
        bool result = buffer.addPage(1, 3, text, now);
        
        CHECK(result);
        CHECK(buffer.total_pages == 3);
        CHECK(buffer.received_count == 1);
        CHECK(buffer.received_bitmap == (1ULL << 0));  // bit 0 = page 1
        CHECK(!buffer.isComplete());
    }
    
    SUBCASE("Add all pages completes buffer") {
        uint8_t text1[18] = {'P', 'a', 'g', 'e', '1', 0};
        uint8_t text2[18] = {'P', 'a', 'g', 'e', '2', 0};
        uint8_t text3[18] = {'P', 'a', 'g', 'e', '3', 0};
        
        buffer.addPage(1, 3, text1, now);
        buffer.addPage(2, 3, text2, now);
        bool result = buffer.addPage(3, 3, text3, now);
        
        CHECK(result);
        CHECK(buffer.isComplete());
        CHECK(buffer.received_count == 3);
        // bits 0,1,2 = pages 1,2,3
        CHECK(buffer.received_bitmap == 0x7ULL);
    }
    
    SUBCASE("Duplicate page is rejected") {
        uint8_t text[18] = {'T', 'e', 's', 't', 0};
        
        buffer.addPage(1, 2, text, now);
        bool result = buffer.addPage(1, 2, text, now);
        
        CHECK(!result);
        CHECK(buffer.received_count == 1);
        // Bitmap still has only bit 0 set
        CHECK(buffer.received_bitmap == (1ULL << 0));
    }
    
    SUBCASE("Invalid page number is rejected") {
        uint8_t text[18] = {'T', 'e', 's', 't', 0};
        
        bool result0 = buffer.addPage(0, 2, text, now);
        bool result3 = buffer.addPage(3, 2, text, now);
        
        CHECK(!result0);
        CHECK(!result3);
    }
    
    SUBCASE("Mismatched total_pages is rejected") {
        uint8_t text[18] = {'T', 'e', 's', 't', 0};

        buffer.addPage(1, 3, text, now);
        bool result = buffer.addPage(2, 2, text, now);

        CHECK(!result);
    }
}

TEST_CASE("NankaiPageBuffer truncation") {
    // When total_pages > MAX_PAGES, the buffer caps to MAX_PAGES
    // and sets the truncated flag.
    // MAX_PAGES = NankaiPageBuffer::MAX_PAGES (library default, overridable).
    // Since SPEC_MAX_PAGES=63, total_pages values above 63 are the only way to
    // exceed a MAX_PAGES=63 build; page_num must stay <= SPEC_MAX_PAGES.
    NankaiPageBuffer buffer;
    uint32_t now = currentMillis();
    
    SUBCASE("total_pages > MAX_PAGES sets truncated flag") {
        uint8_t text[18] = {'T', 'e', 's', 't', 0};
        
        // total_pages=99, capped to MAX_PAGES
        bool result = buffer.addPage(1, 99, text, now);
        
        CHECK(result);
        CHECK(buffer.truncated);
        CHECK(buffer.total_pages == NankaiPageBuffer::MAX_PAGES);  // capped
        CHECK(buffer.original_total_pages == 99);  // original preserved
    }
    
    SUBCASE("Truncated buffer completes when MAX_PAGES pages received") {
        uint8_t text[18] = {'T', 'e', 's', 't', 0};
        
        // total_pages=99, cap to MAX_PAGES
        buffer.addPage(1, 99, text, now);
        CHECK_FALSE(buffer.isComplete());
        
        // Fill pages 2..MAX_PAGES
        for (uint8_t p = 2; p <= NankaiPageBuffer::MAX_PAGES; ++p) {
            buffer.addPage(p, 99, text, now);
        }
        
        CHECK(buffer.isComplete());
        CHECK(buffer.truncated);
        CHECK(buffer.received_count == NankaiPageBuffer::MAX_PAGES);
    }
    
    SUBCASE("Page beyond truncated limit is rejected") {
        uint8_t text[18] = {'T', 'e', 's', 't', 0};
        
        buffer.addPage(1, 99, text, now);
        // MAX_PAGES 超のページ番号は effective_total (= MAX_PAGES) で拒否され、
        // SPEC_MAX_PAGES=63 を超える値は先に範囲チェックで拒否される。
        bool result = buffer.addPage(static_cast<uint8_t>(NankaiPageBuffer::MAX_PAGES + 1), 99, text, now);
        
        CHECK_FALSE(result);
    }
    
    SUBCASE("Normal (non-truncated) buffer has truncated=false") {
        uint8_t text[18] = {'T', 'e', 's', 't', 0};
        buffer.addPage(1, 1, text, now);
        CHECK_FALSE(buffer.truncated);
        CHECK(buffer.total_pages == 1);
    }
}

TEST_CASE("NankaiPageBuffer text aggregation") {
    NankaiPageBuffer buffer;
    uint32_t now = currentMillis();

    SUBCASE("Pages received out of order are stored correctly") {
        uint8_t text1[18] = {'P', '1', 0};
        uint8_t text2[18] = {'P', '2', 0};
        uint8_t text3[18] = {'P', '3', 0};
        CHECK(buffer.addPage(3, 3, text3, now));
        CHECK(buffer.addPage(1, 3, text1, now));
        CHECK(buffer.addPage(2, 3, text2, now));
        CHECK(buffer.isComplete());
        CHECK(buffer.getTextLength() == 6);
        CHECK(memcmp(buffer.aggregated_text + 0 * 18, "P1", 2) == 0);
        CHECK(memcmp(buffer.aggregated_text + 1 * 18, "P2", 2) == 0);
        CHECK(memcmp(buffer.aggregated_text + 2 * 18, "P3", 2) == 0);
    }

    SUBCASE("Null byte terminates page length") {
        uint8_t text[18] = {'A', 'B', 0, 'C', 'D', 0};
        buffer.addPage(1, 1, text, now);
        CHECK(buffer.getTextLength() == 2);
        CHECK(buffer.aggregated_text[0] == 'A');
        CHECK(buffer.aggregated_text[1] == 'B');
    }
}



TEST_CASE("NankaiPageBufferManager") {
    NankaiPageBufferManager manager;
    
    SUBCASE("Add page to new buffer") {
        NankaiPageKey key = {1};
        uint8_t text[18] = {'T', 'e', 's', 't', 0};
        
        NankaiPageBuffer* result = manager.addPage(key, 1, 1, text, currentMillis());
        
        CHECK(result != nullptr);
    }
    
    SUBCASE("Add page to existing buffer") {
        NankaiPageKey key = {1};
        uint8_t text1[18] = {'P', '1', 0};
        uint8_t text2[18] = {'P', '2', 0};
        
        NankaiPageBuffer* result1 = manager.addPage(key, 1, 2, text1, currentMillis());
        CHECK(result1 == nullptr);
        
        NankaiPageBuffer* result2 = manager.addPage(key, 2, 2, text2, currentMillis());
        CHECK(result2 != nullptr);
    }
    
#if AZARAC_NANKAI_BUFFERS >= 2
    SUBCASE("Multiple events") {
        NankaiPageKey key1 = {1};
        NankaiPageKey key2 = {2};
        uint8_t text[18] = {'T', 'e', 's', 't', 0};
        
        manager.addPage(key1, 1, 1, text, currentMillis());
        manager.addPage(key2, 1, 1, text, currentMillis());
        
        CHECK(manager.getBuffer(key1) != nullptr);
        CHECK(manager.getBuffer(key2) != nullptr);
    }
#endif // AZARAC_NANKAI_BUFFERS >= 2
    
    SUBCASE("Clear all buffers") {
        NankaiPageKey key = {1};
        uint8_t text[18] = {'T', 'e', 's', 't', 0};
        
        manager.addPage(key, 1, 1, text, currentMillis());
        manager.clearAll();
        
        CHECK(manager.getBuffer(key) == nullptr);
    }
}

TEST_CASE("NankaiPageBufferManager buffer limit") {
    NankaiPageBufferManager manager;
    
    SUBCASE("Max buffers is configurable") {
        uint32_t now = currentMillis();
        // Fill all buffers
        for (uint8_t i = 0; i < NankaiPageBufferManager::MAX_BUFFERS; i++) {
            NankaiPageKey key = {static_cast<uint8_t>(i + 1)};
            uint8_t text[18] = {'T', 'e', 's', 't', 0};
            manager.addPage(key, 1, 1, text, now);
        }
        
        // Adding one more should evict the oldest
        NankaiPageKey key_new = {static_cast<uint8_t>(NankaiPageBufferManager::MAX_BUFFERS + 1)};
        uint8_t text[18] = {'N', 'e', 'w', 0};
        manager.addPage(key_new, 1, 1, text, now);
        
        // Oldest buffer (first inserted key) should be evicted
        NankaiPageKey key0 = {1};
        CHECK(manager.getBuffer(key0) == nullptr);
        
        // New buffer should exist
        CHECK(manager.getBuffer(key_new) != nullptr);
    }
}

// ゼロ鍵が空スロットに誤マッチしないこと

TEST_CASE("NankaiPageBufferManager empty slots never match") {
    NankaiPageBufferManager manager;
    NankaiPageKey zero;  // all-zero identity

    // Empty slots hold an all-zero key; getBuffer must not return one.
    CHECK(manager.getBuffer(zero) == nullptr);

    uint8_t text[18] = {'T', 'e', 's', 't', 0};
    manager.addPage(zero, 1, 2, text, 1000);
    CHECK(manager.getBuffer(zero) != nullptr);
    // The same zero-key event continues in its buffer, not a fresh empty slot.
    CHECK(manager.addPage(zero, 2, 2, text, 1000) != nullptr);
}

// 失効（TIMEOUT_MS）と LRU の区別

TEST_CASE("NankaiPageBuffer expiry") {
    SUBCASE("isExpired boundary") {
        NankaiPageBuffer buffer;
        uint8_t text[18] = {'P', 0};
        buffer.addPage(1, 2, text, 1000);
        CHECK_FALSE(buffer.isExpired(1000 + NankaiPageBuffer::TIMEOUT_MS));
        CHECK(buffer.isExpired(1000 + NankaiPageBuffer::TIMEOUT_MS + 1));
    }

    SUBCASE("expireBuffers drops a stale buffer") {
        NankaiPageBufferManager manager;
        NankaiPageKey key = {1, 4, 10, 30, 15};
        uint8_t text[18] = {'P', 0};
        manager.addPage(key, 1, 2, text, 1000);
        CHECK(manager.getBuffer(key) != nullptr);

        // Touching the manager past the timeout expires the stale buffer.
        manager.addPage({2, 4, 10, 30, 15}, 1, 1, text,
                        1000 + NankaiPageBuffer::TIMEOUT_MS + 1);
        CHECK(manager.getBuffer(key) == nullptr);
    }
}

#if AZARAC_NANKAI_BUFFERS >= 2
TEST_CASE("NankaiPageBufferManager expiry is not LRU eviction") {
    NankaiPageBufferManager manager;
    NankaiPageKey k1 = {1, 4, 10, 30, 15};
    NankaiPageKey k2 = {2, 4, 10, 30, 15};
    uint8_t text[18] = {'P', 0};
    manager.addPage(k1, 1, 2, text, 1000);
    manager.addPage(k2, 1, 2, text, 1000);
    // Both buffers are equally old: past the timeout both must expire, whereas a
    // single LRU eviction would drop only one.
    manager.addPage({3, 4, 10, 30, 15}, 1, 1, text,
                    1000 + NankaiPageBuffer::TIMEOUT_MS + 1);
    CHECK(manager.getBuffer(k1) == nullptr);
    CHECK(manager.getBuffer(k2) == nullptr);
}

TEST_CASE("NankaiPageBufferManager: zero key follows its buffer across slot reuse") {
    NankaiPageBufferManager manager;
    uint8_t text[18] = {'T', 'e', 's', 't', 0};
    NankaiPageKey nonzero = {7, 6, 15, 12, 30};
    NankaiPageKey zero;  // all-zero identity

    CHECK(manager.addPage(nonzero, 1, 2, text, 0) == nullptr);        // slot 0 (stale later)
    CHECK(manager.addPage(zero, 1, 2, text, 30000) == nullptr);       // slot 1

    // At t=70000 slot 0 expires; a zero-key page must continue in its own buffer
    // (slot 1), not bind to the freshly emptied slot 0.
    NankaiPageBuffer* done = manager.addPage(zero, 2, 2, text, 70000);
    CHECK(done != nullptr);
}
#endif // AZARAC_NANKAI_BUFFERS >= 2

#endif // AZARAC_ENABLE_NANKAI
