#include "layout.h"

//	debug solution
void Layout::error(const char *location, const char *msg)
{
	if (DEBUG)
		cout << "Error at " << location << ": "<< msg << endl;
}

#if defined WIN32
#define CLEAN_SCREEN "CLS"
#elif defined __linux
#define CLEAN_SCREEN "clear"
#endif

/***********************************************************************
 * 
 * void cls (void)
 * 
 * refresh the dispay
 * 		@param	void
 * 
 **********************************************************************/
void Layout::cls (void)
{
	system(CLEAN_SCREEN);
}

/***********************************************************************
 * 
 * void DisplayEnter()
 * 
 * dispay the invite to press enter
 * 
 **********************************************************************/
void Layout::DisplayEnter()
{
//	error(AT, "fake error");
	DisplayLine();
	cout << endl << "\tTaper <ENTREE> pour continuer...";
	cin.get();
	cls();
}

/***********************************************************************
 * 
 * void DisplayLine()
 * 
 * dispay an horizontal line
 * 
 **********************************************************************/
void Layout::DisplayLine()
{
	int i;
    cout << "\t";
    for(i=0; i<170;i++)
        cout << "_";
    cout << endl << endl;
}

/***********************************************************************
 * 
 * void DisplayTop()
 * 
 * dispay the top part
 * 		@param	string text		the text to appear on top
 * 
 **********************************************************************/
void Layout::DisplayTop(string text)
{
	cls();
	cout << endl;
    cout << "\t\t\t\t\t\t\t\t *************************************** " << endl;
    cout << "\t\t\t\t\t\t\t\t|\t\t\t\t\t|" << endl;
    cout << "\t\t\t\t\t\t\t\t|\t\t" << text << "\t\t|" << endl;
    cout << "\t\t\t\t\t\t\t\t|\t\t\t\t\t|" << endl;
    cout << "\t\t\t\t\t\t\t\t *************************************** " << endl;
    //	line
    DisplayLine();
}

/***********************************************************************
 * 
 * void DisplayTitle()
 * 
 * dispay the top part with title
 * 
 **********************************************************************/
void Layout::DisplayTitle()
{
	cls();
    //	software's title
    DisplayTop("   RPG   ");
}

/***********************************************************************
 * 
 * int DisplayChoose()
 * 
 * invite user to choose
 * 
 **********************************************************************/
int Layout::DisplayChoose(int &choice)
{
	string getChoice = "";
    DisplayLine();
	cout << "\tVotre choix :\t";
	try
	{
		while(getline(cin,getChoice) && getChoice.size() != 1)
		{
			cout << "\t\t\tSaisie incorrecte !!!" << endl;
		}
		choice = (int)getChoice[0] - 48;
	}
	catch (exception const& e)
	{
		cerr << "ERREUR : " << e.what() << endl;
	}
	return choice;
}
