# AzaraC アーキテクチャドキュメント

## 概要

AzaraCは準天頂衛星システム（QZSS）のL1S信号から災危通報メッセージをデコードするArduinoライブラリです。本ドキュメントでは、ライブラリの内部アーキテクチャと設計思想について解説します。

## ファイル構成

```
src/
├── azaraC.h              # メインヘッダ（azaraC_config.h → Message.h → Parser.h）
├── azaraC_config.h       # コンパイル時設定マクロ（軽量、定義ファイルからも参照）
├── Message.h             # Message / Mt43Data / Mt44Data 構造体
├── Mt43Data.h            # MT=43 タグ付き共用体（災害カテゴリ別データ）
├── Mt44Data.h            # MT=44 生データ構造体（配列化されたB4 D1-D36）
├── Parser.h / Parser.cpp # メインパーサー（postDecode() で重複除去を一元化）
├── decoder/
│   ├── Decoder.cpp       # 共通デコード処理（CRC, ビット抽出, 時間解決）
│   ├── DecoderDcx.cpp    # MT=44 DCX/CAMF デコード
│   └── DecoderQzqsm.cpp  # MT=43 QZQSM デコード
├── framer/
│   ├── UbxFramer.cpp     # UBX-RXM-SFRBX フレーマー
│   └── NmeaFramer.cpp    # NMEA $QZQSM フレーマー
├── json/
│   ├── JsonWriter.cpp    # プリミティブJSONライター
│   ├── JsonSerializer.cpp      # 直列化エントリポイント
│   ├── JsonSerializerDcx.cpp   # MT=44 JSON生成
│   └── JsonSerializerQzqsm.cpp # MT=43 JSON生成
├── internal/
│   ├── DcxHelper.h/cpp   # DCX デコード補助関数
│   ├── Dedup.h/cpp       # 重複除去リングバッファ
│   ├── NankaiPageBuffer.h # 南海トラフページ集約
│   ├── JsonSerializer.h  # 直列化インターフェース
│   └── ... (その他内部ヘッダ)
└── definition/
    ├── _index.h           # 全103定義テーブルを集約
    └── qzss_*.h           # 自動生成の定義ルックアップ関数
```

## システム構成図

