
#ifndef _CONSOLE_MENU_H
#define _CONSOLE_MENU_H

class ConsoleMenu {
	public:
		ConsoleMenu(int item_num,  const char * const * menuItems);
		char getMove();
		void print() const;
		
	private:
		int nitems;
		char **items;
}; 

#endif
