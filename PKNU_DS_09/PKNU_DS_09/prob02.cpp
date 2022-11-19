//테스트 결과 데이터 출력 성공
#define _CRT_SECURE_NO_WARNINGS

#include "pos.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_CASES 10
#define MAX 50

//미로 정보
#define WHITE 0 //지나갈 수 없는 위치
#define BLACK 1 //지나갈 수 있는 위치 
#define VISITED 2 //이미 방문한 위치

//구조체 
typedef struct testCase {
	int comp_count, size;
	int component[MAX];
	int maze[MAX][MAX];
}Case;

//함수
void createCase(int test_case);
void read_maze();
bool movable(Case*, Position cur, int dir);
void search(Case*);
Position startPos(Case*);
void printComp(Case*);

//전역 변수
int test_case;
Case* c[MAX_CASES];
Queue* q;

int main() {
	read_maze();
	q = create(); //Queue 생성
	for (int i = 0; i < test_case; i++) {
		search(c[i]); //case[i] component 탐색
		printComp(c[i]); //case[i] component의 크기 출력
	}

	//미로 출력 테스트
	/*for (int i = 0; i < test_case; i++) {
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
	c[test_case] = (Case*)malloc(sizeof(Case));
	c[test_case]->comp_count = 0;
}

void read_maze() {
	int N, index;
	FILE* fp = fopen("input.txt", "r");
	if (fp == NULL) {
		return;
	}

	fscanf(fp, "%d", &test_case); //몇 개의 case가 있는지
	for (int i = 0; i < test_case; i++) {
		createCase(i); //case가 저장될 공간 할당

		fscanf(fp, "%d", &N); //해당 case의 maze 크기는 
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

void search(Case* c) {
	Position cur;
	while (1) { //해당 Case에 찾을 component가 더이상 없을 때까지 무한 반복 
		cur = startPos(c); //해당 Case의 component 시작지점을 찾는다
		if (cur.x == -1 && cur.y == -1) { // 더 이상 찾을 시작지점이 없으면 종료
			break;
		}
		enqueue(q, cur); //Que에 현재 좌표를 저장
		c->maze[cur.x][cur.y] = -1; //얼마나 이동했는지를 음수로 표기 >> 한 칸씩 탐색 할 때마다 -1 
		while(!isEmpty(q)) { //Que에 값이 없을 때 까지 해당 component를 탐색(component 탐색 종료 조건)
			cur = dequeue(q); //Que에서 좌표를 가져온다
			for (int dir = 0; dir < 8; dir++) { //해당 지점에서 이동이 가능한 좌표를 찾는다 
				if (movable(c, cur, dir)) { // 현위치에서 해당 방향으로 이동이 가능하면
					Position p = moveTo(cur, dir); 
					c->maze[p.x][p.y] = c->maze[cur.x][cur.y] - 1; //p지점에 방문표시를 한다
					enqueue(q, p); //Que에 방문한 좌표를 저장한다 
				}
			}
		}
		c->component[c->comp_count++] = q->comp_size; //Que에 기록된 size를 각 component별 저장
		make_empty(q); //사용한 Que 초기화 
	}
	
}

bool movable(Case* c, Position pos, int dir) { //dir 방향으로 이동할 수 있는지 검사
	Position tile = moveTo(pos, dir); //dir 방향 타일 검사
	if (c->maze[tile.x][tile.y] == BLACK) { // BLACK일 때만 ? 
		return true;
	}
	return false;
}

Position startPos(Case* c) { //component 영역이 시작되는 지점을 찾아 값을 반환
	Position start_pos;
	start_pos.x = -1;
	start_pos.y = -1;
	for (int i = 0; i < c->size; i++) {
		for (int j = 0; j < c->size; j++) {
			if (c->maze[i][j] == BLACK) { // BLACK을 만나면 해당 위치가 시작지점이 됨
				start_pos.x = i;
				start_pos.y = j;

				return start_pos;
			}
		}
	}

	return start_pos;
}

void printComp(Case* c) {
	for (int i = 0; i < c->comp_count; i++) {
		printf("%d ", c->component[i]);
	}
	printf("\n");
}
