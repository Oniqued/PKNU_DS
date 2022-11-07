#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 100
#define MAX_CAPACITY 100

int bracketType(char ch);
void push(int index);
char pop();

int stack[MAX_CAPACITY];
int top = -1; //top의 초기값은 stack에 아무것도 없는 상태 : -1

int main() {
	char buffer[BUFFER_SIZE];
	int index = 1;
	scanf("%s", buffer);
	for (int i = 0; buffer[i] != NULL; i++) {
		if (bracketType(buffer[i]) == 0) {
			push(index);
			index++;
		}
		else if (bracketType(buffer[i]) == 1) {
			pop();
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

void push(int index) {
	/*if (isFull()) { //stack이 가득 차면 더이상 넣을 수 없다
		printf("Stack is full\n");
		return;
	}*/
	top++;
	stack[top] = index;
	printf("%d ", stack[top]);
}

char pop() {
	/*if (isEmpty()) { //stack에 이미 아무것도 없으면 뺄 수 없다
		printf("There is nothing in Stack\n");
		return;
	}*/
	int tmp = stack[top];
	printf("%d ", stack[top]);
	top--;
	return tmp;
}