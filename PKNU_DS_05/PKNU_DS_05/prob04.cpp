//테스트 결과 데이터 출력 성공
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#define BUFFER_SIZE 256

//사용될 함수
void load();
void save();
void filter(char buffer[]);

//사용될 전역 변수 
char buffer[BUFFER_SIZE];
char* content[BUFFER_SIZE];

int main() {
	load();
	save();

	return 0;
}

//파일 읽고 필터링 한 내용을 content에 저장
void load() {
	FILE* file = fopen("sample.html", "r");
	if (file == NULL) {
		printf("ERROR! FAILED TO OPEN FILE\n");
		return;
	}
	else {
		printf("OPEN sample.html...\n");
	}
	int i = 0; //줄의 번호 저장
	while (fgets(buffer, BUFFER_SIZE, file) != NULL) {
		//문장 끝에있는 개행 제거
		for (int j = 0; j < BUFFER_SIZE; j++) {
			if (buffer[j] == '\n') {
				buffer[j] = NULL;
			}
		}
		//Tag를 제거
		filter(buffer);
		//Tag를 제거한 한 줄
		content[i] = strdup(buffer);
		i++;
	}
	fclose(file);
}

//파일 저장
void save() {
	FILE* file = fopen("sample.txt", "w");
	if (file == NULL) {
		printf("FAILED TO WRITE FILE\n");
		return;
	}
	else {
		printf("SUCCESSED TO SAVE FILE (with sample.txt)\n");
	}
	
	for (int i = 0; content[i] != NULL; i++) {
		fprintf(file, "%s\n", content[i]);
	}

	fclose(file);
}

//Tag 자르기 
void filter(char buffer[]) {
	int i = 0;
	int j = 0;
	char tmp[BUFFER_SIZE];
	while (buffer[i] != '\0') {
		//Tag 시작 부분
		if (buffer[i] == '<') { 
			//Tag의 끝부분이 나올때 까지 i++
			while (buffer[i] != '>') {
				i++;
			}
			i++; //'>'부분 건너뛰기
			//다음 문자가 Tag시작이면 다시 위 과정 반복
			if (buffer[i] == '<') continue;
		}
		//Tag를 자른 순수 문자 하나씩 tmp[0]부터 저장
		tmp[j++] = buffer[i++];
	}
	tmp[j] = '\0'; //끝에 NULL CHAR 추가
	strcpy(buffer, tmp); //buffer에 tmp 덮어쓰기
}
