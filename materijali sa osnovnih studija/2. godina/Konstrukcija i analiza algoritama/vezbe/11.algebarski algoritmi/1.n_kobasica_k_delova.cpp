#include<iostream>

using namespace std;

//nase resenje je rez=k-nzd(n,k)
int main(){

  int n,k;
  cin>>n,k;

  int rezani_kraj=0;
  for(int i=1;i<k;++i)
      rezani_kraj+= (i * n % k==0);

  cout<<k-1-rezani_kraj<<endl;

  return 0;
}