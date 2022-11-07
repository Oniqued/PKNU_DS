#include "stack.h"
#define MAX_CAPACITY 100

int stack[MAX_CAPACITY];
int top = -1; //top의 초기값은 stack에 아무것도 없는 상태 : -1

void push(int index) {
	/*if (isFull()) { //stack이 가득 차면 더이상 넣을 수 없다
		printf("Stack is full\n");
		return;
	}*/
	top++;
	stack[top] = index;
}

char pop() {
	/*if (isEmpty()) { //stack에 이미 아무것도 없으면 뺄 수 없다
		printf("There is nothing in Stack\n");
		return;
	}*/
	int tmp = stack[top];
	top--;
	return tmp;
}