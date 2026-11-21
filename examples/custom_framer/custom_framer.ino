// 独自フレーマを差し込む例（Parser(IFramer&)）。
//
// 受信機が NMEA $QZQSM でも UBX-RXM-SFRBX でもない場合、IFramer を実装して
// 1 フレーム分の 250 bit と SVID を Parser に渡せます。
// ここでは次の 1 行テキストを 1 フレームとして扱います（デバッグ用の簡易プロトコル）。
//
//   AZC,<svid>,<64 桁の 16 進>\n
//   例: AZC,184,5300...  （32 バイト = 250 bit + 6 bit のパディング）
//
// IFramer の契約:
//   - feed() はフレームが完成したときだけ true を返し、Frame の svid と bits[32] を
//     全フィールド埋めてから返す（部分書きのまま true を返すと全ゼロのフレームとして復号される）
//   - false のときは out を書かなくてよい
//   - reset() は受信途中の状態を捨てる
// 独自フレーマを渡した Parser は UBX/NMEA の自動判定を行いません（このフレーマだけを使います）。

#include <azaraC.h>

class AzcLineFramer : public azaraC::IFramer {
public:
    bool feed(uint8_t byte, azaraC::Frame& out) override {
        if (byte == '\r') return false;
        if (byte != '\n') {
            if (len_ < sizeof(buf_)) buf_[len_++] = static_cast<char>(byte);
            return false;
        }
        const bool ok = parseLine(out);
        len_ = 0;
        return ok;
    }

    void reset() override { len_ = 0; }

private:
    // "AZC,<svid>,<64 hex>" を Frame へ。壊れていれば false。
    bool parseLine(azaraC::Frame& out) {
        buf_[len_] = '\0';
        if (len_ < 6 || strncmp(buf_, "AZC,", 4) != 0) return false;

        const char* p = buf_ + 4;
        uint16_t svid = 0;
        uint8_t digits = 0;
        while (*p >= '0' && *p <= '9') {
            svid = static_cast<uint16_t>(svid * 10 + (*p - '0'));
            if (++digits > 3 || svid > 255) return false;
            ++p;
        }
        if (digits == 0 || *p != ',') return false;
        ++p;

        // 32 バイト分の 16 進（64 桁）を要求する。
        if (strlen(p) != 64) return false;
        for (uint8_t i = 0; i < 32; ++i) {
            const int hi = hexValue(p[i * 2]);
            const int lo = hexValue(p[i * 2 + 1]);
            if (hi < 0 || lo < 0) return false;
            out.bits[i] = static_cast<uint8_t>((hi << 4) | lo);
        }
        out.svid = static_cast<uint8_t>(svid);
        return true;
    }

    static int hexValue(char c) {
        if (c >= '0' && c <= '9') return c - '0';
        if (c >= 'a' && c <= 'f') return c - 'a' + 10;
        if (c >= 'A' && c <= 'F') return c - 'A' + 10;
        return -1;
    }

    char   buf_[80] = {};
    size_t len_ = 0;
};

AzcLineFramer framer;
azaraC::Parser  parser(framer);   // カスタムフレーマ経路
azaraC::Message msg;

void setup() {
    Serial.begin(115200);
    uint32_t start = millis();
    while (!Serial && (millis() - start < 5000)) { delay(10); }
    Serial.println(F("[azaraC] custom framer ready: AZC,<svid>,<64 hex>"));
}

void loop() {
    parser.updateClock();   // 無受信期間でも 32 bit 時刻の折り返しを観測する

    while (Serial.available()) {
        // 報告時刻（年解決用）。SNTP や GNSS の $GPRMC から更新する想定。未同期は 0。
        if (parser.feed(static_cast<uint8_t>(Serial.read()), msg, 0)) {
            azaraC::toJson(msg, Serial);
            Serial.println();
        }
    }
}
