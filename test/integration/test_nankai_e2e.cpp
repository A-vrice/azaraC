// 南海トラフ複数ページ集約E2Eテスト

#include <string>
#include "doctest.h"
#include "../src/internal/NankaiPageBuffer.h"
#include "../src/Parser.h"
#include "../test_helpers.h"

using namespace azaraC::internal;

#if (AZARAC_ENABLE_NANKAI)
namespace {

std::string makeSinglePageNmea(uint8_t info_code) {
    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);
    setBits(bits, 8, 6, 43);
    setBits(bits, 14, 3, 2);
    setBits(bits, 17, 4, 4);
    setBits(bits, 53, 4, info_code);
    setBits(bits, 201, 6, 1);
    setBits(bits, 207, 6, 1);
    setBits(bits, 214, 6, 1);
    setBits(bits, 226, 24, crc24qRef(bits, 226));
    return makeNmeaQzqsm(58, bits);
}

bool feedAll(azaraC::Parser& parser, azaraC::Message& msg, const std::string& nmea) {
    for (size_t i = 0; i < nmea.length(); ++i) {
        if (parser.feed(nmea[i], msg, 0)) return true;
    }
    return false;
}

} // namespace

TEST_CASE("Nankai E2E: parser decode, dedup and reset") {
    SUBCASE("decodes a synthetic message") {
        azaraC::Parser parser;
        azaraC::Message msg;
        REQUIRE(feedAll(parser, msg, makeSinglePageNmea(1)));
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

    SUBCASE("duplicate is suppressed") {
        azaraC::Parser parser;
        azaraC::Message msg;
        const std::string nmea = makeSinglePageNmea(1);
        CHECK(feedAll(parser, msg, nmea));
        CHECK_FALSE(feedAll(parser, msg, nmea));
    }

    SUBCASE("reset allows re-output") {
        azaraC::Parser parser;
        azaraC::Message msg;
        const std::string nmea = makeSinglePageNmea(1);
        CHECK(feedAll(parser, msg, nmea));
        parser.reset();
        CHECK(feedAll(parser, msg, nmea));
    }

    SUBCASE("different messages are not suppressed") {
        azaraC::Parser parser;
        azaraC::Message msg;
        CHECK(feedAll(parser, msg, makeSinglePageNmea(1)));
        CHECK(feedAll(parser, msg, makeSinglePageNmea(2)));
    }
}

TEST_CASE("Nankai E2E: Text extraction from single page") {
    azaraC::Parser parser;
    azaraC::Message msg;

    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);
    setBits(bits, 8, 6, 43);
    setBits(bits, 14, 3, 2);
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

TEST_CASE("Nankai E2E: page bounds are rejected") {
    struct Case { uint8_t page; uint8_t total; bool emitted; const char* name; };
    const Case cases[] = {
        {1, 1, true,  "page=1,total=1"},
        {2, 1, false, "page > total"},
        {1, 0, false, "total=0"},
        {0, 1, false, "page=0"},
    };
    for (const Case& c : cases) {
        INFO(c.name);
        uint8_t bits[32] = {};
        setBits(bits, 0, 8, 0x53);
        setBits(bits, 8, 6, 43);
        setBits(bits, 14, 3, 2);
        setBits(bits, 17, 4, 4);
        setBits(bits, 53, 4, 1);
        setBits(bits, 201, 6, c.page);
        setBits(bits, 207, 6, c.total);
        setBits(bits, 214, 6, 1);
        setBits(bits, 226, 24, crc24qRef(bits, 226));
        const std::string nmea = makeNmeaQzqsm(58, bits);

        azaraC::Parser parser;
        azaraC::Message msg;
        bool output = false;
        for (char ch : nmea) {
            if (parser.feed(static_cast<uint8_t>(ch), msg, 0)) {
                output = true;
                break;
            }
        }
        CHECK(output == c.emitted);
        if (c.emitted) CHECK(msg.valid);
    }
}

TEST_CASE("Nankai E2E: Page tracking with single page") {
    azaraC::Parser parser;
    azaraC::Message msg;

    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);
    setBits(bits, 8, 6, 43);
    setBits(bits, 14, 3, 2);
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

// Nankai 27ページ完全集約 E2E テスト (integration_e2e.md #1)。テキストは nankai_vectors.json の実データ。

// ヘルパ: ページ番号と本文を指定した南海トラフ前沿電文を作る
static void buildNankaiPage(uint8_t page_num, uint8_t total_pages, uint8_t info_code,
                            const uint8_t* text, uint8_t text_len, uint8_t* bits,
                            uint8_t rt_month = 0, uint8_t rt_day = 0,
                            uint8_t rt_hour = 0, uint8_t rt_minute = 0,
                            uint8_t information_type = 0, uint8_t report_classification = 2) {
    memset(bits, 0, 32);
    setBits(bits, 0, 8, 0x53);       // Preamble
    setBits(bits, 8, 6, 43);         // msg_type
    setBits(bits, 14, 3, report_classification); // Rc: 2=実警報, 7=訓練/試験
    setBits(bits, 17, 4, 4);         // disaster_category = 4 (Nankai)
    // report_time: bit 21 から month(4)+day(5)+hour(5)+minute(6)
    setBits(bits, 21, 4, rt_month);
    setBits(bits, 25, 5, rt_day);
    setBits(bits, 30, 5, rt_hour);
    setBits(bits, 35, 6, rt_minute);
    setBits(bits, 41, 2, information_type);  // It (0=発表 / 2=取消)
    setBits(bits, 53, 4, info_code);  // info_code
    // 本文: bit 57..200 の 18 バイト
    for (uint8_t i = 0; i < text_len && i < 18; ++i) {
        setBits(bits, 57 + i * 8, 8, text[i]);
    }
    setBits(bits, 201, 6, page_num);       // page
    setBits(bits, 207, 6, total_pages);    // total_page
    setBits(bits, 214, 6, 1);              // version = 1
    uint32_t crc = crc24qRef(bits, 226);
    setBits(bits, 226, 24, crc);
}

// 18 バイトのページペイロードは test/scripts/gen_all_vectors.py が azarashi から生成した。
// 唯一の正は test/data/nankai_vectors.json（nankai_pages_generated.h として生成される）。ページデータを手で編集せず、ヘッダを再生成すること。
#include "../data/nankai_pages_generated.h"

TEST_CASE("Nankai E2E: Rc separates training from a real alert") {
    azaraC::Parser parser;
    azaraC::Message msg;
    uint8_t bits[32];

    const uint8_t drill[] = {'D', 'R', 'I', 'L', 'L'};
    buildNankaiPage(1, 1, 1, drill, sizeof(drill), bits,
                    /*rt_month=*/6, /*rt_day=*/15, /*rt_hour=*/12, /*rt_minute=*/30,
                    /*information_type=*/0, /*report_classification=*/7);
    CHECK(feedAll(parser, msg, makeNmeaQzqsm(58, bits)));

    const uint8_t real[] = {'R', 'E', 'A', 'L'};
    buildNankaiPage(1, 1, 1, real, sizeof(real), bits,
                    /*rt_month=*/6, /*rt_day=*/15, /*rt_hour=*/12, /*rt_minute=*/30,
                    /*information_type=*/0, /*report_classification=*/2);
    CHECK(feedAll(parser, msg, makeNmeaQzqsm(58, bits)));

    const azaraC::Mt43Data* mt43 = msg.getMt43();
    REQUIRE(mt43 != nullptr);
    CHECK(mt43->report_classification == 2);
    const azaraC::NankaiData* nankai = mt43->getNankai();
    REQUIRE(nankai != nullptr);
    REQUIRE(nankai->is_aggregated);
    CHECK(std::string(nankai->aggregated_text_ptr, nankai->aggregated_len) == "REAL");
}

#if AZARAC_NANKAI_BUFFERS >= 2
TEST_CASE("Nankai E2E: training and real pages do not share an aggregate buffer") {
    azaraC::Parser parser;
    azaraC::Message msg;
    uint8_t bits[32];
    const uint8_t drill[] = {'D', 'R', 'I', 'L', 'L'};
    const uint8_t real1[] = {'R', 'E', 'A', 'L', '1'};
    const uint8_t real2[] = {'R', 'E', 'A', 'L', '2'};

    buildNankaiPage(1, 2, 1, drill, sizeof(drill), bits, 6, 15, 12, 30, 0, 7);
    CHECK_FALSE(feedAll(parser, msg, makeNmeaQzqsm(58, bits)));
    buildNankaiPage(1, 2, 1, real1, sizeof(real1), bits, 6, 15, 12, 30, 0, 2);
    CHECK_FALSE(feedAll(parser, msg, makeNmeaQzqsm(58, bits)));
    buildNankaiPage(2, 2, 1, real2, sizeof(real2), bits, 6, 15, 12, 30, 0, 2);
    CHECK(feedAll(parser, msg, makeNmeaQzqsm(58, bits)));

    const azaraC::NankaiData* nankai = msg.getMt43()->getNankai();
    REQUIRE(nankai != nullptr);
    REQUIRE(nankai->is_aggregated);
    CHECK(std::string(nankai->aggregated_text_ptr, nankai->aggregated_len) == "REAL1REAL2");
}
#endif

TEST_CASE("Nankai E2E: getNankaiBuffer exposes an incomplete buffer") {
    azaraC::Parser parser;
    azaraC::Message msg;
    uint8_t bits[32];
    const uint8_t text[18] = {'p', 'a', 'r', 't', 'i', 'a', 'l'};

    buildNankaiPage(1, 2, 1, text, sizeof(text), bits);
    const std::string nmea = makeNmeaQzqsm(58, bits);

    bool output = false;
    for (size_t i = 0; i < nmea.length(); ++i) {
        if (parser.feed(nmea[i], msg, 0)) output = true;
    }
    CHECK_FALSE(output);

    const NankaiPageKey key{1, 0, 0, 0, 0, 0, 2};
    const NankaiPageBuffer* buf = parser.getNankaiBuffer(key);
    REQUIRE(buf != nullptr);
    CHECK_FALSE(buf->isComplete());
    CHECK(buf->total_pages == 2);
    CHECK(buf->received_count == 1);
}

// 借用ポインタの寿命（H2）: 集約完了後に Message を値コピーしても、aggregated_text_ptr は
// Parser 内部の NankaiPageBuffer を指したまま。別事象を feed() するとバッファが再利用され、
// コピー側は「別の警報文」を読む。docs/api-reference.md の注意書きと同じ契約を回帰で固定する。
TEST_CASE("Nankai E2E: copied Message keeps a borrowed pointer into Parser storage") {
    azaraC::Parser parser;
    azaraC::Message msg;
    uint8_t bits[32];

    auto feedOnePage = [&](uint8_t info_code, const char* text, uint8_t len, uint8_t minute = 30) {
        buildNankaiPage(1, 1, info_code,
                        reinterpret_cast<const uint8_t*>(text), len, bits,
                        /*rt_month=*/6, /*rt_day=*/15, /*rt_hour=*/12, /*rt_minute=*/minute);
        const std::string nmea = makeNmeaQzqsm(58, bits);
        for (char c : nmea) {
            if (parser.feed(static_cast<uint8_t>(c), msg, 0)) return true;
        }
        return false;
    };

    REQUIRE(feedOnePage(5, "FIRST-EVENT-TEXT", 16));
    const azaraC::Mt43Data* mt43 = msg.getMt43();
    REQUIRE(mt43 != nullptr);
    const azaraC::NankaiData* first = mt43->getNankai();
    REQUIRE(first != nullptr);
    REQUIRE(first->is_aggregated);
    REQUIRE(first->aggregated_text_ptr != nullptr);
    const char* borrowed = first->aggregated_text_ptr;
    CHECK(std::string(borrowed, first->aggregated_len) == "FIRST-EVENT-TEXT");

    // 値コピー: ポインタはそのまま複製される（所有権は移らない）。
    azaraC::Message copy = msg;
    const azaraC::Mt43Data* copyMt43 = copy.getMt43();
    REQUIRE(copyMt43 != nullptr);
    const azaraC::NankaiData* copied = copyMt43->getNankai();
    REQUIRE(copied != nullptr);
    CHECK(copied->aggregated_text_ptr == borrowed);   // 同じ Parser 内部を指す

    // 全スロットを埋めてから別事象を送る。AZARAC_NANKAI_BUFFERS=1 なら B が A を追い出し、
    // 4 以上なら埋めたスロットのうち最も古い A が追い出される。BUFFERS に依存せず同じ検証になる。
    for (uint8_t i = 0; i + 1 < azaraC::internal::NankaiPageBufferManager::MAX_BUFFERS; ++i) {
        REQUIRE(feedOnePage(7, "FILL-EVENT", 10, static_cast<uint8_t>(i + 1)));
    }
    REQUIRE(feedOnePage(6, "SECOND-EVENT-TXT", 16));

    // コピー側は同じアドレスのまま、内容だけが別の警報文に変わる。これが H2 の実害。
    CHECK(copied->aggregated_text_ptr == borrowed);
    CHECK(std::string(copied->aggregated_text_ptr, copied->aggregated_len) != "FIRST-EVENT-TEXT");
}

// ページ別の本文長は最初の NUL まで。NankaiPageBuffer::compactText() と同じ手順。
// 実電文の最終ページは送信中 NUL パッドなので、集約本文は ページ数 * TEXT_PER_PAGE より短くなる。
[[maybe_unused]] static uint16_t pageUsedLength(const uint8_t* page) {
    uint16_t n = 0;
    while (n < NankaiPageBuffer::TEXT_PER_PAGE && page[n] != 0) ++n;
    return n;
}

// ページ表を compactText() が作る連続本文へ詰める。
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
    // 上の nankai_page_data[]（18 バイト固定ペイロード）を共用する

    azaraC::Parser parser;
    azaraC::Message msg;
    uint8_t bits[32];

    // 期待する本文は NankaiPageBuffer::compactText() と同じ: 各ページの本文を最初の NUL まで。よって NUL 埋めされた最終ページの分だけ 27*18 バイトより短くなる。
    uint8_t expected_body[27 * NankaiPageBuffer::TEXT_PER_PAGE];
    const uint16_t EXPECTED_AGG_LEN = compactPages(nankai_page_data, 27, expected_body);
    CHECK(EXPECTED_AGG_LEN < 27 * NankaiPageBuffer::TEXT_PER_PAGE);  // final page is short

    // ページ 1..26 では出力なし。ページ 27 で集約が完了する。
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
            CHECK(nankai->aggregated_len == EXPECTED_AGG_LEN);
            // 既定構成で実メッセージが打ち切られないことを固定
            CHECK(nankai->truncated == false);
            CHECK(memcmp(nankai->aggregated_text_ptr, expected_body, EXPECTED_AGG_LEN) == 0);

            // compactText() 後も getNankaiBuffer() 経由の長さが集約本文と一致する。
            const NankaiPageBuffer* buf = parser.getNankaiBuffer(NankaiPageKey{5, 0, 0, 0, 0, 0, 2});
            REQUIRE(buf != nullptr);
            CHECK(buf->compacted);
            CHECK(buf->getTextLength() == EXPECTED_AGG_LEN);
        }
    }

    const azaraC::Mt43Data* mt43 = msg.getMt43();
    REQUIRE(mt43 != nullptr);
    const azaraC::NankaiData* nankai = mt43->getNankai();
    REQUIRE(nankai != nullptr);
    CHECK(nankai->is_aggregated == true);
    CHECK(nankai->aggregated_len == EXPECTED_AGG_LEN);

    // 集約本文を完全一致で確かめる（フラグと長さだけの検証では見逃す並べ替え・打ち切り・部分上書きを捕らえる）。
    CHECK(memcmp(nankai->aggregated_text_ptr, expected_body, EXPECTED_AGG_LEN) == 0);

    // 安定部分の検証: 前文（ページ 1）と後文（最終ページの使用中バイト）
    CHECK(memcmp(nankai->aggregated_text_ptr,
                 nankai_page_data[0], pageUsedLength(nankai_page_data[0])) == 0);
    {
        const uint16_t last = pageUsedLength(nankai_page_data[26]);
        CHECK(memcmp(nankai->aggregated_text_ptr + EXPECTED_AGG_LEN - last,
                     nankai_page_data[26], last) == 0);
    }

    StringPrint sp;
    internal::JsonSerializer::serialize(msg, sp);
    const auto& s = sp.str();
    CHECK(s.find("\"text_utf8\":") != std::string::npos);
    CHECK(s.find("\"text_hex\"") == std::string::npos);
}
#endif // AZARAC_NANKAI_MAX_PAGES >= 27

