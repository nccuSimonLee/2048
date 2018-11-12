#include <stdio.h>
#include <math.h>
#include <time.h>
#include <conio.h>
#include <stdlib.h>
#include <unordered_map>
#define MAXSIZE 4

struct Stack {
	int data[MAXSIZE];
	int top;
};
typedef struct Stack stack;

void UpdateBoard(int board[4][4], char move, int newboard[4][4]);
void PrintBoard(int board[4][4]);
void InitBoard(int board[4][4]);
void SwapBoard(int oldboard[4][4], int newboard[4][4]);
int Direction(char c);
int GetZeroPos(int board[4][4]);
int CheckDir(char c, char std_dir[8]);

void PrintArr(int arr[], int n) {
	for (int i = 0; i < n; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
	return;
}


// for data structure stack
void StackInit(stack *s) {
	s->top = -1;
}

int isempty(stack *s) {
	if (s->top == -1) return 1;
	else return 0;
}

int isfull(stack *s) {
	if (s->top < MAXSIZE - 1) return 0;
	else return 1;
}

void Push(int item, stack *s) {
	if (isfull(s) == 1) {
		printf("Error: stack overflow\n");
	}
	else {
		s->data[++s->top] = item;
	}
	return;
}

int Pop(stack *s) {
	if (isempty(s)) {
		printf("Error: stack empty\n");
	}
	else {
		return s->data[s->top--];
	}
	return -1;
}
// =================================================

int CheckDir(char c, char std_dir[8]) {
	for (int i = 0; i < 8; i++) {
		if (c == std_dir[i]) return 1;
	}
	return 0;
}


int Direction(char c) {
	switch (c)
	{
	case 'i': case 'I':
		printf("Up\n");
		break;
	case 'k': case 'K':
		printf("Down\n");
		break;
	case 'j': case 'J':
		printf("Left\n");
		break;
	case 'l': case 'L':
		printf("Right\n");
		break;
	default:
		return -1;
	}
	return 0;
}


// game function
void ColtoA(int arr[4], stack *a) {
	int i;
	for (i = 3; i > -1; i--) {
		Push(arr[i], a);
	}
	return;
}

void AtoB(stack *a, stack *b) {
	int tmp1, tmp2;
	tmp1 = Pop(a);
	while (isempty(a) == 0) {
		tmp2 = Pop(a);
		if (tmp1 > 0) {
			if (tmp1 == tmp2) {
				Push(tmp1 + tmp2, b);
				tmp1 = 0;
			}
			else if (tmp2 > 0) {
				Push(tmp1, b);
				tmp1 = tmp2;
			}
			else continue;
		}
		else tmp1 = tmp2;
	}
	if (tmp1) Push(tmp1, b);
	while (isfull(b) == 0) {
		Push(0, b);
	}
	return;
}

void BtoC(stack *b, stack *c) {
	int tmp1;
	while (isempty(b) == 0) {
		tmp1 = Pop(b);
		if (tmp1 > 0) Push(tmp1, c);
	}
	while (isfull(c) == 0) {
		Push(0, c);
	}
	return;
}

void BC(stack *b, stack *c) {
	stack tmp;
	StackInit(&tmp);
	while (isfull(&tmp) == 0) {
		Push(Pop(b), &tmp);
	}
	while (isempty(&tmp) == 0) {
		Push(Pop(&tmp), c);
	}
	return;
}


void UpdateCol(int arr[], stack *s, char move) {
	stack A;
	StackInit(&A);
	stack B;
	StackInit(&B);
	ColtoA(arr, &A);
	AtoB(&A, &B);
	if ((move == 'j') | (move == 'i')) {
		BC(&B, s);
		return;
	}
	BtoC(&B, s);
	return;
}

void ExtractColRow(int arr[][4], int m, int n, int op[]) {
	if (n == -1) { // extract row
		for (int i = 0; i < 4; i++) {
			op[i] = arr[m][i];
		}
	}
	else {
		for (int i = 0; i < 4; i++) {
			op[i] = arr[i][n];
		}
	}
	return;
}

void Reverse(int arr[], int n) {
	int tmp;
	int i = 0, j = n - 1;
	while (i < j) {
		tmp = arr[i];
		arr[i] = arr[j];
		arr[j] = tmp;
		i++;
		j--;
	}
	return;
}

int* getRand(int min, int max, int num) {
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


void InitBoard(int board[4][4]) {
	int a, b, i, j, count;
	int *randnum;
	randnum = getRand(0, 15, 2);
	a = randnum[0];
	b = randnum[1];
	count = 0;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if ((count == a) | (count == b)) board[i][j] = 2;
			else board[i][j] = 0;
			count++;
		}
	}
	return;
}

