//moja funkc ne radi dobro a njena radi ali ne vidim gde sam pogresio

#include <iostream>
#include <algorithm>
#include <vector>


using namespace std;

class Tacka{
public:
Tacka(){}                         //moramo da iammo prazan konstruktor zbog one globalne tacke
Tacka(int a, int b){ x=a; y=b;}
int getX(){return x;}
int getY(){return y;}
private:
int x;
int y;
};

Tacka P0;  //globalna, sluzi nam za sort


int orijentacija(Tacka &p,Tacka &q,Tacka &r){
  int val=(q.getY()-p.getY())*(r.getX()-q.getX())-(q.getX()-p.getX())*(r.getY()-q.getY());
  if(val==0) return 0;
  return (val>0) ? 1 : 2;  //1 neg 2 poz
}

//ne moramo sqrt jer nas interesuje odnos a ne konkretna razdaljina
int rastojanje(Tacka &p1,Tacka &p2){
  return (p1.getX()-p2.getX())*(p1.getX()-p2.getX()) + (p1.getY()-p2.getY())*(p1.getY()-p2.getY());
}

//hocemo prvo poz orjentaciju pa onda neg
bool compare(Tacka &p1,Tacka &p2){
  int orient=orijentacija(P0,p1,p2);
  if(orient==2) return true;  
  else if(orient==1) return false;
  return rastojanje(P0,p1) < rastojanje(P0,p2);
}




void symple_polygon(vector<Tacka> &tacke){
  int indeks_ekstremne_tacke=0;  //trazimo tacku sa najvecom x i najmanjom y koord
  int maxX=tacke[0].getX();
  int minY=tacke[0].getY();

  int n=tacke.size();
  for(int i=1;i<n;i++){
    if(tacke[i].getX() > maxX){
      maxX=tacke[i].getX();
      minY=tacke[i].getY();
      indeks_ekstremne_tacke=i;
    }
    else if(tacke[i].getX()==maxX){
      if(tacke[i].getY()<minY){
        minY=tacke[i].getY();
        indeks_ekstremne_tacke=i;
      }
    }
  }
   
   Tacka tmp=tacke[0];
   tacke[0]=tacke[indeks_ekstremne_tacke];
   tacke[indeks_ekstremne_tacke]=tmp;

   P0=tacke[0];

   sort(tacke.begin()+1,tacke.end(),compare);

   vector<Tacka> rezultat;
   rezultat.push_back(tacke[0]);
   rezultat.push_back(tacke[1]);
   rezultat.push_back(tacke[2]);
  
   int m=2;

   for(int k=3;k<n;k++){
     //idemo kroz ostale tacke i ako naidjemo na neku takvu da izmedju poslednje dve dodate tacke i te trenutne
     //vazi da cine trougao neg orijentacije to znaci da poslednju dodatu treba izvbaciti iz rez
     while(orijentacija(rezultat[m-1],rezultat[m],tacke[k])==1){
       rezultat.pop_back();
       m--;
     }

     m++;
     rezultat.push_back(tacke[k]);
   }


   cout<<"konveksni omotac cine tacke:"<<endl;
   for(Tacka &p : rezultat){
     cout<<p.getX()<<" "<<p.getY()<<endl;
   }

} 

  




int main(){

  vector<Tacka> tacke ={ {0, 3}, {2, 2}, {6, 4}, {1, 1}, {2, 1}, {2, 5}, {3, 0}, {0, 0}, {3, 3} };

  
  symple_polygon(tacke);
  

  return 0;
}