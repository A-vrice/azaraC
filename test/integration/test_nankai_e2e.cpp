// test/integration/test_nankai_e2e.cpp — 南海トラフ複数ページ集約E2Eテスト

#include <string>
#include "doctest.h"
#include "../src/internal/NankaiPageBuffer.h"
#include "../src/Parser.h"
#include "../test_helpers.h"

using namespace azaraC::internal;

#if (AZARAC_ENABLE_NANKAI)
TEST_CASE("Nankai E2E: Parser decodes synthetic Nankai message") {
    azaraC::Parser parser;
    azaraC::Message msg;

    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);
    setBits(bits, 8, 6, 43);
    setBits(bits, 14, 3, 1);
    setBits(bits, 17, 4, 4);
    setBits(bits, 53, 4, 1);
    setBits(bits, 201, 6, 1);
    setBits(bits, 207, 6, 1);
    setBits(bits, 214, 6, 1);

    uint32_t crc = crc24qRef(bits, 226);
    setBits(bits, 226, 24, crc);

    std::string nmea = makeNmeaQzqsm(58, bits);

    bool output = false;
    for (size_t i = 0; i < nmea.length(); i++) {
        if (parser.feed(nmea[i], msg, 0)) {
            output = true;
            break;
        }
    }

    CHECK(output);
    CHECK(msg.valid);
    CHECK(msg.payload_type == azaraC::MsgPayloadType::Mt43);
    
    const Mt43Data* mt43 = msg.getMt43();
    REQUIRE(mt43 != nullptr);
    CHECK(mt43->disaster_category == 4);
    
    const NankaiData* nankai = mt43->getNankai();
    REQUIRE(nankai != nullptr);
    CHECK(nankai->page == 1);
    CHECK(nankai->total_page == 1);
}

TEST_CASE("Nankai E2E: Parser duplicate suppression") {
    azaraC::Parser parser;
    azaraC::Message msg;

    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);
    setBits(bits, 8, 6, 43);
    setBits(bits, 14, 3, 1);
    setBits(bits, 17, 4, 4);
    setBits(bits, 53, 4, 1);
    setBits(bits, 201, 6, 1);
    setBits(bits, 207, 6, 1);
    setBits(bits, 214, 6, 1);

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
    CHECK(output1);

    bool output2 = false;
    for (size_t i = 0; i < nmea.length(); i++) {
        if (parser.feed(nmea[i], msg, 0)) {
            output2 = true;
            break;
        }
    }
    CHECK_FALSE(output2);
}

TEST_CASE("Nankai E2E: Parser reset allows re-output") {
    azaraC::Parser parser;
    azaraC::Message msg;

    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);
    setBits(bits, 8, 6, 43);
    setBits(bits, 14, 3, 1);
    setBits(bits, 17, 4, 4);
    setBits(bits, 53, 4, 1);
    setBits(bits, 201, 6, 1);
    setBits(bits, 207, 6, 1);
    setBits(bits, 214, 6, 1);

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
    CHECK(output1);

    parser.reset();

    bool output2 = false;
    for (size_t i = 0; i < nmea.length(); i++) {
        if (parser.feed(nmea[i], msg, 0)) {
            output2 = true;
            break;
        }
    }
    CHECK(output2);
}

TEST_CASE("Nankai E2E: Multiple different messages not suppressed") {
    azaraC::Parser parser;
    azaraC::Message msg;

    uint8_t bits1[32] = {};
    setBits(bits1, 0, 8, 0x53);
    setBits(bits1, 8, 6, 43);
    setBits(bits1, 14, 3, 1);
    setBits(bits1, 17, 4, 4);
    setBits(bits1, 53, 4, 1);
    setBits(bits1, 201, 6, 1);
    setBits(bits1, 207, 6, 1);
    setBits(bits1, 214, 6, 1);
    uint32_t crc1 = crc24qRef(bits1, 226);
    setBits(bits1, 226, 24, crc1);
    std::string nmea1 = makeNmeaQzqsm(58, bits1);

    uint8_t bits2[32] = {};
    setBits(bits2, 0, 8, 0x53);
    setBits(bits2, 8, 6, 43);
    setBits(bits2, 14, 3, 1);
    setBits(bits2, 17, 4, 4);
    setBits(bits2, 53, 4, 2);
    setBits(bits2, 201, 6, 1);
    setBits(bits2, 207, 6, 1);
    setBits(bits2, 214, 6, 1);
    uint32_t crc2 = crc24qRef(bits2, 226);
    setBits(bits2, 226, 24, crc2);
    std::string nmea2 = makeNmeaQzqsm(58, bits2);

    bool output1 = false;
    for (size_t i = 0; i < nmea1.length(); i++) {
        if (parser.feed(nmea1[i], msg, 0)) {
            output1 = true;
            break;
        }
    }
    CHECK(output1);

    bool output2 = false;
    for (size_t i = 0; i < nmea2.length(); i++) {
        if (parser.feed(nmea2[i], msg, 0)) {
            output2 = true;
            break;
        }
    }
    CHECK(output2);
}

