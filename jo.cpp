#include<iostream>
using namespace std;
int main(){
    int n, i, j;
    while(cin>>n){
        for(i=0;i<n;i++){
            for(j=0;j<n;j++){
                if(n-1-j==i){
                    cout<<2;
                    continue;
                }
                if(i==j){
                    cout<<1;
                }
                else{
                    cout<<3;
                    continue;
                }
            }
            cout<<endl;
        }
    }
}