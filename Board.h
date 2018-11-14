#ifndef _BOARD_H
#define _BOARD_H

#include <math.h> 
int inline nDigits(int n) {
	// ?À„’˚îµÈL∂»
	return floor(log10(abs(n))) + 1;
}

class Board {
	public:
		Board();
		Board(int board_size);
		Board(const Board &originObject);
		~Board();
		void printBoard();
		void initBoard();
		void updateBoard(char move);
		
	private:
		int size;
		int **elements;
		static int board_bound_size;
		void setBoard();
		int *getRand(int num) const;
		void printBound();
		void printInside();
		void printNumber(int number);
		

};


#endif
