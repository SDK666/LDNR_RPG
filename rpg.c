#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#define DEBUG 1
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

/*
 * author:		Lethael
 * creationdate:171204
 * correction:	SDK666
 * translation:	SDK666
 * lastupdate:	171213
 * lastupdateby:SDK666
 * 
 * game base for simplified RPG-like
 */
 
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
	int Health;		//	points of life
	int Strength;	//	attack power
	int Resistance;	//	defense
	int ArmorClass;	//	Protection's value
	int StrBonus;	//	strenght bonus if str >= 13
	int ResBonus;	//	resistance bonus if str >= 13
	Inventory_t Bag[5];
	Equipment_t Equip[5];
}Character_t;


/*	player's choice	*/
char PlayerAction = '\0';

/* Inventory + Equipment */

/*	player	*/
Character_t hero;
/*	opponents	*/
Character_t monster[2]; 
/*	victories count	*/
int victories=0;

/**
 * function InitPlayer
 * 	create the Player Character
 */
void InitPlayer(Character_t *character);

/**
 * function InitMonster
 * 	create the Non Player Character
 */
void InitMonster(Character_t *TabMonster);

/**
 * function InitCharacter
 * 	create *character
 * 	based on Character_t
 */
void InitCharacter(Character_t *character);

/**
 * function DamageCharacter
 * 	define damages done by Attaker to *Defender
 */
void DamageCharacter(Character_t Attaker, Character_t *Defender);

/**
 * function Fight
 * 	define the involved fighters
 */
void Fight(Character_t Fighter1, Character_t *Fighter2);

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
 * function Play();
 * 	runs the game
 */
void Play();

main()
{
	
	/*	initialize srand to current time	*/
	srand(time(NULL));
	Play();
}

/* #################### FONCTIONS ################### */
void InitCharacter(Character_t *character)
{
	/*	Initialize bonus to 0	*/
	character->StrBonus = 0;	// Bonus for upgrade damage
	character->ResBonus = 0;	// Bonus for upgrade Health and Armor Class
	/*	randomize Strength and Resistance	*/
	/*	########## BEGIN STRENGTH ##########	*/
	character->Strength = (rand() % (18 - 8 + 1)) + 8; //Between 3 and 18
	/*	Attribute Strenght Bonus if random is better than 13	*/
	if(character->Strength >= 13 && character->Strength <=15)
		character->StrBonus = 1;
	if(character->Strength >= 16 && character->Strength <=17)
		character->StrBonus = 2;
	if(character->Strength == 18)
		character->StrBonus = 3;
	/*	End of attribute Strenght Bonus	*/
	DEBUG_PRINT(("%d Strength\n", character->Strength)); //Just for test
	/*	########## END STRENGTH ##########	*/
	
	/*	########## BEGIN RESISTANCE ##########	*/
	character->Resistance = (rand() % (18 - 8 + 1)) + 8;
	/*	Attribute Resitance Bonus if random is better than 13	*/
	if(character->Resistance >= 13 && character->Resistance <=15)
		character->ResBonus = 1;
	if(character->Resistance >= 16 && character->Resistance <=17)
		character->ResBonus = 2;
	if(character->Resistance == 18)
		character->ResBonus = 3;
	/*	End of attribute ResitanceBonus */
	DEBUG_PRINT(("%d Resistance\n", character->Resistance)); //Just for test
	/*	########## END RESISTANCE ##########	*/
	
	character->ArmorClass = 10 + character->ResBonus; /* + nothing actually. Need to have Armor 
	
	/*	Initialize Health	*/
	character->Health = 6 + character->ResBonus;	//	set character's health by 6 + ResBonus and for next lvl it's Health + rnd 1-6 + ResBonus 
	DEBUG_PRINT(("%d Health\n", character->Health)); //Just for test
}

void InitPlayer(Character_t *character)
{
	/*	sets character name	*/
	printf("Veuillez saisir votre nom : \n");
	scanf("%s", character->Name);
	getchar();
	InitCharacter(character);
}

void InitMonster(Character_t *character)
{
	InitCharacter(character);
}

