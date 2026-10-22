#pragma once
// メッセージ本体: raw な整列ストレージ上のタグ付き union。コピー/破棄は placement-new と明示的デストラクタで行う。
// payload の各型は trivially copyable のまま維持すること（Mt43Data::copyFrom はストレージを memcpy する）。

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

    // 有効な payload の最大サイズ（DCX off では Mt44 を復号しないのでその ~280 B/Message を削る。Uno は 2 KB）。
    // Ternary instead of std::max: Arduino.h defines `max` as a macro.
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

    // Reset scalars and destroy payload without zeroing payload_storage_ (avoids a redundant memset before initPayload()).
    void clear() {
        destroyPayload();
        svid = 0;
        msg_type = 0;
        crc24 = 0;
        valid = false;
        unsupported_reason = UnsupportedReason::None;
        // payload_type is already MsgPayloadType::Empty from destroyPayload()
    }

    template<typename T>
    void initPayload() {
        // Compile-time guard: instantiating a disabled payload (e.g. Mt44 with AZARAC_ENABLE_DCX_CAMF=0) fails here instead of overflowing.
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
    // 生の payload 領域。生存期間と型は initPayload<T>() / getMt43() / getMt44() だけが決める（公開すると initPayload() 無しで payload_type と不整合に書ける）。
    // payload には uint64_t を含む型（Mt44Data 等）が入るため境界が必要。AVR の alignof(uint64_t) は 1 なので、この指定は AVR では境界を要求しない（8 の倍数への切り上げが起きない）。ホストは 8 のまま。
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

// Type mapping specializations for Message payload
template<> inline MsgPayloadType Message::typeForPayload<Mt43Data>() { return MsgPayloadType::Mt43; }
template<> inline MsgPayloadType Message::typeForPayload<Mt44Data>() { return MsgPayloadType::Mt44; }

} // namespace azaraC
