#include<iostream>

using namespace std;


int nzd(int a, int b){
  if(b==0) return a;
  return nzd(b,a%b);
}

int main(){

 int a,b,c;
 cin>>a,b,c;

 cout<<nzd(nzd(a,b),c)<<endl;

  return 0;
}