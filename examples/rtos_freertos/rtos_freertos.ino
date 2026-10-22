// azaraC — examples/rtos_freertos/rtos_freertos.ino
//
// FreeRTOS タスクベースの NMEA / UBX デコーダ
//
// このスケッチは loop() を使わず、FreeRTOS タスクで全ての処理を行います。
// ESP32 系 Arduino コア専用です（xTaskCreatePinnedToCore を使用）。
//
// アーキテクチャ: UART RX Task ──(Message Queue)──▶ Output Task
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

#if !defined(ESP32)
#error "rtos_freertos uses the ESP32 Arduino core (xTaskCreatePinnedToCore)."
#endif

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>
#include <freertos/semphr.h>


// キューサイズ (保持できるメッセージ数)
static constexpr size_t kQueueSize = 16;

static constexpr size_t kUartBufferSize = 256;

// スタックサイズ (ワード単位)
static constexpr uint32_t kRxTaskStackSize = 4096;
static constexpr uint32_t kOutputTaskStackSize = 4096;

// タスク優先度 (高い値 = 高い優先度)
static constexpr UBaseType_t kRxTaskPriority = 2;
static constexpr UBaseType_t kOutputTaskPriority = 1;

// ピン定義例 (ESP32-C3 DevKitM-1)
#define RX_PIN 20
#define TX_PIN 21
#define SERIAL_GNSS Serial1


// メッセージキュー (azaraC::Message をやり取り)
// FreeRTOS のキューはバイトコピーで、Message のコピー ctor/dtor は通らない。payload の
// サブオブジェクトは trivially copyable で所有ポインタを持たないため、この example では
// オブジェクト表現のコピーとして扱う（標準のコピー意味論ではない）。Nankai の
// aggregated_text_ptr は Parser 内部への借用ポインタなのでキューには載せない（processByte を参照）。
static QueueHandle_t g_messageQueue = nullptr;

// Serial は RX タスク（集約済み南海トラフ）と Output タスク（キュー・統計）の両方から書く。
// 1 レコードが途中で混ざらないよう、JSON 1 通・統計行・起動行を丸ごとミューテックスで囲む。
// ヒープ確保禁止のため、FreeRTOS のヒープを消費しない静的確保のミューテックスを使う。
static StaticSemaphore_t g_serialMutexBuffer;
static SemaphoreHandle_t g_serialMutex = nullptr;

// パーサー (NMEA/UBX共用)
static azaraC::Parser g_Parser;

// GNSS 時刻キャッシュ (UBX-NAV-PVT 等から更新)
static uint32_t g_cachedGnssUnixTime = 0;

// 複数タスクから触るため std::atomic。brace-init は ESP32 コア 2.x でコンパイルエラーになり得るので、明示的なデフォルトコンストラクタで初期化する。
static struct Stats {
    std::atomic<uint32_t> Messages;
    std::atomic<uint32_t> queueFullErrors;
    Stats() : Messages(0), queueFullErrors(0) {}
} g_stats;


static void uartRxTask(void* pvParameters);
static void outputTask(void* pvParameters);
static void processByte(uint8_t b, azaraC::Parser& parser);

// 1 通の JSON を、他のタスクの出力と混ざらないように書き出す。
static void printJson(const azaraC::Message& msg) {
    if (xSemaphoreTake(g_serialMutex, portMAX_DELAY) == pdTRUE) {
        azaraC::toJson(msg, Serial);
        Serial.println();
        xSemaphoreGive(g_serialMutex);
    }
}

// タスク開始後の 1 行出力も同じミューテックスで直列化する。
// テンプレートにすると Arduino の prototype 自動生成が `T` を解決できず .ino がコンパイルできないため、F() の型で受ける。
static void printLine(const __FlashStringHelper* text) {
    if (xSemaphoreTake(g_serialMutex, portMAX_DELAY) == pdTRUE) {
        Serial.println(text);
        xSemaphoreGive(g_serialMutex);
    }
}

