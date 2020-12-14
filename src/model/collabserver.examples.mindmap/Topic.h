///////////////////////////////////////////////////////////
//  Topic.h
//  Implementation of the Class Topic
//  Created on:      14-dec.-2020 12:59:05
//  Original author: Istvan DAVID
///////////////////////////////////////////////////////////

#if !defined(EA_EDA0EFDC_4780_4e7e_B779_60DAC1377069__INCLUDED_)
#define EA_EDA0EFDC_4780_4e7e_B779_60DAC1377069__INCLUDED_

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
#endif // !defined(EA_EDA0EFDC_4780_4e7e_B779_60DAC1377069__INCLUDED_)
