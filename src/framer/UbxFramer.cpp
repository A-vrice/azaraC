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
        _st = (b == 0x62) ? St::CLASS : St::SYNC1;
        break;
    case St::CLASS:
        _class = b; _ck_a = _ck_b = 0;
        _ck_a += b; _ck_b += _ck_a;
        _st = St::ID;
        break;
    case St::ID:
        _id = b; _ck_a += b; _ck_b += _ck_a;
        _st = St::LEN_L;
        break;
    case St::LEN_L:
        _len = b; _ck_a += b; _ck_b += _ck_a;
        _st = St::LEN_H;
        break;
    case St::LEN_H:
        _len |= (uint16_t)b << 8;
        _ck_a += b; _ck_b += _ck_a;
        _pos = 0;
        _st = (_len > 0 && _len <= sizeof(_buf)) ? St::PAYLOAD : St::SYNC1;
        break;
    case St::PAYLOAD:
        _buf[_pos++] = b;
        _ck_a += b; _ck_b += _ck_a;
        if (_pos >= _len) _st = St::CK_A;
        break;
    case St::CK_A:
        if (b != _ck_a) { reset(); return false; }
        _st = St::CK_B;
        break;
    case St::CK_B:
        _st = St::SYNC1;
        if (b != _ck_b) return false;
        // class=0x02 id=0x13 = RXM-SFRBX
        if (_class != 0x02 || _id != 0x13) return false;
        return parse(out);
    }
    return false;
}

bool UbxFramer::parse(Frame& out) {
    // SFRBX header: gnssId(1) svId(1) sigId(1) freqId(1) numWords(1) chn(1) version(1) reserved(1)
    if (_len < 8) return false;
    uint8_t gnssId   = _buf[0];
    uint8_t svId     = _buf[1];
    uint8_t sigId    = _buf[2];
    uint8_t numWords = _buf[4];

    // QZSS gnssId=5, L1S sigId=0 or 1
    if (gnssId != 5)  return false;
    if (sigId != 0 && sigId != 1) return false;
    if (numWords < 8) return false;  // L1S subframe = 8 words × 32 bits = 256 bits (250 data bits)
    if (_len < 8u + numWords * 4u) return false;

    // Pack 250 nav bits MSB-first into out.bits[32]: 8 words × 32 bits (256 total),
    // first 250 are data, last 6 of word 8 are zero-filled padding.
    memset(out.bits, 0, sizeof(out.bits));
    uint16_t bit_pos = 0;
    for (uint8_t w = 0; w < numWords && bit_pos < 250; ++w) {
        // Words are little-endian in the UBX payload
        uint32_t word = ((uint32_t)_buf[8 + w*4 + 3] << 24) |
                        ((uint32_t)_buf[8 + w*4 + 2] << 16) |
                        ((uint32_t)_buf[8 + w*4 + 1] <<  8) |
                         (uint32_t)_buf[8 + w*4 + 0];
        // Bit 31 of the first word is the first bit of the subframe.
        for (int8_t b2 = 31; b2 >= 0 && bit_pos < 250; --b2, ++bit_pos) {
            if ((word >> b2) & 1u) {
                out.bits[bit_pos / 8] |= (0x80u >> (bit_pos % 8));
            }
        }
    }
    // Convert ublox svId to L1S PRN if possible, else keep original
    auto prn_str = def::ublox_qzss_svid_prn_map_lookup(svId);
    if (prn_str.has_value()) {
        out.svid = 0;
        for (char c : prn_str.value()) {
            out.svid = out.svid * 10 + (c - '0');
        }
    } else {
        out.svid = svId;
    }
    
    out.source = FrameSource::UBX;
    return true;
}

} // namespace internal
} // namespace azaraC
