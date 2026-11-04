#include "UbxFramer.h"
#include "definition/_index.h"
#if defined(__AVR__)
#include "../internal/avr_std/cstring"
#else
#include <cstring>
#endif

namespace azaraC {
namespace internal {

void UbxFramer::reset() {
    _st  = St::SYNC1;
    _pos = 0;
    _ck_a = _ck_b = 0;
}

bool UbxFramer::feed(uint8_t b, Frame& out) {
    switch (_st) {
    case St::SYNC1:
        if (b == 0xB5) _st = St::SYNC2;
        break;
    case St::SYNC2:
        if (b == 0x62) _st = St::CLASS;
        else if (b != 0xB5) _st = St::SYNC1;
        // この 0xB5 は新フレームの先頭候補なので SYNC2 を維持して取り直す
        break;
    case St::CLASS:
        // SFRBX のヘッダは 02 13 28 00 固定なので、ここに来た 0xB5 は新たな同期候補。フレームを捨てずに取り直す。
        if (b == 0xB5) { _st = St::SYNC2; break; }
        _class = b; _ck_a = _ck_b = 0;
        _ck_a += b; _ck_b += _ck_a;
        _st = St::ID;
        break;
    case St::ID:
        if (b == 0xB5) { _st = St::SYNC2; break; }
        _id = b; _ck_a += b; _ck_b += _ck_a;
        _st = St::LEN_L;
        break;
    case St::LEN_L:
        if (b == 0xB5) { _st = St::SYNC2; break; }
        _len = b; _ck_a += b; _ck_b += _ck_a;
        _st = St::LEN_H;
        break;
    case St::LEN_H:
        _len |= (uint16_t)b << 8;
        _ck_a += b; _ck_b += _ck_a;
        _pos = 0;
        _st = (_len > 0 && _len <= sizeof(_buf)) ? St::PAYLOAD : (b == 0xB5 ? St::SYNC2 : St::SYNC1);
        break;
    case St::PAYLOAD:
        _buf[_pos++] = b;
        _ck_a += b; _ck_b += _ck_a;
        if (_pos >= _len) _st = St::CK_A;
        break;
    case St::CK_A:
        if (b != _ck_a) { bool sync = (b == 0xB5); reset(); if (sync) _st = St::SYNC2; return false; }
        _st = St::CK_B;
        break;
    case St::CK_B:
        _st = St::SYNC1;
        // b は次フレームの同期候補にもなる: どの拒否でも 0xB5 の候補を残す
        if (b != _ck_b) { if (b == 0xB5) _st = St::SYNC2; return false; }
        // class=0x02 id=0x13 = RXM-SFRBX
        if (_class != 0x02 || _id != 0x13) { if (b == 0xB5) _st = St::SYNC2; return false; }
        if (!parse(out)) { if (b == 0xB5) _st = St::SYNC2; return false; }
        return true;
    }
    return false;
}

bool UbxFramer::parse(Frame& out) {
    // SFRBX ヘッダ: gnssId(1) svId(1) sigId(1) freqId(1) numWords(1) chn(1) version(1) reserved(1)
    if (_len < 8) return false;
    uint8_t gnssId   = _buf[0];
    uint8_t svId     = _buf[1];
    uint8_t sigId    = _buf[2];
    uint8_t numWords = _buf[4];

    // QZSS は gnssId=5、L1S は sigId=0 か 1
    if (gnssId != 5)  return false;
    if (sigId != 0 && sigId != 1) return false;
    // L1S サブフレーム = 8 ワード × 32 bit = 256 bit（データは 250 bit）。u-blox は詰め物のワードを
    // 1 個足すことがある（numWords=9。実機の azarashi フィクスチャは 8/9 の両方）。それ以外は拒否し、長すぎるフレームが 250 bit の詰めループを越えて余分なワードを持ち込めないようにする。
    if (numWords != 8 && numWords != 9) return false;
    if (_len != 8u + static_cast<uint16_t>(numWords) * 4u) return false;

    // 航法ビットを MSB-first で out.bits[32] へ詰める: 8 ワード × 32 bit = 256、先頭 250 がデータで残りはゼロ詰め。
    // ワードはリトルエンディアンで word の bit31 がサブフレームの先頭ビットなので、各ワードのバイトスワップがそのまま out.bits の該当 4 バイトになる（1 bit ずつの可変シフトループの代わりに直接ストア）。
    // 先頭 7 ワード = 28 バイトは全域データ。word7 は bit 224..249 がデータで byte28-30 が全域、byte31 は上位 2 bit のみ（残り 6 bit はゼロ詰めのまま）。numWords=9 の余剰ワードは無視する。
    memset(out.bits, 0, sizeof(out.bits));
    for (uint8_t w = 0; w < numWords && w < 8; ++w) {
        const uint8_t b0 = _buf[8 + w * 4u + 0], b1 = _buf[8 + w * 4u + 1];
        const uint8_t b2 = _buf[8 + w * 4u + 2], b3 = _buf[8 + w * 4u + 3];
        if (w < 7) {
            out.bits[w * 4u + 0] = b3;
            out.bits[w * 4u + 1] = b2;
            out.bits[w * 4u + 2] = b1;
            out.bits[w * 4u + 3] = b0;
        } else {
            out.bits[28] = b3;
            out.bits[29] = b2;
            out.bits[30] = b1;
            out.bits[31] = (uint8_t)(b0 & 0xC0u);
        }
    }
    // SVID→PRN 変換は数値参照で直接取る（ラベル経由だと AVR で共有バッファコピー+再パースが発生する）。
    const auto prn = def::ublox_qzss_svid_prn_map_lookup_num(svId);
    out.svid = prn.value_or(svId);
    return true;
}

} // namespace internal
} // namespace azaraC
