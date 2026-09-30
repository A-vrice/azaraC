// test/integration/test_no_alloc.cpp — ライブラリが動的確保を行わないことの検証
//
// 公開 API（Parser::feed / toJson）が malloc/calloc/realloc/posix_memalign と
// operator new/new[] を一切呼ばないことを、リンカの --wrap で計測した生カウンタで
// 検証する。Valgrind Massif と違い「ライブラリ自身の確保が 0 か」を直接示す。
//
// --wrap の制約: 未解決参照のみ差し替える。計測区間（snapshot〜delta）は
// ライブラリ呼び出しの前後だけに置き、テスト基盤（doctest / std::string など）の
// 確保を混ぜない。このファイル内の std::string 使用は計測区間外に限る。
//
// 出力が空になる構成（該当カテゴリが AZARAC_ENABLE_*=0）でも計測が空回りしない
// よう、「この構成で必ずデコードできる」電文を #if で選ぶ。全カテゴリが無効な
// 構成では JSON 出力の確認をスキップする（確保ゼロの assert は常に生きる）。
//
// ホストビルド専用（test/Makefile の test-no-alloc）。GNU ld の --wrap が必要で、
// macOS の ld64 では利用できない。

#include "../test_helpers.h"
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <cstdlib>
#include <new>
#if (AZARAC_ENABLE_NANKAI) && (AZARAC_NANKAI_MAX_PAGES >= 27)
#include "../data/nankai_pages_generated.h"
#endif

namespace noalloc {
unsigned long g_allocs = 0;
inline unsigned long snapshot() { return g_allocs; }
inline unsigned long delta(unsigned long base) { return g_allocs - base; }
}  // namespace noalloc

// --- C アロケータを --wrap で差し替えてカウントする ---
extern "C" {
void* __real_malloc(size_t);
void* __real_calloc(size_t, size_t);
void* __real_realloc(void*, size_t);
void* __wrap_malloc(size_t size) { ++noalloc::g_allocs; return __real_malloc(size ? size : 1); }
void* __wrap_calloc(size_t n, size_t size) { ++noalloc::g_allocs; return __real_calloc(n, size); }
void* __wrap_realloc(void* p, size_t size) { ++noalloc::g_allocs; return __real_realloc(p, size); }
int __wrap_posix_memalign(void** out, size_t align, size_t size) {
    (void)align; (void)size;
    ++noalloc::g_allocs;
    if (out) *out = nullptr;
    return 12;  // ENOMEM。呼ばれた時点で失敗させる（この経路が通らない前提の計測用）
}
}

// --- operator new / new[] も置換してカウントする。本体が std::malloc を明示的に
// 呼ぶため、置換した new 経由の 1 回の確保は __wrap_malloc でも数えられ 2 回加算
// される（テストは >= 1 しか要求しない）。---
void* operator new(size_t size) {
    ++noalloc::g_allocs;
    void* p = std::malloc(size ? size : 1);
    if (!p) throw std::bad_alloc();
    return p;
}
void* operator new[](size_t size) { return ::operator new(size); }
void operator delete(void* p) noexcept { std::free(p); }
void operator delete[](void* p) noexcept { std::free(p); }
void operator delete(void* p, size_t) noexcept { std::free(p); }
void operator delete[](void* p, size_t) noexcept { std::free(p); }

namespace {

// 出力先。bytes は「JSON を実際に書いたか」の確認用で、自身は確保しない。
struct CountingPrint : Print {
    unsigned long bytes = 0;
    size_t write(uint8_t) override { ++bytes; return 1; }
    size_t write(const char*, size_t n) override { bytes += n; return n; }
    void print(char) override { ++bytes; }
    void print(const char* s) override { while (s && *s) { ++bytes; ++s; } }
};

// 実データ由来のベクタ。
// MT43: test/integration/test_realdata.cpp の dc=1 緊急地震速報
// MT44: test/integration/test_azarashi_dcx.cpp の Outside Japan (Fiji)
// UBX : test/framer/test_ublox_azarashi.cpp の sv56 pattern1 (Marine)
const char* const kMt43Cat1 =
    "$QZQSM,57,9AAF8DED25000325BA00DA4A0F5AAC5A8000000008000000200000136DCCFB4*02";
const char* const kMt44Outside =
    "$QZQSM,56,9AB08408E0598969E00066AFFE8E6F70091200000000000000000100CD1A410*0C";
const uint8_t kUbxMarine[] = {
    0xB5, 0x62, 0x02, 0x13, 0x2C, 0x00,
    0x05, 0x02, 0x01, 0x00, 0x09, 0x40, 0x02, 0x00,
    0xC5, 0xF1, 0xAD, 0x9A, 0x04, 0x05, 0x80, 0x11,
    0x54, 0x8D, 0xA0, 0x60, 0x3F, 0x82, 0xD2, 0x11,
    0x0F, 0xAA, 0x7D, 0x50, 0x28, 0x0C, 0x43, 0xC9,
    0x10, 0x00, 0x50, 0x7D, 0x31, 0x79, 0xF0, 0x28,
    0x73, 0x18, 0x10, 0xB2, 0x62, 0x2F
};

// 計測区間の実体: feed + toJson のみ。区間外の準備は呼び出し側で済ませる。
unsigned long measureNmea(const char* nmea, CountingPrint& sink) {
    Parser p;
    Message m;
    unsigned long base = noalloc::snapshot();
    for (const char* s = nmea; *s; ++s) {
        if (p.feed(static_cast<uint8_t>(*s), m, 0) && m.valid) toJson(m, sink);
    }
    return noalloc::delta(base);
}

unsigned long measureUbx(const uint8_t* bytes, unsigned len, CountingPrint& sink) {
    Parser p;
    Message m;
    unsigned long base = noalloc::snapshot();
    for (unsigned i = 0; i < len; ++i) {
        if (p.feed(bytes[i], m, 0) && m.valid) toJson(m, sink);
    }
    return noalloc::delta(base);
}

}  // namespace

