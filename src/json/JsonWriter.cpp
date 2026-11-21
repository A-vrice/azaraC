#include "JsonWriter.h"

namespace azaraC {
namespace internal {

#if defined(__AVR__)
// AVR ではキーが Flash にある。writeEscapedKey は Flash から直接走査してスタックへ 1 回写すため、キー引き当て用の静的 RAM バッファは持たない。
#endif

void writeChar(Print& out, char c) { out.print(c); }

void writeRaw(Print& out, JsonKey k) {
#if defined(__AVR__)
    // 共有キーバッファは使わない: writeEscaped の途中で呼ばれると、書き出し中のキー/ラベルを壊す。
    // スタックへ 1 度写して 1 回の write() で出す（実コアの print(const char*) と同じ経路）。
    char buf[AZARAC_KEY_BUF_SIZE];
    for (uint8_t i = 0; i < k.len; ++i) buf[i] = static_cast<char>(AZARAC_PGM_READ_BYTE(k.p + i));
    out.write(buf, k.len);
#else
    out.write(k.p, k.len);
#endif
}

void writeUint32(Print& out, uint32_t v) {
    char buf[10]; int8_t i = 10;
    if (v == 0) { out.write("0", 1); return; }
    while (v) { buf[--i] = '0' + (v % 10); v /= 10; }
    out.write(buf + i, 10 - i);   // 長さ既知の write（print(const char*) の strlen 走査を避ける）
}

void writeUint64(Print& out, uint64_t v) {
    char buf[20]; int8_t i = 20;
    if (v == 0) { out.write("0", 1); return; }
    while (v) { buf[--i] = '0' + (v % 10); v /= 10; }
    out.write(buf + i, 20 - i);
}

// JSON 文字列をエスケープする（キーと値の両方で使う）
static void writeEscaped(Print& out, std::string_view s) {
    if (s.empty()) return;
    // エスケープ不要な文字列（キーとほぼ全てのラベル）は 1 回の write() で出す。
    // 1 バイト 1 回の print() が文書全体のコストの大半を占めるため。
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

#if AZARAC_ENABLE_NANKAI
// UTF-8 の 1 単位を判定する。valid なら len バイトの正しいシーケンス。
// 不正なら len は U+FFFD 1 個で置換すべき maximal subpart のバイト数（Python errors="replace" 互換）。
// 不正バイトは再処理するので、壊れたシーケンスの残りも個別に置換される。
struct Utf8Unit { bool valid; uint8_t len; };
static Utf8Unit utf8Unit(const uint8_t* p, size_t n) {
    const uint8_t b0 = p[0];
    if (b0 < 0x80) return {true, 1};
    auto cont = [&](size_t k) { return k < n && (p[k] & 0xC0) == 0x80; };
    if (b0 >= 0xC2 && b0 <= 0xDF) {           // C0/C1 は overlong で不正
        return cont(1) ? Utf8Unit{true, 2} : Utf8Unit{false, 1};
    }
    if (b0 >= 0xE0 && b0 <= 0xEF) {
        const uint8_t b1 = (n > 1) ? p[1] : 0;
        const bool b1ok = cont(1)
            && (b0 != 0xE0 || b1 >= 0xA0)     // E0: overlong 禁止
            && (b0 != 0xED || b1 <= 0x9F);    // ED: サロゲート禁止
        if (!b1ok) return {false, 1};
        return cont(2) ? Utf8Unit{true, 3} : Utf8Unit{false, 2};
    }
    if (b0 >= 0xF0 && b0 <= 0xF4) {           // F5-FF は不正
        const uint8_t b1 = (n > 1) ? p[1] : 0;
        const bool b1ok = cont(1)
            && (b0 != 0xF0 || b1 >= 0x90)     // F0: overlong 禁止
            && (b0 != 0xF4 || b1 <= 0x8F);    // F4: > U+10FFFF 禁止
        if (!b1ok) return {false, 1};
        if (!cont(2)) return {false, 2};
        return cont(3) ? Utf8Unit{true, 4} : Utf8Unit{false, 3};
    }
    return {false, 1};                        //  stray continuation 等
}

// ASCII 1 バイトの JSON エスケープ（writeEscaped と同じ規則）。
static void escapeByte(Print& out, uint8_t c) {
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
                writeRaw(out, AZARAC_KEY("\\u00"));
                out.print(hexDigit(c >> 4));
                out.print(hexDigit(c));
            } else {
                out.print(static_cast<char>(c));
            }
            break;
    }
}

void writeStrUtf8(Print& out, std::string_view s) {
    out.print('"');
    const uint8_t* p = reinterpret_cast<const uint8_t*>(s.data());
    const size_t n = s.size();
    size_t i = 0;
    while (i < n) {
        const Utf8Unit u = utf8Unit(p + i, n - i);
        if (u.valid) {
            if (u.len == 1) {
                escapeByte(out, p[i]);
            } else {
                // 有効なマルチバイトは全バイト >= 0x80 なのでエスケープ不要。
                out.write(reinterpret_cast<const char*>(p + i), u.len);
            }
        } else {
            // 不正シーケンスは U+FFFD (EF BF BD) 1 個に置換（Flash から直接書く）。
            writeRaw(out, AZARAC_KEY("\xEF\xBF\xBD"));
        }
        i += u.len;
    }
    out.print('"');
}
#endif // AZARAC_ENABLE_NANKAI

// キー（JsonKey）をエスケープ付きで書く。
// AVR では Flash から直接走査し、エスケープ不要ならスタックへ 1 回写して 1 回の write で出す（キー引き当て用の静的 RAM バッファを持たない）。
static void writeEscapedKey(Print& out, JsonKey k) {
#if defined(__AVR__)
    char buf[AZARAC_KEY_BUF_SIZE];
    bool plain = true;
    for (uint8_t i = 0; i < k.len; ++i) {
        const uint8_t c = static_cast<uint8_t>(AZARAC_PGM_READ_BYTE(k.p + i));
        buf[i] = static_cast<char>(c);
        if (c == '"' || c == '\\' || c < 0x20) plain = false;
    }
    if (plain) { out.write(buf, k.len); return; }
    // AZARAC_KEY は文字列リテラル専用なので通常ここへは来ないが、契約は string_view 版と同じにする
    writeEscaped(out, std::string_view(buf, k.len));
#else
    writeEscaped(out, std::string_view(k.p, k.len));
#endif
}

void writeOptStr(Print& out, std::optional<std::string_view> s) {
    if (!s) { writeRaw(out, AZARAC_KEY("null")); return; }
    writeStr(out, *s);
}

void writeHex(Print& out, uint8_t v) {
    char buf[4] = { '"', '0', '0', '"' };
    buf[1] = hexDigit(v >> 4);
    buf[2] = hexDigit(v);
    out.write(buf, 4);
}

// `"key":`。キーは Flash から直接書き出し、戻り値の寿命契約は持たない。
static void writeKey(Print& out, JsonKey k) {
    out.print('"');
    writeEscapedKey(out, k);
    writeRaw(out, AZARAC_KEY("\":"));
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
    char buf[10];
    buf[0] = '0'; buf[1] = 'x';
    for (int i = 0; i < 8; ++i) {
        buf[2 + i] = hexDigit(v >> (28 - i * 4));
    }
    out.print('"');
    out.write(buf, 10);
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
    // 上限 9 は uint32 の最大桁数 - 1。
    // 明示すると GCC が buf[digits] の範囲を証明でき、-O2 -flto の -Wstringop-overflow 偽陽性（digits を [129,255] と誤認）を避けられる。
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
    writeKey(out, k);
    out.print('"');
    writeEscapedKey(out, v);
    out.print('"');
    if (!last) writeChar(out, ',');
}

void wf_v(Print& out, JsonKey field, uint32_t value,
          std::optional<std::string_view> label, bool last) {
    // `"d1_magnitude":1,"d1_magnitude_label":"…"`: キー名は Flash から 2 回直接書く。
    out.print('"'); writeEscapedKey(out, field); writeRaw(out, AZARAC_KEY("\":"));
    writeUint32(out, value); writeChar(out, ',');
    out.print('"'); writeEscapedKey(out, field); writeRaw(out, AZARAC_KEY("_label\":"));
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
