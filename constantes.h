#ifndef CONSTANTES_H_INCLUDED
#define CONSTANTES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define DEBUG 1

#ifdef DEBUG
# define DEBUG_PRINT(x) printf x
#else
# define DEBUG_PRINT(x) do {} while (0)
#endif

#if defined WIN32
#define CLEAN_SCREEN "CLS"
#elif defined __linux
#define CLEAN_SCREEN "clear"
#endif

/**
 * Structure Equipment
 * 	Weapons, Armors, Shields
 */
typedef struct Equipment
{
	char NameEquip[30];
	int NumEquip;
	int Price;
	int Bonus;
}Equipment_t;

/**
 * structure Inventory
 * 	Items, Equipment, Money
 */
typedef struct Inventory
{
	char NameItem[255];
	int NumItems;
	int Price;
}Inventory_t;

/**
 * structure Character
 * 	defines anyone (player or opponent)
 */
typedef struct Character
{
	char Name[30];
	int Level;
	int Exp;
	int ExpNextLvl;	//  EXP needed for next level by Level * ExpNextLevel	
	int Health;		//	points of life
	int Strength;	//	attack power
	int Resistance;	//	defense
	int ArmorClass;	//	Protection's value
	int Victories;
	int StrBonus;	//	strenght bonus if str >= 13
	int ResBonus;	//	resistance bonus if str >= 13
	Inventory_t Bag[5];
	Equipment_t Equip[5];
}Character_t;

#endif // CONSTANTES_H_INCLUDED
