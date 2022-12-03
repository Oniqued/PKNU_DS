#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#define MAX 100

void queens(int row, int N, int* cols);
bool promising(int* cols, int row, int col);

int cnt;

int main() {
	int cols[MAX];
	for (int N = 1; N <= 15; N++) {
	cnt = 0;
		printf("N[%d] = ", N);
		queens(0, N, cols); 
		printf("%d\n", cnt);
	}
}

void queens(int row, int N, int* cols) {
	if (row == N) {
		cnt++;
		return;
	}

	for (int col = 0; col < N; col++) {
		cols[row] = col;
		if (promising(cols, row, col)) {
			queens(row + 1, N, cols);
		}
	}
}

//Queen이 이동 가능한지 체크 
bool promising(int* cols, int row, int col) {
	for (int i = 0; i < row; i++) {
		if (cols[i] == col) {
			return false;
		}
		else if ((row - i) == abs(col - cols[i])) {
			return false;
		}
	}
	return true;
}