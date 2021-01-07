#include<iostream>
#include<vector>
#include<set>
#include<algorithm>

using namespace std;

int main(){

  long n,i,dx,dy,gx,gy,x1,x2,y1,y2;
  cin>>n;
  cin>>dx>>dy>>gx>>gy;

  for(int i=2;i<=n;i++){
    cin>>x1>>y1>>x2>>y2;
    if(x1>dx)
      dx=x1;
    if(x2<gx)
      gx=x2;
    if(y1>dy)
      dy=y1;
    if(y2<gy)
      gy=y2;
    if((gy-dy<1) || (gx-dx<1) ){
      cout<<"0";    //nema preseka ako se ovo desi
      return 0;
    } 

  }

  cout<<(gy-dy)*(gx-dx)<<endl;

  return 0;
}