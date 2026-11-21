#pragma once

#include "Frame.h"

namespace azaraC {

class IFramer {
public:
    // `out` の両メンバー（svid と bits の 32 バイト全部）を埋め終えてから true を返すこと。
    // 独自フレーマー経路では Parser がゼロ初期化するが、部分書き込みでも全ゼロのデータとして復号されてしまう。
    virtual bool feed(uint8_t byte, Frame& out) = 0;
    virtual void reset() = 0;
    virtual ~IFramer() = default;
};

} // namespace azaraC
