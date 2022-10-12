//테스트 데이터 결과 출력 성공
#include <stdio.h>

int main() {
	int num;
	printf("Please enter number: ");
	scanf_s("%d", &num);
	
	while (num > 0) {
		num = num / 2;
		printf("%d ", num);
	}

	return 0;
}