// Nankai aggregated_text_ptr は Parser 内部バッファへの借用ポインタで、次の feed()/reset() や別イベントの集約で無効化される。
// queue 経由で別タスクへ渡すと dangling になるため、集約済みはこのタスクで直列化して出力し、queue には載せない。
static void processByte(uint8_t b, azaraC::Parser& parser) {
    azaraC::Message msg;
    if (parser.feed(b, msg, g_cachedGnssUnixTime)) {
#if AZARAC_ENABLE_NANKAI
        const azaraC::Mt43Data* mt43 = msg.getMt43();
        const azaraC::NankaiData* nankai = mt43 ? mt43->getNankai() : nullptr;
        if (nankai && nankai->is_aggregated) {
            printJson(msg);
            g_stats.Messages++;
            return;
        }
#endif
        // キューに送信 (待たない)
        if (xQueueSend(g_messageQueue, &msg, 0) != pdTRUE) {
            g_stats.queueFullErrors++;
        } else {
            g_stats.Messages++;
        }
    }
}


static void uartRxTask(void* pvParameters) {
    (void)pvParameters;

    uint8_t Buffer[kUartBufferSize];

    printLine(F("[RTOS] UART RX task started"));

    for (;;) {
        size_t Available = SERIAL_GNSS.available();
        if (Available > 0) {
            size_t toRead = (Available < kUartBufferSize) ? Available : kUartBufferSize;
            for (size_t i = 0; i < toRead; i++) {
                Buffer[i] = static_cast<uint8_t>(SERIAL_GNSS.read());
                processByte(Buffer[i], g_Parser);
            }
        }

        // 少し待機して CPU 使用率を下げる (1ms 待機 = 約1000回/秒のポーリング)
        vTaskDelay(pdMS_TO_TICKS(1));
    }
}


static void outputTask(void* pvParameters) {
    (void)pvParameters;

    azaraC::Message msg;

    printLine(F("[RTOS] Output task started"));

    for (;;) {
        // キューからメッセージを待機 (最大 100ms)
        if (xQueueReceive(g_messageQueue, &msg, pdMS_TO_TICKS(100)) == pdTRUE) {
            printJson(msg);
        }

        // 統計情報の定期出力 (約10秒ごと)
        static TickType_t lastStatsTime = 0;
        TickType_t now = xTaskGetTickCount();
        if ((now - lastStatsTime) >= pdMS_TO_TICKS(10000)) {
            lastStatsTime = now;
            const uint32_t stats = g_stats.Messages.load();
            const uint32_t qfull = g_stats.queueFullErrors.load();
            if (xSemaphoreTake(g_serialMutex, portMAX_DELAY) == pdTRUE) {
                Serial.printf("[STATS] Messages: %lu, Queue Full: %lu\n",
                             static_cast<unsigned long>(stats),
                             static_cast<unsigned long>(qfull));
                xSemaphoreGive(g_serialMutex);
            }
        }
    }
}


void setup() {
    Serial.begin(115200);
    uint32_t start = millis();
    while (!Serial && (millis() - start < 5000)) { delay(10); } // 5秒タイムアウト

    Serial.println(F("================================="));
    Serial.println(F("[azaraC] RTOS FreeRTOS Example"));
    Serial.println(F("NMEA ($QZQSM) or UBX (SFRBX)"));
    Serial.println(F("================================="));

    SERIAL_GNSS.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN);
    Serial.print(F("[INIT] GNSS UART on RX="));
    Serial.println(RX_PIN);

    g_serialMutex = xSemaphoreCreateMutexStatic(&g_serialMutexBuffer);
    if (g_serialMutex == nullptr) {
        Serial.println(F("[ERROR] Failed to create serial mutex!"));
        for (;;) {
            vTaskDelay(pdMS_TO_TICKS(1000));
        }
    }

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
    printLine(F("[INIT] UART RX task created"));

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
        printLine(F("[ERROR] Failed to create output task!"));
        for (;;) {
            vTaskDelay(pdMS_TO_TICKS(1000));
        }
    }
    printLine(F("[INIT] Output task created"));

    printLine(F("[INIT] All tasks started, suspending setup/loop..."));

    // setup/loop タスクをサスペンド (RTOS タスクで全て処理)
    vTaskSuspend(nullptr);
}

// loop() は使わない。RTOS タスクで全て処理し、vTaskSuspend(nullptr) で setup タスクが停止するため到達しない。

void loop() {
    // ここには到達しない
    vTaskDelay(portMAX_DELAY);
}
