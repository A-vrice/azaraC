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

// Nankai 27ページ完全集約 E2E テスト (integration_e2e.md #1)
// nankai_vectors.json の実データテキストを使用

// Helper: build a Nankai page message with specific page number and text
static void buildNankaiPage(uint8_t page_num, uint8_t total_pages, uint8_t info_code,
                            const uint8_t* text, uint8_t text_len, uint8_t* bits,
                            uint8_t rt_month = 0, uint8_t rt_day = 0,
                            uint8_t rt_hour = 0, uint8_t rt_minute = 0) {
    memset(bits, 0, 32);
    setBits(bits, 0, 8, 0x53);       // Preamble
    setBits(bits, 8, 6, 43);         // msg_type
    setBits(bits, 14, 3, 1);         // report_classification = 1 (訓練)
    setBits(bits, 17, 4, 4);         // disaster_category = 4 (Nankai)
    // report_time: month(4)+day(5)+hour(5)+minute(6) at bit 21
    setBits(bits, 21, 4, rt_month);
    setBits(bits, 25, 5, rt_day);
    setBits(bits, 30, 5, rt_hour);
    setBits(bits, 35, 6, rt_minute);
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

// 18-byte page payloads generated from azarashi via test/scripts/gen_all_vectors.py.
// Source of truth: test/data/nankai_vectors.json (emitted as nankai_pages_generated.h).
// Do not hand-edit page data — regenerate the header instead.
#include "../data/nankai_pages_generated.h"

// Per-page text length up to the first NUL, mirroring NankaiPageBuffer::compactText().
// The final page of the real message is NUL-padded on the wire, so the aggregated
// body is shorter than pages * TEXT_PER_PAGE.
[[maybe_unused]] static uint16_t pageUsedLength(const uint8_t* page) {
    uint16_t n = 0;
    while (n < NankaiPageBuffer::TEXT_PER_PAGE && page[n] != 0) ++n;
    return n;
}

// Compact a page table into the contiguous body produced by compactText().
[[maybe_unused]] static uint16_t compactPages(const uint8_t (*pages)[NankaiPageBuffer::TEXT_PER_PAGE],
                             uint8_t count, uint8_t* out) {
    uint16_t w = 0;
    for (uint8_t p = 0; p < count; ++p) {
        uint16_t n = pageUsedLength(pages[p]);
        memcpy(out + w, pages[p], n);
        w += n;
    }
    return w;
}

#if AZARAC_NANKAI_MAX_PAGES >= 27
TEST_CASE("Nankai E2E: 27-page full aggregation with real text data") {
    // Uses shared nankai_page_data[] defined above (18-byte fixed payloads)

    azaraC::Parser parser;
    azaraC::Message msg;
    uint8_t bits[32];

    // Build the expected body exactly like NankaiPageBuffer::compactText(): per-page
    // text up to the first NUL. The real final page is NUL-padded, so the body is
    // shorter than 27*18 bytes.
    uint8_t expected_body[27 * NankaiPageBuffer::TEXT_PER_PAGE];
    const uint16_t EXPECTED_AGG_LEN = compactPages(nankai_page_data, 27, expected_body);
    CHECK(EXPECTED_AGG_LEN < 27 * NankaiPageBuffer::TEXT_PER_PAGE);  // final page is short

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
            // 既定構成で実メッセージが打ち切られないことを固定
            CHECK(nankai->truncated == false);
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

    // Stable portion checks: prefix (page 1) and suffix (final page's used bytes)
    CHECK(memcmp(nankai->aggregated_text_ptr,
                 nankai_page_data[0], pageUsedLength(nankai_page_data[0])) == 0);
    {
        const uint16_t last = pageUsedLength(nankai_page_data[26]);
        CHECK(memcmp(nankai->aggregated_text_ptr + EXPECTED_AGG_LEN - last,
                     nankai_page_data[26], last) == 0);
    }

    // Verify JSON output contains text_utf8
    StringPrint sp;
    internal::JsonSerializer::serialize(msg, sp);
    const auto& s = sp.str();
    CHECK(s.find("\"text_utf8\":") != std::string::npos);
    CHECK(s.find("\"text_hex\"") == std::string::npos);
}
#endif // AZARAC_NANKAI_MAX_PAGES >= 27

// Nankai NUL バイト打ち切り リグレッションテスト
// ページ内に 0x00 が埋め込まれた場合、NUL 以降のデータが aggregated_text に
// 含まれず aggregated_len が短縮されることを検証する。

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

    // compactText() により完成時は NUL ホールが詰められ、[ptr, ptr+len) は
    // 連続したテキストになる。aggregated_len は論理的な結合長 (NUL 打ち切り後)。
    static constexpr uint16_t EXPECTED_LEN = 18 + 9 + 18; // 45

    // Compact 後の期待レイアウト (連続): A*18 + A*9 + C*18
    char expected_compact[18 + 9 + 18];
    memcpy(expected_compact +  0, p1, 18);
    memcpy(expected_compact + 18, p2, 9);
    memcpy(expected_compact + 27, p3, 18);

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

            // compact 後の [ptr, ptr+len) は NUL ホールなしの連続テキスト
            CHECK(nankai->aggregated_len == EXPECTED_LEN);
            CHECK(nankai->aggregated_text_ptr != nullptr);
            CHECK(memcmp(nankai->aggregated_text_ptr, expected_compact, EXPECTED_LEN) == 0);
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
    CHECK(memcmp(nankai->aggregated_text_ptr, expected_compact, EXPECTED_LEN) == 0);

    // JSON 出力に text_utf8 が使われること (compact 済みのため embedded NUL なし)
    StringPrint sp;
    internal::JsonSerializer::serialize(msg, sp);
    const auto& s = sp.str();
    CHECK(s.find("\"text_utf8\":") != std::string::npos);
    CHECK(s.find("\"text_hex\"") == std::string::npos);
}

