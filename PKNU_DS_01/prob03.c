//�׽�Ʈ ��� ������ ��� �Ϸ�
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void) {
	int num, tmp;
	int arr[100]; //������ 100�� ���� �����ϴ� �迭
	int buffer[100];
	int n = 0;
	int isDup; //�ߺ� ����
	printf("Enter number\n");
	while (scanf("%d", &num) != EOF) {
		if (num == -1) { //-1�� �ԷµǸ� ���α׷� ����
			break;
		}
		isDup = 0; //�ߺ� false�� �ʱ�ȭ 
		for (int i = 0; i <= n; i++) { //�ߺ� �˻� ����
			if(arr[i] == num) { //num�� arr[i]�� ��ġ�ϸ� �ߺ����� ���
				printf("duplicate\n");
				isDup = 1; //�ߺ� true
				n--; 
				break;
			}
		}
		
		if (isDup == 0) { //�ߺ��� �ƴҶ�, ����
			arr[n] = num; //�ߺ��� �ƴϸ� �Է¹��� ���� �״�� �迭�� ����

			for (int i = 0; i <= n; i++) {
				for (int j = i + 1; j <= n; j++) {
					if (arr[i] > arr[j]) {
						tmp = arr[i];
						arr[i] = arr[j];
						arr[j] = tmp;
					}
				}
			}

			for (int i = 0; i <= n; i++) {
				printf("[%d]", arr[i]);
			}
			printf("\n");
		}
		n++;
	}

	return 0;
}