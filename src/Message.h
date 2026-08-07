#pragma once
// azaraC - src/Message.h
// Main message struct (Safe tagged union)
//
// Safe tagged union: payload (Mt43Data/Mt44Data) is held in raw aligned
// storage; payload types MUST remain trivially copyable + trivially
// destructible, so copy/move/destroy reduce to memcpy / tag reset.

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

// ---- Unsupported reason enum -------------------------------------------

enum class UnsupportedReason : uint8_t {
    None = 0,
    DisabledAtCompileTime = 1,
    UnknownCategory = 2,
    UnsupportedVersion = 3,
};

// ---- Message payload type tag ------------------------------------------

enum class MsgPayloadType : uint8_t {
    Empty,
    Mt43,
    Mt44
};

// ---- main message struct (Safe tagged union) ---------------------------

struct Message {
    uint8_t  svid = 0;
    uint8_t  msg_type = 0;
    uint32_t crc24 = 0;
    bool     valid = false;
    UnsupportedReason unsupported_reason = UnsupportedReason::None;
    MsgPayloadType payload_type = MsgPayloadType::Empty;

    // Storage for the active payload (aligned to 8 bytes)
    // Size is based on the maximum of Mt43Data and Mt44Data to ensure
    // safe placement-new for either payload type. (Ternary instead of
    // std::max: Arduino's Arduino.h defines a `max` function-like macro.)
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

    Message(Message&& other) noexcept
        : svid(other.svid)
        , msg_type(other.msg_type)
        , crc24(other.crc24)
        , valid(other.valid)
        , unsupported_reason(other.unsupported_reason)
        , payload_type(other.payload_type)
    {
        movePayloadFrom(other);
    }

    Message& operator=(Message&& other) noexcept {
        if (this != &other) {
            destroyPayload();
            svid = other.svid;
            msg_type = other.msg_type;
            crc24 = other.crc24;
            valid = other.valid;
            unsupported_reason = other.unsupported_reason;
            payload_type = other.payload_type;
            movePayloadFrom(other);
        }
        return *this;
    }

    ~Message() {
        destroyPayload();
    }

    // Reset scalars and destroy payload WITHOUT zeroing payload_storage_.
    // Use before initPayload() to avoid a redundant memset when storage will
    // be immediately overwritten by placement-new.
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
        payload_type = MsgPayloadType::Empty;  // Mt43Data/Mt44Data trivially destructible → no-op
    }

    void copyPayloadFrom(const Message& other) {
        memcpy(payload_storage_, other.payload_storage_, payload_size_);
    }

    void movePayloadFrom(Message& other) {
        memcpy(payload_storage_, other.payload_storage_, payload_size_);
        other.payload_type = MsgPayloadType::Empty;
    }
};

// Type mapping specializations for Message payload
template<> inline MsgPayloadType Message::typeForPayload<Mt43Data>() { return MsgPayloadType::Mt43; }
template<> inline MsgPayloadType Message::typeForPayload<Mt44Data>() { return MsgPayloadType::Mt44; }

} // namespace azaraC
