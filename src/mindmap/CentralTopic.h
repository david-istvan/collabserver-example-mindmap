#pragma once

#include <vector>

#include "mindmap/MainTopic.h"
#include "mindmap/Topic.h"

class CentralTopic : public Topic {
   public:
    CentralTopic() = default;

   private:
    std::vector<MainTopic> m_mainTopics;
};
