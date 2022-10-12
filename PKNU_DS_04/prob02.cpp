//테스트 결과 데이터 출력 성공
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define ARR_SIZE 100
#define BUFFER_SIZE 100

//사용될 전역 변수
FILE* file;
int arr[ARR_SIZE][ARR_SIZE];
double arr_avgX[ARR_SIZE];
double arr_avgY[ARR_SIZE];
double arr_sdX[ARR_SIZE];
double arr_sdY[ARR_SIZE];
int N;

//사용될 함수
void open_file();
void read_file();
void average();
void SD();

int main() {
	open_file();
	read_file();
	average();
	SD();

	//출력문
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("%d\t", arr[i][j]);
		}
		printf("%.2f\t%.2f\n\n", arr_avgX[i], arr_sdX[i]);
	}
	
	for (int i = 0; i < N; i++) {
		printf("%.2f\t", arr_avgY[i]);
	}
	printf("\n\n");
	for (int i = 0; i < N; i++) {
		printf("%.2f\t", arr_sdY[i]);
	}
	
	return 0;
}

//파일 열기
void open_file() {
	file = fopen("input.txt", "r");
	if (file == NULL) {
		printf("파일이 없습니다\n");
	}
	else {
		printf("파일을 엽니다\n");
	}
}

//파일 내용 읽기
void read_file() {
	fscanf(file, "%d", &N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			fscanf(file, "%d", &arr[i][j]);
		}
	}
}

//평균
void average() {
	double sum;
	for (int i = 0; i < N; i++) {
		sum = 0;
		for (int j = 0; j < N; j++) {
			sum += arr[i][j];
		}
		arr_avgX[i] = sum / N;
	}

	for (int i = 0; i < N; i++) {
		sum = 0;
		for (int j = 0; j < N; j++) {
			sum += arr[j][i];
		}
		arr_avgY[i] = sum / N;
	}
}

//표준 편차
void SD() {
	double sum;
	for (int i = 0; i < N; i++) {
		sum = 0;
		for (int j = 0; j < N; j++) {
			sum += pow((arr[i][j] - arr_avgX[i]), 2);
		}
		arr_sdX[i] = sqrt(sum / N);
	}

	for (int i = 0; i < N; i++) {
		sum = 0;
		for (int j = 0; j < N; j++) {
			sum += pow((arr[j][i] - arr_avgY[i]), 2);
		}
		arr_sdY[i] = sqrt(sum / N);
	}
}