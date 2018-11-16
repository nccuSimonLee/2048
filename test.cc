#include <iostream>
#include "ConsoleMenu.h"
#include "Board.h"
using namespace std;

const char * const menu_items[]={"I = UP",
				"K = DOWN",
				"J = LEFT",
				"L = RIGHT"};

int main() {
	Board board(4);
	board.initBoard();
	board.printBoard();
	ConsoleMenu menu(4, menu_items);
	menu.print();
	int move = menu.getMove();
	board.updateBoard(move);
	board.printBoard();
	return 0;
}
