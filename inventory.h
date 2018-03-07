#ifndef INVENTORY_H
#define INVENTORY_H

#include "lib.h"

/**
 * structure Inventory
 * 	Items, Equipment, Money
 */

using namespace std;

class Inventory
{
	private:
		string NameItem[255];
		int NumItems;
		int Price;
	
	protected:
	
	public:
		// constructeur defaut + param
		Inventory();
		// copy constructor
		Inventory( const Inventory &I);
		// operator=
		Inventory & operator=(const Inventory &I);
				
		// destructeur
		virtual ~Inventory() {};

};

#endif
