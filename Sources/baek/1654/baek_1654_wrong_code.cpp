#include <iostream>
#include <algorithm>
#include <tuple>
#include <string>
#include <vector>
using namespace std;

long long BinarySearch(const vector<long long>& lineVec, long long N, long long left, long long right)
{
    if (left >= right)
    {
        return right;
    }

    long long mid = (left + right) / 2;
    long long cnt = 0;
    for (long long i = 0; i < lineVec.size(); ++i)
    {
        cnt += lineVec[i] / mid;
    }

    if (N <= cnt)
    {
        return BinarySearch(lineVec, N, mid + 1, right);
        
    }
    else
    {
        return BinarySearch(lineVec, N, left, mid - 1);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    long long K, N;
    cin >> K >> N;

    vector<long long> lineVec;
    long long num;
    long long maxSize = 0;
    for (long long i = 0; i < K; ++i)
    {
        cin >> num;
        lineVec.push_back(num);
        maxSize = max(num, maxSize);
    }

    cout << BinarySearch(lineVec, N, 1, maxSize);

    return 0;
}