#pragma once
// NMEA を出力する受信機からの $QZQSM 文を解析する。

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
    uint8_t _xsum  = 0;  // 受信バイトの XOR 継続値
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
