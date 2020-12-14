///////////////////////////////////////////////////////////
//  MainTopic.h
//  Implementation of the Class MainTopic
//  Created on:      14-dec.-2020 12:59:05
//  Original author: Istvan DAVID
///////////////////////////////////////////////////////////

#if !defined(EA_5E0BF563_4B06_48fe_9163_F459F6E829D5__INCLUDED_)
#define EA_5E0BF563_4B06_48fe_9163_F459F6E829D5__INCLUDED_

#include "Topic.h"
#include "SubTopic.h"

class MainTopic : public Topic
{

public:
	MainTopic();
	virtual ~MainTopic();
	SubTopic *m_SubTopic;

};
#endif // !defined(EA_5E0BF563_4B06_48fe_9163_F459F6E829D5__INCLUDED_)
