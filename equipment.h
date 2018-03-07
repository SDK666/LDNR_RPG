#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include "lib.h"

/**
 * Structure Equipment
 * 	Weapons, Armors, Shields
 */

using namespace std;

class Equipment
{
	private:
		string NameEquip;
		int NumEquip;
		int Price;
		int Bonus;
	
	protected:
	
	public:
		// constructeur defaut + param
		Equipment();
		// copy constructor
		Equipment( const Equipment &E);
		// operator=
		Equipment & operator=(const Equipment &E);
				
		// destructeur
		virtual ~Equipment() {};

};

#endif