// Nankai ページ欠損 e2e テスト (integration_e2e.md #3)
// 27ページ中 page 14 をスキップ → 集約未完了 → 欠損ページ投入で集約完了

#if AZARAC_NANKAI_MAX_PAGES >= 27
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
#endif // AZARAC_NANKAI_MAX_PAGES >= 27

// 鍵正規化リグレッション: report_unix が途中で解決されても 1 バッファに集約される
// report_time は固定なので、解決済み/未解決で鍵の identity は変わらない。

TEST_CASE("Nankai E2E: report_unix becoming valid mid-broadcast keeps one buffer") {
    azaraC::Parser parser;
    azaraC::Message msg;
    uint8_t bits[32];
    constexpr uint8_t TOTAL = 3;

    uint8_t text[NankaiPageBuffer::TEXT_PER_PAGE];
    for (uint8_t i = 0; i < NankaiPageBuffer::TEXT_PER_PAGE; ++i)
        text[i] = static_cast<uint8_t>('a' + i);

    bool output = false;
    for (uint8_t page = 1; page <= TOTAL; ++page) {
        buildNankaiPage(page, TOTAL, 5, text, NankaiPageBuffer::TEXT_PER_PAGE, bits,
                        /*rt_month=*/6, /*rt_day=*/15, /*rt_hour=*/12, /*rt_minute=*/30);
        std::string nmea = makeNmeaQzqsm(58, bits);
        // First page has no baseline; the remaining pages get a valid report_unix.
        const uint32_t report_unix = (page == 1) ? 0u : 1700000000u;

        output = false;
        for (size_t i = 0; i < nmea.length(); i++)
            if (parser.feed(nmea[i], msg, report_unix)) { output = true; break; }
        if (page < TOTAL) CHECK_FALSE(output);
    }

    REQUIRE(output);
    const Mt43Data* mt43 = msg.getMt43();
    REQUIRE(mt43 != nullptr);
    const NankaiData* nankai = mt43->getNankai();
    REQUIRE(nankai != nullptr);
    CHECK(nankai->is_aggregated == true);
    CHECK(nankai->total_page == TOTAL);
    CHECK(nankai->truncated == false);
}

