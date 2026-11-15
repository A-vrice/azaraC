#pragma once

#include "../Message.h"

#if defined(ARDUINO) && ARDUINO >= 1
#  include <Print.h>
#else
#  include "../internal/PrintShim.h"
#endif

namespace azaraC {
namespace internal {

class JsonSerializer {
public:
    static void serialize(const Message& msg, Print& out);

    // 境界付きバッファへ書き出す（Print を持たない呼び出し側向け）。
    // len が 0 のときは何も書かず 0 を返す。len > 0 なら必ず NUL 終端し、
    // 入り切らない残りは捨てる（バッファ外へは 1 バイトも書かない）。
    // 戻り値は書き込んだバイト数（NUL を除く）。必要な長さは切り詰め時も返らないので、
    // 完全な JSON が要るなら Print 版か、十分な len を渡すこと。
    static size_t serialize(const Message& msg, char* buf, size_t len);
};

} // namespace internal
} // namespace azaraC
