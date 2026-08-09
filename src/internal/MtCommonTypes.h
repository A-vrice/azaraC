#pragma once
// Shared types used by both MT=43 (QZQSM/DCR) and MT=44 (DCX/CAMF)

#if defined(__AVR__)
#include "avr_std/cstdint"
#else
#include <cstdint>
#endif

namespace azaraC {

// shared sub-structs

struct TimeFields {
    uint8_t  month;   // 1-12 (0 = unresolved)
    uint8_t  day;     // 1-31 (0 = unresolved)
    uint8_t  hour;    // 0-23
    uint8_t  minute;  // 0-59
    uint32_t unix_time; // 0 = not resolved
};

struct LatLon {
    uint8_t  lat_ns;   // 0=N 1=S
    uint8_t  lat_deg;  // 0-89
    uint8_t  lat_min;  // 0-59
    uint8_t  lat_sec;  // 0-59
    uint8_t  lon_ew;   // 0=E 1=W
    uint16_t lon_deg;  // 0-179
    uint8_t  lon_min;  // 0-59
    uint8_t  lon_sec;  // 0-59
};

} // namespace azaraC
