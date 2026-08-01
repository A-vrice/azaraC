#pragma once
// azaraC - src/azaraC_config.h
// Compile-time configuration macros.
// Separated from azaraC.h so that definition files can include only the
// configuration macros without pulling in the entire library.
//
// Optional compile-time overrides (define BEFORE including this header):
//   #define AZARAC_DEDUP_SLOTS 16   // default: 8
//   #define AZARAC_LANG_JA 0        // Enable Japanese labels (default: 1)
//   #define AZARAC_LANG_EN 1        // Enable English labels (default: 0)

// ---- language selection macros -----------------------------------------------
#ifndef AZARAC_LANG_JA
#define AZARAC_LANG_JA 1
#endif

#ifndef AZARAC_LANG_EN
#define AZARAC_LANG_EN 0
#endif

// ---- disaster category control macros ----------------------------------------
// (AVR defaults are applied in the platform preset below, BEFORE these
// normal defaults, so #ifndef in both sections works.)

// ---- platform presets (AVR / resource-constrained targets) --------------------
// These reduce default buffer sizes and definition categories when compiling
// for AVR.
// They come BEFORE the normal defaults so #ifndef in both sections works:
// user -D override → AVR section skips → normal section skips → user value used.
// no override → AVR section sets reduced value → normal section skips → AVR value used.
// no AVR → AVR section skipped → normal section uses normal default.
#if defined(__AVR__)
#ifndef AZARAC_NANKAI_MAX_PAGES
#define AZARAC_NANKAI_MAX_PAGES 4
#endif
#ifndef AZARAC_NANKAI_BUFFERS
#define AZARAC_NANKAI_BUFFERS 1
#endif
#ifndef AZARAC_DEDUP_SLOTS
#define AZARAC_DEDUP_SLOTS 4
#endif
#ifndef AZARAC_FLASH_BUF_SIZE
// Shared definition-lookup buffer (see internal/FlashString.h). With the
// AVR category preset (SEISMIC/TSUNAMI only) the longest label is 30 bytes;
// 64 leaves headroom. The full-category default is 800 (D20 ash-fall).
#define AZARAC_FLASH_BUF_SIZE 64
#endif
#ifndef AZARAC_DCX_USE_FLOAT
#define AZARAC_DCX_USE_FLOAT
#endif
// AVR (Arduino Uno etc.) has only 32KB Flash: the large definition pools
// (EX1 ~41KB, local government ~38KB, ...) exceed even a single PROGMEM
// array limit (32KB). Only the small categories (SEISMIC / TSUNAMI) are
// enabled by default. Override with -D or #define before including azaraC.h
// if you need other categories (requires more flash than the Uno provides).
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

// ---- normal defaults (non-AVR or overridden values) ---------------------------
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

// ---- duplicate suppression ----------------------------------------------------
#ifndef AZARAC_DEDUP_SLOTS
#define AZARAC_DEDUP_SLOTS 8
#endif

// ---- DCX coordinate precision -------------------------------------------------
// Use float (32-bit) instead of double (64-bit) for DCX coordinate storage.
// #define AZARAC_DCX_USE_FLOAT

// ---- Nankai Trough page buffer config ----------------------------------------
#ifndef AZARAC_NANKAI_MAX_PAGES
#define AZARAC_NANKAI_MAX_PAGES 12
#endif
// aggregated_text のサイズは MAX_PAGES から自動計算（1ページ 18 バイト + ヌル終端）
// ユーザが明示的に定義した場合はそれが優先される（#ifndef ガード）
#ifndef AZARAC_NANKAI_AGGREGATED_TEXT_SIZE
#define AZARAC_NANKAI_AGGREGATED_TEXT_SIZE (AZARAC_NANKAI_MAX_PAGES * 18 + 1)
#endif
#ifndef AZARAC_NANKAI_BUFFERS
#define AZARAC_NANKAI_BUFFERS 4
#endif

#if AZARAC_NANKAI_BUFFERS > 2 && defined(ARDUINO_AVR_UNO)
#warning "Nankai buffers may exhaust SRAM on Arduino Uno. Consider AZARAC_NANKAI_BUFFERS=1"
#endif

// ---- PROGMEM abstraction (AVR / embedded) ------------------------------------
// On AVR, const data is placed in RAM unless marked with PROGMEM.
// On desktop, PROGMEM is a no-op.
// These macros provide a portable way to store data in Flash on AVR.
// Usage: const char myString[] AZARAC_PROGMEM = "hello";
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
