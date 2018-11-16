#include "Board.h"
#include <cstdlib>
#include <cstdio> 
#include <ctime>
#include <iostream>
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
	delete [] element_copy;
}

// allocate the board's memory
void Board::setBoard() {
	elements = new int*[size]; // board_size row
	for(int i = 0; i < size; i++)
		elements[i] = new int[size]; // board_size column
	element_copy = new int[size];
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

void Board::updateBoard(int move) { // 1:left, 2:up, 3:right, 4:down
	int i;
	switch(move) {
		case 1: {
			for(i = 0; i < size; i++)
				updateRow(i);
			break;
		}
		case 2: {
			for(i = 0; i < size; i++)
				updateCol(i);
			break;
		}
		case 3: {
			for(i = 0; i < size; i++) {
				reverse(i, 0); // 0 = row, 1 = col
				updateRow(i);
				reverse(i, 0);
			}
			break;
		}
		case 4: {
			for(i = 0; i < size; i++) {
				reverse(i, 1);
				updateCol(i);
				reverse(i, 1);
			}
			break;
		}
	}
}

void Board::updateRow(int index) {
	int i;
	for(i = 0; i < size; i++)
		element_copy[i] = elements[index][i];
	update();
	for(i = 0; i < size; i++)
		elements[index][i] = element_copy[i];
}

void Board::updateCol(int index) {
	int i;
	for(i = 0; i < size; i++)
		element_copy[i] = elements[i][index];
	update();
	for(i = 0; i < size; i++)
		elements[i][index] = element_copy[i];
}

void Board::update() {
	/* the elements in a row or a column need to search the next non-zero element
	if the elements on the right of element[i] are all zero, then end the update procedure,
	otherwise, if the next element--element[j] is equal to element[i], add it to element[i] and set element[j] to zero.
	specially, if element[i] is zero, it need to i--, that means only move and no addition, so the next element equal to it can be added to it.
	finally, if the element[j] is not equal to element[i], then move it to element[i+1] and set element[j] to zero.*/
	int i, j, tmp_next;
	bool all_zero = false;
	for(i = 0; i < size - 1 && !all_zero; i++) {
		tmp_next = 0;
		for(j = i + 1; j < size; j++) {
			if(element_copy[j] != 0) {
				tmp_next = element_copy[j];
				element_copy[j] = 0;
				break;
			}
		}
		if(tmp_next == 0)
			all_zero = true;
		else {
			if(element_copy[i] == 0)
				element_copy[i--] += tmp_next;
			else if(element_copy[i] == tmp_next)
				element_copy[i] += tmp_next;
			else
				element_copy[i+1] = tmp_next;
		}
	} 
}

void Board::reverse(int index, int row_or_col) {
	int i, tmp;
	if(row_or_col == 0) { // row
		for(i = 0; i < size / 2; i++) {
			tmp = elements[index][i];
			elements[index][i] = elements[index][size-1-i];
			elements[index][size-1-i] = tmp;
		}
	}
	else {
		for(i = 0; i < size / 2; i++) {
			tmp = elements[i][index];
			elements[i][index] = elements[size-1-i][index];
			elements[size-1-i][index] = tmp;
		}
	}
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

void Board::printBoard() {
	// Your code goes here
	// 從上往下一列一列?
	for (int i = 0; i < size; i++) { // row
		printBound(); // 上?界
		printInside(); // 從這開始描繪棋格
		for (int j = 0; j < size; j++) { // column
			printNumber(elements[i][j]);
		}
		printf("*\n");
		printInside();// 棋格描繪完?
	}
	printBound(); // 下?界
}

void Board::printBound() {
	for (int i = 0; i < board_bound_size; i++)
		printf("*");
	printf("\n");
}

void Board::printInside() {
	// ?出棋盤內部結?
	int n_space = (board_bound_size - size + 1) / size; // 棋盤每格裡面的空白數量
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
