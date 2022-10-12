//�׽�Ʈ ��� ������ ��� ����
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER_SIZE 1024
#define WORDS_SIZE 9999

//���� �޼���
void open_file();
void read_file();
void sort();
void save_file();

//���� ��������
FILE* file;
int n;
char buffer[BUFFER_SIZE]; //�ӽ� ���� ����
char* words[WORDS_SIZE]; //�ܾ ����� ����
char* dict[WORDS_SIZE]; //���� �� ��

int main(void) {
	open_file();
	read_file();
	sort();
	save_file();

	return 0;
}

//������ ���� �޼���
void open_file() {
	file = fopen("shuffled_dict.txt", "r");
	if (file == NULL) {
		printf("���� ���� ����\n");
	}
	else {
		printf("���� ���� ����\n");
	}
}

//������ ���� �д� �޼���
void read_file() {
	n = 0;
	while (fgets(buffer, BUFFER_SIZE, file) != NULL) {
		dict[n] = strdup(buffer);
		for (int i = 0; i < BUFFER_SIZE; i++) {
			//�� �� �� ������ '��'�� ������ '��'������ ���ڱ����� words�� �����Ѵ�
			if (buffer[i] == '\t') {
				buffer[i] = '\0';
				words[n] = strdup(buffer);
			}
		}
		//printf("[%d]%s", n, dict[n]);
		n++;
	}
}

//���� �˰��� �ð� ���⵵ O(n^2)
void sort() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < (n -i) -1; j++) {
			if (strcmp(words[j], words[j + 1]) > 0) {
				char* tmp = words[j];
				words[j] = words[j + 1];
				words[j + 1] = tmp;

				//words�� ������ ������ �°� dict�� �����Ѵ�
				tmp = dict[j];
				dict[j] = dict[j + 1];
				dict[j + 1] = tmp;
			}
		}
	}
}

//������ �����ϴ� �޼��� 
void save_file() {
	FILE* s_file = fopen("sorted_dict.txt", "w");
	printf("������ �������Դϴ�...\n");
	//���ĵ� dict�� ���� �� �о�ͼ� ����
	for (int i = 0; i < n; i++) { 
		fputs(dict[i], s_file);
	}
	printf("sorted_dict.txt ���� �Ϸ�!");
}