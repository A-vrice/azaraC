#pragma once
// 南海トラフ地震の複数ページ集約バッファページは aggregated_text[] の (page_num-1)*TEXT_PER_PAGE へ直接書き、受信済みページは 64 bit の bitmap で管理する。
// PageData 配列を持たないので（MAX_PAGES=63 で約 1 KB 節約）ソートも不要で、重複判定は O(1)。
// total_pages > MAX_PAGES なら打ち切る。

#if defined(__AVR__)
#include "avr_std/cstdint"
#else
#include <cstdint>
#endif
#if defined(__AVR__)
#include "avr_std/cstddef"
#else
#include <cstddef>
#endif
#if defined(__AVR__)
#include "avr_std/cstring"
#else
#include <cstring>
#endif
#include "../azaraC_config.h"

namespace azaraC {
namespace internal {

// 事象の鍵。svid は除外（複数衛星が同一電文を中継するため重複する）。
// identity = {info_code, information_type, report_classification, 生の report_time DHM}。
// DHM は正規化前の生プロトコルビット（NankaiData::report_*）:
// Mt43Data::event_time は resolveTime() が 2/30→3/1 を書き換え月 0 を補完するため、report_unix の有無でハッシュが割れ、1 事象が複数バッファに分かれる。
// information_type（It: 0=発表 / 2=取消）も鍵に必要（無いと発表と取消が同じ Pn を先着優先で潰し合い文面が混ざる）。
// report_classification（Rc: 2=実警報 / 7=訓練・試験）も鍵に必要。含めないと訓練が実警報を抑止し、
// 訓練ページと実警報ページが同じ集約バッファで連結される。
// dedup 側も同じ 7 フィールドを使う（Dedup.h dedupEventToken）。
struct NankaiPageKey {
    uint8_t  info_code = 0;             // 1B — Is（情報系列コード、4b）
    uint8_t  report_month  = 0;         // 1B — 生の report_time 月 (4b)
    uint8_t  report_day    = 0;         // 1B — 生の report_time 日 (5b)
    uint8_t  report_hour   = 0;         // 1B — 生の report_time 時 (5b)
    uint8_t  report_minute = 0;         // 1B — 生の report_time 分 (6b)
    uint8_t  information_type = 0;      // 1B — It (2b: 0=発表, 2=取消)
    uint8_t  report_classification = 0; // 1B — Rc (3b: 2=実警報, 7=訓練/試験)
    // 合計 7B（パディングなし）

    constexpr NankaiPageKey() = default;
    // it / rc は末尾の既定引数（既存呼び出し {ic, mo, d, h, m} の意味を変えない）。
    constexpr NankaiPageKey(uint8_t ic, uint8_t mo = 0, uint8_t d = 0, uint8_t h = 0, uint8_t m = 0,
                            uint8_t it = 0, uint8_t rc = 0)
        : info_code(ic), report_month(mo), report_day(d), report_hour(h),
          report_minute(m), information_type(it), report_classification(static_cast<uint8_t>(rc & 0x7u)) {}

    bool operator==(const NankaiPageKey& o) const {
        return info_code == o.info_code &&
               information_type == o.information_type &&
               report_classification == o.report_classification &&
               report_month  == o.report_month &&
               report_day    == o.report_day &&
               report_hour   == o.report_hour &&
               report_minute == o.report_minute;
    }