// 同じ事象を別のページ順で再受信しても再通知しない。集約メッセージの同一性はページ集合を完成させた電文ではなく事象そのもの（info_code + 報告時刻）。
// 既定の AZARAC_NANKAI_BUFFERS=1 では事象BがAのページバッファを追い出すため、 3手目は集約が再完了して dedup の判定に到達する（バッファ数が2以上でもページ重複で再完了しないだけで、期待値は同じ0）。
#if AZARAC_ENABLE_DEDUP
#if AZARAC_NANKAI_MAX_PAGES >= 27
TEST_CASE("Nankai E2E: 同一事象の再放送は再通知しない") {
    azaraC::Parser parser;
    azaraC::Message msg;
    uint8_t bits[32];

    auto feedEvent = [&](uint8_t rt_minute, bool reversed) -> int {
        int emitted = 0;
        for (uint8_t i = 0; i < 27; ++i) {
            const uint8_t page = reversed ? static_cast<uint8_t>(27 - i)
                                          : static_cast<uint8_t>(i + 1);
            buildNankaiPage(page, 27, /*info_code=*/5,
                            nankai_page_data[page - 1], NankaiPageBuffer::TEXT_PER_PAGE, bits,
                            /*rt_month=*/6, /*rt_day=*/15, /*rt_hour=*/12, rt_minute);
            std::string nmea = makeNmeaQzqsm(58, bits);
            for (size_t k = 0; k < nmea.length(); ++k) {
                if (parser.feed(nmea[k], msg, 0)) ++emitted;
            }
        }
        return emitted;
    };

    CHECK(feedEvent(30, false) == 1);   // 事象A
    CHECK(feedEvent(31, false) == 1);   // 事象B（報告時刻が違う＝別の情報）
    CHECK(feedEvent(30, true) == 0);    // 事象Aの再放送（完成ページが入れ替わる）
}
#endif

