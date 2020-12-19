///////////////////////////////////////////////////////////
//  Marker.h
//  Implementation of the Class Marker
//  Created on:      14-dec.-2020 17:53:43
//  Original author: Istvan DAVID
///////////////////////////////////////////////////////////

#if !defined(EA_2399B671_4E82_4d10_ACB5_EDC44F90903B__INCLUDED_)
#define EA_2399B671_4E82_4d10_ACB5_EDC44F90903B__INCLUDED_

class Marker
{

public:
	Marker();
	virtual ~Marker();

	Marker(const char* _name);
	const char* GetSymbol();
	void SetSymbol(const char* newVal);

private:
	const char* symbol;
	const char* name;

};
#endif // !defined(EA_2399B671_4E82_4d10_ACB5_EDC44F90903B__INCLUDED_)
