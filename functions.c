#include "functions.h"

/*
functions.c
#######################################

Purpose : the game functions.
*/

/* #################### GLOBALS ################### */
/*	player's choice	*/
char PlayerAction[20] = "";
char Language[20] = "";

/*	player	*/
Character_t hero;
/*	opponents	*/
Character_t monstersList[2];
/*	names for monsters	*/
char monstersNames[100][255];

/*	Inventory for shop	*/
Inventory_t ShopInv[10];
Equipment_t ShopEqu[5];

/* #################### FONCTIONS ################### */

/**
 * function cls
 * 		clear screen
 * 		CLEAN_SCREEN depends on OS
 * 		>>> works for Linux and Windows
 */
void cls (void)
{
	system(CLEAN_SCREEN);
}

/**
 * function Play
 * 		runs the game
 * 		and initialize monsters
 */
void Play()
{
	DisplayWarning();
	MonstersInit(monstersList, 2);
	/*	TO DELETE FOR FINAL USE !!!	*/
	MonstersList(monstersList, 2);
	ActionMenu();
}

/**
 * function RandomValues
 * 		used to define all random values
 * 		@param	int Minimum
 * 		@param	int Maximum
 * 		@return	int
 */
int RandomValues(int Minimum, int Maximum)
{
	return rand() % (Maximum - Minimum + 1) + Minimum;
}

/**
 * function InitCharacter
 * 		initialize character's stats
 * 		includes some DEBUG_PRINT
 * 		@param	Character_t *character
 * 		@return	void
 */
void InitCharacter(Character_t *character)
{
	/*	Initialize Level, exp, victories and ExpNextLevel	*/
	character->Level = 1;
	character->Exp = 0;
	character->Victories = 0;
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
	
	character->ArmorClass = 10 + character->ResBonus; // + nothing actually. Need to have Armor 
	
	/*	Initialize Health	*/
	character->Health = 6 + character->ResBonus;	//	set character's health by 6 + ResBonus and for next lvl it's Health + rnd 1-6 + ResBonus 
	DEBUG_PRINT(("%d Health\n", character->Health)); //Just for test
}

/**
 * function InitPlayer
 * 		invite the player to create character
 * 		@param	Character_t *character
 * 		@return	void
 */
void InitPlayer(Character_t *character)
{
	cls();
	if (Language[0] == 'F')
		DisplayTop("  CREER  ");
	else
		DisplayTop(" CREATE  ");
	int i;
	/*	sets character name	*/
	printf("\t");
	if(Language[0] == 'F')
		printf("Quel est votre nom ?");
	else
		printf("What's your name ?");
	printf("\t");
	scanf("%s", character->Name);
	getchar();

	InitCharacter(character);
}

/**
 * Function lvlUp
 * 		upgrade player's stats
 * 		@param	Character_t *character
 * 		@return	void
 */
void lvlUp(Character_t *character)
{
	char Waiting[20];
	character->Level += 1;
	character->ExpNextLvl *= character->Level;
	
	character->Health += RandomValues(1, 6);
	if(Language[0] == 'F')
		printf("\tVous avez maintenant %d points de vie\n", character->Health);
	else
		printf("\tNow you have %d health points\n", character->Health);
	
	//	Every 2 levels, player gain +1 to Str bonus
	if(character->Level % 2 == 0)
		character->StrBonus += 1;
}

/**
 * function MonsterCopy
 * 		create a copy of a monster
 * 		to use in a fight
 * 		@param	Character_t *MT (monster target)
 * 		@param	Character_t MS (monster source)
 * 		@return	void
 */
void MonsterCopy(Character_t *MT, Character_t MS)
{
	strcpy(MT->Name,MS.Name);
	MT->Level = MS.Level;
	MT->Health = MS.Health;
	MT->Strength = MS.Strength;
	MT->Resistance = MS.Resistance;
	MT->Exp = MS.Exp;
}

/**
 * function MonsterInit
 * 		create the Non Player Character
 * 		@param	Character_t *monster
 * 		@param	int rank
 * 		@return	void
 */
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

/**
 * function MonsterDisplay
 * 		shows the monster's stats
 * 		only works in debug mode
 * 		@param	Character_t monster
 * 		@return	void
 */
