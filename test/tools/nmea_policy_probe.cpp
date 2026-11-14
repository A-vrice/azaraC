// AZARAC_NMEA_STRICT_SVID / AZARAC_NMEA_REJECT_NONZERO_PADDING の受理表を実行検証する。
// make nmea-policy が 3 構成（既定 / STRICT=1 / STRICT=2+REJECT=1）でビルド・実行する。
#include <cstdio>
#include <string>
#include "azaraC_config.h"
#include "framer/NmeaFramer.h"

namespace {

int failures = 0;

void expect(bool got, bool want, const char* what) {
    if (got == want) return;
    std::printf("FAIL: %s (accepted=%d, expected=%d)\n", what, got ? 1 : 0, want ? 1 : 0);
    ++failures;
}

// $QZQSM 文を組み立てる。last は 32 バイト目（フレーム bit 248-255）で、下位 6 bit が仕様上のパディング域。
std::string sentence(uint8_t svid, uint8_t last) {
    uint8_t bits[32] = {};
    bits[0] = 0x53;   // preamble
    bits[31] = last;
    char head[24];
    std::snprintf(head, sizeof head, "$QZQSM,%02u,", static_cast<unsigned>(svid));
    std::string s = head;
    char hex[3];
    for (int i = 0; i < 32; ++i) {
        std::snprintf(hex, sizeof hex, "%02X", bits[i]);
        s += hex;
    }
    uint8_t x = 0;
    for (size_t i = 1; i < s.size(); ++i) x ^= static_cast<uint8_t>(s[i]);
    char tail[8];
    std::snprintf(tail, sizeof tail, "*%02X\r\n", x);
    return s + tail;
}

bool accepts(const std::string& s) {
    azaraC::internal::NmeaFramer framer;
    azaraC::internal::Frame frame;
    for (char c : s) {
        if (framer.feed(static_cast<uint8_t>(c), frame)) return true;
    }
    return false;
}

} // namespace

int main() {
    for (uint8_t svid = 0; svid <= 63; ++svid) {
        bool want = true;
#if AZARAC_NMEA_STRICT_SVID == 1
        want = (svid >= 53);
#elif AZARAC_NMEA_STRICT_SVID == 2
        want = (svid == 55 || svid == 56 || svid == 57 || svid == 58 || svid == 61);
#endif
        char name[32];
        std::snprintf(name, sizeof name, "svid %u", static_cast<unsigned>(svid));
        expect(accepts(sentence(svid, 0x00)), want, name);
    }

#if AZARAC_NMEA_REJECT_NONZERO_PADDING
    expect(accepts(sentence(55, 0x3F)), false, "padding bits 250-255 nonzero must be rejected");
#else
    expect(accepts(sentence(55, 0x3F)), true, "padding bits 250-255 nonzero must be masked");
#endif
    expect(accepts(sentence(55, 0x00)), true, "zero padding must be accepted");

    if (failures != 0) {
        std::printf("%d failure(s)\n", failures);
        return 1;
    }
    std::printf("ok\n");
    return 0;
}