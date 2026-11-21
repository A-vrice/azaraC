// Parser 統合テスト。注: ほとんどのテストは EEW (dc=1) を使う。AZARAC_ENABLE_EEW でガード。

#include <string>
#include <vector>
#include "doctest.h"
#include "../src/Parser.h"
#include "../test_helpers.h"

using namespace azaraC;

// カテゴリ非依存のテスト（常時コンパイル）

#if (AZARAC_ENABLE_NANKAI)
TEST_CASE("Parser getNankaiBuffer returns nullptr for unknown key") {
    Parser parser;

    azaraC::internal::NankaiPageKey key = {1};
    const azaraC::internal::NankaiPageBuffer* buf = parser.getNankaiBuffer(key);
    CHECK(buf == nullptr);
}
#endif

// 一括入力の等価性（カテゴリ非依存）。
// 逐次 feed(byte) と feed(data, len) が同じ結果を返し、同じ電文を残すことを固定する。
#if (AZARAC_ENABLE_SEISMIC)
TEST_CASE("Parser: bulk feed is equivalent to byte-by-byte feed") {
    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);
    setBits(bits, 8, 6, 43);
    setBits(bits, 14, 3, 2);       // 報告分類
    setBits(bits, 17, 4, 3);       // 震度
    setBits(bits, 214, 6, 1);      // Vn
    setBits(bits, 226, 24, crc24qRef(bits, 226));
    const std::string nmea = makeNmeaQzqsm(58, bits);

    Parser byte_parser;
    Message byte_msg;
    bool byte_out = false;
    for (char c : nmea) {
        if (byte_parser.feed(static_cast<uint8_t>(c), byte_msg, 0)) byte_out = true;
    }
    REQUIRE(byte_out);

    Parser bulk_parser;
    Message bulk_msg;
    const bool bulk_out = bulk_parser.feed(
        reinterpret_cast<const uint8_t*>(nmea.data()), nmea.size(), bulk_msg, 0);

    CHECK(bulk_out);
    CHECK(bulk_msg.valid == byte_msg.valid);
    CHECK(bulk_msg.msg_type == byte_msg.msg_type);
    CHECK(bulk_msg.svid == byte_msg.svid);
    CHECK(bulk_msg.crc24 == byte_msg.crc24);
    CHECK(bulk_msg.payload_type == byte_msg.payload_type);
}

TEST_CASE("Parser: bulk feed reports no message for incomplete input") {
    Parser parser;
    Message msg;
    // 途中で切れた文（完成すれば 1 通だが、ここでは '$QZQSM,55,' まで）。
    static const char partial[] = "$QZQSM,55,00";
    CHECK_FALSE(parser.feed(reinterpret_cast<const uint8_t*>(partial), sizeof(partial) - 1, msg, 0));
    // nullptr / len=0 は何もせず false。
    CHECK_FALSE(parser.feed(nullptr, 0, msg, 0));
    CHECK_FALSE(parser.feed(reinterpret_cast<const uint8_t*>(""), 0, msg, 0));
}

static std::string makeSeismicNmea(uint8_t intensity) {
    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);
    setBits(bits, 8, 6, 43);
    setBits(bits, 14, 3, 2);
    setBits(bits, 17, 4, 3);
    setBits(bits, 69, 3, intensity);   // 先頭エントリの震度
    setBits(bits, 72, 6, 13);          // 先頭エントリの都道府県
    setBits(bits, 214, 6, 1);
    setBits(bits, 226, 24, crc24qRef(bits, 226));
    return makeNmeaQzqsm(58, bits) + "\r\n";
}

// 43/44 以外の MT（L1S では DCR 以外の MT も毎秒流れる）。
static std::string makeOtherMtNmea() {
    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x9A);
    setBits(bits, 8, 6, 50);
    setBits(bits, 226, 24, crc24qRef(bits, 226));
    return makeNmeaQzqsm(58, bits) + "\r\n";
}