int GetZeroPos(int board[4][4]) {
	int pos[16], i, j;
	int k = 0, count = 0, n = 0;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (board[i][j] == 0) {
				pos[k] = count;
				k++;
			}
			count++;
		}
	}
	for (i = 0; i < 15; i++) {
		if (pos[i] >= 0) n++;
	}
	if (n > 0) {
		int *randpos = getRand(0, n, 1);
		return pos[randpos[0]];
	}
	else return -1;
}

void UpdateBoard(int board[4][4], char move, int newboard[4][4]) {
	int i, j, arr[4];
	switch (move) {
	case 'k': case 'K': { //downward or rightward
		stack C;
		StackInit(&C);
		for (i = 0; i < 4; i++) {
			ExtractColRow(board, -1, i, arr);
			UpdateCol(arr, &C, move);
			for (j = 0; j < 4; j++) {
				newboard[j][i] = Pop(&C);
			}
		}
		break;
	}
	case 'l': case 'L': {
		stack C;
		StackInit(&C);
		for (i = 0; i < 4; i++) {
			ExtractColRow(board, i, -1, arr);
			UpdateCol(arr, &C, move);
			for (j = 0; j < 4; j++) {
				newboard[i][j] = Pop(&C);
			}
		}
		break;
	}
	case 'i': case 'I': {//upward or leftward
		stack C;
		StackInit(&C);
		for (i = 0; i < 4; i++) {
			ExtractColRow(board, -1, i, arr);
			//Reverse(arr, 4);
			UpdateCol(arr, &C, move);
			for (j = 3; j > -1; j--) {
				newboard[j][i] = Pop(&C);
			}
		}
		break;
	}
	case 'j': case 'J': {
		stack C;
		StackInit(&C);
		for (i = 0; i < 4; i++) {
			stack C;
			StackInit(&C);
			ExtractColRow(board, i, -1, arr);
			//Reverse(arr, 4);
			UpdateCol(arr, &C, move);
			for (j = 3; j > -1; j--) {
				newboard[i][j] = Pop(&C);
			}
		}
		break;
	}
	}
	int zeropos = GetZeroPos(newboard); // get zero position
	int count = 0;
	if (zeropos >= 0) { // put 2(90%) or 4(10%) into it
		int *p;
		int randn;
		for (i = 0; i < 4; i++) {
			if (zeropos == -1) break;
			for (j = 0; j < 4; j++) {
				if (count == zeropos) {
					p = getRand(1, 10, 1);
					if (p[0] > 1) randn = 2;
					else randn = 4;
					newboard[i][j] = randn;
					zeropos = -1;
					break;
				}
				count++;
			}
		}
	}
	return;
}

void SwapBoard(int oldboard[4][4], int newboard[4][4]) {
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			oldboard[i][j] = newboard[i][j];
		}
	}
	return;
}


// Print board function
void PrintBound(int n) {
	// ?出?界 ; n = ?界長度
	for (int i = 1; i <= n; i++) {
		printf("*");
	}
	printf("\n");
}

void PrintInside(int n) {
	// ?出棋盤內部結?
	int n_space = (n - MAXSIZE + 1) / MAXSIZE; // 棋盤每格裡面的空白數量
	for (int i = 1; i <= 4; i++) { // column
		printf("*");
		for (int j = 1; j <= n_space; j++) {
			printf(" ");
		}
	}
	printf("*\n");
}

int nDigits(int n) {
	// ?算整數長度
	return floor(log10(abs(n))) + 1;
}

void PrintNumber(int number, int n) {
	int n_space = (n - MAXSIZE + 1) / MAXSIZE;
	int n_len; int inside_spa;
	if (number) {
		n_len = nDigits(number);
		if (n_len >= 4) inside_spa = 1;
		else inside_spa = n_space / 2 - n_len + 1;
		printf("*");
		for (int j = 1; j <= inside_spa; j++) {
			printf(" ");
		}
		printf("%d", number);
		for (int j = 1; j <= n_space - (n_len + inside_spa); j++) {
			printf(" ");
		}
	}
	else {
		printf("*");
		for (int j = 1; j <= n_space; j++) {
			printf(" ");
		}
	}
}

void PrintBoard(int b[4][4]) {

	// Your code goes here
	// 從上往下一列一列?
	for (int i = 0; i <= 3; i++) { // row
		PrintBound(29); // 上?界
		PrintInside(29); // 從這開始描繪棋格
		for (int j = 0; j <= 3; j++) { // column
			PrintNumber(b[i][j], 29);
		}
		printf("*\n");
		PrintInside(29);// 棋格描繪完?
	}
	PrintBound(29); // 下?界
}


int FastLog2(int a) {
	if (a == 0) {
		return 0;
	}

	int count = 0;
	while (a != 1) {
		a = a >> 1;
		count++;
	}
	return count;
}

