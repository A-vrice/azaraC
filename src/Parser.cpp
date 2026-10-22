#include "Parser.h"
#include "internal/DedupWindow.h"
#include "internal/TimeFields.h"

namespace azaraC {

bool Parser::feed(uint8_t byte, Message& out, uint32_t report_unix) {
    internal::Frame frame;

    // カスタムフレーマ（排他モード）
    if (_custom) {
        // カスタムフレーマは全フィールドを埋めずに true を返し得る。決定的なゼロ基準を与えるが、このオプトイン経路に限る:
        // 毎バイト 33 B をゼロ化すると、成功時に必ず Frame を埋める組み込みフレーマにコストが乗る。
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
    if (!_decoder.decode(frame, out, report_unix)) return false;
    // 手順③ の照合範囲は MT～VN（bit 8..219 = 212 bit、bit 220..225 は Reserved）。
    // プリアンブルと Reserved は放送で巡回し、受信衛星はフレームに無く NMEA/UBX ヘッダ由来なので鍵に含めない。
    // MT=44 の SD は事務局回答の照合範囲（MT および CAMF〜EM）に無く、Decoder::messageIdentity がゼロにしてから digest を取る。
    const uint32_t identity = internal::Decoder::messageIdentity(frame.bits);
    return postDecode(out, out, identity);   // decoded と out は同一（postDecode は aliasing 前提）
}

bool Parser::postDecode(const Message& decoded, Message& out, uint32_t identity) {
    // dedup 有効期間の受信時刻（手順④'）。
    // 下の Nankai 集約も同じ時計を使うので、両段階で「現在」が一致する。
    // 64 bit を丸ごと保持する: NankaiPageBuffer のタイムアウトは uint64 で、32 bit の dedup 窓は約 49.7 日ごとに巻き戻るため、ここで切り詰めると符号なしの経過時間比較がアンダーフローする。
    const uint64_t now_ms64 = internal::getMillis();
    const uint32_t now_ms = static_cast<uint32_t>(now_ms64);
    const uint32_t window_ms = internal::dedupWindowMs(decoded);

    // Nankai Trough page aggregation
#if AZARAC_ENABLE_NANKAI
    if (decoded.payload_type == MsgPayloadType::Mt43) {
        const Mt43Data* mt43 = decoded.getMt43();
        const NankaiData* nankai = mt43 ? mt43->getNankai() : nullptr;
        if (mt43 && mt43->disaster_category == 4) {
            // getNankai() が無いのは電文として成立していない場合。集約できないので出力しない。
            if (!nankai) { out.clear(); return false; }
            // out が decoded と同一でも安全: processNankaiAggregation が上書きするのは is_aggregated / aggregated_* / truncated / page / total_page だけで、直後に鍵として読む info_code と report_* は不変。
            if (!processNankaiAggregation(decoded, out, mt43, now_ms64)) {
                out.clear();
                return false;
            }
            // 同一性は事象そのもの（info_code + 情報種別 + 報告時刻）。
            // ページ集合を完成させた電文は到着順で変わるため、その crc24 を鍵にすると同じ事象が再送のたびに別情報として通知される。
            // 情報種別を含めるのは同一 info_code + 同一報告時刻の発表と取消を別扱いするため（NankaiPageKey 参照）。
            const internal::DedupKey key = internal::dedupEventKey(internal::dedupEventToken(
                nankai->info_code, mt43->information_type, nankai->report_month, nankai->report_day,
                nankai->report_hour, nankai->report_minute));
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
bool Parser::processNankaiAggregation(const Message& decoded, Message& out, const Mt43Data* d, uint64_t current_ms) {

    const NankaiData* nankai = d->getNankai();
    if (!nankai) return false;

    // 事象の identity = info_code + information_type + report_time month/day/hour/minute。
    // 正規化済みの Mt43Data::event_time は使わず電文の生ビット (NankaiData::report_*) から取る: resolveTime() は暦外の日付を書き換えたり（2/30 → 3/1）月=0 に近い月を割り当てるため、放送途中で report_unix が現れると 1 つの事象が複数バッファに分裂する（NankaiPageKey 参照）。
    internal::NankaiPageKey key;
    key.info_code       = nankai->info_code;
    key.information_type = d->information_type;
    key.report_month    = nankai->report_month;
    key.report_day      = nankai->report_day;
    key.report_hour     = nankai->report_hour;
    key.report_minute   = nankai->report_minute;

    internal::NankaiPageBuffer* completed = _nankaiBuffers.addPage(
        key,
        nankai->page,
        nankai->total_page,
        nankai->text,
        current_ms
    );

    if (completed) {
        out = decoded;
        Mt43Data* outMt43 = out.getMt43();
        if (outMt43) {
            NankaiData* outNankai = outMt43->getNankai();
            if (outNankai) {
                outNankai->is_aggregated = false;
                outNankai->aggregated_len = 0;
                outNankai->aggregated_text_ptr = nullptr;
                outNankai->truncated = completed->truncated;
                outNankai->page = 1;
                outNankai->total_page = completed->original_total_pages;

                uint16_t textLen = completed->compactText();
                if (textLen > 0) {
                    // ゼロコピー: NankaiPageBuffer の内部ストレージを指す。
                    // 次の feed() または reset() までのみ有効（NankaiData の説明参照）— 以降 aggregated_text_ptr は宙に浮く。
                    outNankai->aggregated_text_ptr = completed->aggregated_text;
                    outNankai->aggregated_len = textLen;
                    outNankai->is_aggregated = true;
                }
            }
        }
        return true;
    }
    return false;
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
#if AZARAC_ENABLE_NANKAI
    _nankaiBuffers.clearAll();
#endif
}

} // namespace azaraC
