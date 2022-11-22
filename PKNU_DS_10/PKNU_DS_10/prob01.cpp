//테스트 결과 데이터 출력 성공
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#define MAX 100

bool isPalindrome(char* input, int begin, int end);

int main() {
	char input[MAX];
	scanf("%s", input);
	int len = strlen(input);
	int begin = 0;
	int end = len - 1;
	
	isPalindrome(input, begin, end);

	return 0;
}

bool isPalindrome(char *input, int begin, int end) {
	//base case: 한글자 씩 줄여나가면서 같지 않을때 까지(No인 동안) || 중간을 지나지 않는 동안
	//문자열에서 시작점과 끝점을 지정 (검사한 부분까지만 palindrome인지 검사) 길이 = 끝점 - 시작점
	if (input[begin] != input[end]) {
		printf("No\n");
		return false;
	}
	else if (begin > end) { 
		printf("Yes\n");
		return true;
	}
	else {
		return isPalindrome(input, begin+1, end-1);
	}
}