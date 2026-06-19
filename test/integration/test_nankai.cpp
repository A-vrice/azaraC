// test/integration/test_nankai.cpp — 南海トラフ複数ページテスト
// Nankai Trough multi-page aggregation の統合テスト

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

TEST_CASE("NankaiPageKey equality") {
    NankaiPageKey key1 = {1, 1234567890};
    NankaiPageKey key2 = {1, 1234567890};
    NankaiPageKey key3 = {2, 1234567890};
    NankaiPageKey key4 = {1, 987654321u};
    
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
    }
    
    SUBCASE("Add first page sets total_pages") {
        uint8_t text[18] = {'H', 'e', 'l', 'l', 'o', 0};
        bool result = buffer.addPage(1, 3, text, now);
        
        CHECK(result);
        CHECK(buffer.total_pages == 3);
        CHECK(buffer.received_pages == 1);
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
        CHECK(buffer.received_pages == 3);
    }
    
    SUBCASE("Duplicate page is rejected") {
        uint8_t text[18] = {'T', 'e', 's', 't', 0};
        
        buffer.addPage(1, 2, text, now);
        bool result = buffer.addPage(1, 2, text, now);
        
        CHECK(!result);
        CHECK(buffer.received_pages == 1);
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
}

TEST_CASE("NankaiPageBuffer clear") {
    NankaiPageBuffer buffer;
    uint32_t now = currentMillis();
    
    SUBCASE("Clear resets buffer") {
        uint8_t text[18] = {'T', 'e', 's', 't', 0};
        buffer.addPage(1, 1, text, now);
        
        CHECK(buffer.isComplete());
        
        buffer.clear();
        
        CHECK(buffer.isEmpty());
        CHECK(buffer.total_pages == 0);
        CHECK(!buffer.isComplete());
    }
}

TEST_CASE("NankaiPageBufferManager") {
    NankaiPageBufferManager manager;
    
    SUBCASE("Add page to new buffer") {
        NankaiPageKey key = {1, 1234567890};
        uint8_t text[18] = {'T', 'e', 's', 't', 0};
        
        NankaiPageBuffer* result = manager.addPage(key, 1, 1, text, currentMillis());
        
        CHECK(result != nullptr);
    }
    
    SUBCASE("Add page to existing buffer") {
        NankaiPageKey key = {1, 1234567890};
        uint8_t text1[18] = {'P', '1', 0};
        uint8_t text2[18] = {'P', '2', 0};
        
        NankaiPageBuffer* result1 = manager.addPage(key, 1, 2, text1, currentMillis());
        CHECK(result1 == nullptr);
        
        NankaiPageBuffer* result2 = manager.addPage(key, 2, 2, text2, currentMillis());
        CHECK(result2 != nullptr);
    }
    
    SUBCASE("Multiple events") {
        NankaiPageKey key1 = {1, 1234567890};
        NankaiPageKey key2 = {2, 1234567890};
        uint8_t text[18] = {'T', 'e', 's', 't', 0};
        
        manager.addPage(key1, 1, 1, text, currentMillis());
        manager.addPage(key2, 1, 1, text, currentMillis());
        
        CHECK(manager.getBuffer(key1) != nullptr);
        CHECK(manager.getBuffer(key2) != nullptr);
    }
    
    SUBCASE("Clear all buffers") {
        NankaiPageKey key = {1, 1234567890};
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
            NankaiPageKey key = {i, 1234567890};
            uint8_t text[18] = {'T', 'e', 's', 't', 0};
            manager.addPage(key, 1, 1, text, now);
        }
        
        // Adding one more should evict the oldest
        NankaiPageKey key_new = {NankaiPageBufferManager::MAX_BUFFERS, 1234567890};
        uint8_t text[18] = {'N', 'e', 'w', 0};
        manager.addPage(key_new, 1, 1, text, now);
        
        // Oldest buffer (key 0) should be evicted
        NankaiPageKey key0 = {0, 1234567890};
        CHECK(manager.getBuffer(key0) == nullptr);
        
        // New buffer should exist
        CHECK(manager.getBuffer(key_new) != nullptr);
    }
    
    SUBCASE("Active count tracks buffer usage") {
        uint32_t now = currentMillis();
        CHECK(manager.getActiveCount() == 0);
        
        for (uint8_t i = 0; i < 3; i++) {
            NankaiPageKey key = {i, 1234567890};
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

TEST_CASE("Parser Nankai duplicate suppression in AUTO mode") {
    azaraC::Parser parser;
    azaraC::Message msg;
    
    // Construct a 1-page Nankai Trough message manually
    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);       // Preamble
    setBits(bits, 8, 6, 43);         // msg_type
    setBits(bits, 14, 3, 1);         // report_classification
    setBits(bits, 17, 4, 4);         // disaster_category = 4 (Nankai Trough)
    setBits(bits, 25, 16, 0);        // event_time
    setBits(bits, 41, 2, 0);         // information_type
    setBits(bits, 53, 4, 1);         // info_code
    // Text: 18 bytes (all zeros is fine)
    setBits(bits, 201, 6, 1);        // page = 1
    setBits(bits, 207, 6, 1);        // total_page = 1
    setBits(bits, 214, 6, 1);        // version = 1
    
    uint32_t crc = crc24qRef(bits, 226);
    setBits(bits, 226, 24, crc);
    
    std::string nmea = makeNmeaQzqsm(58, bits);
    
    bool output1 = false;
    for (size_t i = 0; i < nmea.length(); i++) {
        if (parser.feed(nmea[i], msg, 0)) {
            output1 = true;
            break;
        }
    }
    
    CHECK(output1 == true);
    CHECK(msg.valid == true);
    CHECK(msg.payload_type == azaraC::MsgPayloadType::Mt43);
    CHECK(msg.mt43.disaster_category == 4);
    
    // Feed the exact same message again, it should be suppressed
    bool output2 = false;
    for (size_t i = 0; i < nmea.length(); i++) {
        if (parser.feed(nmea[i], msg, 0)) {
            output2 = true;
            break;
        }
    }
    
    CHECK(output2 == false); // Should be suppressed!
}
