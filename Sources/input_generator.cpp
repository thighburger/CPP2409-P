#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    // `` `` ```
    srand(time(0));

    // �� � N� �� (1   N   1000)
    int N = rand() % 1000 + 1;  // 1`` 1000``` `` `
    cout << N << endl;

    // PPPP PP PP (1PP NPPP PP)
    for (int i = 1; i <= N; ++i) {
        cout << i << " ";  //  
    }
    cout << endl;

    return 0;
}
