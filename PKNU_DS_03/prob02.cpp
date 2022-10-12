//테스트 결과 데이터 출력 성공
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define INTERVAL_SIZE 256

//사용될 메서드
void sort(int inter_amt, int inter0[], int inter1[]);
void dup_sort(int arr_len, int arr0[], int arr1[]);

int main(void) {
	int inter0[INTERVAL_SIZE];
	int inter1[INTERVAL_SIZE];
	int inter_amt;

	printf("구간의 갯수 입력: ");
	scanf("%d", &inter_amt);
	
	printf("구간의 시작점과 끝 점을 %d번 입력\n", inter_amt);
	for (int i = 0; i < inter_amt; i++) {
		scanf("%d", &inter0[i]);
		scanf("%d", &inter1[i]);
	}

	sort(inter_amt, inter0, inter1);
	dup_sort(inter_amt, inter0, inter1);

	printf("\n");
	for (int i = 0; i < inter_amt; i++) {
		printf("%d %d\n", inter0[i], inter1[i]);
	}

	return 0;
}

//정렬 알고리즘 
void sort(int arr_len, int arr0[], int arr1[]) {
	for (int i = 0; i < arr_len; i++) {
		for (int j = 0; j < arr_len - 1; j++) {
			if (arr0[j] > arr0[j + 1]) {
				int tmp = arr0[j];
				arr0[j] = arr0[j + 1];
				arr0[j + 1] = tmp;
				
				//끝점은 시작점과 붙어 다님 
				tmp = arr1[j];
				arr1[j] = arr1[j + 1];
				arr1[j + 1] = tmp;
			}
		}
	}
}

//시작점이 같은 경우 끝점이 빠른 것이 먼저 출력되게 한다
void dup_sort(int arr_len, int arr0[], int arr1[]) {
	for (int i = 0; i < arr_len; i++) {
		if (arr0[i] == arr0[i + 1] && arr1[i] > arr1[i + 1]) {
			int tmp = arr1[i];
			arr1[i] = arr1[i + 1];
			arr1[i + 1] = tmp;
		}
	}
}