// 成立後のフレームの復号が out を clear() しても、true のときは成立した電文が残ること。
TEST_CASE("Parser: bulk feed keeps the message when a rejected frame follows") {
    const std::string a = makeSeismicNmea(3);
    SUBCASE("duplicate follows") {
        Parser parser;
        Message msg;
        const std::string s = a + a;
        REQUIRE(parser.feed(reinterpret_cast<const uint8_t*>(s.data()), s.size(), msg, 0));
        CHECK(msg.valid);
        CHECK(msg.msg_type == 43);
        CHECK(msg.payload_type == MsgPayloadType::Mt43);
    }
    SUBCASE("non-DCR MT follows") {
        Parser parser;
        Message msg;
        const std::string s = a + makeOtherMtNmea();
        REQUIRE(parser.feed(reinterpret_cast<const uint8_t*>(s.data()), s.size(), msg, 0));
        CHECK(msg.valid);
        CHECK(msg.msg_type == 43);
        CHECK(msg.payload_type == MsgPayloadType::Mt43);
    }
}

TEST_CASE("Parser: bulk feed leaves the last message of several") {
    Parser parser;
    Message msg;
    const std::string s = makeSeismicNmea(3) + makeSeismicNmea(5) + makeOtherMtNmea();
    REQUIRE(parser.feed(reinterpret_cast<const uint8_t*>(s.data()), s.size(), msg, 0));
    REQUIRE(msg.valid);
    const Mt43Data* d = msg.getMt43();
    REQUIRE(d != nullptr);
    REQUIRE(d->getSeismic() != nullptr);
    CHECK(d->getSeismic()->entries[0].intensity_code == 5);
}

TEST_CASE("Parser: feedUntilMessage returns every message in a buffer") {
    Parser parser;
    Message msg;
    const std::string a = makeSeismicNmea(3);
    const std::string b = makeSeismicNmea(5);
    const std::string s = a + makeOtherMtNmea() + b;
    const uint8_t* p = reinterpret_cast<const uint8_t*>(s.data());
    size_t n = s.size();
    std::vector<uint8_t> intensities;
    size_t first_used = 0;
    while (n > 0) {
        const size_t used = parser.feedUntilMessage(p, n, msg, 0);
        REQUIRE(used > 0);
        REQUIRE(used <= n);
        if (first_used == 0) first_used = used;
        if (msg.valid) {
            const Mt43Data* d = msg.getMt43();
            REQUIRE(d != nullptr);
            REQUIRE(d->getSeismic() != nullptr);
            intensities.push_back(d->getSeismic()->entries[0].intensity_code);
        }
        p += used;
        n -= used;
    }
    // 他 MT は落ち、2 通が送信順に出る。最初の 1 通は先頭の文の中で止まる。
    REQUIRE(intensities.size() == 2);
    CHECK(intensities[0] == 3);
    CHECK(intensities[1] == 5);
    CHECK(first_used <= a.size());
}

TEST_CASE("Parser: feedUntilMessage consumes everything when nothing completes") {
    Parser parser;
    Message msg;
    msg.valid = true;
    static const char partial[] = "$QZQSM,55,00";
    CHECK(parser.feedUntilMessage(reinterpret_cast<const uint8_t*>(partial), sizeof(partial) - 1, msg, 0)
          == sizeof(partial) - 1);
    CHECK_FALSE(msg.valid);

    const std::string other = makeOtherMtNmea();
    msg.valid = true;
    CHECK(parser.feedUntilMessage(reinterpret_cast<const uint8_t*>(other.data()), other.size(), msg, 0)
          == other.size());
    CHECK_FALSE(msg.valid);

    msg.valid = true;
    CHECK(parser.feedUntilMessage(nullptr, 10, msg, 0) == 0);
    CHECK_FALSE(msg.valid);
}
#endif // (AZARAC_ENABLE_SEISMIC)

// EEW 依存のテスト（dc=1）

#if (AZARAC_ENABLE_EEW)