void MonsterDisplay(Character_t monster)
{
	DEBUG_PRINT(("%s\n",monster.Name));
	DEBUG_PRINT(("\tRang : %d\n",monster.Level));
	DEBUG_PRINT(("\tVie : %d\n",monster.Health));
	DEBUG_PRINT(("\tForce : %d\n",monster.Strength));
	DEBUG_PRINT(("\tDefense : %d\n",monster.Resistance));
}

/**
 * function MonstersList
 * 		runs through the array of monsters
 * 		to display each one's stats
 * 		only works in debug mode
 * 		@param	Character_t *TabMonster
 * 		@param	int taille
 * 		@return	void
 */
void MonstersList(Character_t *TabMonster, int taille)
{
	int i=0;
	for(i=0;i<taille;i++)
	{
		MonsterDisplay(TabMonster[i]);
		printf("\n");
	}
}

/**
 * function MonstersInitNames
 * 		define the names for opponents
 * 		@param	Character_t *TabMonster
 * 		@return	void
 */
void MonstersInitNames(Character_t *TabMonster)
{
	strcpy(TabMonster[0].Name,"Goblin");
	strcpy(TabMonster[1].Name,"Hobgoblin");
}

/**
 * function MonstersInit
 * 		initialize the Non Player Characters
 * 		@param	Character_t *TabMonster
 * 		@param	int taille
 * 		@return	void
 */
void MonstersInit(Character_t *TabMonster, int taille)
{
	int i=0;
	int rank = 0;
	MonstersInitNames(TabMonster);
	for(i=0;i<taille;i++)
	{
		rank=i;	//	modify when monster system exists
		MonsterInit(&TabMonster[i], rank);
	}
}

/**
 * function InitFighter
 * 		find a playable monster from the pool of monsters
 * 		@param	Character_t * monster
 * 		@param	Character_t *TabMonster
 * 		@param	int taille
 * 		@return	void
 */
void InitFighter(Character_t * monster, Character_t *TabMonster, int taille)
{
	int i;
	i = RandomValues(0,1); //Initialize i for monsters
	if (i<0)
		i=0;
	if(i>taille)
		i=taille-1;

	if(TabMonster[i].Health<=0)
		InitFighter(monster, TabMonster, taille);
	else
		MonsterCopy(monster, TabMonster[i]);
}

/**
 * function DisplayEnnemy
 * 		show ASCII for :
 * 		@param	Character_t M
 * 		@return	void
 */
void DisplayEnnemy(Character_t M)
{
	printf("\n");
	switch(M.Level)
	{
		//	hobgoblin
		case 1:
			printf("\t            ,      ,  \n");
			printf("\t           /(.-\"\"-.)\\\n");
			printf("\t        |\\ \\/      \\/ /|\n");
			printf("\t        | \\/ =.  .= \\/ |\n");
			printf("\t        \\( \\  o\\/o  / )/\n");
			printf("\t         \\_, '/  \\' ,_/\n");
			printf("\t          /   \\__/   \\\n");
			printf("\t          \\,___/\\___,/\n");
			printf("\t        ___\\ \\|uu|/ /___\n");
			printf("\t      /`    \\ .--. /    `\\\n");
			printf("\t     /       '----'       \\\n");
			break;
		//	goblin
		case 0:
		default:
			printf("\t             ,      ,\n");
			printf("\t            /(.-\"\"-.)\\\n");
			printf("\t        |\\  \\/      \\/  /|\n");
			printf("\t        | \\ / =.  .= \\ / |\n");
			printf("\t        \\( \\   o\\/o   / )/\n");
			printf("\t         \\_, '-/  \\-' ,_/\n");
			printf("\t           /   \\__/   \\\n");
			printf("\t           \\ \\__/\\__/ /\n");
			printf("\t         ___\\ \\|--|/ /___\n");
			printf("\t       /`    \\      /    `\\\n");
			printf("\t      /       '----'       \\\n");
			break;
	}
	
	printf("\t%s\n",M.Name);
}

/**
 * function DamageCharacter
 * 		define damages done by Attacker to * Defender
 * 		@param	Character_t Attacker
 * 		@param	Character_t * Defender
 * 		@return	void
 */
