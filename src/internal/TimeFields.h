#pragma once
// プラットフォーム非依存のオーバーフロー安全な millis()。外部依存なし。
// - Arduino: millis()（約 49.7 日で巻き戻る）を volatile カウンタで uint64_t へ拡張する。<atomic> を使わない（32 bit MCU の libatomic リンク問題を避ける）。
// - ホスト: std::chrono::steady_clock。
// volatile + read-compute-write は同期していない: マルチコアの呼び出し側では非単調な値を見得るが、単一タスクでの使用は安全。
// AVR と Cortex-M では、割り込みを無条件に許可するのではなく、呼び出し側の割り込み状態を保存して復元する。
#if defined(__AVR__)
#include "avr_std/cstdint"
#else
#include <cstdint>
#endif
#if defined(ARDUINO) && ARDUINO >= 1
#include <Arduino.h>
#else
#include <chrono>
#endif

namespace azaraC {
namespace internal {

// 現在時刻（ミリ秒、uint64_t、巻き戻し安全）。
static inline uint64_t getMillis() {
#if defined(ARDUINO) && ARDUINO >= 1
    // 上位 32 bit = 巻き戻り回数、下位 32 bit = 直近の生の millis() 値。
    // 同期しない read-compute-write はマルチコア / FreeRTOS で逆行し得るが、単一タスクの粗い計時には十分。
    static volatile uint64_t s_last = 0;

    uint32_t raw;
#if defined(__AVR__)
    // interrupts() を呼ばず SREG を保存する: getMillis() は呼び出し側のクリティカルセクションや
    // ISR から呼ばれ得るため、そこで割り込みを許可し直すとその原子性を壊す。
    uint8_t irq_state = SREG;
    cli();
#elif defined(__arm__)
    // Cortex-M: 割り込みを無条件に許可するのではなく PRIMASK を復元する。
    // mrs/msr を直接使う: CMSIS intrinsic は一部の Arduino ARM コア（rp2040、Teensy）で見えず、
    // どの Cortex-M もこの命令を備えている。
    uint32_t irq_state;
    __asm__ volatile("mrs %0, primask" : "=r"(irq_state));
    __asm__ volatile("cpsid i" ::: "memory");
#else
    // このコア（Xtensa など）には可搬な保存/復元 API が無い。従来の挙動のまま。
    noInterrupts();
#endif
    // 下の拡張が一貫した値を 1 つ見るよう、クリティカルセクション内で millis() を読む。
    raw = millis();
    uint64_t prev = s_last;
    uint32_t prev_low = static_cast<uint32_t>(prev);
    uint64_t high = prev & 0xFFFFFFFF00000000ULL;
    if (raw < prev_low) {
        high += (1ULL << 32);
    }
    uint64_t current = high | raw;
    s_last = current;
#if defined(__AVR__)
    SREG = irq_state;
#elif defined(__arm__)
    __asm__ volatile("msr primask, %0" :: "r"(irq_state) : "memory");
#else
    interrupts();
#endif
    return current;
#else
    auto now = std::chrono::steady_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch()
    ).count();
    return static_cast<uint64_t>(ms);
#endif
}

} // namespace internal
} // namespace azaraC
