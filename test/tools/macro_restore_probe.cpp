#if AZARAC_TEST_CORE_MACROS
#define abs(x) ((x) + 100)
#define min(a, b) ((a) + (b) + 1000)
#define max(a, b) ((a) - (b) + 2000)
#endif

#include "azaraC.h"

#if AZARAC_TEST_CORE_MACROS
#if !defined(abs) || !defined(min) || !defined(max)
#error "Arduino macros must be restored"
#endif
static_assert(abs(-7) == 93);
static_assert(min(2, 3) == 1005);
static_assert(max(2, 3) == 1999);
#elif defined(abs) || defined(min) || defined(max)
#error "Arduino macros must remain undefined"
#endif
