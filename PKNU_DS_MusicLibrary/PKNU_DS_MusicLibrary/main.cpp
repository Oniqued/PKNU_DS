//테스트 결과 데이터 출력 성공
#define _CRT_NONSTDC_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include "string_tools.h"
#include "library.h"

#define BUFFER_LENGTH 200

void process_command();
void handle_add();
void handle_load();
void handle_search();
void handle_play();
void handle_save();
void handle_remove();

int main()
{
	initialize();	// Artist 배열을 초기화
	handle_load();
	process_command();
}

void handle_load()
{
	char buffer[BUFFER_LENGTH];

	printf("Data file name ? ");
	if (read_line(stdin, buffer, BUFFER_LENGTH) <= 0) // 줄 단위로 입력을 받음(파일 포인터, 데이터를 읽어올 변수, 길이)
		return;	// 데이터 파일을 불러오지 않음

	FILE* fp = fopen(buffer, "r"); // 파일포인터 fp에 buffer에 저장된 파일의 이름을 "읽기 모드"로 저장함
	if (fp == NULL) {
		printf("No such file exists.\n");
		return;
	}

	load(fp); // 파일 포인터를 매개변수로 넘겨줌
	fclose(fp); // 파일을 다 읽은 다음 파일을 닫아줌
}

void process_command()
{
	char command_line[BUFFER_LENGTH];
	char* command;

	while (1)	// 무한 루프를 돌면서 -> 프롬프트를 출력하며 사용자의 명령어를 입력받음
	{
		printf("$ "); // prompt
		if (read_line(stdin, command_line, BUFFER_LENGTH) <= 0) // 줄 단위로 입력을 받음(파일 포인터, 데이터를 읽어올 변수, 길이)
			continue;	// 다시 명령 프롬프트를 호출

		command = strtok(command_line, " ");	// 공백문자 전까지 tokenize하여 저장
		if (strcmp(command, "add") == 0)
			handle_add();
		else if (strcmp(command, "search") == 0)
			handle_search();
		else if (strcmp(command, "play") == 0)
			handle_play();
		else if (strcmp(command, "remove") == 0)
			handle_remove();
		else if (strcmp(command, "save") == 0) {
			char* tmp = strtok(NULL, " ");
			if (strcmp(tmp, "as") != 0)
				continue;
			handle_save();
		}
		else if (strcmp(command, "status") == 0)
			status();
		else if (strcmp(command, "exit") == 0)
			break;
	}
}

void handle_remove()	// 노래의 index를 tokenizing해서 해당 곡을 삭제
{
	char* id_str = strtok(NULL, " "); // COMMAND 다음에 오는 번호를 읽어냄
	int index = atoi(id_str);
	remove(index);
}

void handle_save()
{
	char* file_name = strtok(NULL, " ");
	FILE* fp = fopen(file_name, "w");	// 파일을 열어서 새 노래를 저장 
	save(fp);
	fclose(fp);
}

void handle_play()
{
	char* id_str = strtok(NULL, " "); // COMMAND 다음에 오는 번호를 읽어냄
	int index = atoi(id_str);
	play(index);
}

void handle_search()
{
	char name[BUFFER_LENGTH], title[BUFFER_LENGTH];
	printf("    Artist: ");
	if (read_line(stdin, name, BUFFER_LENGTH) <= 0) {
		printf("    Artist name required \n");
		return;
	}
	printf("    Title: "); // 1. 가수가 존재하지 않을 때 2. 가수가 존재할 때
	int length = read_line(stdin, title, BUFFER_LENGTH);
	if (length <= 0) {
		search_song(name);
	}
	else
		search_song(name, title); // 함수 오버로딩을 통해 search_song 호출
}

void handle_add()
{
	char buffer[BUFFER_LENGTH];
	char* artist = NULL, * title = NULL, * path = NULL;
	printf("    Artist: ");
	if (read_line(stdin, buffer, BUFFER_LENGTH) > 0) // 적어도 한 글자 이상 입력을 받음
		artist = strdup(buffer); // 입력받은 이름을 복사해서 저장

	printf("    Title: ");
	if (read_line(stdin, buffer, BUFFER_LENGTH) > 0) // 적어도 한 글자 이상 입력을 받음
		title = strdup(buffer); // 입력받은 곡을 복사해서 저장

	printf("    Path: ");
	if (read_line(stdin, buffer, BUFFER_LENGTH) > 0) // 적어도 한 글자 이상 입력을 받음
		path = strdup(buffer); // 입력받은 경로를 복사해서 저장

	printf("%s %s %s \n", artist, title, path);	// 입력받은 정보를 출력

	/* add to the music library */
	add_song(artist, title, path);
}