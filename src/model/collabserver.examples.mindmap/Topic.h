///////////////////////////////////////////////////////////
//  Topic.h
//  Implementation of the Class Topic
//  Created on:      14-dec.-2020 11:22:26
//  Original author: Istvan DAVID
///////////////////////////////////////////////////////////

#if !defined(EA_B665DA74_38E1_4d43_AC24_ED262303739A__INCLUDED_)
#define EA_B665DA74_38E1_4d43_AC24_ED262303739A__INCLUDED_

#include "Marker.h"

class Topic
{

public:
	Topic();
	virtual ~Topic();
	Marker *m_Marker;

private:
	std::string name;

};
#endif // !defined(EA_B665DA74_38E1_4d43_AC24_ED262303739A__INCLUDED_)