void DamageCharacter(Character_t Attacker, Character_t * Defender)
{
	/*	init variables	*/
	int ToHit=0, damage = 0;
	ToHit = RandomValues(1, 20) + Attacker.StrBonus;/* If rnd give >= 19 */ 
	//	ToHit need to be sup than ArmorClass to make damages
	if(ToHit >= Defender->ArmorClass)
	{
		damage = RandomValues(1, 6) + Attacker.StrBonus;	//Actually 1D6 but it can be change with some weapons
		
		if (ToHit >= 19)
		{
			if(Language[0] == 'F')
			{
				printf("\t%s lance le de, et fait... %d : un CRITIQUE !!!\n", Attacker.Name, ToHit);
				printf("\t%s frappe son ennemi de toutes ses forces !", Attacker.Name);
				printf(" Les os de %s se brisent sous les coups\n", Defender->Name);
				damage += 6;
				printf("\t%s fait %d degats !\n", Attacker.Name, damage);
			}
			else
			{ 
				printf("\t%s rolls the dice and it does... %d : a CRITICAL HIT !!!\n", Attacker.Name, ToHit);
				printf("\t%s crushes the enemy with all of the power ! \n", Attacker.Name);
				printf("Some of %s's bones are broken !\n", Defender->Name);
				damage += 6;
				printf("\t%s make %d damages !\n", Attacker.Name, damage);
			}
		}
		if (ToHit < 19)
		{
			if(Language[0] == 'F')
			{
				printf("\t%s lance le de, et fait... ! %d\n", Attacker.Name, ToHit);
				printf("\t%s fait %d degats !\n", Attacker.Name, damage);
			}
			else
			{
				printf("\t%s rolls the dice and it does...%d\n", Attacker.Name, ToHit);
				printf("\t%s slices %s, and his blood fell to the ground\n", Attacker.Name, Defender->Name);
				printf("\t%s makes %d damages !\n", Attacker.Name, damage);
			}
		}
		Defender->Health -= damage;
	}
	if (ToHit < Defender->ArmorClass)
	{
		if(Language[0] == 'F')
			printf("\t%s fait %d ... et rate son coup\n", Attacker.Name, ToHit);
		else
			printf("\t%s did %d ... and missed\n", Attacker.Name, ToHit);
	}
}	

/**
 * 	function Defense
 * 		upgrades ResBonus and StrBonus by 1 one time
 * 		@param	Character_t * Defender
 * 		@param	int StrBeforeFight
 * 		@param	int ACBeforeFight
 * 		@return	void
 */
void Defense(Character_t * Defender, int StrBeforeFight, int ACBeforeFight)
{	
	if (Defender->ArmorClass - ACBeforeFight < 3)
	{
		Defender->ArmorClass += 1;
		if(Language[0] == 'F')
			printf("\tVous avez maintenant %d CA\n", Defender->ArmorClass);
		else
			printf("\tYou now have %d AC\n", Defender->ArmorClass);
	}
	
	if (Defender->StrBonus - StrBeforeFight == 0)
		Defender->StrBonus += 1;
}

/**
 * function FightHeroturn
 * 		invite player to choose fight attitude
 * 		and reacts accordingly
 * 		@param	Character_t * Hero
 * 		@param	Character_t * Monster
 * 		@param	int StrBeforeFight
 * 		@param	int ACBeforeFight
 * 		@return	void
 */