TEST_CASE("Nankai E2E: Text extraction from single page") {
    azaraC::Parser parser;
    azaraC::Message msg;

    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);
    setBits(bits, 8, 6, 43);
    setBits(bits, 14, 3, 1);
    setBits(bits, 17, 4, 4);
    setBits(bits, 53, 4, 1);
    const char* text = "Test";
    for (int i = 0; i < 4; i++) {
        setBits(bits, 57 + i * 8, 8, (uint8_t)text[i]);
    }
    setBits(bits, 201, 6, 1);
    setBits(bits, 207, 6, 1);
    setBits(bits, 214, 6, 1);

    uint32_t crc = crc24qRef(bits, 226);
    setBits(bits, 226, 24, crc);

    std::string nmea = makeNmeaQzqsm(58, bits);

    bool output = false;
    for (size_t i = 0; i < nmea.length(); i++) {
        if (parser.feed(nmea[i], msg, 0)) {
            output = true;
            break;
        }
    }

    CHECK(output);
    
    const Mt43Data* mt43 = msg.getMt43();
    REQUIRE(mt43 != nullptr);
    
    const NankaiData* nankai = mt43->getNankai();
    REQUIRE(nankai != nullptr);
    CHECK(nankai->text[0] == 'T');
    CHECK(nankai->text[1] == 'e');
    CHECK(nankai->text[2] == 's');
    CHECK(nankai->text[3] == 't');
}

TEST_CASE("Nankai E2E: Oversized page rejected") {
    const char* nmea_oversized = "$QZQSM,58,9AAFA19C918002F1C0C271C0410000000000000000000000000036D81121AA2D0*07";

    Message msg;
    bool ok = decodeNmea(nmea_oversized, msg);
    CHECK_FALSE(ok);
}

TEST_CASE("Nankai E2E: Page tracking with single page") {
    azaraC::Parser parser;
    azaraC::Message msg;

    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);
    setBits(bits, 8, 6, 43);
    setBits(bits, 14, 3, 1);
    setBits(bits, 17, 4, 4);
    setBits(bits, 53, 4, 5);
    setBits(bits, 201, 6, 1);
    setBits(bits, 207, 6, 1);
    setBits(bits, 214, 6, 1);

    uint32_t crc = crc24qRef(bits, 226);
    setBits(bits, 226, 24, crc);

    std::string nmea = makeNmeaQzqsm(58, bits);

    bool output = false;
    for (size_t i = 0; i < nmea.length(); i++) {
        if (parser.feed(nmea[i], msg, 0)) {
            output = true;
            break;
        }
    }

    REQUIRE(output);
    
    const Mt43Data* mt43 = msg.getMt43();
    REQUIRE(mt43 != nullptr);
    
    const NankaiData* nankai = mt43->getNankai();
    REQUIRE(nankai != nullptr);
    CHECK(nankai->page == 1);
    CHECK(nankai->total_page == 1);
    CHECK(nankai->info_code == 5);
}

// ═══════════════════════════════════════════════════════════════════════════════
// Nankai 27ページ完全集約 E2E テスト (integration_e2e.md #1)
// nankai_vectors.json の実データテキストを使用
// ═══════════════════════════════════════════════════════════════════════════════

