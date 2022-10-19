//�׽�Ʈ ��� ������ ��� ����
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
void addNodeDesc(Node* node);
void addNodeFront(Node* node);
void addNodeAfter(Node* prev, Node* node);
void printDescNode();


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

	printf("[����1] ���� �� ��� �ܾ� & �󵵼� ���\n");
	printNode();
	printf("\n\n------------------------------------------\n");
	
	printf("[����2] �ܾ� ���� �󵵰� 10���� ���� �ܾ ���\n");
	delNodeUnder(10);
	printNode();
	printf("\n\n------------------------------------------\n");
	
	printf("[����3] �ܾ� ���� �󵵰� 10���� ���� �ܾ �������� ���\n");
	
	while (head != NULL) {
		addNodeDesc(head);
	}
	printDescNode();
	return 0;
}

//�����͸� �� �տ� ������, 1. ���ο� ��� ���� 2. ������ ����� next�� ���� ���� ���� 3. �Ǿտ� ����
void addFront(char* word) {
	Node* tmp = (Node*)malloc(sizeof(Node));
	tmp->data = word; // �ּ� ����
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
	if (prev == NULL) {
		head = head->next;
	}
	else { //���� ��带 �����ߴ�. ���� ���� �״�� prev�� �ȴ� (���� ��带 �����ϸ� ���� ���� ���� �����Ƿ� ���� ���� �״�� �д�)
		prev->next = tmp->next; //(prev->next = (prev->next)->next;
	}
}

//������ ������ �°� ������ ������ ����
void addAccord(char* word) {
	Node* curr = head; //curr�� ù��° ��带 ����Ŵ
	Node* prev = NULL; //prev�� curr����� �� ��带 ����Ŵ (��忡 �����͸� �����Ϸ��� ���� ����� �ּҸ� �˰��־���ϹǷ�)
	while (curr != NULL && strcmp(curr->data, word) <= 0) { //curr�� NULL�� �ƴϸ� word�� prev.data ���� ũ�ų� ���ٸ� ���� ���� �̵�
		if (strcmp(curr->data, word) == 0){
			curr->count++;
			return;
		}
		prev = curr; //pre�� cur�� ���� (prev�� curr-1��° ���) (��忡 �����͸� �����Ϸ��� ���� ����� �ּҸ� �˰��־���ϹǷ�)
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
			removeAfter(prev); //���ǿ� ��ġ�� ��带 ���ܽ��״�. 
			//�� �Լ��� ������ �Ŀ��� 
			//prev�� �״���̹Ƿ� prev = curr�� ������ �ʴ´�.
			curr = curr->next; //������ ����� ���� ��带 ����Ű�� �����͸�  �ű�� �۾� 
		}
		else {
			prev = curr;
			curr = curr->next;
		}
		//curr = curr->next;
	}
}

//��� �������� ����
void addNodeDesc(Node* node) {
	Node* currDesc = headDesc; 
	Node* prevDesc = NULL;	
	while (currDesc != NULL && (currDesc->count >= node->count)) { //curr�� �� ��ġ ã�� >> ���� Desc��庸�� �������� ���� ���� ���� �ݺ�
		if (currDesc->count == node->count) { //�������� ����� count�� ���� ���ϴ� ����� count�� ���ٸ� (�ƴϸ� �׳� else��)
			if (strcmp(currDesc->data, node->data) < 0) { //�������� ����� �ܾ ���� ���ϴ� ����� �ܾ ���Ѵ�.
				//�������� �ܾ �� ũ�� �ڿ��ٰ� �־���ϹǷ�..
				prevDesc = currDesc; 
				currDesc = currDesc->next; //���� �� ���� ����Ű�� �Ѵ� (���� ������ else�� �̵�)
			}
		}
		else {
			prevDesc = currDesc;
			currDesc = currDesc->next;
		}
	}
	if (prevDesc == NULL) {
		addNodeFront(node);
	}
	else { //���� ��� ������ �������� ��带 �ִ´�
		addNodeAfter(prevDesc, node);
	}
}

//��带 �� �տ� �߰�
void addNodeFront(Node* node) {
	Node* tmp = (Node*)malloc(sizeof(Node)); //���� ���� �ӽó�� ���� 
	tmp = head; //�ӽó�忡 ��� ��� ���� 
	head = head->next; //�׸��� ��� ����� �պκ��� �����, ��� ���� �κ��� ��尡 �ǰ� �Ѵ� (�ٵ��)
	tmp->next = headDesc; //���� �ӽó���� ����(������ ����� ���� ��尡 �־���)�� headDesc�� ������ ���δ�
	//[tmp] - [headDesc] ���� 
	headDesc = tmp; //���������� headDesc�� ���� ���� tmp�� �ȴ� (tmp->next���� ������ �ִ� headDesc�� ������) [headDesc]
}

//prev ������ ��� �߰�
void addNodeAfter(Node* prev, Node* node) {
	if (prev == NULL) {
		return;
	}
	Node* tmp = (Node*)malloc(sizeof(Node));
	tmp = head;
	head = head->next;
	tmp->next = prev->next;
	prev->next = tmp;
}

//�������� ��� ���
void printDescNode() {
	int total = 0;
	for (Node* node = headDesc; node != NULL; node = node->next) {
		printf("%s: %d\n", node->data, node->count);
		total++;
	}
	printf("%d\n", total);
}