///////////////////////////////////////////////////////////
//  Topic.cpp
//  Implementation of the Class Topic
//  Created on:      14-dec.-2020 17:53:43
//  Original author: Istvan DAVID
///////////////////////////////////////////////////////////

#include "Topic.h"


Topic::Topic(){

}



Topic::~Topic(){

}





Topic::Topic(const char* _name){
    name = _name;
}


const char* Topic::GetName(){

	return name;
}


void Topic::SetName(const char* newVal){

	name = newVal;
}