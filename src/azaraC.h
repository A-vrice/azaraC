#pragma once
// azaraC — QZSS L1S DCX/CAMF + QZQSM decoder for Arduino
//
// Usage:
//   #include <azaraC.h>
//
// Optional compile-time overrides (define BEFORE this include):
//   #define AZARAC_DEDUP_SLOTS 16   // default: 8
//   #define AZARAC_LANG_JA 1        // Enable Japanese labels (default: 1)
//   #define AZARAC_LANG_EN 0        // Enable English labels (default: 0)

// ---- language selection macros -----------------------------------------------
#ifndef AZARAC_LANG_JA
#define AZARAC_LANG_JA 1
#endif

#ifndef AZARAC_LANG_EN
#define AZARAC_LANG_EN 0
#endif

// ---- disaster category control macros ----------------------------------------
#ifndef AZARAC_ENABLE_EEW
#define AZARAC_ENABLE_EEW 1
#endif
#ifndef AZARAC_ENABLE_HYPOCENTER
#define AZARAC_ENABLE_HYPOCENTER 1
#endif
#ifndef AZARAC_ENABLE_SEISMIC
#define AZARAC_ENABLE_SEISMIC 1
#endif
#ifndef AZARAC_ENABLE_NANKAI
#define AZARAC_ENABLE_NANKAI 1
#endif
#ifndef AZARAC_ENABLE_TSUNAMI
#define AZARAC_ENABLE_TSUNAMI 1
#endif
#ifndef AZARAC_ENABLE_NW_PAC_TSUNAMI
#define AZARAC_ENABLE_NW_PAC_TSUNAMI 1
#endif
#ifndef AZARAC_ENABLE_VOLCANO
#define AZARAC_ENABLE_VOLCANO 1
#endif
#ifndef AZARAC_ENABLE_ASH_FALL
#define AZARAC_ENABLE_ASH_FALL 1
#endif
#ifndef AZARAC_ENABLE_WEATHER
#define AZARAC_ENABLE_WEATHER 1
#endif
#ifndef AZARAC_ENABLE_FLOOD
#define AZARAC_ENABLE_FLOOD 1
#endif
#ifndef AZARAC_ENABLE_TYPHOON
#define AZARAC_ENABLE_TYPHOON 1
#endif
#ifndef AZARAC_ENABLE_MARINE
#define AZARAC_ENABLE_MARINE 1
#endif

#include "Message.h"
#include "Parser.h"
#include "internal/JsonSerializer.h"

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
