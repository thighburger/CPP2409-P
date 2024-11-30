#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    // 랜덤 시드 초기화
    srand(time(0));

    // 학생 수 N을 생성 (1 ≤ N ≤ 1000)
    int N = rand() % 10 + 1;  // 1부터 1000까지의 랜덤 값
    cout << N << endl;

    // 학생들의 번호 생성 (1부터 N까지의 번호)
    for (int i = 1; i <= N; ++i) {
        cout << i << " ";  // 번호 출력
    }
    cout << endl;

    return 0;
}