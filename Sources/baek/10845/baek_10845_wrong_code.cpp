#include <iostream>
#include <string>
#include <algorithm>
#include <queue>

using namespace std;

int main() {
	int n;
	cin >> n;
	queue<int> q;
	for (int i = 0; i < n; i++)
	{
		string str;
		cin >> str;
		if (str == "push")
		{
			int num;
			cin >> num;
			q.push(num);
		}
		else if (str == "pop")
		{
			if (!q.empty())
			{
				cout << q.front() << '\n';
				q.pop();
			}
			else
				cout << -1 << '\n';
		}
		else if (str == "size")
		{
			cout << q.size() << '\n';
		}
		else if (str == "empty")
		{
			if (q.empty())
				cout << 1 << '\n';
			else
				cout << 0 << '\n';
		}
		else if (str == "front")
		{
			cout << q.front() << '\n';
		}
		else if (str == "back")
		{
			cout << q.back() << '\n';
		}
	}

	return 0;
}