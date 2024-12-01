#include <iostream> 
using namespace std;



int main(void){
    int N;
    cin>>N;
    int count=1;
    int num[1000]={0};
    int temp[1000]={0};
    int i=0;
    int t=1;

    for(int i=0;i<N;i++)
        cin>> num[i];

    while(count != N){
        if(num[i]==count){
            count++;
            i++;
        }
        else if(temp[t-1]==count){
            temp[t-1]=0;
            t--;
            count++;
            
            }
        else {           
            
            temp[t]=num[i];
            i++;
            t++;
            
        }
        if(t>1){
                if(temp[t-1]<temp[t]){
                    cout<<"Sad";
                    
                    return 0;
                    }
            }
    }
    cout<<"Nice";


    return 0;
}
