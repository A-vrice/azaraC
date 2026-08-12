#pragma once
// Main message struct.
// Safe tagged union: payload held in raw aligned storage; copy/destroy use
// placement-new + explicit destructor. Payload sub-objects must stay
// trivially copyable (Mt43Data::copyFrom uses memcpy).

#if defined(__AVR__)
#include "internal/avr_std/algorithm"
#else
#include <algorithm>
#endif
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

    // Max of Mt43Data/Mt44Data for safe placement-new of either.
    // Ternary instead of std::max: Arduino.h defines `max` as a macro.
    static constexpr size_t payload_size_ =
        (sizeof(Mt43Data) > sizeof(Mt44Data) ? sizeof(Mt43Data) : sizeof(Mt44Data));
    alignas(8) unsigned char payload_storage_[payload_size_];

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

    // Reset scalars and destroy payload without zeroing payload_storage_
    // (avoids a redundant memset before initPayload()).
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
        destroyPayload();
        new (payload_storage_) T();
        payload_type = typeForPayload<T>();
    }

    Mt43Data* getMt43() {
        return (payload_type == MsgPayloadType::Mt43)
            ? reinterpret_cast<Mt43Data*>(payload_storage_) : nullptr;
    }

    Mt44Data* getMt44() {
        return (payload_type == MsgPayloadType::Mt44)
            ? reinterpret_cast<Mt44Data*>(payload_storage_) : nullptr;
    }

    const Mt43Data* getMt43() const {
        return (payload_type == MsgPayloadType::Mt43)
            ? reinterpret_cast<const Mt43Data*>(payload_storage_) : nullptr;
    }

    const Mt44Data* getMt44() const {
        return (payload_type == MsgPayloadType::Mt44)
            ? reinterpret_cast<const Mt44Data*>(payload_storage_) : nullptr;
    }

private:
    template<typename T> static MsgPayloadType typeForPayload();

    void destroyPayload() {
        switch (payload_type) {
            case MsgPayloadType::Mt43:
                getMt43()->~Mt43Data();
                break;
            case MsgPayloadType::Mt44:
                getMt44()->~Mt44Data();
                break;
            default: break;
        }
        payload_type = MsgPayloadType::Empty;
    }

    void copyPayloadFrom(const Message& other) {
        switch (other.payload_type) {
            case MsgPayloadType::Mt43:
                new (payload_storage_) Mt43Data(*other.getMt43());
                break;
            case MsgPayloadType::Mt44:
                new (payload_storage_) Mt44Data(*other.getMt44());
                break;
            default: break;
        }
    }
};

// Type mapping specializations for Message payload
template<> inline MsgPayloadType Message::typeForPayload<Mt43Data>() { return MsgPayloadType::Mt43; }
template<> inline MsgPayloadType Message::typeForPayload<Mt44Data>() { return MsgPayloadType::Mt44; }

} // namespace azaraC
