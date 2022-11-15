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
	int size;
	int component[MAX];
	int maze[MAX][MAX];
}Case;

//함수
void createCase(int test_case);
void read_maze();
void search(Case*);
void printComp(Case*);

//전역 변수
int test_case;
Case *c[MAX_CASES];

int main() {
	read_maze();
	for (int i = 0; i < test_case; i++) {
		search(c[i]); //case[i] component의 크기 탐색
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
	printf("Load Completed\n");
	fclose(fp);
}

void search(Case *c) {
	Position cur; //현위치
	Stack s = create(); //위치 정보가 저장될 스택
	
	
	
}

void startPos(Case *c) {
	
}