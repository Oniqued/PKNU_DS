//�׽�Ʈ ��� ������ ��� ����
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS

#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1000

//���� �Լ�
void load_file();
void tok_line(char* index[]);
void compress(char str[]);
void prettier();
void save_file();

//���� ���� ����
int m, n; //��, ���� ����
char buffer[BUFFER_SIZE];
char* index[BUFFER_SIZE];
char* output[BUFFER_SIZE][BUFFER_SIZE];
int space[BUFFER_SIZE][BUFFER_SIZE]; //�� output�� �߰��� ������ ���̸� �����ϴ� �迭

int main() {
	load_file();
	prettier();
	save_file();

	return 0;
}

//������ �д� �Լ�
void load_file() {
	FILE* table = fopen("table.txt", "r");
	if (table == NULL) {
		printf("���� ���� ����");
		return;
	}
	else {
		fscanf(table, "%d %d ", &m, &n);
		//read_line

		int i = 0;
		while (fgets(buffer, BUFFER_SIZE, table) != NULL) { //���� ������ �д´�
			compress(buffer); //�ߺ� ����, ���� ����
			index[i++] = strdup(buffer); //�� ���� ����index�� ����
		}
		tok_line(index); //index�� &�������� �߶� output�迭�� �� ��ü�� ����
	}
}

//& �������� �߶� ����
void tok_line(char* index[]) {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (j == 0) {
				output[i][j] = strtok(index[i], "&");
			}
			else {
				output[i][j] = strtok(NULL, "&");
			}
		}
	}
}

//������ ���� ���� �� ���� ����
void compress(char str[]) {
	//���� ���� ���� ����(\n����)
	for (int i = 0; i < strlen(str); i++) {
		if (buffer[i] == '\n') {
			buffer[i] = NULL;
		}
	}
	//�ߺ� ���� ����
	int n = 0;
	char tmp[BUFFER_SIZE];
	for (int i = 0; i < strlen(str); i++) {
		if (str[i] == ' ' && str[i + 1] == ' ') { //����, ���� �ε����� �����̸� ���� �ϳ��� ���... �ݺ�
			continue;
		}
		tmp[n++] = str[i];
	}
	tmp[n] = 0; //���� NULL �߰�
	strcpy(str, tmp); //str�� tmp�� �����Ѵ�
}

//����ϰ� ��µǱ� ���� ���� �߰�
void prettier() {
	int max;
	for (int i = 0; i < m; i++) {
		max = 0;
		//�� �࿡�� ���̰� ���� �� �ܾ��� ���̸� ã�´�
		for (int j = 0; j < n; j++) {
			if (strlen(output[j][i]) > max) {
				max = strlen(output[j][i]);
			}
		}
		//space�迭�� output�� �߰��� ������ ���̸� �����Ѵ�
		for (int j = 0; j < n; j++) {
			space[j][i] = (max - strlen(output[j][i]));
		}
	}
}

//���� ����
void save_file() {
	FILE* fp = fopen("output.txt", "w");

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			fprintf(fp, "%s", output[i][j]);
			for (int k = 0; k < space[i][j]; k++) {
				fprintf(fp, " ");
			}
		}
		fprintf(fp, "\n");
	}
	printf("output.txt ���� �Ϸ�\n");
}