#include <bits/stdc++.h>
using namespace std;
int main() {
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	string tmp,a[6]={"push","front","back","size","empty","pop"};
	int n,nn;
	cin>>n;
	queue<int> q;
	
	for(int i=0;i<n;i++){
		cin>>tmp;
		if(tmp==a[0]){
			cin>>nn;
			q.push(nn);
		}
		else if(tmp==a[1]){
			if(!q.empty()) cout<<q.front()<<"\n";
			else cout<<"-1\n";
		}
		else if(tmp==a[2]){
			if(!q.empty()) cout<<q.back()<<"\n";
			else cout<<"-1\n";
		}
		else if(tmp==a[3]){
			cout<<q.size()<<"\n";
		}
		else if(tmp==a[4]){
			if(q.empty()) cout<<"1\n";
			else cout<<"0\n";
		}
		else if(tmp==a[5]){
			if(q.empty()) cout<<"-1\n";
			else{
				nn=q.front();
				q.pop();
				cout<<nn<<"\n";
			}
		}
	}
	return 0;
}