// reset の framer 状態クリアを検証するための最小 EEW 文。
static std::string makeEewNmea58() {
    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);
    setBits(bits, 8, 6, 43);
    setBits(bits, 14, 3, 1);
    setBits(bits, 17, 4, 1);
    setBits(bits, 214, 6, 1);
    setBits(bits, 226, 24, crc24qRef(bits, 226));
    return makeNmeaQzqsm(58, bits);
}

static std::vector<uint8_t> makeEewUbx193() {
    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);
    setBits(bits, 8, 6, 43);
    setBits(bits, 17, 4, 1);
    setBits(bits, 214, 6, 1);
    setBits(bits, 226, 24, crc24qRef(bits, 226));
    return makeUbxSfrbx(193, bits);
}

TEST_CASE("Parser AUTO mode: NMEA message decoded") {
    Parser parser;
    Message msg;

    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);
    setBits(bits, 8, 6, 43);
    setBits(bits, 14, 3, 1);
    setBits(bits, 17, 4, 1);
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
    CHECK(msg.msg_type == 43);
    CHECK(msg.payload_type == MsgPayloadType::Mt43);
}

TEST_CASE("Parser: CRC 不正のフレームは svid を残さない") {
    Parser parser;
    Message msg;

    // 正常なフレームで svid を入れる
    const std::string good = makeEewNmea58();
    bool output = false;
    for (size_t i = 0; i < good.length(); ++i) {
        if (parser.feed(good[i], msg, 0)) { output = true; break; }
    }
    CHECK(output);
    CHECK(msg.svid == 186);  // NMEA の Satellite ID 58 は PRN 186 に正規化される

    // CRC だけ壊す（NMEA チェックサムは作り直すのでフレーマは通る）
    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);
    setBits(bits, 8, 6, 43);
    setBits(bits, 14, 3, 1);
    setBits(bits, 17, 4, 1);
    setBits(bits, 214, 6, 1);
    setBits(bits, 226, 24, 0xDEADBEu);
    const std::string bad = makeNmeaQzqsm(61, bits);

    bool accepted = false;
    for (size_t i = 0; i < bad.length(); ++i) {
        if (parser.feed(bad[i], msg, 0)) accepted = true;
    }
    CHECK_FALSE(accepted);
    CHECK_FALSE(msg.valid);
    CHECK(msg.svid == 0);  // 直前の 186 も、壊れたフレームの 189 も残らない
}

// F1 契約: 不完全入力は feed=false を返し続け、完成フレームでフレーマ状態が回復する。
// 回復フレームは別 identity（report minute を変更）にして、dedup 有効でも抑止されず全ビルドで回復を検証する。
TEST_CASE("Parser: incomplete input never reports success and recovers") {
    Parser parser;
    Message msg;

    const std::string good = makeEewNmea58();
    bool output = false;
    for (size_t i = 0; i < good.length(); ++i) {
        if (parser.feed(good[i], msg, 0)) { output = true; break; }
    }
    REQUIRE(output);
    CHECK(msg.valid == true);

    // 不完全な $QZQSM 文（チェックサム無し）を 1 バイトずつ投入 → すべて false。
    const std::string partial = "$QZQSM,58,9AAF";
    for (size_t i = 0; i < partial.length(); ++i) {
        INFO("partial byte ", i);
        CHECK_FALSE(parser.feed(partial[i], msg, 0));
    }

    // 別 identity の完成フレームで状態が回復する（同一再投入は dedup が抑止するのが正しいため minute を変える）。
    uint8_t rbits[32] = {};
    setBits(rbits, 0, 8, 0x53);
    setBits(rbits, 8, 6, 43);
    setBits(rbits, 14, 3, 1);
    setBits(rbits, 17, 4, 1);
    setBits(rbits, 35, 6, 1);   // report minute=1 → 先頭フレームと別の dedup identity
    setBits(rbits, 214, 6, 1);
    setBits(rbits, 226, 24, crc24qRef(rbits, 226));
    const std::string recovery = makeNmeaQzqsm(58, rbits);
    bool recovered = false;
    for (size_t i = 0; i < recovery.length(); ++i) {
        if (parser.feed(recovery[i], msg, 0)) { recovered = true; break; }
    }
    CHECK(recovered);
    CHECK(msg.valid == true);
}

