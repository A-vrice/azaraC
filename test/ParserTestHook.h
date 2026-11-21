#pragma once

#include "Parser.h"

#if defined(AZARAC_TESTING) && AZARAC_TESTING
namespace azaraC {
namespace internal {

struct ParserTestHook {
    static bool postDecode(Parser& parser, const Message& decoded, Message& out,
                           uint32_t identity, uint64_t now_ms) {
        return parser.postDecodeAt(decoded, out, identity, now_ms);
    }

    static uint64_t observeClock(Parser& parser, uint64_t now_ms) {
        return parser.observeClock(now_ms);
    }

#if AZARAC_ENABLE_NANKAI
    static const NankaiPageBuffer* getBuffer(const Parser& parser, const NankaiPageKey& key) {
        return parser._nankaiBuffers.getBuffer(key);
    }
#endif
};

} // namespace internal
} // namespace azaraC
#endif
