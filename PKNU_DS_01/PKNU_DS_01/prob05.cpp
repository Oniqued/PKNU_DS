#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define BUFFER_SIZE 100
//
int arr[BUFFER_SIZE];
int arrNoDup[BUFFER_SIZE];
int arrLen;
int n = 0; //���� arr�� ����ִ� ���� ��
int dupLen = 0;

void add(int num);
void delDup();

int main(void) {
	int num;
	scanf("%d", &arrLen);
	
	//�Է� �޾Ƽ� ���� ����
	for (int i = 0; i < arrLen; i++) {
		scanf("%d", &num);
		add(num);
		n++;
	}
	
	delDup();


	printf("%d: ", dupLen);
	for (int i = 0; i < dupLen; i++) {
		printf("%d ", arrNoDup[i]);
	}

	return 0;
}

//���� ����
void add(int num) {
	int i = n-1;
	while (i >= 0 && arr[i] > num) {
		arr[i + 1] = arr[i];
		i--;
	}
	if (i == -1) { //���� ó���� �־�� �� ��
		arr[0] = num;
	}
	else{ //�߰��� �־�� �Ҷ� i-- ���༭ �ٽ� +1������� 
		arr[i+1] = num;
	}
}

void delDup() {
	
	for (int i = 0; i < arrLen; i++) {
		if (dupLen == 0) {
			arrNoDup[dupLen] = arr[i];
			dupLen++;
			continue;
		}
		if (arrNoDup[dupLen - 1] == arr[i]) {
			continue;
		}
		else {
			arrNoDup[dupLen] = arr[i];
			dupLen++;
		}
		
	}
}