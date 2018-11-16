
#ifndef _CONSOLE_MENU_H
#define _CONSOLE_MENU_H

class ConsoleMenu {
	public:
		ConsoleMenu(int item_num,  const char * const * menuItems);
		int getMove();
		void print() const;
		
	private:
		int nitems;
		int inputTransform(char move);
		char **items;
}; 

#endif
