///////////////////////////////////////////////////////////
//  MainTopic.h
//  Implementation of the Class MainTopic
//  Created on:      14-dec.-2020 11:22:25
//  Original author: Istvan DAVID
///////////////////////////////////////////////////////////

#if !defined(EA_CB141DC6_0174_4d59_9EF7_695E74669E8A__INCLUDED_)
#define EA_CB141DC6_0174_4d59_9EF7_695E74669E8A__INCLUDED_

#include "Topic.h"
#include "SubTopic.h"

class MainTopic : public Topic
{

public:
	MainTopic();
	virtual ~MainTopic();
	SubTopic *m_SubTopic;

};
#endif // !defined(EA_CB141DC6_0174_4d59_9EF7_695E74669E8A__INCLUDED_)
