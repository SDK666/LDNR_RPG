#include "interface.h"

/*								LAYOUT								*/
/***********************************************************************
 * 
 * void cls (void)
 * 
 * refresh the dispay
 * 		@param	void
 * 
 **********************************************************************/
void Interface::cls (void)
{
	Layout::cls();
}

/***********************************************************************
 * 
 * void DisplayEnter()
 * 
 * dispay the invite to press enter
 * 
 **********************************************************************/
void Interface::DisplayEnter()
{
	Layout::error(AT, "fake error");
	Layout::DisplayEnter();
}

/***********************************************************************
 * 
 * void DisplayLine()
 * 
 * dispay an horizontal line
 * 
 **********************************************************************/
void Interface::DisplayLine()
{
	Layout::DisplayLine();
}
/***********************************************************************
 * 
 * void DisplayTop()
 * 
 * dispay the top part
 * 		@param	string text		the text to appear on top
 * 
 **********************************************************************/
void Interface::DisplayTop(string text)
{
	Layout::DisplayTop(text);
}

/***********************************************************************
 * 
 * void DisplayTitle()
 * 
 * dispay the top part with title
 * 
 **********************************************************************/
void Interface::DisplayTitle()
{
	Layout::DisplayTitle();
}

/***********************************************************************
 * 
 * int DisplayChoose()
 * 
 * invite user to choose
 * 
 **********************************************************************/
int Interface::DisplayChoose(int &choice)
{
	return Layout::DisplayChoose(choice);
}

/*							CONSTRUCTORS								*/
Interface::Interface ()
{
	this->language = 0;
	this->PlayerAction = -1;
	this->monsters = vector<Character>();
}
// copy constructor
Interface::Interface ( const Interface &I)
{
	this->language = I.language;
	this->PlayerAction = I.PlayerAction;
	this->monsters = I.monsters;
}
// operator=
Interface & Interface::operator=(const Interface &I)
{
	this->language = I.language;
	this->PlayerAction = I.PlayerAction;
	this->monsters = I.monsters;
}

/*							STARTERS								*/
/***********************************************************************
 * 
 * void Start()
 * 
 * initiate the program
 * 
 **********************************************************************/
void Interface::Start()
{
	DisplayWarning();
	MonstersInit(2);
	/*	TO DELETE FOR FINAL USE !!!	*/
	MonstersList(2);
	
	MainMenu();
}

/**
 * function DisplayWarning
 * 		first display
 * 		in all languages (FR/EN)
 * 		prompt language choice
 * 		and general layout
 * 		@return	void
 */
void Interface::DisplayWarning()
{
	cls();
	cout << endl << endl;
	cout << " ########## ";
	cout << "Veuillez passer en plein PLEIN ECRAN avant de continuer";
	cout << " ########## ";
	cout << endl << endl;
	cout << " ########## ";
	cout << "Please switch to full screen";
	cout << " ########## ";
	
	cout << endl << endl << endl << endl << endl << endl << endl << endl;
    cout << "\t\t Tapez ENTREE pour continuer.";
	cout << endl << endl;
    cout << "\t\t Press ENTER to continue.";
	cin.get();

	DisplayTitle();
	ChooseLanguage();
	StartMenu();
}

/**
 * function ChooseLanguage
 * 		select the language (FR/EN)
 * 		@return	void
 */
void Interface::ChooseLanguage()
{
	int max = 2;
	/*	Loop until Language > 1 char and Language != F or E	*/
	do
	{
		cout << endl;
		cout << "\tSelect your language :" << endl;
		cout << "\t\t[1] Francais" << endl;
		cout << "\t\t[2] English" << endl;
		
		DisplayChoose(language);
		
		/*	result of the chosen action	*/
		if( language > max)
		{
			cout << "Veuillez ne saisir qu'un chiffre" << endl;
			cout << "Please choose only one digit" << endl;
		}
		if( language != 1 && language != 2)
		{
			printf("Veuillez saisir soit 1 soit 2\n");
			printf("Please choose either 1 or 2\n");
		}
		
	} while( language == 0 && language > max);
}

