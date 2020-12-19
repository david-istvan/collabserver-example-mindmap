///////////////////////////////////////////////////////////
//  MainTopic.h
//  Implementation of the Class MainTopic
//  Created on:      14-dec.-2020 17:53:43
//  Original author: Istvan DAVID
///////////////////////////////////////////////////////////

#if !defined(EA_08E6FF56_B11D_4386_9F6F_ED5CE9F78093__INCLUDED_)
#define EA_08E6FF56_B11D_4386_9F6F_ED5CE9F78093__INCLUDED_

#include "SubTopic.h"
#include "Topic.h"

class MainTopic : public Topic {
   public:
    MainTopic();
    virtual ~MainTopic();
    SubTopic *m_SubTopic;
};
#endif  // !defined(EA_08E6FF56_B11D_4386_9F6F_ED5CE9F78093__INCLUDED_)
