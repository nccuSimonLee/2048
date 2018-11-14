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
		void setBoard();
		int *getRand(int num) const;
		void printBound(int n);
		void printInside(int n);
		void printNumber(int number, int n);
		

};

#endif
