//테스트 결과 데이터 출력 성공
#define _CRT_SECURE_NO_WARNINGS

#include "pos.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_CASES 10
#define MAX 50

//미로 정보
#define WHITE 0 //지나갈 수 없는 위치
#define BLACK 1 //지나갈 수 있는 위치 
#define VISITED 2 //이미 방문한 위치
#define BACKTRACKED 3 //방문했다가 되돌아 나온 위치

//구조체 
typedef struct testCase {
	int comp_count, size;
	int component[MAX];
	int maze[MAX][MAX];
}Case;

//함수
void createCase(int test_case);
void read_maze();
void search(Case*);
bool movable(Case*, Position cur, int dir);
Position startPos(Case*);
void printComp(Case*);

//전역 변수
int test_case;
Case *c[MAX_CASES];

int main() {
	read_maze();
	for (int i = 0; i < test_case; i++) {
		search(c[i]); //case[i] component 탐색
		printComp(c[i]); //case[i] component의 크기 출력
	}

	/* //미로 출력 테스트
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

void search(Case *c) {
	Position cur; //현위치
	Stack *s = create(); //위치 정보가 저장될 스택 생성 및 초기화
	while (1) { 
		cur = startPos(c); // 컴포넌트의 시작위치를 찾는다
		if(cur.x == -1 && cur.y == -1){ //시작위치 찾기에 실패했으면 >> 더이상 component가 없으면 현재 case 종료
			return;
		}
		while (1) {
			c->maze[cur.x][cur.y] = VISITED; //현위치 방문 표시로 표시
			// 종료 조건 : 더이상 갈 곳이 없으면  >> 8방향 모두 BLACK이 없으면 해당 component 저장하고 종료 
			if (isEmpty(s) && s->comp_size != 0) { // stack이 비어있을 때만 검사
				c->component[c->comp_count++] = s->comp_size+1;
				//free(s);
				initStack(s); // 스택 초기화
				break;
			}
		
			bool forwarded = false; // 8방향 중 한 곳으로 전진하는데 성공했는지를 표시
			for (int dir = 0; dir < 8; dir++) {
				if (movable(c, cur, dir)) {
					push(s, cur); //현재 위치를 stack에 push
					cur = moveTo(cur, dir); //dir 방향으로 한 칸 이동한 위치를 새로운 cur로 변경
					forwarded = true; //전진 성공
					break;
				}
			}
			if (!forwarded) { //8방향 중 어느 곳으로도 가지 못했으면 //false면 
				c->maze[cur.x][cur.y] = BACKTRACKED; //왔다간 위치임을 표시
				if (isEmpty(s)) { //되돌아갈 위치가 없다면 원래 길이 없는 미로임
					printf("No path exists.\n");
					break;
				}
				cur = pop(s); //8방향 중 갈 곳이 없으면 pop해서 이전위치로 돌아감
			}
		}

	}
}

bool movable(Case *c, Position pos, int dir) { //dir 방향으로 이동할 수 있는지 검사
	Position tile = moveTo(pos, dir); //dir 방향 타일 검사
	if (c->maze[tile.x][tile.y] == BLACK ) { // BLACK일 때만 ? 
		return true;
	}
	return false;
}

Position startPos(Case *c) { //component 영역이 시작되는 지점을 찾아 값을 반환
	Position start_pos;
	for (int i = 0; i < c->size; i++) {
		for (int j = 0; j < c->size; j++) {
			if (c->maze[i][j] == BLACK) { // BLACK을 만나면 해당 위치가 시작지점이 됨
				start_pos.x = i;
				start_pos.y = j;

				return start_pos;
			}
		}
	}
	start_pos.x = -1;
	start_pos.y = -1;
	return start_pos;
}

void printComp(Case* c) {
	for (int i = 0; i < c->comp_count; i++) {
		printf("%d ", c->component[i]);
	}
	printf("\n");
}
