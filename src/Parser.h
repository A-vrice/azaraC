#pragma once

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
// RAM: Parser obj ~1.4 KB (static, default Nankai 1-buffer @63 pages: 1168 B
// manager + 261 B framers/decoder/dedup; host-measured sizeof = 1432 B); stack per
// feed() ~330 B (Message 296B + Frame 33B, host-measured default config). ~1.7 KB
// recommended; min 232 B (AVR preset: Nankai/DCX off). For 2 KB targets keep
// Nankai/DCX disabled.
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

    // Shared decode → postDecode path; on decode failure copies the cleared
    // Decoder state into `out` so a reused Message never retains stale payload.
    bool handleFrame(const internal::Frame& frame, Message& out, uint32_t report_unix);

#if AZARAC_ENABLE_NANKAI
    // Process Nankai Trough page aggregation
    // Returns true if message should be output (page aggregation complete or not Nankai)
    bool processNankaiAggregation(const Message& decoded, Message& out, const Mt43Data* d, uint64_t current_ms);
#endif
};


} // namespace azaraC
