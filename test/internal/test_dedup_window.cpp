// test/internal/test_dedup_window.cpp — 情報有効時間（手順④）のカテゴリ別窓
//
// DedupWindow.h の条件表は「その情報がまだ配信中か」を決める唯一の場所で、
// 窓を短くする誤りは生きた警報の再通知（dedup の重複除去が効かない）に直結する。
// 表の値をカテゴリ・副条件ごとに固定し、payload を渡さない経路（該当型が
// 無効/未設定）でもクラッシュせず fallback に落ちることを確かめる。
//
// Parser::handleFrame も併せて検証する。custom framer 経路（feed が false）と
// デコード失敗経路は、out に前回の有効メッセージが残ったままにならない契約
// （decode 失敗時は空の Message を丸ごとコピーする）を負っている。

#define ARDUINO 0
#include "../src/Parser.h"
#include "../src/internal/DedupWindow.h"
#include "doctest.h"
#include <initializer_list>

using namespace azaraC;
using namespace azaraC::internal;

namespace {

constexpr uint32_t MIN = 60UL * 1000UL;
constexpr uint32_t HR = 60UL * MIN;
constexpr uint32_t DAY = 24UL * HR;

constexpr uint32_t FALLBACK = 12345UL;  // 表に無いカテゴリの目印

// payload を渡さない（該当型が無効・未設定）経路
uint32_t windowNoPayload(uint8_t dc, uint8_t info = 0) {
    return dedupWindowMs(FALLBACK, dc, info, nullptr);
}

// Message 版の経路（Parser が実際に使う）
uint32_t windowViaMessage(uint8_t dc, uint8_t info, Mt43Data::ActiveType type) {
    Message m{};
    m.svid = 186;
    m.payload_type = MsgPayloadType::Mt43;
    Mt43Data* d = m.getMt43();
    REQUIRE(d != nullptr);
    d->disaster_category = dc;
    d->information_type = info;
    d->active_type = type;
    return dedupWindowMs(m);
}

} // namespace

TEST_CASE("dedup window: payload-less categories use the table") {
    CHECK(windowNoPayload(1) == 5UL * MIN);   // 緊急地震速報
    CHECK(windowNoPayload(2) == 2UL * HR);    // 震源
    CHECK(windowNoPayload(3) == 2UL * HR);    // 震度
    CHECK(windowNoPayload(6) == 10UL * HR);   // 北西太平洋津波
    CHECK(windowNoPayload(8) == DAY);         // 火山
    CHECK(windowNoPayload(9) == HR);          // 降灰
    CHECK(windowNoPayload(12) == 3UL * HR);   // 台風
}

TEST_CASE("dedup window: Nankai Trough (dc=4) splits on cancellation") {
    CHECK(windowNoPayload(4, 0) == DAY);        // 発表
    CHECK(windowNoPayload(4, 1) == DAY);        // 訂正
    CHECK(windowNoPayload(4, 2) == 2UL * HR);   // 取消
}

TEST_CASE("dedup window: unknown category falls back") {
    CHECK(windowNoPayload(0) == FALLBACK);
    CHECK(windowNoPayload(7) == FALLBACK);    // 未割当
    CHECK(windowNoPayload(13) == FALLBACK);   // 予約
    CHECK(windowNoPayload(15) == FALLBACK);
}

TEST_CASE("dedup window: tsunami (dc=5) needs announcement and warning code 3-5") {
    // payload 無しでは警報コードが読めないので 10 時間側に倒れる
    CHECK(windowNoPayload(5, 0) == 10UL * HR);

#if AZARAC_ENABLE_TSUNAMI
    TsunamiData t{};
    // 発表(info=0) × 警報コード 3/4/5 → 24 時間
    for (uint8_t dw : {3, 4, 5}) {
        t.warning_code = dw;
        CHECK(dedupWindowMs(FALLBACK, 5, 0, &t) == DAY);
    }
    // 発表でもコードが 0..2 / 6 以上は 10 時間
    for (uint8_t dw : {0, 1, 2, 6, 31}) {
        t.warning_code = dw;
        CHECK(dedupWindowMs(FALLBACK, 5, 0, &t) == 10UL * HR);
    }
    // 解除/訂正(info != 0)はコードが 3 でも 10 時間
    t.warning_code = 3;
    CHECK(dedupWindowMs(FALLBACK, 5, 1, &t) == 10UL * HR);
    CHECK(dedupWindowMs(FALLBACK, 5, 2, &t) == 10UL * HR);
#endif
}

