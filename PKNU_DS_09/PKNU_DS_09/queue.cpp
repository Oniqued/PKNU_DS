#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

Queue* create() { //Queue 생성 및 초기화 //Queue는 해당 component의 Queue임. comp_size의 계산이 끝나면 해당 queue 파기
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
		//Queue에 데이터를 처음 넣을 때, 큐의 front는 new_node가 되고 rear도 new_node가 된다
		q->front = new_node;
		q->rear = new_node; 
	}
	else { 
		// Queue에 데이터를 삽입할 때, 끝에서부터 추가함 // rear의 다음 노드를 new_node와 연결 >> 이제 rear는 new_node가 됨
		q->rear->next = new_node;
		q->rear = new_node;
	}
	//Queue에 좌표(pos)가 하나씩 추가될 때마다 해당 comp_size를 1씩 증가시킴
	q->comp_size++;
}

Position dequeue(Queue* q) {
	Node* old_front;
	Position pos;

	old_front = q->front;
	pos = old_front->pos;
	q->front = old_front->next;
	if (q->front == NULL) { //앞부분을 삭제후, Queue가 이제 비었다면 Queue의 rear부분도 NULL로 바꿔준다
		q->rear = NULL;
	}
	free(old_front); //잉여 노드 free

	return pos; // 뺀 노드의 좌표 반환
}

Position peek(Queue* q) { //Queue의 맨 앞부분 좌표 반환
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
		return true; //NULL이면 true 반환
	}
	else {
		return false;
	}
}