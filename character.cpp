#include "character.h"

// constructeur defaut + param
Character::Character(string name)
{
	this->Name = name;
}

// copy constructor
Character::Character( const Character &C)
{
	Name = C.Name;
	this->Level = C.Level;
	this->ArmorClass = C.ArmorClass;
	this->Health = C.Health;
	this->Strength = C.Strength;
	this->StrBonus = C.StrBonus;
	this->Resistance = C.Resistance;
	this->ArmorClass = C.ArmorClass;
	this->Exp = C.Exp;
}

// operator=
Character & Character::operator=(const Character &C)
{
	Name = C.Name;
	this->Level = C.Level;
	this->ArmorClass = C.ArmorClass;
	this->Health = C.Health;
	this->Strength = C.Strength;
	this->StrBonus = C.StrBonus;
	this->Resistance = C.Resistance;
	this->ArmorClass = C.ArmorClass;
	this->Exp = C.Exp;
}

/**
 * function RandomValues
 * 		used to define all random values
 * 		@param	int Minimum
 * 		@param	int Maximum
 * 		@return	int
 */
int Character::RandomValues(int Minimum, int Maximum)
{
	return rand() % (Maximum - Minimum + 1) + Minimum;
}

/**
 * function InitCharacter
 * 		initialize character's stats
 * 		includes some DEBUG_PRINT
 * 		@return	void
 */
void Character::InitCharacter()
{
	/*	Initialize Level, exp, victories and ExpNextLevel	*/
	this->Level = 1;
	this->Exp = 0;
	this->Victories = 0;
	this->ExpNextLvl = 1500;
	
	/*	Initialize bonus to 0	*/
	this->StrBonus = 0;	// Bonus for upgrade damage
	this->ResBonus = 0;	// Bonus for upgrade Health and Armor Class
	/*	randomize Strength and Resistance	*/
	/*	########## BEGIN STRENGTH ##########	*/
	this->Strength = RandomValues(8, 18); //Between 3 and 18
	/*	Attribute Strenght Bonus if random is better than 13	*/
	if(this->Strength >= 13 && this->Strength <=15)
		this->StrBonus = 1;
	if(this->Strength >= 16 && this->Strength <=17)
		this->StrBonus = 2;
	if(this->Strength == 18)
		this->StrBonus = 3;
	/*	End of attribute Strenght Bonus	*/
	DEBUG_PRINT(("%d Strength\n", this->Strength)); //Just for test
	/*	########## END STRENGTH ##########	*/
	
	/*	########## BEGIN RESISTANCE ##########	*/
	this->Resistance = RandomValues(8, 18);
	/*	Attribute Resitance Bonus if random is better than 13	*/
	if(this->Resistance >= 13 && this->Resistance <=15)
		this->ResBonus = 1;
	if(this->Resistance >= 16 && this->Resistance <=17)
		this->ResBonus = 2;
	if(this->Resistance == 18)
		this->ResBonus = 3;
	/*	End of attribute ResitanceBonus */
	DEBUG_PRINT(("%d Resistance\n", this->Resistance)); //Just for test
	/*	########## END RESISTANCE ##########	*/
	
	this->ArmorClass = 10 + this->ResBonus; // + nothing actually. Need to have Armor 
	
	/*	Initialize Health	*/
	this->Health = 6 + this->ResBonus;	//	set character's health by 6 + ResBonus and for next lvl it's Health + rnd 1-6 + ResBonus 
	DEBUG_PRINT(("%d Health\n", this->Health)); //Just for test
}

/**
 * function MonsterInit
 * 		create the Non Player Character
 * 		@param	int rank
 * 		@return	void
 */
void Character::MonsterInit(int rank)
{
	int bonus = 0;	//	bonus point for health
	int xp = 0;		//	XP hero will gain defeating the monster
	int armor = 0;	//	monster's armor class
	switch (rank)
	{
		case 1:
			bonus = 1;
			xp = 600;
			armor = 14;
			break;
		case 0:
		default:
			bonus = -1;
			xp = 500;
			armor = 12;
			break;
	}
	this->Level = rank;
	this->ArmorClass = armor;
	this->Health = RandomValues(1, 6) + bonus;
	if(this->Health <= 0)
		this->Health = 1;
	this->Strength = RandomValues(1, 6) + bonus;
	if(this->Strength <= 0)
		this->Strength = 1;
	this->StrBonus = 0;
	this->Resistance = RandomValues(1, 6) + bonus;
	if(this->Resistance <= 0)
		this->Resistance = 1;
	this->Exp = xp;
	//DEBUG_PRINT(("%d\n", this->ArmorClass)); //Just for test
}

/**
 * function MonsterDisplay
 * 		shows the monster's stats
 * 		only works in debug mode
 * 		@return	void
 */
void Character::MonsterDisplay()
{
	DEBUG_PRINT(("%s\n",this->Name.c_str()));
	DEBUG_PRINT(("\tRang : %d\n",this->Level));
	DEBUG_PRINT(("\tVie : %d\n",this->Health));
	DEBUG_PRINT(("\tForce : %d\n",this->Strength));
	DEBUG_PRINT(("\tDefense : %d\n",this->Resistance));
}

/**
 * function DisplayCharacter
 * 		shows the character stats
 * 		@return	void
 */
void Character::DisplayCharacter(int language)
{
    if ( language == 1)
    {
		cout << "\tCaractéristiques de " << this->Name << endl;
		cout << "\t\tNiveau \t:\t\t" << this->Level << endl;
		cout << "\t\tVie \t:\t\t" << this->Health << endl;
		cout << "\t\tForce \t:\t\t" << this->Strength << endl;
		cout << "\t\tDéfense\t:\t\t" << this->Resistance << endl;
		cout << "\t\tClasse d'Armure\t:\t" << this->ArmorClass << endl;
		cout << "\t\tExpérience :\t\t" << this->Exp << endl;
		cout << "\t\tVictoire :\t\t" << this->Victories << endl;
		cout << "\t\tProchain niveau :\t" << this->ExpNextLvl - this->Exp << " exp" << endl;
	}
    else
    {
		cout << "\tCharacteristics of" << this->Name << endl;
		cout << "\t\tLevel \t:\t\t" << this->Level << endl;
		cout << "\t\tLife \t:\t\t" << this->Health << endl;
		cout << "\t\tForce \t:\t\t" << this->Strength << endl;
		cout << "\t\tDefense\t:\t\t" << this->Resistance << endl;
		cout << "\t\tArmor Class\t:\t" << this->ArmorClass << endl;
		cout << "\t\tExperience :\t\t" << this->Exp << endl;
		cout << "\t\tVictorie(s) :\t\t" << this->Victories << endl;
		cout << "\t\tNext level :\t" << this->ExpNextLvl - this->Exp << " exp" << endl;
	}
}

/**
 * Function lvlUp
 * 		upgrade player's stats
 * 		@param	int language
 * 		@return	void
 */
void Character::lvlUp(int language)
{
	this->Level += 1;
	this->ExpNextLvl *= this->Level;
	
	this->Health += RandomValues(1, 6);
	if ( language == 1)
		cout << "\tVous avez maintenant " << this->Health << " points de vie" << endl;
	else
		cout << "\tNow you have " << this->Health << " health points" << endl;
	
	//	Every 2 levels, player gain +1 to Str bonus
	if(this->Level % 2 == 0)
		this->StrBonus += 1;
}
