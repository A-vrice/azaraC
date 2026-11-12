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

namespace internal {
struct ParserTestHook;
} // namespace internal

// RAM: Parser 実体は静的確保で約 5.4 KB（既定: dedup 4 KB + Nankai 管理部 1.2 KB + framer/decoder）、推奨 5.8 KB。
// dedup/Nankai 有効時は 64 bit epoch guard 用に 8 B を追加する（両方無効ならメンバ自体が存在しない）。
// AVR preset（Nankai/DCX off、dedup 64x8）では約 0.7 KB。2 KB SRAM のターゲットでは Nankai/DCX を無効のままにすること。
// スタック上限: feed() が host -Os で 808 B / AVR preset で 259 B。JSON 出力は別チェーン（host 1,600 B）。
// AZARAC_DEDUP_SLOTS を AVR preset の 64 未満へ縮めるのは、再通知を実測し直す場合のみ（azaraC_config.h）。
class Parser {
public:
    Parser() = default;
    // カスタムフレーマ（Sony、Furuno 等）を注入する。オブジェクトの所有は呼び出し側。
    explicit Parser(internal::IFramer& framer) : _custom(&framer) {}

    // コピー/ムーブ禁止: dedup テーブル 4 KB と Nankai バッファを二重に確保し、_custom（ユーザー所有のフレーマ）も二重参照になるため。
    Parser(const Parser&) = delete;
    Parser& operator=(const Parser&) = delete;
    Parser(Parser&&) = delete;
    Parser& operator=(Parser&&) = delete;

    // 1 バイト入力し、新規かつ妥当な電文が `out` に揃えば true。
    // `out` をメッセージとして読めるのは true のときだけ。false のときの内容は未定義で、直前の値や復号途中のフィールドが残り得る。
    // 例外は診断用の `unsupported_reason` で、復号器が完成フレームを拒否した場合に理由が入る（それ以外の false では保証しない）。
    // report_unix: 時刻解決に使う報告の UNIX epoch。0 は未解決（DHM フィールドは残るが unix_time は 0 のまま）。
    bool feed(uint8_t byte, Message& out, uint32_t report_unix = 0);

    void reset();

#if AZARAC_ENABLE_NANKAI
    // 鍵に一致するバッファを返す（受信途中でも返る。完了判定は isComplete()）。無ければ nullptr。
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
#if defined(AZARAC_TESTING) && AZARAC_TESTING
    friend struct internal::ParserTestHook;
#endif
    // 32 bit 時刻の一周以上を検出するための最終観測時刻。DedupFilter/NankaiPageBuffer の
    // last_seen は RAM 削減のため 32 bit のままで、通常の折り返しは符号なし差分で扱える。
#if AZARAC_ENABLE_DEDUP || AZARAC_ENABLE_NANKAI
    uint64_t                         _last_now_ms = 0;
#endif

    // 復号後の共通経路（カスタムフレーマ経路と AUTO 経路）: Nankai 集約 → dedup → out へのコピー。
    // 妥当・非重複・集約済みで出力すべきなら true。
    // identity: 手順③ の照合範囲（MT～VN）の digest。ビット範囲と除外対象は呼び出し側に記す。
    // decoded と out が同一オブジェクトならコピーは行わない。
    bool postDecode(const Message& decoded, Message& out, uint32_t identity);

    // テストから時刻を注入するための実体。postDecode は getMillis() を渡すだけ。
    bool postDecodeAt(const Message& decoded, Message& out, uint32_t identity, uint64_t now_ms64);

    // decode → postDecode を `out` 自体に対して行う。decode() が先に out をクリアするため、復号失敗で前の payload が残らない。
    // frame が非 const なのは messageIdentity が MT=44 の SD を一時的にゼロにするため。
    bool handleFrame(internal::Frame& frame, Message& out, uint32_t report_unix);

#if AZARAC_ENABLE_NANKAI
    // Nankai のページ集約。Complete のときだけ out を出力用に設定する。
    // DuplicateComplete は完成済みイベントの再送で、呼び出し側が dedup 履歴だけ更新する。
    internal::NankaiAggregateResult processNankaiAggregation(
        const Message& decoded, Message& out, const Mt43Data* d, uint64_t current_ms);
#endif
};


} // namespace azaraC