// F1 契約: 完成フレーム＋CRC 失敗は valid=false・svid=0（ヘッダ由来の値を残さない）。
TEST_CASE("Parser: complete frame with bad CRC clears valid and svid") {
    Parser parser;
    Message msg;

    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);
    setBits(bits, 8, 6, 43);
    setBits(bits, 14, 3, 1);
    setBits(bits, 17, 4, 1);
    setBits(bits, 214, 6, 1);
    setBits(bits, 226, 24, crc24qRef(bits, 226));   // 正しい CRC を設定
    bits[10] ^= 0x01;                              // ペイロードを破壊（CRC 対象内）→ CRC 不一致
    const std::string bad = makeNmeaQzqsm(58, bits);   // NMEA チェックサムは再計算される

    bool accepted = false;
    for (size_t i = 0; i < bad.length(); ++i) {
        if (parser.feed(bad[i], msg, 0)) accepted = true;
    }
    CHECK_FALSE(accepted);
    CHECK(msg.valid == false);
    CHECK(msg.svid == 0);
}

TEST_CASE("Parser AUTO mode: UBX message decoded") {
    Parser parser;
    Message msg;

    uint8_t nav_bits[32] = {};
    setBits(nav_bits, 0, 8, 0x53);
    setBits(nav_bits, 8, 6, 43);
    setBits(nav_bits, 17, 4, 1);
    setBits(nav_bits, 214, 6, 1);
    uint32_t crc = crc24qRef(nav_bits, 226);
    setBits(nav_bits, 226, 24, crc);
    auto ubx = makeUbxSfrbx(193, nav_bits);

    bool output = false;
    for (auto b : ubx) {
        if (parser.feed(b, msg, 0)) {
            output = true;
            break;
        }
    }

    CHECK(output);
    CHECK(msg.valid);
    CHECK(msg.msg_type == 43);
    CHECK(msg.payload_type == MsgPayloadType::Mt43);
    REQUIRE(msg.getMt43() != nullptr);
    CHECK(msg.getMt43()->disaster_category == 1);
}

#if AZARAC_ENABLE_DEDUP
TEST_CASE("Parser EEW duplicate suppression") {
    Parser parser;
    Message msg;

    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);
    setBits(bits, 8, 6, 43);
    setBits(bits, 14, 3, 1);
    setBits(bits, 17, 4, 1);
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
    CHECK(msg.valid);

    const Mt43Data* mt43 = msg.getMt43();
    REQUIRE(mt43 != nullptr);
    CHECK(mt43->disaster_category == 1);

    bool output2 = false;
    for (size_t i = 0; i < nmea.length(); i++) {
        if (parser.feed(nmea[i], msg, 0)) {
            output2 = true;
            break;
        }
    }
    CHECK_FALSE(output2);
}
#endif // AZARAC_ENABLE_DEDUP

TEST_CASE("Parser reset clears state") {
    Parser parser;
    Message msg;

    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);
    setBits(bits, 8, 6, 43);
    setBits(bits, 14, 3, 1);
    setBits(bits, 17, 4, 1);
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

