#ifndef _BOARDPRESENT_H
#define _BOARDPRESENT_H

#include "Board.h"

class Board;

class BoardPresent {
	public:
		BoardPresent(int bound_size=29);
		void print(const Board &board);
		
	private:
		int board_bound_size;
		void printBound();
		void printInside(const Board &board);
		void printNumber(int number, const Board &board);
};


#endif
