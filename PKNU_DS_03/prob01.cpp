//�׽�Ʈ ��� ������ ��� ����
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define BUFFER_SIZE 100

int main(void) {
	int arr_len;
	int arr[BUFFER_SIZE];
	printf("�迭�� ����: ");
	scanf("%d", &arr_len);

	printf("���� �Է�\n");
	for(int i = 0; i < arr_len; i++) {
		scanf("%d", &arr[i]);
	}
	
	//�ִ� ã�� 
	int max_num;
	for (int i = 0; i < arr_len; i++) {
		int max = 0;
		//���� ū ������ ã�´�
		for (int j = 0; j < arr_len-i; j++) {
			if (arr[j] > max) {
				max = arr[j];
				max_num = j; //max�� �迭�� ��ȣ ����
			}
		}
		//arr[max_num]�� arr[(arr_len-1)-i] swap
		int tmp = arr[max_num];
		arr[max_num] = arr[(arr_len - 1) - i];
		arr[(arr_len - 1) - i] = tmp;
	}

	for (int i = 0; i < arr_len; i++) {
		printf("%d ", arr[i]);
	}
	
	return 0;
}