TEST_CASE("No allocation: MT43 feed + JSON") {
    CountingPrint sink;
    CHECK(measureNmea(kMt43Cat1, sink) == 0);
#if AZARAC_ENABLE_EEW
    CHECK(sink.bytes > 0);
#endif
}

TEST_CASE("No allocation: MT44 feed + JSON") {
    CountingPrint sink;
    CHECK(measureNmea(kMt44Outside, sink) == 0);
#if AZARAC_ENABLE_DCX_CAMF
    CHECK(sink.bytes > 0);
#endif
}

TEST_CASE("No allocation: UBX SFRBX feed + JSON") {
    CountingPrint sink;
    CHECK(measureUbx(kUbxMarine, sizeof(kUbxMarine), sink) == 0);
#if AZARAC_ENABLE_MARINE
    CHECK(sink.bytes > 0);
#endif
}

TEST_CASE("No allocation: counter detects deliberate new[]") {
    // カウンタ自体の自己検証。落ちるなら operator new の置換が効いていない。
    unsigned long base = noalloc::snapshot();
    volatile int* p = new int[3];
    unsigned long d = noalloc::delta(base);
    CHECK(d >= 1);
    delete[] p;
}

#if (AZARAC_ENABLE_NANKAI) && (AZARAC_NANKAI_MAX_PAGES >= 27)
// 南海トラフ 27 ページ集約: ページバッファ経由の最長経路。
// NMEA 文は計測区間の外で組み立てる（makeNmeaQzqsm は std::string を作るため）。
namespace {
constexpr unsigned kPageCount = 27;

struct RenderedPages {
    char text[kPageCount][80];
    unsigned len[kPageCount];
};

void buildNankaiPage(uint8_t page_num, uint8_t total_pages, uint8_t info_code,
                     const uint8_t* text, uint8_t text_len, uint8_t* bits) {
    std::memset(bits, 0, 32);
    setBits(bits, 0, 8, 0x53);       // Preamble
    setBits(bits, 8, 6, 43);         // msg_type
    setBits(bits, 14, 3, 1);         // report_classification
    setBits(bits, 17, 4, 4);         // disaster_category = Nankai
    setBits(bits, 21, 4, 5);         // report_time month
    setBits(bits, 25, 5, 1);         // day
    setBits(bits, 41, 2, 0);         // information_type
    setBits(bits, 53, 4, info_code);
    for (uint8_t i = 0; i < text_len && i < 18; ++i) {
        setBits(bits, 57 + i * 8, 8, text[i]);
    }
    setBits(bits, 201, 6, page_num);
    setBits(bits, 207, 6, total_pages);
    setBits(bits, 214, 6, 1);        // version
    setBits(bits, 226, 24, crc24qRef(bits, 226));
}

void renderNankaiPages(RenderedPages& out) {
    uint8_t bits[32];
    for (unsigned k = 0; k < kPageCount; ++k) {
        buildNankaiPage(static_cast<uint8_t>(k + 1), kPageCount, 5,
                        nankai_page_data[k], internal::NankaiPageBuffer::TEXT_PER_PAGE, bits);
        std::string s = makeNmeaQzqsm(58, bits);   // 計測区間外（std::string を作る）
        out.len[k] = static_cast<unsigned>(s.size());
        for (unsigned i = 0; i < s.size(); ++i) out.text[k][i] = s[i];
    }
}
}  // namespace

TEST_CASE("No allocation: Nankai 27-page aggregation + JSON") {
    static RenderedPages pages;
    renderNankaiPages(pages);
    Parser p;
    Message m;
    CountingPrint sink;
    unsigned emitted = 0;
    unsigned long base = noalloc::snapshot();
    for (unsigned k = 0; k < kPageCount; ++k) {
        for (unsigned i = 0; i < pages.len[k]; ++i) {
            if (p.feed(static_cast<uint8_t>(pages.text[k][i]), m, 0)) {
                ++emitted;
                if (m.valid) toJson(m, sink);
            }
        }
    }
    unsigned long d = noalloc::delta(base);
    CHECK(d == 0);
    CHECK(emitted == 1);      // 最終ページで集約が完了し 1 通だけ出力される
    CHECK(sink.bytes > 0);
}
#endif  // AZARAC_ENABLE_NANKAI && AZARAC_NANKAI_MAX_PAGES >= 27
