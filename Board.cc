#include "Board.h"
#include <cstdlib>
#include <cstdio> 
#include <ctime>
#include <iostream>
#include <stack>
using namespace std;

int Board::board_bound_size = 29;
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

void Board::printBoard() {
	// Your code goes here
	// ��������һ��һ��?
	for (int i = 0; i < size; i++) { // row
		printBound(); // ��?��
		printInside(); // ���@�_ʼ���L���
		for (int j = 0; j < size; j++) { // column
			printNumber(elements[i][j]);
		}
		printf("*\n");
		printInside();// ������L��?
	}
	printBound(); // ��?��
}

void Board::printBound() {
	for (int i = 0; i < board_bound_size; i++)
		printf("*");
	printf("\n");
}

void Board::printInside() {
	// ?����P�Ȳ��Y?
	int n_space = (board_bound_size - size + 1) / size; // ��Pÿ���e��Ŀհה���
	for (int i = 0; i < size; i++) { // column
		printf("*");
		for (int j = 0; j < n_space; j++)
			printf(" ");
	}
	printf("*\n");
}

void Board::printNumber(int number) {
	int n_space = (board_bound_size - size + 1) / size;
	int n_len; int inside_spa;
	int j;
	if (number) {
		n_len = nDigits(number);
		if (n_len >= 4) inside_spa = 1;
		else inside_spa = n_space / 2 - n_len + 1;
		printf("*");
		for (j = 0; j < inside_spa; j++)
			printf(" ");
		printf("%d", number);
		for (j = 0; j < n_space - (n_len + inside_spa); j++)
			printf(" ");
	}
	else {
		printf("*");
		for (j = 0; j < n_space; j++)
			printf(" ");
	}
}
