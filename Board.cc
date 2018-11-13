#include "Board.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stack>
using namespace std;


Board::Board() {
	size = 0;
}

Board::Board(int board_size) {
	size = board_size;
	setBoard();
}

Board::Board(const Board &originObject) {
	size = originObject.size;
	setBoard();
	for(int i = 0; i < size; i++) {
		for(int j = 0; j < size; j++)
			elements[i][j] = originObject.elements[i][j];
	}
}

Board::~Board() {
	for(int i = 0; i < size; i++)
		delete [] elements[i];
	delete [] elements;
}

// allocate the board's memory
void Board::setBoard() {
	elements = new int*[size]; // board_size row
	for(int i = 0; i < size; i++)
		elements[i] = new int[size]; // board_size column
}

// initialize a board, make it be filled with 0 and 2
void Board::initBoard() {
	int a, b; // the position in which need to put 2
	int *randnum = getRand(2);
	a = randnum[0];
	b = randnum[1];
	int count = 0;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if ((count == a) | (count == b)) elements[i][j] = 2;
			else elements[i][j] = 0;
			count++;
		}
	}
	return;
}



int* Board::getRand(int num) const {
	int max = size * size - 1, min = 0;
	int tol = max - min + 1;  //算出總數
	int a[30000];  //放min~max的所有數字 
	static int b[30000];  //放取出的亂數 
	int i, j;
	for (i = 0; i<tol; i++) {  //跟電腦要記憶格放數字，從小排到大放進a[0]~a[tol-1] 
		*(a + i) = min + i;
	}
	srand(time(NULL));
	int ctr;  //這只是個容器，拿來裝a[n]裡的n，而這個n是用亂數製造的 
	for (i = 0; i<num; i++) {
		ctr = rand() % (tol - i);
		b[i] = a[ctr];  //把抓好的亂數丟到b裡面 
		for (j = ctr; j<(tol - 1 - i); j++) {  //這是整個不重複亂數函數的經髓所在！
			a[j] = a[j + 1];  //很微妙的通通往前移動一格 
		}
	}
	return b;
}
