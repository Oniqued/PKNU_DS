//테스트 결과 데이터 출력 성공
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER_SIZE 1024
#define WORDS_SIZE 9999

//사용될 메서드
void open_file();
void read_file();
void sort();
void save_file();

//사용될 전역변수
FILE* file;
int n;
char buffer[BUFFER_SIZE]; //임시 저장 공간
char* words[WORDS_SIZE]; //단어가 저장될 공간
char* dict[WORDS_SIZE]; //사전 한 줄

int main(void) {
	open_file();
	read_file();
	sort();
	save_file();

	return 0;
}

//파일을 여는 메서드
void open_file() {
	file = fopen("shuffled_dict.txt", "r");
	if (file == NULL) {
		printf("파일 열기 실패\n");
	}
	else {
		printf("파일 열기 성공\n");
	}
}

//파일의 글을 읽는 메서드
void read_file() {
	n = 0;
	while (fgets(buffer, BUFFER_SIZE, file) != NULL) {
		dict[n] = strdup(buffer);
		for (int i = 0; i < BUFFER_SIZE; i++) {
			//한 줄 씩 읽으며 '탭'을 만나면 '탭'이전의 문자까지만 words에 저장한다
			if (buffer[i] == '\t') {
				buffer[i] = '\0';
				words[n] = strdup(buffer);
			}
		}
		//printf("[%d]%s", n, dict[n]);
		n++;
	}
}

//정렬 알고리즘 시간 복잡도 O(n^2)
void sort() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < (n -i) -1; j++) {
			if (strcmp(words[j], words[j + 1]) > 0) {
				char* tmp = words[j];
				words[j] = words[j + 1];
				words[j + 1] = tmp;

				//words를 정렬한 순서에 맞게 dict도 정렬한다
				tmp = dict[j];
				dict[j] = dict[j + 1];
				dict[j + 1] = tmp;
			}
		}
	}
}

//파일을 저장하는 메서드 
void save_file() {
	FILE* s_file = fopen("sorted_dict.txt", "w");
	printf("파일을 저장중입니다...\n");
	//정렬된 dict를 한줄 씩 읽어와서 저장
	for (int i = 0; i < n; i++) { 
		fputs(dict[i], s_file);
	}
	printf("sorted_dict.txt 저장 완료!");
}