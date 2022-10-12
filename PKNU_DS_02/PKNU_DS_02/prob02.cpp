#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#define BUFFER_SIZE 256

//메서드 정의
void open_file();
int add(int n, char* words[]);
void sort(char* words[]);
int del_dup(char* words[]);

//사용할 전역 변수
char buffer[BUFFER_SIZE];
char search[100];
int search_len, count, unique;
char* words[BUFFER_SIZE];

int main(void) {
	printf("찾을 단어 입력: ");
	scanf("%s", search);
	search_len = strlen(search);
	
	open_file(); //파일 읽고 내용을 단어 형태로 저장
	sort(words); //정렬
	del_dup(words); //중복 제거 

	//해당 단어 출력
	for (int i = 0; i < unique; i++) {
		printf("%s\n", words[i]);
	}
	printf("%d", unique); //중복을 뺀 단어 갯수 출력 
	
	return 0;
}

void open_file() {
	int n = 0;
	FILE* harry = fopen("harry.txt", "r");
	if (harry == NULL) {
		printf("파일이 없습니다.");
		return;
	}
	else {
		printf("파일을 성공적으로 로드했습니다.\n");
		while (fscanf(harry, "%s", buffer) != EOF) { //단어별로 잘라 buffer에 저장
			if (strncmp(buffer, search, search_len) == 0) { //buffer가 search로 시작하는 단어인지 확인
				add(n, words); //조건에 일치 하면 배열에 추가 
				n++;
			}
		}
	}
}

//words에 단어 추가 
int add(int n, char* words[]) {
	words[n] = strdup(buffer); //버퍼의 내용을 words에 저장
	count = n; //몇개의 단어가 있는지 기록
	return count;
}

//정렬 알고리즘 
void sort(char* words[]) { 
	for (int i = 0; i <= count; i++) {
		for (int j = i + 1; j <= count; j++) {
			if (strcmp(words[i], words[j]) > 0) {
				char* tmp = words[i];
				words[i] = words[j];
				words[j] = tmp;
			}
		}
	}
}

//중복 제거 알고리즘 
int del_dup(char* words[]) {
	int j = 0;
	for (int i = 0; i <= count; i++) {
		if (i == 0 || strcmp(words[i], words[i - 1]) > 0) {
			words[j++] = words[i];
		}
	}
	unique = j; //중복을 제거한 배열까지만 저장

	return unique;
}