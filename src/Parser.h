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

// RAM: Parser obj ~5.4 KB (static, default: Nankai 1-buffer @63 pages = 1,168 B manager + dedup 4,096 B (512x8) + framers/decoder; host-measured sizeof = 5,464 B), ~5.8 KB recommended; min 712 B (AVR preset: 4 pages / 1 buffer, dedup 64x8 = 512 B, Nankai/DCX off).
// For 2 KB targets keep Nankai/DCX disabled.
// Do not shrink AZARAC_DEDUP_SLOTS below the AVR preset's 64 without re-measuring (azaraC_config.h の実測値参照)。
// Stack: feed() の worst-case 静的チェーンは host -Os で 808 B、AVR preset (atmega328p -Os, DCX/Nankai off) で 259 B。
// 値は -fstack-usage + -fcallgraph-info=su で call graph の最大経路を合計した上限（経路はフレーム内容依存）。
// JSON 出力側は別チェーン（JsonSerializer::serialize 系、host -Os で 1,600 B 上限）。
class Parser {
public:
    Parser() = default;
    // Custom framer (e.g. Sony, Furuno) — caller owns the object
    explicit Parser(internal::IFramer& framer) : _custom(&framer) {}

    // コピー/ムーブ禁止: 実体で持つ 4 KB の dedup テーブルと Nankai バッファを二重に食い、_custom （ユーザー所有の framer を指す）も二重に指すため、コンパイル時に落とす。
    Parser(const Parser&) = delete;
    Parser& operator=(const Parser&) = delete;
    Parser(Parser&&) = delete;
    Parser& operator=(Parser&&) = delete;

    // Feed one byte. Returns true when a new, non-duplicate, valid message is in `out`.
    // report_unix: UNIX epoch of the report for time resolution (0 = use fixed baseline 2024-01-01)
    bool feed(uint8_t byte, Message& out, uint32_t report_unix = 0);

    void reset();

#if AZARAC_ENABLE_NANKAI
    // Returns the buffer matching the key (i.e. Nankai page aggregation is complete), or nullptr if not found.
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

    // Common post-decode path (custom-framer and AUTO routes): Nankai aggregation → dedup → copy to out; returns true if the message should be output (valid, non-duplicate, aggregation handled). identity: digest of the 手順③ comparison span (MT～VN); the bits and exclusions are noted at the call site. decoded and out may be the same object — then nothing is copied.
    bool postDecode(const Message& decoded, Message& out, uint32_t identity);

    // Shared decode → postDecode path, decoding into `out` itself: decode() clears out first, so a failed decode never leaves a previous payload behind. frame is non-const (messageIdentity zeroes MT=44's SD temporarily).
    bool handleFrame(internal::Frame& frame, Message& out, uint32_t report_unix);

#if AZARAC_ENABLE_NANKAI
    // Nankai page aggregation; returns true if the message should be output (aggregation complete, or not Nankai)
    bool processNankaiAggregation(const Message& decoded, Message& out, const Mt43Data* d, uint64_t current_ms);
#endif
};


} // namespace azaraC
