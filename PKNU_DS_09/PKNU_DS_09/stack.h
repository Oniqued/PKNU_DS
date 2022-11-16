#ifndef STACK_H
#define STACK_H

#include "pos.h"

#define STACK_SIZE 2500

typedef struct stack {
    Position pos[STACK_SIZE];
    int top;
    int comp_size;
}Stack;

Stack* create();
void initStack(Stack*);
void push(Stack *, Position pos);
Position pop(Stack *);
bool isEmpty(Stack *);

#endif STACK_H