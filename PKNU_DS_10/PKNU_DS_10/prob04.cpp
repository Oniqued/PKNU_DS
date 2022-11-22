//테스트 결과 데이터 출력 성공
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX 1000

void floor(int* data, int start, int end);
void ceiling(int* data, int start, int end);

int K;

int main() {
	int data[MAX];
	int N;

	scanf("%d", &N);
	int start = 0, end = N - 1;
	for (int i = 0; i < N; i++) {
		scanf("%d", &data[i]);
	}
	scanf("%d", &K);
	floor(data, start, end);
	ceiling(data, start, end);

	return 0;
}

void floor(int *data, int start, int end) {
	if (start > end) {
		printf("%d\n", data[end]);
		return;
	}
	else if (data[start] >= K) {
		if (start == 0) {
			printf("-1\n");
			return;
		}
		printf("%d\n", data[start - 1]);
		return;
	}
	else {
		floor(data, start + 1, end);
	}
}

void ceiling(int *data, int start, int end) {
	if (start > end) {
		printf("-1\n");
		return;
	}
	else if (data[start] >= K) {
		if (data[start] == K) {
			printf("%d\n", data[start+1]);
			return;
		}
		printf("%d\n", data[start]);
		return;
	}
	else {
		ceiling(data, start + 1, end);
	}
}