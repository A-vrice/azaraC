// azaraC - src/internal/NmeaFramer.cpp

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
            }
            // else: silently drop the byte. If the sentence is garbage, the checksum
            // will reject it later. Truncating is safer than resetting mid-sentence
            // which could drop the sentence boundary.
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
        if (lo == 0xFF || _csumH == 0xFF) { reset(); break; }
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

    // parse svid
    char* p = _buf + 6;
    uint16_t svid_tmp = 0;
    bool has_digit = false;
    while (*p && *p != ',') {
        if (*p >= '0' && *p <= '9') {
            svid_tmp = svid_tmp * 10 + (*p - '0');
            has_digit = true;
            if (svid_tmp > 255) return false;
        } else {
            return false; // Reject non-digit characters
        }
        p++;
    }
    if (!has_digit || *p != ',') return false;
    uint8_t svid = static_cast<uint8_t>(svid_tmp);
    ++p;  // skip comma

    // hex decode into bits[] — single pass
    memset(out.bits, 0, sizeof(out.bits));
    uint8_t byte_idx = 0;
    uint8_t hex_count = 0;
    uint8_t nibble = 0;

    while (*p && ((*p >= '0' && *p <= '9') || (*p >= 'A' && *p <= 'F') || (*p >= 'a' && *p <= 'f'))) {
        if (hex_count >= 64) return false;  // reject payloads longer than 64 hex chars
        uint8_t val = hexVal(*p++);
        if (val == 0xFF) return false;      // defensive: loop condition already filters
        hex_count++;
        if (byte_idx >= 32) continue;       // first 32 bytes captured; keep counting
        nibble = (nibble << 4) | val;
        if ((hex_count & 1) == 0) {
            out.bits[byte_idx++] = nibble;
            nibble = 0;
        }
    }

    // Validate length: QZSS L1S is 250 bits = 63 hex chars (31 bytes + 1 nibble).
    // Some receivers output 64 hex chars (32 bytes), so accept both 63 and 64.
    if (hex_count != 63 && hex_count != 64) return false;

    // Handle trailing nibble (odd hex length, e.g. 63 chars)
    if ((hex_count & 1) && byte_idx < 32) {
        out.bits[byte_idx++] = nibble << 4;
    }
    if (byte_idx < 31) return false;  // Need at least 31 bytes for 250 bits
    
    // For 64 hex chars (32 bytes), mask the last nibble (padding) to get 250 bits
    if (hex_count == 64) {
        out.bits[31] &= 0xF0;
    }

    // QZQSM NMEA SVID is L1S PRN - 128 (e.g. 56 -> 184)
    if (svid >= 55 && svid <= 63) {
        out.svid = svid + 128;
    } else {
        out.svid = svid;
    }
    
    out.source = FrameSource::NMEA;
    return true;
}

} // namespace internal
} // namespace azaraC
