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
 * lastupdate:	171221
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
char PlayerAction[20] = "";
char Language[20] = "";

/*	player	*/
Character_t hero;
/*	opponents	*/
Character_t monstersList[2];
/*	names for monsters	*/
char monstersNames[100][255];
/*	victories count	*/
int victories=0;

/*	Inventory for shop	*/
Inventory_t ShopInv[10];
Equipment_t ShopEqu[5];

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
int RandomValues(int Minimum, int Maximum)
{
	/*	Esay function for all random values	*/
	return rand() % (Maximum - Minimum + 1) + Minimum;
}

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
	character->Strength = RandomValues(8, 18); //Between 3 and 18
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
	character->Resistance = RandomValues(8, 18);
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
	if(Language[0] == 'F')
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
	
	character->Health += RandomValues(1, 6);
	printf("Vous avez maintenant %d points de vie\n", character->Health);
	
	printf("Veuillez appuyer sur [entrée] pour continuer");
	getchar();
	
	//	Every 2 levels, player gain +1 to Str bonus
	if(character->Level % 2 == 0)
		character->StrBonus += 1;
}

void MonsterCopy(Character_t *MT, Character_t MS)
{
	strcpy(MT->Name,MS.Name);
	MT->Level = MS.Level;
	MT->Health = MS.Health;
	MT->Strength = MS.Strength;
	MT->Resistance = MS.Resistance;
	MT->Exp = MS.Exp;
}

void MonsterInit(Character_t *monster, int rank)
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
	monster->Level = rank;
	monster->ArmorClass = armor;
	monster->Health = RandomValues(1, 6) + bonus;
	if(monster->Health <= 0)
		monster->Health = 1;
	monster->Strength = RandomValues(1, 6) + bonus;
	if(monster->Strength <= 0)
		monster->Strength = 1;
	monster->Resistance = RandomValues(1, 6) + bonus;
	if(monster->Resistance <= 0)
		monster->Resistance = 1;
	monster->Exp = xp;
	//DEBUG_PRINT(("%d\n", monster->ArmorClass)); //Just for test
}

void MonsterDisplay(Character_t monster)
{
	DEBUG_PRINT(("%s\n",monster.Name));
	DEBUG_PRINT(("\tRang : %d\n",monster.Level));
	DEBUG_PRINT(("\tVie : %d\n",monster.Health));
	DEBUG_PRINT(("\tForce : %d\n",monster.Strength));
	DEBUG_PRINT(("\tDefense : %d\n",monster.Resistance));
}

void MonstersList(Character_t *TabMonster, int taille)
{
	int i=0;
	for(i=0;i<taille;i++)
	{
		MonsterDisplay(TabMonster[i]);
		printf("\n");
	}
}

void MonstersInitNames(Character_t * monsters)
{
	strcpy(monsters[0].Name,"Goblin");
	strcpy(monsters[1].Name,"Hobgoblin");
}

void MonstersInit(Character_t *monsters, int taille)
{
	int i=0;
	int rank = 0;
	MonstersInitNames(monsters);
	for(i=0;i<taille;i++)
	{
		rank=i;	//	modify when monster system exists
		MonsterInit(&monsters[i], rank);
	}
}

