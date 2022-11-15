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
	long huristic;
}Case;

//함수 프로토타입
void load();
void allocation(int i);
void init();
void search(int i, int j, int input);
void printHuristic();

//사용될 전역 변수
int test_cases;
int none_huristic_start;
int prev_huristic_value;
int prev_huristic;
Case *c[MAX];

int main() {
	clock_t start = clock();
	load();
	clock_t end = clock();
	//printHuristic();
	printf("Elapsed Time: %lf\n", (double)(end - start)/ CLOCKS_PER_SEC);

	return 0;
}

void load() {
	int input_len, input;

	FILE* fp = fopen("input.txt", "r");
	if (fp == NULL) {
		return;
	}

	fscanf(fp, "%d", &test_cases); //테스트 케이스 갯수 스캔
	for (int i = 0; i < test_cases; i++) { //테스트 케이스 갯수 만큼 반복
		allocation(i); //메모리 할당
		init();
		fscanf(fp, "%d", &input_len); //해당 테스트 케이스 data의 길이는?
		for (int j = 0; j < input_len; j++) {
			fscanf(fp, "%d", &input); //넣으려는 값 스캔
			search(i, j, input); //해당 input의 h()값
			c[i]->data[j] = input; //데이터 삽입 
		}
		printf("%d\n", c[i]->huristic % 1000000);
	}
}

void allocation(int i) {
	c[i] = (Case*)malloc(sizeof(Case)); //테스트 케이스 메모리 공간 생성
	c[i]->huristic = 0; //huristic 초기화
}

void init() {
	none_huristic_start = 0;
	prev_huristic_value = 0;
	prev_huristic = 0;
}

//none_huristic_start = -1
//prev_huristic_value = 1
//prev_huristic = 1

void search(int i, int j, int input) { //1 1 2
	int tmp_h = 0;
	int k = j - 1;
	
	if (prev_huristic != 0 && none_huristic_start < 0) {
		c[i]->huristic += k;
	}
	
	//if (prev_huristic_value != 0 && c[i]->data[k] <= input) {
	//	c[i]->huristic = c[i]->huristic + prev_huristic_value + 1;
	//	for (int p = none_huristic_start; p >= 0; p--) {
	//		if (c[i]->data[p] <= input) {
	//			c[i]->huristic++;
	//		}
	//	}
	//	prev_huristic = j;
	//	prev_huristic_value = c[i]->huristic; //이전 휴리스틱의 값
	//	//printf("h(%d) = %d\n", j, c[i]->huristic);
	//	return;
	//}

	for(k = j-1; k >= 0 && k != -1; k--){
		if (c[i]->data[k] <= input) {
			tmp_h++;
		}
		else {
			c[i]->huristic += tmp_h; //h(j) = tmp_h // tmp_h = 1
			none_huristic_start = k; //휴리스틱에 포함되지 않는 부분의 시작지점 // -1
			prev_huristic = j; //1
			if (tmp_h == 0) {
				prev_huristic_value = 0; //이전 휴리스틱의 값
			}
			else {
				prev_huristic_value = tmp_h; //이전 휴리스틱의 값
			}
			//printf("h(%d) = %d\n", j, c[i]->huristic);
			return;
		}
	}
}

void printHuristic() {
	for (int i = 0; i < test_cases; i++) {
		printf("%d\n", c[i]->huristic % 1000000);
	}
}