// azaraC — examples/rtos_freertos/rtos_freertos.ino
//
// FreeRTOS タスクベースの NMEA / UBX デコーダ
//
// このスケッチは loop() を使わず、FreeRTOS タスクで全ての処理を行います。
// RTOS 対応の Arduino 環境 (ESP32, ESP32-S3, ESP32-C3 等) で動作します。
//
// アーキテクチャ:
//   ┌─────────────────┐     ┌─────────────┐     ┌─────────────────┐
//   │  UART RX Task   │────▶│  Message    │────▶│  Output Task    │
//   │  (Serial受信)    │     │  Queue      │     │  (JSON出力)      │
//   └─────────────────┘     └─────────────┘     └─────────────────┘
//
// Wiring (例:ESP32-C3 DevKitM-1):
//   GNSS TX → GPIO20 (Serial1 RX)
//   GND             → GND
//
// config (u-blox):
//   CFG-MSGOUT-NMEA_ID_GGA_UART1 = 1 //NMEAの場合
//   CFG-MSGOUT-UBX_RXM_SFRBX_UART1 = 1 //UBXの場合 
//   CFG-SIGNAL-QZSS_L1S_ENA      = 1
//   CFG-UART1-BAUDRATE            = 9600
//

#include <azaraC.h>
#include <atomic>

#if defined(ESP32) || defined(ESP32S3) || defined(ESP32C3) || defined(ESP32C6)
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>
#else
// ESP32 以外の FreeRTOS 対応ボード用
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#endif

// 設定

// キューサイズ (保持できるメッセージ数)
static constexpr size_t kQueueSize = 16;

// UART 受信バッファサイズ
static constexpr size_t kUartBufferSize = 256;

// タスクスタックサイズ (ワード単位)
static constexpr uint32_t kRxTaskStackSize = 4096;
static constexpr uint32_t kOutputTaskStackSize = 4096;

// タスク優先度 (高い値 = 高い優先度)
static constexpr UBaseType_t kRxTaskPriority = 2;
static constexpr UBaseType_t kOutputTaskPriority = 1;

// ピン定義例 (ESP32-C3 DevKitM-1)
#define RX_PIN 20
#define TX_PIN 21
#define SERIAL_GNSS Serial1

// グローバル変数

// メッセージキュー (azaraC::Message をやり取り)
static QueueHandle_t g_messageQueue = nullptr;

// パーサー (NMEA/UBX共用)
static azaraC::Parser g_Parser;

// GNSS 時刻キャッシュ (UBX-NAV-PVT 等から更新)
static uint32_t g_cachedGnssUnixTime = 0;

// 統計カウンタ
// std::atomic を使用して複数タスクからのアクセスを安全にする
// brace-initialization は Arduino 環境 (ESP32 コア 2.x) でコンパイルエラーの
// 可能性があるため、明示的なデフォルトコンストラクタで初期化する。
static struct Stats {
    std::atomic<uint32_t> Messages;
    std::atomic<uint32_t> queueFullErrors;
    Stats() : Messages(0), queueFullErrors(0) {}
} g_stats;

// 関数プロトタイプ

static void uartRxTask(void* pvParameters);
static void outputTask(void* pvParameters);
static void processByte(uint8_t b, azaraC::Parser& parser);

// バイト処理
// Note: Nankai aggregated_text_ptr は Parser 内部バッファへの借用ポインタ
// （次の feed()/reset() や別イベントの集約で無効化される）。queue 経由で
// 別タスクへ渡す前にコピー/シリアライズしないと dangling になるため、
// is_aggregated の場合はここで JSON にシリアライズしてから送信するか、
// 下記のように aggregated テキストをコピーしてから enqueue すること。
static void processByte(uint8_t b, azaraC::Parser& parser) {
    azaraC::Message msg;
    if (parser.feed(b, msg, g_cachedGnssUnixTime)) {
#if AZARAC_ENABLE_NANKAI
        // Nankai 集約メッセージは aggregated_text_ptr が Parser 内部バッファへの
        // 借用ポインタ (次の feed()/reset()/集約再利用で無効化)。
        // 本サンプルは Message をそのままキューへ投入しており、outputTask 側の
        // toJson() は出力時にこの借用ポインタを参照する (内部コピーしない)。
        // RX タスクと出力タスクの並行性により、出力前にバッファが再利用されると
        // text_utf8 が破損し得る。厳密には xQueueSend() 前に toJson() で文字列化
        // するか、集約テキストを所有コピーしたキュー要素を送ること。
#endif
        // キューに送信 (待たない)
        if (xQueueSend(g_messageQueue, &msg, 0) != pdTRUE) {
            g_stats.queueFullErrors++;
        } else {
            g_stats.Messages++;
        }
    }
}

// UART RX タスク