/**
 * function StartMenu
 * 		start screen
 * 		invite player to create character
 * 		@return	void
 */
void Interface::StartMenu()
{
	int max = 1;
	/*	invite screen	*/
	if (language == 1)
		DisplayTop("Bienvenue");
	else
		DisplayTop(" Welcome ");
		
	/*	Loop until PlayerAction > 1 char and PlayerAction[0] != C or Q	*/
	do
	{	
		/*	reset PlayerAction	*/
		PlayerAction = -1;
		/*	invite Player to take action	*/
		if (language == 1)
		{
			cout << endl;
			cout << "\t[1] Créer un personnage";
			cout << endl;
			cout << "\t[0] Quitter" << endl;
		}
		else
		{
			cout << endl;
			cout << "\t[1] Create your character";
			cout << endl;
			cout << "\t[0] Quit" << endl;
		}
		DisplayChoose(PlayerAction);
		/*	result of the chosen action	*/
		if( PlayerAction > max)
			cout << "Veuillez ne saisir qu'un chiffre." << endl;
		if( PlayerAction != 1 && PlayerAction != 0)
			cout << "Veuillez saisir soit 1 soit 0" << endl;
			
	} while( PlayerAction > max || PlayerAction == -1 ); 
	
	switch(PlayerAction)
	{
		case 1:
			InitPlayer();
			break;
		case 0:
			Quit();
			break;
		default:
			StartMenu();
			break;
	}
}

/**
 * function Quit
 * 		shows last message and leave the game
 * 		@return	void
 */
void Interface::Quit()
{
	if ( language == 1)
		DisplayTop("Au revoir");
	else
		DisplayTop(" See you ");
	exit(1);
}

/**
 * function InitPlayer
 * 		invite the player to create character
 * 		@return	void
 */
void Interface::InitPlayer()
{
	cls();
	if ( language == 1 )
		DisplayTop("  CREER  ");
	else
		DisplayTop(" CREATE  ");
	int i;
	/*	sets character name	*/
	cout << "\t";
	if( language == 1 )
		cout << "Quel est votre nom ?";
	else
		cout << "What's your name ?";
	cout << "\t";
	cin >> hero.Name;

	hero.InitCharacter();
}

/**
 * function MonstersInit
 * 		initialize the Non Player Characters
 * 		@param	int taille
 * 		@return	void
 */
void Interface::MonstersInit(int taille)
{
	int i=0;
	int rank = 0;
	MonstersInitNames();
	for(i=0;i<taille;i++)
	{
		rank=i;	//	modify when monster system exists
		monsters[i].MonsterInit(rank);
	}
}

/**
 * function MonstersInitNames
 * 		define the names for opponents
 * 		@return	void
 */
void Interface::MonstersInitNames()
{
	Character gob = Character("Goblin");
	Character hob = Character("Hobgoblin");
	monsters.push_back(gob);
	monsters.push_back(hob);
}

/**
 * function MonstersList
 * 		runs through the array of monsters
 * 		to display each one's stats
 * 		only works in debug mode
 * 		@param	int taille
 * 		@return	void
 */
void Interface::MonstersList(int taille)
{
	int i=0;
	for(i=0;i<taille;i++)
	{
		monsters[i].MonsterDisplay();
		cout << endl;
	}
}

/*								MENUS								*/
/***********************************************************************
 * 
 * void MainMenu()
 * 
 * display the main menu
 * 
 **********************************************************************/