void FightHeroTurn(Character_t * Hero, Character_t * Monster, int StrBeforeFight,int ACBeforeFight)
{ 
	
	do
	{
		/*	reset PlayerAction	*/
		strcpy(PlayerAction, "");
	
		/*	invite Player to take action	*/
		printf("\n");
		if (Language[0] == 'F')
		{
			printf("\tC'est votre tour d'attaquer contre %s, que voulez-vous faire ?\n", Monster->Name);
			printf("\t\t[A]ttaquer\n");
			printf("\t\t[D]efendre\n");
		}
		else
		{
			printf("\tIt is your turn to attack %s, what will you do ?\n", Monster->Name);
			printf("\t\t[A]ttack\n");
			printf("\t\t[D]efend\n");
		}
		DisplayChoose(PlayerAction);
		/*	reset screen	*/
		if (Language[0] == 'F')
		{
			DisplayTop("  COMBAT ");
			/*	give feedback of keyboard entry	*/
			printf("\tVous avez choisi : %c\n", PlayerAction[0]);
		}
		else
		{
			DisplayTop("  FIGHT  ");
			/*	give feedback of keyboard entry	*/
			printf("\tYou chose : %c\n", PlayerAction[0]);
		}
		/*	result of the chosen action	*/
		if(PlayerAction[0] != 'A' && PlayerAction[0] != 'D')
		{
			if (Language[0] == 'F')
				printf("\tMauvais choix \n");
			else
				printf("\tWrong choice \n");
		}
		if (PlayerAction[0] == 'A')
			DamageCharacter(*Hero, Monster);
		
		if (PlayerAction[0] == 'D')
			Defense(Hero, StrBeforeFight, ACBeforeFight);

		/*	Monster's turn	*/
			printf("\n");
		/*	display the remaining life	*/
		if (Language[0] == 'F')
			printf("\t\t%s a %d de vie restante\n", Monster->Name, Monster->Health);
		else
			printf("\t\t%s has %d health left\n", Monster->Name, Monster->Health);
		/*	next round	*/
		if (Monster->Health > 0)
			FightMonsterTurn(Monster,Hero, StrBeforeFight, ACBeforeFight);
	} while(Hero->Health > 0 && Monster->Health > 0);	//	as long as both are alive
	
	/*	after fight	*/
	/*	player wins	*/
	if(Hero->Health > 0)
	{
		/*	AC & StrBonus becomes again like before the fight	*/
		Hero->ArmorClass = ACBeforeFight;
		Hero->StrBonus = StrBeforeFight;
		Hero->Victories++;
		Hero->Exp += Monster->Exp;
		if (Language[0] == 'F')
			printf("\t\tVous avez gagne le combat !\n");
		else
			printf("\t\tYou won the fight !\n");
		if(Hero->Exp >= Hero->ExpNextLvl)
		{
			printf("\t\tVous avez gagne un niveau !\n");
			lvlUp(Hero);
		}
		DisplayEnter();
	}
	/*	player loses	*/
	else if (Hero->Health <= 0)
	{
		DisplayDeath();
	}
	ActionMenu();
}

/**
 * function FightMonsterturn
 * 		Monster's attack
 * 		@param	Character_t * Monster
 * 		@param	Character_t * Hero
 * 		@param	int StrBeforeFight
 * 		@param	int ACBeforeFight
 * 		@return	void
 */
void FightMonsterTurn(Character_t * Monster, Character_t * Hero, int StrHeroBeforeFight, int ACHeroBeforeFight)
{ 	

	printf("\n");
	if (Language[0] == 'F')
		printf("\t%s vous attaque\n", Monster->Name);
	else
		printf("\t%s attacks you\n", Monster->Name);
	DamageCharacter(*Monster, Hero);
	/*	display the remaining life	*/
	if (Language[0] == 'F')
		printf("\t\t%s a %d de vie restante\n", Hero->Name, Hero->Health);
	else
		printf("\t\t%s has %d health left\n", Hero->Name, Hero->Health);
	/*	next round	*/
	if (Hero->Health > 0)
		FightHeroTurn(Hero,Monster, StrHeroBeforeFight, ACHeroBeforeFight);
	else
		DisplayDeath();
}

/**
 * function DisplayDeath
 * 		shows last message before quitting the game
 * 		@return	void
 */
void DisplayDeath()
{
	printf("\n");
	if (Language[0] == 'F')
	{
		printf("\tVous avez perdu le combat !\n");
		printf("\tVous êtes mort ...\n");
	}
	else
	{
		printf("\tYou lost the fight !\n");
		printf("\tYou are dead ...\n");
	}
	DisplayEnter();
	/*	just quit the game for now	*/
	DisplayOutro();
}

/**
 * function DisplayCharacter
 * 		shows the character stats
 * 		@param	Character_t character
 * 		@return	void
 */
