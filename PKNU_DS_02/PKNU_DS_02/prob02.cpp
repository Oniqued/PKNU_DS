#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#define BUFFER_SIZE 256

//�޼��� ����
void open_file();
int add(int n, char* words[]);
void sort(char* words[]);
int del_dup(char* words[]);

//����� ���� ����
char buffer[BUFFER_SIZE];
char search[100];
int search_len, count, unique;
char* words[BUFFER_SIZE];

int main(void) {
	printf("ã�� �ܾ� �Է�: ");
	scanf("%s", search);
	search_len = strlen(search);
	
	open_file(); //���� �а� ������ �ܾ� ���·� ����
	sort(words); //����
	del_dup(words); //�ߺ� ���� 

	//�ش� �ܾ� ���
	for (int i = 0; i < unique; i++) {
		printf("%s\n", words[i]);
	}
	printf("%d", unique); //�ߺ��� �� �ܾ� ���� ��� 
	
	return 0;
}

void open_file() {
	int n = 0;
	FILE* harry = fopen("harry.txt", "r");
	if (harry == NULL) {
		printf("������ �����ϴ�.");
		return;
	}
	else {
		printf("������ ���������� �ε��߽��ϴ�.\n");
		while (fscanf(harry, "%s", buffer) != EOF) { //�ܾ�� �߶� buffer�� ����
			if (strncmp(buffer, search, search_len) == 0) { //buffer�� search�� �����ϴ� �ܾ����� Ȯ��
				add(n, words); //���ǿ� ��ġ �ϸ� �迭�� �߰� 
				n++;
			}
		}
	}
}

//words�� �ܾ� �߰� 
int add(int n, char* words[]) {
	words[n] = strdup(buffer); //������ ������ words�� ����
	count = n; //��� �ܾ �ִ��� ���
	return count;
}

//���� �˰��� 
void sort(char* words[]) { 
	for (int i = 0; i <= count; i++) {
		for (int j = i + 1; j <= count; j++) {
			if (strcmp(words[i], words[j]) > 0) {
				char* tmp = words[i];
				words[i] = words[j];
				words[j] = tmp;
			}
		}
	}
}

//�ߺ� ���� �˰��� 
int del_dup(char* words[]) {
	int j = 0;
	for (int i = 0; i <= count; i++) {
		if (i == 0 || strcmp(words[i], words[i - 1]) > 0) {
			words[j++] = words[i];
		}
	}
	unique = j; //�ߺ��� ������ �迭������ ����

	return unique;
}