// 同一 info_code + 同一報告時刻でも情報種別（発表/取消）が違えば別の情報として通知する。
// 事象鍵が It を含まないと、後から完成した取消が発表の dedup 履歴に潰されて落ちる（集約バッファでも両者が1つに混ざる）。
#if AZARAC_NANKAI_MAX_PAGES >= 27
TEST_CASE("Nankai E2E: 同一 info_code + 報告時刻でも発表と取消は別に通知する") {
    azaraC::Parser parser;
    azaraC::Message msg;
    uint8_t bits[32];

    auto feedEvent = [&](uint8_t information_type) -> int {
        int emitted = 0;
        for (uint8_t page = 1; page <= 27; ++page) {
            buildNankaiPage(page, 27, /*info_code=*/5,
                            nankai_page_data[page - 1], NankaiPageBuffer::TEXT_PER_PAGE, bits,
                            /*rt_month=*/6, /*rt_day=*/15, /*rt_hour=*/12, /*rt_minute=*/30,
                            /*information_type=*/information_type);
            std::string nmea = makeNmeaQzqsm(58, bits);
            for (size_t k = 0; k < nmea.length(); ++k) {
                if (parser.feed(nmea[k], msg, 0)) ++emitted;
            }
        }
        return emitted;
    };

    CHECK(feedEvent(0) == 1);   // 発表
    CHECK(feedEvent(2) == 1);   // 取消（It だけ違う＝別の情報）
    CHECK(feedEvent(0) == 0);   // 発表の再放送は抑制される
}
#endif
#endif // AZARAC_ENABLE_DEDUP