void DisplayCharacter(Character_t character)
{
    DisplayTop(" R.P.G.  ");
    
    if (Language[0] == 'F')
    {
		printf("\tCaractéristiques de %s\n",character.Name);
		printf("\t\tNiveau \t:\t\t%d\n",character.Level);
		printf("\t\tVie \t:\t\t%d\n",character.Health);
		printf("\t\tForce \t:\t\t%d\n",character.Strength);
		printf("\t\tDéfense\t:\t\t%d\n",character.Resistance);
		printf("\t\tClasse d'Armure\t:\t%d\n",character.ArmorClass);
		printf("\t\tExpérience :\t\t%d\n",character.Exp);
		printf("\t\tVictoire :\t\t%d\n",character.Victories);
		printf("\t\tProchain niveau :\t%d exp\n", character.ExpNextLvl - character.Exp);
	}
    else
    {
		printf("\tCharacteristics of %s\n",character.Name);
		printf("\t\tLevel \t:\t\t%d\n",character.Level);
		printf("\t\tLife \t:\t\t%d\n",character.Health);
		printf("\t\tForce \t:\t\t%d\n",character.Strength);
		printf("\t\tDefense\t:\t\t%d\n",character.Resistance);
		printf("\t\tArmor Class\t:\t%d\n",character.ArmorClass);
		printf("\t\tExperience :\t\t%d\n",character.Exp);
		printf("\t\tVictorie(s) :\t\t%d\n",character.Victories);
		printf("\t\tNext level :\t%d exp\n", character.ExpNextLvl - character.Exp);
	}
	
	DisplayEnter();
	ActionMenu();
}

/**
 * function ActionMenu
 * 		display main menu for player
 * 		@return	void
 */
void ActionMenu()
{
	int valRecupStr, valRecupDef;
	//DisplayTop(hero.Name);
    DisplayTop(" R.P.G.  ");
	/*	reset PlayerAction	*/
	strcpy(PlayerAction,"");
	Character_t tempMonster;
	
	/*	Loop until PlayerAction > 1 char	*/
	/*	invite Player to take action	*/
	do
	{
		printf("\n");
		if (Language[0] == 'F')
		{
			printf("\tVous pouvez : \n");
			printf("\t\t[V]oir votre personnage\n");
			printf("\t\t[F]aire le combat\n");
			printf("\t\t[Q]uitter\n");
		}
		else
		{
			printf("\tYou can : \n");
			printf("\t\t[V]erify your character\n");
			printf("\t\t[F]ight a monster\n");
			printf("\t\t[Q]uit\n");
		}
		DisplayChoose(PlayerAction);
		/*	result of the chosen action	*/
		if(strlen(PlayerAction) > 1)
			printf("Veuillez ne saisir qu'une lettre\n");
	}while(strlen(PlayerAction) > 1);
	
	switch(PlayerAction[0])
	{
		case 'V':
			DisplayCharacter(hero);
			break;
		case 'F':
			if (Language[0] == 'F')
			{
				DisplayTop("  COMBAT ");
				printf("\tVous avez rencontré un monstre !\n");
			}
			else
			{
				DisplayTop("  FIGHT  ");
				printf("\tYou have encountered a monster !\n");
			}
			/**	Need to have Strbonus & ArmorClass
			 * 	for use them for
			 * 	Defense function
			 **/
			valRecupStr = hero.StrBonus;
			valRecupDef = hero.ArmorClass;
			InitFighter(&tempMonster, monstersList, 2);
			/*	splash screen	*/
			DisplayEnnemy(tempMonster);
			FightHeroTurn(&hero, &tempMonster, valRecupStr, valRecupDef );
			break;
		case 'Q':
			DisplayOutro();
			break;
		default:
			ActionMenu();
			break;
	}
}

/**
 * function DisplayChoose
 * 		invite user to choose from previously displayed menu
 * 		@param	*text
 * 		@return	void
 */
void DisplayChoose(char *text)
{
	printf("\n");
	DisplayLine();
	printf("\n");
	if (Language[0] == 'F')
		printf("\tVotre choix : ");
	else
		printf("\tYour choice : ");
	scanf("%s", text);
	getchar();
	text[0] = toupper(text[0]);
}

/**
 * function ChooseLanguage
 * 		select the language (FR/EN)
 * 		@return	void
 */
