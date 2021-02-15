#include "collaboration/Timestamp.h"

#include <cassert>
#include <msgpack.hpp>

unsigned int Timestamp::m_effectiveID = 0;

// -----------------------------------------------------------------------------

Timestamp::Timestamp(const int value) {
    assert(Timestamp::m_effectiveID != 0);
    m_id = Timestamp::m_effectiveID;
    m_time = std::chrono::time_point<std::chrono::steady_clock>::min();
}

Timestamp::Timestamp(const TimePoint time, const int id) {
    assert(id != 0);
    m_id = id;
    m_time = time;
}

Timestamp Timestamp::now() {
    assert(Timestamp::m_effectiveID != 0);
    Timestamp t = {0};  // Dev note: See constructor doc to understand {0}
    t.m_id = Timestamp::m_effectiveID;
    t.m_time = std::chrono::steady_clock::now();
    return t;
}

void Timestamp::setEffectiveID(const unsigned int id) { Timestamp::m_effectiveID = id; }

bool Timestamp::serialize(std::stringstream& _buffer) const {
    Timestamp::Clock::duration currentTime = m_time.time_since_epoch();
    msgpack::pack(_buffer, m_id);
    msgpack::pack(_buffer, currentTime.count());
    return true;
}

std::size_t Timestamp::unserialize(const std::stringstream& _buffer) {
    std::string str(_buffer.str());
    std::size_t offset = 0;

    msgpack::object_handle r1 = msgpack::unpack(str.data(), str.size(), offset);
    msgpack::object_handle r2 = msgpack::unpack(str.data(), str.size(), offset);

    unsigned int id = r1.get().as<unsigned int>();
    auto time = r2.get().as<Timestamp::Clock::rep>();
    m_time = Timestamp::TimePoint(Timestamp::Clock::duration(time));
    return offset;
}

// -----------------------------------------------------------------------------

Timestamp& Timestamp::operator=(const int value) {
    // Dev note: see constructor note
    assert(Timestamp::m_effectiveID != 0);
    m_id = Timestamp::m_effectiveID;
    m_time = std::chrono::time_point<std::chrono::steady_clock>::min();
    return *this;
}

Timestamp& Timestamp::operator=(const Timestamp& other) {
    m_id = other.m_id;
    m_time = other.m_time;
    return *this;
}

bool operator==(const Timestamp& rhs, const Timestamp& lhs) {
    return (rhs.m_time == lhs.m_time) && (rhs.m_id == lhs.m_id);
}

bool operator!=(const Timestamp& rhs, const Timestamp& lhs) { return !(rhs == lhs); }

bool operator>(const Timestamp& rhs, const Timestamp& lhs) {
    if (rhs.m_time == lhs.m_time) {
        return rhs.m_id > lhs.m_id;
    }
    return rhs.m_time > lhs.m_time;
}

bool operator<(const Timestamp& rhs, const Timestamp& lhs) {
    if (rhs.m_time == lhs.m_time) {
        return rhs.m_id < lhs.m_id;
    }
    return rhs.m_time < lhs.m_time;
}
