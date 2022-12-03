#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define N 8
#define PATH 0 
#define WALL 1 
#define VISITED 2 
#define BLOCKED 3 

int cnt = 0;
int maze[N][N]
= {
{0, 0, 0, 0, 0, 0, 0, 1},
{0, 1, 1, 0, 1, 1, 0, 1},
{0, 0, 0, 1, 0, 0, 0, 1},
{0, 1, 0, 0, 1, 1, 0, 0},
{0, 1, 1, 1, 0, 0, 0, 1},
{0, 1, 0, 0, 0, 1, 0, 1},
{0, 0, 0, 1, 0, 0, 0, 1},
{0, 1, 1, 1, 0, 1, 0, 0}
};

void findMazePath(int x, int y);
bool movable(int x, int y, int dir);
void printMaze();

int main() {
	printMaze();
	findMazePath(0, 0);
	printf("Count: %d\n", cnt);

	return 0;
}

void findMazePath(int x, int y) {
    if (x == N - 1 && y == N - 1){ // 최종 위치 도달하면 카운트한다.
        cnt++;
    }
    //현재 위치를 찾는다는 것 자체가 이 위치는 갈 수 있는 조건 0이기 때문에 온것이다. 따라서 온 길은 2로 수정해준다.
    maze[x][y] = VISITED;

    //북
    if (x >= 1 && x < N){
        if (maze[x - 1][y] == PATH) {
            findMazePath(x - 1, y);
        }
    }

    //동
    if (y >= 0 && y < N - 1){
        if (maze[x][y + 1] == PATH){
            findMazePath(x, y + 1);
        }
    }
    
    //남
    if (x >= 0 && x < N - 1){
        if (maze[x + 1][y] == PATH){
            findMazePath(x + 1, y);
        }
    }

    //서
    if (y >= 1 && x < N){
        if (maze[x][y - 1] == PATH){
            findMazePath(x, y - 1);
        }
    }

    // 북동남서를 전부 다 검색하고 나면 0으로 변경해주어 다시 검색할 수 있도록 해준다.
    maze[x][y] = PATH;
}

void printMaze() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("%d ", maze[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}