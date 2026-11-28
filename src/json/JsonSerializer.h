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
    // 戻り値は書き込んだ長さ、required は完全な JSON の長さ（ともに NUL を除く）。
    // buf が非 nullptr かつ len > 0 なら NUL 終端する。nullptr / len == 0 は測長のみ。
    static size_t serialize(const Message& msg, char* buf, size_t len, size_t* required = nullptr);
};

} // namespace internal
} // namespace azaraC
