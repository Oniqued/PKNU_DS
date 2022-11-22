//테스트 결과 데이터 출력 성공
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX 1000

void countSum(int* data, int start, int end);

int count = 0;
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

	countSum(data, start, end);
	printf("%d\n", count);

	return 0;
}

void countSum(int *data, int start, int end) {
	int sum = data[start] + data[end];
	if (start >= end) {
		return;
	}
	else if (sum > K) {
		countSum(data, start, end-1);
	}
	else if (sum < K) {
		countSum(data, start+1, end);
	}
	else {
		count++;
		countSum(data, start+1, end-1);
	}
}

