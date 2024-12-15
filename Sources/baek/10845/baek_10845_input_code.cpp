#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <random>
#include <string>
#include <chrono>

using namespace std;

int main(int argc, char* argv[]) {
    // 명령 개수 설정 (명령행 인자로 받을 수 있도록 수정)
    int N;
    if (argc > 1) {
        try {
            N = stoi(argv[1]); // 명령행 인자 파싱
            if (N < 1 || N > 10000) {
                cerr << "Error: N must be between 1 and 10000." << endl;
                return 1;
            }
        } catch (const std::invalid_argument& e) {
            cerr << "Error: Invalid argument for N." << endl;
            return 1;
        }
    } else {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distrib(1, 10);
        N = distrib(gen);
    }
    cout << N << endl;

    // 난수 생성 엔진 초기화
    random_device rd;
    mt19937 gen(rd());

    // 명령어 목록
    vector<string> commands = {"push", "pop", "size", "empty", "front", "back"};
    uniform_int_distribution<> command_distrib(0, commands.size() - 1);
    uniform_int_distribution<> value_distrib(1, 1000);

    for (int i = 0; i < N; ++i) {
        string command = commands[command_distrib(gen)];
        cout << command;
        if (command == "push") {
            cout << " " << value_distrib(gen);
        }
        cout << endl;
    }

    return 0;
}