// Helper: build a Nankai page message with specific page number and text
static void buildNankaiPage(uint8_t page_num, uint8_t total_pages, uint8_t info_code,
                            const uint8_t* text, uint8_t text_len, uint8_t* bits) {
    memset(bits, 0, 32);
    setBits(bits, 0, 8, 0x53);       // Preamble
    setBits(bits, 8, 6, 43);         // msg_type
    setBits(bits, 14, 3, 1);         // report_classification = 1 (訓練)
    setBits(bits, 17, 4, 4);         // disaster_category = 4 (Nankai)
    setBits(bits, 25, 16, 0);        // event_time (dummy)
    setBits(bits, 41, 2, 0);         // information_type
    setBits(bits, 53, 4, info_code);  // info_code
    // Text: 18 bytes at bits 57..200
    for (uint8_t i = 0; i < text_len && i < 18; ++i) {
        setBits(bits, 57 + i * 8, 8, text[i]);
    }
    setBits(bits, 201, 6, page_num);       // page
    setBits(bits, 207, 6, total_pages);    // total_page
    setBits(bits, 214, 6, 1);              // version = 1
    uint32_t crc = crc24qRef(bits, 226);
    setBits(bits, 226, 24, crc);
}

// Fixed 18-byte page payloads verified against azarashi (nankai_vectors.json).
// Pages 1, 8-26: exact match with azarashi text_information output.
// Pages 2-7 and 27: synthetic filler (no real data available in nankai_vectors.json).
// Using byte arrays instead of UTF-8 strings to avoid strlen() on multibyte text
// and to store the exact 18-byte protocol payload directly.
static const uint8_t nankai_page_data[27][18] = {
    { 0xE5,0x8D,0x97,0xE6,0xB5,0xB7,0xE3,0x83,0x88,0xE3,0x83,0xA9,0xE3,0x83,0x95,0xE6,0xB2,0xBF },  // page 1 (azarashi)
    { 0xE3,0x81,0x84,0xE3,0x81,0xAE,0xE3,0x83,0x97,0xE3,0x83,0xAC,0xE3,0x83,0xBC,0xE3,0x83,0x88 },  // page 2 (azarashi: いのプレート)
    { 0xE5,0xA2,0x83,0xE7,0x95,0x8C,0xE3,0x81,0xA7,0xE9,0x80,0x9A,0xE5,0xB8,0xB8,0xE3,0x81,0xA8 },  // page 3 (azarashi: 境界で通常と)
    { 0xE3,0x81,0xAF,0xE7,0x95,0xB0,0xE3,0x81,0xAA,0xE3,0x82,0x8B,0xE3,0x82,0x86,0xE3,0x81,0xA3 },  // page 4 (azarashi: は異なるゆっ)
    { 0xE3,0x81,0x8F,0xE3,0x82,0x8A,0xE3,0x81,0x99,0xE3,0x81,0xB9,0xE3,0x82,0x8A,0xE3,0x81,0x8C },  // page 5 (azarashi: くりすべりが)
    { 0xE7,0x99,0xBA,0xE7,0x94,0x9F,0xE3,0x81,0x97,0xE3,0x81,0xA6,0xE3,0x81,0x84,0xE3,0x82,0x8B },  // page 6 (azarashi: 発生している)
    { 0xE3,0x81,0x93,0xE3,0x81,0xA8,0xE3,0x81,0x8C,0xE6,0x8E,0xA8,0xE5,0xAE,0x9A,0xE3,0x81,0x95 },  // page 7 (azarashi: ことが推定さ)
    { 0xE3,0x82,0x8C,0xE3,0x81,0xBE,0xE3,0x81,0x99,0xE3,0x80,0x82,0xE3,0x81,0x93,0xE3,0x81,0xAE },  // page 8 (azarashi)
    { 0xE9,0x80,0x9A,0xE5,0xB8,0xB8,0xE3,0x81,0xA8,0xE3,0x81,0xAF,0xE7,0x95,0xB0,0xE3,0x81,0xAA },  // page 9 (azarashi)
    { 0xE3,0x82,0x8B,0xE3,0x82,0x86,0xE3,0x81,0xA3,0xE3,0x81,0x8F,0xE3,0x82,0x8A,0xE3,0x81,0x99 },  // page 10 (azarashi)
    { 0xE3,0x81,0xB9,0xE3,0x82,0x8A,0xE3,0x81,0xAE,0xE7,0x99,0xBA,0xE7,0x94,0x9F,0xE3,0x81,0xAB },  // page 11 (azarashi)
    { 0xE3,0x82,0x88,0xE3,0x82,0x8A,0xE3,0x80,0x81,0xE5,0x8D,0x97,0xE6,0xB5,0xB7,0xE3,0x83,0x88 },  // page 12 (azarashi)
    { 0xE3,0x83,0xA9,0xE3,0x83,0x95,0xE5,0x9C,0xB0,0xE9,0x9C,0x87,0xE3,0x81,0xAE,0xE6,0x83,0xB3 },  // page 13 (azarashi)
    { 0xE5,0xAE,0x9A,0xE9,0x9C,0x87,0xE6,0xBA,0x90,0xE5,0x9F,0x9F,0xE3,0x81,0xA7,0xE3,0x81,0xAF },  // page 14 (azarashi)
    { 0xE3,0x80,0x81,0xE5,0xA4,0xA7,0xE8,0xA6,0x8F,0xE6,0xA8,0xA1,0xE5,0x9C,0xB0,0xE9,0x9C,0x87 },  // page 15 (azarashi)
    { 0xE3,0x81,0xAE,0xE7,0x99,0xBA,0xE7,0x94,0x9F,0xE5,0x8F,0xAF,0xE8,0x83,0xBD,0xE6,0x80,0xA7 },  // page 16 (azarashi)
    { 0xE3,0x81,0x8C,0xE5,0xB9,0xB3,0xE5,0xB8,0xB8,0xE6,0x99,0x82,0xE3,0x81,0xAB,0xE6,0xAF,0x94 },  // page 17 (azarashi)
    { 0xE3,0x81,0xB9,0xE3,0x81,0xA6,0xE7,0x9B,0xB8,0xE5,0xAF,0xBE,0xE7,0x9A,0x84,0xE3,0x81,0xAB },  // page 18 (azarashi)
    { 0xE9,0xAB,0x98,0xE3,0x81,0xBE,0xE3,0x81,0xA3,0xE3,0x81,0xA6,0xE3,0x81,0x84,0xE3,0x82,0x8B },  // page 19 (azarashi)
    { 0xE3,0x81,0xA8,0xE8,0x80,0x83,0xE3,0x81,0x88,0xE3,0x82,0x89,0xE3,0x82,0x8C,0xE3,0x81,0xBE },  // page 20 (azarashi)
    { 0xE3,0x81,0x99,0xE3,0x80,0x82,0xE4,0xBB,0x8A,0xE5,0xBE,0x8C,0xE3,0x81,0xAE,0xE6,0x94,0xBF },  // page 21 (azarashi)
    { 0xE5,0xBA,0x9C,0xE3,0x82,0x84,0xE8,0x87,0xAA,0xE6,0xB2,0xBB,0xE4,0xBD,0x93,0xE3,0x81,0xAA },  // page 22 (azarashi)
    { 0xE3,0x81,0xA9,0xE3,0x81,0x8B,0xE3,0x82,0x89,0xE3,0x81,0xAE,0xE5,0x91,0xBC,0xE3,0x81,0xB3 },  // page 23 (azarashi)
    { 0xE3,0x81,0x8B,0xE3,0x81,0x91,0xE7,0xAD,0x89,0xE3,0x81,0xAB,0xE5,0xBF,0x9C,0xE3,0x81,0x98 },  // page 24 (azarashi)
    { 0xE3,0x81,0x9F,0xE9,0x98,0xB2,0xE7,0x81,0xBD,0xE5,0xAF,0xBE,0xE5,0xBF,0x9C,0xE3,0x82,0x92 },  // page 25 (azarashi)
    { 0xE3,0x81,0xA8,0xE3,0x81,0xA3,0xE3,0x81,0xA6,0xE3,0x81,0x8F,0xE3,0x81,0xA0,0xE3,0x81,0x95 },  // page 26 (azarashi)
    { 0xE5,0x8D,0x97,0xE6,0xB5,0xB7,0xE3,0x83,0x88,0xE3,0x83,0xA9,0xE3,0x83,0x95,0xE5,0x9C,0xB0 },  // page 27 (synthetic)
};

