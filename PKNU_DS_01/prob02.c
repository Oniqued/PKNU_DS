//테스트 결과 데이터 출력 완료
#include<stdio.h>

int main() {
	int num;
	int data[100];
	int tmp;

	while (1) {
		printf("Enter the number of data you want to compare (2 <= n <= 100): ");
		scanf_s("%d", &num); //사용자로부터 입력될 정수의 갯수를 입력 받는다
		if (num < 2) { //조건에 일치 하지 않을 시 실행
			printf("num must be over 1\n");
		}
		else if (num > 100) {
			printf("num must be under 101\n");
		}
		else { //조건에 일치 하면 반복문 탈출 
			break;
		}
	}
	for (int i = 0; i < num; i++) { //입력될 정수의 갯수 만큼 반복
		scanf_s("%d", &data[i]);
	}

	for (int i = 0; i < num; i++) { //정렬 알고리즘 
		for (int j = i + 1; j < num; j++) { //배열의 길이만큼 반복함
			if (data[i] > data[j]) { //[i]의 값이 [j]보다 크면 서로 스왑
				tmp = data[i];
				data[i] = data[j];
				data[j] = tmp;
			}
		}
	}

	printf("%d %d", data[0], data[1]);

	return 0;
}