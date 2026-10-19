#pragma once
// Compile-time configuration macros. Separated from azaraC.h so definition files can include only these macros.

// language selection macros
#ifndef AZARAC_LANG_JA
#define AZARAC_LANG_JA 1
#endif

#ifndef AZARAC_LANG_EN
#define AZARAC_LANG_EN 0
#endif

// disaster category control macros (the AVR preset below applies defaults before these, so #ifndef works in both.)

// AVR/resource-constrained presets: reduced buffer sizes and categories.
// Placed before the normal defaults so #ifndef works in both sections — a user -D override wins (both sections skip), AVR sets the reduced values, and non-AVR falls through to the normal defaults.
#if defined(__AVR__)
#ifndef AZARAC_NANKAI_MAX_PAGES
#define AZARAC_NANKAI_MAX_PAGES 4
#endif
#ifndef AZARAC_NANKAI_BUFFERS
#define AZARAC_NANKAI_BUFFERS 1
#endif
#ifndef AZARAC_DEDUP_SLOTS
// 64 slots (8 sets x 8 ways) = 512 B.
// Measured on the AVR categories (dc=3 震度, dc=5 津波, 8,669 frames / 77 distinct MT～VN): 64x8 re-announces 0 informations, 32x8 (256 B) also 0, 16x8 (128 B) 93 — 32x8 is the measured floor, but 64x8 is what 512 B of an Uno's 2 KB SRAM buys.
// Do not drop below 32.
#define AZARAC_DEDUP_SLOTS 64
#endif
#ifndef AZARAC_DEDUP_WAYS
#define AZARAC_DEDUP_WAYS 8
#endif
#ifndef AZARAC_DEDUP_MT44_MAX_WINDOW_MS
// MT=44 (DCX/CAMF) の窓の上限。
// ホストは A8-Hazard Duration の上限（6 時間〜7 日、internal/DedupWindow.h）を使うが、AVR の 64 スロットでは 7 日の窓が「まだ生きている情報」の枠を長く占め、押し出しによる再通知を招く。
// MT44 の再送は同じ電文が 2 回（まれに 3〜4 回）・間隔は最大 16 秒（issue #34 の実測）なので 5 分で足りる。
// A8 の窓は最短でも 6 時間なので常に効く。
#define AZARAC_DEDUP_MT44_MAX_WINDOW_MS 300000UL  // 5 min
#endif
// DCX/CAMF's tables alone are ~100 KB and its decoder ~20 KB on top, so it only fits a 256 KB part (ATmega2560, DCX/CAMF + SEISMIC/TSUNAMI, JA: 144,804 B image — see test/bench/avr).
// Nothing is switched on by the chip name: every AVR part starts at SEISMIC/TSUNAMI, the Uno's set, and the user opts in with build flags — -DAZARAC_AVR_LARGE_FLASH=1 (the name this preset was built around) or -DAZARAC_ENABLE_DCX_CAMF=1. The library is a separate translation unit, so a #define placed in the sketch does not reach it.
// Tables above 64 KiB also need the far Flash addressing in internal/FlashString.h, which such devices select automatically (FLASHEND > 0xFFFF).
// The remaining families stay off by default even on large parts (all of them at once is ~242 KiB); enable them the same way (-DAZARAC_ENABLE_EEW=1 …) as needed.
#if !defined(AZARAC_AVR_LARGE_FLASH)
#define AZARAC_AVR_LARGE_FLASH 0
#endif
#ifndef AZARAC_ENABLE_EEW
#define AZARAC_ENABLE_EEW 0
#endif
#ifndef AZARAC_ENABLE_HYPOCENTER
#define AZARAC_ENABLE_HYPOCENTER 0
#endif
#ifndef AZARAC_ENABLE_SEISMIC
#define AZARAC_ENABLE_SEISMIC 1
#endif
#ifndef AZARAC_ENABLE_NANKAI
#define AZARAC_ENABLE_NANKAI 0
#endif
#ifndef AZARAC_ENABLE_TSUNAMI
#define AZARAC_ENABLE_TSUNAMI 1
#endif
#ifndef AZARAC_ENABLE_NW_PAC_TSUNAMI
#define AZARAC_ENABLE_NW_PAC_TSUNAMI 0
#endif
#ifndef AZARAC_ENABLE_VOLCANO
#define AZARAC_ENABLE_VOLCANO 0
#endif
#ifndef AZARAC_ENABLE_ASH_FALL
#define AZARAC_ENABLE_ASH_FALL 0
#endif
#ifndef AZARAC_ENABLE_WEATHER
#define AZARAC_ENABLE_WEATHER 0
#endif
#ifndef AZARAC_ENABLE_FLOOD
#define AZARAC_ENABLE_FLOOD 0
#endif
#ifndef AZARAC_ENABLE_TYPHOON
#define AZARAC_ENABLE_TYPHOON 0
#endif
#ifndef AZARAC_ENABLE_MARINE
#define AZARAC_ENABLE_MARINE 0
#endif
#ifndef AZARAC_ENABLE_DCX_CAMF
#define AZARAC_ENABLE_DCX_CAMF AZARAC_AVR_LARGE_FLASH
#endif

