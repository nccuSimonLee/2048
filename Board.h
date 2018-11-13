#ifndef _BOARD_H
#define _BOARD_H

class Board {
	public:
		Board();
		Board(int board_size);
		Board(const Board &originObject);
		~Board();
		void print() const;
		void initBoard();
		void updateBoard(char move);
		
	private:
		int size;
		int **elements;
		void setBoard();
		int *getRand(int num) const;

};

#endif