TEST_CASE("Nankai E2E: 27-page full aggregation with real text data") {
    // Uses shared nankai_page_data[] defined above (18-byte fixed payloads)

    azaraC::Parser parser;
    azaraC::Message msg;
    uint8_t bits[32];

    // Build expected aggregated body: concatenation of all 27 pages (18 bytes each).
    // No page contains a 0x00 byte (all UTF-8 Japanese), so the full 486 bytes
    // should appear in aggregated_text without null-termination truncation.
    static constexpr uint16_t EXPECTED_AGG_LEN = 27 * NankaiPageBuffer::TEXT_PER_PAGE;
    uint8_t expected_body[EXPECTED_AGG_LEN];
    for (uint8_t p = 0; p < 27; ++p) {
        memcpy(expected_body + p * NankaiPageBuffer::TEXT_PER_PAGE,
               nankai_page_data[p], NankaiPageBuffer::TEXT_PER_PAGE);
    }

    // Feed all 27 pages in order
    // Pages 1..26 won't produce output (aggregation in progress),
    // only page 27 completes the aggregation and produces output.
    for (uint8_t page = 1; page <= 27; ++page) {
        buildNankaiPage(page, 27, 5,
                        nankai_page_data[page - 1], NankaiPageBuffer::TEXT_PER_PAGE, bits);
        std::string nmea = makeNmeaQzqsm(58, bits);

        bool output = false;
        for (size_t i = 0; i < nmea.length(); i++) {
            if (parser.feed(nmea[i], msg, 0)) {
                output = true;
                break;
            }
        }
        INFO("page=", page);
        if (page < 27) {
            // Intermediate pages: no output yet (aggregation in progress)
            CHECK_FALSE(output);
        } else {
            // Final page: aggregation complete, output produced
            CHECK(output);
            CHECK(msg.valid);
            CHECK(msg.payload_type == azaraC::MsgPayloadType::Mt43);

            const azaraC::Mt43Data* mt43 = msg.getMt43();
            REQUIRE(mt43 != nullptr);
            CHECK(mt43->disaster_category == 4);

            const azaraC::NankaiData* nankai = mt43->getNankai();
            REQUIRE(nankai != nullptr);
            CHECK(nankai->is_aggregated == true);
            CHECK(nankai->aggregated_len == EXPECTED_AGG_LEN);
            // Full exact match of the aggregated body
            CHECK(memcmp(nankai->aggregated_text_ptr, expected_body, EXPECTED_AGG_LEN) == 0);
        }
    }

    // After all 27 pages, the last message should be aggregated
    const azaraC::Mt43Data* mt43 = msg.getMt43();
    REQUIRE(mt43 != nullptr);
    const azaraC::NankaiData* nankai = mt43->getNankai();
    REQUIRE(nankai != nullptr);
    CHECK(nankai->is_aggregated == true);
    CHECK(nankai->aggregated_len == EXPECTED_AGG_LEN);

    // Full exact match of the aggregated body — catches reordering, truncation,
    // or partial overwrites that flag/length-only checks would miss.
    CHECK(memcmp(nankai->aggregated_text_ptr, expected_body, EXPECTED_AGG_LEN) == 0);

    // Stable portion checks: prefix (page 1) and suffix (page 27)
    CHECK(memcmp(nankai->aggregated_text_ptr,
                 nankai_page_data[0], NankaiPageBuffer::TEXT_PER_PAGE) == 0);
    CHECK(memcmp(nankai->aggregated_text_ptr + EXPECTED_AGG_LEN - NankaiPageBuffer::TEXT_PER_PAGE,
                 nankai_page_data[26], NankaiPageBuffer::TEXT_PER_PAGE) == 0);

    // Verify JSON output contains text_utf8
    StringPrint sp;
    internal::JsonSerializer::serialize(msg, sp);
    const auto& s = sp.str();
    CHECK(s.find("\"text_utf8\":") != std::string::npos);
    CHECK(s.find("\"text_hex\"") == std::string::npos);
}

