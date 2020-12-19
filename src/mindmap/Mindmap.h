#pragma once

#include <vector>

#include "mindmap/CentralTopic.h"
#include "mindmap/Marker.h"

class Mindmap {
   public:
    Mindmap() = default;
    Mindmap(const char* _name) : m_name{_name} {}

    const char* getName() const { return m_name; }
    void setName(const char* _name) { m_name = _name; }

   private:
    const char* m_name;
    CentralTopic* m_centralTopic;
    std::vector<Marker> m_markers;
};
