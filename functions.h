#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include "constantes.h"

/*
functions.h
#######################################

Purpose : prototypes for the game functions.
*/
void cls (void);

/**
 * function Play();
 * 	runs the game
 */
void Play();

/**
 * function Random
 * 	used to define all random values
 * 	Minimum and Maximum parameters
 **/
 int RandomValues(int Minimum, int Maximum);
 
/**
 * function InitPlayer
 * 	create the Player Character
 */
void InitPlayer(Character_t *character);

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
void MonstersInitNames(Character_t * monsters);

/**
 * function MonstersInit
 * 	create the Non Player Characters
 */
void MonstersInit(Character_t *TabMonster, int taille);

/**
 * function InitCharacter
 * 	create *character
 * 	based on Character_t
 */
void InitCharacter(Character_t *character);

/**
 * Function lvlUp
 * upgrade player
 * based on character_t
 */
void lvlUp(Character_t *character);

/**
 * Function InitFighter
 * 	find a playable monster from *monsters
 */
void InitFighter(Character_t * monster, Character_t * monsters, int taille);

/**
 * function DamageCharacter
 * 	define damages done by Attacker to *Defender
 */
void DamageCharacter(Character_t Attacker, Character_t *Defender);

/**
 * function Fight
 * 	define the involved fighters
 */
void Fight(Character_t *Fighter1, Character_t *Fighter2);

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
