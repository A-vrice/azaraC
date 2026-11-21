#include "NmeaFramer.h"
#include "../azaraC_config.h"
#if defined(__AVR__)
#include "../internal/avr_std/cstring"
#else
#include <cstring>
#endif

namespace azaraC {
namespace internal {

void NmeaFramer::reset() {
    _st  = St::WAIT;
    _pos = 0;
    _xsum = 0;
    _csumH = 0;
}

bool NmeaFramer::feed(uint8_t b, Frame& out) {
    char c = static_cast<char>(b);
    if (c == '$') {
        _pos = 0; _xsum = 0; _st = St::COLLECT;
        return false;
    }

    switch (_st) {
    case St::WAIT:
        break;
    case St::COLLECT:
        if (c == '*') {
            _buf[_pos] = '\0';
            _st = St::CSUM1;
        } else if (c == '\r' || c == '\n') {
            reset();
        } else {
            if (_pos < sizeof(_buf) - 1) {
                _xsum ^= b;
                _buf[_pos++] = static_cast<char>(c);
            } else {
                reset();  // 溢れたら切り詰め済み接頭＋一致チェックサムでも解析させない
            }
        }
        break;
    case St::CSUM1: {
        uint8_t hi = hexVal(c);
        if (hi == 0xFF) { reset(); break; }
        _csumH = hi;
        _st = St::CSUM2;
        break;
    }
    case St::CSUM2: {
        uint8_t lo = hexVal(c);
        if (lo == 0xFF) { reset(); break; }
        uint8_t recv = (_csumH << 4) | lo;
        _st = St::WAIT;
        if (recv != _xsum) return false;
        return parse(out);
    }
    }
    return false;
}

bool NmeaFramer::parse(Frame& out) {
    // 期待する形: QZQSM,<svid>,<hex-data>先頭 6 バイトは固定なので Flash に置く（素のリテラルは avr-libc のリンカスクリプトで .data = SRAM に入る）。
    // リテラルは AZARAC_STRNCMP_P が PSTR で包むので、ここでは素のままでよい（ホストでは no-op）。
    if (AZARAC_STRNCMP_P(_buf, "QZQSM,", 6) != 0) return false;

    char* p = _buf + 6;
    uint16_t svid_tmp = 0;
    uint8_t digit_count = 0;
    while (*p && *p != ',') {
        if (*p >= '0' && *p <= '9') {
            svid_tmp = svid_tmp * 10 + (*p - '0');
            ++digit_count;
            if (svid_tmp > 255) return false;
        } else {
            return false;
        }
        p++;
    }
    // 仕様の Satellite ID は「PRN 下位 6bit の2桁10進」（DCR-017 §4.3.1 / Table 4.3.1-1、DCX-004 §4.4.1 / Table 4.4-1）。
    // 1桁は仕様の2文字表記に合わない（PRN 183 = 55 は2桁）。3桁は `| 0x80` しても PRN 契約（181-191）の外の値になる（100 → 228）。
    // 64-99 は2桁だが 6bit に収まらないため拒否する（64 → 192）。
    // 0-52 は 6bit として有効だが PRN 128-180 に対応し、L1S の PRN 契約（181-191）の外になる。
    // 既定は実機互換のため通し、利用側が svid で絞る（azarashi も長さ 2 を要求して拒否する）。
    // AZARAC_NMEA_STRICT_SVID でフレーマ側の受理範囲を絞れる（0=現状 / 1=53-63 / 2=仕様表の列挙）。
    if (digit_count != 2 || *p != ',' || svid_tmp > 63) return false;
#if AZARAC_NMEA_STRICT_SVID == 1
    if (svid_tmp < 53) return false;   // PRN 181-191 の外（L1S の契約外）
#elif AZARAC_NMEA_STRICT_SVID == 2
    switch (svid_tmp) {
    case 55: case 56: case 57: case 58: case 61: break;   // PRN 183,184,185,186,189
    default: return false;
    }
#endif
    uint8_t svid = static_cast<uint8_t>(svid_tmp);
    ++p;

    memset(out.bits, 0, sizeof(out.bits));
    uint8_t byte_idx = 0;
    uint8_t hex_count = 0;
    uint8_t nibble = 0;

    while (*p && ((*p >= '0' && *p <= '9') || (*p >= 'A' && *p <= 'F') || (*p >= 'a' && *p <= 'f'))) {
        if (hex_count >= 64) return false;
        uint8_t val = hexVal(*p++);
        if (val == 0xFF) return false;      // 保険: ループ条件で既に弾いている
        hex_count++;
        if (byte_idx >= 32) continue;       // 数えるのは続ける: 総長の検証は hex_count が行う
        nibble = (nibble << 4) | val;
        if ((hex_count & 1) == 0) {
            out.bits[byte_idx++] = nibble;
            nibble = 0;
        }
    }
    // QZSS L1S = 252 bit（250 bit データ + 2 bit 詰め物、仕様 Table 4.3.1-1）= 63 hex 文字だが、64 文字で送る受信機もあるので両方受ける。
    // '*' より前の余分なバイト（feed が NUL 終端済み）はゴミなので拒否する。
    if (hex_count != 63 && hex_count != 64) return false;
    if (*p != '\0') return false;

    if ((hex_count & 1) && byte_idx < 32) {
        out.bits[byte_idx++] = nibble << 4;
    }
    // 64 hex 文字（32 バイト）: bit 252-255 をマスクする。bit 250-251 は仕様上 0 が保証される。
    // 非 0 を拒否するかは AZARAC_NMEA_REJECT_NONZERO_PADDING（既定 0 = マスクして受理）。
    if (hex_count >= 63) {
#if AZARAC_NMEA_REJECT_NONZERO_PADDING
        if ((out.bits[31] & 0x3Fu) != 0) return false;
#endif
        out.bits[31] &= 0xC0u;
    }

    // QZQSM の Satellite ID は PRN の下位 6bit (DCR-017 §4.3.1 / DCX-004 §4.4.1)。
    // Frame::svid は PRN 契約（api-reference.md の 181-191）なので上位ビットを立てて正規化する。
    out.svid = static_cast<uint8_t>(svid | 0x80);

    return true;
}

} // namespace internal
} // namespace azaraC
