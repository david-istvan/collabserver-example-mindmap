///////////////////////////////////////////////////////////
//  Mindmap.h
//  Implementation of the Class Mindmap
//  Created on:      14-dec.-2020 11:22:26
//  Original author: Istvan DAVID
///////////////////////////////////////////////////////////

#if !defined(EA_7FB857FF_89CA_4377_AB0D_AE99E7500C20__INCLUDED_)
#define EA_7FB857FF_89CA_4377_AB0D_AE99E7500C20__INCLUDED_

#include "CentralTopic.h"
#include "Marker.h"

class Mindmap
{

public:
	Mindmap();
	virtual ~Mindmap();
	CentralTopic *m_CentralTopic;
	Marker *m_Marker;

private:
	std::string name;

};
#endif // !defined(EA_7FB857FF_89CA_4377_AB0D_AE99E7500C20__INCLUDED_)
