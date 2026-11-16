// JSON シリアライザのエントリポイント

#include "azaraC.h"
#include "JsonSerializer.h"
#include "JsonWriter.h"
#include "definition/_index.h"
#if defined(__AVR__)
#include "../internal/avr_std/optional"
#else
#include <optional>
#endif
#if defined(__AVR__)
#include "../internal/avr_std/string_view"
#else
#include <string_view>
#endif

namespace azaraC {
namespace internal {

// 前方宣言（実体は別ファイル）
#if (AZARAC_ENABLE_DCX_CAMF)
void serializeDcx(const Message& m, Print& out);
#endif
#if (AZARAC_ENABLE_EEW)
bool serializeEEW(const Mt43Data* d, Print& out);
#endif
#if (AZARAC_ENABLE_HYPOCENTER)
bool serializeHypocenter(const Mt43Data* d, Print& out);
#endif
#if (AZARAC_ENABLE_SEISMIC)
bool serializeSeismic(const Mt43Data* d, Print& out);
#endif
#if (AZARAC_ENABLE_NANKAI)
bool serializeNankai(const Mt43Data* d, Print& out);
#endif
#if (AZARAC_ENABLE_TSUNAMI)
bool serializeTsunami(const Mt43Data* d, Print& out);
#endif
#if (AZARAC_ENABLE_NW_PAC_TSUNAMI)
bool serializeNwPacTsu(const Mt43Data* d, Print& out);
#endif
#if (AZARAC_ENABLE_VOLCANO)
bool serializeVolcano(const Mt43Data* d, Print& out);
#endif
#if (AZARAC_ENABLE_ASH_FALL)
bool serializeAshFall(const Mt43Data* d, Print& out);
#endif
#if (AZARAC_ENABLE_WEATHER)
bool serializeWeather(const Mt43Data* d, Print& out);
#endif
#if (AZARAC_ENABLE_FLOOD)
bool serializeFlood(const Mt43Data* d, Print& out);
#endif
#if (AZARAC_ENABLE_TYPHOON)
bool serializeTyphoon(const Mt43Data* d, Print& out);
#endif
#if (AZARAC_ENABLE_MARINE)
bool serializeMarine(const Mt43Data* d, Print& out);
#endif

// msg_type による振り分け
void JsonSerializer::serialize(const Message& msg, Print& out) {
    using namespace azaraC::def;
    out.print('{');
    wf_u(out, AZARAC_KEY("schema_version"), 2);
    wf_u(out, AZARAC_KEY("svid"),     msg.svid);
    wf_u(out, AZARAC_KEY("msg_type"), msg.msg_type);
    wf_x(out, AZARAC_KEY("crc24"),    msg.crc24);

#if (AZARAC_ENABLE_DCX_CAMF)
    if (msg.msg_type == 44) {
        serializeDcx(msg, out);
    } else
#endif
    if (msg.msg_type == 43) {
        const Mt43Data* d = msg.getMt43();
        if (!d) {
            wf_s(out, AZARAC_KEY("note"), AZARAC_KEY("invalid_mt43"), /*last=*/true);
            out.print('}');
            return;
        }
        
        wf_u(out, AZARAC_KEY("report_classification"), d->report_classification);
        AZARAC_LABEL(out, "report_classification_label",
            qzss_dcr_jma_report_classification_lookup,
            qzss_dcr_jma_report_classification_en_lookup, d->report_classification, false);
        wf_u(out, AZARAC_KEY("disaster_category"), d->disaster_category);
        AZARAC_LABEL(out, "disaster_category_label",
            qzss_dcr_jma_disaster_category_lookup,
            qzss_dcr_jma_disaster_category_en_lookup, d->disaster_category, false);
        wf_u(out, AZARAC_KEY("information_type"), d->information_type);
        AZARAC_LABEL(out, "information_type_label",
            qzss_dcr_jma_information_type_lookup,
            qzss_dcr_jma_information_type_en_lookup, d->information_type, false);
        // Vn は decodeQzqsm が 1 以外を拒否するため常に 1。それでも「値が無い」と区別できるよう明示的に出す。
        wf_u(out, AZARAC_KEY("version"), d->version);
        writeDHM(out, AZARAC_KEY("report_time"), d->event_time);
        wk(out, AZARAC_KEY("data")); out.print('{');

        // disaster_category で振り分ける（7/13 は仕様で未定義）
        bool serialized = false;
        switch (d->disaster_category) {
#if (AZARAC_ENABLE_EEW)
        case 1:  serialized = serializeEEW(d, out); break;
#endif
#if (AZARAC_ENABLE_HYPOCENTER)
        case 2:  serialized = serializeHypocenter(d, out); break;
#endif
#if (AZARAC_ENABLE_SEISMIC)
        case 3:  serialized = serializeSeismic(d, out); break;
#endif
#if (AZARAC_ENABLE_NANKAI)
        case 4:  serialized = serializeNankai(d, out); break;
#endif
#if (AZARAC_ENABLE_TSUNAMI)
        case 5:  serialized = serializeTsunami(d, out); break;
#endif
#if (AZARAC_ENABLE_NW_PAC_TSUNAMI)
        case 6:  serialized = serializeNwPacTsu(d, out); break;
#endif
#if (AZARAC_ENABLE_VOLCANO)
        case 8:  serialized = serializeVolcano(d, out); break;
#endif
#if (AZARAC_ENABLE_ASH_FALL)
        case 9:  serialized = serializeAshFall(d, out); break;
#endif
#if (AZARAC_ENABLE_WEATHER)
        case 10: serialized = serializeWeather(d, out); break;
#endif
#if (AZARAC_ENABLE_FLOOD)
        case 11: serialized = serializeFlood(d, out); break;
#endif
#if (AZARAC_ENABLE_TYPHOON)
        case 12: serialized = serializeTyphoon(d, out); break;
#endif
#if (AZARAC_ENABLE_MARINE)
        case 14: serialized = serializeMarine(d, out); break;
#endif
        default:
            break;
        }
        if (!serialized) wf_s(out, AZARAC_KEY("note"), AZARAC_KEY("unsupported_category"), /*last=*/true);

        out.print('}');

    } else {
        wf_s(out, AZARAC_KEY("note"), AZARAC_KEY("unsupported_msg_type"), /*last=*/true);
    }

    out.print('}');
}

namespace {
// 固定長バッファへ書く Print。溢れた分は捨てる（バッファ外へは書かない）。
// シリアライザが Print に使うのは write(uint8_t) / write(const char*, size_t)（→ write(const uint8_t*, size_t)）/ print(char) だけで、
// print(char) は実コアもホストのシムも write(uint8_t) へ流すので write の 2 本で足りる。
class BufferPrint : public Print {
public:
    BufferPrint(char* buf, size_t cap) : buf_(buf), cap_(cap) {}

