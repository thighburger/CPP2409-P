#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <filesystem>
#include <vector>
#include <algorithm>

using namespace std;
namespace fs = std::filesystem;

// 주어진 코드 내용을 파일에 작성하는 함수
void writeCodeToFile(const string& code, const string& filename) {
    ofstream outFile(filename); // 파일을 쓰기 모드로 열기
    if (outFile.is_open()) {
        outFile << code; // 코드 내용을 파일에 쓰기
        outFile.close(); // 파일 닫기
    } else {
        cout << filename << " 파일을 열 수 없습니다!" << endl; // 파일 열기 실패 메시지 출력
    }
}

// 프로그램 실행 함수 (입력 리디렉션 및 오류 스트림 처리)
string runProgram(const string& filename, const string& input) {
    ofstream inputFile("test_input.txt"); // 임시 입력 파일 생성
    inputFile << input; // 입력 내용을 파일에 쓰기
    inputFile.close(); // 파일 닫기

    // 프로그램 실행 및 출력/오류 스트림 리디렉션
    string command = filename + " < test_input.txt 2>&1"; // 표준 입력 리디렉션 및 표준 에러를 표준 출력으로 병합
    FILE* pipe = _popen(command.c_str(), "r"); // 파이프를 통해 명령 실행 결과 읽기
    if (!pipe) {
        return "Error opening program."; // 프로그램 실행 실패 시 오류 메시지 반환
    }

    string result;
    char buffer[128];
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) { // 파이프에서 결과 읽기
        result += buffer;
    }

    _pclose(pipe); // 파이프 닫기
    return result; // 실행 결과 반환
}

// 입력 생성기 실행 함수
string generateInput() {
    string command = "input_generator.exe"; // 입력 생성기 실행 명령
    FILE* pipe = _popen(command.c_str(), "r"); // 파이프를 통해 명령 실행 결과 읽기
    if (!pipe) {
        return "Error generating input."; // 입력 생성 실패 시 오류 메시지 반환
    }

    string result;
    char buffer[128];
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) { // 파이프에서 결과 읽기
        result += buffer;
    }

    _pclose(pipe); // 파이프 닫기
    return result; // 생성된 입력 반환
}

// 코드 설정 함수 (올바른 코드, 잘못된 코드, 입력 생성기 코드 선택)
void setupPrograms() {
    string code;
    int choice;

    cout << "어떤 코드를 입력하시겠습니까?" << endl;
    cout << "1. 올바른 코드 입력" << endl;
    cout << "2. 잘못된 코드 입력" << endl;
    cout << "3. 입력 생성기 코드 입력" << endl;
    cout << "0. 뒤로가기" << endl;
    cout << "선택: ";
    cin >> choice; // 사용자 선택 입력
    cin.ignore(); // 입력 버퍼 비우기

    if (choice == 0) return; // 뒤로가기
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
    while (getline(cin, line)) { // 한 줄씩 입력 받기
        if (line == "done") break; // 'done' 입력 시 입력 종료
        code += line + "\n"; // 입력된 코드에 추가
    }

    string filename;
    if (choice == 1) {
        filename = "correct_program.cpp";
    } else if (choice == 2) {
        filename = "wrong_program.cpp";
    } else {
        filename = "input_generator.cpp";
    }

    writeCodeToFile(code, filename); // 코드 파일에 쓰기
    cout << "코드 설정 완료!" << endl;
}

// 반례 찾기 함수 (무작위 입력 생성 및 두 프로그램의 출력 비교)
void findCounterexample() {
    int testCount;
    cout << "테스트 반복 횟수를 입력하세요 (0 입력 시 뒤로가기): ";
    cin >> testCount; // 테스트 횟수 입력
    cin.ignore(); // 입력 버퍼 비우기
    if (testCount == 0) return;

    for (int i = 0; i < testCount; ++i) {
        string input = generateInput(); // 입력 생성
        cout << "생성된 입력:\n" << input << endl;

        string correctOutput = runProgram("correct_program.exe", input); // 올바른 프로그램 실행
        string wrongOutput = runProgram("wrong_program.exe", input); // 잘못된 프로그램 실행

        if (correctOutput != wrongOutput) { // 출력이 다를 경우 반례 발견
            cout << "반례 발견!" << endl;
            cout << "입력값:\n" << input << endl;
            cout << "올바른 코드 출력: \n" << correctOutput << endl;
            cout << "잘못된 코드 출력: \n" << wrongOutput << endl;
            return; // 반례 발견 시 함수 종료
        }
    }

    cout << "반례를 찾지 못했습니다." << endl; // 지정된 횟수 동안 반례를 찾지 못한 경우
}

