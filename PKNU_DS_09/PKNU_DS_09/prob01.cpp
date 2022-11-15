//�׽�Ʈ ��� ������ ��� ����
#define _CRT_SECURE_NO_WARNINGS

#include "pos.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_CASES 10
#define MAX 50

//�̷� ����
#define WHITE 0 //������ �� ���� ��ġ
#define BLACK 1 //������ �� �ִ� ��ġ 
#define VISITED 2 //�̹� �湮�� ��ġ
#define BACKTRACKED 3 //�湮�ߴٰ� �ǵ��� ���� ��ġ

//����ü 
typedef struct testCase {
	int size;
	int component[MAX];
	int maze[MAX][MAX];
}Case;

//�Լ�
void createCase(int test_case);
void read_maze();
void search(Case*);
void printComp(Case*);

//���� ����
int test_case;
Case *c[MAX_CASES];

int main() {
	read_maze();
	for (int i = 0; i < test_case; i++) {
		search(c[i]); //case[i] component�� ũ�� Ž��
		printComp(c[i]); //case[i] component�� ũ�� ���
	}
	
	/* //�̷� ��� �׽�Ʈ
	for (int i = 0; i < test_case; i++) {
		for (int j = 0; j < c[i]->size; j++) {
			for (int k = 0; k < c[i]->size; k++) {
				printf("%d ", c[i]->maze[j][k]);
			}
			printf("\n");
		}
	}*/

	return 0;
}

void createCase(int test_case) {
	c[test_case] = (Case *)malloc(sizeof(Case));
}

void read_maze() {
	int N, index;
	FILE* fp = fopen("input.txt", "r");
	if (fp == NULL) {
		return;
	}

	fscanf(fp, "%d", &test_case); //�� ���� case�� �ִ���
	for (int i = 0; i < test_case; i++) {
		createCase(i); //case�� ����� ���� �Ҵ�

		fscanf(fp, "%d", &N); //�ش� case�� maze ũ��� 
		c[i]->size = N; 
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < N; k++) {
				fscanf(fp, "%d", &index); 
				c[i]->maze[j][k] = index;
			}
		}
	}
	printf("Load Completed\n");
	fclose(fp);
}

void search(Case *c) {
	Position cur; //����ġ
	Stack s = create(); //��ġ ������ ����� ����
	
	
	
}

void startPos(Case *c) {
	
}