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
    NankaiPageKey key1 = {1234567890, 1};
    NankaiPageKey key2 = {1234567890, 1};
    NankaiPageKey key3 = {1234567890, 2};
    NankaiPageKey key4 = {987654321u, 1};
    
    SUBCASE("Same keys are equal") {
        CHECK(key1 == key2);
    }
    
    SUBCASE("Different info_code") {
        CHECK(key1 != key3);
    }
    
    SUBCASE("Different event_time") {
        CHECK(key1 != key4);
    }
    
    SUBCASE("Invalid key") {
        NankaiPageKey invalid = {0, 0};
        CHECK(!invalid.isValid());
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

    SUBCASE("Pages received out of order are stored correctly") {
        uint8_t text1[18] = {'P', '1', 0};
        uint8_t text2[18] = {'P', '2', 0};
        uint8_t text3[18] = {'P', '3', 0};
        
        // Add pages in reverse order
        CHECK(buffer.addPage(3, 3, text3, now));
        CHECK(buffer.addPage(1, 3, text1, now));
        CHECK(buffer.addPage(2, 3, text2, now));
        
        CHECK(buffer.isComplete());
        
        // getText should return them in page order (1, 2, 3)
        char result[256];
        buffer.getText(result, sizeof(result));
        CHECK(std::string(result) == "P1P2P3");
    }
}

TEST_CASE("NankaiPageBuffer truncation") {
    // When total_pages > MAX_PAGES, the buffer caps to MAX_PAGES
    // and sets the truncated flag.
    // With the test Makefile default MAX_PAGES=63, we need total_pages > 63.
    // Since SPEC_MAX_PAGES=63, we can only test with total_pages values
    // between 64 and 255 (uint8_t max) where page_num is still <= 63.
    NankaiPageBuffer buffer;
    uint32_t now = currentMillis();
    
    SUBCASE("total_pages > MAX_PAGES sets truncated flag") {
        uint8_t text[18] = {'T', 'e', 's', 't', 0};
        
        // total_pages=99, MAX_PAGES=63 (test default)
        bool result = buffer.addPage(1, 99, text, now);
        
        CHECK(result);
        CHECK(buffer.truncated);
        CHECK(buffer.total_pages == NankaiPageBuffer::MAX_PAGES);  // capped to 63
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
        // MAX_PAGES=63, so page 64 should be rejected
        bool result = buffer.addPage(64, 99, text, now);
        
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
    
    SUBCASE("Single page text") {
        uint8_t text[18] = {'H', 'e', 'l', 'l', 'o', 0};
        buffer.addPage(1, 1, text, now);
        
        CHECK(buffer.isComplete());
        CHECK(buffer.getTextLength() == 5);
        
        char result[256];
        buffer.getText(result, sizeof(result));
        CHECK(std::string(result) == "Hello");
    }
    
    SUBCASE("Multi-page text concatenation") {
        uint8_t text1[18] = {'P', 'a', 'g', 'e', '1', ' ', 0};
        uint8_t text2[18] = {'P', 'a', 'g', 'e', '2', 0};
        
        buffer.addPage(1, 2, text1, now);
        buffer.addPage(2, 2, text2, now);
        
        CHECK(buffer.isComplete());
        
        char result[256];
        buffer.getText(result, sizeof(result));
        CHECK(std::string(result) == "Page1 Page2");
    }
    
    SUBCASE("Null byte terminates page") {
        uint8_t text[18] = {'A', 'B', 0, 'C', 'D', 0};
        buffer.addPage(1, 1, text, now);
        
        CHECK(buffer.getTextLength() == 2);
        
        char result[256];
        buffer.getText(result, sizeof(result));
        CHECK(std::string(result) == "AB");
    }
    
    SUBCASE("Empty page handling") {
        uint8_t text1[18] = {'A', 'B', 0};
        uint8_t text2[18] = {0};
        uint8_t text3[18] = {'C', 'D', 0};
        
        buffer.addPage(1, 3, text1, now);
        buffer.addPage(2, 3, text2, now);
        buffer.addPage(3, 3, text3, now);
        
        char result[256];
        buffer.getText(result, sizeof(result));
        CHECK(std::string(result) == "ABCD");
    }

    SUBCASE("getText stops at max_len boundary") {
        uint8_t text1[18] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
                             'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R'};
        uint8_t text2[18] = {'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 0};

        buffer.addPage(1, 2, text1, now);
        buffer.addPage(2, 2, text2, now);
        CHECK(buffer.isComplete());

        char result_small[10];
        buffer.getText(result_small, sizeof(result_small));
        CHECK(std::string(result_small).length() <= 9);
        CHECK(result_small[9] == '\0');
    }
}

TEST_CASE("NankaiPageBufferManager") {
    NankaiPageBufferManager manager;
    
    SUBCASE("Add page to new buffer") {
        NankaiPageKey key = {1234567890, 1};
        uint8_t text[18] = {'T', 'e', 's', 't', 0};
        
        NankaiPageBuffer* result = manager.addPage(key, 1, 1, text, currentMillis());
        
        CHECK(result != nullptr);
    }
    
    SUBCASE("Add page to existing buffer") {
        NankaiPageKey key = {1234567890, 1};
        uint8_t text1[18] = {'P', '1', 0};
        uint8_t text2[18] = {'P', '2', 0};
        
        NankaiPageBuffer* result1 = manager.addPage(key, 1, 2, text1, currentMillis());
        CHECK(result1 == nullptr);
        
        NankaiPageBuffer* result2 = manager.addPage(key, 2, 2, text2, currentMillis());
        CHECK(result2 != nullptr);
    }
    
    SUBCASE("Multiple events") {
        NankaiPageKey key1 = {1234567890, 1};
        NankaiPageKey key2 = {1234567890, 2};
        uint8_t text[18] = {'T', 'e', 's', 't', 0};
        
        manager.addPage(key1, 1, 1, text, currentMillis());
        manager.addPage(key2, 1, 1, text, currentMillis());
        
        CHECK(manager.getBuffer(key1) != nullptr);
        CHECK(manager.getBuffer(key2) != nullptr);
    }
    
    SUBCASE("Clear all buffers") {
        NankaiPageKey key = {1234567890, 1};
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
            NankaiPageKey key = {1234567890, i};
            uint8_t text[18] = {'T', 'e', 's', 't', 0};
            manager.addPage(key, 1, 1, text, now);
        }
        
        // Adding one more should evict the oldest
        NankaiPageKey key_new = {1234567890, NankaiPageBufferManager::MAX_BUFFERS};
        uint8_t text[18] = {'N', 'e', 'w', 0};
        manager.addPage(key_new, 1, 1, text, now);
        
        // Oldest buffer (key 0) should be evicted
        NankaiPageKey key0 = {1234567890, 0};
        CHECK(manager.getBuffer(key0) == nullptr);
        
        // New buffer should exist
        CHECK(manager.getBuffer(key_new) != nullptr);
    }
    
    SUBCASE("Active count tracks buffer usage") {
        uint32_t now = currentMillis();
        CHECK(manager.getActiveCount() == 0);
        
        for (uint8_t i = 0; i < 3; i++) {
            NankaiPageKey key = {1234567890, i};
            uint8_t text[18] = {'T', 'e', 's', 't', 0};
            manager.addPage(key, 1, 1, text, now);
            CHECK(manager.getActiveCount() == (i + 1));
        }
        
        manager.clearAll();
        CHECK(manager.getActiveCount() == 0);
    }
}

