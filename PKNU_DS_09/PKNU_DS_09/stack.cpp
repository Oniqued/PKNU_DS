#include "stack.h"
#include <stdlib.h>

Stack* create() {
    Stack *s = (Stack *)malloc(sizeof(Stack));
    s->top = -1;

    return s;
}

void push(Stack *s, Position pos) {
    s->top++;
    s->pos[s->top] = pos;
}

Position pop(Stack *s) {
    Position tmp = s->pos[s->top];
    s->top--;
    
    return tmp;
}

bool isEmpty(Stack* s) {
    if (s->top < 0) {
        return true;
    }
    return false;
}