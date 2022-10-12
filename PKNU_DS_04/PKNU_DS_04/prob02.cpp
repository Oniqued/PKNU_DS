//�׽�Ʈ ��� ������ ��� ����
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define ARR_SIZE 100
#define BUFFER_SIZE 100

//���� ���� ����
FILE* file;
int arr[ARR_SIZE][ARR_SIZE];
double arr_avgX[ARR_SIZE];
double arr_avgY[ARR_SIZE];
double arr_sdX[ARR_SIZE];
double arr_sdY[ARR_SIZE];
int N;

//���� �Լ�
void open_file();
void read_file();
void average();
void SD();

int main() {
	open_file();
	read_file();
	average();
	SD();

	//��¹�
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

//���� ����
void open_file() {
	file = fopen("input.txt", "r");
	if (file == NULL) {
		printf("������ �����ϴ�\n");
	}
	else {
		printf("������ ���ϴ�\n");
	}
}

//���� ���� �б�
void read_file() {
	fscanf(file, "%d", &N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			fscanf(file, "%d", &arr[i][j]);
		}
	}
}

//���
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

//ǥ�� ����
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