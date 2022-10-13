#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 100

//��� ����ü 
struct NODE {
	char *data; //����� ������
	int count; //�ش� �ܾ��� ���� Ƚ���� ������ ���� 
	struct NODE* next; //�ش� ����� ���� ������ ����Ų��
};
typedef struct NODE Node; //NODE Ÿ���� ���� Node�� ����
Node* head = NULL; //ù ��� (ù ��带 �Ҿ������ �ʵ��� ���������� ����)
Node* headDesc = NULL;

//���� �Լ�
void addFront(char* word);
void removeFront();
void addAccord(char* word);
void addAfter(Node* prev, char* word);
void removeAfter(Node* prev);
void printNode();
void delNodeUnder(int c);
void descNode();


int main() {
	char buffer[BUFFER_SIZE]; //���Ͽ��� �о���� �ܾ �ӽ÷� ������ ����

	FILE* file = fopen("harry.txt", "r");
	if (file == NULL) {
		printf("ERROR! FAILED TO OPEN FILE\n");
		return 0;
	}
		
	while (fscanf(file, "%s", buffer) != EOF) {
		addAccord(strdup(buffer));
	}
	fclose(file);

	//printf("[����1] ���� �� ��� �ܾ� & �󵵼� ���\n");
	//printNode();
	//printf("------------------------------------------\n\n");
	//printf("[����2] �ܾ� ���� �󵵰� 10���� ���� �ܾ ���\n");
	//delNodeUnder(10);
	//printNode();
	descNode();

	return 0;
}

//�����͸� �� �տ� ������, 1. ���ο� ��� ���� 2. ������ ����� next�� ���� ���� ���� 3. �Ǿտ� ����
void addFront(char* word) {
	Node* tmp = (Node*)malloc(sizeof(Node));
	tmp->data = word; // strcpy no, �ּ� ����
	tmp->count = 1; //�ܾ ���� �������Ƿ� count = 1
	tmp->next = head; //���ο� ����� next�� ù ��忴�� ���� �ٲ۴� (���� ���࿡�� ù ��忡 NULL ����Ǿ�����)
	head = tmp; //���� ���� ���� tmp�� �ȴ� >> ���۳�� ���� ��, Node[0] : data = word, next = NULL
}

//�Ǿ� ��带 ����
void removeFront() {
	head = head->next; //�� �ճ�带 �����Ϸ��� ���� head�� ���� ���� �ٲ��ָ� �ȴ�.
	//free?
}

//�ش� ��� �տ� ��带 �߰��ϴ� �Լ�
void addAfter(Node* prev, char* word) {
	if (prev == NULL) {
		return;
	}
	//�ش� ��� �տ� �������� ���ο� Node�� �ϳ� ����� ���ο� ��忡 �����͸� �ִ´�. 
	//�׸��� ���ο� ���� ���� ��带 �������ְ� ���� ���� ���ο� ���� �����Ѵ�.
	Node* tmp = (Node*)malloc(sizeof(Node));
	tmp->data = word;
	tmp->count = 1; //�ܾ �߰��Ǿ����Ƿ� count = 1
	tmp->next = prev->next;
	prev->next = tmp;
}

//�ش� ����� ���� ��带 �����ϴ� �Լ�
void removeAfter(Node* prev) { //���� ��尡 NULL�̸� �������� ���� head�ΰ��̹Ƿ� head�� ������ ����������Ѵ�.
	Node* tmp = prev->next; //���� ���
	if (tmp == NULL) {
		return;
	}
	else { //���� ��带 �����ߴ�. ���� ���� �״�� prev�� �ȴ�
		prev->next = tmp->next;
	}
}

//������ ������ �°� ������ ������ ����
void addAccord(char* word) {
	Node* curr = head; //cur�� ù��° ��带 ����Ŵ
	Node* prev = NULL; //pre�� cur����� �� ��带 ����Ŵ (��忡 �����͸� �����Ϸ��� ���� ����� �ּҸ� �˰��־���ϹǷ�)
	while (curr != NULL && strcmp(curr->data, word) <= 0) { //cur�� NULL�� �ƴϸ� word�� pre.data ���� ũ�ų� ���ٸ� ���� ���� �̵�
		if (strcmp(curr->data, word) == 0){
			curr->count++;
			return;
		}
		prev = curr; //pre�� cur�� ���� (pre�� cur-1��° ���) (��忡 �����͸� �����Ϸ��� ���� ����� �ּҸ� �˰��־���ϹǷ�)
		curr = curr->next; //���� ���� �̵��ϸ� word���� ũ�Ⱑ ū �����͸� ã��
	}
	if (prev == NULL) { //word�� ��� �� ���� ũ�Ⱑ ���� �ܾ��� 
		addFront(word); //��� ù��°�� �ܾ �ִ´�
	}
	else {
		addAfter(prev, word);
	}
}

//��带 ����ϴ� �Լ�
void printNode() {
	int total = 0;
	for (Node* curr = head; curr != NULL; curr = curr->next) {
		printf("%s: %d\n", curr->data, curr->count);
		total++; //����� ���� ���
	}
	printf("%d\n", total);
}

//���ϳ� �ܾ� ����󵵰� 10���� ���� ��� ����
void delNodeUnder(int c) {
	Node* curr = head;
	Node* prev = NULL;
	while(curr != NULL) {
		if (curr->count <= c) { 
			removeAfter(prev); //���ǿ� ��ġ�� ��带 ���ܽ��״�. prev�� �״���̹Ƿ� prev = curr�� ������ �ʴ´�.
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
//	for(Node *curr = head; curr != NULL; curr = curr->next){ //��� ��ȸ
//		if (curr->count > max) { //count�� ���� ū ��带 ã�´�
//			max = curr->count; 
//			maxNode = curr; 
//		}
//	}
//	
//	printf("%s: %d", maxNode->data, maxNode->count);
//}

//��� �������� ����
void descNode() {
	Node* curr = head; //�������� ���
	Node* currDesc = headDesc;

	while (currDesc != NULL && (currDesc->count >= curr->count)) { //���ο� ����Ʈ �ȿ� �ִ� ������ �������� ���� �� ������

	}
	if (currDesc == NULL) {
		addNodeFront(curr);
	}
	else {

	}
}

//��带 �� �տ� �߰�
void addNodeFront(Node* node) {
	node->next = headDesc;
	headDesc = node;
}