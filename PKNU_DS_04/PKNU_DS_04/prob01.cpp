//�׽�Ʈ ��� ������ ��� ����
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define ARR_SIZE 100

int length;
int length_XY = 0;
int arr_main[ARR_SIZE];
int arrX[ARR_SIZE];
int arrY[ARR_SIZE];

void find_inverse();

int main(void) {

	printf("������ ���� �Է�: ");
	scanf("%d", &length);
	
	for (int i = 0; i < length; i++) {
		scanf("%d", &arr_main[i]);
	}

	find_inverse();
	printf("%d", length_XY);

	return 0;
}

void find_inverse() {
	for (int i = 0; i < length; i++) {
		for (int j = i + 1; j < length; j++) {
			if (arr_main[i] > arr_main[j]) {
				arrX[length_XY] = arr_main[i];
				arrY[length_XY] = arr_main[j];
				length_XY++;
			}
		}
	}
}