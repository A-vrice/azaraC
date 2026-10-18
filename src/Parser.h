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
// RAM: Parser obj ~5.4 KB (static, default: Nankai 1-buffer @63 pages = 1,168 B manager + dedup table 4,096 B (512x8) + framers/decoder; host-measured sizeof = 5,464 B). ~5.8 KB recommended; min 712 B (AVR preset: 4 pages / 1 buffer, dedup 64x8 = 512 B, Nankai/DCX off). For 2 KB targets keep Nankai/DCX disabled; do not shrink AZARAC_DEDUP_SLOTS below the AVR preset's 64 without re-measuring (see azaraC_config.h for the measured error rates).
// Stack: feed() の worst-case 静的チェーンは host -Os で 808 B、AVR preset (atmega328p -Os, DCX/Nankai off) で 259 B。
// 以前は復号先に局所 Message を持っていたため host 1,112 B / AVR preset 414 B だった（frame あたり Message 288 B + そのコピー。今は out へ直接デコードする）。
// 値は -fstack-usage + -fcallgraph-info=su で call graph の最大経路を合計した上限（経路はフレーム内容依存）。JSON 出力側は別チェーン（JsonSerializer::serialize 系、host -Os で 1,600 B 上限）。
//
class Parser {
public:
    Parser() = default;
    // Custom framer (e.g. Sony, Furuno) — caller owns the object
    explicit Parser(internal::IFramer& framer) : _custom(&framer) {}

    // コピー/ムーブ禁止。Parser は 4 KB の dedup テーブルと Nankai バッファを実体で持ち、
    // _custom はユーザー所有の framer を指す。複製は SRAM を二重に食ううえ
    // framer を二重所有させるので、コンパイル時に落とす。
    Parser(const Parser&) = delete;
    Parser& operator=(const Parser&) = delete;
    Parser(Parser&&) = delete;
    Parser& operator=(Parser&&) = delete;

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
    // identity: 手順③ の照合対象（MT～VN = フレーム bit 8..219）の digest。
    // decoded と out は同一オブジェクトでもよい（handleFrame は常にそう渡す）。その場合はコピーしない。
    bool postDecode(const Message& decoded, Message& out, uint32_t identity);

    // Shared decode → postDecode path。デコード先は `out` そのもの:
    // decode() が冒頭で out.clear() するので、失敗時に再使用中の Message が前の payload を残すことはない。
    // frame は非 const: messageIdentity が MT=44 の SD を一時的にゼロにする（呼び出しの前後で内容は不変）。
    bool handleFrame(internal::Frame& frame, Message& out, uint32_t report_unix);

#if AZARAC_ENABLE_NANKAI
    // Process Nankai Trough page aggregation
    // Returns true if message should be output (page aggregation complete or not Nankai)
    bool processNankaiAggregation(const Message& decoded, Message& out, const Mt43Data* d, uint64_t current_ms);
#endif
};


} // namespace azaraC