TEST_CASE("dedup window: weather (dc=10) needs Ar=1 and a special Ww") {
    CHECK(windowNoPayload(10, 0) == 3UL * HR);

#if AZARAC_ENABLE_WEATHER
    WeatherData w{};
    w.warning_state = 1;
    w.count = 1;
    for (uint8_t ww : {1, 3, 6, 23}) {   // 特別警報系・土砂災害警戒情報
        w.entries[0].sub_category = ww;
        CHECK(dedupWindowMs(FALLBACK, 10, 0, &w) == DAY);
    }
    for (uint8_t ww : {0, 7, 21, 22}) {  // 注意報系・大雨/竜巻注意情報
        w.entries[0].sub_category = ww;
        CHECK(dedupWindowMs(FALLBACK, 10, 0, &w) == 3UL * HR);
    }
    // 特別警報系でも「解除/訂正」(Ar != 1) は 3 時間
    w.entries[0].sub_category = 3;
    w.warning_state = 0;
    CHECK(dedupWindowMs(FALLBACK, 10, 0, &w) == 3UL * HR);
    w.warning_state = 2;
    CHECK(dedupWindowMs(FALLBACK, 10, 0, &w) == 3UL * HR);
    // Ww が 7 番目以降は見ない: count は配列長 6 を超えても走査側でクランプされる
    w.warning_state = 1;
    w.count = 6;                      // 配列長ちょうど（7 以上は entries[] 外を指す）
    w.entries[0].sub_category = 21;
    w.entries[5].sub_category = 3;    // 6 件目（i < 6 の上限）は見る
    CHECK(dedupWindowMs(FALLBACK, 10, 0, &w) == DAY);
#endif
}

TEST_CASE("dedup window: flood (dc=11) needs Lv 2-4 and no cancellation") {
    CHECK(windowNoPayload(11, 0) == 3UL * HR);

#if AZARAC_ENABLE_FLOOD
    FloodData f{};
    f.count = 1;
    for (uint8_t lv : {2, 3, 4}) {
        f.entries[0].warning_level = lv;
        CHECK(dedupWindowMs(FALLBACK, 11, 0, &f) == DAY);
    }
    for (uint8_t lv : {0, 1, 5}) {
        f.entries[0].warning_level = lv;
        CHECK(dedupWindowMs(FALLBACK, 11, 0, &f) == 3UL * HR);
    }
    // info=2（取消）は Lv が 3 でも 3 時間
    f.entries[0].warning_level = 3;
    CHECK(dedupWindowMs(FALLBACK, 11, 2, &f) == 3UL * HR);
    // Lv 2..4 が配列長（3）を超える count でも走査はクランプされる
    f.count = 3;
    f.entries[0].warning_level = 0;
    f.entries[2].warning_level = 3;
    CHECK(dedupWindowMs(FALLBACK, 11, 0, &f) == DAY);
#endif
}

TEST_CASE("dedup window: marine (dc=14) needs a warning code") {
    CHECK(windowNoPayload(14, 0) == 3UL * HR);

#if AZARAC_ENABLE_MARINE
    MarineData mi{};
    mi.count = 1;
    for (uint8_t wc : {10, 11, 12, 20, 21, 22, 23}) {
        mi.entries[0].warning_code = wc;
        CHECK(dedupWindowMs(FALLBACK, 14, 0, &mi) == DAY);
    }
    for (uint8_t wc : {0, 1, 9, 13, 24, 31}) {   // 0=解除, 31=その他
        mi.entries[0].warning_code = wc;
        CHECK(dedupWindowMs(FALLBACK, 14, 0, &mi) == 3UL * HR);
    }
    // 配列長（8）ちょうどの count でも全件走査して警報コードを見る
    mi.count = 8;
    mi.entries[0].warning_code = 0;
    mi.entries[7].warning_code = 11;
    CHECK(dedupWindowMs(FALLBACK, 14, 0, &mi) == DAY);
#endif
}

