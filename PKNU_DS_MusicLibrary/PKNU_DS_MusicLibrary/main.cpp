//�׽�Ʈ ��� ������ ��� ����
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
	initialize();	// Artist �迭�� �ʱ�ȭ
	handle_load();
	process_command();
}

void handle_load()
{
	char buffer[BUFFER_LENGTH];

	printf("Data file name ? ");
	if (read_line(stdin, buffer, BUFFER_LENGTH) <= 0) // �� ������ �Է��� ����(���� ������, �����͸� �о�� ����, ����)
		return;	// ������ ������ �ҷ����� ����

	FILE* fp = fopen(buffer, "r"); // ���������� fp�� buffer�� ����� ������ �̸��� "�б� ���"�� ������
	if (fp == NULL) {
		printf("No such file exists.\n");
		return;
	}

	load(fp); // ���� �����͸� �Ű������� �Ѱ���
	fclose(fp); // ������ �� ���� ���� ������ �ݾ���
}

void process_command()
{
	char command_line[BUFFER_LENGTH];
	char* command;

	while (1)	// ���� ������ ���鼭 -> ������Ʈ�� ����ϸ� ������� ��ɾ �Է¹���
	{
		printf("$ "); // prompt
		if (read_line(stdin, command_line, BUFFER_LENGTH) <= 0) // �� ������ �Է��� ����(���� ������, �����͸� �о�� ����, ����)
			continue;	// �ٽ� ��� ������Ʈ�� ȣ��

		command = strtok(command_line, " ");	// ���鹮�� ������ tokenize�Ͽ� ����
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

void handle_remove()	// �뷡�� index�� tokenizing�ؼ� �ش� ���� ����
{
	char* id_str = strtok(NULL, " "); // COMMAND ������ ���� ��ȣ�� �о
	int index = atoi(id_str);
	remove(index);
}

void handle_save()
{
	char* file_name = strtok(NULL, " ");
	FILE* fp = fopen(file_name, "w");	// ������ ��� �� �뷡�� ���� 
	save(fp);
	fclose(fp);
}

void handle_play()
{
	char* id_str = strtok(NULL, " "); // COMMAND ������ ���� ��ȣ�� �о
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
	printf("    Title: "); // 1. ������ �������� ���� �� 2. ������ ������ ��
	int length = read_line(stdin, title, BUFFER_LENGTH);
	if (length <= 0) {
		search_song(name);
	}
	else
		search_song(name, title); // �Լ� �����ε��� ���� search_song ȣ��
}

void handle_add()
{
	char buffer[BUFFER_LENGTH];
	char* artist = NULL, * title = NULL, * path = NULL;
	printf("    Artist: ");
	if (read_line(stdin, buffer, BUFFER_LENGTH) > 0) // ��� �� ���� �̻� �Է��� ����
		artist = strdup(buffer); // �Է¹��� �̸��� �����ؼ� ����

	printf("    Title: ");
	if (read_line(stdin, buffer, BUFFER_LENGTH) > 0) // ��� �� ���� �̻� �Է��� ����
		title = strdup(buffer); // �Է¹��� ���� �����ؼ� ����

	printf("    Path: ");
	if (read_line(stdin, buffer, BUFFER_LENGTH) > 0) // ��� �� ���� �̻� �Է��� ����
		path = strdup(buffer); // �Է¹��� ��θ� �����ؼ� ����

	printf("%s %s %s \n", artist, title, path);	// �Է¹��� ������ ���

	/* add to the music library */
	add_song(artist, title, path);
}