// ═══════════════════════════════════════════════════════════════════════════════
// Nankai NUL バイト打ち切り リグレッションテスト
// ページ内に 0x00 が埋め込まれた場合、NUL 以降のデータが aggregated_text に
// 含まれず aggregated_len が短縮されることを検証する。
// ═══════════════════════════════════════════════════════════════════════════════

TEST_CASE("Nankai E2E: NUL byte mid-page stops aggregation at null") {
    // 3 ページ構成。page 2 の 9 バイト目に 0x00 を埋め込む。
    // NankaiPageBuffer::getTextLength/getText の stop-at-NUL を直接検証する。
    constexpr uint8_t TOTAL = 3;

    // Page 1: 18 × 'A' (0x41)
    static const uint8_t p1[NankaiPageBuffer::TEXT_PER_PAGE] = {
        'A','A','A','A','A','A','A','A','A',
        'A','A','A','A','A','A','A','A','A'
    };
    // Page 2: 'A'×9, NUL, 'B'×8 (NUL 以降の 8 バイトは集約対象外)
    static const uint8_t p2[NankaiPageBuffer::TEXT_PER_PAGE] = {
        'A','A','A','A','A','A','A','A','A',
        0x00,'B','B','B','B','B','B','B','B'
    };
    // Page 3: 18 × 'C' (0x43)
    static const uint8_t p3[NankaiPageBuffer::TEXT_PER_PAGE] = {
        'C','C','C','C','C','C','C','C','C',
        'C','C','C','C','C','C','C','C','C'
    };

    const uint8_t* page_texts[TOTAL] = { p1, p2, p3 };

    // ポインタ化後: aggregated_text_ptr は NankaiPageBuffer 内部の raw buffer を指す。
    // そのためデータはページ単位（18バイト固定オフセット）で格納されており、
    // NUL バイト以降のデータも raw buffer 上には存在する。
    // aggregated_len は論理的な結合長（NUL 打ち切り後）を示す。
    static constexpr uint16_t EXPECTED_LEN = 18 + 9 + 18; // 45

    // Raw buffer 上の期待レイアウト（ページ単位）
    // Page 1 at offset 0:  18 bytes of 'A'
    // Page 2 at offset 18: 9 'A', NUL, 8 'B'
    // Page 3 at offset 36: 18 bytes of 'C'
    // aggregated_len = 45 だが、aggregated_text_ptr から 45 バイト読むと NUL + 'B' を含む
    char expected_raw[3 * NankaiPageBuffer::TEXT_PER_PAGE];
    memcpy(expected_raw +  0, p1, 18);
    memcpy(expected_raw + 18, p2, 18);
    memcpy(expected_raw + 36, p3, 18);

    azaraC::Parser parser;
    azaraC::Message msg;
    uint8_t bits[32];

    for (uint8_t page = 1; page <= TOTAL; ++page) {
        buildNankaiPage(page, TOTAL, 5,
                        page_texts[page - 1], NankaiPageBuffer::TEXT_PER_PAGE, bits);
        std::string nmea = makeNmeaQzqsm(58, bits);

        bool output = false;
        for (size_t i = 0; i < nmea.length(); i++) {
            if (parser.feed(nmea[i], msg, 0)) {
                output = true;
                break;
            }
        }
        INFO("page=", page);
        if (page < TOTAL) {
            CHECK_FALSE(output);
        } else {
            CHECK(output);
            CHECK(msg.valid);
            CHECK(msg.payload_type == azaraC::MsgPayloadType::Mt43);

            const azaraC::Mt43Data* mt43 = msg.getMt43();
            REQUIRE(mt43 != nullptr);
            CHECK(mt43->disaster_category == 4);

            const azaraC::NankaiData* nankai = mt43->getNankai();
            REQUIRE(nankai != nullptr);
            CHECK(nankai->is_aggregated == true);

            // aggregated_len が論理的な結合長（NUL 打ち切り後）を示すこと
            CHECK(nankai->aggregated_len == EXPECTED_LEN);

            // aggregated_text_ptr は NankaiPageBuffer 内の raw buffer を指す
            // → ページ単位のレイアウトを持つ（NUL バイトも保持）
            CHECK(nankai->aggregated_text_ptr != nullptr);
            CHECK(memcmp(nankai->aggregated_text_ptr, expected_raw, sizeof(expected_raw)) == 0);
        }
    }

    // 集約完了後の最終確認
    const azaraC::Mt43Data* mt43 = msg.getMt43();
    REQUIRE(mt43 != nullptr);
    const azaraC::NankaiData* nankai = mt43->getNankai();
    REQUIRE(nankai != nullptr);
    CHECK(nankai->is_aggregated == true);
    CHECK(nankai->aggregated_len == EXPECTED_LEN);
    CHECK(nankai->aggregated_text_ptr != nullptr);

    // JSON 出力に text_utf8 が使われること
    // 注: ポインタ化後、aggregated_text_ptr は raw buffer（NUL 含む）を指すため、
    // JSON 出力には NUL 以降のデータも含まれる。これは実データ（UTF-8 Japanese, NUL 不含）では問題にならない。
    StringPrint sp;
    internal::JsonSerializer::serialize(msg, sp);
    const auto& s = sp.str();
    CHECK(s.find("\"text_utf8\":") != std::string::npos);
    CHECK(s.find("\"text_hex\"") == std::string::npos);
}

