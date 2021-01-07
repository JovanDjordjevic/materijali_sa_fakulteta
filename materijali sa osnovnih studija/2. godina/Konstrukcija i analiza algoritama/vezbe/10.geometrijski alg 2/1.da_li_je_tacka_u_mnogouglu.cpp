//bezvezxe je komplikovala sa klasama, moglo je samo sa strukturama

#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;


Tacka P0;  //globalna, sluzice nam za sortiranje

class Tacka{
  public: 
     Tacka(int x, int y){
       this.x=x;
       this.y=y;
     }
     int getX(){
       return x;
     }
     int getY(){
       return y;
     }
private:
int x;
int y;
};


class Mnogougao{
  public:
  Mnogougao(vector<Tacka> &ps){
    tacke=ps;
  }
   
int orijentacija(Tacka p,Tacka q,Tacka r){
  int val=(q.getY()-p.getY()) * (r.getX()-q.getX()) - (q.getX()-p.getX())*(r.getY()-q.getY());
  if(val==0) return 0;
  else return (val>0) ? 1 : 2;  //1 neg, 2 poz
} 

bool u_trouglu(Tacka a, Tacka b, Tacka c, Tacka d){
    //ona func od proslog cassa ili ona koja proverava povrsine 3 manja trougla, mrzi me da pisem ovo sad
}   





  bool binarna_pretraga(Tacka &p){
    int l=tacke.size()-1;
    int r=1;
    int s;

    Tacka lp=tacke[l], rp=tacke[r];
    Tacka start=tacke[0];

    while(abs(l-r)>1){
      s=(l+r)/2;
      if(orijentacija(start,tacke[s],p)==1){
        lp=tacke[s];
        l=s;
      }
      else{
        rp=tacke[s];
        r=s;
      }
    }
    cout<<l<<" "<<r<<endl;
    return u_trouglu(start,lp,rp,p);
  }

  private:
  vector<Tacka> tacke;
};







int orijentacija(Tacka p,Tacka q,Tacka r){
  int val=(q.getY()-p.getY()) * (r.getX()-q.getX()) - (q.getX()-p.getX())*(r.getY()-q.getY());
  if(val==0) return 0;
  else return (val>0) ? 1 : 2;  //1 neg, 2 poz
}

//ne mroamo koren jer nam treba odnos rastojanja a ne bas samo rastojanje
bool rastojanje(Tacka &p1, Tacka &p2){
  return (p1.getX()-p2.getX())*(p1.getX()-p2.getX()) + (p1.getY()-p2.getY())*(p1.getY()-p2.getY());
}

bool compare(Tacka &p1, Tacka &p2){
  int orient=orijentacija(P0,p1,p2);
  if(orient==2) return true;   //ako je pozitivna orijentacija onda p1 treba da bude pre p2
  else if(orient==1) return false;  //ako je neg onda p2 pre p1
  else
    return rastojanje(P0,p1) < rastojanje(P0,p2); //ako su kolinearne onda se sortijraju prema udaljenosti od P0
}




Mnogougao simple_polygon(vector<Tacka> &tacke){
  int indeks_ekstremne_tacke=0;    //trazimo tacku sa najvecom x koordinatom ili ako ima vise onda sa najmanjom y
  int maxX=tacke[0].getX();
  int minY=tacke[0].getY();
  int n=tacke.size();

  for(int i=1;i<n;i++){
    if(tacke[i].getX()>maxX){
      maxX=tcke[i].getX();
      minY=tacke[i].getY();
      indeks_ekstremne_tacke=i;
    }
    else if(tacke[i].getX()==maxX)
      if(tacke[i].getY() < minY){
        minY=tacke[i].getY();
        indeks_ekstremne_tacke=i;
      }
  }
     
  Tacka tmp=tacke[0];                       //zamenimo prvu u nizu i ekstremnu i sortitramo
  tacke[0]=tacke[indeks_ekstremne_tacke];
  tacke[indeks_ekstremne_tacke]=tmp;

  P0=tacke[0];   //ovo je ona globalna koju koristimo za sortiranje, dakle ekstremna tacka koja je sad na pocetku niza 

  sort(tacke.begin()+1,tacke.end(),compare);
  
  vector<Tacka> rezultat;
  rezultat.push_back(tacke[0]);
  rezultat.push_back(tacke[1]);
  rezultat.push_back(tacke[2]);  

  int m=2;

  for(int k=3;k<n;k++){
    while(orijentacija(rezultat[m-1],rezultat[m],tacke[k])==1){
      rezultat.pop_back();
      m--;
    }

    m++;
    rezultat.push_back(tacke[k]);
  }

  Mnogougao p(rezultat);
  return p;
}






int main(){

  vector<Tacka> tacke = { {0, 3}, {1, 1}, {2, 2}, {4, 4}, {0, 0}, {1, 2}, {3, 1}, {3, 3} };
 
  Mnogougao p=simple_polygon(tacke);

  Tacka t(5,5);

  cout<<p.binarna_pretraga(t)<<endl;


  return 0;
}