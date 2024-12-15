#include <iostream>
#include <random>
#include <ctime>
#include <chrono>

using namespace std; // std 네임스페이스 사용 선언

int main() {
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    srand(seed);

    int n = (rand() % 100) + 1;
    cout << n << endl;

    for (int i = 0; i < n; ++i) {
        cout << (rand() % 100) + 1 << " ";
    }
    cout << endl;

    return 0;
}