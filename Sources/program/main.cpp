#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>

using namespace std;

// 프로그램 실행 함수
string runProgram(const string& filename, const string& input) {
    ofstream inputFile("test_input.txt");
    inputFile << input;
    inputFile.close();

    string command = filename + " < test_input.txt 2>&1";
    FILE* pipe = _popen(command.c_str(), "r");
    if (!pipe) {
        return "Error opening program.";
    }

    string result;
    char buffer[128];
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) { 
        result += buffer;
    }

    _pclose(pipe);
    return result;
}

// 입력 생성기 실행 함수
string generateInput() {
    string command = "input_generator.exe";
    FILE* pipe = _popen(command.c_str(), "r");
    if (!pipe) {
        return "Error generating input.";
    }

    string result;
    char buffer[128];
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result += buffer;
    }

    _pclose(pipe);
    return result;
}

// 주어진 코드 내용을 파일에 작성하는 함수
void writeCodeToFile(const string& code, const string& filename) {
    ofstream outFile(filename);
    if (outFile.is_open()) {
        outFile << code;
        outFile.close();
    } else {
        cout << "파일을 열 수 없습니다!" << endl;
    }
}

// 코드 설정 함수
void setupPrograms() {
    string code;
    int choice;

    cout << "어떤 코드를 입력하시겠습니까?" << endl;
    cout << "1. 올바른 코드 입력" << endl;
    cout << "2. 잘못된 코드 입력" << endl;
    cout << "3. 입력 생성기 코드 입력" << endl;
    cout << "선택: ";
    cin >> choice;
    cin.ignore();

    if (choice == 1) {
        cout << "올바른 코드의 내용을 입력하세요. (종료하려면 'done' 입력): " << endl;
    } else if (choice == 2) {
        cout << "잘못된 코드의 내용을 입력하세요. (종료하려면 'done' 입력): " << endl;
    } else if (choice == 3) {
        cout << "입력 생성기 코드의 내용을 입력하세요. (종료하려면 'done' 입력): " << endl;
    } else {
        cout << "잘못된 선택입니다." << endl;
        return;
    }

    string line;
    while (getline(cin, line)) {
        if (line == "done") break;
        code += line + "\n";
    }

    string filename;
    if (choice == 1) {
        filename = "correct_program.cpp";
    } else if (choice == 2) {
        filename = "wrong_program.cpp";
    } else {
        filename = "input_generator.cpp";
    }

    writeCodeToFile(code, filename);
    string compileCommand = "g++ " + filename + " -o " + filename.substr(0, filename.find('.')) + ".exe";
    system(compileCommand.c_str());
    cout << "코드 설정 및 컴파일 완료!" << endl;
}

// 반례 찾기 함수
void findCounterexample() {
    int testCount;
    cout << "테스트 반복 횟수를 입력하세요: ";
    cin >> testCount;
    cin.ignore();

    for (int i = 0; i < testCount; ++i) {
        string input = generateInput();
        cout << "생성된 입력:\n" << input << endl;

        string correctOutput = runProgram("correct_program.exe", input);
        string wrongOutput = runProgram("wrong_program.exe", input);

        if (correctOutput != wrongOutput) {
            cout << "반례 발견!" << endl;
            cout << "입력값:\n" << input << endl;
            cout << "올바른 코드 출력: " << correctOutput << endl;
            cout << "잘못된 코드 출력: " << wrongOutput << endl;
            return;
        }
    }

    cout << "반례 없음" << endl;
}

int main() {
    while (true) {
        cout << "메뉴:" << endl;
        cout << "1. 프로그램 설정" << endl;
        cout << "2. 반례 찾기" << endl;
        cout << "3. 종료" << endl;
        cout << "선택: ";
        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            setupPrograms();
            break;
        } else if (choice == 2) {
            findCounterexample();
        } else if (choice == 3) {
            cout << "프로그램을 종료합니다." << endl;
            break;
        } else {
            cout << "잘못된 선택입니다. 다시 시도하세요." << endl;
        }
    }

    return 0;
}