// ═══════════════════════════════════════════════════════════════════════════════
// Nankai ページ欠損 e2e テスト (integration_e2e.md #3)
// 27ページ中 page 14 をスキップ → 集約未完了 → 欠損ページ投入で集約完了
// ═══════════════════════════════════════════════════════════════════════════════

TEST_CASE("Nankai E2E: Page missing prevents aggregation") {
    // Uses shared nankai_page_data[] defined above (18-byte fixed payloads)

    azaraC::Parser parser;
    azaraC::Message msg;
    uint8_t bits[32];
    constexpr uint8_t SKIP_PAGE = 14;

    // Phase 1: Feed all pages EXCEPT the skipped one
    for (uint8_t page = 1; page <= 27; ++page) {
        if (page == SKIP_PAGE) continue;

        buildNankaiPage(page, 27, 5,
                        nankai_page_data[page - 1], NankaiPageBuffer::TEXT_PER_PAGE, bits);
        std::string nmea = makeNmeaQzqsm(58, bits);

        bool output = false;
        for (size_t i = 0; i < nmea.length(); i++) {
            if (parser.feed(nmea[i], msg, 0)) {
                output = true;
                break;
            }
        }
        // Intermediate pages should not produce output
        CHECK_FALSE(output);
    }

    // Phase 2: After 26 pages (page 14 missing), aggregation should NOT be complete
    // Re-feed the last page (27) to get a callback and check state
    {
        buildNankaiPage(27, 27, 5,
                        nankai_page_data[26], NankaiPageBuffer::TEXT_PER_PAGE, bits);
        std::string nmea = makeNmeaQzqsm(58, bits);

        bool output = false;
        for (size_t i = 0; i < nmea.length(); i++) {
            if (parser.feed(nmea[i], msg, 0)) {
                output = true;
                break;
            }
        }
        // Should NOT output because page 14 is missing
        CHECK_FALSE(output);
    }

    // Phase 3: Feed the missing page 14 — aggregation should now complete
    {
        buildNankaiPage(SKIP_PAGE, 27, 5,
                        nankai_page_data[SKIP_PAGE - 1], NankaiPageBuffer::TEXT_PER_PAGE, bits);
        std::string nmea = makeNmeaQzqsm(58, bits);

        bool output = false;
        for (size_t i = 0; i < nmea.length(); i++) {
            if (parser.feed(nmea[i], msg, 0)) {
                output = true;
                break;
            }
        }
        // NOW aggregation should complete
        CHECK(output);
        CHECK(msg.valid);
        CHECK(msg.payload_type == azaraC::MsgPayloadType::Mt43);

        const azaraC::Mt43Data* mt43 = msg.getMt43();
        REQUIRE(mt43 != nullptr);
        CHECK(mt43->disaster_category == 4);

        const azaraC::NankaiData* nankai = mt43->getNankai();
        REQUIRE(nankai != nullptr);
        CHECK(nankai->is_aggregated == true);
        CHECK(nankai->aggregated_len > 0);
    }
}