```
┌─────────────────────────────────────────────────────────────────────────┐
│                            GNSS モジュール                              │
│                    (u-blox, Furuno, Sony 等)                            │
└──────────────────────────────┬──────────────────────────────────────────┘
                               │ シリアル通信 (UART)
                               │ NMEA $QZQSM / UBX-RXM-SFRBX
                               ▼
┌──────────────────────────────────────────────────────────────────────────┐
│                            Parser                                       │
│  ┌────────────────────────────────────────────────────────────────────┐  │
│  │                     フレーマー自動判別                              │  │
│  │  ┌─────────────┐  ┌──────────────┐  ┌──────────────────────────┐  │  │
│  │  │ UbxFramer   │  │ NmeaFramer   │  │ CustomFramer (IFramer)   │  │  │
│  │  │ (UBX-RXM-   │  │ ($QZQSM)     │  │ (Sony, Furuno 等)        │  │  │
│  │  │  SFRBX)     │  │              │  │                          │  │  │
│  │  └──────┬──────┘  └──────┬───────┘  └────────────┬─────────────┘  │  │
│  │         └────────────────┼───────────────────────┘                │  │
│  │                          ▼                                        │  │
│  │                    Frame (ビット列)                                │  │
│  └──────────────────────────┬────────────────────────────────────────┘  │
│                             ▼                                           │
│  ┌────────────────────────────────────────────────────────────────────┐  │
│  │                        Decoder                                     │  │
│  │  ┌──────────────────────────────────────────────────────────────┐  │  │
│  │  │ CRC-24Q 検証                                                  │  │  │
│  │  └──────────────────────────┬───────────────────────────────────┘  │  │
│  │                             ▼                                      │  │
│  │  ┌──────────────────────────────────────────────────────────────┐  │  │
│  │  │ msg_type による分岐                                            │  │  │
│  │  │  ┌─────────────────────┐  ┌────────────────────────────────┐ │  │  │
│  │  │  │ MT=43 (QZQSM)       │  │ MT=44 (DCX/CAMF)              │ │  │  │
│  │  │  │  ┌───────────────┐  │  │  ┌──────────────────────────┐ │ │  │  │
│  │  │  │  │ EEW           │  │  │  │ A1-A13 CAMF フィールド   │ │ │  │  │
│  │  │  │  │ Hypocenter    │  │  │  │ EX1-EX11 拡張フィールド  │ │ │  │  │
│  │  │  │  │ Seismic       │  │  │  │ A17 B1-B4 拡張 (v1.1)   │ │ │  │  │
│  │  │  │  │ Nankai        │  │  │  └──────────────────────────┘ │ │  │  │
│  │  │  │  │ Tsunami       │  │  └────────────────────────────────┘ │  │  │
│  │  │  │  │ Volcano       │  │                                      │  │  │
│  │  │  │  │ Ash Fall      │  │                                      │  │  │
│  │  │  │  │ Weather       │  │                                      │  │  │
│  │  │  │  │ Flood         │  │                                      │  │  │
│  │  │  │  │ Typhoon       │  │                                      │  │  │
│  │  │  │  │ Marine        │  │                                      │  │  │
│  │  │  │  └───────────────┘  │                                      │  │  │
│  │  │  └─────────────────────┘                                      │  │  │
│  │  └──────────────────────────┬───────────────────────────────────┘  │  │
│  │                             ▼                                      │  │
│  │                        Message                                     │  │
│  └──────────────────────────┬────────────────────────────────────────┘  │
│                             ▼                                           │
│  ┌────────────────────────────────────────────────────────────────────┐  │
│  │                      DedupFilter (重複除去)                         │  │
│  │              {svid, msg_type, crc24} によるリングバッファ            │  │
│  └──────────────────────────┬────────────────────────────────────────┘  │
│                             ▼                                           │
│  ┌────────────────────────────────────────────────────────────────────┐  │
│  │                   NankaiPageBuffer (南海トラフ)                     │  │
│  │              複数ページメッセージの集約処理                          │  │
│  └──────────────────────────┬────────────────────────────────────────┘  │
│                             ▼                                           │
│                     出力 (Message)                                      │
└──────────────────────────────┬──────────────────────────────────────────┘
                               │
                               ▼
┌──────────────────────────────────────────────────────────────────────────┐
│                      JsonSerializer                                      │
│  ┌────────────────────────────────────────────────────────────────────┐  │
│  │ Message → JSON → Print& (Serial, WiFiClient, 等)                  │  │
│  └────────────────────────────────────────────────────────────────────┘  │
└──────────────────────────────────────────────────────────────────────────┘
```

## コンポーネント詳細

### 1. Parser (パーサー)

[`Parser`](src/Parser.h)はライブラリのメインエントリーポイントです。以下の責務を持ちます:

- **フレーマー自動判別**: 入力バイトストリームからUBX/NMEAを自動判別
- **メッセージデコード**: フレームの復号とCRC検証
- **重複除去 + 南海トラフページ集約**: 統合された `postDecode()` メソッドが、Nankai集約・重複チェック・メッセージ出力のパイプラインを一元管理

#### 内部フロー

```
feed(byte)
  │
  ├─ Framerでフレーム化
  │
  ├─ Decoder.decode() → Message
  │
  └─ postDecode(decoded, out)
        │
        ├─ Nankai集約処理（MT=43 カテゴリ4のみ）
        ├─ DedupFilter で重複チェック
        └─ out = decoded（または集約結果）
```

```cpp
// 基本的な使用例
azaraC::Parser parser;
azaraC::Message msg;

void loop() {
    while (Serial1.available()) {
        if (parser.feed(Serial1.read(), msg)) {
            // 新しいメッセージを受信
            azaraC::toJson(msg, Serial);
        }
    }
}
```

### 2. Framer (フレーマー)

フレーマーはシリアルバイトストリームからメッセージフレームを抽出します。[`IFramer`](include/internal/IFramer.h)インターフェースを実装します:

| フレーマー | プロトコル | 対応デバイス |
|-----------|-----------|-------------|
| [`UbxFramer`](include/internal/UbxFramer.h) | UBX-RXM-SFRBX | u-blox M10, ZED-F9P |
| [`NmeaFramer`](include/internal/NmeaFramer.h) | NMEA $QZQSM | Furuno GT-87, 汎用GNSS |
| Custom (IFramer) | 任意 | Sony, その他 |

