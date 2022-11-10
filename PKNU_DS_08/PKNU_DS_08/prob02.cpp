#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 100

//����ü 
typedef struct stack {
	char* name;
	int top;
	char* data[BUFFER_SIZE];
}*Stack;

//���� ����
Stack stack[BUFFER_SIZE]; 
int count = 0;

//������Ÿ��
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
		if (read_line(stdin, command_line, BUFFER_SIZE) <= 0) { //�ƹ��͵� �Էµ��� ������ �Ѿ
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
	char* stack_name = strtok(NULL, " "); //��ɾ� �߿��� ������ �̸� ����
	stack[count] = (Stack)malloc(sizeof(Stack));
	stack[count]->name = strdup(stack_name);
	stack[count]->top = -1;
	count++;
}

void handlePush() {
	char* stack_name = strtok(NULL, " "); //��ɾ�� ������ �̸� ����
	char* stack_data = strtok(NULL, " "); //��ɾ�� �ְ��� �ϴ� ������ ����
	if (stack_name == NULL || stack_data == NULL) {
		printf("please enter command correctly\n");
		return;
	}

	for (int i = 0; i < count; i++) { // �̸��� ��ġ�ϴ� ������ ã�´� 
		if (strcmp(stack_name, stack[i]->name) == 0) {
			stack[i]->top++;
			stack[i]->data[stack[i]->top] = strdup(stack_data);
		}
	}
	
}

void handlePop() {
	char* stack_name = strtok(NULL, " "); //��ɾ�� ������ �̸� ����

	for (int i = 0; i < count; i++) { // �̸��� ��ġ�ϴ� ������ ã�´� 
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
	char* stack_name = strtok(NULL, " "); //��ɾ�� ������ �̸� ����
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

int read_line(FILE* fp, char str[], int n) // (���� ������, ���ڿ��� ������ �迭, ���ڿ��� ũ��)
{
	int ch, i = 0;
	while ((ch = fgetc(fp)) != '\n' && ch != EOF)	// fp���� �о���� ���ڿ��� ����Ű�� �ƴϰ� ������ ���� �ƴ� �� ���� ����
		if (i < n - 1)
			str[i++] = ch; // str[i]�� ch�� �����ϰ� i�� 1 ����

	str[i] = '\0'; // C-style ���ڿ�. �迭�� �������� null ���� ����
	return i; // �� ���ڸ� �о����� ����
}
