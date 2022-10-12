#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 100

char buffer[BUFFER_SIZE];
//노드 구조체 
struct NODE {
	char* data;
	int count = 0;
	struct NODE* next;
}; 
typedef struct NODE Node; //NODE 타입의 변수 Node를 선언
Node* head = NULL; //첫 노드 (첫 노드를 잃어버리지 않도록 전역변수로 선언)

int main() {
	int total = 0;
	FILE* file = fopen("harry.txt", "r");
	if (file == NULL) {
		printf("ERROR! FAILED TO OPEN FILE\n");
		return;
	}
	
	while (fscanf(file, "%s", buffer) != EOF) {
		
		
	}


	fclose(file);

	return 0;
}

//데이터를 맨 앞에 넣을땐, 1. 새로운 노드 생성 2. 생성된 노드의 next를 다음 노드와 연결 3. 맨앞에 삽입
void addFront(char* word) {
	Node* tmp = (Node*)malloc(sizeof(Node));
	tmp->data = word;
	tmp->next = head; //새로운 노드의 next를 첫 노드였던 노드로 바꾼다 (최초 시행에는 첫 노드에 NULL 저장되어있음)
	head = tmp; //시작 노드는 이제 tmp가 된다 >> 시작노드 내용 즉, Node[0] : data = word, next = NULL
}

//사전식 순서에 맞게 적절히 데이터 삽입
void addAccord(char* word) {
	Node* p = head; //p는 첫번째 노드를 가리킴
	Node* q = NULL; //q는 p노드의 전 노드를 가리킴
	while(p != NULL && strcmp(p->data, word)) { //p가 NULL이 아니며 word가 p.data 보다 크거나 같다면 다음 노드로 이동
		
	}

}