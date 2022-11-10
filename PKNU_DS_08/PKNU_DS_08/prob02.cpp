#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 100

//구조체 
typedef struct stack {
	char* name;
	int top;
	char* data[BUFFER_SIZE];
}*Stack;

//전역 변수
Stack stack[BUFFER_SIZE]; 
int count = 0;

//프로토타입
void processCommand();
void handleCreate();
void handlePush();
void handlePop();
void handleList();
int read_line(FILE* fp, char str[], int n);

int main() {
	processCommand();

	return 0;
}

void processCommand() {
	char command_line[BUFFER_SIZE];
	char* command;

	while (1) {
		printf("$ ");
		if (read_line(stdin, command_line, BUFFER_SIZE) <= 0) { //아무것도 입력되지 않으면 넘어감
			continue;
		}
		command = strtok(command_line, " ");
		if (strcmp(command, "create") == 0) {
			handleCreate();
		}
		else if (strcmp(command, "push") == 0) {
			handlePush();
		}
		else if (strcmp(command, "pop") == 0) {
			handlePop();
		}
		else if (strcmp(command, "list") == 0) {
			handleList();
		}
		else if (strcmp(command, "exit") == 0) {
			break;
		}
		else {
			printf("unknown command\n");
		}
	}
}

void handleCreate() {
	char* stack_name = strtok(NULL, " "); //명령어 중에서 스택의 이름 추출
	stack[count] = (Stack)malloc(sizeof(Stack));
	stack[count]->name = strdup(stack_name);
	stack[count]->top = -1;
	count++;
}

void handlePush() {
	char* stack_name = strtok(NULL, " "); //명령어에서 스택의 이름 추출
	char* stack_data = strtok(NULL, " "); //명령어에서 넣고자 하는 데이터 추출
	if (stack_name == NULL || stack_data == NULL) {
		printf("please enter command correctly\n");
		return;
	}

	for (int i = 0; i < count; i++) { // 이름이 일치하는 스택을 찾는다 
		if (strcmp(stack_name, stack[i]->name) == 0) {
			stack[i]->top++;
			stack[i]->data[stack[i]->top] = strdup(stack_data);
		}
	}
	
}

void handlePop() {
	char* stack_name = strtok(NULL, " "); //명령어에서 스택의 이름 추출

	for (int i = 0; i < count; i++) { // 이름이 일치하는 스택을 찾는다 
		if (strcmp(stack_name, stack[i]->name) == 0) {
			if (stack[i]->top <= -1) {
				return;
			}
			printf("%s\n", stack[i]->data[stack[i]->top]);
			stack[i]->top--;
		}
	}
}

void handleList() {
	char* stack_name = strtok(NULL, " "); //명령어에서 스택의 이름 추출
	if (stack_name == NULL) {
		printf("please enter stack name\n");
		return;
	}
	for(int i = 0; i < count; i++){
		if (strcmp(stack_name, stack[i]->name) == 0) {
			for (int j = stack[i]->top; j >= 0; j--) {
				printf("%s\n", stack[i]->data[j]);
			}
		}
	}
}

int read_line(FILE* fp, char str[], int n) // (파일 포인터, 문자열을 저장할 배열, 문자열의 크기)
{
	int ch, i = 0;
	while ((ch = fgetc(fp)) != '\n' && ch != EOF)	// fp에서 읽어오는 문자열이 엔터키도 아니고 파일의 끝도 아닐 때 까지 읽음
		if (i < n - 1)
			str[i++] = ch; // str[i]에 ch를 저장하고 i를 1 증가

	str[i] = '\0'; // C-style 문자열. 배열의 마지막에 null 문자 저장
	return i; // 몇 글자를 읽었는지 리턴
}
