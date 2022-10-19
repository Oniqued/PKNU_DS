//�׽�Ʈ ������ ��� ��� �Ϸ� 
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


double prob(int N, int k) {
	int test_time = 1000000; //���� �ݺ� Ƚ��
	int dice; 
	int dice_1 = 0;
	double result;
	double tmp = 0;
	
	for (int i = 0; i < test_time; i++) {
		for (int j = 0; j < N; j++) { //�Է� Ƚ����ŭ �ֻ����� ������
			dice = (int)(rand() % 6 + 1); //�ֻ����� ������
			if (dice == 1) { //�ֻ������� 1 ���� Ƚ�� ����
				dice_1++;
			}
		}
		if (dice_1 < k) { //1�� ���� Ƚ���� k���� ������ Ȯ���� �ݿ�
			tmp++;
		}
		dice_1 = 0; //�ֻ������� 1�� ���� Ƚ�� �ʱ�ȭ
	}
	result = 1 - (tmp / test_time); //��ü Ȯ������ ��� k�� 1�� ���� Ȯ��
	return result;
}

int main(void) {
	int roll, times;
	srand((unsigned int)time(NULL)); //���� ������ ���� �Լ�
	
	while (1) { //����ڰ� �ùٸ� ���� �Է����� ������ �Է��� �ٽ� ��û
		printf("�ֻ����� ������ Ƚ��(6�� ����� �Է�, 36����): ");
		scanf("%d", &roll);
		if (roll % 6 != 0) {
			printf("6�ǹ���� �Է��Ͻʽÿ�\n");
			continue;
		}
		else if(roll > 36) {
			printf("36������ ���ڸ� �Է��Ͻʽÿ�\n");
		}
		else {
			times = roll / 6;
			break;
		}
	}

	printf("%f", prob(roll, times)); //�Լ� �������� ���

	return 0;
}
