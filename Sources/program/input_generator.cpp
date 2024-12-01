#include <iostream>
#include <random>
#include <chrono>

using namespace std;

int main() {
    // 현재 시간의 밀리초를 기반으로 시드 생성
    unsigned seed = chrono::steady_clock::now().time_since_epoch().count();
    srand(seed);

    int N = rand() %30 + 1;
    int K = rand() % 10 + 1;
    cout << N << " " << K << endl;

    return 0;
}
