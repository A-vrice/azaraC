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

// 定数定義
static constexpr uint8_t  QZSS_SVID_MIN  = 183;
static constexpr uint8_t  QZSS_SVID_MAX  = 192;
static constexpr uint8_t  MSG_TYPE_MT43  = 43;
static constexpr uint8_t  MSG_TYPE_MT44  = 44;
static constexpr uint32_t HEARTBEAT_MS   = 5000;
static constexpr uint32_t STATS_INTERVAL = 10;  // メッセージ数

//
// この変数は parser.feed() の第3引数として渡され、DCR/DCX電文の「年」を正確に
// 算出するために使用されます。値が0の場合、年は解決されませんが月・日・時・分は
// 正しく取得できます。
//
// ライブラリはUBX-NAV-PVT (0x01 0x07) をパースしないため、ユーザーは別途
// 実装する必要があります。以下は実装例です：
//
//   【方法1: SNTPを使用】
//   // with_sntp.ino の例: time(nullptr) で現在時刻を取得
//   uint32_t now = (time(nullptr) > 0) ? static_cast<uint32_t>(time(nullptr)) : 0;
//
//   【方法2: UBX-NAV-PVTを手動パース】
//   // UBX-NAV-PVT メッセージ (クラス0x01, ID0x07) を受信し、
//   // iTOW (4bytes) + 年月日時分秒フィールドから UNIX時刻を計算して更新
//   // 例:
//   //   if (ubx_class == 0x01 && ubx_id == 0x07) {
//   //       uint16_t year  = (payload[12] << 8) | payload[13];
//   //       uint8_t  month = payload[14];
//   //       uint8_t  day   = payload[15];
//   //       uint8_t  hour  = payload[16];
//   //       uint8_t  min   = payload[17];
//   //       uint8_t  sec   = payload[18];
//   //       cached_gnss_unix_time = to_unix_time(year, month, day, hour, min, sec);
//   //   }
//
//   【方法3: 他の時刻源】
//   // GPSセンテロドライブ、RTC、または他の時刻同期手段から取得
//
// 詳細は with_sntp.ino の「SNTP時刻解決付きパターン」を参照してください。

// ============================================================
// to_unix_time ヘルパー関数
// UTCの年月日時分秒からUNIX時刻（秒）を計算します。
// 簡易実装: 1970年1月1日からの日数を計算して86400を乗算。
// うるう年を考慮した正確な計算を行います。
// ============================================================
static uint32_t to_unix_time(uint16_t year, uint8_t month, uint8_t day,
                             uint8_t hour, uint8_t minute, uint8_t sec) {
    // 月を3月起点に調整（うるう年計算を簡単にするため）
    if (month <= 2) {
        year--;
        month += 12;
    }
    // ユリウス日数からの近似計算
    int32_t a = year / 100;
    int32_t b = 2 - a + (a / 4);
    int32_t jd = (int32_t)(365.25 * (year + 4716)) +
                 (int32_t)(30.6001 * (month + 1)) +
                 day + b - 1524;
    // UNIXエポック (1970-01-01) のユリウス日数 = 2440588
    int32_t days_since_epoch = jd - 2440588;
    return (uint32_t)((days_since_epoch * 86400UL) +
                      (hour * 3600UL) +
                      (minute * 60UL) +
                      sec);
}

static uint32_t cached_gnss_unix_time = 0;

// 統計カウンタ
// Parser::feed() が true を返した時点で msg.valid は保証されるため、
// total_messages は feed() が true を返した回数をカウントする。
// 将来 CRC/フレームエラーを Parser から取得できるようになったら、
// errors カウンタを追加して error rate を算出する設計にできる。
struct Statistics {
    uint32_t total_messages = 0;      // feed() が true を返した回数
    uint32_t mt43_count = 0;          // MT=43 メッセージ数
    uint32_t mt44_count = 0;          // MT=44 メッセージ数
    uint32_t last_svid = 0;           // 最後に受信したSVID
};

Statistics stats;

// 統計情報を表示
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

// メッセージの妥当性チェック
// 注意: Parser::feed() が true を返した時点で msg.valid == true は保証されている。
// この関数は feed() 呼出し前に呼ばれることはないため、msg.valid チェックはデッドコード。
// 将来、invalid なメッセージも取得できる API が追加された時点で復活させる。
bool validateMessage(const azaraC::Message& msg) {
    // SVIDの範囲チェック (QZSS L1S: 183-191)
    if (msg.svid < QZSS_SVID_MIN || msg.svid > QZSS_SVID_MAX) {
        Serial.print(F("[WARN] Unexpected SVID: "));
        Serial.println(msg.svid);
        // 警告のみで処理は続行
    }

    // msg_typeのチェック
    if (msg.msg_type != MSG_TYPE_MT43 && msg.msg_type != MSG_TYPE_MT44) {
        Serial.print(F("[ERROR] Unknown msg_type: "));
        Serial.println(msg.msg_type);
        return false;
    }

    return true;
}

// MT=43 メッセージの詳細バリデーション
bool validateMt43(const azaraC::Message& msg) {
    const azaraC::Mt43Data* mt43 = msg.getMt43();
    if (!mt43) {
        Serial.println(F("[ERROR] Failed to get MT43 data"));
        return false;
    }

    // disaster_categoryの範囲チェック
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

    // 日付の妥当性チェック
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

// MT=44 メッセージの詳細バリデーション
bool validateMt44(const azaraC::Message& msg) {
    const azaraC::Mt44Data* mt44 = msg.getMt44();
    if (!mt44) {
        Serial.println(F("[ERROR] Failed to get MT44 data"));
        return false;
    }

    // service_kindのチェック
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


        // 第3引数にUNIX時刻を渡すことで、DCR/DCX電文の「年」を正確に算出できます
        if (parser.feed(b, msg, cached_gnss_unix_time)) {
            // feed() == true で msg.valid は保証される
            stats.total_messages++;
            stats.last_svid = msg.svid;

            // 基本的な妥当性チェック (SVID / msg_type 範囲チェック)
            if (!validateMessage(msg)) {
                Serial.println(F("[ERROR] Message validation failed"));
                continue;
            }

            // メッセージタイプ別の処理
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

            // JSON出力
            azaraC::toJson(msg, Serial);
            Serial.println();

            // 統計表示
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