// Shared definition-lookup buffer (see internal/FlashString.h).
// Must come after the categories above so a preset (not only a user -D) selects the size, and it must cover the longest label of every category the *labels* can come from: the tables are enabled by their own guards, not by this chain, so a category missing here silently truncates its labels (azarac_pgm_view clamps at AZARAC_FLASH_BUF_SIZE - 1, mid-UTF-8).
// Ordered by longest label; `test/bench/avr/check_flash_buf.py` sweeps every category combination against this chain and fails on a short buffer (run by `make -C test bench`) — add a branch whenever it complains.
#ifndef AZARAC_FLASH_BUF_SIZE
#if AZARAC_ENABLE_DCX_CAMF
// DCX/CAMF adds far longer labels (a4_hazard_definition: 683 B) → 800 B.
#define AZARAC_FLASH_BUF_SIZE 800
#elif AZARAC_ENABLE_EEW || AZARAC_ENABLE_HYPOCENTER
// longest is 596 B (notification_on_disaster_prevention, JA) / 515 B (EN).
#define AZARAC_FLASH_BUF_SIZE 640
#elif AZARAC_ENABLE_NANKAI
// NANKAI info-code longest label is 509 B ("調査中B"); 540 leaves headroom.
#define AZARAC_FLASH_BUF_SIZE 540
#elif AZARAC_ENABLE_VOLCANO || AZARAC_ENABLE_FLOOD
// 88 B (volcanic_warning_code, EN) and 78 B (flood_forecast_region, EN).
#define AZARAC_FLASH_BUF_SIZE 96
#elif AZARAC_ENABLE_NW_PAC_TSUNAMI
// NW-PAC longest label is 72 B (English tsunamigenic potential); 80 leaves headroom.
#define AZARAC_FLASH_BUF_SIZE 80
#else
// SEISMIC/TSUNAMI longest label is 45 B; WEATHER/TYPHOON/MARINE and the
// VOLCANO|ASH_FALL region table stay under 63 B, so 64 fits them too.
#define AZARAC_FLASH_BUF_SIZE 64
#endif
// The preset keeps an Uno at 64 B, so this only fires when long-label categories were enabled on top of it: the buffer has to grow for the labels to stay correct, and that is 2 KB of an Uno's SRAM.
// The user's call, hence a warning.
#if AZARAC_FLASH_BUF_SIZE > 256 && defined(ARDUINO_AVR_UNO)
#warning "AZARAC_FLASH_BUF_SIZE is large for the Uno's 2 KB SRAM — enable fewer categories, or shrink it knowing labels then truncate"
#endif
#endif
#endif // __AVR__

// normal defaults (non-AVR or overridden values)
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
#ifndef AZARAC_ENABLE_DCX_CAMF
#define AZARAC_ENABLE_DCX_CAMF 1
#endif

// duplicate suppression
// Associativity of the dedup table: WAYS entries per set.
// Larger = more tolerance to hash collisions (fewer false "new" for a still-live information), smaller = cheaper per decision.
// AZARAC_DEDUP_SLOTS must divide evenly.
#ifndef AZARAC_DEDUP_WAYS
#define AZARAC_DEDUP_WAYS 8
#endif
// 512 slots (64 sets x 8 ways) = 4 KB.
// A receiver must keep every information still inside its validity window: 津波警報 stays live for 24 h and 気象 can carry several informations at once, so the live set is hundreds of entries.
// Measured with the shipping DedupFilter over 30 QZSS archive days of 2024 (`make -C test dedup-realday`): peak informations live at once ranged 20..327 (median 66), and the worst day (2024-08-28, 327 live) still re-announces on 256 slots — 512 was the measured floor.
// One quiet day alone suggests 128; it is not.
// MISSED (a live alert suppressed) was 0 on every day and at every capacity.
#ifndef AZARAC_DEDUP_SLOTS
#define AZARAC_DEDUP_SLOTS 512
#endif

// Fallback validity window of one information, in milliseconds: an information not received again within its window stops counting as a duplicate (アプリケーションノートv2 原PDF p.25 手順④').
// The per-category table of 配信終了条件 (p.26-27: 緊急地震速報 5分 / 震源・震度 2時間 / 津波 最大24時間 / 降灰 最大1時間 / 台風 3時間…) and MT=44 の A8 由来の窓 live in internal/DedupWindow.h; this value is used only for categories missing from that table (未割当・予約の災害種別、payload 未設定). 24 h is the longest window in the spec, so an unlisted category is never re-announced while it is still live.
#ifndef AZARAC_DEDUP_WINDOW_MS
#define AZARAC_DEDUP_WINDOW_MS 86400000UL  // 24 h
#endif

