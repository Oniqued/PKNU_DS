#include "stack.h"

#define MAX 100

void load();
int search(Case c);

int test_cases;
Case c[MAX];

int main() {
	load();
	/*for (int i = 0; i < test_cases; i++) {
		printf("%d\n", search(c[i]));
	}*/
	
	/*for (int i = 0; i < test_cases; i++) {
		for (int j = 0; j < c[i]->top; j++) {
			printf("%d ", c[i]->stack[j]);
		}
	}*/

	return 0;
}

void load() {
	int index_amt;
	int index;
	FILE* fp = fopen("sample_input.txt", "r");
	if (fp == NULL) {
		return;
	}

	fscanf(fp, "%d", &test_cases); //�׽�Ʈ ���̽� ���� ��ĵ
	for (int i = 0; i < test_cases; i++) { //�׽�Ʈ ���̽� ���� ��ŭ �ݺ�
		create(); //�׽�Ʈ ���̽� ����
		fscanf(fp, "%d", &index_amt); //�ش� �׽�Ʈ ���̽� stack�� ���̴�?
		c[i]->top = index_amt - 1; //c[i]->stack�� top �ʱ�ȭ
		for (int j = 0; j <= c[i]->top; j++) {
			fscanf(fp, "%d", &index); //�������� �� ��ĵ
			push(c[i], index); //��ĵ �� �� ���ʷ� stack�� ����
		}
	}
}

int search(Case c) {
	int count = 0;
	for (c->top; c->top >= 0; c->top--) {
		for (int i = c->top - 1; i >= 0; i--) {
			if (c->top >= i) {
				count++;
			}
		}
	}
	return count;
}