// NMEA 部は EEW (dc=1)、UBX 部は DCX (MT=44) を使う。両マクロが必要。
#if (AZARAC_ENABLE_DCX_CAMF)
TEST_CASE("Parser handles mixed NMEA and UBX messages") {
    Parser parser;
    Message msg;

    uint8_t bits1[32] = {};
    setBits(bits1, 0, 8, 0x53);
    setBits(bits1, 8, 6, 43);
    setBits(bits1, 14, 3, 1);
    setBits(bits1, 17, 4, 1);
    setBits(bits1, 214, 6, 1);
    uint32_t crc1 = crc24qRef(bits1, 226);
    setBits(bits1, 226, 24, crc1);
    std::string nmea1 = makeNmeaQzqsm(58, bits1);

    bool output1 = false;
    for (size_t i = 0; i < nmea1.length(); i++) {
        if (parser.feed(nmea1[i], msg, 0)) {
            output1 = true;
            break;
        }
    }
    CHECK(output1);
    CHECK(msg.payload_type == MsgPayloadType::Mt43);

    uint8_t nav_bits[32] = {};
    setBits(nav_bits, 0, 8, 0x53);
    setBits(nav_bits, 8, 6, 44);
    setBits(nav_bits, 24, 2, 1);
    setBits(nav_bits, 26, 9, 111);
    setBits(nav_bits, 214, 6, 1);
    uint32_t crc2 = crc24qRef(nav_bits, 226);
    setBits(nav_bits, 226, 24, crc2);
    auto ubx = makeUbxSfrbx(193, nav_bits);

    bool output2 = false;
    for (auto b : ubx) {
        if (parser.feed(b, msg, 0)) {
            output2 = true;
            break;
        }
    }
    CHECK(output2);
    CHECK(msg.payload_type == MsgPayloadType::Mt44);
}
#endif // AZARAC_ENABLE_DCX_CAMF


TEST_CASE("Parser: long garbage between valid frames recovers") {
    azaraC::Parser parser;
    azaraC::Message msg;

    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);
    setBits(bits, 8, 6, 43);
    setBits(bits, 14, 3, 1);
    setBits(bits, 17, 4, 1);
    setBits(bits, 214, 6, 1);
    uint32_t crc = crc24qRef(bits, 226);
    setBits(bits, 226, 24, crc);
    std::string nmea = makeNmeaQzqsm(58, bits);

    std::string garbage;
    for (int i = 0; i < 1000; ++i) {
        garbage += static_cast<char>(0x41 + (i % 26));
    }
    std::string stream = garbage + nmea;

    bool output = false;
    for (size_t i = 0; i < stream.length(); ++i) {
        if (parser.feed(stream[i], msg, 0)) {
            output = true;
            break;
        }
    }
    CHECK(output);
    CHECK(msg.valid);
    CHECK(msg.payload_type == azaraC::MsgPayloadType::Mt43);
}

TEST_CASE("Parser: rapid consecutive resets still decode") {
    azaraC::Parser parser;
    azaraC::Message msg;

    const std::string partial = "$QZQSM,58,9AAF";
    for (int r = 0; r < 10; ++r) {
        for (char c : partial) {
            parser.feed(static_cast<uint8_t>(c), msg, 0);
        }
        parser.reset();
    }

    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);
    setBits(bits, 8, 6, 43);
    setBits(bits, 14, 3, 1);
    setBits(bits, 17, 4, 1);
    setBits(bits, 214, 6, 1);
    uint32_t crc = crc24qRef(bits, 226);
    setBits(bits, 226, 24, crc);
    std::string nmea = makeNmeaQzqsm(58, bits);

    bool output = false;
    for (size_t i = 0; i < nmea.length(); ++i) {
        if (parser.feed(nmea[i], msg, 0)) {
            output = true;
            break;
        }
    }
    CHECK(output);
    CHECK(msg.valid);
}

TEST_CASE("Parser: reset clears NMEA framer state") {
    const std::string nmea = makeEewNmea58();
    const size_t cut = nmea.size() * 2 / 3;   // '$' と prefix、payload の途中まで

    azaraC::Parser parser;
    azaraC::Message msg;
    for (size_t i = 0; i < cut; ++i) {
        parser.feed(static_cast<uint8_t>(nmea[i]), msg, 0);
    }
    parser.reset();

    // '$' を除いた残りを流す。framer が reset されていれば WAIT のままで出力しない。
    bool output = false;
    for (size_t i = cut; i < nmea.size(); ++i) {
        if (parser.feed(static_cast<uint8_t>(nmea[i]), msg, 0)) {
            output = true;
            break;
        }
    }
    CHECK_FALSE(output);

    // 陽性対照: 完全な文は 1 回で復号できる。
    azaraC::Parser fresh;
    azaraC::Message fresh_msg;
    bool decoded = false;
    for (char c : nmea) {
        if (fresh.feed(static_cast<uint8_t>(c), fresh_msg, 0)) {
            decoded = true;
            break;
        }
    }
    CHECK(decoded);
    CHECK(fresh_msg.valid);
}

