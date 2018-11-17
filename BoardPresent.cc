#include "Board.h"
#include "BoardPresent.h"
#include <cstdio>

BoardPresent::BoardPresent(int bound_size) {
	board_bound_size = bound_size;
}


void BoardPresent::print(const Board &board){
	// Your code goes here
	// ��������һ��һ��?
	for (int i = 0; i < board.size; i++) { // row
		printBound(); // ��?��
		printInside(board); // ���@�_ʼ���L���
		for (int j = 0; j < board.size; j++) { // column
			printNumber(board.elements[i][j], board);
		}
		printf("*\n");
		printInside(board);// ������L��?
	}
	printBound(); // ��?��
}

void BoardPresent::printBound() {
	for (int i = 0; i < board_bound_size; i++)
		printf("*");
	printf("\n");
}

void BoardPresent::printInside(const Board &board){
	// ?����P�Ȳ��Y?
	int n_space = (board_bound_size - board.size + 1) / board.size; // ��Pÿ���e��Ŀհה���
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
