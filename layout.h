#ifndef LAYOUT_H
#define LAYOUT_H

#include "lib.h"

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define AT __FILE__ ":" TOSTRING(__LINE__)

using namespace std;

class Layout
{
	private:
	
	protected:
		virtual void error(const char *location, const char *msg);
		/***********************************************************************
		 * 
		 * void cls (void)
		 * 
		 * refresh the dispay
		 * 		@param	void
		 * 
		 **********************************************************************/
		virtual void cls (void)=0;
		/***********************************************************************
		 * 
		 * void DisplayEnter()
		 * 
		 * dispay the invite to press enter
		 * 
		 **********************************************************************/
		virtual void DisplayEnter()=0;
		/***********************************************************************
		 * 
		 * void DisplayLine()
		 * 
		 * dispay an horizontal line
		 * 
		 **********************************************************************/
		virtual void DisplayLine()=0;
		/***********************************************************************
		 * 
		 * void DisplayTop()
		 * 
		 * dispay the top part
		 * 		@param	string text		the text to appear on top
		 * 
		 **********************************************************************/
		virtual void DisplayTop(string text)=0;
		/***********************************************************************
		 * 
		 * void DisplayTitle()
		 * 
		 * dispay the top part with title
		 * 
		 **********************************************************************/
		virtual void DisplayTitle()=0;
		/***********************************************************************
		 * 
		 * int DisplayChoose()
		 * 
		 * invite user to choose
		 * 		@param	int choice	
		 * 		@return	int choice	
		 * 
		 **********************************************************************/
		virtual int DisplayChoose(int &choice)=0;
	
	public:
		// constructeur defaut + param
		Layout () {};
		// copy constructor
		Layout ( const Layout &L) {};
		// operator=
		Layout & operator=(const Layout &L) {};
				
		// destructeur
		virtual ~Layout() {};
};

#endif