    void clear() {
        info_code = 0;
        information_type = 0;
        report_classification = 0;
        report_month = 0;
        report_day = 0;
        report_hour = 0;
        report_minute = 0;
    }
};

// 7 バイト（パディングなし）を固定する: 鍵はページ受信のたびにコピーされ、バッファごとに 1 個常駐する。
static_assert(sizeof(NankaiPageKey) == 7, "NankaiPageKey must stay 7 bytes");

// addPageEx の結果。Duplicate は受信済みページで、本文・受信数は変えないが last_update_ms は更新する。
enum class NankaiPageAddResult : uint8_t {
    Rejected,
    Added,
    Duplicate
};

// 集約結果。DuplicateComplete は完成済みバッファへの受信済みページ再送で、
// dedup 履歴の更新だけを行い、本文は再出力しないために使う。
enum class NankaiAggregateResult : uint8_t {
    Rejected,
    NotComplete,
    Complete,
    DuplicateComplete
};

// 1 事象分のページ集約バッファ。
// 打ち切り: total_pages > MAX_PAGES なら pages 1..MAX_PAGES を残して truncated を立て、残りは静かに破棄する。
// ページ数上限・バッファ数は azaraC_config.h の AZARAC_NANKAI_MAX_PAGES / AZARAC_NANKAI_BUFFERS が唯一の定義元（範囲は spec の Pn/Pm: 1-63, 6bit）。

// MAX_PAGES は 64-bit bitmap に収まる 63 まで（spec の Pn/Pm 上限）
static_assert(AZARAC_NANKAI_MAX_PAGES > 0 && AZARAC_NANKAI_MAX_PAGES <= 63,
              "AZARAC_NANKAI_MAX_PAGES must be in range 1-63");

struct NankaiPageBuffer {
    static constexpr uint8_t MAX_PAGES = AZARAC_NANKAI_MAX_PAGES;
    static constexpr uint8_t SPEC_MAX_PAGES = 63;  // 仕様の最大（6 bit）
    static constexpr uint8_t TEXT_PER_PAGE = 18;
    static constexpr uint32_t TIMEOUT_MS = 60000;

    NankaiPageKey key;                  // 7B
    uint64_t received_bitmap = 0;       // 8B — bit (page_num-1) が受信済みの印
    uint32_t last_update_ms = 0;        // 4B — TIMEOUT_MS=60s なので 32 bit 差分比較で十分（49.7 日でラップ）
    uint8_t total_pages = 0;            // 1B — 実効ページ数（MAX_PAGES で頭打ち）
    uint8_t original_total_pages = 0;   // 1B — 電文が示す元のページ数
    uint8_t received_count = 0;         // 1B — 受信したページ数
    bool truncated : 1;                 // 1b — total_pages > MAX_PAGES のとき true
    bool compacted : 1;                 // 1b — compactText() がページを詰めた後 true（getTextLength の読み方を切り替える）
    // aggregated_text はオフセット 24 (host) / 23 (AVR) — char の境界は 1 なのでその前にパディングが無い
    char aggregated_text[MAX_PAGES * TEXT_PER_PAGE + 1];

    NankaiPageBuffer() : aggregated_text{} {
        clearAll();
    }

    // ページ番号と総ページ数の組が集約対象として妥当か。
    // total > MAX_PAGES は現行契約どおり受け付け、総ページ数を MAX_PAGES に丸める（呼び出し側で truncated を立てる）。
    static constexpr bool pageInRange(uint8_t page_num, uint8_t total_pages_in) {
        const uint8_t effective_total = total_pages_in > MAX_PAGES ? MAX_PAGES : total_pages_in;
        return page_num >= 1 && page_num <= SPEC_MAX_PAGES && page_num <= effective_total;
    }

    // ページを追加する（page_num は 1 始まり、total_pages_in は Pm 由来、text_data は 18 バイト）。
    // 追加できたら true。既存テストとの互換用ラッパー。
    bool addPage(uint8_t page_num, uint8_t total_pages_in, const uint8_t* text_data, uint64_t current_ms) {
        return addPageEx(page_num, total_pages_in, text_data, current_ms) == NankaiPageAddResult::Added;
    }

