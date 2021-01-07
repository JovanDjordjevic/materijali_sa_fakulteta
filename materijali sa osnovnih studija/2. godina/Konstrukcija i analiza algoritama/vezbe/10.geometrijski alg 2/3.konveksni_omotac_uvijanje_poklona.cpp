#include <iostream>
#include <algorithm>
#include <vector>
#include<cmath>

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

//po onoj dormuli a*b=|a|*|b|*cos(fi)
float ugao_izmedju_linija(Tacka &p1,Tacka &p2,Tacka &p3,Tacka &p4){
    int v1x=p2.getX()-p1.getX();  //prvi vektor cine tacke p1 i p2
    int v1y=p2.getY()-p1.getY();
    int v2x=p4.getX()-p3.getX();   //a drugi tacke p3 i p4
    int v2y=p4.getY()-p3.getY();

    int skalar=v1x*v2x+v1y*v2y;
    
    return acos( (skalar)/ ( sqrt(v1x*v1x + v1y*v1y) * sqrt(v2x*v2x + v2y*v2y) ) );
}








void uvijanje_poklona(vector<Tacka> &tacke){
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

  Tacka tmp=tacke[0];                         //tu ekstremnu stavljamo na pocetak niza
  tacke[0]=tacke[indeks_ekstremne_tacke];
  tacke[indeks_ekstremne_tacke]=tmp;

  vector<Tacka> rezultat;
  
  Tacka p=tacke[0];
  Tacka ekstremna_tacka=p;

  Tacka l0=p,  l1{p.getX()+2,p.getY()};   //ne razumem, u resenju kaze da ima u knjizi objasnjenje

  float min_ugao,ugao;
  int min_ugao_indeks;

  do{
    min_ugao=5.0;  //treba da postavimo na pocetku na nesto vece od Pi
    rezultat.push_back(p);

    for(int i=0;i<n;i++){
      if(p.getX()==tacke[i].getX() && p.getY()==tacke[i].getY()) continue;
      ugao=ugao_izmedju_linija(l0,l1,p,tacke[i]);
      if(ugao<min_ugao){
        min_ugao=ugao;
        min_ugao_indeks=i;
      }
    }

    l0=p;
    p=tacke[min_ugao_indeks];
    l1=p;

  }while(p.getX()!=ekstremna_tacka.getX() ||  p.getY()!=ekstremna_tacka.getY());


  for(Tacka p : rezultat){
    cout<<p.getX()<<" "<<p.getY()<<endl;
  }

}






int main(){

  vector<Tacka> tacke ={ {0, 3}, {2, 2}, {6, 4}, {1, 1}, {2, 1}, {2, 5}, {3, 0}, {0, 0}, {3, 3} };

  
  uvijanje_poklona(tacke);
  

  return 0;
}