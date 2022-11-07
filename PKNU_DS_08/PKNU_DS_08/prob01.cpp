#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 100
#define MAX_CAPACITY 100

int bracketType(char ch);
void push(int index);
char pop();

int stack[MAX_CAPACITY];
int top = -1; //top�� �ʱⰪ�� stack�� �ƹ��͵� ���� ���� : -1

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

void push(int index) {
	/*if (isFull()) { //stack�� ���� ���� ���̻� ���� �� ����
		printf("Stack is full\n");
		return;
	}*/
	top++;
	stack[top] = index;
	printf("%d ", stack[top]);
}

char pop() {
	/*if (isEmpty()) { //stack�� �̹� �ƹ��͵� ������ �� �� ����
		printf("There is nothing in Stack\n");
		return;
	}*/
	int tmp = stack[top];
	printf("%d ", stack[top]);
	top--;
	return tmp;
}