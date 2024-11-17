#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>

using namespace std;

//  프로그램 실행 함수
//  입력값을 파일로 전달하고 해당 프로그램을 실행한 후 결과를 문자열로 반환
string runProgram(const string& filename, int input) {
    // 입력값을 test_input.txt에 기록
    ofstream inputFile("test_input.txt");
    inputFile << input << endl; // 입력값을 파일에 작성
    inputFile.close();

    // 프로그램 실행 명령어 생성
    string command = filename + " < test_input.txt 2>&1"; // 입력값을 파일에서 읽고, 표준 출력을 캡처
    char buffer[128];
    string result = "";
    FILE* pipe = _popen(command.c_str(), "r"); // 명령어 실행 결과를 읽을 파이프 생성
    if (!pipe) {
        return "Error opening program."; // 파이프 생성 실패 시 에러 메시지 반환
    }

    // 파이프에서 데이터를 읽어서 결과에 추가
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result += buffer;
    }

    _pclose(pipe); // 파이프 닫기
    return result; // 프로그램 실행 결과 반환
}

// 주어진 코드 내용을 지정된 파일에 작성하는 함수
void writeCodeToFile(const string& code, const string& filename) {
    ofstream outFile(filename);
    if (outFile.is_open()) {
        outFile << code; // 파일에 코드 작성
        outFile.close(); // 파일 닫기
    } else {
        cout << "파일을 열 수 없습니다!" << endl;
    }
}



int main() {
    string correctCode, wrongCode;
    int minInput, maxInput;

    // 사용자로부터 올바른 코드 입력 받기
    cout << "올바른 코드의 내용을 입력하세요. (종료하려면 'done' 입력): " << endl;
    string line;
    while (getline(cin, line)) {
        if (line == "done") break; // 'done'을 입력하면 종료
        correctCode += line + "\n"; // 입력받은 각 줄을 코드에 추가
    }

    // 사용자로부터 잘못된 코드 입력 받기
    cout << "잘못된 코드의 내용을 입력하세요. (종료하려면 'done' 입력): " << endl;
    while (getline(cin, line)) {
        if (line == "done") break; // 'done'을 입력하면 종료
        wrongCode += line + "\n"; // 입력받은 각 줄을 코드에 추가
    }

    // 사용자로부터 테스트할 입력 범위 받기
    cout << "테스트할 최소 입력값을 입력하세요: ";
    cin >> minInput; // 최소 입력값
    cout << "테스트할 최대 입력값을 입력하세요: ";
    cin >> maxInput; // 최대 입력값

    // 입력받은 코드를 파일에 작성
    writeCodeToFile(correctCode, "correct_program.cpp");
    writeCodeToFile(wrongCode, "wrong_program.cpp");

    // 두 코드 파일을 컴파일
    system("g++ correct_program.cpp -o correct_program.exe"); // 올바른 코드 컴파일
    system("g++ wrong_program.cpp -o wrong_program.exe");     // 잘못된 코드 컴파일

    // 입력값을 범위 내에서 하나씩 테스트
    for (int i = minInput; i <= maxInput; ++i) {
        // 올바른 코드와 잘못된 코드를 실행하고 출력 결과를 가져오기
        string correctOutput = runProgram("correct_program.exe", i);
        string wrongOutput = runProgram("wrong_program.exe", i);

        // 출력값 비교
        if (correctOutput != wrongOutput) {
            // 출력값이 다르면 반례 발견
            cout << "입력에 대한 반례 발견!" << endl;
            cout << "입력값: " << i << endl; // 입력값 출력
            cout << "올바른 코드 출력: " << correctOutput << endl; // 올바른 코드 출력
            cout << "잘못된 코드 출력: " << wrongOutput << endl; // 잘못된 코드 출력
            return 0; // 반례가 발견되면 프로그램 종료
        }
    }

    // 반례를 찾지 못한 경우
    cout << "반례없음" << endl;
    return 0;
}