// 鍵の生ビット正規化リグレッション: report_time が暦上正規化される値でも
// 解決状況に依存せず 1 バッファに集約される（report_* は resolveTime を通さない）。

TEST_CASE("Nankai E2E: key uses raw report_time, not the normalized date") {
    constexpr uint8_t TOTAL = 3;
    uint8_t text[NankaiPageBuffer::TEXT_PER_PAGE];
    for (uint8_t i = 0; i < NankaiPageBuffer::TEXT_PER_PAGE; ++i)
        text[i] = static_cast<uint8_t>('a' + i);

    // (rt_month, rt_day) のうち解決後と生値が食い違う組:
    //   4/31 → 5/1（4月は30日まで）、month=0 は近傍の月が割り当てられる。
    const uint8_t cases[2][2] = {{4, 31}, {0, 15}};

    for (uint8_t c = 0; c < 2; ++c) {
        CAPTURE(c);
        azaraC::Parser parser;
        azaraC::Message msg;
        uint8_t bits[32];
        bool output = false;

        for (uint8_t page = 1; page <= TOTAL; ++page) {
            buildNankaiPage(page, TOTAL, 5, text, NankaiPageBuffer::TEXT_PER_PAGE, bits,
                            cases[c][0], cases[c][1], /*rt_hour=*/12, /*rt_minute=*/30);
            std::string nmea = makeNmeaQzqsm(58, bits);
            // 1ページ目は基準時刻なし、2ページ目以降は有効な report_unix が付く。
            const uint32_t report_unix = (page == 1) ? 0u : 1700000000u;

            output = false;
            for (size_t i = 0; i < nmea.length(); i++)
                if (parser.feed(nmea[i], msg, report_unix)) { output = true; break; }
            if (page < TOTAL) CHECK_FALSE(output);
        }

        REQUIRE(output);
        const Mt43Data* mt43 = msg.getMt43();
        REQUIRE(mt43 != nullptr);
        const NankaiData* nankai = mt43->getNankai();
        REQUIRE(nankai != nullptr);
        // 生値が電文から取り込まれていること（鍵の日付成分がケース指定どおり）。
        CHECK(nankai->report_month == cases[c][0]);
        CHECK(nankai->report_day == cases[c][1]);
        CHECK(nankai->is_aggregated == true);
        CHECK(nankai->total_page == TOTAL);
    }
}

// 打ち切り（total_pages > MAX_PAGES）E2E テスト
// 既定値非依存: MAX_PAGES は NankaiPageBuffer から取得する。
// 6bit フィールドに収まる範囲（MAX_PAGES+2 <= 63）でのみ成立するため、
// MAX_PAGES=63（仕様最大）では電文上打ち切りが発生せずガードで除外される。

