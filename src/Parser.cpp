#include "Parser.h"
#include "internal/DedupWindow.h"
#include "internal/TimeFields.h"

namespace azaraC {

#if AZARAC_ENABLE_DEDUP || AZARAC_ENABLE_NANKAI
namespace {
// FreeRTOS のマルチコアでは getMillis() が数 ms 逆行し得る。この範囲は受信順序の揺らぎとして
// 最終観測時刻に丸め、履歴を捨てない。これを超える後退は時計の再設定とみなして履歴を捨てる。
constexpr uint64_t kClockRollbackToleranceMs = 1000;
} // namespace
#endif

bool Parser::feed(uint8_t byte, Message& out, uint32_t report_unix) {
    internal::Frame frame;

    // カスタムフレーマ（排他モード）
    if (_custom) {
        // カスタムフレーマは全フィールドを埋めずに true を返し得る。
        // 決定的なゼロ基準を与えるが、このオプトイン経路に限る: 毎バイト 33 B をゼロ化すると、成功時に必ず Frame を埋める組み込みフレーマにコストが乗る。
        frame = internal::Frame{};
        if (!_custom->feed(byte, frame)) return false;
        return handleFrame(frame, out, report_unix);
    }

    // AUTO 常時: UBX優先試行（UBXはバイナリ、NMEAはASCIIで競合しない）
    bool ubx_ok = _ubx.feed(byte, frame);
    bool nmea_ok = ubx_ok ? false : _nmea.feed(byte, frame);
    if (!ubx_ok && !nmea_ok) return false;

    return handleFrame(frame, out, report_unix);
}

size_t Parser::feedUntilMessage(const uint8_t* data, size_t len, Message& out, uint32_t report_unix) {
    out.valid = false;
    if (!data) return 0;
    for (size_t i = 0; i < len; ++i) {
        // 1 バイト版と同じ経路（Nankai 集約・dedup を含む）。
        if (feed(data[i], out, report_unix)) return i + 1;
    }
    out.valid = false;   // 途中で完成して棄却されたフレームの値を成立と誤読させない
    return len;
}

bool Parser::feed(const uint8_t* data, size_t len, Message& out, uint32_t report_unix) {
    if (!data) return false;
    // 成立後のフレームの復号は out を clear() するので、作業用に分けて成立したものだけ out へ写す。
    Message scratch;
    bool any = false;
    while (len > 0) {
        const size_t n = feedUntilMessage(data, len, scratch, report_unix);
        if (scratch.valid) {
            out = scratch;
            any = true;
        }
        data += n;
        len -= n;
    }
    // 成立しなかったときも、復号器が完成フレームを断った理由は 1 バイト版と同じく out で読めるようにする。
    if (!any) out.unsupported_reason = scratch.unsupported_reason;
    return any;
}

bool Parser::handleFrame(internal::Frame& frame, Message& out, uint32_t report_unix) {
    if (!_decoder.decode(frame, out, report_unix)) {
        // 復号に失敗したフレームで valid だけ立った中途半端な Message を残さない。
        // decodeQzqsm() は valid=true を設定した後に oob_ で false を返す経路があるため、ここで落とす。
        // CRC 失敗時は Decoder が svid も 0 に戻すが、プリアンブル不一致や未知 MT の false では
        // frame 由来の svid が残る。契約どおり、呼び出し側は false のとき out を読まないこと。
        out.valid = false;
        return false;
    }
    // 手順③ の照合範囲は MT～VN（bit 8..219 = 212 bit、bit 220..225 は Reserved）。
    // プリアンブルと Reserved は放送で巡回し、受信衛星はフレームに無く NMEA/UBX ヘッダ由来なので鍵に含めない。
    // MT=44 の SD は事務局回答の照合範囲（MT および CAMF〜EM）に無く、Decoder::messageIdentity がゼロにしてから digest を取る。
    const uint32_t identity = internal::Decoder::messageIdentity(frame.bits);
    return postDecode(out, out, identity);   // decoded と out は同一（postDecode は aliasing 前提）
}

bool Parser::postDecode(const Message& decoded, Message& out, uint32_t identity) {
    return postDecodeAt(decoded, out, identity, internal::getMillis());
}

uint64_t Parser::observeClock(uint64_t now_ms64) {
#if AZARAC_ENABLE_DEDUP || AZARAC_ENABLE_NANKAI
    // dedup と Nankai 集約で共有する受信時刻（手順④'）。
    // 年齢が 2^32 ms（約 49.7 日）を超えると符号なし差分が巻き戻って新しく見えるため、世代（上位 32 bit）が変わったら履歴を捨てる。
    // 後退は許容量まで丸め、超えた場合も時計の再設定として履歴を捨てる。いずれも再通知を許容し、生きた警報の抑止を避ける。
    if (now_ms64 < _last_now_ms) {
        if (_last_now_ms - now_ms64 > kClockRollbackToleranceMs) {
            _dedup.reset();
#if AZARAC_ENABLE_NANKAI
            _nankaiBuffers.clearAll();
#endif
            // 時計の再設定。基準も低い方へ張り直す（丸めると新時刻が旧高値を追い越すまで凍結する）。
        } else {
            now_ms64 = _last_now_ms;   // 受信順序の揺らぎは丸める
        }
    } else if ((now_ms64 >> 32) != (_last_now_ms >> 32)) {
        // 世代（2^32 ms 境界）を跨いだ。経過が短くても古い履歴は巻き戻って見えるため捨てる。
        _dedup.reset();
#if AZARAC_ENABLE_NANKAI
        _nankaiBuffers.clearAll();
#endif
    }
    _last_now_ms = now_ms64;
#endif
    return now_ms64;
}

void Parser::updateClock() {
#if AZARAC_ENABLE_DEDUP || AZARAC_ENABLE_NANKAI
    (void)observeClock(internal::getMillis());
#endif
}

bool Parser::postDecodeAt(const Message& decoded, Message& out, uint32_t identity, uint64_t now_ms64) {
    now_ms64 = observeClock(now_ms64);
    const uint32_t now_ms = static_cast<uint32_t>(now_ms64);
    const uint32_t window_ms = internal::dedupWindowMs(decoded);

    // 南海トラフのページ集約
#if AZARAC_ENABLE_NANKAI
    if (decoded.payload_type == MsgPayloadType::Mt43) {
        const Mt43Data* mt43 = decoded.getMt43();
        const NankaiData* nankai = mt43 ? mt43->getNankai() : nullptr;
        if (mt43 && mt43->disaster_category == 4) {
            // getNankai() が無いのは電文として成立していない場合。集約できないので出力しない。
            if (!nankai) { out.clear(); return false; }
            // out が decoded と同一でも安全: Complete のとき processNankaiAggregation が上書きするのは
            // is_aggregated / aggregated_* / truncated / page / total_page だけ。
            // 直後に鍵として読む info_code と report_* は不変。
            const internal::NankaiAggregateResult aggregate = processNankaiAggregation(
                decoded, out, mt43, now_ms64);
            if (aggregate == internal::NankaiAggregateResult::Rejected ||
                aggregate == internal::NankaiAggregateResult::NotComplete) {
                out.clear();
                return false;
            }

            // 同一性は事象そのもの（info_code + 情報種別 + Rc + 報告時刻）。完成したページ集合の crc24 を鍵にすると、
            // 到着順で値が変わり同じ事象が再送のたびに別情報として通知される（鍵の内訳は NankaiPageKey 参照）。
            const internal::DedupKey key = internal::dedupEventKey(internal::dedupEventToken(
                nankai->info_code, mt43->information_type, nankai->report_month, nankai->report_day,
                nankai->report_hour, nankai->report_minute, mt43->report_classification));

            if (aggregate == internal::NankaiAggregateResult::DuplicateComplete) {
                // 完成済みイベントの再送。本文は再出力せず、dedup 履歴だけ更新する。
                // 未完成ページの重複ではここへ来ない（完成通知を抑止しないため）。
                (void)_dedup.isDuplicate(key, now_ms, window_ms);
                out.clear();
                return false;
            }

            if (_dedup.isDuplicate(key, now_ms, window_ms)) {
                out.clear();
                return false;
            }
            return true;
        }
    }
#endif
    // 重複チェック: 同一の情報（MT～VN の内容一致）は通知しない
    internal::DedupKey key{ decoded.msg_type, identity };
    if (_dedup.isDuplicate(key, now_ms, window_ms)) { out.clear(); return false; }

    // 同一オブジェクトなら内容は既に out にあるのでコピーしない（handleFrame は常にそう渡す）。
    if (&decoded != &out) out = decoded;
    return true;
}

#if AZARAC_ENABLE_NANKAI
internal::NankaiAggregateResult Parser::processNankaiAggregation(
    const Message& decoded, Message& out, const Mt43Data* d, uint64_t current_ms) {

    const NankaiData* nankai = d->getNankai();
    if (!nankai) return internal::NankaiAggregateResult::Rejected;

    // identity は電文の生ビット（NankaiData::report_*）から取る。正規化済みの event_time を使わない理由は NankaiPageKey 参照。
    internal::NankaiPageKey key;
    key.info_code       = nankai->info_code;
    key.information_type = d->information_type;
    key.report_month    = nankai->report_month;
    key.report_day      = nankai->report_day;
    key.report_hour     = nankai->report_hour;
    key.report_minute   = nankai->report_minute;
    key.report_classification = static_cast<uint8_t>(d->report_classification & 0x7u);

    internal::NankaiPageBuffer* buffer = nullptr;
    const internal::NankaiAggregateResult result = _nankaiBuffers.addPageEx(
        key,
        nankai->page,
        nankai->total_page,
        nankai->text,
        current_ms,
        &buffer
    );

    if (result != internal::NankaiAggregateResult::Complete) {
        return result;
    }
    if (!buffer) {
        return internal::NankaiAggregateResult::Rejected;
    }

    out = decoded;
    Mt43Data* outMt43 = out.getMt43();
    if (outMt43) {
        NankaiData* outNankai = outMt43->getNankai();
        if (outNankai) {
            outNankai->is_aggregated = false;
            outNankai->aggregated_len = 0;
            outNankai->aggregated_text_ptr = nullptr;
            outNankai->truncated = buffer->truncated;
            outNankai->total_page = buffer->original_total_pages;

            uint16_t textLen = buffer->compactText();
            // 集約本文があれば page=1（完成イベントの代表ページ）。ゼロ長なら完成ページ番号を保つ（provenance）。
            outNankai->page = (textLen > 0) ? 1 : nankai->page;
            if (textLen > 0) {
                // ゼロコピー: NankaiPageBuffer の内部ストレージを指す。
                // 次の feed() または reset() まで有効（NankaiData の説明参照）。
                outNankai->aggregated_text_ptr = buffer->aggregated_text;
                outNankai->aggregated_len = textLen;
                outNankai->is_aggregated = true;
            }
        }
    }
    return internal::NankaiAggregateResult::Complete;
}
#endif

#if AZARAC_ENABLE_NANKAI
const internal::NankaiPageBuffer* Parser::getNankaiBuffer(const internal::NankaiPageKey& key) const {
    return _nankaiBuffers.getBuffer(key);
}
#endif

void Parser::reset() {
    _ubx.reset();
    _nmea.reset();
    if (_custom) _custom->reset();
    _dedup.reset();
#if AZARAC_ENABLE_DEDUP || AZARAC_ENABLE_NANKAI
    _last_now_ms = 0;
#endif
#if AZARAC_ENABLE_NANKAI
    _nankaiBuffers.clearAll();
#endif
}

} // namespace azaraC
