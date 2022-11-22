//테스트 결과 데이터 출력 성공
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#define MAX 100

int compare(char* str1, char* str2);

int main() {
	char str1[MAX], str2[MAX];
	scanf("%s %s2", str1, str2);

	if (compare(str1, str2) > 0) {
		printf("%s\n%s\n", str2, str1);
	}
	else if (compare(str1, str2) <= 0) {
		printf("%s\n%s\n", str1, str2);
	}
}

int compare(char* str1, char* str2) {
	
	if (str1[0] > str2[0]) {
		return 1;
	}
	else if (str1[0] < str2[0]) {
		return -1;
	}
	else if (str1[0] == NULL && str2[0] == NULL) {
		return 0;
	}
	else {
		return compare(str1+1, str2+1);
	}
}