//테스트 결과 데이터 출력 성공
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#define MAX 100

//사용될 함수
bool isInclude(char arr[]);
void check(char words[]);
void getMaxLength();

//사용될 전역변수 
char words[MAX];
char result[MAX];
int index[MAX];
int maxStart, maxLength; 

int main() {
	scanf("%s", words);
	check(words);
	getMaxLength();

	//시작위치 부터 (시작위치 + 해당 자음의 길이)까지 출력
	for (int i = maxStart; i < maxStart + maxLength; i++) {
		printf("%c", words[i]);
	}

	return 0;
}

//해당 char가 모음인지 자음인지 확인 .. 모음 true / 자음 false
bool isInclude(char ch) {
	if (ch == 'a' ||
		ch == 'e' ||
		ch == 'i' ||
		ch == 'o' ||
		ch == 'u') {
		return true;
	}
	return false;
}

//문자열을 스캔하면서 자음이 나오면 해당 자음이 나온 배열 시작위치를 j에 저장하고,
//index에는 해당 자음의 연속된 길이를 저장
void check(char words[]) {
	for (int i = 0; i < strlen(words); i++) {
		int j = i; //자음 index의 시작 위치
		int length = 0;
		while (isInclude(words[i]) == false && (i < strlen(words))) {
			length++;
			i++;
		}
		index[j] = length; //자음의 시작 위치, 자음의 길이를 저장
	}
}

// index를 순회하며 연속된 자음의 길이가 가장 긴 자음의 시작지점과, 그 길이를 반환
void getMaxLength() {
	maxLength = 0; 
	for (int i = 0; i < strlen(words); i++) {
		if (index[i] > maxLength) {
			maxLength = index[i];
			maxStart = i;
		}
	}
}