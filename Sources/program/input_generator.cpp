#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <random> 
#include <chrono>

using namespace std;

int main() {
    // 현재 시간의 밀리초를 기반으로 시드 생성
    unsigned seed = chrono::steady_clock::now().time_since_epoch().count();
    srand(seed); 

    int N = rand() % 10 + 1; 
    cout << N << endl;

    vector<int> students;
    for (int i = 1; i <= N; ++i) {
        students.push_back(i);  
    }


    random_device rd;  
    mt19937 gen(rd()); 
    shuffle(students.begin(), students.end(), gen);

    for (int i = 0; i < N; ++i) {
        cout << students[i] << " ";  
    }
    cout << endl;

    return 0;
}

