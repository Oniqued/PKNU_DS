#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define BUFFER_SIZE 100
//
int arr[BUFFER_SIZE];
int arrNoDup[BUFFER_SIZE];
int arrLen;
int n = 0; //현재 arr에 들어있는 숫자 수
int dupLen = 0;

void add(int num);
void delDup();

int main(void) {
	int num;
	scanf("%d", &arrLen);
	
	//입력 받아서 삽입 정렬
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

//삽입 정렬
void add(int num) {
	int i = n-1;
	while (i >= 0 && arr[i] > num) {
		arr[i + 1] = arr[i];
		i--;
	}
	if (i == -1) { //제일 처음에 넣어야 할 때
		arr[0] = num;
	}
	else{ //중간에 넣어야 할때 i-- 해줘서 다시 +1해줘야함 
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