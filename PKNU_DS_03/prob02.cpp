//�׽�Ʈ ��� ������ ��� ����
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define INTERVAL_SIZE 256

//���� �޼���
void sort(int inter_amt, int inter0[], int inter1[]);
void dup_sort(int arr_len, int arr0[], int arr1[]);

int main(void) {
	int inter0[INTERVAL_SIZE];
	int inter1[INTERVAL_SIZE];
	int inter_amt;

	printf("������ ���� �Է�: ");
	scanf("%d", &inter_amt);
	
	printf("������ �������� �� ���� %d�� �Է�\n", inter_amt);
	for (int i = 0; i < inter_amt; i++) {
		scanf("%d", &inter0[i]);
		scanf("%d", &inter1[i]);
	}

	sort(inter_amt, inter0, inter1);
	dup_sort(inter_amt, inter0, inter1);

	printf("\n");
	for (int i = 0; i < inter_amt; i++) {
		printf("%d %d\n", inter0[i], inter1[i]);
	}

	return 0;
}

//���� �˰��� 
void sort(int arr_len, int arr0[], int arr1[]) {
	for (int i = 0; i < arr_len; i++) {
		for (int j = 0; j < arr_len - 1; j++) {
			if (arr0[j] > arr0[j + 1]) {
				int tmp = arr0[j];
				arr0[j] = arr0[j + 1];
				arr0[j + 1] = tmp;
				
				//������ �������� �پ� �ٴ� 
				tmp = arr1[j];
				arr1[j] = arr1[j + 1];
				arr1[j + 1] = tmp;
			}
		}
	}
}

//�������� ���� ��� ������ ���� ���� ���� ��µǰ� �Ѵ�
void dup_sort(int arr_len, int arr0[], int arr1[]) {
	for (int i = 0; i < arr_len; i++) {
		if (arr0[i] == arr0[i + 1] && arr1[i] > arr1[i + 1]) {
			int tmp = arr1[i];
			arr1[i] = arr1[i + 1];
			arr1[i + 1] = tmp;
		}
	}
}