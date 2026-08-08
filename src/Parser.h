#pragma once
// azaraC - src/Parser.h

#include "Message.h"
#include "framer/IFramer.h"
#include "framer/UbxFramer.h"
#include "framer/NmeaFramer.h"
#include "decoder/Decoder.h"
#include "internal/Dedup.h"
#if AZARAC_ENABLE_NANKAI
#include "internal/NankaiPageBuffer.h"
#endif

namespace azaraC {

//
// Minimum RAM requirements:
//   - Parser object: ~1.3 KB total (static, with default Nankai 4-buffer config):
//       ~992 B NankaiPageBufferManager (4 × 248 B, configurable via AZARAC_NANKAI_BUFFERS)
//       + framers, decoder, dedup (~320 B)
//   - Stack per feed(): ~220 B (Message ~190B + Frame ~34B)
//   - Total: ~1.5 KB recommended for full config
//   - Minimal: ~650 B (Nankai 1 buffer) + framers/decoder/dedup = ~970 B
//   - For 2 KB targets (Arduino Uno): disable DCX and Nankai entirely
//
class Parser {
public:
    Parser() = default;
    // Custom framer (e.g. Sony, Furuno) — caller owns the object
    explicit Parser(internal::IFramer& framer) : _custom(&framer) {}

    // Feed one byte. Returns true when a new, non-duplicate, valid message is in `out`.
    // report_unix: UNIX epoch of the report for time resolution (0 = use fixed baseline 2024-01-01)
    bool feed(uint8_t byte, Message& out, uint32_t report_unix = 0);

    void reset();

#if AZARAC_ENABLE_NANKAI
    // Check if Nankai Trough page aggregation is complete for given key
    // Returns pointer to the buffer matching the key, or nullptr if not found
    const internal::NankaiPageBuffer* getNankaiBuffer(const internal::NankaiPageKey& key) const;
#endif

private:
    internal::UbxFramer              _ubx;
    internal::NmeaFramer             _nmea;
    internal::Decoder                _decoder;
    internal::DedupFilter            _dedup;
#if AZARAC_ENABLE_NANKAI
    internal::NankaiPageBufferManager _nankaiBuffers;
#endif
    internal::IFramer*               _custom = nullptr;

    // Common post-decode handler: Nankai aggregation → dedup → copy to out.
    // Extracted to eliminate duplication between custom framer and AUTO mode paths.
    // Returns true if message should be output (valid, non-duplicate, aggregation handled).
    bool postDecode(const Message& decoded, Message& out);

#if AZARAC_ENABLE_NANKAI
    // Process Nankai Trough page aggregation
    // Returns true if message should be output (page aggregation complete or not Nankai)
    bool processNankaiAggregation(const Message& decoded, Message& out, const Mt43Data* d, uint64_t current_ms);
#endif
};


} // namespace azaraC
