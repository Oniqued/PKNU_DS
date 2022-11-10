#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 100

//����ü 
typedef struct stackName StackName;
typedef struct stack Stack;

struct stackName {
	char* name;
	Stack* stack;
};

struct stack {
	int top = -1;
	char* data;
};

//���� ����
StackName* stackNames[BUFFER_SIZE]; 
int count = 0;

//������Ÿ��
void processCommand();
void handleCreate();
void handlePush();
void push();
void handlePop();
void pop();
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
	}
}

void handleCreate() {
	char* stack_name = strtok(NULL, " "); //��ɾ� �߿��� ������ �̸� ����
	stackNames[count]->name = strdup(stack_name);
	count++;

	printf("%s\n", stackNames[count]->name);
}

void handlePush() {
	char* stack_name = strtok(NULL, " "); //��ɾ�� ������ �̸� ����
	char* stack_data = strtok(NULL, " "); //��ɾ�� �ְ��� �ϴ� ������ ����
	for (int i = 0; i < count; i++) { // �̸��� ��ġ�ϴ� ������ ã�´� 
		if (strcmp(stackNames[i]->name, stack_name) == 0) {
			
		}
	}

}

void handlePop() {

}

void pop() {

}

void handleList() {

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
