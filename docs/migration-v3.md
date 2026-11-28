# azaraC v2 から v3 への移行

## カスタムフレーマ

`azaraC::internal::IFramer` と `azaraC::internal::Frame` は `azaraC::IFramer`、`azaraC::Frame` になりました。内部ヘッダの代わりに `<IFramer.h>` と `<Frame.h>`（またはまとめて `<azaraC.h>`）を使い、継承元と `feed()` の引数型を更新してください。フレーマは引き続き呼び出し側が所有し、`Parser` より長く生存させます。[カスタムフレーマの例](../examples/custom_framer/custom_framer.ino)を参照してください。

## 南海トラフの集約進捗

`Parser::getNankaiBuffer()` は削除されました。集約の進捗を見るには、受信した電文の値から公開キーを作り、`getNankaiProgress()` を呼びます。

```cpp
#if AZARAC_ENABLE_NANKAI
azaraC::NankaiEventKey key{info_code, report_month, report_day, report_hour,
                          report_minute, information_type, report_classification};
azaraC::NankaiProgress progress;
if (parser.getNankaiProgress(key, progress)) {
    // progress.received_count / progress.total_pages などを参照
}
#endif
```

キーには正規化前の報告時刻と、発表・取消および実警報・訓練を区別するための `information_type`、`report_classification` を指定します。取得するのは進捗のコピーで、キーが無ければ `false` を返して出力を変更しません。完成した本文は、`feed()` が返した `Message` の `getMt43()->getNankai()` で参照します。本文ポインタの寿命については [API リファレンス](api-reference.md#南海トラフのページ集約)を参照してください。

## 無効にしたカテゴリの公開型・アクセサ

`AZARAC_ENABLE_EEW=0` など、MT=43 のカテゴリを無効にすると、対応するペイロード型とアクセサ（例: `azaraC::EewData`、`Mt43Data::getEew()`）は存在しなくなります。複数の構成で使うコードでは、呼び出しだけでなく型の参照も `#if AZARAC_ENABLE_EEW` などで囲んでください。南海トラフを無効にすると `NankaiEventKey`、`NankaiProgress`、`getNankaiProgress()` も除外されます。

`AZARAC_ENABLE_DCX_CAMF=0` は例外で、`Mt44Data` と `getMt44()` は残り、`getMt44()` は常に `nullptr` を返します。

## 非 AVR の Parser RAM

非 AVR で南海トラフを有効にしたときの `AZARAC_NANKAI_BUFFERS` の既定値は 1 から 2 になり、実警報と訓練・試験を並行して集約できます。既定構成の `Parser` は約 5.4 KB からホスト実測 6,624 B になります。実際の RAM 使用量は対象ボード、コンパイラ、ビルド設定によって異なるため、更新後に再計測してください。RAM を優先する場合は、全翻訳単位に `-DAZARAC_NANKAI_BUFFERS=1` を指定して同時集約数を 1 に戻せます。AVR プリセットは 1 のままで、南海トラフ自体は既定で無効です。
