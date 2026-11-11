// Wi-Fi クライアントとして JSON メッセージを TCP サーバーに送信する例。
// 送信内容は「1 行 JSON」の TCP ストリームで、MQTT プロトコルではない。MQTT ブローカーへ
// 転送するには PubSubClient 等で CONNECT/PUBLISH を実装する必要がある（ポート 1883 に
// 生 JSON を送ってもブローカーは切断する）。HTTP エンドポイントへは別途 POST 実装が必要。
// WAN など信頼できない経路へ転送する場合は WiFiClientSecure（TLS）を使うこと。
//
// 必要な設定:
//   - WIFI_SSID: Wi-Fiネットワーク名
//   - WIFI_PASS: Wi-Fiパスワード
//   - SERVER_HOST: 送信先サーバーアドレス
//   - SERVER_PORT: 送信先ポート番号
//
// 配線 (ESP32-C3 DevKitM-1):
//   GNSS TX → GPIO20 (Serial1 RX)
//   GNSS RX → GPIO21 (Serial1 TX)
//   GND     → GND

#include <azaraC.h>
#include <WiFi.h>

#ifndef WIFI_SSID
  #define WIFI_SSID "YOUR_SSID"
#endif
#ifndef WIFI_PASS
  #define WIFI_PASS "YOUR_PASS"
#endif
#ifndef SERVER_HOST
  #define SERVER_HOST "192.168.1.100"
#endif
#ifndef SERVER_PORT
  #define SERVER_PORT 1883   // 送信先 TCP ポート（1883 は MQTT の慣習だが本例は生 JSON 行を送る）
#endif

azaraC::Parser  parser;
azaraC::Message msg;
WiFiClient wifiClient;

uint32_t lastReconnectAttempt = 0;
uint32_t lastTcpAttempt = 0;
const uint32_t RECONNECT_INTERVAL = 5000;
bool serverConnected = false;

static uint32_t cached_gnss_unix_time = 0;

void connectWiFi() {
    Serial.print(F("[wifi] connecting to "));
    Serial.println(WIFI_SSID);

    WiFi.begin(WIFI_SSID, WIFI_PASS);

    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 20) {
        delay(500);
        Serial.print(F("."));
        attempts++;
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println(F(" OK"));
        Serial.print(F("[wifi] IP: "));
        Serial.println(WiFi.localIP());
    } else {
        Serial.println(F(" FAILED"));
    }
}

// TCPサーバー接続（切断時のみ再接続を試みる）
bool connectServer() {
    if (wifiClient.connected()) {
        serverConnected = true;
        return true;
    }

    Serial.print(F("[tcp] connecting to "));
    Serial.print(SERVER_HOST);
    Serial.print(F(":"));
    Serial.println(SERVER_PORT);

    if (wifiClient.connect(SERVER_HOST, SERVER_PORT)) {
        Serial.println(F("[tcp] connected"));
        serverConnected = true;
        return true;
    } else {
        Serial.println(F("[tcp] connection failed"));
        serverConnected = false;
        return false;
    }
}

class WifiPrint : public Print {
public:
    WiFiClient& client;
    explicit WifiPrint(WiFiClient& c) : client(c) {}
    size_t write(uint8_t c) override { return client.write(c); }
    size_t write(const uint8_t* buf, size_t len) override { return client.write(buf, len); }
};

bool sendJson(const azaraC::Message& msg) {
    if (!wifiClient.connected()) {
        serverConnected = false;
        return false;
    }

    WifiPrint wifiPrint(wifiClient);
    azaraC::toJson(msg, wifiPrint);
    wifiPrint.println();

    return true;
}

// ステータスLED制御。ESP32-C3 DevKitM-1 内蔵 LED は GPIO8 (active low)。
// classic ESP32 の GPIO6-11 は SPI Flash 接続なので GPIO8 を駆動しない（起動不能の恐れ）。
// 他のボードは内蔵 LED のピンが異なるため駆動しない（配線に合わせて変更すること）。
void setStatusLED(bool on) {
#if defined(ARDUINO_ESP32C3_DEV) || defined(CONFIG_IDF_TARGET_ESP32C3)
    static bool initialized = false;
    if (!initialized) {
        pinMode(8, OUTPUT);
        initialized = true;
    }
    digitalWrite(8, on ? LOW : HIGH);
#else
    (void)on;
#endif
}

void setup() {
    Serial.begin(115200);
    uint32_t start = millis();
    while (!Serial && (millis() - start < 5000)) { delay(10); } // 5秒タイムアウト

    Serial.println(F("[azaraC] wifi_client ready"));

    connectWiFi();

#if defined(ARDUINO_ESP32C3_DEV) || defined(CONFIG_IDF_TARGET_ESP32C3)
    Serial1.begin(9600, SERIAL_8N1, /*rx=*/20, /*tx=*/21);
#elif defined(CONFIG_IDF_TARGET_ESP32C6) || defined(ARDUINO_ESP32C6_DEV)
    // ESP32-C6 は GPIO16/17 が UART0（Serial 出力）なので別ピンを使う
    Serial1.begin(9600, SERIAL_8N1, /*rx=*/4, /*tx=*/5);
#elif defined(ESP32)
    // classic ESP32 は GPIO16/17 が UART2 の既定。S3 などは配線に合わせて変更する
    Serial1.begin(9600, SERIAL_8N1, /*rx=*/16, /*tx=*/17);
#else
    Serial1.begin(9600, SERIAL_8N1);
#endif
}

void loop() {
    if (WiFi.status() != WL_CONNECTED) {
        setStatusLED(false);
        serverConnected = false;  // サーバー接続も切断
        uint32_t now = millis();
        if (now - lastReconnectAttempt > RECONNECT_INTERVAL) {
            lastReconnectAttempt = now;
            connectWiFi();
        }
    } else {
        setStatusLED(true);
        // サーバーは切断時のみ、Wi-Fi 接続済みのときだけ再接続を試みる
        if (!serverConnected) {
            uint32_t now = millis();
            if (now - lastTcpAttempt > RECONNECT_INTERVAL) {
                lastTcpAttempt = now;
                connectServer();
            }
        }
    }

    while (Serial1.available()) {
        uint8_t b = static_cast<uint8_t>(Serial1.read());

        // 第3引数に UNIX 時刻を渡すと DCR/DCX 電文の「年」が解決する
        if (parser.feed(b, msg, cached_gnss_unix_time)) {
            azaraC::toJson(msg, Serial);
            Serial.println();

            if (sendJson(msg)) {
                Serial.println(F("[tcp] sent"));
            } else {
                Serial.println(F("[tcp] send failed (not connected)"));
            }
        }
    }
}
