#pragma once
// Parses UBX-RXM-SFRBX (class=0x02, id=0x13) from u-blox receivers.
// Only accepts QZSS L1S subframes (gnssId=5, sigId∈{0,1}).

#include "IFramer.h"

namespace azaraC {
namespace internal {

class UbxFramer : public IFramer {
public:
    bool feed(uint8_t byte, Frame& out) override;
    void reset() override;

private:
    enum class St : uint8_t {
        SYNC1, SYNC2, CLASS, ID,
        LEN_L, LEN_H, PAYLOAD, CK_A, CK_B
    };

    St      _st    = St::SYNC1;
    uint8_t _class = 0;
    uint8_t _id    = 0;
    uint16_t _len  = 0;
    uint16_t _pos  = 0;
    uint8_t  _ck_a = 0, _ck_b = 0;
    uint8_t  _buf[64] = {};   // SFRBX max payload = 8(header) + 4*10(words) = 48 bytes; 64 for safety margin

    bool parse(Frame& out);
};

} // namespace internal
} // namespace azaraC
