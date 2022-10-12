#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 100

char buffer[BUFFER_SIZE];
//��� ����ü 
struct NODE {
	char* data;
	int count = 0;
	struct NODE* next;
}; 
typedef struct NODE Node; //NODE Ÿ���� ���� Node�� ����
Node* head = NULL; //ù ��� (ù ��带 �Ҿ������ �ʵ��� ���������� ����)

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

//�����͸� �� �տ� ������, 1. ���ο� ��� ���� 2. ������ ����� next�� ���� ���� ���� 3. �Ǿտ� ����
void addFront(char* word) {
	Node* tmp = (Node*)malloc(sizeof(Node));
	tmp->data = word;
	tmp->next = head; //���ο� ����� next�� ù ��忴�� ���� �ٲ۴� (���� ���࿡�� ù ��忡 NULL ����Ǿ�����)
	head = tmp; //���� ���� ���� tmp�� �ȴ� >> ���۳�� ���� ��, Node[0] : data = word, next = NULL
}

//������ ������ �°� ������ ������ ����
void addAccord(char* word) {
	Node* p = head; //p�� ù��° ��带 ����Ŵ
	Node* q = NULL; //q�� p����� �� ��带 ����Ŵ
	while(p != NULL && strcmp(p->data, word)) { //p�� NULL�� �ƴϸ� word�� p.data ���� ũ�ų� ���ٸ� ���� ���� �̵�
		
	}

}