// azaraC - src/Parser.cpp

#include "Parser.h"
#include "internal/TimeFields.h"

namespace azaraC {

bool Parser::feed(uint8_t byte, Message& out, uint32_t report_unix) {
    internal::Frame frame;

    // --- カスタムフレーマ（排他モード）---
    if (_custom) {
        if (!_custom->feed(byte, frame)) return false;
        Message decoded;
        if (!_decoder.decode(frame, decoded, report_unix)) return false;
        return postDecode(decoded, out);
    }

    // --- AUTO モード: UBX / NMEA を並行試行 ---
    bool ubx_ok  = false;
    bool nmea_ok = false;

    switch (_mode) {
    case Mode::UBX:
        ubx_ok = _ubx.feed(byte, frame);
        break;
    case Mode::NMEA:
        nmea_ok = _nmea.feed(byte, frame);
        break;
    case Mode::AUTO:
    default:
        ubx_ok  = _ubx.feed(byte, frame);
        if (!ubx_ok) nmea_ok = _nmea.feed(byte, frame);
        break;
    }

    if (!ubx_ok && !nmea_ok) return false;

    Message decoded;
    if (!_decoder.decode(frame, decoded, report_unix)) return false;
    return postDecode(decoded, out);
}

bool Parser::postDecode(const Message& decoded, Message& out) {
    // Nankai Trough page aggregation
    if (decoded.payload_type == MsgPayloadType::Mt43) {
        const Mt43Data* mt43 = decoded.getMt43();
        if (mt43 && mt43->disaster_category == 4) {
            // decoded と out を別オブジェクトにすることでエイリアシング UB を回避
            if (!processNankaiAggregation(decoded, out, internal::getMillis())) {
                return false;
            }
            // Aggregation complete - check dedup before outputting
            internal::DedupKey key{ out.svid, out.msg_type, out.crc24 };
            if (_dedup.isDuplicate(key)) return false;
            return true;
        }
    }

    // 重複チェック
    internal::DedupKey key{ decoded.svid, decoded.msg_type, decoded.crc24 };
    if (_dedup.isDuplicate(key)) return false;

    out = decoded;
    return true;
}

bool Parser::processNankaiAggregation(const Message& decoded, Message& out, uint64_t current_ms) {
    const Mt43Data* d = decoded.getMt43();
    if (!d) return false;

    const NankaiData* nankai = d->getNankai();
    if (!nankai) return false;

    // Create key for this event (svid NOT included - see design doc)
    internal::NankaiPageKey key;
    key.info_code = nankai->info_code;
    key.event_time_unix = d->event_time.unix_time;
// Guard: prevent aggregation when event_time fields are provided but unresolved.
// If event_time.unix_time == 0 while month/day/hour/minute are set, the time
// could not be resolved (e.g. missing report_unix baseline), and different
// events may collide on the same key {info_code, 0}. NankaiPageKey::isValid()
// checks event_time_unix != 0.
// However, if ALL raw time fields are zero, no time data was encoded at all,
// so aggregation is permitted (key collision risk is acceptable since events
// are indistinguishable without time data).
if (!key.isValid()) {
    bool time_provided = (d->event_time.month != 0 || d->event_time.day != 0 ||
                          d->event_time.hour != 0 || d->event_time.minute != 0);
    if (time_provided) {
        return false;  // Time fields provided but unresolved → reject
    }
    // else: no time data → allow aggregation
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
        // All pages received - copy decoded message and add aggregated text
        out = decoded;

        // Get the Mt43Data from the copied message
        Mt43Data* outMt43 = out.getMt43();
        if (outMt43) {
            NankaiData* outNankai = outMt43->getNankai();
            if (outNankai) {
                // Explicitly initialize to deterministic defaults (textLen == 0 path)
                outNankai->is_aggregated = false;
                outNankai->aggregated_len = 0;

                // Copy aggregated text to message
                uint16_t textLen = completed->getTextLength();
                if (textLen >= static_cast<uint16_t>(sizeof(outNankai->aggregated_text))) {
                    return false;
                }
                if (textLen > 0) {
                    completed->getText(outNankai->aggregated_text, sizeof(outNankai->aggregated_text));
                    outNankai->aggregated_len = textLen;
                    outNankai->is_aggregated = true;
                }
            }
        }

        return true;
    }

    // Not complete yet - don't output
    return false;
}

const internal::NankaiPageBuffer* Parser::getNankaiBuffer(const internal::NankaiPageKey& key) const {
    return _nankaiBuffers.getBuffer(key);
}

void Parser::reset() {
    _ubx.reset();
    _nmea.reset();
    if (_custom) _custom->reset();
    _dedup.reset();
    _nankaiBuffers.clearAll();
    _mode = Mode::AUTO;
}

} // namespace azaraC