    size_t total() const { return total_; }

    size_t write(uint8_t c) override {
        ++total_;
        if (cap_ != 0 && used_ + 1 < cap_) buf_[used_++] = static_cast<char>(c);
        return 1;
    }

    // 実コアの Print で仮想なのは write(const uint8_t*, size_t) で、write(const char*, size_t) は
    // それへ流す非仮想の中継。上書きするのは前者にし、using で char* 版の名前隠しを防ぐ。
    using Print::write;

    size_t write(const uint8_t* s, size_t size) override {
        total_ += size;
        if (cap_ == 0 || !s) return size;
        const size_t room = (cap_ - 1) - used_;
        const size_t n = (size < room) ? size : room;
        if (n) {
            // n は room 以下に丸めてあり used_ + n <= cap_ - 1 が常に成り立つ。Codacy の memcpy 指摘はこの不変条件を読めないための誤検知
            memcpy(buf_ + used_, s, n);  // nosemgrep
            used_ += n;
        }
        return size;
    }

private:
    char*  buf_;
    size_t cap_;
    size_t used_  = 0;
    size_t total_ = 0;
};
} // namespace

size_t JsonSerializer::serialize(const Message& msg, char* buf, size_t len) {
    if (!buf || len == 0) return 0;
    BufferPrint out(buf, len);
    serialize(msg, out);
    // 入ったバイト数（NUL を除く）。切り詰め時も buf[返り値] == '\0' が成り立つ。
    const size_t written = (out.total() < len - 1) ? out.total() : (len - 1);
    buf[written] = '\0';
    return written;
}

} // namespace internal
} // namespace azaraC
