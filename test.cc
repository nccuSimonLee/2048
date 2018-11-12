#include <iostream>
#include "ConsoleMenu.h"
using namespace std;

const char * const menu_items[]={"I = UP",
				"K = DOWN",
				"J = LEFT",
				"L = RIGHT"};
int main() {
	ConsoleMenu console(4, menu_items);
	console.print();
	char move = console.getMove();
	cout << "move is " << move << endl; 
	return 0;
}
