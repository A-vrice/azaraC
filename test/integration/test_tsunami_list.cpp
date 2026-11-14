// 津波 / 北西太平洋津波のリスト終端判定の回帰テスト。
// IS-QZSS-DCR-017 Table 4.1.2-21 / 4.1.2-26: 未使用エントリは Ta/Th/Pl すべて 0。
// 終端はエントリ全体の 0 で判定する（Pl のみだと Ta/Th 非0の非準拠電文でエントリを取りこぼす）。

#include "../test_helpers.h"
#include "doctest.h"
#include <algorithm>

using namespace azaraC;

namespace {

// MT43 共通ヘッダを設定する（preamble/MT/category/report_time/version）。
void mt43Header(uint8_t* bits, uint8_t category) {
    setBits(bits, 0, 8, 0x53);     // preamble A
    setBits(bits, 8, 6, 43);       // MT=43
    setBits(bits, 14, 3, 0);       // report_classification
    setBits(bits, 17, 4, category);
    setBits(bits, 21, 4, 1);       // report_time month=1
    setBits(bits, 25, 5, 1);       // day=1
    setBits(bits, 30, 5, 0);       // hour
    setBits(bits, 35, 6, 0);       // minute
    setBits(bits, 41, 2, 0);       // information_type
    setBits(bits, 214, 6, 1);      // version=1
}

Message decodeBits(const uint8_t* bits) {
    uint8_t buf[32];
    std::copy(bits, bits + 32, buf);
    setBits(buf, 226, 24, crc24qRef(buf, 226));
    Frame frame{};
    std::copy(buf, buf + 32, frame.bits);
    frame.svid = 193;
    Decoder dec;
    Message msg{};
    dec.decode(frame, msg, 0);   // report_unix=0: 到着時刻の unix は未解決でよい
    return msg;
}

} // namespace

#if (AZARAC_ENABLE_TSUNAMI)
TEST_CASE("Tsunami list: termination is whole-entry zero, not Pl only") {
    // entry0: Ta=100, Th=2, Pl=100（有効）。entry1: 全 0 → 終端。
    uint8_t bits[32] = {};
    mt43Header(bits, 5);
    setBits(bits, 80, 4, 3);            // warning_code
    setBits(bits, 84, 12, 100);         // entry0 Ta
    setBits(bits, 84 + 12, 4, 2);       // entry0 Th
    setBits(bits, 84 + 16, 10, 100);    // entry0 Pl
    Message msg = decodeBits(bits);
    const TsunamiData* t = msg.getMt43()->getTsunami();
    REQUIRE(t != nullptr);
    CHECK(t->count == 1);
    CHECK(t->entries[0].region_code == 100);

    // 非準拠: entry0 は Pl=0 だが Ta/Th 非0 → 終端しない。entry1 も読む。
    uint8_t bits2[32] = {};
    mt43Header(bits2, 5);
    setBits(bits2, 84, 12, 100);        // entry0 Ta（非0）
    setBits(bits2, 84 + 12, 4, 2);      // entry0 Th（非0）
    setBits(bits2, 84 + 16, 10, 0);     // entry0 Pl=0
    setBits(bits2, 84 + 26, 12, 200);   // entry1 Ta
    setBits(bits2, 84 + 26 + 12, 4, 3); // entry1 Th
    setBits(bits2, 84 + 26 + 16, 10, 101); // entry1 Pl
    Message msg2 = decodeBits(bits2);
    const TsunamiData* t2 = msg2.getMt43()->getTsunami();
    REQUIRE(t2 != nullptr);
    CHECK(t2->count == 2);
    CHECK(t2->entries[0].arrival_time_raw == 100);
    CHECK(t2->entries[0].height_code == 2);
    CHECK(t2->entries[0].region_code == 0);
    CHECK(t2->entries[1].region_code == 101);

    // Pl 非0・Ta=Th=0 のエントリは含む（終端しない）。
    uint8_t bits3[32] = {};
    mt43Header(bits3, 5);
    setBits(bits3, 84 + 16, 10, 100);   // entry0 Pl のみ非0
    Message msg3 = decodeBits(bits3);
    const TsunamiData* t3 = msg3.getMt43()->getTsunami();
    REQUIRE(t3 != nullptr);
    CHECK(t3->count == 1);
    CHECK(t3->entries[0].region_code == 100);
    CHECK(t3->entries[0].arrival_time_raw == 0);
}
#endif // AZARAC_ENABLE_TSUNAMI

#if (AZARAC_ENABLE_NW_PAC_TSUNAMI)
TEST_CASE("NW Pacific tsunami list: termination is whole-entry zero, not Pl only") {
    // entry0: Ta=100, Th=2, Pl=5（有効）。entry1: 全 0 → 終端。
    uint8_t bits[32] = {};
    mt43Header(bits, 6);
    setBits(bits, 53, 3, 1);            // potential
    setBits(bits, 56, 12, 100);         // entry0 Ta
    setBits(bits, 56 + 12, 9, 2);       // entry0 Th
    setBits(bits, 56 + 21, 7, 5);       // entry0 Pl
    Message msg = decodeBits(bits);
    const NwPacTsunamiData* t = msg.getMt43()->getNwPac();
    REQUIRE(t != nullptr);
    CHECK(t->count == 1);
    CHECK(t->entries[0].region_code == 5);

    // 非準拠: entry0 は Pl=0 だが Ta/Th 非0 → 終端しない。
    uint8_t bits2[32] = {};
    mt43Header(bits2, 6);
    setBits(bits2, 56, 12, 100);        // entry0 Ta
    setBits(bits2, 56 + 12, 9, 2);      // entry0 Th
    setBits(bits2, 56 + 21, 7, 0);      // entry0 Pl=0
    setBits(bits2, 56 + 28, 12, 200);   // entry1 Ta
    setBits(bits2, 56 + 28 + 12, 9, 3); // entry1 Th
    setBits(bits2, 56 + 28 + 21, 7, 6); // entry1 Pl
    Message msg2 = decodeBits(bits2);
    const NwPacTsunamiData* t2 = msg2.getMt43()->getNwPac();
    REQUIRE(t2 != nullptr);
    CHECK(t2->count == 2);
    CHECK(t2->entries[0].arrival_time_raw == 100);
    CHECK(t2->entries[0].region_code == 0);
    CHECK(t2->entries[1].region_code == 6);

    // Pl 非0・Ta=Th=0 は含む。
    uint8_t bits3[32] = {};
    mt43Header(bits3, 6);
    setBits(bits3, 56 + 21, 7, 5);      // entry0 Pl のみ非0
    Message msg3 = decodeBits(bits3);
    const NwPacTsunamiData* t3 = msg3.getMt43()->getNwPac();
    REQUIRE(t3 != nullptr);
    CHECK(t3->count == 1);
    CHECK(t3->entries[0].region_code == 5);
}
#endif // AZARAC_ENABLE_NW_PAC_TSUNAMI
