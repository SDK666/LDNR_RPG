#ifndef INTERFACE_H
#define INTERFACE_H

#include "layout.h"
#include "character.h"

using namespace std;

class Interface:public Layout
{
	private:
		int language;
		int PlayerAction;
		
		Character hero;
		vector<Character> monsters;
		/*								LAYOUT								*/
		/***********************************************************************
		 * 
		 * void cls (void)
		 * 
		 * refresh the dispay
		 * 		@param	void
		 * 
		 **********************************************************************/
		void cls (void);
		/***********************************************************************
		 * 
		 * void DisplayEnter()
		 * 
		 * dispay the invite to press enter
		 * 
		 **********************************************************************/
		void DisplayEnter();
		/***********************************************************************
		 * 
		 * void DisplayLine()
		 * 
		 * dispay an horizontal line
		 * 
		 **********************************************************************/
		void DisplayLine();
		/***********************************************************************
		 * 
		 * void DisplayTop()
		 * 
		 * dispay the top part
		 * 		@param	string text		the text to appear on top
		 * 
		 **********************************************************************/
		void DisplayTop(string text);
		/***********************************************************************
		 * 
		 * void DisplayTitle()
		 * 
		 * dispay the top part with title
		 * 
		 **********************************************************************/
		void DisplayTitle();
		/***********************************************************************
		 * 
		 * int DisplayChoose()
		 * 
		 * invite user to choose
		 * 		@param	int choice	
		 * 		@return	int choice	
		 * 
		 **********************************************************************/
		int DisplayChoose(int &choice);

		/**
		 * function Quit
		 * 	end screen
		 */
		void Quit();
	
	protected:
		/*							STARTERS								*/
		/**
		 * function DisplayWarning
		 * 	first message
		 */
		void DisplayWarning();
		/**
		 * function ChooseLanguage
		 * 	select the language
		 */
		void ChooseLanguage();
		/**
		 * function StartMenu
		 * 	start screen
		 */
		void StartMenu();
		/**
		 * function InitPlayer
		 * 	create the Player Character
		 */
		void InitPlayer();
		/**
		 * function MonstersInit
		 * 	create the Non Player Characters
		 */
		void MonstersInit(int taille);
		/**
		 * function MonstersInitNames
		 * 	define the names for opponents
		 */
		void MonstersInitNames();
		/**
		 * function MonstersList
		 * 	display the existing monsters
		 */
		void MonstersList(int taille);

		/*								MENUS								*/
		/***********************************************************************
		 * 
		 * void MainMenu()
		 * 
		 * display the main menu
		 * 
		 **********************************************************************/
		void MainMenu();
		/**
		 * Function InitFighter
		 * 	find a playable monster from *monsters
		 */
		void InitFighter(Character * monster, int taille);
		/**
		 * function MonsterCopy
		 * 	used to define fighter
		 * 	*MT (monster target) takes
		 * 		MS (monster source) attributes
		 */
		void MonsterCopy(Character *MT, Character MS);
		/**
		 * function DisplayEnnemy
		 * 		show ASCII for :
		 * 		@param	Character_t M
		 * 		@return	void
		 */
		void DisplayEnnemy(Character M);
		/**
		 * function FightHeroturn
		 * 	Hero's turn
		 */
		void FightHeroTurn(Character * Monster, int StrBeforeFight,int ACBeforeFight);
		/**
		 * function FightMonsterturn
		 * 	Monster's turn
		 */
		void FightMonsterTurn(Character * Monster, int StrHeroBeforeFight, int ACHeroBeforeFight);
		/**
		 * function DisplayDeath
		 * 	shows last message
		 */
		void DisplayDeath();
		/**
		 * function DamageCharacter
		 * 	define damages done by Attacker to *Defender
		 */
		void DamageCharacter(Character Attacker, Character * Defender);
		/**
		 * 	function Defense
		 * 	upgrade ResBonus by 1 and 
		 * 	StrBonus by 1 one time
		 **/
		void Defense(Character * Defender, int StrBeforeFight, int ACBeforeFight);
	
	public:
		// constructeur defaut + param
		Interface ();
		// copy constructor
		Interface ( const Interface &I);
		// operator=
		Interface & operator=(const Interface &I);
				
		// destructeur
		virtual ~Interface() {};

		/***********************************************************************
		 * 
		 * void Start()
		 * 
		 * initiate the program
		 * 
		 **********************************************************************/
		void Start();

};

#endif