void ChooseLanguage()
{
	/*	Loop until Language > 1 char and Language != F or E	*/
	do
	{
		printf("\n");
		printf("\tSelect your language :\n");
		printf("\t\t[F]rancais\n");
		printf("\t\t[E]nglish\n");
		DisplayChoose(Language);
		/*	result of the chosen action	*/
		if(strlen(Language) > 1)
		{
			printf("Veuillez ne saisir qu'une lettre\n");
			printf("Please choose only one letter\n");
		}
		if(Language[0] != 'F' && Language[0] != 'E')
		{
			printf("Veuillez saisir soit F soit E\n");
			printf("Please choose either F or E\n");
		}
		
	}while(strlen(Language) > 1 || Language[0] != 'F' && Language[0] != 'E');
}

/**
 * function DisplayLine
 * 		showsan horizontal line
 * 		@return	void
 */
void DisplayLine()
{
	int i;
    printf("\t");
    for(i=0; i<170;i++)
        printf("_");
    printf("\n\n");
}

/**
 * function DisplayEnter
 * 		invit player to push <enter>
 * 		@return	void
 */
void DisplayEnter()
{
	DisplayLine();
	if (Language[0] == 'F')
		printf("\n\tVeuillez appuyer sur [ENTREE] pour continuer");
	else
		printf("\n\tPlease press [ENTER] to continue");
	getchar();
}

/**
 * function DisplayTop
 * 		for the top part of the screen
 * 		@param	*text
 * 		@return	void
 */
void DisplayTop(char *text)
{
	cls();
	printf("\n");
    printf("\t\t\t\t\t\t\t\t *************************************** \n");
    printf("\t\t\t\t\t\t\t\t|\t\t\t\t\t|\n");
    printf("\t\t\t\t\t\t\t\t|\t\t%s\t\t|\n",text);
    printf("\t\t\t\t\t\t\t\t|\t\t\t\t\t|\n");
    printf("\t\t\t\t\t\t\t\t *************************************** \n");
    //	line
    DisplayLine();
}

/**
 * function DisplayTitle
 * 		show the game title
 * 		@return	void
 */
void DisplayTitle()
{
    //	game title
    DisplayTop(" R.P.G.  ");
}

/**
 * function DisplayIntro
 * 		start screen
 * 		invite player to create character
 * 		@return	void
 */
void DisplayIntro()
{
	/*	invite screen	*/
	if (Language[0] == 'F')
		DisplayTop("Bienvenue");
	else
		DisplayTop(" Welcome ");
		
	/*	Loop until PlayerAction > 1 char and PlayerAction[0] != C or Q	*/
	do
	{	
		/*	reset PlayerAction	*/
		PlayerAction[0] = '\0';
		/*	invite Player to take action	*/
		if (Language[0] == 'F')
			printf("\n\t[C]réer un personnage\n\t[Q]uitter\n");
		else
			printf("\n\t[C]reate your character\n\t[Q]uit\n");
		DisplayChoose(PlayerAction);
		/*	result of the chosen action	*/
		if(strlen(PlayerAction) > 1)
			printf("Veuillez ne saisir qu'une lettre\n");		
		if(PlayerAction[0] != 'C' && PlayerAction[0] != 'Q')
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

/**
 * function DisplayOutro
 * 		shows last message and leave the game
 * 		@return	void
 */
void DisplayOutro()
{
	if (Language[0] == 'F')
		DisplayTop("Au revoir");
	else
		DisplayTop(" See you ");
	exit(1);
}

/**
 * function DisplayWarning
 * 		first display
 * 		in all languages (FR/EN)
 * 		prompt language choice
 * 		and general layout
 * 		@return	void
 */
void DisplayWarning()
{
	cls();
    printf("\n\n");
    printf(" ########## ");
    printf("Veuillez passer en plein PLEIN ECRAN avant de continuer");
    printf(" ########## ");
    printf("\n\n");
    printf(" ########## ");
    printf("Please switch to full screen");
    printf(" ########## ");
    printf("\n\n\n\n\n\n\n\n");
    printf("\t\t Tapez ENTREE pour continuer.");
    printf("\n\n");
	printf("\t\t Press ENTER to continue.");
	getchar();
	DisplayTitle();
	ChooseLanguage();
	DisplayIntro();
}
