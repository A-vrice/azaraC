// azaraC — examples/error_handling/error_handling.ino
//
// エラーハンドリングと状態監視の例
// CRCエラー、フレームエラーの統計を表示する
// ※ 重複排除はParser内部で自動的に行われるため、example側では検出できません
//
// Wiring (ESP32-C3 DevKitM-1):
//   GNSS TX → GPIO20 (Serial1 RX)
//   GNSS RX → GPIO21 (Serial1 TX)
//   GND     → GND

#include <azaraC.h>


azaraC::Parser  parser;
azaraC::Message msg;

static constexpr uint8_t  QZSS_SVID_MIN  = 181;  // PRN181–191（実データには ID 53/54 = PRN181/182 もある）
static constexpr uint8_t  QZSS_SVID_MAX  = 191;
static constexpr uint8_t  MSG_TYPE_MT43  = 43;
static constexpr uint8_t  MSG_TYPE_MT44  = 44;
static constexpr uint32_t HEARTBEAT_MS   = 5000;
static constexpr uint32_t STATS_INTERVAL = 10;  // メッセージ数

//
// この変数は parser.feed() の第3引数で、DCR/DCX 電文の「年」の算出に使われる。0 なら年は解決されないが月・日・時・分は正しく取れる。ライブラリは UBX-NAV-PVT (0x01 0x07) をパースしないため、時刻源はユーザーが用意する:
//   - SNTP: uint32_t now = (time(nullptr) > 0) ? static_cast<uint32_t>(time(nullptr)) : 0;  (with_sntp.ino)
//   - UBX-NAV-PVT を手動パース: payload[12..13]=year, [14]=month, [15]=day, [16]=hour, [17]=min, [18]=sec
//   - RTC など他の同期手段
//

// UTC の年月日時分秒 → UNIX 秒。Decoder::days_from_civil と同等の Howard Hinnant 整数演算のみ（float 不使用、AVR で軽量）。
static uint32_t to_unix_time(uint16_t year, uint8_t month, uint8_t day,
                             uint8_t hour, uint8_t minute, uint8_t sec) {
    uint32_t y = year;
    uint32_t m = month;
    uint32_t d = day;
    y -= (m <= 2);
    uint32_t era = y / 400;
    uint32_t yoe = y - era * 400;
    uint32_t doy = (153 * (m + (m > 2 ? -3 : 9)) + 2) / 5 + d - 1;
    uint32_t doe = yoe * 365 + yoe / 4 - yoe / 100 + doy;
    int32_t days_since_epoch = (int32_t)(era * 146097 + doe - 719468);
    return (uint32_t)((uint32_t)days_since_epoch * 86400UL +
                      (uint32_t)hour * 3600UL +
                      (uint32_t)minute * 60UL +
                      (uint32_t)sec);
}

static uint32_t cached_gnss_unix_time = 0;

// Parser::feed() が true を返した時点で msg.valid は保証されるため、total_messages は feed() の成功回数。将来 CRC/フレームエラーが API から取れるようになったら、errors を足して error rate を算出する。
struct Statistics {
    uint32_t total_messages = 0;
    uint32_t mt43_count = 0;          // MT=43 メッセージ数
    uint32_t mt44_count = 0;          // MT=44 メッセージ数
    uint32_t last_svid = 0;           // 最後に受信したSVID
};

Statistics stats;

void printStatistics() {
    Serial.println(F("=== azaraC Statistics ==="));
    Serial.print(F("Total messages:    "));
    Serial.println(stats.total_messages);
    Serial.print(F("MT=43 (QZQSM):     "));
    Serial.println(stats.mt43_count);
    Serial.print(F("MT=44 (DCX):       "));
    Serial.println(stats.mt44_count);
    Serial.print(F("Last SVID:         "));
    Serial.println(stats.last_svid);
    Serial.println(F("========================"));
}

// 注意: Parser::feed() が true を返した時点で msg.valid == true は保証されている。この関数は feed() 呼出し前に呼ばれないため msg.valid チェックはデッドコード。invalid も取れる API ができたら復活させる。
bool validateMessage(const azaraC::Message& msg) {
    // SVIDの範囲チェック (QZSS L1S PRN: 181-191)
    if (msg.svid < QZSS_SVID_MIN || msg.svid > QZSS_SVID_MAX) {
        Serial.print(F("[WARN] Unexpected SVID: "));
        Serial.println(msg.svid);
        // 警告のみで処理は続行
    }

    if (msg.msg_type != MSG_TYPE_MT43 && msg.msg_type != MSG_TYPE_MT44) {
        Serial.print(F("[ERROR] Unknown msg_type: "));
        Serial.println(msg.msg_type);
        return false;
    }

    return true;
}

