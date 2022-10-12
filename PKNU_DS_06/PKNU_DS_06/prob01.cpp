#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS

#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 100
#define DICT_SIZE 9999

void load();

char buffer[BUFFER_SIZE];
char dict[DICT_SIZE];

struct NODE {
	char* word;
	int count;
	struct NODE* next;
};
typedef struct NODE Node;
Node* head = NULL;

int main(void) {
	load();
	return 0;
}

void load() {
	FILE* file = fopen("harry.txt", "r");
	if (file == NULL) {
		printf("ERROR! FAILED TO OPEN FILE\n");
		return;
	}
	else {
		//�ϴ� �� �а� ���� ���� ���� �ܾ �̹� �ִ� �ܾ�� +1 �ϴ� ���� 
		while (fscanf(file, "%s", buffer) != EOF) {
			//��� ���� �ܾ� buffer�� �̹� ���Ḯ��Ʈ�� �ִ��� �˻�
			Node* p = head;
			while (p != NULL) {
				strcmp(p->word, buffer) == 0 ??
					p = p->next;
			}
			if (p != NULL) p->count++;
			else {
				Node* t = ()malloc();
				t->word = strdup(buffer); t->count = 1; t->next = NULL;
				//malloc���� ��带 ���� �����, �ű⿡ �ܾ �����ϰ�, ī��Ʈ�� 1��
				//���� ��带 head�� ����Ű�� ���Ḯ��Ʈ�� insert
				addFirst(t);
			}
		}
	}
}