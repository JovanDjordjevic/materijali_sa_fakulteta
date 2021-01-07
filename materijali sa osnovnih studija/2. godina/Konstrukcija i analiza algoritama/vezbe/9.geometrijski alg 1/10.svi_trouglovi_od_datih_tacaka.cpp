//ne racuna dobro, u odnosu na njeno resenje promenio sam samo sto sam tacke cuvao u vektoru

#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>

using namespace std;

struct Tacka{
  char ime;
  int x;
  int y;
};


//kao u zadatku za konveksni mnogougao, ako su obe strane one proporcije iste onda su tri tacke kolinearne
//ovde nam pravu obrazuju npr a i b, a za c ispitujemo
bool kolinearne(Tacka a,Tacka b, Tacka c){
  int a1=b.x - a.x;
  int a2=b.y - a.y;
  int b1=c.x - a.x;
  int b2=c.y - b.y;
   return a1*b2 == a2*b1;
}



int main(){

int n;
cin>>n;
vector<Tacka> tacke(n);

for(int i=0;i<n;i++){
  cin>>tacke[i].ime>>tacke[i].x>>tacke[i].y;
}

bool nadjeno=false;

for(int i=0;i<n;i++)
  for(int j=i+1;j<n;j++)
    for(int k=j+1;k<n;k++)
      if(!kolinearne(tacke[i],tacke[j],tacke[k])){
        nadjeno=true;
        cout<<tacke[i].ime<<" "<<tacke[j].ime<<" "<<tacke[k].ime<<endl;
      }
  
  if(!nadjeno)
    cout<<"nema trouglova"<<endl;

  return 0;
}