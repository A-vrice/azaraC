#pragma once
// azaraC — QZSS L1S DCX/CAMF + QZQSM decoder for Arduino

// Workaround for arduino:mbed_nano (and other mbed-based cores):
// pinDefinitions.h defines `abs` as a macro, which breaks std::chrono
// (and any standard library header that uses abs() as a function).
// Undefine it before including any headers that might pull in <chrono>.
#if defined(ARDUINO) && defined(abs)
#undef abs
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

#if __cplusplus < 201703L
#error "This tool requires C++17 or later"
#endif

namespace azaraC {

// Convenience wrapper: serialize msg as JSON to any Print& (Serial, WiFiClient, etc.)
inline void toJson(const Message& msg, Print& out) {
    internal::JsonSerializer::serialize(msg, out);
}

} // namespace azaraC
