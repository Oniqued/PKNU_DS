//�׽�Ʈ ��� ������ ��� �Ϸ�
#include<stdio.h>

int main() {
	int num;
	int data[100];
	int tmp;

	while (1) {
		printf("Enter the number of data you want to compare (2 <= n <= 100): ");
		scanf_s("%d", &num); //����ڷκ��� �Էµ� ������ ������ �Է� �޴´�
		if (num < 2) { //���ǿ� ��ġ ���� ���� �� ����
			printf("num must be over 1\n");
		}
		else if (num > 100) {
			printf("num must be under 101\n");
		}
		else { //���ǿ� ��ġ �ϸ� �ݺ��� Ż�� 
			break;
		}
	}
	for (int i = 0; i < num; i++) { //�Էµ� ������ ���� ��ŭ �ݺ�
		scanf_s("%d", &data[i]);
	}

	for (int i = 0; i < num; i++) { //���� �˰��� 
		for (int j = i + 1; j < num; j++) { //�迭�� ���̸�ŭ �ݺ���
			if (data[i] > data[j]) { //[i]�� ���� [j]���� ũ�� ���� ����
				tmp = data[i];
				data[i] = data[j];
				data[j] = tmp;
			}
		}
	}

	printf("%d %d", data[0], data[1]);

	return 0;
}