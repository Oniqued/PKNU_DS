#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

Queue* create() { //Queue ���� �� �ʱ�ȭ //Queue�� �ش� component�� Queue��. comp_size�� ����� ������ �ش� queue �ı�
	Queue* q = (Queue*)malloc(sizeof(Queue));
	q->front = NULL;
	q->rear = NULL;
	q->comp_size = 0;
	
	return q;
}

void enqueue(Queue* q, Position pos) {
	Node* new_node = (Node*)malloc(sizeof(Node));
	
	new_node->pos = pos;
	new_node->next = NULL;
	if (q->front == NULL) { 
		//Queue�� �����͸� ó�� ���� ��, ť�� front�� new_node�� �ǰ� rear�� new_node�� �ȴ�
		q->front = new_node;
		q->rear = new_node; 
	}
	else { 
		// Queue�� �����͸� ������ ��, ���������� �߰��� // rear�� ���� ��带 new_node�� ���� >> ���� rear�� new_node�� ��
		q->rear->next = new_node;
		q->rear = new_node;
	}
	//Queue�� ��ǥ(pos)�� �ϳ��� �߰��� ������ �ش� comp_size�� 1�� ������Ŵ
	q->comp_size++;
}

Position dequeue(Queue* q) {
	Node* old_front;
	Position pos;

	old_front = q->front;
	pos = old_front->pos;
	q->front = old_front->next;
	if (q->front == NULL) { //�պκ��� ������, Queue�� ���� ����ٸ� Queue�� rear�κе� NULL�� �ٲ��ش�
		q->rear = NULL;
	}
	free(old_front); //�׿� ��� free

	return pos; // �� ����� ��ǥ ��ȯ
}

Position peek(Queue* q) { //Queue�� �� �պκ� ��ǥ ��ȯ
	if (isEmpty(q)) {
		printf("ERROR: Queue is empty\n");
	}
	return q->front->pos;
}

void destoy(Queue* q) {
	make_empty(q);
	free(q);
}

void make_empty(Queue* q) {
	while (!isEmpty(q)) {
		dequeue(q);
	}
	q->comp_size = 0;
}

bool isEmpty(Queue* q) {
	if (q->front == NULL) {
		return true; //NULL�̸� true ��ȯ
	}
	else {
		return false;
	}
}