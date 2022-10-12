#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

void tok_line(char buffer[]);

char* arr[3];

int main() {
	char str[] = { "asdasda & asdajsdlkajsd & aa" };
	tok_line(str);
	int i = 0;
	for (int i = 0; i < 3; i++) {
		printf("%s", arr[i]);
	}
	
	

    return 0;
}

void tok_line(char buffer[]) {
	char* token;
	char check[] = { "&" };
	int i = 0;

	token = strtok(buffer, check);
	while (token != NULL) {
		arr[i++] = token;
		token = strtok(NULL, check);
	}
}