TEST_CASE("Parser: reset clears UBX framer state") {
    const std::vector<uint8_t> pkt = makeEewUbx193();
    const size_t cut = 12;   // sync + header + payload の途中まで

    azaraC::Parser parser;
    azaraC::Message msg;
    for (size_t i = 0; i < cut; ++i) {
        parser.feed(pkt[i], msg, 0);
    }
    parser.reset();

    bool output = false;
    for (size_t i = cut; i < pkt.size(); ++i) {
        if (parser.feed(pkt[i], msg, 0)) {
            output = true;
            break;
        }
    }
    CHECK_FALSE(output);

    // 陽性対照: 完全な packet は 1 回で復号できる。
    azaraC::Parser fresh;
    azaraC::Message fresh_msg;
    bool decoded = false;
    for (uint8_t b : pkt) {
        if (fresh.feed(b, fresh_msg, 0)) {
            decoded = true;
            break;
        }
    }
    CHECK(decoded);
    CHECK(fresh_msg.valid);
}

TEST_CASE("Parser: mode switch NMEA to UBX after partial frame") {
    azaraC::Parser parser;
    azaraC::Message msg;

    std::string nmea_partial = "$QZQSM,58,9AAF";
    uint8_t nav_bits[32] = {};
    setBits(nav_bits, 0, 8, 0x53);
    setBits(nav_bits, 8, 6, 43);
    setBits(nav_bits, 17, 4, 1);
    setBits(nav_bits, 214, 6, 1);
    uint32_t crc = crc24qRef(nav_bits, 226);
    setBits(nav_bits, 226, 24, crc);
    auto ubx = makeUbxSfrbx(193, nav_bits);

    for (char c : nmea_partial) {
        parser.feed((uint8_t)c, msg, 0);
    }

    bool ubx_found = false;
    for (auto b : ubx) {
        if (parser.feed(b, msg, 0)) {
            ubx_found = true;
            break;
        }
    }
    CHECK(ubx_found);
    CHECK(msg.valid);
    CHECK(msg.payload_type == azaraC::MsgPayloadType::Mt43);
}

TEST_CASE("Parser: stale NMEA partial data doesn't leak") {
    azaraC::Parser parser;
    azaraC::Message msg;

    std::string stale_prefix = "$GPGGA,1234";
    for (char c : stale_prefix) {
        parser.feed((uint8_t)c, msg, 0);
    }

    uint8_t bits[32] = {};
    setBits(bits, 0, 8, 0x53);
    setBits(bits, 8, 6, 43);
    setBits(bits, 14, 3, 1);
    setBits(bits, 17, 4, 1);
    setBits(bits, 214, 6, 1);
    uint32_t crc = crc24qRef(bits, 226);
    setBits(bits, 226, 24, crc);
    std::string nmea = makeNmeaQzqsm(58, bits);

    bool output = false;
    for (size_t i = 0; i < nmea.length(); ++i) {
        if (parser.feed(nmea[i], msg, 0)) {
            output = true;
            break;
        }
    }
    CHECK(output);
    CHECK(msg.valid);
    const azaraC::Mt43Data* mt43 = msg.getMt43();
    REQUIRE(mt43 != nullptr);
    CHECK(mt43->disaster_category == 1);
}

