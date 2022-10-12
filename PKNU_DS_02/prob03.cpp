#define _CRT_NONSTDC_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#define BUFFER_SIZE 256
#define WORDS_AMOUNT 5000

//사용될 전역 변수
FILE* harry;
char buffer[BUFFER_SIZE];
char* words[WORDS_AMOUNT];
int words_check[WORDS_AMOUNT];
int count;

//메서드 정의
void read_file();
int search_word_limit(int limit);
void sort(char* words[]);
void del_dup(char* words[]);

int main(void) {
	read_file();
	search_word_limit(6);
	sort(words);
	del_dup(words);

	for (int i = 0; i < count; i++) {
		printf("%s: %d\n", words[i], words_check[i]);
	}
	printf("%d\n", count);

	return 0;
}

//파일 열기
void read_file() {
	harry = fopen("harry.txt", "r");
	if (harry == NULL) {
		printf("파일 열기에 실패했습니다.\n프로그램을 종료합니다.");
		return;
	}
	else {
		printf("파일을 열었습니다.\n");
	}
}

//길이가 6이상인 단어들만 저장
int search_word_limit(int limit) {
	int i = 0;
	while (fscanf(harry, "%s", buffer) != EOF) {
		if (strlen(buffer) >= limit) { //단어의 길이가 limit이상일때만 단어 저장
			words[i++] = strdup(buffer);
		}
	}
	count = i;

	return count;
}

//단어 정렬 알고리즘 :: Bubble Sort
void sort(char* words[]) {
	for (int i = 0; i < count; i++) {
		for (int j = i + 1; j < count; j++) {
			if (strcmp(words[i], words[j]) > 0) {
				char* tmp = words[i];
				words[i] = words[j];
				words[j] = tmp;
			}
		}
	}
}

//단어 중복 제거 알고리즘 
//:: 중복을 제거하고 해당 단어의 등장횟수를 check에 따로 저장한다
void del_dup(char* words[]) {
	int j = 0;
	for (int i = 0; i < count; i++) {
		if (i == 0 || strcmp(words[i], words[i - 1]) > 0) {
			words[j] = words[i];
			words_check[j] = words_check[j] + 1; //현재 단어 등장 횟수 + 1
			j++;
		}
		else{ //위 조건이 일치 하지 않으면 중복된 값을 만난 것이므로 check + 1
			words_check[j-1] = words_check[j - 1] + 1;
		}
	}
	count = j; //중복을 제거한 배열 words[j]의 양만큼 count에 저장
}