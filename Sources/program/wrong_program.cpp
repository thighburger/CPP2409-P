#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;

string bitconvert(int num) {
    if (num == 0) return "0";
    string output ="";
    while (num > 0) {
        output += (num%2 == 0 ? '0' : '1');
        num /= 2;
    }
    reverse(output.begin(), output.end());
    return output;
}

int decimalconvert(string bit) {
    int output = 0;
    for (int i = 0; i < bit.length(); i++) {
        output += (bit[bit.length()-i-1] == '0' ? 0 : 1) * pow(2,i);
    }
    return output;
}

int main() {
    int n, k;
    cin >> n >> k;
    
    string inputbit = bitconvert(n); // n 2 
    string sample(inputbit.length(), '0'); //  n  
    
    int inum = 0; //1  
    bool needsExtraDigit = false;
    bool first = true;
    for (int i = 0; i < inputbit.length(); i++) {
        if (inputbit[i] == '1') inum++; // 1  count
        if (inum < k) sample[i] = inputbit[i];
        if (inum == k && first == true) {
            int index = i;
            //   
            while (index >= 0 && inputbit[index] == '1') {
                index--;
            }
            if (index < 0) {
                needsExtraDigit = true;
            } else {
                sample[index] = '1';
            }
            first = false;
        }
    }
    // cout << "inputbit: " << inputbit << endl;
    // cout << "sample:   " << sample << endl;


    
    
    if (inum <= k || n <= k) cout << 0;
    else {
        if (needsExtraDigit) sample = "1" + string(inputbit.length(), '0');
        cout << decimalconvert(sample) - n;
    }
    return 0;
}
