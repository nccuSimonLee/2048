#include "ConsoleMenu.h"
#include <cstring>
#include <conio.h>
#include <iostream>
using namespace std;

ConsoleMenu::ConsoleMenu(int item_num,  const char * const * menu_items) {
	nitems = item_num;
	items = new char *[nitems];
	for(int i = 0; i < nitems; i++) {
        items[i] = strdup(menu_items[i]);
    }
}

int ConsoleMenu::getMove() {
	char move;
	int move_int;
	do {
		move = getch();
		move_int = inputTransform(move);
	} while(move_int == 0);
	return move_int;
	
}

int ConsoleMenu::inputTransform(char move) {
	switch(move) {
		case 'j': case 'J': {
			return 1;
			break;
		}
		case 'i': case 'I': {
			return 2;
			break;
		}
		case 'l': case 'L': {
			return 3;
			break;
		}
		case 'k': case 'K': {
			return 4;
			break;
		}
		default:
			return 0;
	}
}

void ConsoleMenu::print() const {
	cout << "Choose a move: ";
	for(int i = 0; i < nitems - 1; i++) {
		cout << items[i] << ", ";
	}
	cout << items[nitems-1] << endl;
	return;
}
