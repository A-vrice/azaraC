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

// RAM: Parser 実体は約 5.4 KB（静的、既定: Nankai 1 バッファ @63 ページ = 管理部 1,168 B + dedup 4,096 B (512x8) + framer/decoder。ホスト実測 sizeof = 5,464 B）。推奨は約 5.8 KB、最小 712 B（AVR preset: 4 ページ / 1 バッファ、dedup 64x8 = 512 B、Nankai/DCX off）。
// 2 KB のターゲットでは Nankai/DCX を無効のままにすること。
// AZARAC_DEDUP_SLOTS を AVR preset の 64 未満へ縮めるのは、実測し直す場合のみ（azaraC_config.h の実測値参照）。
// スタック: feed() の最悪ケースの静的チェーンは host -Os で 808 B、AVR preset (atmega328p -Os, DCX/Nankai off) で 259 B。
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
    // report_unix: 時刻解決に使う報告の UNIX epoch（0 = 未解決: DHM フィールドは保持し、unix_time は 0 のまま）
    bool feed(uint8_t byte, Message& out, uint32_t report_unix = 0);

    void reset();

#if AZARAC_ENABLE_NANKAI
    // 鍵に一致するバッファ（= Nankai のページ集約が完了している）を返す。無ければ nullptr。
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

    // 復号後の共通経路（カスタムフレーマ経路と AUTO 経路）: Nankai 集約 → dedup → out へのコピー。出力すべきなら true（妥当・非重複・集約済み）。
    // identity: 手順③ の照合範囲（MT～VN）の digest で、ビット範囲と除外対象は呼び出し側に記す。decoded と out は同一オブジェクトでもよく、その場合はコピーしない。
    bool postDecode(const Message& decoded, Message& out, uint32_t identity);

    // decode → postDecode の共通経路で、`out` 自体へ復号する: decode() が先に out をクリアするため、復号失敗で以前の payload が残らない。frame は非 const（messageIdentity が MT=44 の SD を一時的にゼロにする）。
    bool handleFrame(internal::Frame& frame, Message& out, uint32_t report_unix);

#if AZARAC_ENABLE_NANKAI
    // Nankai のページ集約。出力すべきなら true（集約完了、または Nankai 以外）
    bool processNankaiAggregation(const Message& decoded, Message& out, const Mt43Data* d, uint64_t current_ms);
#endif
};


} // namespace azaraC
