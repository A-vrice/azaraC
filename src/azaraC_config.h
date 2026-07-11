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

// ---- Nankai Trough page buffer config ----------------------------------------
#ifndef AZARAC_NANKAI_MAX_PAGES
#define AZARAC_NANKAI_MAX_PAGES 12
#endif
#ifndef AZARAC_NANKAI_AGGREGATED_TEXT_SIZE
#define AZARAC_NANKAI_AGGREGATED_TEXT_SIZE 217
#endif
#ifndef AZARAC_NANKAI_BUFFERS
#define AZARAC_NANKAI_BUFFERS 4
#endif
