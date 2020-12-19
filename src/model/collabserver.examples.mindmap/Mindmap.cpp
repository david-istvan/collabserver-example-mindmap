///////////////////////////////////////////////////////////
//  Mindmap.cpp
//  Implementation of the Class Mindmap
//  Created on:      14-dec.-2020 17:53:43
//  Original author: Istvan DAVID
///////////////////////////////////////////////////////////

#include "Mindmap.h"

Mindmap::Mindmap() {}

Mindmap::~Mindmap() {}

Mindmap::Mindmap(const char* _name) { name = _name; }

const char* Mindmap::GetName() { return name; }

void Mindmap::SetName(const char* newVal) { name = newVal; }
