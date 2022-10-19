#include <stdio.h>

int main() {
	int arr[] = {1,2,3,4,5,6};
	int arrLen = sizeof(arr) / sizeof(int);

	for (int i = 0; i < arrLen; i++) {
		for(int j = i + 1; j < arrLen; j++){
			if (arr[i] < arr[j]) {
				int tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
		}
	}

	for (int i = 0; i < arrLen; i++) {
		printf("%d ", arr[i]);
	}


	return 0;
}