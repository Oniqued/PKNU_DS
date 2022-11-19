#ifndef QUEUE_H
#define QUEUE_H

#include "pos.h"

typedef struct node {
	Position pos;
	node* next;
}Node;

typedef struct queue {
	Node* front;
	Node* rear;
	int comp_size;
}Queue;

Queue* create();
void enqueue(Queue*, Position pos);
Position dequeue(Queue*);
Position peek(Queue*);
void destoy(Queue*);
void make_empty(Queue*);
bool isEmpty(Queue*);

#endif