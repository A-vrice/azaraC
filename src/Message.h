#pragma once
// メッセージ本体: 整列済みバイトストレージ上のタグ付き union。コピーと破棄は placement-new と明示的デストラクタで行う。
// payload の各型は trivially copyable のまま維持すること（Mt43Data::copyFrom がストレージを memcpy するため）。

#if defined(__AVR__)
#include "internal/avr_std/cstdint"
#else
#include <cstdint>
#endif
#if defined(__AVR__)
#include "internal/avr_std/cstring"
#else
#include <cstring>
#endif
#if defined(__AVR__)
#include "internal/avr_std/new"
#else
#include <new>
#endif

#include "azaraC_config.h"
#include "Mt43Data.h"
#include "Mt44Data.h"

namespace azaraC {

enum class UnsupportedReason : uint8_t {
    None = 0,
    DisabledAtCompileTime = 1,
    UnknownCategory = 2,
    UnsupportedVersion = 3,
};

enum class MsgPayloadType : uint8_t {
    Empty,
    Mt43,
    Mt44
};

struct Message {
    uint8_t  svid = 0;
    uint8_t  msg_type = 0;
    uint32_t crc24 = 0;
    bool     valid = false;
    UnsupportedReason unsupported_reason = UnsupportedReason::None;
    MsgPayloadType payload_type = MsgPayloadType::Empty;

    // 有効な payload の最大サイズ。DCX off では Mt44 を復号しないのでその分（約 280 B/Message）を削れる。
    // 三項演算子なのは Arduino.h の `max` マクロと衝突しないため。
#if AZARAC_ENABLE_DCX_CAMF
    static constexpr size_t payload_size_ =
        (sizeof(Mt43Data) > sizeof(Mt44Data) ? sizeof(Mt43Data) : sizeof(Mt44Data));
#else
    static constexpr size_t payload_size_ = sizeof(Mt43Data);
#endif

    Message() : payload_type(MsgPayloadType::Empty) {
        memset(payload_storage_, 0, sizeof(payload_storage_));
    }

    Message(const Message& other)
        : svid(other.svid)
        , msg_type(other.msg_type)
        , crc24(other.crc24)
        , valid(other.valid)
        , unsupported_reason(other.unsupported_reason)
        , payload_type(other.payload_type)
    {
        copyPayloadFrom(other);
    }

    Message& operator=(const Message& other) {
        if (this != &other) {
            destroyPayload();
            svid = other.svid;
            msg_type = other.msg_type;
            crc24 = other.crc24;
            valid = other.valid;
            unsupported_reason = other.unsupported_reason;
            payload_type = other.payload_type;
            copyPayloadFrom(other);
        }
        return *this;
    }

    ~Message() {
        destroyPayload();
    }

    // スカラーを初期値へ戻し payload を破棄する。payload_storage_ はクリアしない（次に initPayload() が上書きする）。
    void clear() {
        destroyPayload();
        svid = 0;
        msg_type = 0;
        crc24 = 0;
        valid = false;
        unsupported_reason = UnsupportedReason::None;
        // payload_type は destroyPayload() で Empty 済み
    }

    template<typename T>
    void initPayload() {
        // 無効化された payload（AZARAC_ENABLE_DCX_CAMF=0 の Mt44 など）は、実行時に溢れさせるのではなくここで静的に失敗させる。
        static_assert(sizeof(T) <= payload_size_,
                      "Payload type exceeds Message storage (disabled at compile time?)");
        destroyPayload();
        new (payload_storage_) T();
        payload_type = typeForPayload<T>();
    }

    Mt43Data* getMt43() {
        return (payload_type == MsgPayloadType::Mt43)
            ? reinterpret_cast<Mt43Data*>(payload_storage_) : nullptr;
    }

    Mt44Data* getMt44() {
#if AZARAC_ENABLE_DCX_CAMF
        return (payload_type == MsgPayloadType::Mt44)
            ? reinterpret_cast<Mt44Data*>(payload_storage_) : nullptr;
#else
        return nullptr;
#endif
    }

    const Mt43Data* getMt43() const {
        return (payload_type == MsgPayloadType::Mt43)
            ? reinterpret_cast<const Mt43Data*>(payload_storage_) : nullptr;
    }

    const Mt44Data* getMt44() const {
#if AZARAC_ENABLE_DCX_CAMF
        return (payload_type == MsgPayloadType::Mt44)
            ? reinterpret_cast<const Mt44Data*>(payload_storage_) : nullptr;
#else
        return nullptr;
#endif
    }

private:
    // 生の payload 領域。型と生存期間は initPayload<T>() / getMt43() / getMt44() だけが決める（public にすると initPayload() 抜きで payload_type と不整合に書ける）。
    // uint64_t を含む型（Mt44Data 等）が入るため境界指定が必要。AVR の alignof(uint64_t) は 1 なので実質要求なし（8 の倍数への切り上げが起きない）、ホストは 8。
    alignas(uint64_t) unsigned char payload_storage_[payload_size_];

    template<typename T> static MsgPayloadType typeForPayload();

    void destroyPayload() {
        switch (payload_type) {
            case MsgPayloadType::Mt43:
                getMt43()->~Mt43Data();
                break;
#if AZARAC_ENABLE_DCX_CAMF
            case MsgPayloadType::Mt44:
                getMt44()->~Mt44Data();
                break;
#endif
            default: break;
        }
        payload_type = MsgPayloadType::Empty;
    }

    void copyPayloadFrom(const Message& other) {
        switch (other.payload_type) {
            case MsgPayloadType::Mt43:
                new (payload_storage_) Mt43Data(*other.getMt43());
                break;
#if AZARAC_ENABLE_DCX_CAMF
            case MsgPayloadType::Mt44:
                new (payload_storage_) Mt44Data(*other.getMt44());
                break;
#endif
            default: break;
        }
    }
};

template<> inline MsgPayloadType Message::typeForPayload<Mt43Data>() { return MsgPayloadType::Mt43; }
template<> inline MsgPayloadType Message::typeForPayload<Mt44Data>() { return MsgPayloadType::Mt44; }

} // namespace azaraC