#### フレーマー自動判別アルゴリズム

```
バイト入力 → UBX同期文字(0xB5 0x62)チェック
           → NMEA '$'文字チェック
           → 判別成功: 該当フレーマーで処理
           → 判別失敗: 次のバイトで再試行
```

### 3. Decoder (デコーダー)

[`Decoder`](include/internal/Decoder.h)はビット列からメッセージフィールドを抽出します:

#### 共通処理
- **CRC-24Q検証**: IS-QZSS-L1S §3.2.8準拠
- **ビット抽出**: MSB-first, 0-indexed
- **日時解決**: UNIX時刻ベースの年月補正

#### MT=43 (QZQSM) サブデコーダー

| 災害カテゴリ | デコーダー関数 | 規格セクション |
|-------------|--------------|---------------|
| 1: EEW | `decodeEEW` | §5.1.2.3.1 |
| 2: 震源情報 | `decodeHypocenter` | §5.1.2.3.2 |
| 3: 震度情報 | `decodeSeismic` | §5.1.2.3.3 |
| 4: 南海トラフ | `decodeNankai` | §5.1.2.3.4 |
| 5: 津波警報 | `decodeTsunami` | §5.1.2.3.5 |
| 6: 北太平洋津波 | `decodeNwPacTsu` | §5.1.2.3.6 |
| 8: 火山情報 | `decodeVolcano` | §5.1.2.3.7 |
| 9: 降灰情報 | `decodeAshFall` | §5.1.2.3.8 |
| 10: 気象警報 | `decodeWeather` | §5.1.2.3.9 |
| 11: 洪水警報 | `decodeFlood` | §5.1.2.3.10 |
| 12: 台風情報 | `decodeTyphoon` | §5.1.2.3.11 |
| 14: 海上警報 | `decodeMarine` | §5.1.2.3.12 |

#### MT=44 (DCX/CAMF) デコーダー

MT=44は階層構造されたCAMFフォーマットを解析します:

```
PAB(8) | MT(8) | SD(10) | CAMF(A1-A13) | EX(EX1-EX11) | Reserved | CRC24
```

サービス種別による分岐:
- **L-Alert**: A2=111 (Japan) & A3=1-4
- **J-Alert**: A2=111 (Japan) & A3=0
- **地方自治体**: A2=111 (Japan) & A3=5-31
- **国外**: A2≠111

### 4. DedupFilter (重複除去)

[`DedupFilter`](include/internal/DedupFilter.h)はリングバッファによる重複除去を行います:

```cpp
// 重複判定キー
struct DedupKey {
    uint8_t  svid;      // 衛星ID
    uint8_t  msg_type;  // メッセージタイプ (43/44)
    uint32_t crc24;     // CRC-24Q値
};
```

デフォルトスロット数は8。複数衛星を受信する場合には増やすことを推奨します:

```cpp
#define AZARAC_DEDUP_SLOTS 32
#include <azaraC.h>
```

### 5. NankaiPageBuffer (南海トラフページ集約)

南海トラフ地震メッセージは最大63ページに分割されます。[`NankaiPageBuffer`](include/internal/NankaiPageBuffer.h)は複数ページを集約して完全なメッセージを再構成します:

```
ページ1 (18バイト本文 + ページ番号/総ページ数)
ページ2 (18バイト本文 + ページ番号/総ページ数)
...
ページN (18バイト本文 + ページ番号/総ページ数)
         ↓
    集約バッファ (可変長、最大1134バイト)
```

**メモリ最適化**: 各バッファは受信したページのみを保持します。63ページ分の領域を事前確保する代わりに、実際に受信したページのデータのみを格納するため、典型的なメッセージ（1〜5ページ）では約70〜80%のメモリ削減が可能です。

| メッセージサイズ | 旧実装 | 新実装 | 削減率 |
|-----------------|--------|--------|--------|
| 1ページ | 1,135B | ~240B | **79%** |
| 5ページ | 1,135B | ~340B | **70%** |
| 63ページ | 1,135B | ~1,350B | +19% |