unsigned long long Digest(int board[4][4]) {
	// convert the board into a long long number
	unsigned long long h = 0;

	unsigned long long basis = 1;
	for (int i = 3; i >= 0; i--) {
		for (int j = 3; j >= 0; j--) {
			int temp = FastLog2(board[i][j]);
			h += temp * basis;
			basis *= 16;
		}
	}

	return h;
}

//Copy the content of src to dst
void CopyBoard(int dst[4][4], int src[4][4]) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			dst[i][j] = src[i][j];
		}
	}
}

//return 1 if the contents of b1 and b2 are the same
//return 0 otherwise
int AreEqual(int b1[4][4], int b2[4][4]) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (b1[i][j] != b2[i][j]) {
				return 0;
			}
		}
	}
	return 1;
}

int CalScore(int b[4][4]) {
	int score = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			score += pow(3, FastLog2(b[i][j]));
		}
	}
	return score;
}

int GetScore(int b[4][4], std::unordered_map<unsigned long long, int> H) {
	unsigned long long h = Digest(b);
	if (H.find(h) != H.end()) {
		return H[h];
	}
	else {
		return -1;
	}
}

char AIGenNextMove(int b[4][4], std::unordered_map<unsigned long long, int> H) {
	char move = 'i'; //move = 'i', 'k', 'j', or 'l'
	char movearr[4] = { 'i', 'k', 'j', 'l' };
	char bestMove;
	int highestScore = -1;
	int tmp_score, score, score2, score3, score4;
	int tempBoard[4][4], tempBoard2[4][4], tempBoard3[4][4], tempBoard4[4][4];

	for (int l = 0; l < 4; l++) {
		UpdateBoard(b, movearr[l], tempBoard4);
		if (AreEqual(tempBoard4, b)) {
			continue;
		}
		score4 = GetScore(tempBoard4, H);
		if (score4 == -1) {
			score4 = CalScore(tempBoard4);
			H[Digest(tempBoard4)] = score4;
		}
		for (int k = 0; k < 4; k++) {
			score3 = score4;
			UpdateBoard(tempBoard4, movearr[k], tempBoard3);
			if (AreEqual(tempBoard3, b)) {
				continue;
			}
			tmp_score = GetScore(tempBoard3, H);
			if (tmp_score == -1) {
				tmp_score = CalScore(tempBoard3);
				H[Digest(tempBoard3)] = tmp_score;
			}
			score3 += tmp_score;
			for (int j = 0; j < 4; j++) {
				score2 = score3;
				UpdateBoard(tempBoard3, movearr[j], tempBoard2);
				if (AreEqual(tempBoard2, b)) {
					continue;
				}
				tmp_score = GetScore(tempBoard2, H);
				if (tmp_score == -1) {
					tmp_score = CalScore(tempBoard2);
					H[Digest(tempBoard2)] = tmp_score;
				}
				score2 += tmp_score;
				for (int i = 0; i < 4; i++) {
					score = score2;
					UpdateBoard(tempBoard2, movearr[i], tempBoard);
					if (AreEqual(tempBoard, b)) {
						continue;
					}
					tmp_score = GetScore(tempBoard, H);
					if (tmp_score == -1) {
						tmp_score = CalScore(tempBoard);
						H[Digest(tempBoard)] = tmp_score;
					}
					score += tmp_score;
					if (score >= highestScore) {
						highestScore = score;
						bestMove = movearr[l]; // The outermost layer of for loop
					}
				}
			}
		}
	}

	return bestMove;
}

int IsGameOver(int board[4][4]) {
	if (GetZeroPos(board) != -1) {
		return 0;
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {
			if (board[i][j] == board[i][j + 1]) {
				return 0;
			}
		}
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 4; j++) {
			if (board[i][j] == board[i + 1][j]) {
				return 0;
			}
		}
	}

	return 1;
}

int main() {
	int board[4][4];
	int newboard[4][4];
	InitBoard(board);
	PrintBoard(board);
	char move;
	char std_dir[8] = { 'i', 'I', 'k', 'K', 'j', 'J', 'l', 'L' };
	int Interupt = 0;
	/*hash table*/std::unordered_map<unsigned long long /*key type*/, int /*value type*/> H;
	while (!IsGameOver(board)) {
		/*move = _getch();
		while (!CheckDir(move, std_dir)) {
		if ((move == 'z') | (move == 'Z')) {
		Interupt = 1;
		break;
		}
		move = _getch();
		}*/
		move = AIGenNextMove(board, H);
		if (Interupt) break;
		system("CLS");
		UpdateBoard(board, move, newboard);

		PrintBoard(board);
		printf("\n");
		Direction(move);
		printf("\n");
		PrintBoard(newboard);
		printf("\n");

		printf("score: %d\n", CalScore(newboard));
		SwapBoard(board, newboard);
	}
	printf("game over !\n");
	getchar();
	return 0;
}