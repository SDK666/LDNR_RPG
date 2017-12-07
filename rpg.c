#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
/*
 * author:	Lethael
 * creationdate:171204
 * correction:	SDK666
 * translation:	SDK666
 * lastupdate:	171207
 * lastupdateby:Lethael
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
	int Health;	//	points of life
	int Strength;	//	attack power
	int Resistance;	//	defense
};

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

main()
{
	/*	initialize srand to current time	*/
	srand(time(NULL));
	/*	variables	*/
	struct Character hero;		//	player
	struct Character monster;	//	opponent
	/*	player's choice	*/
	char PlayerAction = '\0';
	/*	initialize player and opponent	*/
	InitCharacter(&hero); // A modifier pour mettre en dur juste pour le héro	//	à discuter ;)
	InitCharacter(&monster);
	
	//	fight loop, to put in a Fight function
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
			DamageCharacter(hero, &monster);
		//	for now it can only be an attack from the player
		printf("%d vie monstre\n", monster.Health);
	}while(hero.Health >= 0 && monster.Health >= 0);	//	as long as both are alive
}

void InitCharacter(struct Character *character)
{
	//	invite message to be changed according to character creation decisions
	/*	sets character name	*/
	printf("Veuillez saisir le nom du personnage : \n");
	scanf("%s", character->Name);
	getchar();
	character->Health = 100;	//	set character's health
	/*	randomize Strength and Resistance	*/
	character->Strength = (rand() % (10 - 1 + 1)) + 1; //Between 1 and 10
	printf("%d Strength\n", character->Strength); //Just for test
	character->Resistance = (rand() % (6 - 1 + 1)) + 1;
}

void DamageCharacter(struct Character Attaker, struct Character *Defender)
{
	//	!!! WARNING : there's no check if defender has better resistance than the attacker's strength !!!
	//		actually a NPC can gain HP if damage is negative !!!
	int damage;
	damage = (Attaker.Strength + (rand() % (7 - 1 + 1)) + 1) - Defender->Resistance / 2; // With divid by 2, result is better
	printf("%d degats !\n", damage);
	Defender->Health -= damage;
}	
