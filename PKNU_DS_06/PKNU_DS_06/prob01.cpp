#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 100

//노드 구조체 
struct NODE {
	char data[BUFFER_SIZE]; //노드의 데이터
	int count = 0; //해당 단어의 등장 횟수를 저장할 변수 
	struct NODE* next; //해당 노드의 다음 번지를 가리킨다
}; 
typedef struct NODE Node; //NODE 타입의 변수 Node를 선언

//사용될 전역 변수
int total = 0; //전체 단어 등장 횟수를 저장할 변수

//사용될 함수
void addFront(char *word);
void addAccord(char *word);
void addAfter(Node* prev, char *word);

Node* head = NULL; //첫 노드 (첫 노드를 잃어버리지 않도록 전역변수로 선언)

int main() {
	char buffer[BUFFER_SIZE]; //파일에서 읽어들인 단어를 임시로 저장할 공간

	FILE* file = fopen("harry.txt", "r");
	if (file == NULL) {
		printf("ERROR! FAILED TO OPEN FILE\n");
		return 0;
	}
	while (fscanf(file, "%s", buffer) != EOF) {
		addAccord(buffer);
	}

	for (Node* p = head; p != NULL; p = p->next) {
		printf("%s: %d\n", p->data, p->count);
	}
	
	printf("%d\n", total);
	

	fclose(file);

	return 0;
}

//데이터를 맨 앞에 넣을땐, 1. 새로운 노드 생성 2. 생성된 노드의 next를 다음 노드와 연결 3. 맨앞에 삽입
void addFront(char *word) {
	Node* tmp = (Node*)malloc(sizeof(Node));
	strcpy(tmp->data, word);
	tmp->count++; //단어가 추가되었으므로 count 증가
	total++;
	tmp->next = head; //새로운 노드의 next를 첫 노드였던 노드로 바꾼다 (최초 시행에는 첫 노드에 NULL 저장되어있음)
	head = tmp; //시작 노드는 이제 tmp가 된다 >> 시작노드 내용 즉, Node[0] : data = word, next = NULL
}

//해당 노드 앞에 노드를 추가하는 함수
void addAfter(Node* prev, char *word) {
	if (prev == NULL) { //해당 노드가 첫번째 노드면 addFront를 실행한다.
		addFront(word);
		return;
	}
	//해당 노드 앞에 넣으려면 새로운 Node를 하나 만들고 새로운 노드에 데이터를 넣는다. 
	//그리고 새로운 노드와 다음 노드를 연결해주고 직전 노드는 새로운 노드와 연결한다.
	Node* tmp = (Node*)malloc(sizeof(Node));
	strcpy(tmp->data, word);
	tmp->count++; //단어가 추가되었으므로 count증가
	total++;
	tmp->next = prev->next;
	prev->next = tmp;
}

//사전식 순서에 맞게 적절히 데이터 삽입
void addAccord(char *word) {
	Node* curr = head; //cur는 첫번째 노드를 가리킴
	Node* prev = NULL; //pre는 cur노드의 전 노드를 가리킴 (노드에 데이터를 삽입하려면 직전 노드의 주소를 알고있어야하므로)
	while(curr != NULL && strcmp(curr->data, word) <= 0) { //cur가 NULL이 아니며 word가 pre.data 보다 크거나 같다면 다음 노드로 이동
		prev = curr; //pre에 cur를 저장 (pre는 cur-1번째 노드) (노드에 데이터를 삽입하려면 직전 노드의 주소를 알고있어야하므로)
		curr = curr->next; //다음 노드로 이동하며 word보다 크기가 큰 데이터를 찾음
	}
	if (prev == NULL) { //word가 노드 중 제일 크기가 작은 단어라면 
		addFront(word); //노드 첫번째에 단어를 넣는다
		return;
	}
	if (strcmp(curr->data, word) == 0) {
		curr->count++; //단어가 추가되었으므로 count 증가
		total++;
		return;
	}
	addAfter(prev, word);
}