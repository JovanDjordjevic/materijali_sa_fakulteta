#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>

#define eps 0.000001  //za poredjenje realnih brojeva

using namespace std;

struct Tacka{
  double x,y;
}tacke[333555];

//ovo 333555 je kao limit dat u zadatku, ovako smo definisali niz tacaka jer nam je potreban za 
//ove dve funkcije ispod, mogli smo i kao vector u mainu pa da ga prosledimo funkcijama

//u1 i u2 su zapravo tangensi ugla prave iz najlevlje tacke(tacke[0]) do p1 odnosno p2
bool cmp(Tacka p1, Tacka p2){
  double u1,u2;
  if( fabs(p1.y-tacke[0].y)<eps ) return false;  //da ne delimo nulom
  if( fabs(p2.y-tacke[0].y)<eps ) return false;  //isto

  u1=(p1.x-tacke[0].x) / (p1.y-tacke[0].y);
  u1=(p2.x-tacke[0].x) / (p2.y-tacke[0].y);

  return (u1<u2);
}


double rastojanje(Tacka p1,Tacka p2){
  return sqrt( (p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y)   );
}







int main(){

int n,p,i;
double d,res;
Tacka tmp;

cin>>n; //broj dece


//vector<Tacka>tacke(n);

p=0;  //indeks u nizu tacaka ekstremne tacke koju trazimo (sa najmanjom y koordinatom ili istom y kao neka druga a najmanjom x)

for(int i=0; i<n; i++){
    cin>>tacke[i].x>>tacke[i].y;
    if(tacke[i].y<tacke[p].y || (fabs(tacke[i].y - tacke[p].y)<eps && tacke[i].x<tacke[p].x )){
      p=i;
    }
}

tmp=tacke[0];
tacke[0]=tacke[p];
tacke[p]=tmp;

sort(tacke+1, tacke+n, cmp);  //sort od prve pa nadalje po uglu (na prvom mestu anm je ta ekstremna tacka)

res=rastojanje(tacke[0],tacke[n-1]);

for(int i=1;i<n;i++){
  d=rastojanje(tacke[i],tacke[i-1]);
  if(d<res) res=d;
}

printf("%.2lf\n",res);

  return 0;
}