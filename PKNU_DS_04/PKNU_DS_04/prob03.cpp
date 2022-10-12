//테스트 결과 데이터 출력 성공
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS

#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1000

//사용될 함수
void load_file();
void tok_line(char* index[]);
void compress(char str[]);
void prettier();
void save_file();

//사용될 전역 변수
int m, n; //행, 열의 갯수
char buffer[BUFFER_SIZE];
char* index[BUFFER_SIZE];
char* output[BUFFER_SIZE][BUFFER_SIZE];
int space[BUFFER_SIZE][BUFFER_SIZE]; //각 output에 추가될 공백의 길이를 저장하는 배열

int main() {
	load_file();
	prettier();
	save_file();

	return 0;
}

//파일을 읽는 함수
void load_file() {
	FILE* table = fopen("table.txt", "r");
	if (table == NULL) {
		printf("파일 열기 실패");
		return;
	}
	else {
		fscanf(table, "%d %d ", &m, &n);
		//read_line

		int i = 0;
		while (fgets(buffer, BUFFER_SIZE, table) != NULL) { //파일 끝까지 읽는다
			compress(buffer); //중복 공백, 개행 제거
			index[i++] = strdup(buffer); //한 줄을 각각index에 저장
		}
		tok_line(index); //index를 &기준으로 잘라서 output배열에 각 객체를 저장
	}
}

//& 기준으로 잘라서 저장
void tok_line(char* index[]) {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (j == 0) {
				output[i][j] = strtok(index[i], "&");
			}
			else {
				output[i][j] = strtok(NULL, "&");
			}
		}
	}
}

//과도한 공백 제거 및 개행 제거
void compress(char str[]) {
	//문장 끝에 개행 제거(\n제거)
	for (int i = 0; i < strlen(str); i++) {
		if (buffer[i] == '\n') {
			buffer[i] = NULL;
		}
	}
	//중복 공백 제거
	int n = 0;
	char tmp[BUFFER_SIZE];
	for (int i = 0; i < strlen(str); i++) {
		if (str[i] == ' ' && str[i + 1] == ' ') { //현재, 다음 인덱스가 공백이면 공백 하나로 축약... 반복
			continue;
		}
		tmp[n++] = str[i];
	}
	tmp[n] = 0; //끝에 NULL 추가
	strcpy(str, tmp); //str에 tmp를 저장한다
}

//깔끔하게 출력되기 위한 공백 추가
void prettier() {
	int max;
	for (int i = 0; i < m; i++) {
		max = 0;
		//각 행에서 길이가 가장 긴 단어의 길이를 찾는다
		for (int j = 0; j < n; j++) {
			if (strlen(output[j][i]) > max) {
				max = strlen(output[j][i]);
			}
		}
		//space배열에 output에 추가될 공백의 길이를 저장한다
		for (int j = 0; j < n; j++) {
			space[j][i] = (max - strlen(output[j][i]));
		}
	}
}

//파일 쓰기
void save_file() {
	FILE* fp = fopen("output.txt", "w");

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			fprintf(fp, "%s", output[i][j]);
			for (int k = 0; k < space[i][j]; k++) {
				fprintf(fp, " ");
			}
		}
		fprintf(fp, "\n");
	}
	printf("output.txt 저장 완료\n");
}