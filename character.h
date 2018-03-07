#ifndef CHARACTER_H
#define CHARACTER_H

#include "inventory.h"
#include "equipment.h"

/**
 * structure Character
 * 	defines anyone (player or opponent)
 */

using namespace std;

class Character
{
	private:
	
	protected:
	
	public:
		string Name;
		int Level;
		int Health;		//	points of life
		int StrBonus;	//	strenght bonus if str >= 13
		int ResBonus;	//	resistance bonus if str >= 13
		int ArmorClass;	//	Protection's value
		int Strength;	//	attack power
		int Resistance;	//	defense
		int Exp;
		int ExpNextLvl;	//  EXP needed for next level by Level * ExpNextLevel	
		int Victories;
		vector<Inventory> Bag;
		vector<Equipment> Equip;
		
		// constructeur defaut + param
		Character(string name="undefined");
		// copy constructor
		Character( const Character &C);
		// operator=
		Character & operator=(const Character &C);
				
		// destructeur
		virtual ~Character() {};

		/**
		 * function RandomValues
		 * 	used to define all random values
		 * 	Minimum and Maximum parameters
		 */
		int RandomValues(int Minimum, int Maximum);
		/**
		 * function InitCharacter
		 * 	create character
		 */
		void InitCharacter();
		/**
		 * function MonsterInit
		 * 	create the Non Player Character
		 */
		void MonsterInit(int rank);
		/**
		 * function MonsterDisplay
		 * 	display the monster's detail
		 */
		void MonsterDisplay();
		/**
		 * function DisplayCharacter
		 * 		shows the character stats
		 * 		@return	void
		 */
		void DisplayCharacter(int language=1);
		/**
		 * Function lvlUp
		 * upgrade player
		 * based on character_t
		 */
		void lvlUp(int language=1);
};

#endif
