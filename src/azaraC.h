#pragma once
// azaraC — QZSS L1S DCX/CAMF + QZQSM decoder for Arduino
#if __cplusplus < 201703L
#error "This tool requires C++17 or later"
#endif

// Workarounds for Arduino core headers that define function-like macros
// colliding with C++ standard library names:
//   - arduino:mbed_nano (and other mbed cores): pinDefinitions.h defines `abs`
//     as a macro, breaking std::chrono / standard headers using abs().
//   - arduino:avr (Uno etc.): Arduino.h defines `min`/`max` as macros,
//     breaking std::min/std::max (used by Message.h and the AVR stdlib shims).
// Undefine them before including any header that uses the std names.
#if defined(ARDUINO)
#  if defined(abs)
#    undef abs
#  endif
#  if defined(min)
#    undef min
#  endif
#  if defined(max)
#    undef max
#  endif
#endif

// Users may #define AZARAC_* overrides BEFORE this include.
// Those overrides are picked up by azaraC_config.h.

#include "azaraC_config.h"

#include "Message.h"
#include "Parser.h"
#include "json/JsonSerializer.h"

#if defined(ARDUINO) && ARDUINO >= 1
#  include <Print.h>
#endif

namespace azaraC {

// Convenience wrapper: serialize msg as JSON to any Print& (Serial, WiFiClient, etc.)
inline void toJson(const Message& msg, Print& out) {
    internal::JsonSerializer::serialize(msg, out);
}

} // namespace azaraC
