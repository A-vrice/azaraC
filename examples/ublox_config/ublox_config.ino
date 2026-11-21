// MCU から u-blox の UART1 を設定し、UBX-RXM-SFRBX を JSON へ変換する。
// 世代を選択: 10 = M10（既定）、9 = F9、8 = M8。対応信号は機種・FW依存。
#define UBLOX_GENERATION 10

#include <azaraC.h>

// GNSS の現在のボーレートに合わせる。この例では受信機の速度は変更しない。
constexpr uint32_t GNSS_BAUD = 9600;
azaraC::Parser parser;
azaraC::Message msg;

// 固定長バッファのみ使用。チェックサム対象は class から payload 末尾まで。
size_t buildUbx(uint8_t id, const uint8_t* payload, uint16_t length,
                uint8_t* frame, size_t capacity) {
    if (capacity < static_cast<size_t>(length) + 8 || (length && !payload)) return 0;
    frame[0] = 0xB5;
    frame[1] = 0x62;
    frame[2] = 0x06;
    frame[3] = id;
    frame[4] = static_cast<uint8_t>(length);
    frame[5] = static_cast<uint8_t>(length >> 8);
    for (uint16_t i = 0; i < length; ++i) frame[6 + i] = payload[i];
    uint8_t a = 0, b = 0;
    for (size_t i = 2; i < static_cast<size_t>(length) + 6; ++i) {
        a += frame[i];
        b += a;
    }
    frame[6 + length] = a;
    frame[7 + length] = b;
    return static_cast<size_t>(length) + 8;
}

// 他の UBX フレームは長さ分読み飛ばす。ACK 自体のチェックサムと対象 ID も確認する。
// 戻り値: 1=ACK、0=NAK、-1=タイムアウト。
int waitAck(uint8_t id) {
    uint8_t state = 0, cls = 0, ackId = 0, a = 0, b = 0, receivedA = 0;
    uint8_t target[2] = {};
    uint16_t length = 0, pos = 0;
    uint32_t start = millis();
    while (millis() - start < 3000) {
        if (!Serial1.available()) { delay(1); continue; }
        uint8_t c = static_cast<uint8_t>(Serial1.read());
        if (state == 0) { if (c == 0xB5) state = 1; continue; }
        if (state == 1) {
            if (c == 0x62) { state = 2; a = b = 0; }
            else state = (c == 0xB5) ? 1 : 0;
            continue;
        }
        if (state <= 6) { a += c; b += a; }
        switch (state) {
        case 2: cls = c; state = 3; break;
        case 3: ackId = c; state = 4; break;
        case 4: length = c; state = 5; break;
        case 5:
            length |= static_cast<uint16_t>(c) << 8;
            pos = 0;
            state = length ? 6 : 7;
            break;
        case 6:
            if (pos < 2) target[pos] = c;
            if (++pos == length) state = 7;
            break;
        case 7: receivedA = c; state = 8; break;
        case 8:
            if (receivedA == a && c == b && cls == 0x05 && length == 2 &&
                target[0] == 0x06 && target[1] == id && ackId <= 1) return ackId;
            state = 0;
            break;
        }
    }
    return -1;
}

bool configure(uint8_t id, const uint8_t* payload, uint16_t length) {
    uint8_t frame[32];
    size_t size = buildUbx(id, payload, length, frame, sizeof(frame));
    if (!size) { Serial.println(F("[u-blox] frame too large")); return false; }
    Serial1.write(frame, size);
    int result = waitAck(id);
    Serial.print(F("[u-blox] CFG 0x"));
    Serial.print(id, HEX);
    if (result == 1) Serial.println(F(": ACK"));
    else if (result == 0) Serial.println(F(": NAK (unsupported key/signal/configuration?)"));
    else Serial.println(F(": timeout (check baud/wiring/UBX protocol)"));
    return result == 1;
}

void setup() {
    Serial.begin(115200);
    uint32_t start = millis();
    while (!Serial && millis() - start < 5000) { delay(10); }
#if defined(ARDUINO_ESP32C3_DEV) || defined(CONFIG_IDF_TARGET_ESP32C3)
    Serial1.begin(GNSS_BAUD, SERIAL_8N1, /*rx=*/20, /*tx=*/21);
#elif defined(CONFIG_IDF_TARGET_ESP32C6) || defined(ARDUINO_ESP32C6_DEV)
    Serial1.begin(GNSS_BAUD, SERIAL_8N1, /*rx=*/4, /*tx=*/5);
#elif defined(ESP32)
    // classic ESP32。S3 / WROVER 等では配線に合わせて変更する。
    Serial1.begin(GNSS_BAUD, SERIAL_8N1, /*rx=*/16, /*tx=*/17);
#else
    Serial1.begin(GNSS_BAUD);
#endif
    delay(1000);  // GNSS の起動待ち（機種に合わせて調整）
#if UBLOX_GENERATION == 10 || UBLOX_GENERATION == 9
    // VALSET version=0, layer=RAM のみ。BBR にも保持する場合は layers を 3 にする。
    // key はリトルエンディアン、値は L / U1 とも 1 バイト。
    const uint8_t payload[] = {
        0, 1, 0, 0,
        0x32, 0x02, 0x91, 0x20, 1,  // CFG-MSGOUT-UBX_RXM_SFRBX_UART1
        0x24, 0x00, 0x31, 0x10, 1,  // CFG-SIGNAL-QZSS_ENA
        0x14, 0x00, 0x31, 0x10, 1   // CFG-SIGNAL-QZSS_L1S_ENA
    };
    configure(0x8A, payload, sizeof(payload));
    delay(500);  // 信号設定による GNSS サブシステム再起動の猶予
#elif UBLOX_GENERATION == 8
    // CFG-MSG: RXM-SFRBX、I2C=0, UART1=1, UART2/USB/SPI=0, reserved=0。
    const uint8_t payload[] = {0x02, 0x13, 0, 1, 0, 0, 0, 0};
    configure(0x01, payload, sizeof(payload));
    Serial.println(F("[u-blox] M8: enable QZSS L1SAIF via CFG-GNSS separately; see examples/README.md"));
#else
#error "UBLOX_GENERATION must be 8, 9 or 10"
#endif
    Serial.println(F("[azaraC] waiting for UBX-RXM-SFRBX (ACK does not guarantee L1S reception)..."));
}

void loop() {
    parser.updateClock();
    while (Serial1.available()) {
        // 未同期時は年を解決しない。GNSS 等の UNIX 時刻があれば第3引数に渡す。
        if (parser.feed(static_cast<uint8_t>(Serial1.read()), msg, 0)) {
            azaraC::toJson(msg, Serial);
            Serial.println();
        }
    }
}