    // 追加結果を区別する実体。Duplicate は受信済みページで、本文・受信数は変えず last_update_ms だけ更新する。
    NankaiPageAddResult addPageEx(uint8_t page_num, uint8_t total_pages_in,
                                  const uint8_t* text_data, uint64_t current_ms) {
        // 検証を状態変更より先に行う。不正ページで既存の total_pages/truncated を汚さない。
        if (!pageInRange(page_num, total_pages_in)) {
            return NankaiPageAddResult::Rejected;
        }

        uint8_t effective_total = total_pages_in > MAX_PAGES ? MAX_PAGES : total_pages_in;

        if (this->total_pages == 0) {
            this->total_pages = effective_total;
            this->original_total_pages = total_pages_in;
            // truncated は有効な初回ページを受け付けたときだけ立てる。
            truncated = (total_pages_in > MAX_PAGES);
        }

        // 以降の total_pages_in は初回値と一致必須
        if (this->original_total_pages != total_pages_in) {
            return NankaiPageAddResult::Rejected;
        }

        // bitmap による重複判定 O(1)
        uint64_t mask = 1ULL << (page_num - 1);
        if (received_bitmap & mask) {
            // F-2: 重複ページの再送でも集約の寿命を延ばす。
            // 本文・受信数は変えない。再出力の抑止は dedup 側で別に扱う。
            last_update_ms = (uint32_t)current_ms;
            return NankaiPageAddResult::Duplicate;
        }

        uint16_t offset = static_cast<uint16_t>(page_num - 1) * TEXT_PER_PAGE;
        memcpy(aggregated_text + offset, text_data, TEXT_PER_PAGE);
        received_bitmap |= mask;
        received_count++;
        last_update_ms = (uint32_t)current_ms;

        return NankaiPageAddResult::Added;
    }

    bool isComplete() const {
        if (total_pages == 0) return false;
        return received_count >= total_pages;
    }

    // NUL を除いたテキスト長。ページごとに最初の 0x00 で止まる（UTF-8 に NUL は無い）。
    // 未完成のバッファでも安全（受信済みページしか読まない）。
    // compactText() 後は本文が先頭から連続しているため、ページ割り付けではなく文字列長を返す。
    uint16_t getTextLength() const {
        if (compacted) {
            uint16_t n = 0;
            while (n < (uint16_t)(MAX_PAGES * TEXT_PER_PAGE) && aggregated_text[n] != 0) ++n;
            return n;
        }

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

    // 受信済みページを連続した C 文字列へ詰める（完成時のみ呼ぶ）。
    // 最終ページ以外は短いことがある（NUL の穴）— serialize は [ptr, ptr+len) を連続で出力するので、穴があると NUL が漏れる。
    // その場での圧縮は安全: 常に w <= p*TEXT_PER_PAGE で、書き込みが次のソースページに達することはない。
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
        compacted = true;
        return w;
    }

    bool isExpired(uint64_t current_ms) const {
        if (total_pages == 0) return false;
        // 通常の 32 bit 折り返しは符号なし差分で扱う。2^32 ms 以上の空白は
        // Parser::postDecodeAt() の epoch guard が先に全バッファを消す。
        return (uint32_t)(current_ms - last_update_ms) > TIMEOUT_MS;
    }

    void clearAll() {
        key.clear();
        total_pages = 0;
        original_total_pages = 0;
        received_count = 0;
        received_bitmap = 0;
        last_update_ms = 0;
        truncated = false;
        compacted = false;
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
    // ページ別の実効長（最初の NUL まで、TEXT_PER_PAGE 上限）
    uint8_t pageTextLength_(const char* page_start) const {
        uint8_t n = 0;
        while (n < TEXT_PER_PAGE && page_start[n] != 0) ++n;
        return n;
    }
};

// 正確な配置: docs/api-reference.md と docs/architecture.md がこのサイズを引用している。
// AZARAC_AVR_STUB は __AVR__ を定義しつつホスト ABI を使うので、期待値はホスト側と同じ。
#if AZARAC_NANKAI_MAX_PAGES == 63
#  if defined(__AVR__) && !defined(AZARAC_AVR_STUB)
static_assert(sizeof(NankaiPageBuffer) == 1158, "NankaiPageBuffer AVR layout");
static_assert(offsetof(NankaiPageBuffer, aggregated_text) == 23, "aggregated_text AVR offset");
#  else
static_assert(sizeof(NankaiPageBuffer) == 1160, "NankaiPageBuffer host/stub layout");
static_assert(offsetof(NankaiPageBuffer, aggregated_text) == 24, "aggregated_text host/stub offset");
#  endif
#elif AZARAC_NANKAI_MAX_PAGES == 4 && defined(__AVR__) && !defined(AZARAC_AVR_STUB)
static_assert(sizeof(NankaiPageBuffer) == 96, "NankaiPageBuffer AVR preset layout");
static_assert(offsetof(NankaiPageBuffer, aggregated_text) == 23, "aggregated_text AVR preset offset");
#endif

// 複数のページバッファを bitmap 追跡 + LRU 追い出しで管理する。バッファ数 = AZARAC_NANKAI_BUFFERS（azaraC_config.h）。

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

