//테스트 결과 데이터 출력 완료
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int num, r_num, arr_len; //사용자 입력 데이터 
	int n = 0;
	printf("배열의 길이: ");
	scanf("%d", &arr_len); //입력될 정수의 갯수를 입력 받음
	int* arr= (int*)malloc(arr_len * sizeof(int));
	
	printf("데이터 입력(띄어쓰기로 구분, 데이터는 9999를 넘지 않습니다): ");
	while (n < arr_len) {
		scanf("%d", &num);
		arr[n] = num;
		n++;
	}
	printf("r_num과 가까운 수 찾기\nr_num: ");
	scanf("%d", &r_num);
	
	int buffer, result;
	int comp_num = 9999; //비교 초기 값은 9999
	for (int i = 0; i < arr_len; i++) { //반복문을 돌며 절댓값을 구하고, 
		if (r_num > arr[i]) {
			buffer = r_num - arr[i];
		}
		else {
			buffer = arr[i] - r_num;
		}
		if (comp_num >= buffer) { //절댓값이 현재 comp_num보다 작으면 result에 arr[i]를 넣습니다
			comp_num = buffer;
			result = arr[i];
		}
	}
	printf("%d", result); //절댓값 차이가 가장 작은 arr[i]가 출력됩니다 
	

	return 0;
}