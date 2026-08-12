#include "Parser.h"
#include "internal/TimeFields.h"

namespace azaraC {

bool Parser::feed(uint8_t byte, Message& out, uint32_t report_unix) {
    internal::Frame frame;

    // カスタムフレーマ（排他モード）
    if (_custom) {
        if (!_custom->feed(byte, frame)) return false;
        Message decoded;
        if (!_decoder.decode(frame, decoded, report_unix)) {
            out.unsupported_reason = decoded.unsupported_reason;
            out.msg_type = decoded.msg_type;
            out.svid     = decoded.svid;
            return false;
        }
        return postDecode(decoded, out);
    }

    // AUTO 常時: UBX優先試行（UBXはバイナリ、NMEAはASCIIで競合しない）
    bool ubx_ok = _ubx.feed(byte, frame);
    bool nmea_ok = ubx_ok ? false : _nmea.feed(byte, frame);
    if (!ubx_ok && !nmea_ok) return false;

    Message decoded;
    if (!_decoder.decode(frame, decoded, report_unix)) {
        out.unsupported_reason = decoded.unsupported_reason;
        out.msg_type = decoded.msg_type;
        out.svid     = decoded.svid;
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
    if (_dedup.isDuplicate(key)) return false;

    out = decoded;
    return true;
}

#if AZARAC_ENABLE_NANKAI
bool Parser::processNankaiAggregation(const Message& decoded, Message& out, const Mt43Data* d, uint64_t current_ms) {

    const NankaiData* nankai = d->getNankai();
    if (!nankai) return false;

    // Create key for this event (svid NOT included - see design doc)
    internal::NankaiPageKey key;
    key.info_code = nankai->info_code;
    key.event_time_unix = d->event_time.unix_time;
    if (!key.isValid()) {
        bool time_provided = (d->event_time.month != 0 || d->event_time.day != 0 ||
                              d->event_time.hour != 0 || d->event_time.minute != 0);
        if (time_provided) {
            // UNIX time was not resolved but DHM fields exist → use as fallback key
            // month is not included (month boundary crossing doesn't uniquely identify date)
            key.fallback_day    = d->event_time.day;
            key.fallback_hour   = d->event_time.hour;
            key.fallback_minute = d->event_time.minute;
            // isValid() now returns true → proceeds to normal aggregation flow
        }
        // time_provided == false → key stays invalid (fallback fields unset).
        // addPage does NOT check key.isValid(); it still keys on info_code and
        // aggregates pages, so aggregation proceeds with the unresolved key.
    }

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

                uint16_t textLen = completed->getTextLength();
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
