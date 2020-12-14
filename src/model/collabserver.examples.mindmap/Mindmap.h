///////////////////////////////////////////////////////////
//  Mindmap.h
//  Implementation of the Class Mindmap
//  Created on:      14-dec.-2020 12:59:05
//  Original author: Istvan DAVID
///////////////////////////////////////////////////////////

#if !defined(EA_8D22742A_8738_413a_8DA0_9EF48390B1C1__INCLUDED_)
#define EA_8D22742A_8738_413a_8DA0_9EF48390B1C1__INCLUDED_

#include "CentralTopic.h"
#include "Marker.h"

class Mindmap
{

public:
	Mindmap();
	virtual ~Mindmap();
	CentralTopic *m_CentralTopic;
	Marker *m_Marker;

	Mindmap(const char* _name);
	const char* GetName();
	void SetName(const char* newVal);

private:
	const char* name;

};
#endif // !defined(EA_8D22742A_8738_413a_8DA0_9EF48390B1C1__INCLUDED_)
