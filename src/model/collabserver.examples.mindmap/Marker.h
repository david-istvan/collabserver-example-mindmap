///////////////////////////////////////////////////////////
//  Marker.h
//  Implementation of the Class Marker
//  Created on:      14-dec.-2020 12:59:05
//  Original author: Istvan DAVID
///////////////////////////////////////////////////////////

#if !defined(EA_84732D68_3944_4801_8C29_33A626AE24CD__INCLUDED_)
#define EA_84732D68_3944_4801_8C29_33A626AE24CD__INCLUDED_

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

};
#endif // !defined(EA_84732D68_3944_4801_8C29_33A626AE24CD__INCLUDED_)
