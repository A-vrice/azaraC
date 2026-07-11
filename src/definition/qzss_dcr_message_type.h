#pragma once
// AUTO-GENERATED from azarashi 0.16.4 with CI-CD
// Source module : qzss_dcr_message_type
// Variable      : qzss_dcr_message_type
// Entries       : 2
// Strategy      : switch

// NOTE: This function may return nullptr for unknown IDs.
// Callers MUST perform a null-check before using the result.

#include <cstdint>
#include <optional>
#include <string_view>
#include "../azaraC_config.h"

namespace azaraC {
namespace def {

[[nodiscard]] inline constexpr const char* qzss_dcr_message_type_lookup(uint8_t id) noexcept {
    switch (id) {
        case 43: return "DCR";
        case 44: return "DCX";
        default: return nullptr;
    }
}

} // namespace def
} // namespace azaraC
