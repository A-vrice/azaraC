#pragma once
// Compile-time configuration macros. Separated from azaraC.h so definition files can include only these macros.

// language selection macros
#ifndef AZARAC_LANG_JA
#define AZARAC_LANG_JA 1
#endif

#ifndef AZARAC_LANG_EN
#define AZARAC_LANG_EN 0
#endif

// disaster category control macros
// (AVR preset below applies defaults before these, so #ifndef works in both.)

// AVR/resource-constrained presets: reduced buffer sizes and categories.
// Placed before the normal defaults so #ifndef in both sections works: a user -D override wins (both sections skip); AVR sets reduced values;
// non-AVR falls through to the normal defaults.
#if defined(__AVR__)
#ifndef AZARAC_NANKAI_MAX_PAGES
#define AZARAC_NANKAI_MAX_PAGES 4
#endif
#ifndef AZARAC_NANKAI_BUFFERS
#define AZARAC_NANKAI_BUFFERS 1
#endif
#ifndef AZARAC_DEDUP_SLOTS
// 64 slots (8 sets x 8 ways) = 512 B. Measured on the AVR categories (dc=3 震度, dc=5 津波, 8,669 frames / 77 distinct MT～VN): 64x8 re-announces 0 informations, 32x8 (256 B) also 0, 16x8 (128 B) 93. 32x8 is the measured floor, but 64x8 is what 512 B of an Uno's 2 KB SRAM buys. Do not drop below 32.
#define AZARAC_DEDUP_SLOTS 64
#endif
#ifndef AZARAC_DEDUP_WAYS
#define AZARAC_DEDUP_WAYS 8
#endif
#ifndef AZARAC_FLASH_BUF_SIZE
// Shared definition-lookup buffer (see internal/FlashString.h).
// AVR default (SEISMIC/TSUNAMI) longest label 30 B → 64 leaves headroom;
// DCX/CAMF adds far longer labels (a4_hazard_definition: 683 B) → 800 B.
// Categories are ordered by longest label; add longer ones to this cascade.
#if defined(AZARAC_ENABLE_DCX_CAMF) && AZARAC_ENABLE_DCX_CAMF
#define AZARAC_FLASH_BUF_SIZE 800
#elif defined(AZARAC_ENABLE_NANKAI) && AZARAC_ENABLE_NANKAI
// NANKAI info-code longest label is 509 B ("調査中B"); 540 leaves headroom.
#define AZARAC_FLASH_BUF_SIZE 540
#elif defined(AZARAC_ENABLE_NW_PAC_TSUNAMI) && AZARAC_ENABLE_NW_PAC_TSUNAMI
// NW-PAC longest label is 72 B (English tsunamigenic potential); 80 leaves headroom.
#define AZARAC_FLASH_BUF_SIZE 80
#else
#define AZARAC_FLASH_BUF_SIZE 64
#endif
#endif
// AVR has only 32KB Flash: large definitions (EX1 ~41KB, local gov ~38KB) exceed a single PROGMEM array limit, so only SEISMIC/TSUNAMI are enabled.
// Override before including if you need others (requires more flash).
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
#define AZARAC_ENABLE_DCX_CAMF 0
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
// Associativity of the dedup table: WAYS entries per set. Larger = more tolerance to hash collisions (fewer false "new" for a still-live information), smaller = cheaper per decision. AZARAC_DEDUP_SLOTS must divide evenly.
#ifndef AZARAC_DEDUP_WAYS
#define AZARAC_DEDUP_WAYS 8
#endif
// 512 slots (64 sets x 8 ways) = 4 KB. A receiver must keep every information still inside its validity window: 津波警報 stays live for 24 h and 気象 can carry several informations at once, so the live set is hundreds of entries.
// Measured with the shipping DedupFilter over 30 QZSS archive days of 2024 (`make -C test dedup-realday`): peak informations live at once ranged 20..327 (median 66), and the worst day (2024-08-28, 327 live) still re-announces on 256 slots. 512 was the measured floor; one quiet day alone suggests 128 is enough — it is not. MISSED (a live alert suppressed) was 0 on every day and at every capacity.
#ifndef AZARAC_DEDUP_SLOTS
#define AZARAC_DEDUP_SLOTS 512
#endif

// Fallback validity window of one information, in milliseconds: an information not received again within its window stops counting as a duplicate (アプリケーションノートv2 原PDF p.25 手順④'). The per-category table of 配信終了条件 (p.26-27: 緊急地震速報 5分 / 震源・震度 2時間 / 津波 最大24時間 / 降灰 最大1時間 / 台風 3時間 …) and MT=44 の A8 由来の窓 live in internal/DedupWindow.h; this value is used only for categories missing from that table (未割当・予約の災害種別、payload 未設定). 24 h is the longest window in the spec, so an unlisted category is never re-announced while it is still live.
#ifndef AZARAC_DEDUP_WINDOW_MS
#define AZARAC_DEDUP_WINDOW_MS 86400000UL  // 24 h
#endif

// Nankai Trough page buffer config
// 63 = 仕様最大ページ数（Pn/Pm は 6bit、1-63）。既定でページ打ち切りが構造的に発生しないようにする。縮小する場合の目安: 実観測の最大は 27。
// 1 = 南海トラフは 1 電文として連続放送され、複数イベントが同時並行しない。
// 複数イベントを同時追跡する場合のみ増やす（RAM はバッファ数に比例）。
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
// Usage: const char s[] AZARAC_PROGMEM = "...";
#ifdef __AVR__
#include <avr/pgmspace.h>
#define AZARAC_PROGMEM PROGMEM
#define AZARAC_PGM_READ_BYTE(addr)    pgm_read_byte(addr)
#define AZARAC_PGM_READ_WORD(addr)    pgm_read_word(addr)
#define AZARAC_PGM_READ_DWORD(addr)   pgm_read_dword(addr)
#define AZARAC_PGM_READ_PTR(addr)     pgm_read_ptr(addr)
#define AZARAC_STRCPY_P(dst, src)     strcpy_P(dst, src)
#else
#define AZARAC_PROGMEM
#define AZARAC_PGM_READ_BYTE(addr)    (*(addr))
#define AZARAC_PGM_READ_WORD(addr)    (*(addr))
#define AZARAC_PGM_READ_DWORD(addr)   (*(addr))
#define AZARAC_PGM_READ_PTR(addr)     (*(addr))
#define AZARAC_STRCPY_P(dst, src)     strcpy(dst, src)
#endif