void DamageCharacter(Character_t Attaker, Character_t *Defender)
{
	/*	init variables	*/
	int damage=0;
	damage = ((rand() % (20 - 1 + 1)) + 1);/* If rnd give > 18 */ 
	if (damage > 18 && damage < 21)
	{ 
		printf("You roll your dice and it does... a CRITICAL HIT !!! %d\n", damage);
		damage += Attaker.StrBonus - (Defender->ArmorClass + Defender->ResBonus);
		damage += 6;
	}
	else
	{
		printf("You roll your dice and it does...%d\n", damage);
		damage += Attaker.StrBonus - (Defender->ArmorClass + Defender->ResBonus);
	}
	/*	check result	*/
	if(damage == 0 )
	{
		damage = 1;
		printf("You hit just enough for to make %d damage !\n", damage);
		Defender->Health -= damage;
	}
	if (damage < 0)
	{
		damage = 0;
		printf("You missed !\n");
	}
	if(damage > 0)
	{
		printf("You slice %s, and his blood falling to the ground\nYou make %d damages !\n", Defender->Name, damage);
		Defender->Health -= damage;
	}
}	

void Fight(Character_t Fighter1, Character_t *TabFighter2)
{
	int i;
	strcpy(TabFighter2[0].Name, "Goblin");
	strcpy(TabFighter2[1].Name, "Hobgoblin");
	
	i = (rand() % (1 - 0 + 1)) + 0; //Initialize i for TabMonsters
			
	if(TabFighter2[i].Health<=0)
		InitMonster(&TabFighter2[i]);
	do
	{
		/*	reset PlayerAction	*/
		PlayerAction = '\0';
		/*	invite Player to take action	*/
		printf("C'est votre tour d'attaquer contre %s, que voulez-vous faire?\n\t[A]ttaquer\n\t[D]efendre\nVotre choix? : ", TabFighter2[i].Name);
		scanf("%c", &PlayerAction);
		getchar();
		/*	give feedback of keyboard entry	*/
		printf("Vous avez entre : %c\n", PlayerAction);
		/*	result of the chosen action	*/
		if(PlayerAction != 'a')
				printf("Mauvais choix \n");
		if (PlayerAction == 'a')
			DamageCharacter(Fighter1, &TabFighter2[i]);
		//	for now it can only be an attack from the player
		printf("%d vie monstre\n", TabFighter2[i].Health);
	} while(Fighter1.Health > 0 && TabFighter2[i].Health > 0);	//	as long as both are alive
	/*	after fight	*/
	if(Fighter1.Health > 0)
	{
		victories++;
	}
	ActionMenu();
}

void DisplayCharacter(Character_t character)
{
	printf("Caractéristiques de %s\n",character.Name);
	printf("\tVie \t:\t%d\n",character.Health);
	printf("\tForce \t:\t%d\n",character.Strength);
	printf("\tDéfense\t:\t%d\n",character.Resistance);
	printf("\tVictoire :\t%d\n",victories);
	ActionMenu();
}

void ActionMenu()
{
	printf("Vous allez rencontrer un monstre !\n");
	/*	reset PlayerAction	*/
	PlayerAction = '\0';
	/*	invite Player to take action	*/
	printf("\nVous pouvez : ");
	printf("\n\t[V]oir votre personnage");
	printf("\n\t[F]aire le combat");
	printf("\n\t[Q]uitter");
	printf("\n\nVotre choix? : ");
	scanf("%c", &PlayerAction);
	getchar();
	PlayerAction = toupper(PlayerAction);
	switch(PlayerAction)
	{
		case 'V':
			DisplayCharacter(hero);
			break;
		case 'F':
			Fight(hero,monster);
			break;
		case 'Q':
			DisplayOutro();
			break;
		default:
			ActionMenu();
			break;
	}
}

void DisplayIntro()
{
	/*	invite screen	*/
	printf("|*************************************|\n");
	printf("|*****         Bienvenue         *****|\n");
	printf("|*************************************|\n");
	
	/*	reset PlayerAction	*/
	PlayerAction = '\0';
	/*	invite Player to take action	*/
	printf("\n\t[C]réer un personnage\n\t[Q]uitter\n\nVotre choix? : ");
	scanf("%c", &PlayerAction);
	getchar();
	PlayerAction = toupper(PlayerAction);
	switch(PlayerAction)
	{
		case 'C':
			InitPlayer(&hero);
			break;
		case 'Q':
			DisplayOutro();
			break;
		default:
			DisplayIntro();
			break;
	}
}

void DisplayOutro()
{
	printf("|*************************************|\n");
	printf("|*****          See you          *****|\n");
	printf("|*************************************|\n");
	exit(1);
}

void Play()
{
	DisplayIntro();
	ActionMenu();
}

