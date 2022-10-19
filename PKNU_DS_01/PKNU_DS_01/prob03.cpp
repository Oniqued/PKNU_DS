#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define BUFFER_SIZE 100

int main() {
	int num;
	int arr[BUFFER_SIZE];
	bool isDup;
	int n = 0;

	while(scanf("%d", &num) != EOF){
		if (num == -1) return 0;
		isDup = false;
		//중복 검사
		for (int i = 0; i < n; i++) {
			if (arr[i] == num) {
				printf("duplicate\n");
				isDup = true;
				continue;
			}
		}
		if (isDup == false) {
			arr[n] = num;
			n++;
			for (int i = 0; i < n; i++) {
				for (int j = i + 1; j < n; j++) {
					if (arr[i] > arr[j]) {
						int tmp = arr[i];
						arr[i] = arr[j];
						arr[j] = tmp;
					}
				}
			}
			for (int i = 0; i < n; i++) {
				printf("%d ", arr[i]);
			}
			printf("\n");
		}
	}

	return 0;
}