#if AZARAC_NANKAI_MAX_PAGES + 2 <= 63
TEST_CASE("Nankai E2E: pages beyond MAX_PAGES are dropped and flagged truncated") {
    const uint8_t MP = NankaiPageBuffer::MAX_PAGES;
    const uint8_t TOTAL = static_cast<uint8_t>(MP + 2);  // > MAX_PAGES → 打ち切り

    azaraC::Parser parser;
    azaraC::Message msg;
    uint8_t bits[32];

    // 0x00 を含まない 18 バイト充填（aggregated_len を厳密一致させる）
    uint8_t text[NankaiPageBuffer::TEXT_PER_PAGE];
    for (uint8_t i = 0; i < NankaiPageBuffer::TEXT_PER_PAGE; ++i)
        text[i] = static_cast<uint8_t>('A' + (i % 26));

    // ページ 1..MAX_PAGES を投入 → 最終ページで打ち切り完了
    for (uint8_t page = 1; page <= MP; ++page) {
        buildNankaiPage(page, TOTAL, 5, text, NankaiPageBuffer::TEXT_PER_PAGE, bits);
        std::string nmea = makeNmeaQzqsm(58, bits);
        bool output = false;
        for (size_t i = 0; i < nmea.length(); i++)
            if (parser.feed(nmea[i], msg, 0)) { output = true; break; }

        if (page < MP) {
            CHECK_FALSE(output);
        } else {
            REQUIRE(output);
            const Mt43Data* mt43 = msg.getMt43();
            REQUIRE(mt43 != nullptr);
            const NankaiData* nankai = mt43->getNankai();
            REQUIRE(nankai != nullptr);
            CHECK(nankai->is_aggregated == true);
            CHECK(nankai->truncated == true);
            CHECK(nankai->aggregated_len ==
                  static_cast<uint16_t>(MP) * NankaiPageBuffer::TEXT_PER_PAGE);
            // 打ち切り時も total_page は電文の総ページ数（仕様値）を報告する
            CHECK(nankai->total_page == TOTAL);
        }
    }

    // MAX_PAGES を超えるページ番号は拒否され、追加出力はない
    buildNankaiPage(static_cast<uint8_t>(MP + 1), TOTAL, 5, text,
                    NankaiPageBuffer::TEXT_PER_PAGE, bits);
    std::string nmea = makeNmeaQzqsm(58, bits);
    bool output = false;
    for (size_t i = 0; i < nmea.length(); i++)
        if (parser.feed(nmea[i], msg, 0)) { output = true; break; }
    CHECK_FALSE(output);
}
#endif // AZARAC_NANKAI_MAX_PAGES + 2 <= 63

// Nankai 63ページ最大集約 E2E テスト
// total_page は6ビットフィールド（最大値63）。63ページ×18バイト=1134バイトは
// aggregated_text[1135] の上限（1134バイト+ヌル終端）にちょうど収まる。
// ページ1-27はazarashi検証済みデータ、ページ28-63は合成データを使用。

#if AZARAC_NANKAI_MAX_PAGES >= 63
TEST_CASE("Nankai E2E: 63-page maximum aggregation (protocol limit)") {
    constexpr uint8_t TOTAL = 63;  // 6-bit max
    static_assert(TOTAL * NankaiPageBuffer::TEXT_PER_PAGE <= 1134, "exceeds aggregated_text buffer");

    azaraC::Parser parser;
    azaraC::Message msg;
    uint8_t bits[32];

    // Pages 1-27: real azarashi data; pages 28-63: synthetic filler (protocol max).
    static const uint8_t filler[NankaiPageBuffer::TEXT_PER_PAGE] = {
        0xE3,0x81,0x8A,0xE3,0x81,0x86,0xE3,0x81,0x8B,
        0xE3,0x82,0x93,0xE3,0x82,0x80,0xE3,0x82,0x8A
    };

    uint8_t pages63[TOTAL][NankaiPageBuffer::TEXT_PER_PAGE];
    for (uint8_t p = 0; p < TOTAL; ++p) {
        const uint8_t* src = (p < 27) ? nankai_page_data[p] : filler;
        memcpy(pages63[p], src, NankaiPageBuffer::TEXT_PER_PAGE);
    }

    // Same compaction as compactText(): the real page 27 is NUL-padded, so the
    // aggregated body is shorter than 63*18 bytes.
    uint8_t expected_body_63[TOTAL * NankaiPageBuffer::TEXT_PER_PAGE];
    const uint16_t EXPECTED_AGG_LEN_63 = compactPages(pages63, TOTAL, expected_body_63);

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
#endif // AZARAC_NANKAI_MAX_PAGES >= 63
#endif // AZARAC_ENABLE_NANKAI
