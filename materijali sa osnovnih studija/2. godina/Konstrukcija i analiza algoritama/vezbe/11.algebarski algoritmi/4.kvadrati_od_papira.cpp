#include<iostream>

using namespace std;

//ovo je najjednostavnije resenje, ima jos 3 data u skripti koja su efikasnija

int broj_kvadrata(int a, int b){
  if(a==b) return 1;
  else if(a>b) return 1+broj_kvadrata(a-b,b);
  else return 1+broj_kvadrata(a,b-a);
}

int main(){

 int a,b;
 cin>>a,b;

 cout<<broj_kvadrata(a,b)<<endl;

  return 0;
}