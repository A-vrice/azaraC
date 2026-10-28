#pragma once

#if defined(__AVR__)
#include "../internal/avr_std/cstdint"
#else
#include <cstdint>
#endif

namespace azaraC {
namespace internal {

struct Frame {
    // 衛星 ID。NMEA/UBX の生 ID を L1S の PRN へ寄せる（仕様 ID 53–63 → 181–191）。
    // NMEA は 64–99 を拒否し、0–52 は 128–180 として通す（PRN 契約 181–191 の外なので利用側で絞る）。
    // UBX は未マッピングの svId をそのまま通す。
    uint8_t     svid;
    uint8_t     bits[32];   // 250 bit を MSB-first。bits[31] の下位 6 bit は詰め物のゼロ
};

} // namespace internal
} // namespace azaraC
