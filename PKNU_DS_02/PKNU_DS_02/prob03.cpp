#define _CRT_NONSTDC_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#define BUFFER_SIZE 256
#define WORDS_AMOUNT 5000

//���� ���� ����
FILE* harry;
char buffer[BUFFER_SIZE];
char* words[WORDS_AMOUNT];
int words_check[WORDS_AMOUNT];
int count;

//�޼��� ����
void read_file();
int search_word_limit(int limit);
void sort(char* words[]);
void del_dup(char* words[]);

int main(void) {
	read_file();
	search_word_limit(6);
	sort(words);
	del_dup(words);

	for (int i = 0; i < count; i++) {
		printf("%s: %d\n", words[i], words_check[i]);
	}
	printf("%d\n", count);

	return 0;
}

//���� ����
void read_file() {
	harry = fopen("harry.txt", "r");
	if (harry == NULL) {
		printf("���� ���⿡ �����߽��ϴ�.\n���α׷��� �����մϴ�.");
		return;
	}
	else {
		printf("������ �������ϴ�.\n");
	}
}

//���̰� 6�̻��� �ܾ�鸸 ����
int search_word_limit(int limit) {
	int i = 0;
	while (fscanf(harry, "%s", buffer) != EOF) {
		if (strlen(buffer) >= limit) { //�ܾ��� ���̰� limit�̻��϶��� �ܾ� ����
			words[i++] = strdup(buffer);
		}
	}
	count = i;

	return count;
}

//�ܾ� ���� �˰��� :: Bubble Sort
void sort(char* words[]) {
	for (int i = 0; i < count; i++) {
		for (int j = i + 1; j < count; j++) {
			if (strcmp(words[i], words[j]) > 0) {
				char* tmp = words[i];
				words[i] = words[j];
				words[j] = tmp;
			}
		}
	}
}

//�ܾ� �ߺ� ���� �˰��� 
//:: �ߺ��� �����ϰ� �ش� �ܾ��� ����Ƚ���� check�� ���� �����Ѵ�
void del_dup(char* words[]) {
	int j = 0;
	for (int i = 0; i < count; i++) {
		if (i == 0 || strcmp(words[i], words[i - 1]) > 0) {
			words[j] = words[i];
			words_check[j] = words_check[j] + 1; //���� �ܾ� ���� Ƚ�� + 1
			j++;
		}
		else{ //�� ������ ��ġ ���� ������ �ߺ��� ���� ���� ���̹Ƿ� check + 1
			words_check[j-1] = words_check[j - 1] + 1;
		}
	}
	count = j; //�ߺ��� ������ �迭 words[j]�� �縸ŭ count�� ����
}