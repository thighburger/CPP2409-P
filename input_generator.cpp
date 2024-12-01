#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    
    srand(time(0));

    
    int N = rand() % 10 + 1; 
    cout << N << endl;

    vector<int> students;
    for (int i = 1; i <= N; ++i) {
        students.push_back(i);  
    }

    
    random_shuffle(students.begin(), students.end());
    for (int i = 0; i < N; ++i) {
        cout << students[i] << " ";  
    }
    cout << endl;

    return 0;
}