#ifdef DEBUG
# define DEBUG_PRINT(x) printf x
#else
# define DEBUG_PRINT(x) do {} while (0)
#endif

/*
 * author:		Lethael
 * creationdate:171204
 * correction:	SDK666
 * translation:	SDK666
 * lastupdate:	171213
 * lastupdateby:Lethael
 * 
 * game base for simplified RPG-like
 */
 
 /**
  *  Structure Equipment
  * Weapons, Armors, Shields
  * */
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
	int Health;		//	points of life
	int Strength;	//	attack power
	int Resistance;	//	defense
	int ArmorClass;	//	Protection's value
	int StrBonus;	//	strenght bonus if str >= 13
	int ResBonus;	//	resistance bonus if str >= 13
	Inventory_t Bag[5];
	Equipment_t Equip[5];
}Character_t;


/*	player's choice	*/
char PlayerAction = '\0';

/* Inventory + Equipment */

/*	player	*/
Character_t hero;
Character_t monster[2]; 
/*	victories count	*/
int victories=0;

/**
 * function InitPlayer
 * 	create the Player Character
 */
void InitPlayer(Character_t *character);

/**
 * function InitMonster
 * 	create the Non Player Character
 */
void InitMonster(Character_t *TabMonster);

/**
 * function InitCharacter
 * 	create *character
 * 	based on Character_t
 */
void InitCharacter(Character_t *character);

/**
 * function DamageCharacter
 * 	define damages done by Attaker to *Defender
 */
void DamageCharacter(Character_t Attaker, Character_t *Defender);

/**
 * function Fight
 * 	define the involved fighters
 */
void Fight(Character_t Fighter1, Character_t *Fighter2);

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
 * function Play();
 * 	runs the game
 */
void Play();

main()
{
	
	/*	initialize srand to current time	*/
	srand(time(NULL));
	Play();
}

/* #################### FONCTIONS ################### */
void InitCharacter(Character_t *character)
{
	/*	Initialize bonus to 0	*/
	character->StrBonus = 0;	// Bonus for upgrade damage
	character->ResBonus = 0;	// Bonus for upgrade Health and Armor Class
	/*	randomize Strength and Resistance	*/
	/*	########## BEGIN STRENGTH ##########	*/
	character->Strength = (rand() % (18 - 8 + 1)) + 8; //Between 3 and 18
	/*	Attribute Strenght Bonus if random is better than 13	*/
	if(character->Strength >= 13 && character->Strength <=15)
		character->StrBonus = 1;
	if(character->Strength >= 16 && character->Strength <=17)
		character->StrBonus = 2;
	if(character->Strength == 18)
		character->StrBonus = 3;
	/*	End of attribute Strenght Bonus	*/
	DEBUG_PRINT(("%d Strength\n", character->Strength)); //Just for test
	/*	########## END STRENGTH ##########	*/
	
	/*	########## BEGIN RESISTANCE ##########	*/
	character->Resistance = (rand() % (18 - 8 + 1)) + 8;
	/*	Attribute Resitance Bonus if random is better than 13	*/
	if(character->Resistance >= 13 && character->Resistance <=15)
		character->ResBonus = 1;
	if(character->Resistance >= 16 && character->Resistance <=17)
		character->ResBonus = 2;
	if(character->Resistance == 18)
		character->ResBonus = 3;
	/*	End of attribute ResitanceBonus */
	DEBUG_PRINT(("%d Resistance\n", character->Resistance)); //Just for test
	/*	########## END RESISTANCE ##########	*/
	
	character->ArmorClass = 10 + character->ResBonus; /* + nothing actually. Need to have Armor 
	
	/*	Initialize Health	*/
	character->Health = 6 + character->ResBonus;	//	set character's health by 6 + ResBonus and for next lvl it's Health + rnd 1-6 + ResBonus 
	DEBUG_PRINT(("%d Health\n", character->Health)); //Just for test
}

void InitPlayer(Character_t *character)
{
	/*	sets character name	*/
	printf("Veuillez saisir votre nom : \n");
	scanf("%s", character->Name);
	getchar();
	InitCharacter(character);
}

void InitMonster(Character_t *character)
{
	InitCharacter(character);
}