TEST_CASE("dedup window: Message overload routes MT43 payload and MT44 fallback") {
    // Mt43: active_type に応じた payload が渡る（津波は code 依存）
    CHECK(windowViaMessage(5, 0, Mt43Data::ActiveType::Tsunami) == 10UL * HR);
#if AZARAC_ENABLE_TSUNAMI
    {
        Message m{};
        m.svid = 186;
        m.payload_type = MsgPayloadType::Mt43;
        Mt43Data* d = m.getMt43();
        REQUIRE(d != nullptr);
        d->disaster_category = 5;
        d->information_type = 0;
        d->initAs<TsunamiData>();
        d->getTsunami()->warning_code = 4;
        CHECK(dedupWindowMs(m) == DAY);
    }
#endif
    // Mt43 でも payload 未設定の型は nullptr 経由（クラッシュせず 10 時間）
    CHECK(windowViaMessage(5, 0, Mt43Data::ActiveType::None) == 10UL * HR);
    // Weather/Flood/Marine も payload を引く経路を通る（カテゴリ3種は条件付き）
    CHECK(windowViaMessage(10, 0, Mt43Data::ActiveType::Weather) == 3UL * HR);
    CHECK(windowViaMessage(11, 0, Mt43Data::ActiveType::Flood) == 3UL * HR);
    CHECK(windowViaMessage(14, 0, Mt43Data::ActiveType::Marine) == 3UL * HR);
    // 津波以外の payload 経路でもカテゴリ表の値を返す
    CHECK(windowViaMessage(8, 0, Mt43Data::ActiveType::Weather) == DAY);
    // Mt44 はカテゴリ条件を持たない → 一律 fallback を使う
    {
        Message m{};
        m.svid = 186;
        m.payload_type = MsgPayloadType::Mt44;
        CHECK(dedupWindowMs(m) == AZARAC_DEDUP_WINDOW_MS);
    }
    // payload 無し（Empty）も fallback
    {
        Message m{};
        CHECK(dedupWindowMs(m) == AZARAC_DEDUP_WINDOW_MS);
    }
}

namespace {

// 常に「フレーム無し」を返すフレーマ（Parser のカスタム排他モード経路）
class NeverFramer : public azaraC::internal::IFramer {
public:
    bool feed(uint8_t, azaraC::internal::Frame&) override { return false; }
    void reset() override {}
};

// 一度だけ指定フレームを返すフレーマ
class OneShotFramer : public azaraC::internal::IFramer {
public:
    OneShotFramer(const azaraC::internal::Frame& f, bool deliver) : _f(f), _deliver(deliver) {}
    bool feed(uint8_t, azaraC::internal::Frame& out) override {
        if (_deliver) { _deliver = false; out = _f; return true; }
        return false;
    }
    void reset() override {}
private:
    azaraC::internal::Frame _f;
    bool _deliver;
};

} // namespace

TEST_CASE("Parser: custom framer with no frame keeps out untouched") {
    NeverFramer framer;
    Parser p(framer);

    Message m{};
    m.valid = true;
    m.msg_type = 43;   // 前回の有効メッセージを装う

    for (int i = 0; i < 8; ++i) {
        CHECK_FALSE(p.feed(0x00, m));
    }
    // フレームが来ない限り out は書き換えない（呼び出し側の前回値が残る）
    CHECK(m.valid);
    CHECK(m.msg_type == 43);
}

TEST_CASE("Parser: custom framer decode failure clears the previous payload") {
    azaraC::internal::Frame bad{};
    bad.svid = 186;
    // bits 全ゼロ = プリアンブル/MT 不正 → Decoder::decode が false を返す
    OneShotFramer framer(bad, /*deliver=*/true);
    Parser p(framer);

    Message m{};
    m.valid = true;
    m.msg_type = 43;
    m.svid = 186;
    m.crc24 = 0xABCDEF;

    CHECK_FALSE(p.feed(0x00, m));
    // 失敗時は decode() がクリアした Message を丸ごとコピーする契約。
    // svid は decode() が frame から書き戻すので残るが、payload は残らない。
    CHECK_FALSE(m.valid);
    CHECK(m.msg_type == 0);
    CHECK(m.svid == 186);
    CHECK(m.payload_type == MsgPayloadType::Empty);
    CHECK(m.crc24 == 0);
}
