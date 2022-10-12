//테스트 결과 데이터 출력 완료
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

int main(void) {
    vector <int> v;
    int arr_len, num;
    printf("배열의 크기: ");
    scanf("%d", &arr_len);

    printf("데이터 입력: ");
    for (int i = 0; i < arr_len; i++){
        scanf("%d", &num);
        v.push_back(num); //마지막 자리부터 데이터 추가
    }

    sort(v.begin(), v.end()); //벡터 정렬
    v.erase(unique(v.begin(), v.end()), v.end()); //중복되는 값 제거

    printf("%d: ", v.size()); //정렬 & 중복 제거를 마친 후 배열의 크기 출력
    for (int i = 0; i < v.size(); i++) { //배열 출력
        printf("%d ", v[i]);
    }

    return 0;
}