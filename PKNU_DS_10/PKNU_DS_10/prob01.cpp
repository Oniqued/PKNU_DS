//�׽�Ʈ ��� ������ ��� ����
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
	//base case: �ѱ��� �� �ٿ������鼭 ���� ������ ����(No�� ����) || �߰��� ������ �ʴ� ����
	//���ڿ����� �������� ������ ���� (�˻��� �κб����� palindrome���� �˻�) ���� = ���� - ������
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