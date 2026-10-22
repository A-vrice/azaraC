#include "JsonWriter.h"

namespace azaraC {
namespace internal {

#if defined(__AVR__)
// キーを書き出すときの 1 次コピー先。ラベルの共有バッファ (def::azarac_flash_buf) とは別に持つ: wf_s はキーを書いた後にラベルを書くが、ラベルは呼び出し側で既にそのバッファへ展開済みなので、同じバッファへキーを写すとラベルを壊す。
static char* keyBuf() {
    static char buf[AZARAC_KEY_BUF_SIZE];
    return buf;
}
#endif

// キーを書き出せる形にする。AVR ではキーが Flash にあるので、sizeof で分かっている長さぶんだけ RAM へ写す。
static std::string_view keyView(JsonKey k) {
#if defined(__AVR__)
    char* buf = keyBuf();
    for (uint8_t i = 0; i < k.len; ++i) {
        buf[i] = static_cast<char>(AZARAC_PGM_READ_BYTE(k.p + i));
    }
    buf[k.len] = '\0';
    return std::string_view(buf, k.len);
#else
    return std::string_view(k.p, k.len);
#endif
}

void writeChar(Print& out, char c) { out.print(c); }

// 共有キーバッファは使わない: writeEscaped の途中で呼ばれると、書き出し中のキー/ラベルを壊す。
void writeRaw(Print& out, JsonKey k) {
#if defined(__AVR__)
    for (uint8_t i = 0; i < k.len; ++i) {
        out.write(static_cast<uint8_t>(AZARAC_PGM_READ_BYTE(k.p + i)));
    }
#else
    out.write(k.p, k.len);
#endif
}

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

// JSON 文字列をエスケープする（キーと値の両方で使う）
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
            case '"':  writeRaw(out, AZARAC_KEY("\\\"")); break;
            case '\\': writeRaw(out, AZARAC_KEY("\\\\")); break;
            case '\b': writeRaw(out, AZARAC_KEY("\\b"));  break;
            case '\f': writeRaw(out, AZARAC_KEY("\\f"));  break;
            case '\n': writeRaw(out, AZARAC_KEY("\\n"));  break;
            case '\r': writeRaw(out, AZARAC_KEY("\\r"));  break;
            case '\t': writeRaw(out, AZARAC_KEY("\\t"));  break;
            default:
                if (c < 0x20) {
                    // 制御文字は \u00XX（snprintf/printf 依存を避けてニブルで書く）
                    writeRaw(out, AZARAC_KEY("\\u00"));
                    out.print(hexDigit(c >> 4));
                    out.print(hexDigit(c));
                } else {
                    // 印字可能な ASCII と UTF-8 はそのまま通す
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
    if (!s) { writeRaw(out, AZARAC_KEY("null")); return; }
    writeStr(out, *s);
}

void writeHex(Print& out, uint8_t v) {
    char buf[5] = "\"00\"";
    buf[1] = hexDigit(v >> 4);
    buf[2] = hexDigit(v);
    out.print(buf);
}

// `"key":`。keyView の戻りは次のキー書き出しまでしか有効でない（AVR では共有のキーバッファを指す）。
static void writeKey(Print& out, JsonKey k) {
    const std::string_view name = keyView(k);
    out.print('"'); writeEscaped(out, name); writeRaw(out, AZARAC_KEY("\":"));
}

void wk(Print& out, JsonKey k) {
    writeKey(out, k);
}

void wf_u(Print& out, JsonKey k, uint32_t v, bool last) {
    writeKey(out, k); writeUint32(out, v); if (!last) writeChar(out, ',');
}

void wf_u64(Print& out, JsonKey k, uint64_t v, bool last) {
    writeKey(out, k); writeUint64(out, v); if (!last) writeChar(out, ',');
}

void wf_x(Print& out, JsonKey k, uint32_t v, bool last) {
    writeKey(out, k);
    char buf[11];
    buf[0] = '0'; buf[1] = 'x';
    for (int i = 0; i < 8; ++i) {
        buf[2 + i] = hexDigit(v >> (28 - i * 4));
    }
    buf[10] = '\0';
    out.print('"');
    out.print(buf);
    out.print('"');
    if (!last) writeChar(out, ',');
}

void wf_deg(Print& out, JsonKey k, int32_t denominator, int32_t v, bool last) {
    writeKey(out, k);

    uint32_t mag = (uint32_t)v;
    if (v < 0) { out.print('-'); mag = 0u - mag; }   // 2 の補数で絶対値（INT32_MIN でも UB にしない）

    const uint32_t den = (uint32_t)denominator;
    writeUint32(out, mag / den);

    // denominator の桁数 = 小数部の桁数（1000000 → 6）
    uint8_t digits = 0;
    // 上限 9 は uint32 の最大桁数 - 1。明示すると GCC が buf[digits] の範囲を
    // 証明でき、-O2 -flto の -Wstringop-overflow 偽陽性（digits を [129,255]
    // と誤認）を出さない。den が 10 桁でも digits=9 のまま。
    for (uint32_t d = den / 10u; d != 0 && digits < 9; d /= 10u) ++digits;
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

void wf_s(Print& out, JsonKey k, std::optional<std::string_view> v, bool last) {
    writeKey(out, k); writeOptStr(out, v); if (!last) writeChar(out, ',');
}

void wf_s(Print& out, JsonKey k, const char* v, bool last) {
    writeKey(out, k);
    if (v) {
        writeStr(out, std::string_view(v));
    } else {
        writeRaw(out, AZARAC_KEY("null"));
    }
    if (!last) writeChar(out, ',');
}

void wf_s(Print& out, JsonKey k, JsonKey v, bool last) {
    writeKey(out, k); writeStr(out, keyView(v)); if (!last) writeChar(out, ',');
}

void wf_v(Print& out, JsonKey field, uint32_t value,
          std::optional<std::string_view> label, bool last) {
    // 名前は 1 度だけ取り出す（`"d1_magnitude":1,"d1_magnitude_label":"…"`）: AVR では Flash からのコピーが 1 回で済む。
    const std::string_view name = keyView(field);
    out.print('"'); writeEscaped(out, name); writeRaw(out, AZARAC_KEY("\":"));
    writeUint32(out, value); writeChar(out, ',');
    out.print('"'); writeEscaped(out, name); writeRaw(out, AZARAC_KEY("_label\":"));
    writeOptStr(out, label);
    if (!last) writeChar(out, ',');
}

void writeDHM(Print& out, JsonKey key, const TimeFields& t, bool last) {
    writeKey(out, key);
    out.print('{');
    wf_u(out, AZARAC_KEY("month"), t.month);
    wf_u(out, AZARAC_KEY("day"),   t.day);
    wf_u(out, AZARAC_KEY("hour"),  t.hour);
    wf_u(out, AZARAC_KEY("min"),   t.minute);
    if (t.unix_time == 0) { wk(out, AZARAC_KEY("unix")); writeRaw(out, AZARAC_KEY("null")); }
    else                  { wf_u(out, AZARAC_KEY("unix"), t.unix_time, /*last=*/true); }
    out.print('}');
    if (!last) writeChar(out, ',');
}

void writeLatLon(Print& out, JsonKey key, const LatLon& ll, bool last) {
    writeKey(out, key);
    out.print('{');
    wf_u(out, AZARAC_KEY("lat_ns"),  ll.lat_ns);
    wf_u(out, AZARAC_KEY("lat_deg"), ll.lat_deg);
    wf_u(out, AZARAC_KEY("lat_min"), ll.lat_min);
    wf_u(out, AZARAC_KEY("lat_sec"), ll.lat_sec);
    wf_u(out, AZARAC_KEY("lon_ew"),  ll.lon_ew);
    wf_u(out, AZARAC_KEY("lon_deg"), ll.lon_deg);
    wf_u(out, AZARAC_KEY("lon_min"), ll.lon_min);
    wf_u(out, AZARAC_KEY("lon_sec"), ll.lon_sec, /*last=*/true);
    out.print('}');
    if (!last) writeChar(out, ',');
}

} // namespace internal
} // namespace azaraC
