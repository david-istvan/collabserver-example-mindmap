///////////////////////////////////////////////////////////
//  Marker.cpp
//  Implementation of the Class Marker
//  Created on:      14-dec.-2020 17:53:43
//  Original author: Istvan DAVID
///////////////////////////////////////////////////////////

#include "Marker.h"

Marker::Marker() {}

Marker::~Marker() {}

Marker::Marker(const char* _name) { name = _name; }

const char* Marker::GetSymbol() { return symbol; }

void Marker::SetSymbol(const char* newVal) { symbol = newVal; }
