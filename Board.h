#ifndef _BOARD_H
#define _BOARD_H

#include "BoardPresent.h"
#include <math.h> 
int inline nDigits(int n) {
	// ?À„’˚îµÈL∂»
	return floor(log10(abs(n))) + 1;
}

class Board {
	friend BoardPresent;
	public:
		Board();
		Board(int board_size);
		Board(const Board &originObject);
		~Board();
		void initBoard();
		void updateBoard(int move);
		int getZeroPos() const; // get a random index of 0 in the board
		
	private:
		int size;
		int **elements;
		int *element_copy; // to retain the copy of a row of a column to update
		BoardPresent presenter;
		void setBoard(); // allocate memory for board
		int *getRand(int min, int max, int num) const;
		void updateRow(int index);
		void updateCol(int index);
		void reverse(int index, int row_or_col);
		void update();

};


#endif
