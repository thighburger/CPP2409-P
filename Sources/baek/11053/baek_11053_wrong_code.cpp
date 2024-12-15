#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<int> vec(n);
    vector<int> value;
    vector<int> count;

    for (int i = 0; i < n; i++)
        cin >> vec[i];

    value.push_back(vec[0]);
    count.push_back(1);

    for (int i = 1; i < n; i++)
    {
        bool isExist = false;

        for (int j = 0; j < value.size(); j++)
        {
            if (value[j] < vec[i])
            {
                value[j] = vec[i];
                count[j]++;

                isExist = true;
            }
        }

        if (!isExist)
        {
            value.push_back(vec[i]);
            count.push_back(1);
        }
    }

    int max = 0;

    for (int i = 0; i < count.size(); i++)
    {
        if (count[i] > max)
            max = count[i];
    }

    cout << max;

    return 0;
}