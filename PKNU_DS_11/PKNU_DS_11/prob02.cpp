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
    if (x == N - 1 && y == N - 1){ // ���� ��ġ �����ϸ� ī��Ʈ�Ѵ�.
        cnt++;
    }
    //���� ��ġ�� ã�´ٴ� �� ��ü�� �� ��ġ�� �� �� �ִ� ���� 0�̱� ������ �°��̴�. ���� �� ���� 2�� �������ش�.
    maze[x][y] = VISITED;

    //��
    if (x >= 1 && x < N){
        if (maze[x - 1][y] == PATH) {
            findMazePath(x - 1, y);
        }
    }

    //��
    if (y >= 0 && y < N - 1){
        if (maze[x][y + 1] == PATH){
            findMazePath(x, y + 1);
        }
    }
    
    //��
    if (x >= 0 && x < N - 1){
        if (maze[x + 1][y] == PATH){
            findMazePath(x + 1, y);
        }
    }

    //��
    if (y >= 1 && x < N){
        if (maze[x][y - 1] == PATH){
            findMazePath(x, y - 1);
        }
    }

    // �ϵ������� ���� �� �˻��ϰ� ���� 0���� �������־� �ٽ� �˻��� �� �ֵ��� ���ش�.
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