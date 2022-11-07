#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "stack.h"

#define BUFFER_SIZE 100

int bracketType(char ch);

int main() {
	char buffer[BUFFER_SIZE];
	int index = 1;
	scanf("%s", buffer);
	for (int i = 0; buffer[i] != NULL; i++) {
		if (bracketType(buffer[i]) == 0) {
			printf("%d ", index);
			index++;
		}
		else if (bracketType(buffer[i]) == 1) {
			index--;
			printf("%d ", index);
		}
	}

	return 0;
}

//��ȣ Ÿ�� �м�
int bracketType(char ch) { 
	if (ch == '(') { //ch�� ���� ��ȣ�� 0
		return 0;
	}
	else if (ch == ')') { //ch�� �ݴ� ��ȣ�� 1
		return 1;
	}
	else { //��ȣ�� �ƴϸ� -1
		return -1;
	}
}