#include "stack.h"
#define MAX_CAPACITY 100

int stack[MAX_CAPACITY];
int top = -1; //top�� �ʱⰪ�� stack�� �ƹ��͵� ���� ���� : -1

void push(int index) {
	/*if (isFull()) { //stack�� ���� ���� ���̻� ���� �� ����
		printf("Stack is full\n");
		return;
	}*/
	top++;
	stack[top] = index;
}

char pop() {
	/*if (isEmpty()) { //stack�� �̹� �ƹ��͵� ������ �� �� ����
		printf("There is nothing in Stack\n");
		return;
	}*/
	int tmp = stack[top];
	top--;
	return tmp;
}