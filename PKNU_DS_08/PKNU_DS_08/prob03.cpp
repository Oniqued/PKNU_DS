#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define BUFFER_SIZE 1000000
#define MAX 100

//����ü 
typedef struct testCase {
	int data[BUFFER_SIZE];
	int huristic;
}Case;

//�Լ� ������Ÿ��
void load();
void allocation(int i);
void search(Case *c, int index);

//���� ���� ����
Case *c[MAX];

int main() {
	clock_t start = clock();
	load();
	clock_t end = clock();
	printf("elapesed time: %lf\n", (double)(end - start)/ CLOCKS_PER_SEC);

	return 0;
}

void load() {
	int test_cases;
	int input_len;
	int input;

	FILE* fp = fopen("sample_input.txt", "r");
	if (fp == NULL) {
		return;
	}

	fscanf(fp, "%d", &test_cases); //�׽�Ʈ ���̽� ���� ��ĵ
	for (int i = 0; i < test_cases; i++) { //�׽�Ʈ ���̽� ���� ��ŭ �ݺ�
		allocation(i); //�޸� �Ҵ�
		fscanf(fp, "%d", &input_len); //�ش� �׽�Ʈ ���̽� data�� ���̴�?
		for (int j = 0; j < input_len; j++) {
			fscanf(fp, "%d", &input); //�������� �� ��ĵ
			search(c[i], input);
			c[i]->data[j] = input; //������ ���� 
			printf("%d ", c[i]->data[j]);
		}
		printf("case: %d, huristic: %d\n", i, c[i]->huristic);
	}
}

void allocation(int i) {
	c[i] = (Case*)malloc(sizeof(Case)); //�׽�Ʈ ���̽� �޸� ���� ����
	c[i]->huristic = 0; //huristic �ʱ�ȭ
}

void search(Case *c, int input) {
	//if(input > )
}