// ページ内の 0x00 以降は aggregated_text に含まれず、aggregated_len が短縮される。

TEST_CASE("Nankai E2E: NUL byte mid-page stops aggregation at null") {
    // 3 ページ構成。page 2 の 9 バイト目に 0x00。NankaiPageBuffer::getTextLength/getText の stop-at-NUL を検証する。
    constexpr uint8_t TOTAL = 3;

    // ページ 1: 18 × 'A' (0x41)
    static const uint8_t p1[NankaiPageBuffer::TEXT_PER_PAGE] = {
        'A','A','A','A','A','A','A','A','A',
        'A','A','A','A','A','A','A','A','A'
    };
    // Page 2: 'A'×9, NUL, 'B'×8 (NUL 以降の 8 バイトは集約対象外)
    static const uint8_t p2[NankaiPageBuffer::TEXT_PER_PAGE] = {
        'A','A','A','A','A','A','A','A','A',
        0x00,'B','B','B','B','B','B','B','B'
    };
    // ページ 3: 18 × 'C' (0x43)
    static const uint8_t p3[NankaiPageBuffer::TEXT_PER_PAGE] = {
        'C','C','C','C','C','C','C','C','C',
        'C','C','C','C','C','C','C','C','C'
    };

    const uint8_t* page_texts[TOTAL] = { p1, p2, p3 };

    // compactText() により完成時は NUL ホールが詰められ、[ptr, ptr+len) は連続したテキストになる。aggregated_len は論理的な結合長 (NUL 打ち切り後)。
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

            CHECK(nankai->aggregated_len == EXPECTED_LEN);
            CHECK(nankai->aggregated_text_ptr != nullptr);
            CHECK(memcmp(nankai->aggregated_text_ptr, expected_compact, EXPECTED_LEN) == 0);
        }
    }

    const azaraC::Mt43Data* mt43 = msg.getMt43();
    REQUIRE(mt43 != nullptr);
    const azaraC::NankaiData* nankai = mt43->getNankai();
    REQUIRE(nankai != nullptr);
    CHECK(nankai->is_aggregated == true);
    CHECK(nankai->aggregated_len == EXPECTED_LEN);
    CHECK(nankai->aggregated_text_ptr != nullptr);
    CHECK(memcmp(nankai->aggregated_text_ptr, expected_compact, EXPECTED_LEN) == 0);

    const NankaiPageBuffer* buf = parser.getNankaiBuffer(NankaiPageKey{5, 0, 0, 0, 0, 0, 2});
    REQUIRE(buf != nullptr);
    CHECK(buf->getTextLength() == EXPECTED_LEN);

    // compact 済みで embedded NUL がないため JSON は text_utf8 を使う
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

    azaraC::Parser parser;
    azaraC::Message msg;
    uint8_t bits[32];
    constexpr uint8_t SKIP_PAGE = 14;

    // フェーズ 1: 飛ばしたページ以外をすべて入力
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
        CHECK_FALSE(output);
    }

    // フェーズ 2: ページ 14 が欠けたままでは集約は未完了（コールバックを得るにはページ 27 を再投入する）。
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
        CHECK_FALSE(output);
    }

    // フェーズ 3: 欠けていたページ 14 を投入すると集約が完了する。
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

        uint8_t expected_body[27 * azaraC::internal::NankaiPageBuffer::TEXT_PER_PAGE] = {};
        const uint16_t expected_len = compactPages(nankai_page_data, 27, expected_body);
        REQUIRE(nankai->aggregated_text_ptr != nullptr);
        CHECK(nankai->aggregated_len == expected_len);
        CHECK(memcmp(nankai->aggregated_text_ptr, expected_body, expected_len) == 0);
    }
}
#endif // AZARAC_NANKAI_MAX_PAGES >= 27

