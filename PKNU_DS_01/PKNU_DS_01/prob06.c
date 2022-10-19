//테스트 데이터 결과 출력 완료 
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


double prob(int N, int k) {
	int test_time = 1000000; //실험 반복 횟수
	int dice; 
	int dice_1 = 0;
	double result;
	double tmp = 0;
	
	for (int i = 0; i < test_time; i++) {
		for (int j = 0; j < N; j++) { //입력 횟수만큼 주사위를 굴린다
			dice = (int)(rand() % 6 + 1); //주사위를 굴린다
			if (dice == 1) { //주사위에서 1 나온 횟수 세기
				dice_1++;
			}
		}
		if (dice_1 < k) { //1이 나온 횟수가 k보다 적으면 확률에 반영
			tmp++;
		}
		dice_1 = 0; //주사위에서 1이 나온 횟수 초기화
	}
	result = 1 - (tmp / test_time); //전체 확률에서 적어도 k번 1이 나올 확률
	return result;
}

int main(void) {
	int roll, times;
	srand((unsigned int)time(NULL)); //완전 랜덤을 위한 함수
	
	while (1) { //사용자가 올바른 값을 입력하지 않으면 입력을 다시 요청
		printf("주사위를 던지는 횟수(6의 배수로 입력, 36까지): ");
		scanf("%d", &roll);
		if (roll % 6 != 0) {
			printf("6의배수로 입력하십시오\n");
			continue;
		}
		else if(roll > 36) {
			printf("36이하의 숫자를 입력하십시오\n");
		}
		else {
			times = roll / 6;
			break;
		}
	}

	printf("%f", prob(roll, times)); //함수 실행결과를 출력

	return 0;
}
