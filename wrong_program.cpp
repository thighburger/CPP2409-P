#include <iostream> 
using namespace std;
 
int main(void){
    long long X;
    cin>>X;
    long long temp;
    long long horse;
    long long k;

    for(int i=1;i<10000001;i++){
    
        if((i*(i+1)/2) > X){
            temp=X-(i-1)*i/2;
            horse=i%2;
            k=i;
            break;
        }
    }
    if(X==1)
        cout<<"1/1";
    else if(X==2)
        cout<<"1/2";
    else if(X==3)
        cout<<"2/1";
    else if(horse==0){//�� 1/i��
        cout<<temp<<"/"<<k-temp+1;
    }
    else//    i/1   
        cout<<k-temp+1<<"/"<<temp;
        
    return 0;
}
