#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#define MAX 100

void queens(int level, int N, int* cols);
bool promising(int* cols, int level);

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

void queens(int level, int N, int* cols) {
	if (level == N) {
		cnt++;
		return;
	}
	for (int i = 0; i <= N; i++) {
		cols[level + 1] = i;
		if (promising(cols, level)) {
			queens(level + 1, N, cols);
		}
	}
}

//Queen이 이동 가능한지 체크 
bool promising(int* cols, int level) {
	for (int i = 0; i < level; i++) {
		if (cols[i] == cols[level]) {
			return false;
		}
		else if ((level - i) == abs(cols[level] - cols[i])) {
			return false;
		}
	}
	return true;
}