bool validateMt43(const azaraC::Message& msg) {
    const azaraC::Mt43Data* mt43 = msg.getMt43();
    if (!mt43) {
        Serial.println(F("[ERROR] Failed to get MT43 data"));
        return false;
    }

    bool valid_category = false;
    switch (mt43->disaster_category) {
        case 1: case 2: case 3: case 4: case 5: case 6:
        case 8: case 9: case 10: case 11: case 12: case 14:
            valid_category = true;
            break;
        default:
            Serial.print(F("[WARN] Unknown disaster_category: "));
            Serial.println(mt43->disaster_category);
            break;
    }

    if (mt43->event_time.month > 12) {
        Serial.print(F("[WARN] Invalid month: "));
        Serial.println(mt43->event_time.month);
    }
    if (mt43->event_time.day > 31) {
        Serial.print(F("[WARN] Invalid day: "));
        Serial.println(mt43->event_time.day);
    }
    if (mt43->event_time.hour > 23) {
        Serial.print(F("[WARN] Invalid hour: "));
        Serial.println(mt43->event_time.hour);
    }
    if (mt43->event_time.minute > 59) {
        Serial.print(F("[WARN] Invalid minute: "));
        Serial.println(mt43->event_time.minute);
    }

    return true;
}

bool validateMt44(const azaraC::Message& msg) {
    const azaraC::Mt44Data* mt44 = msg.getMt44();
    if (!mt44) {
        Serial.println(F("[ERROR] Failed to get MT44 data"));
        return false;
    }

    switch (mt44->service_kind) {
        case azaraC::Mt44ServiceKind::LAlert:
        case azaraC::Mt44ServiceKind::JAlert:
        case azaraC::Mt44ServiceKind::LocalGovernment:
        case azaraC::Mt44ServiceKind::OutsideJapan:
        case azaraC::Mt44ServiceKind::NullMessage:
            break;
        default:
            Serial.print(F("[WARN] Unknown service_kind: "));
            Serial.println(static_cast<int>(mt44->service_kind));
            break;
    }

    return true;
}

void setup() {
    Serial.begin(115200);
    uint32_t start = millis();
    while (!Serial && (millis() - start < 5000)) { delay(10); } // 5秒タイムアウト

    #if defined(ESP32)
        Serial1.begin(9600, SERIAL_8N1, /*rx=*/20, /*tx=*/21);
    #else
        Serial1.begin(9600, SERIAL_8N1);
    #endif
    Serial.println(F("[azaraC] error_handling ready"));
    Serial.println(F("Waiting for QZSS messages..."));
}

void loop() {
    while (Serial1.available()) {
        uint8_t b = static_cast<uint8_t>(Serial1.read());


        // 第3引数に UNIX 時刻を渡すと DCR/DCX 電文の「年」が解決する
        if (parser.feed(b, msg, cached_gnss_unix_time)) {
            // feed() == true で msg.valid は保証される
            stats.total_messages++;
            stats.last_svid = msg.svid;

            if (!validateMessage(msg)) {
                Serial.println(F("[ERROR] Message validation failed"));
                continue;
            }

            if (msg.msg_type == MSG_TYPE_MT43) {
                stats.mt43_count++;
                if (!validateMt43(msg)) {
                    Serial.println(F("[WARN] MT43 validation warning"));
                }
            } else if (msg.msg_type == MSG_TYPE_MT44) {
                stats.mt44_count++;
                if (!validateMt44(msg)) {
                    Serial.println(F("[WARN] MT44 validation warning"));
                }
            }

            azaraC::toJson(msg, Serial);
            Serial.println();

            if (stats.total_messages % STATS_INTERVAL == 0) {
                printStatistics();
            }
        }
    }
    // ハートビート出力（受信がない場合）
    static uint32_t last_heartbeat = 0;
    uint32_t now = millis();
    if (now - last_heartbeat > HEARTBEAT_MS) {
        last_heartbeat = now;
        Serial.print(F("[INFO] Heartbeat - Total: "));
        Serial.println(stats.total_messages);
    }
}
