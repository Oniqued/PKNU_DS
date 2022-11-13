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
	long huristic;
}Case;

//�Լ� ������Ÿ��
void load();
void allocation(int i);
void init();
void search(int i, int j, int input);
void printHuristic();

//���� ���� ����
int test_cases;
int none_huristic_start;
int prev_huristic_value;
int prev_huristic;
Case *c[MAX];

int main() {
	clock_t start = clock();
	load();
	clock_t end = clock();
	//printHuristic();
	printf("Elapsed Time: %lf\n", (double)(end - start)/ CLOCKS_PER_SEC);

	return 0;
}

void load() {
	int input_len, input;

	FILE* fp = fopen("input.txt", "r");
	if (fp == NULL) {
		return;
	}

	fscanf(fp, "%d", &test_cases); //�׽�Ʈ ���̽� ���� ��ĵ
	for (int i = 0; i < test_cases; i++) { //�׽�Ʈ ���̽� ���� ��ŭ �ݺ�
		allocation(i); //�޸� �Ҵ�
		init();
		fscanf(fp, "%d", &input_len); //�ش� �׽�Ʈ ���̽� data�� ���̴�?
		for (int j = 0; j < input_len; j++) {
			fscanf(fp, "%d", &input); //�������� �� ��ĵ
			search(i, j, input); //�ش� input�� h()��
			c[i]->data[j] = input; //������ ���� 
		}
		printf("%d\n", c[i]->huristic % 1000000);
	}
}

void allocation(int i) {
	c[i] = (Case*)malloc(sizeof(Case)); //�׽�Ʈ ���̽� �޸� ���� ����
	c[i]->huristic = 0; //huristic �ʱ�ȭ
}

void init() {
	none_huristic_start = 0;
	prev_huristic_value = 0;
	prev_huristic = 0;
}

//none_huristic_start = -1
//prev_huristic_value = 1
//prev_huristic = 1

void search(int i, int j, int input) { //1 1 2
	int tmp_h = 0;
	int k = j - 1;
	
	if (prev_huristic != 0 && none_huristic_start < 0) {
		c[i]->huristic += k;
	}
	
	//if (prev_huristic_value != 0 && c[i]->data[k] <= input) {
	//	c[i]->huristic = c[i]->huristic + prev_huristic_value + 1;
	//	for (int p = none_huristic_start; p >= 0; p--) {
	//		if (c[i]->data[p] <= input) {
	//			c[i]->huristic++;
	//		}
	//	}
	//	prev_huristic = j;
	//	prev_huristic_value = c[i]->huristic; //���� �޸���ƽ�� ��
	//	//printf("h(%d) = %d\n", j, c[i]->huristic);
	//	return;
	//}

	for(k = j-1; k >= 0 && k != -1; k--){
		if (c[i]->data[k] <= input) {
			tmp_h++;
		}
		else {
			c[i]->huristic += tmp_h; //h(j) = tmp_h // tmp_h = 1
			none_huristic_start = k; //�޸���ƽ�� ���Ե��� �ʴ� �κ��� �������� // -1
			prev_huristic = j; //1
			if (tmp_h == 0) {
				prev_huristic_value = 0; //���� �޸���ƽ�� ��
			}
			else {
				prev_huristic_value = tmp_h; //���� �޸���ƽ�� ��
			}
			//printf("h(%d) = %d\n", j, c[i]->huristic);
			return;
		}
	}
}

void printHuristic() {
	for (int i = 0; i < test_cases; i++) {
		printf("%d\n", c[i]->huristic % 1000000);
	}
}