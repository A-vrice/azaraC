// 南海トラフ単体テスト E2E は test_nankai_e2e.cpp

#include <string>
#include <chrono>
#include "doctest.h"
#include "../src/internal/NankaiPageBuffer.h"
#include "../src/Parser.h"
#include "../test_helpers.h"

using namespace azaraC::internal;

// 現在時刻（ms、非 Arduino）。NANKAI 無効時は呼び出しが消えるため maybe_unused。
[[maybe_unused]] static uint32_t currentMillis() {
    auto now = std::chrono::steady_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch()).count();
    return static_cast<uint32_t>(ms);
}

#if (AZARAC_ENABLE_NANKAI)
TEST_CASE("NankaiPageKey equality") {
    // identity = info_code + information_type + report_classification + report_time DHM（月/日/時/分）。
    NankaiPageKey key1 = {1, 4, 10, 30, 15, 0, 2};
    NankaiPageKey key2 = {1, 4, 10, 30, 15, 0, 2};
    NankaiPageKey key3 = {2, 4, 10, 30, 15, 0, 2};  // different info_code
    NankaiPageKey key4 = {1, 4, 10, 30, 16, 0, 2};  // different minute
    NankaiPageKey key5 = {1, 5, 10, 30, 15, 0, 2};  // different month
    NankaiPageKey key6 = {1, 4, 10, 30, 15, 2, 2};  // different information_type (取消)
    NankaiPageKey key7 = {1, 4, 10, 30, 15, 0, 7};  // different report_classification (訓練)

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

    SUBCASE("Different information_type") {
        // 発表(0) と取消(2) は同一 info_code + 同一報告時刻でも別の情報。
        CHECK(!(key1 == key6));
    }

    SUBCASE("Different report_classification") {
        // 訓練/試験(7) と実警報(2) は同一 info_code + 同一報告時刻でも別の情報。
        CHECK(!(key1 == key7));
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
        CHECK(buffer.received_bitmap == 0x7ULL);
    }
    
    SUBCASE("Duplicate page is rejected") {
        uint8_t text[18] = {'T', 'e', 's', 't', 0};
        
        buffer.addPage(1, 2, text, now);
        bool result = buffer.addPage(1, 2, text, now);
        
        CHECK(!result);
        CHECK(buffer.received_count == 1);
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
    // total_pages > MAX_PAGES なら total_pages を MAX_PAGES（ライブラリ既定、上書き可）に丸め、truncated フラグを立てる。
    // SPEC_MAX_PAGES=63 なので MAX_PAGES=63 のビルドを超え得るのは total_pages>63 のみ。page_num は SPEC_MAX_PAGES 以下でなければならない。
    NankaiPageBuffer buffer;
    uint32_t now = currentMillis();
    
    SUBCASE("total_pages > MAX_PAGES sets truncated flag") {
        uint8_t text[18] = {'T', 'e', 's', 't', 0};
        
        // total_pages=99 は MAX_PAGES で頭打ち
        bool result = buffer.addPage(1, 99, text, now);
        
        CHECK(result);
        CHECK(buffer.truncated);
        CHECK(buffer.total_pages == NankaiPageBuffer::MAX_PAGES);  // capped
        CHECK(buffer.original_total_pages == 99);  // original preserved
    }
    
    SUBCASE("Truncated buffer completes when MAX_PAGES pages received") {
        uint8_t text[18] = {'T', 'e', 's', 't', 0};
        
        buffer.addPage(1, 99, text, now);
        CHECK_FALSE(buffer.isComplete());
        
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
        // MAX_PAGES 超のページ番号は先に範囲チェックで拒否される（effective_total=MAX_PAGES でも拒否）。
        bool result = buffer.addPage(static_cast<uint8_t>(NankaiPageBuffer::MAX_PAGES + 1), 99, text, now);
        
        CHECK_FALSE(result);
    }
    
    SUBCASE("Invalid first page does not set truncated or total_pages") {
        uint8_t text[18] = {'T', 'e', 's', 't', 0};
        CHECK_FALSE(buffer.addPage(2, 1, text, now));
        CHECK_FALSE(buffer.truncated);
        CHECK(buffer.total_pages == 0);
        CHECK(buffer.isEmpty());
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

    SUBCASE("getTextLength after compactText uses the contiguous text") {
        uint8_t text1[18] = {'P', '1', 0};
        uint8_t text2[18] = {'P', '2', 0};
        uint8_t text3[18] = {'P', '3', 0};
        buffer.addPage(1, 3, text1, now);
        buffer.addPage(2, 3, text2, now);
        buffer.addPage(3, 3, text3, now);
        CHECK(buffer.getTextLength() == 6);

        CHECK(buffer.compactText() == 6);
        CHECK(buffer.compacted);
        CHECK(buffer.getTextLength() == 6);  // ページ割り付けではなく連続文字列として読む
        CHECK(memcmp(buffer.aggregated_text, "P1P2P3", 6) == 0);
    }

    SUBCASE("getTextLength after compactText with a missing page") {
        uint8_t text1[18] = {'P', '1', 0};
        uint8_t text3[18] = {'P', '3', 0};
        CHECK(buffer.addPage(1, 3, text1, now));
        CHECK(buffer.addPage(3, 3, text3, now));
        CHECK_FALSE(buffer.isComplete());

        CHECK(buffer.compactText() == 4);
        CHECK(buffer.getTextLength() == 4);
        CHECK(memcmp(buffer.aggregated_text, "P1P3", 4) == 0);
    }

    SUBCASE("clearAll restores the page-offset length path") {
        uint8_t text[18] = {'P', '1', 0};
        buffer.addPage(1, 1, text, now);
        CHECK(buffer.compactText() == 2);
        CHECK(buffer.compacted);

        buffer.clearAll();
        CHECK_FALSE(buffer.compacted);
        CHECK(buffer.getTextLength() == 0);

        uint8_t page2[18] = {'A', 'B', 0};
        CHECK(buffer.addPage(2, 3, page2, now));
        CHECK_FALSE(buffer.compacted);
        CHECK(buffer.getTextLength() == 2);  // 空のページ 1 を飛ばしてページ 2 を読む
    }
}



TEST_CASE("NankaiPageBufferManager") {
    NankaiPageBufferManager manager;
    
    SUBCASE("Add page to new buffer") {
        NankaiPageKey key = {1};
        uint8_t text[18] = {'T', 'e', 's', 't', 0};
        
        NankaiPageBuffer* result = manager.addPage(key, 1, 1, text, currentMillis());
        
        REQUIRE(result != nullptr);
        CHECK(manager.getBuffer(key) == result);
        CHECK(result->total_pages == 1);
        CHECK(result->received_count == 1);
        CHECK(result->received_bitmap == (1ULL << 0));
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

    SUBCASE("Invalid page for a new key does not evict an in-progress event") {
        NankaiPageKey keyA = {1};
        NankaiPageKey keyB = {2};
        uint8_t text1[18] = {'A', '1', 0};
        uint8_t text2[18] = {'A', '2', 0};
        const uint32_t now = currentMillis();

        CHECK(manager.addPage(keyA, 1, 2, text1, now) == nullptr);
        REQUIRE(manager.getBuffer(keyA) != nullptr);

        // page > total の不正ページは、別鍵の新規バッファを割り当ててはいけない。
        CHECK(manager.addPage(keyB, 2, 1, text1, now) == nullptr);
        CHECK(manager.getBuffer(keyA) != nullptr);
        CHECK(manager.getBuffer(keyB) == nullptr);
        CHECK(manager.getBuffer(keyA)->received_count == 1);

        // 事象Aの残りページは引き続き完成できる。
        CHECK(manager.addPage(keyA, 2, 2, text2, now) != nullptr);
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

TEST_CASE("NankaiPageBufferManager aggregate status") {
    NankaiPageBufferManager manager;
    NankaiPageKey key = {1};
    uint8_t text[18] = {'T', 'e', 's', 't', 0};
    NankaiPageBuffer* completed = nullptr;

    CHECK(manager.addPageEx(key, 1, 2, text, 1000, &completed) ==
          NankaiAggregateResult::NotComplete);
    CHECK(completed == nullptr);

    // 未完成バッファの重複ページは Complete ではない。
    CHECK(manager.addPageEx(key, 1, 2, text, 1001, &completed) ==
          NankaiAggregateResult::NotComplete);
    CHECK(completed == nullptr);

    CHECK(manager.addPageEx(key, 2, 2, text, 1002, &completed) ==
          NankaiAggregateResult::Complete);
    REQUIRE(completed != nullptr);

    // 完成済みバッファの受信済みページ再送。
    completed = nullptr;
    CHECK(manager.addPageEx(key, 1, 2, text, 1003, &completed) ==
          NankaiAggregateResult::DuplicateComplete);
    CHECK(completed == nullptr);
}

TEST_CASE("NankaiPageBufferManager buffer limit") {
    NankaiPageBufferManager manager;
    
    SUBCASE("Max buffers is configurable") {
        uint32_t now = currentMillis();
        for (uint8_t i = 0; i < NankaiPageBufferManager::MAX_BUFFERS; i++) {
            NankaiPageKey key = {static_cast<uint8_t>(i + 1)};
            uint8_t text[18] = {'T', 'e', 's', 't', 0};
            manager.addPage(key, 1, 1, text, now);
        }
        
        // もう 1 つ追加すると最も古いバッファが追い出される。
        NankaiPageKey key_new = {static_cast<uint8_t>(NankaiPageBufferManager::MAX_BUFFERS + 1)};
        uint8_t text[18] = {'N', 'e', 'w', 0};
        manager.addPage(key_new, 1, 1, text, now);
        
        NankaiPageKey key0 = {1};
        CHECK(manager.getBuffer(key0) == nullptr);
        
        CHECK(manager.getBuffer(key_new) != nullptr);
    }
}

#if AZARAC_NANKAI_BUFFERS >= 2
TEST_CASE("NankaiPageBufferManager eviction respects report_classification (F-1)") {
    NankaiPageBufferManager manager;
    uint8_t text[18] = {'T', 'e', 's', 't', 0};
    const NankaiPageKey realAlert = {1, 9, 14, 19, 1, 0, 2};   // 実警報 Rc=2
    const NankaiPageKey realAlert2 = {2, 9, 14, 19, 3, 0, 2};  // 別の実警報 Rc=2
    const NankaiPageKey training = {3, 9, 14, 19, 5, 0, 7};    // 訓練 Rc=7
    const NankaiPageKey training2 = {4, 9, 14, 19, 9, 0, 7};   // 別の訓練 Rc=7

    SUBCASE("Training event evicts training, not the older real alert") {
        manager.addPageEx(realAlert, 1, 10, text, 0, nullptr);
        manager.addPageEx(training, 1, 10, text, 10000, nullptr);
        manager.addPageEx(training2, 1, 10, text, 20000, nullptr);

        CHECK(manager.getBuffer(realAlert) != nullptr);
        CHECK(manager.getBuffer(training) == nullptr);
        CHECK(manager.getBuffer(training2) != nullptr);

        // 実警報の集約はリセットされず、続きから集まる。
        manager.addPageEx(realAlert, 2, 10, text, 24000, nullptr);
        REQUIRE(manager.getBuffer(realAlert) != nullptr);
        CHECK(manager.getBuffer(realAlert)->received_count == 2);
    }

    SUBCASE("Training page is dropped rather than evicting a real alert") {
        manager.addPageEx(realAlert, 1, 10, text, 0, nullptr);
        manager.addPageEx(realAlert2, 1, 10, text, 10000, nullptr);

        CHECK(manager.addPageEx(training, 1, 10, text, 20000, nullptr) ==
              NankaiAggregateResult::Rejected);
        CHECK(manager.getBuffer(realAlert) != nullptr);
        CHECK(manager.getBuffer(realAlert2) != nullptr);
        CHECK(manager.getBuffer(training) == nullptr);
    }

    SUBCASE("Real alert evicts the oldest training buffer") {
        manager.addPageEx(training, 1, 10, text, 0, nullptr);
        manager.addPageEx(training2, 1, 10, text, 10000, nullptr);
        manager.addPageEx(realAlert, 1, 10, text, 20000, nullptr);

        CHECK(manager.getBuffer(training) == nullptr);
        CHECK(manager.getBuffer(training2) != nullptr);
        CHECK(manager.getBuffer(realAlert) != nullptr);
    }

    SUBCASE("Eviction among real alerts stays oldest-first") {
        const NankaiPageKey realAlert3 = {5, 9, 14, 19, 12, 0, 2};
        manager.addPageEx(realAlert, 1, 10, text, 0, nullptr);
        manager.addPageEx(realAlert2, 1, 10, text, 10000, nullptr);
        manager.addPageEx(realAlert3, 1, 10, text, 20000, nullptr);

        CHECK(manager.getBuffer(realAlert) == nullptr);
        CHECK(manager.getBuffer(realAlert2) != nullptr);
        CHECK(manager.getBuffer(realAlert3) != nullptr);
    }
}
#endif // AZARAC_NANKAI_BUFFERS >= 2

TEST_CASE("NankaiPageBufferManager empty slots never match") {
    NankaiPageBufferManager manager;
    NankaiPageKey zero;  // all-zero identity

    // 空スロットは全ゼロの鍵を持つ。getBuffer を返してはならない。
    CHECK(manager.getBuffer(zero) == nullptr);

    uint8_t text[18] = {'T', 'e', 's', 't', 0};
    manager.addPage(zero, 1, 2, text, 1000);
    CHECK(manager.getBuffer(zero) != nullptr);
    // 同じゼロ鍵の事象は新しい空スロットではなく元のバッファへ続く。
    CHECK(manager.addPage(zero, 2, 2, text, 1000) != nullptr);
}

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

        // タイムアウトを過ぎて触れば、古いバッファは失効する。
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
    // 2 つのバッファが同じ古さなら、タイムアウト超過で両方失効する。LRU 1 件の追い出しでは 1 件しか落ちない。
    manager.addPage({3, 4, 10, 30, 15}, 1, 1, text,
                    1000 + NankaiPageBuffer::TIMEOUT_MS + 1);
    CHECK(manager.getBuffer(k1) == nullptr);
    CHECK(manager.getBuffer(k2) == nullptr);
}

TEST_CASE("NankaiPageBufferManager: zero key follows its buffer across slot reuse") {
    NankaiPageBufferManager manager;
    uint8_t text[18] = {'T', 'e', 's', 't', 0};
    NankaiPageKey nonzero = {7, 6, 15, 12, 30};
    NankaiPageKey zero;

    CHECK(manager.addPage(nonzero, 1, 2, text, 0) == nullptr);        // slot 0 (stale later)
    CHECK(manager.addPage(zero, 1, 2, text, 30000) == nullptr);       // slot 1

    // t=70000 で slot 0 が失効する。ゼロ鍵のページは空になった slot 0 ではなく自分のバッファ（slot 1）へ続く。
    NankaiPageBuffer* done = manager.addPage(zero, 2, 2, text, 70000);
    CHECK(done != nullptr);
}
#endif // AZARAC_NANKAI_BUFFERS >= 2

#endif // AZARAC_ENABLE_NANKAI
