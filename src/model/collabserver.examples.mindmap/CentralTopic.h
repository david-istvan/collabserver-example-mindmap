///////////////////////////////////////////////////////////
//  CentralTopic.h
//  Implementation of the Class CentralTopic
//  Created on:      14-dec.-2020 17:53:42
//  Original author: Istvan DAVID
///////////////////////////////////////////////////////////

#if !defined(EA_A66A1E57_3868_42af_BE76_93A25D420811__INCLUDED_)
#define EA_A66A1E57_3868_42af_BE76_93A25D420811__INCLUDED_

#include "MainTopic.h"
#include "Topic.h"

class CentralTopic : public Topic {
   public:
    CentralTopic();
    virtual ~CentralTopic();
    MainTopic *m_MainTopic;
};
#endif  // !defined(EA_A66A1E57_3868_42af_BE76_93A25D420811__INCLUDED_)
