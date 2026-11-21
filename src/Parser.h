#pragma once

#include "Message.h"
#include "IFramer.h"
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

#if AZARAC_ENABLE_NANKAI
struct NankaiEventKey {
    uint8_t info_code = 0;
    uint8_t report_month = 0;
    uint8_t report_day = 0;
    uint8_t report_hour = 0;
    uint8_t report_minute = 0;
    uint8_t information_type = 0;
    uint8_t report_classification = 0;
};

struct NankaiProgress {
    uint8_t received_count = 0;
    uint8_t total_pages = 0;
    uint8_t original_total_pages = 0;
    bool truncated = false;

    bool isComplete() const { return total_pages != 0 && received_count == total_pages; }
};
#endif

// RAM: Parser 実体は静的確保で約 6.6 KB（実測 6,624 B。既定: dedup 4 KB + Nankai 2×1,160 B + framer/decoder）、推奨 7.0 KB。
// dedup/Nankai 有効時は 64 bit epoch guard 用に 8 B を追加する（両方無効ならメンバ自体が存在しない）。
// AVR preset（Nankai/DCX off、dedup 64x8）では約 0.7 KB。2 KB SRAM のターゲットでは Nankai/DCX を無効のままにすること。
// スタック上限: feed() が host -Os で 808 B / AVR preset で 259 B。JSON 出力は別チェーン（host 1,600 B）。
// AZARAC_DEDUP_SLOTS を AVR preset の 64 未満へ縮めるのは、再通知を実測し直す場合のみ（azaraC_config.h）。
class Parser {
public:
    Parser() = default;
    // カスタムフレーマ（Sony、Furuno 等）を注入する。オブジェクトの所有は呼び出し側。
    explicit Parser(IFramer& framer) : _custom(&framer) {}

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

    // data を先頭から feed(byte) し、電文が 1 通成立した時点で止める。戻り値は消費したバイト数（0..len）。
    // 戻ったとき out.valid が true なら、消費した最後のバイトで電文が成立している（false なら out は未定義）。
    // 残り（data + 戻り値, len - 戻り値）を渡し直せば、複数の電文を取りこぼさずに順に受け取れる。
    // data が nullptr なら 0 を返す。
    size_t feedUntilMessage(const uint8_t* data, size_t len, Message& out, uint32_t report_unix = 0);

    // data の len バイトをすべて feed(byte) する（通信バッファをそのまま流す用途）。
    // 1 通以上成立すれば true で、out には最後に成立した電文が残る（後続の重複や他 MT のフレームでは消えない）。
    // 途中で成立した電文は上書きされるので、取りこぼしたくないときは feedUntilMessage() を使うこと。
    // 南海トラフ集約の aggregated_text_ptr は、同じ呼び出しの後続フレームで借用先が再利用されると無効になり得る。
    // 戻り値の契約は feed(byte) と同じ（false のとき out は未定義）。
    bool feed(const uint8_t* data, size_t len, Message& out, uint32_t report_unix = 0);

    void reset();

    // 受信が無い間も 64 bit 時計を観測する。loop() から定期的に呼ぶことで、
    // 2^32 ms（約 49.7 日）以上の空白でも折り返しを検出して dedup/Nankai 履歴を捨てられる。
    // dedup/Nankai が両方無効な構成では何もしない。ESP32 の getMillis() は 64 bit 源なので必須ではない。
    void updateClock();

#if AZARAC_ENABLE_NANKAI
    // 保持中の集約の進捗をコピーする。鍵が見つからなければ false を返し、out は変更しない。
    bool getNankaiProgress(const NankaiEventKey& key, NankaiProgress& out) const;
#endif

private:
    internal::UbxFramer              _ubx;
    internal::NmeaFramer             _nmea;
    internal::Decoder                _decoder;
    internal::DedupFilter            _dedup;
#if AZARAC_ENABLE_NANKAI
    internal::NankaiPageBufferManager _nankaiBuffers;
#endif
    IFramer*                         _custom = nullptr;
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

    // 世代・後退の epoch guard を適用し、丸めた現在時刻を返す。postDecodeAt と updateClock で共有する。
    uint64_t observeClock(uint64_t now_ms64);

    // テストから時刻を注入するための実体。postDecode は getMillis() を渡すだけ。
    bool postDecodeAt(const Message& decoded, Message& out, uint32_t identity, uint64_t now_ms64);

    // decode → postDecode を `out` 自体に対して行う。decode() が先に out をクリアするため、復号失敗で前の payload が残らない。
    // frame が非 const なのは messageIdentity が MT=44 の SD を一時的にゼロにするため。
    bool handleFrame(Frame& frame, Message& out, uint32_t report_unix);

#if AZARAC_ENABLE_NANKAI
    // Nankai のページ集約。Complete のときだけ out を出力用に設定する。
    // DuplicateComplete は完成済みイベントの再送で、呼び出し側が dedup 履歴だけ更新する。
    internal::NankaiAggregateResult processNankaiAggregation(
        const Message& decoded, Message& out, const Mt43Data* d, uint64_t current_ms);
#endif
};


} // namespace azaraC
