//�׽�Ʈ ��� ������ ��� �Ϸ�
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

vector <string> v; //string�� ���� ����

bool comp(string a, string b) { //�ܾ� ���� ��
	if (a.size() == b.size()) {
		return a < b;
	}
	else {
		return a.size() < b.size();
	}
}

int main() {
	int v_len; 
	printf("�Էµ� �ܾ� ����: ");
	scanf("%d ", &v_len);
	v.resize(v_len + 1); //\0

	for (int i = 1; i <= v_len; i++) { //�ܾ� �Է�
		getline(cin, v[i]); //����ڷκ��� v[i]�� �ܾ� �Է� ����
	}

	sort(v.begin(), v.end(), comp); //�ܾ� ���̼� ����, ���̰� ���ٸ� ������ ����
	printf("-----------\n");
	for (int i = 1; i <= v_len; i++) {
		string tmp = v[i - 1]; // \0
		if (v[i] == tmp) { // \0����
			continue;
		}
		else {
			cout << v[i] << '\n'; //�迭 ���� ���
		}
	}

	return 0;
}