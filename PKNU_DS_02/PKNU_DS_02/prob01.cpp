//�׽�Ʈ ��� ������ ��� ����
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#define BUFFER_SIZE 20

//���� �������� 
char str1[BUFFER_SIZE];
char str2[BUFFER_SIZE];
bool isSame;

//�޼��� ����
void cmp(char str1[], char str2[]);

int main(void) {
	scanf("%s", str1);
	scanf("%s", str2);
	cmp(str1, str2);
	if (isSame == true) {
		printf("yes\n");
	}
	return 0;
}

//������ �迭�� ��ȸ�ϸ� ���� ���� ������ false
void cmp(char str1[], char str2[]) {
	for (int i = 0; i < strlen(str1); i++) {
		isSame = false;
		for (int j = 0; j < strlen(str2); j++) {
			if (str1[i] == str2[j]) {
				isSame = true;
			}
		}
		if (isSame == false) {
			printf("no\n");
			return;
		}
	}

	for (int i = 0; i < strlen(str2); i++) {
		isSame = false;
		for (int j = 0; j < strlen(str1); j++) {
			if (str2[i] == str1[j]) {
				isSame = true;
			}
		}
		if (isSame == false) {
			printf("no\n");
			return;
		}
	}
}