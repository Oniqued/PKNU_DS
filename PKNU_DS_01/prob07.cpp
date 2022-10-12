//테스트 결과 데이터 출력 완료
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

vector <string> v; //string형 벡터 선언

bool comp(string a, string b) { //단어 길이 비교
	if (a.size() == b.size()) {
		return a < b;
	}
	else {
		return a.size() < b.size();
	}
}

int main() {
	int v_len; 
	printf("입력될 단어 갯수: ");
	scanf("%d ", &v_len);
	v.resize(v_len + 1); //\0

	for (int i = 1; i <= v_len; i++) { //단어 입력
		getline(cin, v[i]); //사용자로부터 v[i]로 단어 입력 받음
	}

	sort(v.begin(), v.end(), comp); //단어 길이순 정렬, 길이가 같다면 사전식 정렬
	printf("-----------\n");
	for (int i = 1; i <= v_len; i++) {
		string tmp = v[i - 1]; // \0
		if (v[i] == tmp) { // \0무시
			continue;
		}
		else {
			cout << v[i] << '\n'; //배열 원소 출력
		}
	}

	return 0;
}