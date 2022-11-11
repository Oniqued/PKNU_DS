#include "stack.h"

#define MAX 100

void load();
int search(Case c);

int test_cases;
Case c[MAX];

int main() {
	load();
	/*for (int i = 0; i < test_cases; i++) {
		printf("%d\n", search(c[i]));
	}*/
	
	/*for (int i = 0; i < test_cases; i++) {
		for (int j = 0; j < c[i]->top; j++) {
			printf("%d ", c[i]->stack[j]);
		}
	}*/

	return 0;
}

void load() {
	int index_amt;
	int index;
	FILE* fp = fopen("sample_input.txt", "r");
	if (fp == NULL) {
		return;
	}

	fscanf(fp, "%d", &test_cases); //테스트 케이스 갯수 스캔
	for (int i = 0; i < test_cases; i++) { //테스트 케이스 갯수 만큼 반복
		create(); //테스트 케이스 생성
		fscanf(fp, "%d", &index_amt); //해당 테스트 케이스 stack의 길이는?
		c[i]->top = index_amt - 1; //c[i]->stack의 top 초기화
		for (int j = 0; j <= c[i]->top; j++) {
			fscanf(fp, "%d", &index); //넣으려는 값 스캔
			push(c[i], index); //스캔 한 값 차례로 stack에 적재
		}
	}
}

int search(Case c) {
	int count = 0;
	for (c->top; c->top >= 0; c->top--) {
		for (int i = c->top - 1; i >= 0; i--) {
			if (c->top >= i) {
				count++;
			}
		}
	}
	return count;
}