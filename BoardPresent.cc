#include "Board.h"
#include "BoardPresent.h"
#include <cstdio>

BoardPresent::BoardPresent(int bound_size) {
	board_bound_size = bound_size;
}


void BoardPresent::print(const Board &board){
	// Your code goes here
	// 從上往下一列一列?
	for (int i = 0; i < board.size; i++) { // row
		printBound(); // 上?界
		printInside(board); // 從這開始描繪棋格
		for (int j = 0; j < board.size; j++) { // column
			printNumber(board.elements[i][j], board);
		}
		printf("*\n");
		printInside(board);// 棋格描繪完?
	}
	printBound(); // 下?界
}

void BoardPresent::printBound() {
	for (int i = 0; i < board_bound_size; i++)
		printf("*");
	printf("\n");
}

void BoardPresent::printInside(const Board &board){
	// ?出棋盤內部結?
	int n_space = (board_bound_size - board.size + 1) / board.size; // 棋盤每格裡面的空白數量
	for (int i = 0; i < board.size; i++) { // column
		printf("*");
		for (int j = 0; j < n_space; j++)
			printf(" ");
	}
	printf("*\n");
}

void BoardPresent::printNumber(int number, const Board &board){
	int n_space = (board_bound_size - board.size + 1) / board.size;
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
