#pragma once
// azaraC - src/framer/NmeaFramer.h
// Parses $QZQSM sentences from any NMEA-outputting receiver.

#include "IFramer.h"

namespace azaraC {
namespace internal {

class NmeaFramer : public IFramer {
public:
    bool feed(uint8_t byte, Frame& out) override;
    void reset() override;

private:
    enum class St : uint8_t { WAIT, COLLECT, CSUM1, CSUM2 };
    St      _st    = St::WAIT;
    char    _buf[82] = {};
    uint8_t _pos   = 0;
    uint8_t _xsum  = 0;  // running XOR
    uint8_t _csumH = 0;

    bool parse(Frame& out);
    static constexpr uint8_t hexVal(char c) {
        if (c >= '0' && c <= '9') return c - '0';
        if (c >= 'A' && c <= 'F') return c - 'A' + 10;
        if (c >= 'a' && c <= 'f') return c - 'a' + 10;
        return 0xFF;
    }
};

} // namespace internal
} // namespace azaraC