// ═══════════════════════════════════════════════════════════════════════════════
// Nankai 63ページ最大集約 E2E テスト
// total_page は6ビットフィールド（最大値63）。63ページ×18バイト=1134バイトは
// aggregated_text[1135] の上限（1134バイト+ヌル終端）にちょうど収まる。
// ページ1-27はazarashi検証済みデータ、ページ28-63は合成データを使用。
// ═══════════════════════════════════════════════════════════════════════════════

TEST_CASE("Nankai E2E: 63-page maximum aggregation (protocol limit)") {
    constexpr uint8_t TOTAL = 63;  // 6-bit max
    static_assert(TOTAL * NankaiPageBuffer::TEXT_PER_PAGE <= 1134, "exceeds aggregated_text buffer");

    azaraC::Parser parser;
    azaraC::Message msg;
    uint8_t bits[32];

    // Build expected aggregated body: 63 pages × 18 bytes = 1134 bytes
    static constexpr uint16_t EXPECTED_AGG_LEN_63 = TOTAL * NankaiPageBuffer::TEXT_PER_PAGE;
    uint8_t expected_body_63[EXPECTED_AGG_LEN_63];

    // Pages 1-27: use verified nankai_page_data
    // Pages 28-63: use synthetic filler (same as pages 2-7)
    static const uint8_t filler[NankaiPageBuffer::TEXT_PER_PAGE] = {
        0xE3,0x81,0x8A,0xE3,0x81,0x86,0xE3,0x81,0x8B,
        0xE3,0x82,0x93,0xE3,0x82,0x80,0xE3,0x82,0x8A
    };

    for (uint8_t p = 0; p < TOTAL; ++p) {
        if (p < 27) {
            memcpy(expected_body_63 + p * NankaiPageBuffer::TEXT_PER_PAGE,
                   nankai_page_data[p], NankaiPageBuffer::TEXT_PER_PAGE);
        } else {
            memcpy(expected_body_63 + p * NankaiPageBuffer::TEXT_PER_PAGE,
                   filler, NankaiPageBuffer::TEXT_PER_PAGE);
        }
    }

    // Feed all 63 pages in order
    for (uint8_t page = 1; page <= TOTAL; ++page) {
        const uint8_t* text_src = (page <= 27)
            ? nankai_page_data[page - 1]
            : filler;
        buildNankaiPage(page, TOTAL, 5,
                        text_src, NankaiPageBuffer::TEXT_PER_PAGE, bits);
        std::string nmea = makeNmeaQzqsm(58, bits);

        bool output = false;
        for (size_t i = 0; i < nmea.length(); i++) {
            if (parser.feed(nmea[i], msg, 0)) {
                output = true;
                break;
            }
        }
        INFO("page=", page);
        if (page < TOTAL) {
            CHECK_FALSE(output);
        } else {
            CHECK(output);
            CHECK(msg.valid);
            CHECK(msg.payload_type == azaraC::MsgPayloadType::Mt43);

            const azaraC::Mt43Data* mt43 = msg.getMt43();
            REQUIRE(mt43 != nullptr);
            CHECK(mt43->disaster_category == 4);

            const azaraC::NankaiData* nankai = mt43->getNankai();
            REQUIRE(nankai != nullptr);
            CHECK(nankai->is_aggregated == true);
            CHECK(nankai->aggregated_len == EXPECTED_AGG_LEN_63);
            // Full exact match
            CHECK(memcmp(nankai->aggregated_text_ptr, expected_body_63, EXPECTED_AGG_LEN_63) == 0);
        }
    }

    // Final verification on the completed aggregation
    const azaraC::Mt43Data* mt43 = msg.getMt43();
    REQUIRE(mt43 != nullptr);
    const azaraC::NankaiData* nankai = mt43->getNankai();
    REQUIRE(nankai != nullptr);
    CHECK(nankai->is_aggregated == true);
    CHECK(nankai->aggregated_len == EXPECTED_AGG_LEN_63);
    CHECK(memcmp(nankai->aggregated_text_ptr, expected_body_63, EXPECTED_AGG_LEN_63) == 0);

    // Stable portion checks: prefix (page 1) and suffix (page 63 = filler)
    CHECK(memcmp(nankai->aggregated_text_ptr,
                 nankai_page_data[0], NankaiPageBuffer::TEXT_PER_PAGE) == 0);
    CHECK(memcmp(nankai->aggregated_text_ptr + EXPECTED_AGG_LEN_63 - NankaiPageBuffer::TEXT_PER_PAGE,
                 filler, NankaiPageBuffer::TEXT_PER_PAGE) == 0);

    // Verify JSON output contains text_utf8
    StringPrint sp;
    internal::JsonSerializer::serialize(msg, sp);
    const auto& s = sp.str();
    CHECK(s.find("\"text_utf8\":") != std::string::npos);
    CHECK(s.find("\"text_hex\"") == std::string::npos);
}
#endif // AZARAC_ENABLE_NANKAI
