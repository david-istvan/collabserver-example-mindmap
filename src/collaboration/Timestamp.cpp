#include "collaboration/Timestamp.h"

#include <cassert>

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