// 鍵は report_time 由来で固定なので、report_unix が途中で解決しても解決済み/未解決で identity は変わらない（1 バッファに集約される）。

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
        // 先頭ページは基準時刻なし、残りページは妥当な report_unix を与える。
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

// report_* は resolveTime を通らないので、暦上正規化される日付でも解決状況に依存せず 1 バッファに集約される。

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

// 打ち切り（total_pages > MAX_PAGES）E2E テスト。MAX_PAGES は NankaiPageBuffer から取得（既定値非依存）。
// 6bit フィールド（<=63）に収まる MAX_PAGES+2 でのみ成立し、MAX_PAGES=63（仕様最大）では打ち切りが起きず #if で除外される。

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

// Nankai 63ページ最大集約 E2E テスト。
// total_page は6ビット（最大63）で、63ページ×18バイト=1134バイトは aggregated_text[1135]（1134+ヌル終端）にちょうど収まる。
// ページ1-27はazarashi検証済みデータ、ページ28-63は合成データを使用。

#if AZARAC_NANKAI_MAX_PAGES >= 63
TEST_CASE("Nankai E2E: 63-page maximum aggregation (protocol limit)") {
    constexpr uint8_t TOTAL = 63;  // 6-bit max
    static_assert(TOTAL * NankaiPageBuffer::TEXT_PER_PAGE <= 1134, "exceeds aggregated_text buffer");

    azaraC::Parser parser;
    azaraC::Message msg;
    uint8_t bits[32];

    // ページ 1-27 は azarashi の実データ、28-63 は合成の埋め草（仕様最大ページ数）。
    static const uint8_t filler[NankaiPageBuffer::TEXT_PER_PAGE] = {
        0xE3,0x81,0x8A,0xE3,0x81,0x86,0xE3,0x81,0x8B,
        0xE3,0x82,0x93,0xE3,0x82,0x80,0xE3,0x82,0x8A
    };

    uint8_t pages63[TOTAL][NankaiPageBuffer::TEXT_PER_PAGE];
    for (uint8_t p = 0; p < TOTAL; ++p) {
        const uint8_t* src = (p < 27) ? nankai_page_data[p] : filler;
        memcpy(pages63[p], src, NankaiPageBuffer::TEXT_PER_PAGE);
    }

    uint8_t expected_body_63[TOTAL * NankaiPageBuffer::TEXT_PER_PAGE];
    const uint16_t EXPECTED_AGG_LEN_63 = compactPages(pages63, TOTAL, expected_body_63);

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
            CHECK(memcmp(nankai->aggregated_text_ptr, expected_body_63, EXPECTED_AGG_LEN_63) == 0);
        }
    }

    const azaraC::Mt43Data* mt43 = msg.getMt43();
    REQUIRE(mt43 != nullptr);
    const azaraC::NankaiData* nankai = mt43->getNankai();
    REQUIRE(nankai != nullptr);
    CHECK(nankai->is_aggregated == true);
    CHECK(nankai->aggregated_len == EXPECTED_AGG_LEN_63);
    CHECK(memcmp(nankai->aggregated_text_ptr, expected_body_63, EXPECTED_AGG_LEN_63) == 0);

    // 安定部分の検証: 前文（ページ 1）と後文（ページ 63 = 埋め草）
    CHECK(memcmp(nankai->aggregated_text_ptr,
                 nankai_page_data[0], NankaiPageBuffer::TEXT_PER_PAGE) == 0);
    CHECK(memcmp(nankai->aggregated_text_ptr + EXPECTED_AGG_LEN_63 - NankaiPageBuffer::TEXT_PER_PAGE,
                 filler, NankaiPageBuffer::TEXT_PER_PAGE) == 0);

    StringPrint sp;
    internal::JsonSerializer::serialize(msg, sp);
    const auto& s = sp.str();
    CHECK(s.find("\"text_utf8\":") != std::string::npos);
    CHECK(s.find("\"text_hex\"") == std::string::npos);
}
#endif // AZARAC_NANKAI_MAX_PAGES >= 63
#endif // AZARAC_ENABLE_NANKAI
