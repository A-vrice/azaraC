#include "Parser.h"
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
    return postDecode(decoded, out);
}

bool Parser::postDecode(const Message& decoded, Message& out) {
    // Nankai Trough page aggregation
#if AZARAC_ENABLE_NANKAI
    if (decoded.payload_type == MsgPayloadType::Mt43) {
        const Mt43Data* mt43 = decoded.getMt43();
        if (mt43 && mt43->disaster_category == 4) {
            // decoded と out を別オブジェクトにすることでエイリアシング UB を回避
            if (!processNankaiAggregation(decoded, out, mt43, internal::getMillis())) {
                out.clear();
                return false;
            }
            // Aggregation complete - check dedup before outputting
            internal::DedupKey key{ out.svid, out.msg_type, out.crc24 };
            if (_dedup.isDuplicate(key)) {
                out.clear();
                return false;
            }
            return true;
        }
    }
#endif
    // 重複チェック
    internal::DedupKey key{ decoded.svid, decoded.msg_type, decoded.crc24 };
    if (_dedup.isDuplicate(key)) { out.clear(); return false; }

    out = decoded;
    return true;
}

#if AZARAC_ENABLE_NANKAI
bool Parser::processNankaiAggregation(const Message& decoded, Message& out, const Mt43Data* d, uint64_t current_ms) {

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
