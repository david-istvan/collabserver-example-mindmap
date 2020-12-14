///////////////////////////////////////////////////////////
//  Topic.h
//  Implementation of the Class Topic
//  Created on:      14-dec.-2020 17:53:43
//  Original author: Istvan DAVID
///////////////////////////////////////////////////////////

#if !defined(EA_94A46B22_5998_435a_943B_D12D1846FDB7__INCLUDED_)
#define EA_94A46B22_5998_435a_943B_D12D1846FDB7__INCLUDED_

#include "Marker.h"

class Topic
{

public:
	Topic();
	virtual ~Topic();
	Marker *m_Marker;

	Topic(const char* _name);
	const char* GetName();
	void SetName(const char* newVal);

private:
	const char* name;

};
#endif // !defined(EA_94A46B22_5998_435a_943B_D12D1846FDB7__INCLUDED_)