void Interface::MainMenu()
{
	int valRecupStr, valRecupDef;
	int max = 2;
	//DisplayTop(hero.Name);
    DisplayTitle();
	/*	reset PlayerAction	*/
	PlayerAction = 0;
	Character tempMonster;
	
	/*	Loop until PlayerAction > 1 char	*/
	/*	invite Player to take action	*/
	do
	{
		cout << endl;
		if ( language == 1)
		{
			cout << "\tVous pouvez :" << endl;
			cout << "\t\t[1] Voir votre personnage" << endl;
			cout << "\t\t[2] Faire le combat" << endl;
			cout << endl;
			cout << "\t\t[0] Quitter" << endl;
		}
		else
		{
			cout << "\tYou can :" << endl;
			cout << "\t\t[1] See your character" << endl;
			cout << "\t\t[2] Go fighting" << endl;
			cout << endl;
			cout << "\t\t[0] Quit" << endl;
		}
		
		DisplayChoose(PlayerAction);
		/*	result of the chosen action	*/
		if( PlayerAction > max)
			printf("Veuillez ne saisir qu'un chiffre\n");
	}while(PlayerAction > max);
	
	switch(PlayerAction)
	{
		case 1:
			DisplayTitle();
			hero.DisplayCharacter(language);
			MainMenu();
			break;
		case 2:
			if ( language == 1)
			{
				DisplayTop("  COMBAT ");
				cout << "\tVous avez rencontré un monstre !" << endl;
			}
			else
			{
				DisplayTop("  FIGHT  ");
				cout << "\tYou have encountered a monster !" << endl;
			}
			/**	Need to have Strbonus & ArmorClass
			 * 	for use them for
			 * 	Defense function
			 **/
			valRecupStr = hero.StrBonus;
			valRecupDef = hero.ArmorClass;
			InitFighter(&tempMonster, 2);
			/*	splash screen	*/
			DisplayEnnemy(tempMonster);
			FightHeroTurn(&tempMonster, valRecupStr, valRecupDef );
			break;
		case 0:
			Quit();
			break;
		default:
			MainMenu();
			break;
	}
}

/**
 * function InitFighter
 * 		find a playable monster from the pool of monsters
 * 		@param	Character_t * monster
 * 		@param	int taille
 * 		@return	void
 */
void Interface::InitFighter(Character * monster, int taille)
{
	int i;
	i = monster->RandomValues(0,1); //Initialize i for monsters
	if (i<0)
		i=0;
	if(i>taille)
		i=taille-1;

	if(monsters[i].Health<=0)
		InitFighter(monster, taille);
	else
		MonsterCopy(monster, monsters[i]);
}

/**
 * function MonsterCopy
 * 		create a copy of a monster
 * 		to use in a fight
 * 		@param	Character_t *MT (monster target)
 * 		@param	Character_t MS (monster source)
 * 		@return	void
 */
void Interface::MonsterCopy(Character *MT, Character MS)
{
	MT->Name = MS.Name;
	MT->Level = MS.Level;
	MT->Health = MS.Health;
	MT->Strength = MS.Strength;
	MT->StrBonus = MS.StrBonus;
	MT->Resistance = MS.Resistance;
	MT->ArmorClass = MS.ArmorClass;
	MT->Exp = MS.Exp;
}

/**
 * function DisplayEnnemy
 * 		show ASCII for :
 * 		@param	Character_t M
 * 		@return	void
 */
void Interface::DisplayEnnemy(Character M)
{
	cout << endl;
	switch(M.Level)
	{
		//	hobgoblin
		case 1:
			cout << "\t            ,      ,  " << endl;
			cout << "\t           /(.-\"\"-.)\\" << endl;
			cout << "\t        |\\ \\/      \\/ /|" << endl;
			cout << "\t        | \\/ =.  .= \\/ |" << endl;
			cout << "\t        \\( \\  o\\/o  / )/" << endl;
			cout << "\t         \\_, '/  \\' ,_/" << endl;
			cout << "\t          /   \\__/   \\" << endl;
			cout << "\t          \\,___/\\___,/" << endl;
			cout << "\t        ___\\ \\|uu|/ /___" << endl;
			cout << "\t      /`    \\ .--. /    `\\" << endl;
			cout << "\t     /       '----'       \\" << endl;
			break;
		//	goblin
		case 0:
		default:
			cout << "\t             ,      ," << endl;
			cout << "\t            /(.-\"\"-.)\\" << endl;
			cout << "\t        |\\  \\/      \\/  /|" << endl;
			cout << "\t        | \\ / =.  .= \\ / |" << endl;
			cout << "\t        \\( \\   o\\/o   / )/" << endl;
			cout << "\t         \\_, '-/  \\-' ,_/" << endl;
			cout << "\t           /   \\__/   \\" << endl;
			cout << "\t           \\ \\__/\\__/ /" << endl;
			cout << "\t         ___\\ \\|--|/ /___" << endl;
			cout << "\t       /`    \\      /    `\\" << endl;
			cout << "\t      /       '----'       \\" << endl;
			break;
	}
	
	cout << "\t" << M.Name << endl;
}