// 파일 복사 함수
void copy(string &sourceFile, string &destinationFile) {
    ifstream source(sourceFile, ios::in); // 원본 파일 읽기 모드로 열기
    if (!source) {
        cerr << "원본 파일을 열 수 없습니다." << endl;
        exit(0);
    }
    ofstream destination(destinationFile, ios::out); // 복사 파일 쓰기 모드로 열기
    if (!destination) {
        cerr << "복사 파일을 열 수 없습니다." << endl;
        exit(0);
    }
    string line;
    while (getline(source, line)) { // 원본 파일에서 한 줄씩 읽어 복사 파일에 쓰기
        destination << line << endl;
    }

    source.close(); // 원본 파일 닫기
    destination.close(); // 복사 파일 닫기
}

// 기존 파일 불러오기 함수
void loadExistingFiles() {
    int Number;
    cout << "문제 번호를 입력해 주세요 (0 입력 시 뒤로가기): ";
    cin >> Number; // 문제 번호 입력
    string basePath = "..\\baek\\" + to_string(Number); // 문제 파일 경로 생성

    if (Number == 0) return;
    // 문제 번호 디렉토리 확인
    if (!fs::exists(basePath) || !fs::is_directory(basePath)) {
        cout << "저장된 문제가 아닙니다." << endl;
        return;
    }

    // 각 코드 파일 복사
    string sourceFile = "..\\baek\\" + to_string(Number) + "\\baek_" + to_string(Number) + "_wrong_code.cpp";
    string destinationFile = "wrong_program.cpp";
    copy(sourceFile, destinationFile);

    sourceFile = "..\\baek\\" + to_string(Number) + "\\baek_" + to_string(Number) + "_correct_code.cpp";
    destinationFile = "correct_program.cpp";
    copy(sourceFile, destinationFile);

    sourceFile = "..\\baek\\" + to_string(Number) + "\\baek_" + to_string(Number) + "_input_code.cpp";
    destinationFile = "input_generator.cpp";
    copy(sourceFile, destinationFile);

    cout << "불러오기가 완료되었습니다." << endl;
}

// 문제 파일 목록을 오름차순으로 정렬하여 나열하는 함수
void listProblemFiles() {
    string path = "..\\baek\\"; // 문제 파일 경로
    vector<int> problemNumbers; // 문제 번호 저장 벡터

    cout << "문제 파일 목록:" << endl;

    // 디렉토리 탐색
    for (const auto& entry : fs::directory_iterator(path)) {
        if (fs::is_directory(entry)) { // 디렉토리인 경우
            string dirName = entry.path().filename().string(); // 디렉토리 이름 가져오기
            try {
                int problemNumber = stoi(dirName); // 디렉토리 이름을 정수로 변환
                problemNumbers.push_back(problemNumber); // 문제 번호 벡터에 추가
            } catch (const invalid_argument& e) {

    // 디렉토리 이름이 숫자가 아닐 경우 무시
                cout<<"숫자로 입력해주세요"<<endl;
                continue;
            }
        }
    }

    // 문제 번호 오름차순으로 정렬
    sort(problemNumbers.begin(), problemNumbers.end());

    // 정렬된 문제 번호 출력
    for (const auto& problem : problemNumbers) {
        cout << "문제 번호: " << problem << endl;
    }
}

// 파일 내용 읽기 함수
string readFile(const string& filename) {
    ifstream inFile(filename); // 파일을 읽기 모드로 열기
    if (inFile.is_open()) {
        string content((istreambuf_iterator<char>(inFile)), (istreambuf_iterator<char>())); // 파일 내용 전체 읽기
        inFile.close(); // 파일 닫기
        return content; // 파일 내용 반환
    } else {
        cerr << filename << " 파일을 열 수 없습니다!" << endl; // 파일 열기 실패 메시지 출력
        return "";
    }
}

// 코드 저장 함수 
void saveExistingPrograms() {
    int problemNumber;
    cout << "저장할 문제 번호를 입력하세요(0 입력 시 뒤로가기기): ";
    cin >> problemNumber; // 문제 번호 입력
    cin.ignore(); // 입력 버퍼 비우기

    if (problemNumber==0) return;
    string basePath = "..\\baek\\" + to_string(problemNumber); // 저장 경로 생성

    // 디렉토리 생성 (존재하지 않을 경우)
    if (!fs::exists(basePath)) {
        if (fs::create_directory(basePath)) { // 디렉토리 생성 시도
            cout << "새 디렉토리를 생성했습니다: " << basePath << endl;
        } else {
            cerr << "디렉토리 생성에 실패했습니다." << endl;
            return;
        }
    }
    else {
        cout << "기존 디렉토리에 저장합니다 : " << basePath << endl;
    }

    // 각 코드 파일 읽기 및 저장
    vector<string> filenames = { // 저장될 파일 이름 목록
        "baek_" + to_string(problemNumber) + "_correct_code.cpp",
        "baek_" + to_string(problemNumber) + "_wrong_code.cpp",
        "baek_" + to_string(problemNumber) + "_input_code.cpp"
    };
    vector<string> sourceFilenames = { // 원본 파일 이름 목록
        "correct_program.cpp",
        "wrong_program.cpp",
        "input_generator.cpp"
    };

    for (size_t i = 0; i < filenames.size(); ++i) {
        string code = readFile(sourceFilenames[i]); // 파일 내용 읽기
        if (code.empty()) {
            cerr << sourceFilenames[i] << " 파일 읽기 실패. 저장을 건너뜁니다." << endl;
            continue; // 파일 읽기 실패 시 다음 파일로 진행
        }

        string fullPath = basePath + "\\" + filenames[i]; // 전체 경로 생성
        writeCodeToFile(code, fullPath); // 파일에 코드 쓰기
        if (fs::exists(fullPath)) //파일 저장 성공여부 확인 후 메세지 출력
            cout << filenames[i] << " 저장 완료!" << endl;
        else
            cout << filenames[i] << " 저장 실패!" << endl;
    }
    cout << "모든 코드 저장이 완료되었습니다." << endl;
}

