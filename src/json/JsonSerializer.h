#pragma once
// azaraC - src/json/JsonSerializer.h

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
};

} // namespace internal
} // namespace azaraC