TEST_CASE("UTF-8 text handling") {
    NankaiPageBuffer buffer;
    uint32_t now = currentMillis();
    
    SUBCASE("Japanese text") {
        uint8_t text[18] = {
            0xE3, 0x81, 0x93,  // こ
            0xE3, 0x82, 0x93,  // ん
            0xE3, 0x81, 0xAB,  // に
            0xE3, 0x81, 0xA1,  // ち
            0xE3, 0x81, 0xAF,  // は
            0x00
        };
        
        buffer.addPage(1, 1, text, now);
        
        CHECK(buffer.getTextLength() == 15);
        
        char result[256];
        buffer.getText(result, sizeof(result));
        CHECK(std::string(result) == "こんにちは");
    }
    
    SUBCASE("Multi-page Japanese text") {
        uint8_t text1[18] = {
            0xE5, 0x8D, 0x97,  // 南
            0xE6, 0xB5, 0xB7,  // 海
            0xE3, 0x83, 0x88,  // ト
            0xE3, 0x83, 0xA9,  // ラ
            0x00
        };
        
        uint8_t text2[18] = {
            0xE3, 0x83, 0x95,  // フ
            0xE5, 0x9C, 0xB0,  // 地
            0xE9, 0x9C, 0x87,  // 震
            0x00
        };
        
        buffer.addPage(1, 2, text1, now);
        buffer.addPage(2, 2, text2, now);
        
        char result[256];
        buffer.getText(result, sizeof(result));
        CHECK(std::string(result) == "南海トラフ地震");
    }
}
#endif // AZARAC_ENABLE_NANKAI