**LRU エビクション**: バッファが全て使用中の場合、最も古いバッファを自動的に解放して新しいイベントを受け入れます。

### 6. JsonSerializer (JSONシリアライザ)

[`JsonSerializer`](include/internal/JsonSerializer.h)はMessageをJSON形式にシリアライズします:

- **ヒープアロケーションなし**: 固定バッファで処理
- **Print& 出力**: Serial, WiFiClient, 任意のPrint派生クラスに対応
- **言語選択**: 日本語/英語ラベルの選択的コンパイル

## データフロー

```
[GNSSモジュール]
      │
      ▼ 1バイトずつ投入
[Parser::feed()]
      │
      ├─→ [Framer] フレーム境界検出
      │       │
      │       ▼ フレーム完成
      ├─→ [Decoder] CRC検証 → デコード
      │       │
      │       ▼ Message生成
      ├─→ [DedupFilter] 重複チェック
      │       │
      │       ▼ 新規メッセージ
      ├─→ [NankaiPageBuffer] ページ集約 (MT=43 カテゴリ4のみ)
      │       │
      │       ▼ 集約完了 or 非南海トラフ
      ▼
[Message出力] → [toJson()] → [Print&]
```

## メモリ設計

### 静的メモリ使用量

| コンポーネント | メモリ使用量 | 備考 |
|---------------|-------------|------|
| DedupFilter | `AZARAC_DEDUP_SLOTS × 6` バイト | デフォルト48バイト |
| NankaiPageBuffer | 可変長（受信ページ数 × 20B + メタデータ） | デフォルト4バッファ、`AZARAC_NANKAI_BUFFERS`で調整可能 |
| Message | 約200バイト | 最大構造体サイズ |
| 定義テーブル | 約15-30KB | 言語選択による |

**NankaiPageBuffer メモリ使用例**（デフォルト4バッファ時）:
- 全バッファ空: ~200B
- 4バッファ×1ページ: ~1.2KB
- 4バッファ×5ページ: ~2.0KB

### ヒープアロケーション

AzaraCは**ヒープアロケーションを行いません**。すべてのバッファは静的に確保されます。これにより、長時間実行時のメモリフラグメンテーションを防止します。

## コンパイル時設定

| マクロ | デフォルト | 説明 |
|-------|-----------|------|
| `AZARAC_DEDUP_SLOTS` | 8 | 重複除去スロット数 |
| `AZARAC_LANG_JA` | 1 | 日本語ラベル有効 |
| `AZARAC_LANG_EN` | 0 | 英語ラベル有効 |
| `AZARAC_NANKAI_BUFFERS` | 4 | 南海トラフページ集約バッファ数 |

```cpp
// カスタム設定例
#define AZARAC_DEDUP_SLOTS 32
#define AZARAC_LANG_JA 1
#define AZARAC_LANG_EN 1
#define AZARAC_NANKAI_BUFFERS 8  // 同時に8イベントまで追跡可能
#include <azaraC.h>
```

## スレッドセーフ性

AzaraCはシングルスレッドでの使用を前提としています。FreeRTOS環境で使用する場合:

```cpp
// タスク内での使用例
void gnssTask(void* pvParameters) {
    azaraC::Parser parser;
    azaraC::Message msg;
    
    while (true) {
        while (Serial1.available()) {
            if (parser.feed(Serial1.read(), msg)) {
                // キューに送信 (スレッドセーフ)
                xQueueSend(messageQueue, &msg, portMAX_DELAY);
            }
        }
        vTaskDelay(1);
    }
}
```

## 拡張性

### カスタムフレーマーの実装

Sony製GNSSモジュール等、標準対応外のデバイスにはカスタムフレーマーを実装できます:

```cpp
class SonyFramer : public azaraC::internal::IFramer {
public:
    bool feed(uint8_t byte, azaraC::internal::Frame& out) override {
        // Sony固有のフレーミング処理
        // ...
        return frameComplete;
    }
    
    void reset() override {
        // 状態リセット
    }
};

// 使用
SonyFramer sony;
azaraC::Parser parser(sony);
```

## 関連ドキュメント

- [API リファレンス](api-reference.md)
- [開発者ガイド](developer-guide.md)
