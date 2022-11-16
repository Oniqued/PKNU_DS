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
bool movable(Case*, Position cur, int dir);
Position startPos(Case*);
void printComp(Case*);

//���� ����
int test_case;
Case *c[MAX_CASES];

int main() {
	read_maze();
	//for (int i = 0; i < test_case; i++) {
	//	search(c[i]); //case[i] component�� ũ�� Ž��
	//	printComp(c[i]); //case[i] component�� ũ�� ���
	//}

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
	fclose(fp);
}

void search(Case *c) {
	int comp_count = 0;
	Position cur; //����ġ
	Stack *s = create(); //��ġ ������ ����� ����
	
	cur = startPos(c); // ������Ʈ�� ������ġ�� ã�´�
	//printf("%d %d\n", cur.x, cur.y);
	while (1) {
		c->maze[cur.x][cur.y] = VISITED; //����ġ �湮 ǥ�÷� ǥ��
		if (NULL) { //���̻� �� ���� ������
			c->component[comp_count++] = s->top + 1;
			break;
		}
		
		bool forwarded = false; // 8���� �� �� ������ �����ϴµ� �����ߴ����� ǥ��
		for (int dir = 0; dir < 8; dir++) {
			if (movable(c, cur, dir)) {
				push(s, cur); //���� ��ġ�� stack�� push
				cur = moveTo(cur, dir); //dir �������� �� ĭ �̵��� ��ġ�� ���ο� cur�� ����
				forwarded = true; //���� ����
				break;
			}
		}
		if (!forwarded) { //8���� �� ��� �����ε� ���� �������� //false�� 
			c->maze[cur.x][cur.y] = BACKTRACKED; //�Դٰ� ��ġ���� ǥ��
			if (isEmpty(s)) {
				printf("No path exists\n");
				break;
			}
			cur = pop(s);
		}
	}
	//printComp();
}

bool movable(Case *c, Position pos, int dir) { //dir �������� �̵��� �� �ִ��� �˻�
	Position tile = moveTo(pos, dir); //dir ���� Ÿ�� �˻�
	if (c->maze[tile.x][tile.y] == BLACK || 
		c->maze[tile.x][tile.y] == VISITED) {
		return true;
	}
	return false;
}

Position startPos(Case *c) { //component ������ ���۵Ǵ� ������ ã�� ���� ��ȯ
	Position start_pos;
	for (int i = 0; i < c->size; i++) {
		for (int j = 0; j < c->size; j++) {
			if (c->maze[i][j] == BLACK) { // BLACK�� ������ �ش� ��ġ�� ���������� ��
				start_pos.x = i;
				start_pos.y = j;

				return start_pos;
			}
		}
	}
}

void printComp(Case* c) {

}