static void uartRxTask(void* pvParameters) {
    (void)pvParameters;

    uint8_t Buffer[kUartBufferSize];

    Serial.println(F("[RTOS] UART RX task started"));

    for (;;) {
        // データ処理 - 1回のループで読み取りと処理を行う
        size_t Available = SERIAL_GNSS.available();
        if (Available > 0) {
            size_t toRead = (Available < kUartBufferSize) ? Available : kUartBufferSize;
            for (size_t i = 0; i < toRead; i++) {
                Buffer[i] = static_cast<uint8_t>(SERIAL_GNSS.read());
                processByte(Buffer[i], g_Parser);  // 読み取りと処理を1回のループで
            }
        }

        // 少し待機して CPU 使用率を下げる
        // 1ms 待機 = 約1000回/秒のポーリング
        vTaskDelay(pdMS_TO_TICKS(1));
    }
}

// 出力タスク

static void outputTask(void* pvParameters) {
    (void)pvParameters;

    azaraC::Message msg;

    Serial.println(F("[RTOS] Output task started"));

    for (;;) {
        // キューからメッセージを待機 (最大 100ms)
        if (xQueueReceive(g_messageQueue, &msg, pdMS_TO_TICKS(100)) == pdTRUE) {
            // JSON を Serial (USB) に出力
            azaraC::toJson(msg, Serial);
            Serial.println();
        }

        // 統計情報の定期出力 (約10秒ごと)
        static TickType_t lastStatsTime = 0;
        TickType_t now = xTaskGetTickCount();
        if ((now - lastStatsTime) >= pdMS_TO_TICKS(10000)) {
            lastStatsTime = now;
            const uint32_t stats = g_stats.Messages.load();
            const uint32_t qfull = g_stats.queueFullErrors.load();
            Serial.printf("[STATS] Messages: %lu, Queue Full: %lu\n",
                         static_cast<unsigned long>(stats),
                         static_cast<unsigned long>(qfull));
        }
    }
}

// setup()

void setup() {
    // USB Serial 初期化
    Serial.begin(115200);
    uint32_t start = millis();
    while (!Serial && (millis() - start < 5000)) { delay(10); } // 5秒タイムアウト

    Serial.println(F("================================="));
    Serial.println(F("[azaraC] RTOS FreeRTOS Example"));
    Serial.println(F("NMEA ($QZQSM) or UBX (SFRBX)"));
    Serial.println(F("================================="));

    // UART 初期化
#if defined(ESP32)
    SERIAL_GNSS.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN);
#else
    SERIAL_GNSS.begin(9600, SERIAL_8N1);
#endif
    Serial.print(F("[INIT] GNSS UART on RX="));
    Serial.println(RX_PIN);

    // メッセージキュー作成
    g_messageQueue = xQueueCreate(kQueueSize, sizeof(azaraC::Message));
    if (g_messageQueue == nullptr) {
        Serial.println(F("[ERROR] Failed to create message queue!"));
        // エラー時は停止
        for (;;) {
            vTaskDelay(pdMS_TO_TICKS(1000));
        }
    }
    Serial.print(F("[INIT] Message queue created (size="));
    Serial.print(kQueueSize);
    Serial.println(F(")"));

    // UART RX タスク作成
    BaseType_t result = xTaskCreatePinnedToCore(
        uartRxTask,           // タスク関数
        "UART_RX",            // タスク名
        kRxTaskStackSize,     // スタックサイズ
        nullptr,              // パラメータ
        kRxTaskPriority,      // 優先度
        nullptr,              // タスクハンドル
        0                     // コア0
    );
    if (result != pdPASS) {
        Serial.println(F("[ERROR] Failed to create UART RX task!"));
        for (;;) {
            vTaskDelay(pdMS_TO_TICKS(1000));
        }
    }
    Serial.println(F("[INIT] UART RX task created"));

    // 出力タスク作成
    result = xTaskCreatePinnedToCore(
        outputTask,              // タスク関数
        "OUTPUT",                // タスク名
        kOutputTaskStackSize,    // スタックサイズ
        nullptr,                 // パラメータ
        kOutputTaskPriority,     // 優先度
        nullptr,                 // タスクハンドル
        tskNO_AFFINITY           // コアアフィニティなし（スケジューラに任せる）
    );
    if (result != pdPASS) {
        Serial.println(F("[ERROR] Failed to create output task!"));
        for (;;) {
            vTaskDelay(pdMS_TO_TICKS(1000));
        }
    }
    Serial.println(F("[INIT] Output task created"));

    Serial.println(F("[INIT] All tasks started, suspending setup/loop..."));

    // setup/loop タスクをサスペンド (RTOS タスクで全て処理)
    vTaskSuspend(nullptr);
}

// loop()
// RTOS タスクで全ての処理を行うため、loop() は使用しません。
// vTaskSuspend(nullptr) で setup タスクが停止されるため、
// この関数は実際には呼ばれません。

void loop() {
    // ここには到達しない
    vTaskDelay(portMAX_DELAY);
}
