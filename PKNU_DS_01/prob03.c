//테스트 결과 데이터 출력 완료
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void) {
	int num, tmp;
	int arr[100]; //정수를 100개 까지 저장하는 배열
	int buffer[100];
	int n = 0;
	int isDup; //중복 상태
	printf("Enter number\n");
	while (scanf("%d", &num) != EOF) {
		if (num == -1) { //-1이 입력되면 프로그램 종료
			break;
		}
		isDup = 0; //중복 false로 초기화 
		for (int i = 0; i <= n; i++) { //중복 검사 실행
			if(arr[i] == num) { //num이 arr[i]와 일치하면 중복문구 출력
				printf("duplicate\n");
				isDup = 1; //중복 true
				n--; 
				break;
			}
		}
		
		if (isDup == 0) { //중복이 아닐때, 실행
			arr[n] = num; //중복이 아니면 입력받은 값이 그대로 배열에 대입

			for (int i = 0; i <= n; i++) {
				for (int j = i + 1; j <= n; j++) {
					if (arr[i] > arr[j]) {
						tmp = arr[i];
						arr[i] = arr[j];
						arr[j] = tmp;
					}
				}
			}

			for (int i = 0; i <= n; i++) {
				printf("[%d]", arr[i]);
			}
			printf("\n");
		}
		n++;
	}

	return 0;
}