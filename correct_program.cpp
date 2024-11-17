#include <iostream> 
using namespace std;
 
int main(void){
    long long X;
    cin>>X;
    int temp;
    int a;
    for(int i=0;i<100000;i++)
        if((i+1)*(i+2)/2>=X){
            temp=i+1;
            a=X-i*(i+1)/2;
            break;
        }
    
    if(X==1)
        cout<<"1/1";
    else if(temp%2==0)
        cout<<a<<"/"<<temp+1-a;
    else
        cout<<temp+1-a<<"/"<<a;
    
    return 0;
}