// Nankai Trough page buffer config
// MAX_PAGES 63 = 仕様最大ページ数（Pn/Pm は 6bit、1-63）なので、既定ではページ打ち切りが構造的に起きない（縮小の目安: 実観測の最大は 27）。
// BUFFERS 1 = 南海トラフは 1 電文として連続放送され、複数イベントが同時並行しない。
// 増やすのは同時追跡時のみ（RAM はバッファ数に比例）。
#ifndef AZARAC_NANKAI_MAX_PAGES
#define AZARAC_NANKAI_MAX_PAGES 63
#endif
#ifndef AZARAC_NANKAI_BUFFERS
#define AZARAC_NANKAI_BUFFERS 1
#endif

#if AZARAC_NANKAI_BUFFERS > 2 && defined(ARDUINO_AVR_UNO)
#warning "Nankai buffers may exhaust SRAM on Arduino Uno. Consider AZARAC_NANKAI_BUFFERS=1"
#endif

// PROGMEM abstraction: stores const data in Flash on AVR (no-op on desktop).
// Usage: const char s[] AZARAC_PROGMEM = "..."; The AZARAC_PGM_READ_* / AZARAC_STRCPY_P helpers address Flash through a 16-bit progmem pointer, which only reaches the first 64 KiB of Flash.
// On a part with more Flash (ATmega2560 …) use avr-libc's far API (`pgm_get_far_address` + `pgm_read_*_far` / `memcpy_PF`) — that is what the definition tables do when FLASHEND > 0xFFFF (see internal/FlashString.h).
#ifdef __AVR__
#include <avr/pgmspace.h>
// Where the definition tables live. avr-libc's linker script puts every progmem-cluster input at the *start* of .text in input order, and the Arduino recipe links the core (core.a) last, so ~116 KiB of tables there (the large-flash preset) would push the core's own PROGMEM above 0xFFFF, where the core's 16-bit `pgm_read_byte(&digital_pin_to_port_PGM[pin])` cannot reach: pinMode/digitalWrite would read the wrong port (measured on a Mega 2560 image with the core stand-in in test/bench/avr — the core's table lands at 0x19F46, immediately after our tables).
// So the tables go to `.text.azaraC.<n>`: every avr-libc script places `*(.text.*)` after both the progmem cluster and the code, which leaves the core's tables low.
// Not `.progmemx.*` — that cluster only exists in scripts from binutils 2.29 on (PR 21849); the older atmel 2.26 script (Ubuntu's binutils-avr and the Arduino toolchain) has no `.progmemx.*` pattern and its broad `*(.progmem*)` swallows the name back into the low cluster, the very failure this avoids (measured 0x19F46 there too).
// Only parts that read Flash far need it, in which case the section's position is irrelevant; <= 64 KiB parts keep plain PROGMEM.
// The counter suffix keeps one section per declaration, like -fdata-sections does for `__progmem__` data: a shared section would be kept whole by --gc-sections as soon as one table in the translation unit is referenced, and a function-local static in an inline function is emitted one-only (weak), which cannot share a section with an ordinary array at all ("section type conflict").
#if FLASHEND > 0xFFFF && !defined(AZARAC_AVR_STUB)
#define AZARAC_PGM_STR_(x) #x
#define AZARAC_PGM_STR(x) AZARAC_PGM_STR_(x)
#define AZARAC_PROGMEM \
    __attribute__((__section__(".text.azaraC." AZARAC_PGM_STR(__COUNTER__))))
#else
#define AZARAC_PROGMEM PROGMEM
#endif
// Small constant tables read through a plain 16-bit Flash pointer (AZARAC_PGM_READ_*), not through the far accessors.
// `PROGMEM` puts them in the `*(.progmem*)` cluster at the front of .text, where the Arduino core's own tables live too, so a 16-bit pointer reaches them; `AZARAC_PROGMEM` would move them to `.text.azaraC.<n>`, which a >64 KiB image places above that window.
// autoresearch.sh gates both ends of this: the core's stand-in PROGMEM and azaraC's own near-Flash tables must stay below 0xFFFF in the large-flash link.
#define AZARAC_PROGMEM_NEAR PROGMEM
#define AZARAC_PGM_READ_BYTE(addr)    pgm_read_byte(addr)
#define AZARAC_PGM_READ_WORD(addr)    pgm_read_word(addr)
#define AZARAC_PGM_READ_DWORD(addr)   pgm_read_dword(addr)
#define AZARAC_PGM_READ_PTR(addr)     pgm_read_ptr(addr)
#define AZARAC_STRCPY_P(dst, src)     strcpy_P(dst, src)
#else
#define AZARAC_PROGMEM
#define AZARAC_PROGMEM_NEAR
#define AZARAC_PGM_READ_BYTE(addr)    (*(addr))
#define AZARAC_PGM_READ_WORD(addr)    (*(addr))
#define AZARAC_PGM_READ_DWORD(addr)   (*(addr))
#define AZARAC_PGM_READ_PTR(addr)     (*(addr))
#define AZARAC_STRCPY_P(dst, src)     strcpy(dst, src)
#endif
