#include "NmeaFramer.h"
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
                reset();  // overrun: truncated prefix + matching checksum must not parse
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
    // Expected: QZQSM,<svid>,<hex-data>
    if (strncmp(_buf, "QZQSM,", 6) != 0) return false;

    char* p = _buf + 6;
    uint16_t svid_tmp = 0;
    bool has_digit = false;
    while (*p && *p != ',') {
        if (*p >= '0' && *p <= '9') {
            svid_tmp = svid_tmp * 10 + (*p - '0');
            has_digit = true;
            if (svid_tmp > 255) return false;
        } else {
            return false;
        }
        p++;
    }
    if (!has_digit || *p != ',') return false;
    uint8_t svid = static_cast<uint8_t>(svid_tmp);
    ++p;

    memset(out.bits, 0, sizeof(out.bits));
    uint8_t byte_idx = 0;
    uint8_t hex_count = 0;
    uint8_t nibble = 0;

    while (*p && ((*p >= '0' && *p <= '9') || (*p >= 'A' && *p <= 'F') || (*p >= 'a' && *p <= 'f'))) {
        if (hex_count >= 64) return false;
        uint8_t val = hexVal(*p++);
        if (val == 0xFF) return false;      // defensive: loop filter already excludes this
        hex_count++;
        if (byte_idx >= 32) continue;       // keep counting: hex_count still validates total length
        nibble = (nibble << 4) | val;
        if ((hex_count & 1) == 0) {
            out.bits[byte_idx++] = nibble;
            nibble = 0;
        }
    }
    // QZSS L1S = 252 bits (250 data + 2-bit padding, spec Table 4.3.1-1) = 63 hex chars, but some receivers emit 64, so accept both.
    // Trailing bytes before '*' (NUL-terminated by feed) are garbage -> reject.
    if (hex_count != 63 && hex_count != 64) return false;
    if (*p != '\0') return false;

    if ((hex_count & 1) && byte_idx < 32) {
        out.bits[byte_idx++] = nibble << 4;
    }
    // 64 hex chars (32 bytes): mask bits 252-255; bits 250-251 are spec-guaranteed 0
    if (hex_count >= 63) {
        out.bits[31] &= 0xC0;
    }

    // QZQSM の Satellite ID は PRN の下位 6bit (DCR-017 §4.3.1 / DCX-004 §4.3.1)。
    // Frame::svid は PRN 契約 (api-reference.md の 181-191) なので上位ビットを立てて正規化する。既に PRN (>=128) なら | 0x80 は恒等。
    out.svid = static_cast<uint8_t>(svid | 0x80);

    return true;
}

} // namespace internal
} // namespace azaraC
