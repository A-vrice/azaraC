#include "internal/TimeFields.h"
#include <cstdint>

uint64_t readMillisFromOtherTU() {
    return azaraC::internal::getMillis();
}
