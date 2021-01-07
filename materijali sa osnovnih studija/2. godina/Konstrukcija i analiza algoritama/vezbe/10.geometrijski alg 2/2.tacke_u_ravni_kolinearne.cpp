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


Tacka P0; //globalna, koristimo u sortiranju kao pcoetak prave


int orijentacija(Tacka p, Tacka q,Tacka r){
  int val=(q.getY()-p.getY())*(r.getX()-q.getX()) - (q.getX()-p.getX())*(r.getY()-q.getY());
  if(val==0) return 0;
  else return (val>0) ? 1 : 2;
}



bool compare(Tacka &p1, Tacka &p2){
    int orient=orijentacija(P0,p1,p2);
    if(orient==0){
      cout<<"IMA KOLINEARNIH"<<endl;
      exit(EXIT_SUCCESS);
    }

    else return orient==2;
}




void tri_kolinearne(vector<Tacka> &tacke){
  int n=tacke.size();
  for(int i=0;i<n;i++){
      Tacka tmp=tacke[0];
      tacke[0]=tacke[i];
      tacke[i]=tmp;

      P0=tacke[0];
      sort(tacke.begin()+1,tacke.end(),compare);
  }
}



int main(){
  vector<Tacka> tacke={{0, 0}, {1, 3}, {2, 5}, {4, 7}, {5, 9}, {7, 2}, {1, 1}, {2, 2}};

  tri_kolinearne(tacke);

  cout<<"nema kolinearnih"<<endl;//ako smo dosli do oovde onda ih neam jer da ima prekinulo bi se u compare funkciji sortiranja 

  return 0;
}