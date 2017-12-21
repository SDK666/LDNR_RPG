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
 * lastupdate:	171215
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
	int Level;
	int Exp;
	int ExpNextLvl;	//  EXP needed for next level by Level * ExpNextLevel	
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
char Language = '\0';

/*	player	*/
Character_t hero;
/*	opponents	*/
Character_t monster[2]; 
/*	victories count	*/
int victories=0;

/*	Inventory for shop	*/
Inventory_t ShopInv[10];
Equipment_t ShopEqu[5];

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
 * Function lvlUp
 * upgrade player
 * based on character_t
 */
void lvlUp(Character_t *character);
 
/**
 * function DamageCharacter
 * 	define damages done by Attaker to *Defender
 */
void DamageCharacter(Character_t Attaker, Character_t *Defender);

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
	/*	Initialize Level, exp, and ExpNextLevel	*/
	character->Level = 1;
	character->Exp = 0;
	character->ExpNextLvl = 1500;
	
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
	int i;
	/*	sets character name	*/
	if(Language == 'F')
		printf("Quel est votre nom? \n");
	else
		printf("What's your name? \n");
	scanf("%s", character->Name);
	getchar();

	InitCharacter(character);
}

void lvlUp(Character_t *character)
{
	char Waiting[20];
	character->Level += 1;
	character->ExpNextLvl *= character->Level;
	
	character->Health += ((rand() % (6 - 1 + 1)) + 1);
	printf("Vous avez maintenant %d points de vie\n", character->Health);
	
	printf("Veuillez appuyer sur [entrée] pour continuer");
	getchar();
	
	//	Every 2 levels, player gain +1 to Str bonus
	if(character->Level % 2 == 0)
		character->StrBonus += 1;
}
void InitMonster(Character_t *monster)
{
	
	if(strcmp(monster->Name, "Goblin") == 0)
	{
		monster->ArmorClass = 12;
		monster->Health = ((rand() % (6 - 1 + 1)) + 1) - 1;	//1D6 -1
		if(monster->Health <= 0)
			monster->Health = 1;
		monster->Exp = 500;
	}
	if(strcmp(monster->Name, "Hobgoblin") == 0)
	{
		monster->ArmorClass = 14;
		monster->Health = ((rand() % (6 - 1 + 1)) + 1) + 1; //1D6
		monster->Exp = 600;
	}	
	//DEBUG_PRINT(("%d\n", monster->ArmorClass)); //Just for test
}

void DamageCharacter(Character_t Attaker, Character_t *Defender)
{
	/*	init variables	*/
	int ToHit=0, damage = 0;
	ToHit = ((rand() % (20 - 1 + 1)) + 1) + Attaker.StrBonus;/* If rnd give >= 19 */ 
	//	ToHit need to be sup than ArmorClass for to make damages
	if(ToHit >= Defender->ArmorClass)
	{
		damage = ((rand() % (6 - 1 + 1)) + 1) + Attaker.StrBonus;	//Actually 1D6 but it can be change with some weapons
		if (ToHit >= 19 && ToHit <= 20)
		{
			if(Language == 'F')
			{
				printf("Vous lancez le de, et faites... Un CRITIQUE !!! %d\n", ToHit);
				printf("Vous frappez votre ennemi de toutes vos forces! Ses os se brisent sous vos coups\n");
				damage += 6;
				printf("Vous faites %d degats !\n", damage);
			}
			else
			{ 
				printf("You roll your dice and it does... a CRITICAL HIT !!! %d\n", ToHit);
				printf("You crush your enemy with all of your power ! Some of his bones are broken!\n");
				damage += 6;
				printf("You make %d damages !\n", damage);
			}
		}
		if (ToHit < 19)
		{
			if(Language == 'F')
			{
				printf("Vous lancez le de, et faites...! %d\n", ToHit);
				printf("Vous faites %d degats !\n", damage);
			}
			else
			{
				printf("You roll your dice and it does...%d\n", ToHit);
				printf("You slice %s, and his blood falling to the ground\nYou make %d damages !\n", Defender->Name, damage);
			}
		}
		Defender->Health -= damage;
	}
	if (ToHit < Defender->ArmorClass)
	{
		if(Language == 'F')
			printf("Vous ratez votre coup... Vous faites %d\n", ToHit);
		else
			printf("You missed... You did %d\n", ToHit);
	}
}	

void Fight(Character_t *Fighter1, Character_t *TabFighter2)
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
			DamageCharacter(*Fighter1, &TabFighter2[i]);
		//	for now it can only be an attack from the player
		printf("%d vie monstre\n", TabFighter2[i].Health);
	} while(Fighter1->Health > 0 && TabFighter2[i].Health > 0);	//	as long as both are alive
	/*	after fight	*/
	if(Fighter1->Health > 0)
	{
		victories++;
		Fighter1->Exp += TabFighter2[i].Exp;
		if(Fighter1->Exp >= Fighter1->ExpNextLvl)
		{
			printf("Vous avez gagne un niveau !\n");
			lvlUp(Fighter1);
		}
	}
	ActionMenu();
}

void DisplayCharacter(Character_t character)
{
	char Waiting[20];
	printf("Caractéristiques de %s\n",character.Name);
	printf("\tLevel \t:\t\t%d\n",character.Level);
	printf("\tVie \t:\t\t%d\n",character.Health);
	printf("\tForce \t:\t\t%d\n",character.Strength);
	printf("\tDéfense\t:\t\t%d\n",character.Resistance);
	printf("\tExp\t:\t\t%d\n",character.Exp);
	printf("\tVictoire :\t\t%d\n",victories);
	printf("\tProchain niveau:\t%d exp\n", character.ExpNextLvl - character.Exp);
	printf("Veuillez appuyer sur [entrée] pour continuer");
	getchar();
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
			Fight(&hero,monster);
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
	
	printf("Select your language\n[F]rancais\n[E]nglish\n");
	scanf("%c", &Language);
	getchar();
	Language = toupper(Language);
	/*	reset PlayerAction	*/
	PlayerAction = '\0';
	/*	invite Player to take action	*/
	if (Language == 'F')
		printf("\n\t[C]réer un personnage\n\t[Q]uitter\n\nVotre choix? : ");
	else
		printf("\n\t[C]reate your character\n\t[Q]uit\n\nYour choice? : ");
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
