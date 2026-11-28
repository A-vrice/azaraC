#include "azaraC_config.h"
#include "framer/NmeaFramer.h"
#include <cassert>
#include <cstdio>

namespace {
size_t sentence(char (&out)[82], unsigned svid, uint8_t last, size_t hex_count) {
    size_t n = static_cast<size_t>(std::snprintf(out, sizeof(out), "$QZQSM,%02u,", svid));
    const char hex[] = "0123456789ABCDEF";
    for (size_t i = 0; i < hex_count; ++i) {
        out[n++] = i == 0 ? '5' : i == 1 ? '3' :
            i == 62 ? hex[last >> 4] : i == 63 ? hex[last & 15] : '0';
    }
    uint8_t checksum = 0;
    for (size_t i = 1; i < n; ++i) checksum ^= static_cast<uint8_t>(out[i]);
    n += static_cast<size_t>(std::snprintf(out + n, sizeof(out) - n, "*%02X\r\n", checksum));
    return n;
}

bool accepts(const char* s, size_t len, azaraC::internal::Frame& out) {
    azaraC::internal::NmeaFramer framer;
    bool accepted = false;
    for (size_t i = 0; i < len; ++i) accepted = framer.feed(static_cast<uint8_t>(s[i]), out) || accepted;
    return accepted;
}
}

int main() {
    char text[82] = {};
    azaraC::internal::Frame out{};
    assert(!accepts(text, 0, out));
    for (unsigned svid = 0; svid <= 99; ++svid) {
        bool want = svid <= 63;
#if AZARAC_NMEA_STRICT_SVID == 1
        want = svid >= 53 && svid <= 63;
#elif AZARAC_NMEA_STRICT_SVID == 2
        want = svid == 55 || svid == 56 || svid == 57 || svid == 58 || svid == 61;
#endif
        const size_t n = sentence(text, svid, 0xC0, 64);
        const bool accepted = accepts(text, n, out);
        assert(accepted == want);
        if (accepted) assert(out.svid == (svid | 0x80));
    }
    for (size_t hex_count = 63; hex_count <= 64; ++hex_count) {
        for (unsigned padding = 0; padding < 64; ++padding) {
            const uint8_t last = static_cast<uint8_t>(0xC0 | padding);
            const size_t n = sentence(text, 55, last, hex_count);
            const bool dirty = (padding & (hex_count == 63 ? 0x30u : 0x3Fu)) != 0;
            const bool want = !AZARAC_NMEA_REJECT_NONZERO_PADDING || !dirty;
            const bool accepted = accepts(text, n, out);
            assert(accepted == want);
            if (accepted) assert(out.bits[31] == 0xC0);
        }
    }
    const size_t n = sentence(text, 55, 0, 64);
    text[n - 4] = '!';
    assert(!accepts(text, n, out));
    std::printf("nmea-policy: OK (SVID=%d padding=%d)\n",
        AZARAC_NMEA_STRICT_SVID, AZARAC_NMEA_REJECT_NONZERO_PADDING);
}