void DamageCharacter(Character_t Attaker, Character_t *Defender)
{
	/*	init variables	*/
	int damage=0;
	damage = ((rand() % (20 - 1 + 1)) + 1);/* If rnd give > 18 */ 
	if (damage > 18 && damage < 21)
	{ 
		printf("You roll your dice and it do... a CRITICAL HIT !!! %d\n", damage);
		damage += Attaker.StrBonus - (Defender->ArmorClass + Defender->ResBonus);
		damage += 6;
	}
	else
	{
		printf("You roll your dice and it do...%d\n", damage);
		damage += Attaker.StrBonus - (Defender->ArmorClass + Defender->ResBonus);
	}
	/*	check result	*/
	if(damage == 0 )
	{
		damage = 1;
		printf("You hit just enough for to make %d damage !\n", damage);
		Defender->Health -= damage;
	}
	if (damage < 0)
	{
		damage = 0;
		printf("You missed !\n");
	}
	if(damage > 0)
	{
		printf("You slice %s, and his blood falling to the ground\nYou make %d damages !\n", Defender->Name, damage);
		Defender->Health -= damage;
	}
}	

void Fight(Character_t Fighter1, Character_t *TabFighter2)
{
	int i;
	strcpy(TabFighter2[0].Name, "Goblin");
	strcpy(TabFighter2[1].Name, "Hobgoblin");
	
	i = (rand() % (1 - 0 + 1)) + 0; //Initialize i for TabMonsters
			
	if(TabFighter2[i].Health<=0)
		InitMonster(&TabFighter2[i]);
	do
	{
		/*	reset PlayerAction	*/
		PlayerAction = '\0';
		/*	invite Player to take action	*/
		printf("C'est votre tour d'attaquer contre %s, que voulez-vous faire?\n\t[A]ttaquer\n\t[D]efendre\nVotre choix? : ", TabFighter2[i].Name);
		scanf("%c", &PlayerAction);
		getchar();
		/*	give feedback of keyboard entry	*/
		printf("Vous avez entre : %c\n", PlayerAction);
		/*	result of the chosen action	*/
		if(PlayerAction != 'a')
				printf("Mauvais choix \n");
		if (PlayerAction == 'a')
			DamageCharacter(Fighter1, &TabFighter2[i]);
		//	for now it can only be an attack from the player
		printf("%d vie monstre\n", TabFighter2[i].Health);
	} while(Fighter1.Health > 0 && TabFighter2[i].Health > 0);	//	as long as both are alive
	/*	after fight	*/
	if(Fighter1.Health > 0)
	{
		victories++;
	}
	ActionMenu();
}

void DisplayCharacter(Character_t character)
{
	printf("Caractéristiques de %s\n",character.Name);
	printf("\tVie \t:\t%d\n",character.Health);
	printf("\tForce \t:\t%d\n",character.Strength);
	printf("\tDéfense\t:\t%d\n",character.Resistance);
	printf("\tVictoire :\t%d\n",victories);
	ActionMenu();
}

void ActionMenu()
{
	printf("Vous allez rencontrer un monstre !\n");
	/*	reset PlayerAction	*/
	PlayerAction = '\0';
	/*	invite Player to take action	*/
	printf("\nVous pouvez : ");
	printf("\n\t[V]oir votre personnage");
	printf("\n\t[F]aire le combat");
	printf("\n\t[Q]uitter");
	printf("\n\nVotre choix? : ");
	scanf("%c", &PlayerAction);
	getchar();
	switch(PlayerAction)
	{
		case 'v':
		case 'V':
			DisplayCharacter(hero);
			break;
		case 'f':
		case 'F':
			Fight(hero,monster);
			break;
		case 'q':
		case 'Q':
			DisplayOutro();
			break;
		default:
			ActionMenu();
			break;
	}
}

void DisplayIntro()
{
	/*	invite screen	*/
	printf("|*************************************|\n");
	printf("|*****         Bienvenue         *****|\n");
	printf("|*************************************|\n");
	
	/*	reset PlayerAction	*/
	PlayerAction = '\0';
	/*	invite Player to take action	*/
	printf("\n\t[C]réer un personnage\n\t[Q]uitter\n\nVotre choix? : ");
	scanf("%c", &PlayerAction);
	getchar();
	PlayerAction = toupper(PlayerAction);
	switch(PlayerAction)
	{
		case 'C':
			InitPlayer(&hero);
			break;
		case 'Q':
			DisplayOutro();
			break;
		default:
			DisplayIntro();
			break;
	}
}

void DisplayOutro()
{
	printf("|*************************************|\n");
	printf("|*****          See you          *****|\n");
	printf("|*************************************|\n");
	exit(1);
}

void Play()
{
	DisplayIntro();
	ActionMenu();
}
