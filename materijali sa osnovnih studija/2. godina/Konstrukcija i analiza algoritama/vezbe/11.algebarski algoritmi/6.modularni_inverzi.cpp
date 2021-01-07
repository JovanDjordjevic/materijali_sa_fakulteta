#include<iostream>

using namespace std;

//inverz je t takav da a*t mod n =1
bool inverz(long long a, long long n, long long &t){
  long long r=n, r1=a;
  t=0;
  long long t1=1;
  
  while(r1>0){
    long long q=r/r1;
    long long tmp;

    tmp=r;
    r=r1;
    r1=tmp-q*r1;

    tmp=t;
    t=t1;
    t1=tmp-q*t1;
  }
  if(t<0)
       t+=n;
  return r==1;
}


int main(){

  long long a,n;

    cin>>a>>n;

    long long inv_a;
    inverz(a,v,inv_a);

    long long x;
    while(cin>>x){
      cout<<(inv_a*x)%n<<endl;
    }
  return 0;
}