#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define BUFFER_SIZE 1000000
#define MAX 100

//구조체 
typedef struct testCase {
	int data[BUFFER_SIZE];
	int huristic;
}Case;

//함수 프로토타입
void load();
void allocation(int i);
void search(int i, int j, int input);

//사용될 전역 변수
int test_cases;
Case *c[MAX];

int main() {
	clock_t start = clock();
	load();
	clock_t end = clock();
	printf("Elapsed Time: %lf\n", (double)(end - start)/ CLOCKS_PER_SEC);

	return 0;
}

void load() {
	int input_len;
	int input;

	FILE* fp = fopen("input.txt", "r");
	if (fp == NULL) {
		return;
	}

	fscanf(fp, "%d", &test_cases); //테스트 케이스 갯수 스캔
	for (int i = 0; i < test_cases; i++) { //테스트 케이스 갯수 만큼 반복
		allocation(i); //메모리 할당
		fscanf(fp, "%d", &input_len); //해당 테스트 케이스 data의 길이는?
		for (int j = 0; j < input_len; j++) {
			fscanf(fp, "%d", &input); //넣으려는 값 스캔
			search(i, j, input);
			c[i]->data[j] = input; //데이터 삽입 
			//printf("%d ", c[i]->data[j]);
		}
		printf("%d\n", c[i]->huristic);
	}
}

void allocation(int i) {
	c[i] = (Case*)malloc(sizeof(Case)); //테스트 케이스 메모리 공간 생성
	c[i]->huristic = 0; //huristic 초기화
}

void search(int i, int j, int input) {
	for(int k = j-1; k >= 0; k--){
		if (c[i]->data[k] < input) {
			c[i]->huristic++;
		}
		else {
			break;
		}
	}
}