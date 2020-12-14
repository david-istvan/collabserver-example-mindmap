///////////////////////////////////////////////////////////
//  CentralTopic.h
//  Implementation of the Class CentralTopic
//  Created on:      14-dec.-2020 12:59:05
//  Original author: Istvan DAVID
///////////////////////////////////////////////////////////

#if !defined(EA_EF04874A_01E0_4635_9C74_A805FB59377C__INCLUDED_)
#define EA_EF04874A_01E0_4635_9C74_A805FB59377C__INCLUDED_

#include "Topic.h"
#include "MainTopic.h"

class CentralTopic : public Topic
{

public:
	CentralTopic();
	virtual ~CentralTopic();
	MainTopic *m_MainTopic;

};
#endif // !defined(EA_EF04874A_01E0_4635_9C74_A805FB59377C__INCLUDED_)
