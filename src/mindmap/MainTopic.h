#pragma once

#include <vector>

#include "mindmap/SubTopic.h"
#include "mindmap/Topic.h"

class MainTopic : public Topic {
   public:
    MainTopic() = default;

   private:
    std::vector<SubTopic> m_subTopics;
};
