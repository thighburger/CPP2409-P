#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

int main() {
    static int N = 1;  // N의 초기값을 1로 설정

    // N의 범위 설정 (1부터 1000까지)
    if (N > 1000) {
        cout << "N의 값이 범위를 초과했습니다." << endl;
        return 0;
    }

    cout << "현재 N의 값: " << N << endl;
    cout << "학생들의 번호: ";
    
    // 학생들의 번호 생성 (1부터 N까지)
    for (int i = 1; i <= N; ++i) {
        cout << i << " ";  // 번호 출력
    }
    cout << endl;

    N++;  // N 값을 1 증가시킴

    return 0;
}


