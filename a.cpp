#include <iostream>
#include <iomanip>
using namespace std;
int main(){
  int i,j,n,x,a,b;
  while(cin>>n) {
    for(i=1;i<=n;i++){
      a=1;
      b=1;
      for(j=1;j<=n;j++){
        x=i;
        if((i>1)&&(j>1)){
          if(i>j){
            x=x-a;
            a++;
          }
          if(i==j)
            x=1;
        }
        if(j>i){
          x=1;
          x=x+b;
          b++;
        }
        cout<<right<<setw(3)<<x;
        if(j<n)
          cout<<" ";
        else
          cout<<endl;
      }
    }
    cout<<endl;
  }
}