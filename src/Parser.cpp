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

bool Parser::handleFrame(internal::Frame& frame, Message& out, uint32_t report_unix) {
    if (!_decoder.decode(frame, out, report_unix)) {
        // 復号に失敗したフレームで valid だけ立った中途半端な Message を残さない。
        // decodeQzqsm() は valid=true を設定した後に oob_ で false を返す経路があるため、
        // ここで落とす。CRC 失敗時は Decoder が svid も 0 に戻す（成功時だけ frame の svid が残る）。
        // その他の false では out の内容は未定義なので、呼び出し側は読まないこと。
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

bool Parser::postDecodeAt(const Message& decoded, Message& out, uint32_t identity, uint64_t now_ms64) {
    // dedup 有効期間の受信時刻（手順④'）。
    // 下の Nankai 集約も同じ時計を使うので、両段階で「現在」が一致する。
    // 通常の 32 bit 折り返しは DedupFilter/NankaiPageBuffer の符号なし差分で扱えるが、
    // 2^32 ms 以上の空白や時計の再設定では 32 bit の last_seen が「最近」に見えてしまう。
    // 小さな後退は受信順序の揺らぎとして丸め、それを超える後退と 2^32 ms 以上の空白だけ履歴を捨てる
    // （再通知は許容し、生きた警報の抑止は避ける）。
#if AZARAC_ENABLE_DEDUP || AZARAC_ENABLE_NANKAI
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
    } else if ((now_ms64 - _last_now_ms) >= (1ULL << 32)) {
        _dedup.reset();
#if AZARAC_ENABLE_NANKAI
        _nankaiBuffers.clearAll();
#endif
    }
    _last_now_ms = now_ms64;
#endif
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
            internal::NankaiPageBuffer* completed = nullptr;
            const internal::NankaiAggregateResult aggregate = processNankaiAggregation(
                decoded, out, mt43, now_ms64, &completed);
            if (aggregate == internal::NankaiAggregateResult::Rejected ||
                aggregate == internal::NankaiAggregateResult::NotComplete) {
                out.clear();
                return false;
            }

            // 同一性は事象そのもの（info_code + 情報種別 + Rc + 報告時刻）。
            // ページ集合を完成させた電文は到着順で変わるため、その crc24 を鍵にすると同じ事象が再送のたびに別情報として通知される。
            // 情報種別を含めるのは同一 info_code + 同一報告時刻の発表と取消を別扱いするため（NankaiPageKey 参照）。
            // Rc を含めるのは訓練/試験が実警報を抑止・混在させないため。
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
    const Message& decoded, Message& out, const Mt43Data* d, uint64_t current_ms,
    internal::NankaiPageBuffer** completed) {

    if (completed) *completed = nullptr;
    const NankaiData* nankai = d->getNankai();
    if (!nankai) return internal::NankaiAggregateResult::Rejected;

    // 事象の identity = info_code + information_type + Rc + report_time（月/日/時/分）。
    // 正規化済みの Mt43Data::event_time は使わず電文の生ビット（NankaiData::report_*）から取る。
    // resolveTime() は暦外の日付を書き換え（2/30 → 3/1）月=0 に近い月を割り当てるため、放送途中で report_unix が現れると 1 つの事象が複数バッファに分裂する（NankaiPageKey 参照）。
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
            outNankai->page = 1;
            outNankai->total_page = buffer->original_total_pages;

            uint16_t textLen = buffer->compactText();
            if (textLen > 0) {
                // ゼロコピー: NankaiPageBuffer の内部ストレージを指す。
                // 次の feed() または reset() まで有効（NankaiData の説明参照）。
                outNankai->aggregated_text_ptr = buffer->aggregated_text;
                outNankai->aggregated_len = textLen;
                outNankai->is_aggregated = true;
            }
        }
    }
    if (completed) *completed = buffer;
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
