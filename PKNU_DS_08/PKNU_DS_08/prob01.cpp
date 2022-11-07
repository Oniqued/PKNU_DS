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

//괄호 타입 분석
int bracketType(char ch) { 
	if (ch == '(') { //ch가 여는 괄호면 0
		return 0;
	}
	else if (ch == ')') { //ch가 닫는 괄호면 1
		return 1;
	}
	else { //괄호가 아니면 -1
		return -1;
	}
}