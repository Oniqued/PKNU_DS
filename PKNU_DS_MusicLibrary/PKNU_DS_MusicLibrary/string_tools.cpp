#include "string_tools.h"

int read_line(FILE* fp, char str[], int n) // (���� ������, ���ڿ��� ������ �迭, ���ڿ��� ũ��)
{
	int ch, i = 0;
	while ((ch = fgetc(fp)) != '\n' && ch != EOF)	// fp���� �о���� ���ڿ��� ����Ű�� �ƴϰ� ������ ���� �ƴ� �� ���� ����
		if (i < n - 1)
			str[i++] = ch; // str[i]�� ch�� �����ϰ� i�� 1 ����

	str[i] = '\0'; // C-style ���ڿ�. �迭�� �������� null ���� ����
	return i; // �� ���ڸ� �о����� ����
}