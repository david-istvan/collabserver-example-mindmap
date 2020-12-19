///////////////////////////////////////////////////////////
//  Mindmap.h
//  Implementation of the Class Mindmap
//  Created on:      14-dec.-2020 17:53:43
//  Original author: Istvan DAVID
///////////////////////////////////////////////////////////

#if !defined(EA_0F49C380_A31A_4d87_8CDE_D977DA6D000B__INCLUDED_)
#define EA_0F49C380_A31A_4d87_8CDE_D977DA6D000B__INCLUDED_

#include "CentralTopic.h"
#include "Marker.h"

class Mindmap {
   public:
    Mindmap();
    virtual ~Mindmap();
    CentralTopic* m_CentralTopic;
    Marker* m_Marker;

    Mindmap(const char* _name);
    const char* GetName();
    void SetName(const char* newVal);

   private:
    const char* name;
};
#endif  // !defined(EA_0F49C380_A31A_4d87_8CDE_D977DA6D000B__INCLUDED_)