/**
 * function FightHeroturn
 * 		invite player to choose fight attitude
 * 		and reacts accordingly
 * 		@param	int StrBeforeFight
 * 		@param	int ACBeforeFight
 * 		@return	void
 */
void Interface::FightHeroTurn(Character * M, int StrBeforeFight,int ACBeforeFight)
{ 
	
	do
	{
		/*	reset PlayerAction	*/
		PlayerAction = 0;
	
		/*	invite Player to take action	*/
		cout << endl;
		if ( language == 1)
		{
			cout << "\tC'est votre tour d'attaquer contre " << M->Name << ", que voulez-vous faire ?" << endl;
			cout << "\t\t[1] Attaquer" << endl;
			cout << "\t\t[2] Defendre" << endl;
		}
		else
		{
			cout << "\tIt is your turn to attack " << M->Name << ", what will you do ?" << endl;
			cout << "\t\t[1] Attack" << endl;
			cout << "\t\t[2] Defend" << endl;
		}
		
		DisplayChoose(PlayerAction);
		/*	reset screen	*/
		if ( language == 1)
		{
			DisplayTop("  COMBAT ");
			/*	give feedback of keyboard entry	*/
			cout << "\tVous avez choisi : " << PlayerAction << endl;
		}
		else
		{
			DisplayTop("  FIGHT  ");
			/*	give feedback of keyboard entry	*/
			cout << "\tYou chose : " << PlayerAction << endl;
		}
		/*	result of the chosen action	*/
		if( PlayerAction != 1 && PlayerAction != 2)
		{
			if ( language == 1)
				cout << "\tMauvais choix" << endl;
			else
				cout << "\tWrong choice" << endl;
		}
		if (PlayerAction == 1)
			DamageCharacter(hero, M);
		
		if (PlayerAction == 2)
			Defense(&hero, StrBeforeFight, ACBeforeFight);

		/*	Monster's turn	*/
			cout << endl;
		/*	display the remaining life	*/
		if (PlayerAction == 1)
			cout << "\t\t" << M->Name << " a " << M->Health << " de vie restante" << endl;
		else
			cout << "\t\t" << M->Name << " has " << M->Health << " health left" << endl;
		/*	next round	*/
		if (M->Health > 0)
			FightMonsterTurn(M, StrBeforeFight, ACBeforeFight);
	} while( hero.Health > 0 && M->Health > 0 );	//	as long as both are alive
	
	/*	after fight	*/
	/*	player wins	*/
	if(hero.Health > 0)
	{
		/*	AC & StrBonus becomes again like before the fight	*/
		hero.ArmorClass = ACBeforeFight;
		hero.StrBonus = StrBeforeFight;
		hero.Victories++;
		hero.Exp += M->Exp;
		if ( language == 1)
			cout << "\t\tVous avez gagne le combat !" << endl;
		else
			cout << "\t\tYou won the fight !" << endl;
		if(hero.Exp >= hero.ExpNextLvl)
		{
			cout << "\t\tVous avez gagne un niveau !" << endl;
			hero.lvlUp(language);
		}
		DisplayEnter();
	}
	/*	player loses	*/
	else if (hero.Health <= 0)
	{
		DisplayDeath();
	}
	MainMenu();
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
void Interface::FightMonsterTurn(Character * M, int StrHeroBeforeFight, int ACHeroBeforeFight)
{ 	
	cout << endl;
	if ( language == 1)
		cout << "\t" << M->Name << " vous attaque" << endl;
	else
		cout << "\t" << M->Name << " attacks you" << endl;
	DamageCharacter(*M, &hero);
	/*	display the remaining life	*/
	if ( language == 1)
		cout << "\t\t" << hero.Name << " a " << hero.Health << " de vie restante" << endl;
	else
		cout << "\t\t" << hero.Name << " has " << hero.Health << " health left" << endl;
	/*	next round	*/
	if (hero.Health > 0)
		FightHeroTurn(M, StrHeroBeforeFight, ACHeroBeforeFight);
	else
		DisplayDeath();
}

/**
 * function DisplayDeath
 * 		shows last message before quitting the game
 * 		@return	void
 */
void Interface::DisplayDeath()
{
	cout << endl;
	if ( language == 1)
	{
		cout << "\tVous avez perdu le combat !" << endl;
		cout << "\tVous êtes mort ..." << endl;
	}
	else
	{
		cout << "\tYou lost the fight !" << endl;
		cout << "\tYou are dead ..." << endl;
	}
	DisplayEnter();
	/*	just quit the game for now	*/
	Quit();
}

/**
 * function DamageCharacter
 * 		define damages done by Attacker to * Defender
 * 		@param	Character_t Attacker
 * 		@param	Character_t * Defender
 * 		@return	void
 */
void Interface::DamageCharacter(Character Attacker, Character * Defender)
{
	/*	init variables	*/
	int ToHit=0, damage = 0;
	ToHit = hero.RandomValues(1, 20) + Attacker.StrBonus;/* If rnd give >= 19 */ 
	//	ToHit need to be sup than ArmorClass to make damages
	if(ToHit >= Defender->ArmorClass)
	{
		damage = hero.RandomValues(1, 6) + Attacker.StrBonus;	//Actually 1D6 but it can be change with some weapons
		
		if (ToHit >= 19)
		{
			damage += 6;
			if( language == 1 )
			{
				cout << "\t" << Attacker.Name << " lance le de, et fait... " << ToHit << " : un CRITIQUE !!!" << endl;
				cout << "\t" << Attacker.Name << " frappe son ennemi de toutes ses forces !";
				cout << " Les os de " << Defender->Name << " se brisent sous les coups" << endl;
				cout << "\t" << Attacker.Name << " fait " << damage << " degats !" << endl;
			}
			else
			{ 
				cout << "\t" << Attacker.Name << " rolls the dice and it does... " << ToHit << " : a CRITICAL HIT !!!" << endl;
				cout << "\t" << Attacker.Name << " crushes the enemy with all of the power !";
				cout << " Some of " << Defender->Name << "'s bones are broken !" << endl;
				cout << "\t" << Attacker.Name << " makes " << damage << " damages !" << endl;
			}
		}
		if (ToHit < 19)
		{
			if( language == 1 )
			{
				cout << "\t" << Attacker.Name << " lance le de, et fait... " << ToHit << endl;
				cout << "\t" << Attacker.Name << " fait " << damage << " degats !" << endl;
			}
			else
			{
				cout << "\t" << Attacker.Name << " rolls the dice and it does... " << ToHit << endl;
				cout << "\t" << Attacker.Name << " slices " << Defender->Name << ", and his blood fell to the ground" << endl;
				cout << "\t" << Attacker.Name << " makes " << damage << " damages !" << endl;
			}
		}
		Defender->Health -= damage;
	}
	if (ToHit < Defender->ArmorClass)
	{
		if( language == 1 )
			cout << "\t" << Attacker.Name << " fait " << ToHit << " ... et rate son coup" << endl;
		else
			cout << "\t" << Attacker.Name << " did " << ToHit << " ... and missed" << endl;
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
void Interface::Defense(Character * Defender, int StrBeforeFight, int ACBeforeFight)
{	
	if (Defender->ArmorClass - ACBeforeFight < 3)
	{
		Defender->ArmorClass += 1;
		if ( language == 1)
			cout << "\tVous avez maintenant " << Defender->ArmorClass << " CA" << endl;
		else
			cout << "\tYou now have " << Defender->ArmorClass << " AC" << endl;
	}
	
	if (Defender->StrBonus - StrBeforeFight == 0)
		Defender->StrBonus += 1;
}