// 도움말 출력 함수
void showHelp() {
    cout << "\n======== 프로그램 도움말 ========" << endl;
    cout << "1. 프로그램 설정" << endl;
    cout << "   - 올바른 코드, 잘못된 코드, 입력 생성기 코드를 입력합니다." << endl;
    cout << "   - 입력이 끝나면 'done'을 입력하여 종료합니다." << endl;
    cout << "   - 모든 코드를 작성하였다면 컴파일을 해주세요." << endl;

    cout << "\n2. 기존 파일 불러오기" << endl;
    cout << "   - 이미 저장된 문제 번호를 입력하면 해당 문제의 코드가 불러와집니다." << endl;
    cout << "   - 불러오기 후후 컴파일을 해주세요." << endl;

    cout << "\n3. 반례 찾기" << endl;
    cout << "   - 입력 생성기를 통해 무작위 입력을 생성하고" << endl;
    cout << "     두 프로그램의 출력을 비교하여 반례를 찾습니다." << endl;

    cout << "\n4. 컴파일" << endl;
    cout << "   - 작성한 코드를 g++ 컴파일러를 통해 실행 파일로 컴파일합니다." << endl;

    cout << "\n5. 저장된 문제 목록 보기" << endl;
    cout << "   - 저장된 문제의 번호를 오름차순으로 나열합니다." << endl;

    cout << "\n6. 저장하기" << endl;
    cout << "   - 현재 작성된 올바른 코드, 잘못된 코드, 입력 생성기 코드를" << endl;
    cout << "     특정 문제 번호의 폴더에 저장합니다." << endl;

    cout << "\n7. 종료" << endl;
    cout << "   - 프로그램을 종료합니다." << endl;

    cout << "\n8. 도움말 보기" << endl;
    cout << "   - 이 도움말을 출력합니다." << endl;

    cout << "==================================" << endl;
}

int main() {
    cout<<"*******주의사항:모든 코드를 작성하였다면 컴파일을 해주세요.(불러오기도 마찬가지)*******"<<endl;
    while (true) {
        cout << "\n\n메뉴:" << endl;
        cout << "1. 프로그램 설정" << endl;
        cout << "2. 기존 파일 불러오기" << endl;
        cout << "3. 반례 찾기" << endl;
        cout << "4. 컴파일" << endl;
        cout << "5. 저장된 문제 목록 보기" << endl;
        cout << "6. 저장하기" << endl; 
        cout << "7. 종료" << endl;
        cout << "8. 도움말" << endl;

        cout << "선택: ";
        int choice;
        cin >> choice; // 메뉴 선택 입력
        cin.ignore(); // 입력 버퍼 비우기

        if (choice == 1) {
            setupPrograms(); // 프로그램 설정 함수 호출
        } else if (choice == 2) {
            loadExistingFiles(); // 기존 파일 불러오기 함수 호출
        } else if (choice == 3) {
            findCounterexample(); // 반례 찾기 함수 호출
        } else if (choice == 4) {
            system("g++ correct_program.cpp -o correct_program.exe"); // 올바른 프로그램 컴파일
            cout << "1/3 완료" << endl;
            system("g++ wrong_program.cpp -o wrong_program.exe"); // 잘못된 프로그램 컴파일
            cout << "2/3 완료" << endl;
            system("g++ input_generator.cpp -o input_generator.exe"); // 입력 생성기 컴파일
            cout << "3/3 완료" << endl;
            cout << "컴파일 완료!" << endl;
            cout << "프로그램을 종료합니다 다시 시작해주세요.";
            break;//컴파일 후 프로그램 종료
        } else if (choice == 5) {
            listProblemFiles(); // 저장된 문제 목록 보기 함수 호출
        } else if (choice == 6) { // 저장 기능 호출
            saveExistingPrograms();
        } else if (choice == 7) {
            cout << "프로그램을 종료합니다." << endl;
            break; // 프로그램 종료
        } else if (choice == 8) {
            showHelp(); // 도움말 출력
        } else {
            cout << "잘못된 선택입니다. 다시 시도하세요." << endl;
        }
    }

    return 0;
}
