    // ページを追加し、全ページ受信ならそのバッファへのポインタ、そうでなければ nullptr を返す。
    // 既存呼び出しとの互換用ラッパー。
    NankaiPageBuffer* addPage(const NankaiPageKey& key, uint8_t page_num,
                               uint8_t total_pages, const uint8_t* text_data,
                               uint64_t current_ms) {
        NankaiPageBuffer* completed = nullptr;
        const NankaiAggregateResult result = addPageEx(key, page_num, total_pages, text_data,
                                                       current_ms, &completed);
        return result == NankaiAggregateResult::Complete ? completed : nullptr;
    }

    // 受信結果を Complete / DuplicateComplete / NotComplete / Rejected で返す。
    // completed は Complete のときだけ設定する。
    NankaiAggregateResult addPageEx(const NankaiPageKey& key, uint8_t page_num,
                                    uint8_t total_pages, const uint8_t* text_data,
                                    uint64_t current_ms, NankaiPageBuffer** completed) {
        if (completed) *completed = nullptr;
        expireBuffers(current_ms);

        // 不正ページのために既存の進行中バッファを clearAll() しない。
        // バッファ内の total_pages 不一致検証は既存状態が必要なので addPageEx() 側に残す。
        if (!NankaiPageBuffer::pageInRange(page_num, total_pages)) {
            return NankaiAggregateResult::Rejected;
        }

        int8_t idx = findBuffer(key);

        if (idx < 0) {
            idx = findEmptyBuffer();
            if (idx < 0) {
                idx = findOldestBuffer(current_ms);
            }
            _buffers[idx].clearAll();
            _buffers[idx].setKey(key);
        }

        const NankaiPageAddResult page_result =
            _buffers[idx].addPageEx(page_num, total_pages, text_data, current_ms);
        if (page_result == NankaiPageAddResult::Rejected) {
            return NankaiAggregateResult::Rejected;
        }
        if (page_result == NankaiPageAddResult::Duplicate) {
            return _buffers[idx].isComplete()
                ? NankaiAggregateResult::DuplicateComplete
                : NankaiAggregateResult::NotComplete;
        }
        if (_buffers[idx].isComplete()) {
            if (completed) *completed = &_buffers[idx];
            return NankaiAggregateResult::Complete;
        }
        return NankaiAggregateResult::NotComplete;
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

    // 追い出し: 最終更新が最も古いバッファを選ぶ（同値なら先頭スロット。真の LRU ではない）。
    // 呼び出し元は findEmptyBuffer() < 0 のときだけ呼ぶので、空バッファは存在しない（age 0 分岐は不要）。
    // 符号なし減算でラップに強い。expireBuffers() が毎回 60s 超を回収するので age は常に 60s 以下。
    int8_t findOldestBuffer(uint64_t current_ms) {
        uint32_t max_age = 0;
        int8_t oldest_idx = 0;

        for (uint8_t i = 0; i < MAX_BUFFERS; ++i) {
            const uint32_t age = (uint32_t)(current_ms - _buffers[i].last_update_ms);
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
