//�׽�Ʈ ��� ������ ��� �Ϸ�
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int num, r_num, arr_len; //����� �Է� ������ 
	int n = 0;
	printf("�迭�� ����: ");
	scanf("%d", &arr_len); //�Էµ� ������ ������ �Է� ����
	int* arr= (int*)malloc(arr_len * sizeof(int));
	
	printf("������ �Է�(����� ����, �����ʹ� 9999�� ���� �ʽ��ϴ�): ");
	while (n < arr_len) {
		scanf("%d", &num);
		arr[n] = num;
		n++;
	}
	printf("r_num�� ����� �� ã��\nr_num: ");
	scanf("%d", &r_num);
	
	int buffer, result;
	int comp_num = 9999; //�� �ʱ� ���� 9999
	for (int i = 0; i < arr_len; i++) { //�ݺ����� ���� ������ ���ϰ�, 
		if (r_num > arr[i]) {
			buffer = r_num - arr[i];
		}
		else {
			buffer = arr[i] - r_num;
		}
		if (comp_num >= buffer) { //������ ���� comp_num���� ������ result�� arr[i]�� �ֽ��ϴ�
			comp_num = buffer;
			result = arr[i];
		}
	}
	printf("%d", result); //���� ���̰� ���� ���� arr[i]�� ��µ˴ϴ� 
	

	return 0;
}