void DamageCharacter(Character_t Attaker, Character_t *Defender)
{
	/*	init variables	*/
	int ToHit=0, damage = 0;
	ToHit = RandomValues(1, 20) + Attaker.StrBonus;/* If rnd give >= 19 */ 
	//	ToHit need to be sup than ArmorClass to make damages
	if(ToHit >= Defender->ArmorClass)
	{
		damage = RandomValues(1, 6) + Attaker.StrBonus;	//Actually 1D6 but it can be change with some weapons
		/*	test about bug	*/
		if (ToHit > 20)
			printf("*****\tVoila donc le bug :P\n");
		if (ToHit >= 19 && ToHit <= 20)
		{
			if(Language[0] == 'F')
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
			if(Language[0] == 'F')
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
		if(Language[0] == 'F')
			printf("Vous ratez votre coup... Vous faites %d\n", ToHit);
		else
			printf("You missed... You did %d\n", ToHit);
	}
}	

void InitFighter(Character_t * monster, Character_t * monsters, int taille)
{
	int i;
	i = (rand() % (1 - 0 + 1)) + 0; //Initialize i for monsters
	if (i<0)
		i=0;
	if(i>taille)
		i=taille-1;

	if(monsters[i].Health<=0)
		InitFighter(monster, monsters, taille);
	else
		MonsterCopy(monster, monsters[i]);
}

void Fight(Character_t *Fighter1, Character_t *Fighter2)
{
	do
	{
		/*	reset PlayerAction	*/
		strcpy(PlayerAction, "");
		/*	Player's turn	*/
		if(strcmp(Fighter1->Name,hero.Name)==0)
		{
			/*	invite Player to take action	*/
			printf("C'est votre tour d'attaquer contre %s, que voulez-vous faire?\n", Fighter2->Name);
			printf("\t[A]ttaquer\n\t[D]efendre\n");
			printf("Votre choix? : ");
			scanf("%s", PlayerAction);
			getchar();
			/*	give feedback of keyboard entry	*/
			PlayerAction[0] = toupper(PlayerAction[0]);
			printf("Vous avez entre : %c\n", PlayerAction[0]);
			/*	result of the chosen action	*/
			if(PlayerAction[0] != 'A' && PlayerAction[0] != 'D')
					printf("Mauvais choix \n");
			if (PlayerAction[0] == 'A')
				DamageCharacter(*Fighter1, Fighter2);
		}
		/*	Monster's turn	*/
		else
		{
			printf("%s vous attaque\n", Fighter1->Name);
			DamageCharacter(*Fighter1, Fighter2);
		}
		/*	display the remaining life	*/
		printf("%d vie %s\n", Fighter2->Health, Fighter2->Name);
		/*	next round	*/
		if (Fighter2->Health > 0)
			Fight(Fighter2,Fighter1);
	} while(Fighter1->Health > 0 && Fighter2->Health > 0);	//	as long as both are alive
	/*	after fight	*/
	if(Fighter1->Health > 0)
	{
		victories++;
		Fighter1->Exp += Fighter2->Exp;
		printf("Vous avez gagne le combat !\n");
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
	/*	reset PlayerAction	*/
	strcpy(PlayerAction,"");
	Character_t tempMonster;
	
	/*	Loop until PlayerAction > 1 char	*/
	/*	invite Player to take action	*/
	do
	{
		printf("\nVous pouvez : ");
		printf("\n\t[V]oir votre personnage");
		printf("\n\t[F]aire le combat");
		printf("\n\t[Q]uitter");
		printf("\n\nVotre choix? : ");
		scanf("%s", PlayerAction);
		getchar();
		/*	result of the chosen action	*/
		if(strlen(PlayerAction) > 1)
			printf("Veuillez ne saisir qu'une lettre\n");
	}while(strlen(PlayerAction) > 1);
	PlayerAction[0] = toupper(PlayerAction[0]);
	switch(PlayerAction[0])
	{
		case 'V':
			DisplayCharacter(hero);
			break;
		case 'F':
			printf("Vous allez rencontrer un monstre !\n");
			InitFighter(&tempMonster, monstersList, 2);
			Fight(&hero, &tempMonster );
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
	printf("|*****          Welcome          *****|\n");
	printf("|*************************************|\n");
	
	/*	Loop until Language > 1 char and Language != F or E	*/
	do
	{	
		printf("Select your language\n");
		printf("\t[F]rancais\n");
		printf("\t[E]nglish\n");
		scanf("%s", Language);
		getchar();
		Language[0] = toupper(Language[0]);
		/*	result of the chosen action	*/
		if(strlen(Language) > 1)
			printf("Veuillez ne saisir qu'une lettre\n");
		if(Language[0] != 'F' || Language[0] != 'E')
			printf("Veuillez saisir soit F soit E\n");
		
	}while(strlen(Language) > 1 || Language[0] != 'F' && Language[0] != 'E');
	
	/*	Loop until PlayerAction > 1 char and PlayerAction[0] != C or Q	*/
	do
	{	
		/*	reset PlayerAction	*/
		PlayerAction[0] = '\0';
		/*	invite Player to take action	*/
		if (Language[0] == 'F')
			printf("\n\t[C]réer un personnage\n\t[Q]uitter\n\nVotre choix? : ");
		else
			printf("\n\t[C]reate your character\n\t[Q]uit\n\nYour choice? : ");
		scanf("%s", PlayerAction);
		getchar();
		PlayerAction[0] = toupper(PlayerAction[0]);
		/*	result of the chosen action	*/
		if(strlen(PlayerAction) > 1)
			printf("Veuillez ne saisir qu'une lettre\n");		
		if(PlayerAction[0] != 'C' || PlayerAction[0] != 'Q')
			printf("Veuillez saisir soit C soit Q\n");
			
	}while(strlen(PlayerAction) > 1 || PlayerAction[0] != 'C' && PlayerAction[0] != 'Q'); 
	switch(PlayerAction[0])
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
	if(Language[0] == 'F')
		printf("|*****         Au revoir         *****|\n");
	else
		printf("|*****          See you          *****|\n");
	printf("|*************************************|\n");
	exit(1);
}

void Play()
{
	DisplayIntro();
	MonstersInit(monstersList, 2);
	MonstersList(monstersList, 2);
	ActionMenu();
}
