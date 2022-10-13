#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 100

//노드 구조체 
struct NODE {
	char *data; //노드의 데이터
	int count; //해당 단어의 등장 횟수를 저장할 변수 
	struct NODE* next; //해당 노드의 다음 번지를 가리킨다
};
typedef struct NODE Node; //NODE 타입의 변수 Node를 선언
Node* head = NULL; //첫 노드 (첫 노드를 잃어버리지 않도록 전역변수로 선언)
Node* headDesc = NULL;

//사용될 함수
void addFront(char* word);
void removeFront();
void addAccord(char* word);
void addAfter(Node* prev, char* word);
void removeAfter(Node* prev);
void printNode();
void delNodeUnder(int c);
void descNode();


int main() {
	char buffer[BUFFER_SIZE]; //파일에서 읽어들인 단어를 임시로 저장할 공간

	FILE* file = fopen("harry.txt", "r");
	if (file == NULL) {
		printf("ERROR! FAILED TO OPEN FILE\n");
		return 0;
	}
		
	while (fscanf(file, "%s", buffer) != EOF) {
		addAccord(strdup(buffer));
	}
	fclose(file);

	//printf("[문제1] 파일 내 모든 단어 & 빈도수 출력\n");
	//printNode();
	//printf("------------------------------------------\n\n");
	//printf("[문제2] 단어 등장 빈도가 10보다 높은 단어만 출력\n");
	//delNodeUnder(10);
	//printNode();
	descNode();

	return 0;
}

//데이터를 맨 앞에 넣을땐, 1. 새로운 노드 생성 2. 생성된 노드의 next를 다음 노드와 연결 3. 맨앞에 삽입
void addFront(char* word) {
	Node* tmp = (Node*)malloc(sizeof(Node));
	tmp->data = word; // strcpy no, 주소 대입
	tmp->count = 1; //단어가 새로 생겼으므로 count = 1
	tmp->next = head; //새로운 노드의 next를 첫 노드였던 노드로 바꾼다 (최초 시행에는 첫 노드에 NULL 저장되어있음)
	head = tmp; //시작 노드는 이제 tmp가 된다 >> 시작노드 내용 즉, Node[0] : data = word, next = NULL
}

//맨앞 노드를 삭제
void removeFront() {
	head = head->next; //맨 앞노드를 삭제하려면 현재 head를 다음 노드로 바꿔주면 된다.
	//free?
}

//해당 노드 앞에 노드를 추가하는 함수
void addAfter(Node* prev, char* word) {
	if (prev == NULL) {
		return;
	}
	//해당 노드 앞에 넣으려면 새로운 Node를 하나 만들고 새로운 노드에 데이터를 넣는다. 
	//그리고 새로운 노드와 다음 노드를 연결해주고 직전 노드는 새로운 노드와 연결한다.
	Node* tmp = (Node*)malloc(sizeof(Node));
	tmp->data = word;
	tmp->count = 1; //단어가 추가되었으므로 count = 1
	tmp->next = prev->next;
	prev->next = tmp;
}

//해당 노드의 다음 노드를 삭제하는 함수
void removeAfter(Node* prev) { //이전 노드가 NULL이면 지워야할 노드는 head인것이므로 head의 정보를 변경해줘야한다.
	Node* tmp = prev->next; //현재 노드
	if (tmp == NULL) {
		return;
	}
	else { //다음 노드를 제외했다. 이전 노드는 그대로 prev가 된다
		prev->next = tmp->next;
	}
}

//사전식 순서에 맞게 적절히 데이터 삽입
void addAccord(char* word) {
	Node* curr = head; //cur는 첫번째 노드를 가리킴
	Node* prev = NULL; //pre는 cur노드의 전 노드를 가리킴 (노드에 데이터를 삽입하려면 직전 노드의 주소를 알고있어야하므로)
	while (curr != NULL && strcmp(curr->data, word) <= 0) { //cur가 NULL이 아니며 word가 pre.data 보다 크거나 같다면 다음 노드로 이동
		if (strcmp(curr->data, word) == 0){
			curr->count++;
			return;
		}
		prev = curr; //pre에 cur를 저장 (pre는 cur-1번째 노드) (노드에 데이터를 삽입하려면 직전 노드의 주소를 알고있어야하므로)
		curr = curr->next; //다음 노드로 이동하며 word보다 크기가 큰 데이터를 찾음
	}
	if (prev == NULL) { //word가 노드 중 제일 크기가 작은 단어라면 
		addFront(word); //노드 첫번째에 단어를 넣는다
	}
	else {
		addAfter(prev, word);
	}
}

//노드를 출력하는 함수
void printNode() {
	int total = 0;
	for (Node* curr = head; curr != NULL; curr = curr->next) {
		printf("%s: %d\n", curr->data, curr->count);
		total++; //노드의 갯수 출력
	}
	printf("%d\n", total);
}

//파일내 단어 등장빈도가 10보다 낮은 노드 제거
void delNodeUnder(int c) {
	Node* curr = head;
	Node* prev = NULL;
	while(curr != NULL) {
		if (curr->count <= c) { 
			removeAfter(prev); //조건에 일치한 노드를 제외시켰다. prev는 그대로이므로 prev = curr는 해주지 않는다.
			curr = curr->next;
		}
		else {
			prev = curr;
			curr = curr->next;
		}
	}
}

//void descNode() {
//	Node* maxNode = NULL;
//	int max = 0;
//	for(Node *curr = head; curr != NULL; curr = curr->next){ //노드 순회
//		if (curr->count > max) { //count가 제일 큰 노드를 찾는다
//			max = curr->count; 
//			maxNode = curr; 
//		}
//	}
//	
//	printf("%s: %d", maxNode->data, maxNode->count);
//}

//노드 내림차순 정렬
void descNode() {
	Node* curr = head; //넣으려는 노드
	Node* currDesc = headDesc;

	while (currDesc != NULL && (currDesc->count >= curr->count)) { //새로운 리스트 안에 있는 값보다 넣으려는 값이 더 작으면

	}
	if (currDesc == NULL) {
		addNodeFront(curr);
	}
	else {

	}
}

//노드를 맨 앞에 추가
void addNodeFront(Node* node) {
	node->next = headDesc;
	headDesc = node;
}