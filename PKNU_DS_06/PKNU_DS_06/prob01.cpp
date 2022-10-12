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
		//일단 다 읽고 넣지 말고 넣은 단어가 이미 있는 단어면 +1 하는 로직 
		while (fscanf(file, "%s", buffer) != EOF) {
			//방금 읽은 단어 buffer가 이미 연결리스트에 있는지 검사
			Node* p = head;
			while (p != NULL) {
				strcmp(p->word, buffer) == 0 ??
					p = p->next;
			}
			if (p != NULL) p->count++;
			else {
				Node* t = ()malloc();
				t->word = strdup(buffer); t->count = 1; t->next = NULL;
				//malloc으로 노드를 새로 만들고, 거기에 단어를 저장하고, 카운트는 1로
				//만든 노드를 head가 가리키는 연결리스트에 insert
				addFirst(t);
			}
		}
	}
}