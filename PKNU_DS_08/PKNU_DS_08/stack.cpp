#include "stack.h"

//create 
//push 
//pop
//distroy

Case create() {
	Case c = (Case)malloc(sizeof(c));
	c->top = -1;

	return c;
}

void push(Case c, int num) {
	c->top++;
	c->stack[c->top] = num;
}

int pop(Case c) {
	int tmp = c->stack[c->top];
	c->top--;

	return tmp;
}