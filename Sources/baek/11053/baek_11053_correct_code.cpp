#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int n,m;
int dp[1001],arr[1001];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;

    //memset(dp, 1, sizeof(dp));

    for(int i=0; i<n ;i++) {
        cin >> arr[i];
    }

    int sum=0;
    for (int i = 0; i < n; i++) {
        dp[i] = 1;
        for (int j = 0; j < i; j++) {
            if (arr[i] > arr[j]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        sum = max(sum, dp[i]);
    }
    
    cout << sum;
    return 0;
}