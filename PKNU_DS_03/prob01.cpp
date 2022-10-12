//테스트 결과 데이터 출력 성공
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define BUFFER_SIZE 100

int main(void) {
	int arr_len;
	int arr[BUFFER_SIZE];
	printf("배열의 길이: ");
	scanf("%d", &arr_len);

	printf("정수 입력\n");
	for(int i = 0; i < arr_len; i++) {
		scanf("%d", &arr[i]);
	}
	
	//최댓값 찾기 
	int max_num;
	for (int i = 0; i < arr_len; i++) {
		int max = 0;
		//가장 큰 정수를 찾는다
		for (int j = 0; j < arr_len-i; j++) {
			if (arr[j] > max) {
				max = arr[j];
				max_num = j; //max인 배열의 번호 저장
			}
		}
		//arr[max_num]과 arr[(arr_len-1)-i] swap
		int tmp = arr[max_num];
		arr[max_num] = arr[(arr_len - 1) - i];
		arr[(arr_len - 1) - i] = tmp;
	}

	for (int i = 0; i < arr_len; i++) {
		printf("%d ", arr[i]);
	}
	
	return 0;
}