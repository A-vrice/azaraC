#include "Parser.h"
#include "internal/DedupWindow.h"
#include "internal/TimeFields.h"

namespace azaraC {

bool Parser::feed(uint8_t byte, Message& out, uint32_t report_unix) {
    internal::Frame frame;

    // カスタムフレーマ（排他モード）
    if (_custom) {
        if (!_custom->feed(byte, frame)) return false;
        return handleFrame(frame, out, report_unix);
    }

    // AUTO 常時: UBX優先試行（UBXはバイナリ、NMEAはASCIIで競合しない）
    bool ubx_ok = _ubx.feed(byte, frame);
    bool nmea_ok = ubx_ok ? false : _nmea.feed(byte, frame);
    if (!ubx_ok && !nmea_ok) return false;

    return handleFrame(frame, out, report_unix);
}

bool Parser::handleFrame(const internal::Frame& frame, Message& out, uint32_t report_unix) {
    Message decoded;
    if (!_decoder.decode(frame, decoded, report_unix)) {
        // decoded is already cleared by decode(); copy it whole so a reused
        // out holding a previous valid message cannot leak stale payload.
        out = decoded;
        return false;
    }
    // 手順③ の照合対象は MT～VN（フレーム bit 8..219 = 212 bit。bit 220..225 は
    // Reserved）。プリアンブル（bit 0..7）と Reserved は放送で巡回するため鍵に含めない。
    // 受信衛星も含めない（Satellite ID はフレームに無く、NMEA/UBX ヘッダ由来）。
    const uint32_t identity = internal::Decoder::crc24q(frame.bits + 1, 212);
    return postDecode(decoded, out, identity);
}

bool Parser::postDecode(const Message& decoded, Message& out, uint32_t identity) {
    // Reception time for the dedup validity window (手順④'). Nankai aggregation
    // below uses the same clock, so both stages agree on "now".
    const uint32_t now_ms = static_cast<uint32_t>(internal::getMillis());
    const uint32_t window_ms = internal::dedupWindowMs(decoded);

    // Nankai Trough page aggregation
#if AZARAC_ENABLE_NANKAI
    if (decoded.payload_type == MsgPayloadType::Mt43) {
        const Mt43Data* mt43 = decoded.getMt43();
        const NankaiData* nankai = mt43 ? mt43->getNankai() : nullptr;
        if (mt43 && mt43->disaster_category == 4) {
            // getNankai() が無いのは電文として成立していない場合。集約できないので
            // 以前と同じく出力しない。
            if (!nankai) { out.clear(); return false; }
            // decoded と out を別オブジェクトにすることでエイリアシング UB を回避
            if (!processNankaiAggregation(decoded, out, mt43, now_ms)) {
                out.clear();
                return false;
            }
            // 同一性は事象そのもの（info_code + 報告時刻）。ページ集合を完成させた
            // 電文は到着順で変わるため、その crc24 を鍵にすると同じ事象が再送の
            // たびに別情報として通知される。
            const internal::DedupKey key = internal::dedupEventKey(internal::dedupEventToken(
                nankai->info_code, nankai->report_month, nankai->report_day,
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

    out = decoded;
    return true;
}

#if AZARAC_ENABLE_NANKAI
bool Parser::processNankaiAggregation(const Message& decoded, Message& out, const Mt43Data* d, uint32_t current_ms) {

    const NankaiData* nankai = d->getNankai();
    if (!nankai) return false;

    // 事象の identity = info_code + report_time month/day/hour/minute。値は電文の生ビット
    // (NankaiData::report_*) から取り、正規化済みの Mt43Data::event_time は使わない:
    // resolveTime() は暦外の日付を書き換えたり（2/30 → 3/1）月=0 に近い月を割り当てるため、
    // 放送途中で report_unix が現れると1つの事象が複数バッファに分裂する。NankaiPageKey 参照。
    internal::NankaiPageKey key;
    key.info_code       = nankai->info_code;
    key.report_month    = nankai->report_month;
    key.report_day      = nankai->report_day;
    key.report_hour     = nankai->report_hour;
    key.report_minute   = nankai->report_minute;

    // Add page to buffer
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
                    // Zero-copy: point into NankaiPageBuffer's internal storage.
                    // VALID ONLY until next feed() or reset() — see NankaiData docs.
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
