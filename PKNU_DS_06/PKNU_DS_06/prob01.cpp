#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 100

//��� ����ü 
struct NODE {
	char data[BUFFER_SIZE]; //����� ������
	int count = 0; //�ش� �ܾ��� ���� Ƚ���� ������ ���� 
	struct NODE* next; //�ش� ����� ���� ������ ����Ų��
}; 
typedef struct NODE Node; //NODE Ÿ���� ���� Node�� ����

//���� ���� ����
int total = 0; //��ü �ܾ� ���� Ƚ���� ������ ����

//���� �Լ�
void addFront(char *word);
void addAccord(char *word);
void addAfter(Node* prev, char *word);

Node* head = NULL; //ù ��� (ù ��带 �Ҿ������ �ʵ��� ���������� ����)

int main() {
	char buffer[BUFFER_SIZE]; //���Ͽ��� �о���� �ܾ �ӽ÷� ������ ����

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

//�����͸� �� �տ� ������, 1. ���ο� ��� ���� 2. ������ ����� next�� ���� ���� ���� 3. �Ǿտ� ����
void addFront(char *word) {
	Node* tmp = (Node*)malloc(sizeof(Node));
	strcpy(tmp->data, word);
	tmp->count++; //�ܾ �߰��Ǿ����Ƿ� count ����
	total++;
	tmp->next = head; //���ο� ����� next�� ù ��忴�� ���� �ٲ۴� (���� ���࿡�� ù ��忡 NULL ����Ǿ�����)
	head = tmp; //���� ���� ���� tmp�� �ȴ� >> ���۳�� ���� ��, Node[0] : data = word, next = NULL
}

//�ش� ��� �տ� ��带 �߰��ϴ� �Լ�
void addAfter(Node* prev, char *word) {
	if (prev == NULL) { //�ش� ��尡 ù��° ���� addFront�� �����Ѵ�.
		addFront(word);
		return;
	}
	//�ش� ��� �տ� �������� ���ο� Node�� �ϳ� ����� ���ο� ��忡 �����͸� �ִ´�. 
	//�׸��� ���ο� ���� ���� ��带 �������ְ� ���� ���� ���ο� ���� �����Ѵ�.
	Node* tmp = (Node*)malloc(sizeof(Node));
	strcpy(tmp->data, word);
	tmp->count++; //�ܾ �߰��Ǿ����Ƿ� count����
	total++;
	tmp->next = prev->next;
	prev->next = tmp;
}

//������ ������ �°� ������ ������ ����
void addAccord(char *word) {
	Node* curr = head; //cur�� ù��° ��带 ����Ŵ
	Node* prev = NULL; //pre�� cur����� �� ��带 ����Ŵ (��忡 �����͸� �����Ϸ��� ���� ����� �ּҸ� �˰��־���ϹǷ�)
	while(curr != NULL && strcmp(curr->data, word) <= 0) { //cur�� NULL�� �ƴϸ� word�� pre.data ���� ũ�ų� ���ٸ� ���� ���� �̵�
		prev = curr; //pre�� cur�� ���� (pre�� cur-1��° ���) (��忡 �����͸� �����Ϸ��� ���� ����� �ּҸ� �˰��־���ϹǷ�)
		curr = curr->next; //���� ���� �̵��ϸ� word���� ũ�Ⱑ ū �����͸� ã��
	}
	if (prev == NULL) { //word�� ��� �� ���� ũ�Ⱑ ���� �ܾ��� 
		addFront(word); //��� ù��°�� �ܾ �ִ´�
		return;
	}
	if (strcmp(curr->data, word) == 0) {
		curr->count++; //�ܾ �߰��Ǿ����Ƿ� count ����
		total++;
		return;
	}
	addAfter(prev, word);
}