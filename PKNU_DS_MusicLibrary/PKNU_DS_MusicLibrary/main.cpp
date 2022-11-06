#define _CRT_NONSTDC_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include "string_tools.h"
#include "library.h"

#define BUFFER_LENGTH 200

void process_command();
void handle_add();

int main() {

	process_command();
}

void process_command() {
	char command_line[BUFFER_LENGTH];
	char* command;

	while (1) { //infinite loop
		printf("$ "); //prompt

		if (read_line(stdin, command_line, BUFFER_LENGTH) <= 0) { //get a line 
			continue; //한 라인을 읽었는데 그 라인의 길이가 0이하라면, 사용자가 아무 명령어도 입력하지 않은 것이므로 
		}
		command = strtok(command_line, " ");//사용자 입력 커맨드 
		if (strcmp(command, "add") == 0) {
			handle_add();
		}
		/*else if (strcmp(command, "search") == 0) {
			handle_search();
		}
		else if (strcmp(command, "remove") == 0) {
			handle_remove();
		}*/
		else if (strcmp(command, "status") == 0) {
			status();
		}
		/*else if (strcmp(command, "play") == 0) {
			handle_play();
		}
		else if (strcmp(command, "save") == 0) {
			handle_save();
		}*/
		else if (strcmp(command, "exit") == 0) {
			break;
		}
	}
}

void handle_add() {
	char buffer[BUFFER_LENGTH];
	char* artist = NULL, *title = NULL, *path = NULL;

	printf("\tArtist: ");
	if (read_line(stdin, buffer, BUFFER_LENGTH) > 0){ //적어도 한글자 이상 입력했다. 
		artist = strdup(buffer);
	}
	printf("\tTitle: ");
	if (read_line(stdin, buffer, BUFFER_LENGTH) > 0) { //적어도 한글자 이상 입력했다. 
		title = strdup(buffer);
	}
	printf("\tPath: ");
	if (read_line(stdin, buffer, BUFFER_LENGTH) > 0) { //적어도 한글자 이상 입력했다. 
		path = strdup(buffer);
	}

	printf("\t%s %s %s\n", artist, title, path);

	// add to the music library 
	add_song(artist, title, path);
}