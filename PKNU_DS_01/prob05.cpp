//�׽�Ʈ ��� ������ ��� �Ϸ�
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

int main(void) {
    vector <int> v;
    int arr_len, num;
    printf("�迭�� ũ��: ");
    scanf("%d", &arr_len);

    printf("������ �Է�: ");
    for (int i = 0; i < arr_len; i++){
        scanf("%d", &num);
        v.push_back(num); //������ �ڸ����� ������ �߰�
    }

    sort(v.begin(), v.end()); //���� ����
    v.erase(unique(v.begin(), v.end()), v.end()); //�ߺ��Ǵ� �� ����

    printf("%d: ", v.size()); //���� & �ߺ� ���Ÿ� ��ģ �� �迭�� ũ�� ���
    for (int i = 0; i < v.size(); i++) { //�迭 ���
        printf("%d ", v[i]);
    }

    return 0;
}