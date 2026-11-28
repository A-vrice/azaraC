// libFuzzer ハーネス: バイトストリーム / フレーマ / JSON 出力のカバレッジ誘導 fuzz。
// ビルド・実行: make -C test fuzz-libfuzzer（clang++ 必須。Linux/CI ターゲット）。
// 入力レイアウト: data[0] % 4 が経路、data[1:] がバイト列。
//   0: Parser AUTO ストリーム  1: NmeaFramer 直接  2: UbxFramer 直接  3: Parser + toJson + JsonCheck
// 決定性: dedup/Nankai の窓（分〜24h）は 1 入力の実行時間（µs〜ms）では決して期限切れにならないため、
// getMillis() の壁時計依存は判定に影響しない（クラッシュ入力の再現が可能）。

#include <cstdint>
#include <cstddef>

#define ARDUINO 0
#include "azaraC.h"
#include "framer/NmeaFramer.h"
#include "framer/UbxFramer.h"
#include "internal/PrintShim.h"
#include "json/JsonCheck.h"

using namespace azaraC;
using namespace azaraC::internal;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
    if (size == 0) return 0;
    const uint8_t* p = data + 1;
    const size_t n = size - 1;
    switch (data[0] & 3u) {
    case 0: {
        Parser parser;
        Message msg{};
        for (size_t i = 0; i < n; ++i) parser.feed(p[i], msg);
        break;
    }
    case 1: {
        NmeaFramer framer;
        Frame frame{};
        for (size_t i = 0; i < n; ++i) if (framer.feed(p[i], frame)) framer.reset();
        break;
    }
    case 2: {
        UbxFramer framer;
        Frame frame{};
        for (size_t i = 0; i < n; ++i) if (framer.feed(p[i], frame)) framer.reset();
        break;
    }
    default: {
        Parser parser;
        Message msg{};
        StringPrint out;
        for (size_t i = 0; i < n; ++i) {
            if (!parser.feed(p[i], msg)) continue;
            out.clear();
            toJson(msg, out);
            JsonCheck check(out.str());
            if (!check.run()) __builtin_trap();
        }
        break;
    }
    }
    return 0;
}
