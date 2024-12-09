#include <iostream>
#include <fstream>
#include <string>

using namespace std;
void copy(string &sourceFile,string &destinationFile){
    // 원본 파일 열기
    ifstream source(sourceFile, ios::in);
    if (!source) {
        cerr << "원본 파일을 열 수 없습니다." << endl;
        exit(0);
    }
    ofstream destination(destinationFile, ios::out);
    if (!destination) {
        cerr << "복사 파일을 열 수 없습니다." << endl;
        exit(0);
    }
    string line;
    while (getline(source, line)) {
        destination << line << endl;
    }

    // 파일 닫기
    source.close();
    destination.close();

    cout << "불러오기가 완료되었습니다." << endl;
}

int main() {
    
    int Number;
    cout<<"문제 번호를 입력해 주세요: ";
    cin>>Number;

    string sourceFile = "..\\baek\\"+to_string(Number)+"\\baek_"+to_string(Number)+"_wrong_code.cpp";  
    string destinationFile = "wrong_program.cpp";  
    copy(sourceFile,destinationFile);

    sourceFile = "..\\baek\\"+to_string(Number)+"\\baek_"+to_string(Number)+"_correct_code.cpp";  
    destinationFile = "correct_program.cpp"; 
    copy(sourceFile,destinationFile);

    sourceFile = "..\\baek\\"+to_string(Number)+"\\baek_"+to_string(Number)+"_input_code.cpp";  
    destinationFile = "input_generator.cpp"; 
    copy(sourceFile,destinationFile);
    

    return 0;
}
