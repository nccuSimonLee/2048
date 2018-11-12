#include "ConsoleMenu.h"
#include <cstring>
#include <iostream>
using namespace std;

ConsoleMenu::ConsoleMenu(int item_num,  const char * const * menu_items) {
	nitems = item_num;
	items = new char *[nitems];
	for(int i = 0; i < nitems; i++) {
        items[i] = strdup(menu_items[i]);
    }
}

char ConsoleMenu::getMove() {
	char move;
	cin >> move;
	return move;
}

void ConsoleMenu::print() const {
	cout << "Choose a move: ";
	for(int i = 0; i < nitems - 1; i++) {
		cout << items[0] << ", ";
	}
	cout << items[nitems-1] << endl;
	return;
}
