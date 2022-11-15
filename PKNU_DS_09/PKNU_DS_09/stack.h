#ifndef STACK_H
#define STACK_H

#include "pos.h"

#define STACK_SIZE 2500

typedef struct stack {
    Position* pos[STACK_SIZE];
    int top;
}Stack;

Stack create();

#endif STACK_H