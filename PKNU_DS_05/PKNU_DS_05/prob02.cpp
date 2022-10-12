//테스트 결과 데이터 출력 성공
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 100

//사용될 함수
void load();
void show();
void colmax();
void colmin();
void rowmax();
void rowmin();
void slice();

//사용될 전역 변수
int N;
int arr[BUFFER_SIZE][BUFFER_SIZE];

int main() {
	char buffer[BUFFER_SIZE];
	load();
	while (1) {
		printf("$ ");
		scanf("%s", buffer);
		if (strcmp(buffer, "show") == 0) {
			show();
		}
		else if (strcmp(buffer, "colmax") == 0) {
			colmax();
		}
		else if (strcmp(buffer, "colmin") == 0) {
			colmin();
		}
		else if (strcmp(buffer, "rowmax") == 0) {
			rowmax();
		}
		else if (strcmp(buffer, "rowmin") == 0) {
			rowmin();
		}
		else if (strcmp(buffer, "slice") == 0) {
			slice();
		}
		//return 0; 으로 메인함수 종료
		else if (strcmp(buffer, "exit") == 0) {
			return 0;
		}
		//사용자가 유효하지 않은 명령어를 입력했을 경우 
		else { 
			printf("ERROR : invalid value");
		}
		printf("\n");
	}

	return 0;
}

//파일 읽기 
void load() {
	FILE* file = fopen("data.mat", "r");
	if (file == NULL) {
		printf("파일열기 실패\n");
		return;
	}
	fscanf(file, "%d ", &N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			fscanf(file, "%d", &arr[i][j]);
		}
	}
	fclose(file);
}

//행렬 출력
void show() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}
}

//각 열의 최댓값 출력
void colmax(){
	int max;
	for (int i = 0; i < N; i++) {
		max = 0;
		for (int j = 0; j < N; j++) {
			if (arr[j][i] > max) {
				max = arr[j][i];
			}
		}
		printf("%d ", max);
	}
	printf("\n");
}

//각 열의 최솟값 출력
void colmin(){
	int min;
	for (int i = 0; i < N; i++) {
		min = 9999;
		for (int j = 0; j < N; j++) {
			if (arr[j][i] < min) {
				min = arr[j][i];
			}
		}
		printf("%d ", min);
	}
	printf("\n");
}

//각 행의 최댓값 출력
void rowmax(){
	int max;
	for (int i = 0; i < N; i++) {
		max = 0;
		for (int j = 0; j < N; j++) {
			if (arr[i][j] > max) {
				max = arr[i][j];
			}
		}
		printf("%d ", max);
	}
	printf("\n");
}

//각 행의 최솟값 출력
void rowmin(){
	int min;
	for (int i = 0; i < N; i++) {
		min = 9999;
		for (int j = 0; j < N; j++) {
			if (arr[i][j] < min) {
				min = arr[i][j];
			}
		}
		printf("%d ", min);
	}
	printf("\n");
}

//
void slice(){
	int x, p, y, q;
	scanf("%d %d %d %d", &x, &p, &y, &q);
	int tmp = y; //y값은 반복문을 다시 돌때 y값 그대로 가지고 있어야하므로 임시 변수에 값을 저장
	for (x; x < N; x = x + p) {
		for (y = tmp; y < N; y = y + q) { //y가 다시 초기화 되야함
			printf("%d ", arr[x][y]);
		}
		printf("\n");
	}
}

