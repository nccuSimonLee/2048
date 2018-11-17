#include <iostream>
#include "ConsoleMenu.h"
#include "Board.h"
#include "BoardPresent.h"
using namespace std;

const char * const menu_items[]={"I = UP",
				"K = DOWN",
				"J = LEFT",
				"L = RIGHT"};

int main() {
	Board board(4);
	BoardPresent presenter;
	board.initBoard();
	//board.printBoard();
	presenter.printBoard(board);
	ConsoleMenu menu(4, menu_items);
	int move;
	while(board.getZeroPos() != -1) {
		menu.print();
		move = menu.getMove();
		board.updateBoard(move);
		presenter.printBoard(board);
	}
	return 0;
}
