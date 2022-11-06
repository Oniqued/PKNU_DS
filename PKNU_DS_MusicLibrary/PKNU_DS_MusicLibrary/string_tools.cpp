#include "string_tools.h"

int read_line(FILE* fp, char str[], int n) // (파일 포인터, 문자열을 저장할 배열, 문자열의 크기)
{
	int ch, i = 0;
	while ((ch = fgetc(fp)) != '\n' && ch != EOF)	// fp에서 읽어오는 문자열이 엔터키도 아니고 파일의 끝도 아닐 때 까지 읽음
		if (i < n - 1)
			str[i++] = ch; // str[i]에 ch를 저장하고 i를 1 증가

	str[i] = '\0'; // C-style 문자열. 배열의 마지막에 null 문자 저장
	return i; // 몇 글자를 읽었는지 리턴
}