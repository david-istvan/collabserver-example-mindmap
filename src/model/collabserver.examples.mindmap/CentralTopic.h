///////////////////////////////////////////////////////////
//  CentralTopic.h
//  Implementation of the Class CentralTopic
//  Created on:      14-dec.-2020 11:22:25
//  Original author: Istvan DAVID
///////////////////////////////////////////////////////////

#if !defined(EA_45B634B6_3C9F_42af_A17F_4E6C02354BA6__INCLUDED_)
#define EA_45B634B6_3C9F_42af_A17F_4E6C02354BA6__INCLUDED_

#include "Topic.h"
#include "MainTopic.h"

class CentralTopic : public Topic
{

public:
	CentralTopic();
	virtual ~CentralTopic();
	MainTopic *m_MainTopic;

};
#endif // !defined(EA_45B634B6_3C9F_42af_A17F_4E6C02354BA6__INCLUDED_)
