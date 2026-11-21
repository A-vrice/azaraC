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
    // 戻り値は書き込んだバイト数（NUL を除く）。
    // required が非 nullptr なら完全な JSON の長さ（NUL を除く）を入れる。*required > 戻り値 なら切り詰め。
    // buf == nullptr / len == 0 でも required は埋まるので、長さだけ測ることもできる。
    static size_t serialize(const Message& msg, char* buf, size_t len, size_t* required = nullptr);
};

} // namespace internal
} // namespace azaraC
