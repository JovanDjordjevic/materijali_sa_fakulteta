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

//proizvod dva broja po modulu
long long pm(long long x,long long y,long long n){
  return ((x%n)*(y%n))%n;
}
//proizvod tri broja po modulu
long long pm(long long x,long long y,long long z,long long n){
  return pm(pm(x,y,n),z,n);
}
//zbir dva broja po modulu
long long zm(long long x,long long y,long long n){
  return ((x%n)+(y%n))%n;
}


bool kto(long long n[],long long a[],int duzina, long long &rezultat){
  long long N=1;
  for(int i=0;i<duzina;i++)
    N*=n[i];                   //N=n1*n2*n3

  rezultat=0;
  for(int i=0;i<duzina;i++){
    long long pi=N/n[i];
    long long pi_inv;
    if(!inverz(pi,n[i],pi_inv)) return false;
    rezultat=zm(rezultat,pm(a[i],pi_inv,pi,N),N);
  }  
  return true;
}

int main(){

  long long a[3],n[3];
  for(int i=0;i<3;i++)
    cin>>a[i]>>n[i];

    long long rezultat;
    kto(n,a,3,rezultat);
  
    cout<<rezultat;

  return 0;
}