#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
/*
 * author:		Lethael
 * creationdate:171204
 * correction:	SDK666
 * translation:	SDK666
 * lastupdate:	171211
 * lastupdateby:SDK666
 * 
 * game base for simplified RPG-like
 */

/**
 * structure Character
 * 	defines anyone (player or opponent)
 */
struct Character
{
	char Name[30];
	int Health;		//	points of life
	int Strength;	//	attack power
	int Resistance;	//	defense
};

/**
 * function InitPlayer
 * 	create the Player Character
 */
void InitPlayer(struct Character *character);

/**
 * function InitMonster
 * 	create the Non Player Character
 */
void InitMonster(struct Character *character);

/**
 * function InitCharacter
 * 	create *character
 * 	based on struct Character
 */
void InitCharacter(struct Character *character);

/**
 * function DamageCharacter
 * 	define damages done by Attaker to *Defender
 */
void DamageCharacter(struct Character Attaker, struct Character *Defender);

/**
 * function Fight
 * 	define the involved fighters
 */
void Fight(struct Character Fighter1, struct Character Fighter2);

main()
{
	/*	initialize srand to current time	*/
	srand(time(NULL));
	/*	variables	*/
	struct Character hero;		//	player
	struct Character monster;	//	opponent
	/*	initialize player and opponent	*/
	InitPlayer(&hero);
	InitMonster(&monster);
	
	/*	the fight	*/
	Fight(hero,monster);
}

void InitCharacter(struct Character *character)
{
	character->Health = 100;	//	set character's health
	/*	randomize Strength and Resistance	*/
	character->Strength = (rand() % (10 - 1 + 1)) + 1; //Between 1 and 10
	printf("%d Strength\n", character->Strength); //Just for test
	character->Resistance = (rand() % (6 - 1 + 1)) + 1;
}

void InitPlayer(struct Character *character)
{
	/*	sets character name	*/
	printf("Veuillez saisir votre nom : \n");
	scanf("%s", character->Name);
	getchar();
	InitCharacter(character);
}

void InitMonster(struct Character *character)
{
	strcpy(character->Name,"someMonster");
	InitCharacter(character);
}

void DamageCharacter(struct Character Attaker, struct Character *Defender)
{
	/*	init variables	*/
	int damage=0;
	damage = (Attaker.Strength + (rand() % (7 - 1 + 1)) + 1) - Defender->Resistance / 2; // With divide by 2, result is better
	/*	check result	*/
	if(damage>0)
	{
		printf("%d degats !\n", damage);
		Defender->Health -= damage;
	}
}	

void Fight(struct Character Fighter1, struct Character Fighter2)
{
	/*	player's choice	*/
	char PlayerAction = '\0';
	do
	{
		/*	reset PlayerAction	*/
		PlayerAction = '\0';
		/*	invite Player to take action	*/
		printf("C'est votre tour d'attaquer, que voulez-vous faire?\n\t[A]ttaquer\n\t[D]efendre\nVotre choix? : ");
		scanf("%c", &PlayerAction);
		getchar();
		/*	give feedback of keyboard entry	*/
		printf("Vous avez entre : %c\n", PlayerAction);
		/*	result of the chosen action	*/
		if(PlayerAction != 'a')
				printf("Mauvais choix \n");
		if (PlayerAction == 'a')
			DamageCharacter(Fighter1, &Fighter2);
		//	for now it can only be an attack from the player
		printf("%d vie monstre\n", Fighter2.Health);
	} while(Fighter1.Health >= 0 && Fighter2.Health >= 0);	//	as long as both are alive
}
