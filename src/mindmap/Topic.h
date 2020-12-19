#pragma once

#include "mindmap/Marker.h"

class Topic {
   public:
    Topic() = default;
    Topic(const char* _name) : m_name{_name} {}
    virtual ~Topic() = default;

    const char* getName() const { return m_name; }
    void setName(const char* _name) { m_name = _name; };

   private:
    const char* m_name;
    Marker* m_marker;
};
