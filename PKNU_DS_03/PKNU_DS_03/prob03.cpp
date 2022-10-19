#define _CRT_NONSTDC_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1000
#define MAX 10000

char buffer[BUFFER_SIZE];
char* words[MAX];
char* exp[MAX];

void load();
void save();

int main() {
	load();
	save();

	return 0;
}

void load() {
	FILE* file = fopen("shuffled_dict.txt", "r");
	if (file == NULL) {
		return;
	}
	int n = 0;
	while (fgets(buffer, BUFFER_SIZE, file) != NULL) {
		if (buffer[strlen(buffer) - 1] == '\n') { //���� �� ���� ����
			buffer[strlen(buffer) - 1] = '\0';
		}

		char* tmp = strtok(buffer, "\t");  //buffer�� �Ǳ������� �ڸ�
		
		//���� ����
		int i = n - 1;
		while (i >= 0 && strcmp(words[i], tmp) > 0) { //�ǵڿ��� ���� ������ ū ���� �ȳ��ö� ���� �ݺ�
			words[i + 1] = words[i]; //������ ũ�� ��ĭ�� �ڷ� �̵�
			exp[i + 1] = exp[i]; //words�� ���� �پ �̵�
			i--;
		}
		//ó������ �� �ݺ��� ���� x �ٷ� words[0]�� �߰�
		//�� ���� ã����
		words[i+1] = strdup(tmp); //���۸� �ڸ� tmp�� words�� ����
		tmp = strtok(NULL, "\t"); //�ڸ� �� NULL���� �����̹Ƿ� NULL���� �ٽ� �ڸ�
		exp[i+1] = strdup(tmp); //�ڸ� tmp�� exp�� ����
		n++;
	}
	fclose(file);
}

void save() {
	FILE* file = fopen("sorted_dict.txt", "w");
	printf("���� ����\n");
	
	for (int i = 0; words[i] != NULL; i++) {
		fprintf(file, "%s : %s\n", words[i], exp[i]);
	}

	
}