// 手順③ の照合対象は MT～VN（bit 8..219 = 212 bit。
// 付属フローチャートも「MT～Vnの212bit」と明記）。
// プリアンブル（bit 0..7）は A(0x53)→B(0x9A)→C(0xC6)、Reserved（bit 220..225）は 16 値で巡回するため、どちらも含めず 1 情報 1 通知に固定する。
#if AZARAC_ENABLE_DEDUP
TEST_CASE("Parser: プリアンブル/Reserved が違っても同一 MT～VN は 1 回だけ通知される") {
    Parser parser;
    Message msg;

    // minute: MT～VN 内の唯一の内容マーカー（bit 35..40）。preamble/reserved は MT～VN 外で identity を変えない。
    auto feedFrame = [&](uint8_t preamble, uint8_t minute, uint8_t reserved) -> int {
        uint8_t bits[32] = {};
        setBits(bits, 0, 8, preamble);
        setBits(bits, 8, 6, 43);
        setBits(bits, 14, 3, 1);      // report_classification
        setBits(bits, 17, 4, 1);      // disaster_category = 1 (EEW)
        setBits(bits, 35, 6, minute); // report_time minute
        setBits(bits, 214, 6, 1);     // version (Vn = bit 214..219)
        setBits(bits, 220, 6, reserved);
        setBits(bits, 226, 24, crc24qRef(bits, 226));
        const std::string nmea = makeNmeaQzqsm(58, bits);
        int emitted = 0;
        for (size_t i = 0; i < nmea.size(); ++i) {
            if (parser.feed(static_cast<uint8_t>(nmea[i]), msg, 0)) ++emitted;
        }
        return emitted;
    };

    CHECK(feedFrame(0x53, 0, 0) == 1);   // 新規情報
    CHECK(feedFrame(0x9A, 0, 0) == 0);   // プリアンブルだけ違う → 重複
    CHECK(feedFrame(0xC6, 0, 0) == 0);   // 同様
    CHECK(feedFrame(0x53, 0, 5) == 0);   // Reserved(220..225) だけ違う → 重複
    CHECK(feedFrame(0x53, 0, 15) == 0);  // 同様（218 bit 鍵なら別情報になる）
    CHECK(feedFrame(0x53, 1, 0) == 1);   // MT～VN が変われば別情報
}
#endif // AZARAC_ENABLE_DEDUP
#endif // AZARAC_ENABLE_EEW

#if (AZARAC_ENABLE_DCX_CAMF)
// QZS 事務局回答: 照合範囲「MT および CAMF〜EM」に SDMT（bit 14）・SDM（bit 15..23）を含めず、SD だけが違う同一内容は 1 回だけ通知する。
#if AZARAC_ENABLE_DEDUP
TEST_CASE("Parser: MT44 は SDMT/SDM が違っても同一内容を 1 回だけ通知する") {
    Parser parser;
    Message msg;

    // MT=44 の L-Alert（A2=Japan, A3=FMMC）。SDMT/SDM と A8 以外は固定。
    auto feed = [&](uint8_t sdmt, uint16_t sdm, uint8_t a8) -> int {
        uint8_t bits[32] = {};
        setBits(bits, 0, 8, 0x53);
        setBits(bits, 8, 6, 44);
        setBits(bits, 14, 1, sdmt);
        setBits(bits, 15, 9, sdm);
        setBits(bits, 24, 2, 1);       // A1=Alert
        setBits(bits, 26, 9, 111);     // A2=Japan
        setBits(bits, 35, 5, 1);       // A3=FMMC (L-Alert)
        setBits(bits, 40, 7, 1);       // A4=Rainfall（NullMessage 判定を避ける）
        setBits(bits, 64, 2, a8);      // A8=Hazard Duration
        setBits(bits, 226, 24, crc24qRef(bits, 226));
        const std::string nmea = makeNmeaQzqsm(58, bits);
        int emitted = 0;
        for (size_t i = 0; i < nmea.size(); ++i) {
            if (parser.feed(static_cast<uint8_t>(nmea[i]), msg, 0)) ++emitted;
        }
        return emitted;
    };

    CHECK(feed(0, 0x000, 1) == 1);   // 新規情報
    CHECK(feed(1, 0x1FF, 1) == 0);   // SD だけ違う → 重複（Step 1 前は 1 になる）
    CHECK(feed(0, 0x1FF, 2) == 1);   // A8 が違う → 別情報
}
#endif // AZARAC_ENABLE_DEDUP
#endif // AZARAC_ENABLE_DCX_CAMF
