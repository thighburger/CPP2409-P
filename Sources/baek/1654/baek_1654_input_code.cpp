#include <iostream>
#include <random>
#include <chrono>

using namespace std;

int main() {
    unsigned seed = chrono::steady_clock::now().time_since_epoch().count();
    srand(seed);

    int N = rand() %100 + 1;
    int K = rand() %100 + 1;
    cout << N << " " << K << endl;
    for(int i=0;i<N;i++)
        cout<<rand()%100<<endl;
    return 0;
}
