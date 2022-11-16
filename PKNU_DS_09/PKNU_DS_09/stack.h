#ifndef STACK_H
#define STACK_H

#include "pos.h"

#define STACK_SIZE 2500

typedef struct stack {
    Position pos[STACK_SIZE];
    int top;
}Stack;

Stack* create();
void push(Stack *, Position pos);
Position pop(Stack *);
bool isEmpty(Stack *);

#endif STACK_H