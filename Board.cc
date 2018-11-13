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
	int tol = max - min + 1;  //�������
	int a[30000];  //��min~max�����Д��� 
	static int b[30000];  //��ȡ���āy�� 
	int i, j;
	for (i = 0; i<tol; i++) {  //����XҪӛ����Ŕ��֣���С�ŵ�����Ma[0]~a[tol-1] 
		*(a + i) = min + i;
	}
	srand(time(NULL));
	int ctr;  //�@ֻ�ǂ��������Á��ba[n]�e��n�����@��n���Áy���u��� 
	for (i = 0; i<num; i++) {
		ctr = rand() % (tol - i);
		b[i] = a[ctr];  //��ץ�õāy���G��b�e�� 
		for (j = ctr; j<(tol - 1 - i); j++) {  //�@�����������}�y�������Ľ������ڣ�
			a[j] = a[j + 1];  //��΢���ͨͨ��ǰ�Ƅ�һ�� 
		}
	}
	return b;
}
