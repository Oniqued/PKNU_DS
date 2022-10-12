//테스트 결과 데이터 출력 성공
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#include <stdio.h>
#define SIZE 19

//사용될 함수
void load();
void judge();
bool horizon();
bool vertical();
bool diagonal();
void winner(int stone);

//사용될 전역 변수
int N;
int board[SIZE][SIZE];

int main() {
	load();

	//우승 조건 체크 (셋다 아니면 not finished 출력)
	if (vertical() == false &&
		horizon() == false &&
		diagonal() == false) {
		printf("Not Finished\n");
	}

	return 0;
}


//파일 읽기
void load() {
	FILE* file = fopen("board.txt", "r");
	if (file == NULL) {
		printf("FAILED TO READ FILE\n");
		return;
	}
	fscanf(file, "%d ", &N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			fscanf(file, "%d", &board[i][j]);
		}
	}
	fclose(file);
}

//승패 판단
/*
*	1. 같은 수가 대각선 방향으로 연속해서 5개가 놓인다
*	2. 같은 수가 수평으로 연속해서 5개가 나열된다
*	3. 같은 수가 수직으로 연속해서 5개가 나열된다
*/

//같은 수가 대각선으로 나열되는 경우
bool diagonal() {
	int count; //같은 돌이 나온 횟수 체크 
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			count = 1; 
			if (board[i][j] == 0) continue; //0인 경우 건너뜀
			for (int k = 1; k < 5; k++) {
				// '/' 방향 대각선 같은 돌 체크
				if (board[i][j] == board[i + k][j - k]) {
					count++;
					//연속해서 5개가 놓이면
					if (count == 5) {
						winner(board[i][j]);
						return true;
					}
				}
			}
			count = 1;
			for (int k = 1; k < 5; k++) {
				// 반대 대각선 같은 돌 체크
				if (board[i][j] == board[i - k][j + k]) {
					count++;
					//연속해서 5개가 놓이면
					if (count == 5) {
						winner(board[i][j]);
						return true;
					}
				}
			}
		}
	}
	return false;
}

//같은 수가 수평으로 나열되는 경우
bool horizon() {
	int count;
	for (int i = 0; i < N; i++) {
		count = 1;
		for (int j = 0; j < N; j++) {
			if ((board[i][j] == board[i][j + 1]) && (board[i][j] != 0)) {
				count++;
				//연속해서 5개가 놓이면
				if (count == 5) {
					winner(board[i][j]);
					return true;
				}
			}
		}
	}
	return false;
}

//같은 수가 수직으로 나열되는 경우
bool vertical() {
	int count;
	for (int i = 0; i < N; i++) {
		count = 1;
		for (int j = 0; j < N; j++) {
			if ((board[j][i] == board[j + 1][i]) && (board[j][i] != 0)) {
				count++;
				//연속해서 5개가 놓이면
				if (count == 5) {
					winner(board[j][i]);
					return true;
				}
			}
		}
	}
	return false;
}

//해당 돌이 무슨 돌인지 체크
void winner(int stone) {
	if (stone == 1) {
		printf("Black\n");
	}
	else if (stone == 2) {
		printf("White\n");
	}
}
