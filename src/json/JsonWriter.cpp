#include "JsonWriter.h"

namespace azaraC {
namespace internal {

static constexpr char HEX_CHARS[] = "0123456789ABCDEF";

void writeChar(Print& out, char c) { out.print(c); }

void writeUint32(Print& out, uint32_t v) {
    char buf[11]; int8_t i = 10; buf[i] = '\0';
    if (v == 0) { out.print('0'); return; }
    while (v) { buf[--i] = '0' + (v % 10); v /= 10; }
    out.print(buf + i);
}

void writeUint64(Print& out, uint64_t v) {
    char buf[21]; int8_t i = 20; buf[i] = '\0';
    if (v == 0) { out.print('0'); return; }
    while (v) { buf[--i] = '0' + (v % 10); v /= 10; }
    out.print(buf + i);
}

// Escapes a JSON string (used for both keys and values)
static void writeEscaped(Print& out, std::string_view s) {
    if (s.empty()) return;
    // エスケープ不要な文字列（キーとほぼ全てのラベル）は 1 回の write() で出す。 1 バイト 1 回の print() が文書全体のコストの大半を占めるため（実測 0.92 呼び出し/バイト）。
    bool plain = true;
    for (size_t i = 0; i < s.size(); ++i) {
        const uint8_t c = static_cast<uint8_t>(s[i]);
        if (c == '"' || c == '\\' || c < 0x20) { plain = false; break; }
    }
    if (plain) { out.write(s.data(), s.size()); return; }

    for (size_t i = 0; i < s.size(); ++i) {
        uint8_t c = static_cast<uint8_t>(s[i]);
        switch (c) {
            case '"':  out.print("\\\""); break;
            case '\\': out.print("\\\\"); break;
            case '\b': out.print("\\b");  break;
            case '\f': out.print("\\f");  break;
            case '\n': out.print("\\n");  break;
            case '\r': out.print("\\r");  break;
            case '\t': out.print("\\t");  break;
            default:
                if (c < 0x20) {
                    // \u00XX via nibbles (avoids snprintf/printf dep)
                    out.print("\\u00");
                    out.print(HEX_CHARS[c >> 4]);
                    out.print(HEX_CHARS[c & 0xF]);
                } else {
                    // Printable ASCII and UTF-8 pass through
                    out.print(static_cast<char>(c));
                }
                break;
        }
    }
}

void writeStr(Print& out, std::string_view s) {
    out.print('"'); writeEscaped(out, s); out.print('"');
}

void writeOptStr(Print& out, std::optional<std::string_view> s) {
    if (!s) { out.print("null"); return; }
    writeStr(out, *s);
}

void writeHex(Print& out, uint8_t v) {
    char buf[5] = "\"00\"";
    buf[1] = HEX_CHARS[v >> 4];
    buf[2] = HEX_CHARS[v & 0x0F];
    out.print(buf);
}

void wk(Print& out, std::string_view k) {
    out.print('"'); writeEscaped(out, k); out.print("\":");
}

void wf_u(Print& out, std::string_view k, uint32_t v, bool last) {
    wk(out, k); writeUint32(out, v); if (!last) writeChar(out, ',');
}

void wf_u64(Print& out, std::string_view k, uint64_t v, bool last) {
    wk(out, k); writeUint64(out, v); if (!last) writeChar(out, ',');
}

void wf_x(Print& out, std::string_view k, uint32_t v, bool last) {
    wk(out, k);
    char buf[11];
    buf[0] = '0'; buf[1] = 'x';
    for (int i = 0; i < 8; ++i) {
        buf[2 + i] = HEX_CHARS[(v >> (28 - i * 4)) & 0xF];
    }
    buf[10] = '\0';
    out.print('"');
    out.print(buf);
    out.print('"');
    if (!last) writeChar(out, ',');
}

void wf_deg(Print& out, std::string_view k, int32_t denominator, int32_t v, bool last) {
    wk(out, k);

    uint32_t mag = (uint32_t)v;
    if (v < 0) { out.print('-'); mag = 0u - mag; }   // 2 の補数で絶対値（INT32_MIN でも UB にしない）

    const uint32_t den = (uint32_t)denominator;
    writeUint32(out, mag / den);

    // denominator の桁数 = 小数部の桁数（1000000 → 6）
    uint8_t digits = 0;
    for (uint32_t d = den / 10u; d != 0; d /= 10u) ++digits;
    if (digits) {
        char buf[12];   // uint32 の denominator は最大 10 桁
        uint32_t frac = mag % den;
        for (int8_t i = (int8_t)digits - 1; i >= 0; --i) { buf[i] = (char)('0' + (frac % 10u)); frac /= 10u; }
        buf[digits] = '\0';
        out.print('.');
        out.print(buf);
    }
    if (!last) writeChar(out, ',');
}

void wf_s(Print& out, std::string_view k, std::optional<std::string_view> v, bool last) {
    wk(out, k); writeOptStr(out, v); if (!last) writeChar(out, ',');
}

void wf_s(Print& out, std::string_view k, const char* v, bool last) {
    wk(out, k);
    if (v) {
        writeStr(out, std::string_view(v));
    } else {
        out.print("null");
    }
    if (!last) writeChar(out, ',');
}

void wf_v(Print& out, std::string_view field, uint32_t value,
          std::optional<std::string_view> label, bool last) {
    wk(out, field); writeUint32(out, value); writeChar(out, ',');
    out.print('"'); writeEscaped(out, field); out.print("_label\":");
    writeOptStr(out, label);
    if (!last) writeChar(out, ',');
}

void writeDHM(Print& out, std::string_view key, const TimeFields& t, bool last) {
    wk(out, key);
    out.print('{');
    wf_u(out, "month", t.month);
    wf_u(out, "day",   t.day);
    wf_u(out, "hour",  t.hour);
    wf_u(out, "min",   t.minute);
    if (t.unix_time == 0) { wk(out, "unix"); out.print("null"); }
    else                  { wf_u(out, "unix", t.unix_time, /*last=*/true); }
    out.print('}');
    if (!last) writeChar(out, ',');
}

void writeLatLon(Print& out, std::string_view key, const LatLon& ll, bool last) {
    wk(out, key);
    out.print('{');
    wf_u(out, "lat_ns",  ll.lat_ns);
    wf_u(out, "lat_deg", ll.lat_deg);
    wf_u(out, "lat_min", ll.lat_min);
    wf_u(out, "lat_sec", ll.lat_sec);
    wf_u(out, "lon_ew",  ll.lon_ew);
    wf_u(out, "lon_deg", ll.lon_deg);
    wf_u(out, "lon_min", ll.lon_min);
    wf_u(out, "lon_sec", ll.lon_sec, /*last=*/true);
    out.print('}');
    if (!last) writeChar(out, ',');
}

} // namespace internal
} // namespace azaraC
