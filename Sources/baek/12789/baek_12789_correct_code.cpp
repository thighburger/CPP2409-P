#include <iostream>

#define endl "\n"
#define fastio() ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

using namespace std;

int n, k;

//이진수 표현 1 비트 카운트
int bitCount(int x){
    if(x == 0) return 0;
    return x % 2 + bitCount(x/2);
}

void solve(){
    for(int i =0;;i++){
        //전체 1 비트 카운트가 k보다 작거나 같으면 k개의 물병보다 적으므로 한번에 이동 가능
        if(bitCount(n) <= k){
            cout << i;
            return ;
        }
        n++;
    }
}

int main(){
    fastio();
    cin >> n >> k;
    solve();
}