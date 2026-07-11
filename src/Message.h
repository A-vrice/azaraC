#pragma once
// azaraC - src/Message.h
// Main message struct (Safe tagged union)
//
// Safe tagged union using explicit memory management (placement new).
// No std::variant dependency for Arduino compatibility.

#include <algorithm>
#include <cstdint>
#include <cstring>
#include <new>
#include <utility>

#include "Mt43Data.h"
#include "Mt44Data.h"

namespace azaraC {

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
    MsgPayloadType payload_type = MsgPayloadType::Empty;

    // Storage for the active payload (aligned to 8 bytes)
    // Size is based on the maximum of Mt43Data and Mt44Data to ensure
    // safe placement-new for either payload type.
    static constexpr size_t payload_size_ = std::max(sizeof(Mt43Data), sizeof(Mt44Data));
    alignas(8) unsigned char payload_storage_[payload_size_];

    Message() : payload_type(MsgPayloadType::Empty) {
        memset(payload_storage_, 0, sizeof(payload_storage_));
    }

    Message(const Message& other)
        : svid(other.svid)
        , msg_type(other.msg_type)
        , crc24(other.crc24)
        , valid(other.valid)
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
            payload_type = other.payload_type;
            movePayloadFrom(other);
        }
        return *this;
    }

    ~Message() {
        destroyPayload();
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
        if (payload_type == MsgPayloadType::Empty) return;
        switch (payload_type) {
            case MsgPayloadType::Mt43: getMt43()->~Mt43Data(); break;
            case MsgPayloadType::Mt44: getMt44()->~Mt44Data(); break;
            case MsgPayloadType::Empty: break;
        }
        payload_type = MsgPayloadType::Empty;
    }

    void copyPayloadFrom(const Message& other) {
        if (other.payload_type == MsgPayloadType::Empty) return;
        switch (other.payload_type) {
            case MsgPayloadType::Mt43: new (payload_storage_) Mt43Data(*other.getMt43()); break;
            case MsgPayloadType::Mt44: new (payload_storage_) Mt44Data(*other.getMt44()); break;
            case MsgPayloadType::Empty: break;
        }
    }

    void movePayloadFrom(Message& other) {
        if (other.payload_type == MsgPayloadType::Empty) return;
        switch (other.payload_type) {
            case MsgPayloadType::Mt43: new (payload_storage_) Mt43Data(std::move(*other.getMt43())); break;
            case MsgPayloadType::Mt44: new (payload_storage_) Mt44Data(std::move(*other.getMt44())); break;
            case MsgPayloadType::Empty: break;
        }
        other.payload_type = MsgPayloadType::Empty;
    }
};

// Type mapping specializations for Message payload
template<> inline MsgPayloadType Message::typeForPayload<Mt43Data>() { return MsgPayloadType::Mt43; }
template<> inline MsgPayloadType Message::typeForPayload<Mt44Data>() { return MsgPayloadType::Mt44; }

} // namespace azaraC
