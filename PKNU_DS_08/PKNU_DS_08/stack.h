#ifndef STACK_H
#define STACK_H

#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1000000

typedef struct testCase {
	int top;
	int stack[BUFFER_SIZE];
}*Case;

Case create();
void push(Case c, int num);
int pop(Case c);

#endif