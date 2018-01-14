#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include "constantes.h"

/*
functions.h
#######################################

Purpose : prototypes for the game functions.
*/

/**
 * function cls
 * 		clear screen
 * 		CLEAN_SCREEN depends on OS
 * 		>>> works for Linux and Windows
 */
void cls (void);

/**
 * function Play
 * 	runs the game
 */
void Play();

/**
 * function RandomValues
 * 	used to define all random values
 * 	Minimum and Maximum parameters
 */
int RandomValues(int Minimum, int Maximum);

/**
 * function InitCharacter
 * 	create *character
 * 	based on Character_t
 */
void InitCharacter(Character_t *character);
 
/**
 * function InitPlayer
 * 	create the Player Character
 */
void InitPlayer(Character_t *character);

/**
 * Function lvlUp
 * upgrade player
 * based on character_t
 */
void lvlUp(Character_t *character);

/**
 * function MonsterCopy
 * 	used to define fighter
 * 	*MT (monster target) takes
 * 		MS (monster source) attributes
 */
void MonsterCopy(Character_t *MT, Character_t MS);

/**
 * function MonsterInit
 * 	create the Non Player Character
 */
void MonsterInit(Character_t *monster, int rank);

/**
 * function MonsterDisplay
 * 	display the monster's detail
 */
void MonsterDisplay(Character_t monster);

/**
 * function MonstersList
 * 	display the existing monsters
 */
void MonstersList(Character_t *TabMonster, int taille);

/**
 * function MonstersInitNames
 * 	define the names for opponents
 */
void MonstersInitNames(Character_t *TabMonster);

/**
 * function MonstersInit
 * 	create the Non Player Characters
 */
void MonstersInit(Character_t *TabMonster, int taille);

/**
 * Function InitFighter
 * 	find a playable monster from *monsters
 */
void InitFighter(Character_t * monster, Character_t *TabMonster, int taille);

/**
 * function DamageCharacter
 * 	define damages done by Attacker to *Defender
 */
void DamageCharacter(Character_t Attacker, Character_t * Defender);

/**
 * 	function Defense
 * 	upgrade ResBonus by 1 and 
 * 	StrBonus by 1 one time
 **/
void Defense(Character_t * Defender, int StrBeforeFight, int ACBeforeFight);

/**
 * function FightHeroturn
 * 	Hero's turn
 */
void FightHeroTurn(Character_t * Hero, Character_t * Monster, int StrBeforeFight,int ACBeforeFight);

/**
 * function FightMonsterturn
 * 	Monster's turn
 */
void FightMonsterTurn(Character_t * Monster, Character_t * Hero, int StrHeroBeforeFight, int ACHeroBeforeFight);

/**
 * function DisplayDeath
 * 	shows last message
 */
void DisplayDeath();

/**
 * function DisplayCharacter
 * 	shows the character stats
 */
void DisplayCharacter(Character_t character);

/**
 * function ActionMenu
 * 	display option for player
 */
void ActionMenu();

/**
 * function DisplayChoose
 * 	invite user
 */
void DisplayChoose(char *text);

/**
 * function ChooseLanguage
 * 	select the language
 */
void ChooseLanguage();

/**
 * function DisplayLine
 * 	an horizontal line
 */
void DisplayLine();

/**
 * function DisplayEnter
 * 	invit player to push enter
 */
void DisplayEnter();

/**
 * function DisplayTop
 * 	for the top part of the screen
 */
void DisplayTop(char *text);

/**
 * function DisplayTitle
 * 	screen
 */
void DisplayTitle();

/**
 * function DisplayIntro
 * 	start screen
 */
void DisplayIntro();

/**
 * function DisplayOutro
 * 	end screen
 */
void DisplayOutro();

/**
 * function DisplayWarning
 * 	first message
 */
void DisplayWarning();

#endif // FUNCTIONS_H_INCLUDED
