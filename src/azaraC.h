#pragma once
// azaraC — QZSS L1S DCX/CAMF + QZQSM decoder for Arduino
#if __cplusplus < 201703L
#error "This tool requires C++17 or later"
#endif

// Undefine Arduino-core `abs`/`min`/`max` macros that collide with std names
// (mbed pinDefinitions.h defines abs; Arduino.h defines min/max).
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

// AZARAC_* overrides defined before this include are honored by azaraC_config.h.

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
