#define _CRT_NONSTDC_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1000
#define MAX 10000

char buffer[BUFFER_SIZE];
char* words[MAX];
char* exp[MAX];

void load();
void save();

int main() {
	load();
	save();

	return 0;
}

void load() {
	FILE* file = fopen("shuffled_dict.txt", "r");
	if (file == NULL) {
		return;
	}
	int n = 0;
	while (fgets(buffer, BUFFER_SIZE, file) != NULL) {
		if (buffer[strlen(buffer) - 1] == '\n') { //문장 끝 개행 제거
			buffer[strlen(buffer) - 1] = '\0';
		}

		char* tmp = strtok(buffer, "\t");  //buffer를 탭기준으로 자름
		
		//삽입 정렬
		int i = n - 1;
		while (i >= 0 && strcmp(words[i], tmp) > 0) { //맨뒤에서 부터 나보다 큰 값이 안나올때 까지 반복
			words[i + 1] = words[i]; //나보다 크면 한칸씩 뒤로 이동
			exp[i + 1] = exp[i]; //words에 따라 붙어서 이동
			i--;
		}
		//처음에는 위 반복문 실행 x 바로 words[0]에 추가
		//들어갈 곳을 찾으면
		words[i+1] = strdup(tmp); //버퍼를 자른 tmp를 words에 저장
		tmp = strtok(NULL, "\t"); //자른 후 NULL부터 시작이므로 NULL부터 다시 자름
		exp[i+1] = strdup(tmp); //자른 tmp를 exp에 저장
		n++;
	}
	fclose(file);
}

void save() {
	FILE* file = fopen("sorted_dict.txt", "w");
	printf("파일 저장\n");
	
	for (int i = 0; words[i] != NULL; i++) {
		fprintf(file, "%s : %s\n", words[i], exp[i]);
	}

	
}